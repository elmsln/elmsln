<?php

class FeedsFeaturesBuilder extends FeaturesBuilderBase {

  public static function listFeatures() {
    return array('feeds' => t('Feeds'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Feeds';
  }

  protected function setComponents() {
    // Standard Feeds.
    if (module_exists('feeds')) {
      $this->setNamedComponents('dependencies', array('feeds'));
      $this->setAllComponents('feeds_importer');
      $this->setRegexComponents('variable', '/^feeds_.+/');
    }

    // Feeds Tamper.
    if (module_exists('feeds_tamper')) {
      $this->setNamedComponents('dependencies', array('feeds_tamper'));
      $this->setAllComponents('feeds_tamper');
      $this->setNamedComponents('variable', array('default_feeds_tamper'));
    }

  }

}
