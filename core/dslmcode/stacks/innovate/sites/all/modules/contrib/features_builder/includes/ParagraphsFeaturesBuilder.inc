<?php

class ParagraphsFeaturesBuilder extends EntityFeaturesBuilder {

  public static function listFeatures() {
    return array('paragraphs' => t('Paragraphs'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  protected function setComponents() {

    if (!$bundles = field_info_bundles('paragraphs_item')) {
      return;
    }

    $dependencies[] = $this->prefix . '_fields';
    $dependencies[] = 'paragraphs';

    $this->setNamedComponents('dependencies', $dependencies);
    $this->setAllComponents('paragraphs');

    foreach ($bundles as $bundle => $bundle_label) {
     $this->setFields('paragraphs_item', $bundle);
    }

  }

}
