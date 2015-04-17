<?php
/**
 * @file
 * Defines the class AuthcacheP13nObjectFactory.
 */

/**
 * A utility class helping with dependency injection.
 *
 * When following the design principle of object composition, it is common for
 * single instances to depend on many other objects. However it can be tedious
 * to wire them up in the first place, especially when the system should remain
 * flexible enough such that single implementations can be easily be swapped
 * out. This class provides methods to keep that process straight forward.
 *
 * Instances of this class each maintain a catalog of resources. Each resource
 * is specified using a blueprint describing the method and parameters
 * necessary to realize it. A resource is only constructed when necessary, i.e.
 * when client code requests it (using AuthcacheP13nObjectFactory::get) or when
 * referenced from another resource.
 *
 * Resources can be defined using an associative array. The simplest definition
 * for a plain value is:
 * @code
 *   $resources['plain_value'] = array(
 *     '#type' => 'value',
 *     '#value' => 42,
 *   );
 * @endcode
 * Other values for the '#type' key include '#class' and '#func' respectively,
 * providing a way to supply constructors and factory methods:
 * @code
 *   $resources['some_class'] = array(
 *     '#type' => 'class',
 *     '#class' => 'SomeClass',
 *     '#arguments' => array('some', 'constructor', 'arguments'),
 *   );
 *   $resources['other'] = array(
 *     '#type' => 'func',
 *     '#func' => 'my_factory_method',
 *     '#arguments' => array('list', 'of', 'arguments'),
 *   );
 * @endcode
 *
 * When the '#value' and '#argument' keys of resource definitions contain
 * strings prefixed with the at-sign (e.g., '@some_class'), they are treated as
 * references to other resources. For example, when instances of a hypotethical
 * CustomerController class require a DBConnection instance, the resource
 * definition may be specified like in the following example:
 * @code
 *   $resource['db'] = array(
 *     '#type' => 'class',
 *     '#class' => 'MariaDBConnection',
 *   );
 *   $resource['customer_controller'] = array(
 *     '#type' => 'class'
 *     '#class' => 'CustomerController',
 *     '#arguments' => array('@db'),
 *   );
 * @endcode
 *
 * Note that referenced resources are only instantiated when the referencing
 * resources are realized. Also note that once a resource is realized, the
 * same object/value is returned on subsequent requests.
 *
 * Sometimes it is necessary to run some code after a resource has been
 * resolved, e.g., for checking whether it has the proper type. Processor
 * functions can be specified following a resource reference in brackets. In
 * the following example, an exception will be thrown when the @db resource
 * resolves to NULL or an inapropriate value. Resource processors may accept
 * one argument.
 * @code
 *   $resource['customer_controller'] = array(
 *     '#type' => 'class'
 *     '#class' => 'CustomerController',
 *     '#arguments' => array('@db[require_instance(MariaDBConnection)]'),
 *   );
 * @endcode
 *
 * Note that the mapping from resource processor names to actual PHP
 * implementations needs to be supplied when the object factory is
 * instantiated.
 *
 * In order to support collection of resources with a variable number of
 * members, the collection type can be used.
 * @code
 *   $resource['xss filter'] = array(
 *     '#type' => 'class'
 *     '#class' => 'XSSFilter',
 *     '#member_of' => 'filters',
 *   );
 *   $resource['html filter'] = array(
 *     '#type' => 'class'
 *     '#class' => 'HTMLFilter',
 *     '#weight' => -1,
 *     '#member_of' => 'filters',
 *   );
 *   $resource['filters'] = array(
 *     '#type' => 'collection',
 *     '#collection' => 'filters',
 *     '#processor' => 'require_instance(Filter)',
 *   );
 * @endcode
 * Retrieving the filters resource result in an array equivalent to:
 * @code
 *   array(
 *     'html filter' => new HTMLFilter(),
 *     'xss filter' => new XSSFilter(),
 *   );
 * @endcode
 */
class AuthcacheP13nObjectFactory {
  protected $resources;
  protected $processors;

  /**
   * Construct new instance and populate it with the given resources.
   *
   * @param array $resources
   *   Resource definitions (the blueprint).
   * @param array $processors
   *   (Optional) A mapping of resource processor names to PHP functions.
   */
  public function __construct($resources = array(), $processors = array()) {
    $this->resources = $resources;
    $this->processors = $processors;
  }

  /**
   * Return the value or instance for the given resource.
   */
  public function get($name) {
    $result = FALSE;

    if (isset($this->resources[$name])) {
      $r = $this->resources[$name];
      switch ($r['#type']) {
        case 'resolved':
          $result = $r['#value'];
          break;

        case 'value':
          $result = $this->resolveReferences($r['#value']);
          break;

        case 'func':
          $arguments = !empty($r['#arguments']) ? $r['#arguments'] : array();
          $arguments = $this->resolveReferences($arguments);
          $result = call_user_func_array($r['#func'], $arguments);
          break;

        case 'class':
          $arguments = !empty($r['#arguments']) ? $r['#arguments'] : array();
          $arguments = $this->resolveReferences($arguments);

          try {
            $reflection = new ReflectionClass($r['#class']);
            // Work around https://bugs.php.net/bug.php?id=52854
            if (empty($arguments)) {
              $result = $reflection->newInstance();
            }
            else {
              $result = $reflection->newInstanceArgs($arguments);
            }
          }
          catch (Exception $e) {
            throw new AuthcacheP13nObjectFactoryException(format_string('Failed to create instance of class @class', array('@class' => $r['#class'])), 0, $e);
          }
          break;

        case 'collection':
          $result = array();
          $members = $this->collectMembers($r['#collection']);
          $processor = isset($r['#processor']) ? $r['#processor'] : '';
          $processors = !empty($r['#processors']) ? $r['#processors'] : array();
          foreach ($members as $name => $definition) {
            $key = isset($definition['#key']) ? $definition['#key'] : $name;
            $ref = '@' . $name;
            if (isset($processors[$key])) {
              $ref .= '[' . $processors[$key] . ']';
            }
            elseif ($processor) {
              $ref .= '[' . $processor . ']';
            }
            $result[$key] = $this->resolveReferences($ref);
          }
          break;

        default:
          throw new AuthcacheP13nObjectFactoryException('Unknown resource type: ' . $r['#type']);
      }

      $this->resources[$name] = array(
        '#type' => 'resolved',
        '#value' => $result,
      );
    }
    else {
      throw new AuthcacheP13nObjectFactoryException('No such resource: ' . $name);
    }

    return $result;
  }

  /**
   * Substitute resource references with their actual values.
   */
  public function resolveReferences($value) {
    $result = FALSE;

    if (is_string($value)) {
      list($literal, $rname, $proc, $procarg) = static::parseReference($value);
      if ($rname) {
        $result = $this->get($rname);
        if ($proc) {
          $result = call_user_func($this->processors[$proc], $result, $procarg, $rname, $this);
          $result = $this->resolveReferences($result);
        }
      }
      else {
        $result = $literal;
      }
    }
    elseif (is_array($value)) {
      $result = array();
      foreach ($value as $key => $child) {
        $result[$key] = $this->resolveReferences($child);
      }
    }
    else {
      $result = $value;
    }

    return $result;
  }

  /**
   * Collect all resources in a collection and return an ordered array.
   */
  public function collectMembers($collection_name) {
    // Necessary until #1272900 lands
    // @ignore style_function_spacing
    $result = array_filter($this->resources, function($definition) use ($collection_name) {
      return isset($definition['#member_of']) && $definition['#member_of'] === $collection_name;
    });
    uasort($result, 'element_sort');
    return $result;
  }

  /**
   * Utility function: Parse a string value.
   *
   * The string value either may contain a literal or a resource reference.
   * References start with an @-sign, followed by the resource name, optionally
   * followed by a processor definition. I.e.: The string
   * <code>@my resource[my processor(processor arg)]</code> references the
   * resource named "my resource". Upon resolving this resource a processor
   * function will alter it before it is returned.
   *
   * @return array
   *   An array with integer indexes containing the four values:
   *   - literal or NULL: The literal value if no ressource reference was
   *     found.
   *   - resource name or NULL: The name of a resource if a reference is
   *     present.
   *   - processor function name or NULL: (Optional) The name of a reference
   *     processor.
   *   - processor argument or NULL: (Optional) The argument for a reference
   *     processor.
   *   Either literal or resource name is always set.
   */
  protected static function parseReference($value) {
    $nobr = '[^\[\]\(\)]';
    $regex = "#^@($nobr+)(\[($nobr+)(\]|\(($nobr*)\)\]))?$#";

    $literal = NULL;
    $rname = NULL;
    $proc = NULL;
    $procarg = NULL;

    if (strpos($value, '@@') === 0) {
      $literal = substr($value, 1);
    }
    elseif (preg_match($regex, $value, $matches)) {
      $rname = $matches[1];
      if (isset($matches[3])) {
        $proc = $matches[3];
      }
      if (isset($matches[5])) {
        $procarg = $matches[5];
      }
    }
    else {
      $literal = $value;
    }

    return array($literal, $rname, $proc, $procarg);
  }

  /**
   * Return the default set of processors suitable.
   */
  public static function defaultProcessors() {
    return array(
      'required' => array(__CLASS__, 'ensureIsSet'),
      'accept_instance' => array(__CLASS__, 'acceptClass'),
      'require_instance' => array(__CLASS__, 'ensureClass'),
    );
  }

  /**
   * A resource processor throwing an exception when the value is NULL.
   *
   * @throws AuthcacheP13nObjectFactoryException
   *
   * @return var
   *   The input value.
   */
  public static function ensureIsSet($value, $ignored_arg, $name) {
    if (!isset($value)) {
      throw new AuthcacheP13nObjectFactoryException("Resource $name cannot be NULL");
    }
    return $value;
  }

  /**
   * Only return value if it can be used in place of the given class.
   *
   * @return var|NULL
   *   The input value or NULL.
   */
  public static function acceptClass($value, $class) {
    if (is_a($value, $class)) {
      return $value;
    }
  }

  /**
   * Throw an exception if given value cannot be used in place of class.
   *
   * @throws AuthcacheP13nObjectFactoryException
   *
   * @return var
   *   The input value.
   */
  public static function ensureClass($value, $class, $name) {
    if (!is_a($value, $class)) {
      throw new AuthcacheP13nObjectFactoryException("Resource $name must be an instance of $class");
    }
    return $value;
  }
}
