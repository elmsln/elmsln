<?php

class FieldFeaturesBuilder extends FeaturesBuilderBase {

  public static function listFeatures() {
    return array('fields' => t('Fields'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  protected function setComponents() {
    $this->setAllComponents('field_base');
    
    // Add dependencies to all modules declaring a field type that's in use.
    foreach (field_info_fields() as $info) {
      $this->setNamedComponents('dependencies', array($info['module']));
    }

    // Field permissions module, if enabled.
    if (module_exists('field_permissions')) {
      $this->setNamedComponents('dependencies', array('field_permissions'));
    }
  }

}
