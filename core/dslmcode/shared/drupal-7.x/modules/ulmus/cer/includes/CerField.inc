<?php

/**
 * @file
 * Contains the base class for CER field plugins.
 *
 * A field plugin tells CER how to interact with fields of a certain type. If a particular
 * field type integrates with Entity API, its CER plugin can be as simple as extending
 * CerField and implementing the getTargetType() method.
 *
 * @todo
 * More info about extending CerFieldHandler to further customize field plugins.
 */

/**
 * @class
 * Represents a single field instance.
 */
abstract class CerField extends FieldInstance {

  /**
   * @var array
   * The plugin definition.
   */
  protected $plugin;

  /**
   * @var array
   */
  protected $settings = array();
  
  /**
   * @var string
   */
  public $fieldTypeLabel;

  /**
   * Gets the type of entity that can be referenced by this field, e.g. 'node'.
   *
   * @return string
   */
  abstract public function getTargetType();

  /**
   * Constructor. Pretty self-explanatory!
   */
  public function __construct(array $plugin) {
    // Store a copy of our plugin definition.
    $this->plugin = $plugin;

    list ($entity_type, $bundle, $field_name) = explode(':', $plugin['identifier']);
    parent::__construct($entity_type, $bundle, $field_name);

    // Store a copy of the field settings for convenience. At the time of this
    // writing, this is needed by the Entity Reference, Node Reference,
    // and Term Reference plugins.
    $info = field_info_field($this->name);
    $this->settings = $info['settings'];

    $type_info = field_info_field_types($info['type']);
    $this->fieldTypeLabel = $type_info['label'];
  }

  /**
   * Returns a CerFieldHandler subclass instance for the given entity.
   *
   * @param object $entity
   *  The entity to be wrapped by the handler.
   *
   * @return CerFieldHandler
   */
  public function getHandler(EntityDrupalWrapper $entity) {
    return new $this->plugin['handler']($this, $entity);
  }

  /**
   * Returns the bundles that this field instance can reference.
   *
   * @return array
   */
  public function getTargetBundles() {
    $info = entity_get_info($this->getTargetType());
    return array_keys($info['bundles']);
  }

  /**
   * Overridden.
   */
  public function requireParent() {
    return $this->plugin['require parent'];
  }

  /**
   * Overridden.
   */
  public function getParents() {
    return array_map('CerField::getPlugin', $this->plugin['parents']);
  }

  /**
   * Returns information about a particular field plugin by its identifier, or all
   * available plugins (i.e., defined by hook_cer_fields()) if no identifier is given.
   * The aggregated result of hook_cer_fields() is statically cached.
   */
  public static function getPluginInfo($identifier = NULL) {
    $info = &drupal_static(__METHOD__);

    if (! isset($info)) {
      $info = module_invoke_all('cer_fields');

      foreach ($info as $key => &$field) {
        $field += array(
          'identifier' =>
            $key,
          'parents' =>
            array(),
          'require parent' =>
            FALSE,
          'handler' =>
            'CerFieldHandler',
        );
      }
      drupal_alter('cer_fields', $info);
    }

    return ($identifier ? (isset($info[$identifier]) ? $info[$identifier] : NULL) : $info);
  }

  /**
   * Returns a single field plugin instance, by its identifier. All plugin instances
   * are statically cached.
   *
   * @param string $identifier
   *  The plugin's identifier, in the format entity_type:bundle:field_name.
   *
   * @return CerField
   *
   * @throws Exception if there's no plugin for the given identifier. Why so harsh, you
   * ask? Because CerFieldChain::unpack() utterly depends on being able to get plugin
   * instances for every field in the chain, and if it can't, it could result in myriad
   * weird and serious problems. Throwing an exception will head that off at the pass.
   */
  public static function getPlugin($identifier) {
    $instances = &drupal_static(__METHOD__);
    
    if (! isset($instances[$identifier])) {
      $info = self::getPluginInfo($identifier);
      if ($info) {
        $instances[$identifier] = new $info['class']($info);
      }
      else {
        throw new Exception("Cannot get instance of invalid plugin $identifier.");
      }
    }

    return $instances[$identifier];
  }

}
