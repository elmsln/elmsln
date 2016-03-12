<?php

class TaxonomyFeaturesBuilder extends EntityFeaturesBuilder {

  public static function listFeatures() {
    return array('taxonomy' => t('Taxonomy'));
  }

  /**
   * {@inheritdoc}
   */
  public function package() {
    return 'Configuration';
  }

  protected function setComponents() {
    $this->setAllComponents('taxonomy');

    if (empty($this->components['taxonomy'])) {
      return;
    }

    $this->setNamedComponents('dependencies', array('taxonomy'));
    foreach ($this->components['taxonomy'] as $bundle => $bundle_label) {
     $this->setFields('taxonomy_term', $bundle);
    }

    $dependencies = array();
    if (field_info_bundles('taxonomy_term')) {
      $dependencies[] = $this->prefix . '_fields';
    }

  }

}
