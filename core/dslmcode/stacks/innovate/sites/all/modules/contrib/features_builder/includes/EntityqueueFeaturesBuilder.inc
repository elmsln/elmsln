<?php

class EntityqueueFeaturesBuilder extends FeaturesBuilderBase {

  public static function listFeatures() {
    return array('entityqueue' => t('Entityqueue'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'CTools';
  }

  protected function setComponents() {
    $this->setAllComponents('entityqueue_queue');
    if (!empty($this->components['entityqueue_queue'])) {
      $this->setNamedComponents('dependencies', array('entityqueue'));
    }
  }

}
