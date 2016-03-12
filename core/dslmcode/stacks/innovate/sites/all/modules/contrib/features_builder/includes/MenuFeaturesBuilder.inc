<?php

class MenuFeaturesBuilder extends FeaturesBuilderBase {

  public static function listFeatures() {
    return array('menu' => t('Menu'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  protected function setComponents() {
    $this->setAllComponents('menu_custom');
    if (!empty($this->components['menu_custom'])) {
      $this->setNamedComponents('dependencies', array('menu'));
    }
  }

}
