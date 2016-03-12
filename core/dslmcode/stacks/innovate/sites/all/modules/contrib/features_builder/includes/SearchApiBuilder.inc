<?php

class SearchApiBuilder extends FeaturesBuilderBase {

  protected $callbacks = NULL;
  protected $processors = NULL;

  /**
   * {@inheritdoc}
   */
  public static function listFeatures() {
    return array('search_api' => t('Search API'));
  }

  /**
   * {@inheritdoc}
   */
  protected function setComponents() {
    // Bail if not using Search API.
    if (!module_exists('search_api')) {
      return;
    }

    $this->setNamedComponents('dependencies', array('search_api'));
    $this->setAllComponents('search_api_index');
    $this->setAllComponents('search_api_server');

    foreach (search_api_server_load_multiple(FALSE) as $server) {
      if (!empty($server->status)) {
        $this->setServerDependencies($server);
      }
    }

    foreach (search_api_index_load_multiple(FALSE) as $index) {
      if (!empty($index->enabled)) {
        $this->setIndexDependencies($index);
      }
    }
  }

  /**
   * Add dependencies used by a server.
   */
  protected function setServerDependencies($server) {
    $services = search_api_get_service_info();
    $service = $services[$server->class];

    // Service class.
    $this->setNamedComponents('dependencies', array($service['module']));
  }

  /**
   * Add dependencies used by an index.
   */
  protected function setIndexDependencies($index) {
    // Data alteration callbacks.
    foreach ($index->options['data_alter_callbacks'] as $name => $config) {
      if (!empty($config['status'])) {
        $this->setDataAlteration($name, $config);
      }
    }

    // Processors.
    foreach ($index->options['processors'] as $name => $config) {
      if (!empty($config['status'])) {
        $this->setProcessor($name, $config);
      }
    }
  }

  /**
   * Add dependencies used by an index's data alteration callbacks.
   */
  protected function setDataAlteration($name, $config) {
    // Invoke search_api_alter_callback_info so we can track which module
    // provided which processor. Unfortunately we can't track changes made via
    // hook_search_api_alter_callback_info_alter().
    if ($this->callbacks === NULL) {
      $this->callbacks = array();
      foreach (module_implements('search_api_alter_callback_info') as $module) {
        $function = $module ."_search_api_alter_callback_info";
        $data = $function();
        foreach (array_keys($data) as $callback) {
          $this->callbacks[$callback] = $module;
        }
      }
    }

    if (!empty($this->callbacks[$name])) {
      $this->setNamedComponents('dependencies', array($this->callbacks[$name]));
    }
  }

  /**
   * Add dependencies used by an index's processors.
   */
  protected function setProcessor($name, $config) {
    // Invoke hook__search_api_processor_info so we can track which module
    // provided which processor. Unfortunately we can't track changes made via
    // hook_search_api_processor_info_alter().
    if ($this->processors === NULL) {
      $this->processors = array();
      foreach (module_implements('search_api_processor_info') as $module) {
        $function = $module ."_search_api_processor_info";
        $data = $function();
        foreach (array_keys($data) as $processor) {
          $this->processors[$processor] = $module;
        }
      }
    }

    if (!empty($this->processors[$name])) {
      $this->setNamedComponents('dependencies', array($this->processors[$name]));
    }
  }

}
