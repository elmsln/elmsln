<?php

/**
 * @file
 * Contains the CER plugin for Taxonomy Term Reference fields.
 */
 
class CerTaxonomyTermReferenceField extends CerField {

  /**
   * Implements CerField::getTargetType().
   */
  public function getTargetType() {
    return 'taxonomy_term';
  }
  
  /**
   * @override CerField::getTargetBundles().
   */
  public function getTargetBundles() {
    $bundles = array();

    foreach ($this->settings['allowed_values'] as $item) {
      $bundles[] = $item['vocabulary'];
    }

    return $bundles;
  }

}
