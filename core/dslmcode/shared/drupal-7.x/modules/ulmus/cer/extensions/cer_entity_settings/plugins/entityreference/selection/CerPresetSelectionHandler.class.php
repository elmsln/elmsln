<?php

class CerPresetSelectionHandler implements EntityReference_SelectionHandler {

  private $entity;

  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new CerPresetSelectionHandler($entity_type, $entity);
  }

  public function __construct($entity_type, $entity) {
    if ($entity_type && $entity) {
      $this->entity = new EntityDrupalWrapper($entity_type, $entity);
    }
  }

  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    $options = array();

    if ($this->entity) {
      $finder = new CerPresetFinder($this->entity);
      $finder->execute();

      foreach ($finder->result['cer'] as $preset) {
        $options['cer'][$preset->pid] = $preset->label_variables['@right'];
      }

      foreach ($finder->result['cer__invert'] as $preset) {
        $options['cer'][$preset->pid] = $preset->label_variables['@left'];
      }
    }

    return $options;
  }

  public function countReferencableEntities($match = NULL, $match_operator = 'CONTAINS') {
    return sizeof($this->getReferencableEntities());
  }

  public function validateReferencableEntities(array $IDs) {
    // Don't bother validating preset IDs.
    return $IDs;
  }

  public function validateAutocompleteInput($input, &$element, &$form_state, $form) {
    return NULL;
  }

  public function entityFieldQueryAlter(SelectQueryInterface $query) {
    // NOP
  }

  public function getLabel($entity) {
    return entity_label('cer', $entity);
  }

  public static function settingsForm($field, $instance) {
    return array();
  }

}
