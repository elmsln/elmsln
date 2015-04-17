<?php
/**
 * @file
 * Defines the class AuthcacheP13nObjectResourcePreprocessor.
 */

/**
 * A utility class suitable for preparing resources for the object factory.
 *
 * @see AuthcacheP13nObjectFactory
 */
class AuthcacheP13nObjectResourcePreprocessor {
  protected $types;
  protected $preprocessors;

  /**
   * Construct new instance and populate it with the given resources.
   *
   * @param array $preprocessors
   *   (Optional) A mapping of resource processor names to PHP functions.
   */
  public function __construct(array $preprocessors) {
    $this->preprocessors = $preprocessors;
    $this->types = array(
      'value' => 'value',
      'func' => 'func',
      'class' => 'class',
      'collection' => 'collection',
    );
  }

  /**
   * Process a list of resource definitions.
   */
  public function preprocess(array $resources) {
    // Priority queue for processable resources.
    $priq = array(array(0, $resources));
    $enqueue = function(array $new_resources, $priority = 0) use (&$priq) {
      $priq[] = array($priority, $new_resources);
    };

    // Process all unprocessed resources and put them into the result map.
    $processed = array();
    while (count($priq)) {
      list($priority, $definitions) = array_shift($priq);
      foreach ($definitions as $key => $definition) {
        foreach ($this->preprocessors as $processor) {
          $result = call_user_func($processor, $definition, $priority, $key, $enqueue);
          if (isset($result)) {
            $definition = $result;
          }
        }
        $processed[$priority][$key] = $definition;
      }
    }

    // Sort processed resource sets by priority.
    ksort($processed);

    // Merge processed resource sets into one.
    $result = array();
    foreach ($processed as $definitions) {
      foreach ($definitions as $key => $definition) {
        $result[$key] = $definition;
      }
    }

    return $this->sanitize($result);
  }

  /**
   * Wrap any invalid resource into a value-resource.
   */
  protected function sanitize(array $resources) {
    $sanitized = array();

    foreach ($resources as $key => $definition) {
      if (is_array($definition) && isset($definition['#type']) && isset($this->types[$definition['#type']])) {
        $sanitized[$key] = $definition;
      }
      elseif (isset($definition)) {
        $sanitized[$key] = array(
          '#type' => 'value',
          '#value' => $definition,
        );
      }
    }

    return $sanitized;
  }

  /**
   * Return the default set of preprocessors.
   */
  public static function defaultPreprocessors() {
    return array(
      'value' => array(__CLASS__, 'processValue'),
      'collection' => array(__CLASS__, 'processCollection'),
      'func' => array(__CLASS__, 'processFactoryMethod'),
      'class' => array(__CLASS__, 'processClassConstructor'),
    );
  }

  /**
   * Detect a value resource and add defaults.
   */
  public static function processValue($resource) {
    if (!is_array($resource)) {
      return array(
        '#type' => 'value',
        '#value' => $resource,
      );
    }

    if (isset($resource['#value'])) {
      return $resource + array(
        '#type' => 'value',
      );
    }
  }

  /**
   * Detect a collection resource and add defaults.
   */
  public static function processCollection($resource) {
    if (is_array($resource) && isset($resource['#collection'])) {
      return $resource + array(
        '#type' => 'collection',
      );
    }
  }

  /**
   * Detect a factory method resource and add defaults.
   */
  public static function processFactoryMethod($resource) {
    if (is_array($resource) && isset($resource['#func'])) {
      return $resource + array(
        '#type' => 'func',
      );
    }
  }

  /**
   * Detect a class constructor resource and add defaults.
   */
  public static function processClassConstructor($resource) {
    if (is_array($resource) && isset($resource['#class'])) {
      return $resource + array(
        '#type' => 'class',
      );
    }
  }
}
