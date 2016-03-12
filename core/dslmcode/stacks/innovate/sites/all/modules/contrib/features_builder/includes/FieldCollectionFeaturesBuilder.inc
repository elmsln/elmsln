<?php

class FieldCollectionFeaturesBuilder extends EntityFeaturesBuilder {

  public static function listFeatures() {
    return array('field_collection' => t('Field Collection'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  protected function setComponents() {

    if (!$bundles = field_info_bundles('field_collection_item')) {
      return;
    }

    $dependencies[] = $this->prefix . '_fields';
    $dependencies[] = 'field_collection';

    $this->setNamedComponents('dependencies', $dependencies);
    $this->setAllComponents('field_collection');

    foreach ($bundles as $bundle => $bundle_label) {
     $this->setFields('field_collection_item', $bundle);
    }

  }

}
