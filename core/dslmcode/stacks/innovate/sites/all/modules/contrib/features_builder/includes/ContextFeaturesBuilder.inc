<?php

class ContextFeaturesBuilder extends FeaturesBuilderBase {

  public static function listFeatures() {
    return array('context' => t('Context'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'CTools';
  }

  protected function setComponents() {
    $this->setAllComponents('context');
  }

}
