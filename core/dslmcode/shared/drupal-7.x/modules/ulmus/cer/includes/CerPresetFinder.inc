<?php

/**
 * This class is a unified way for CER to find the presets that apply to a given
 * entity. The result set is segmented into two parts: presets where the entity
 * is on the left side, and bidirectional presets with the entity on the right
 * side (i.e., the ones which need to be inverted before use). The execute()
 * method will return a merged and sorted array of presets, but the segmented
 * result set is exposed to the world as well for other uses (i.e., CER Entity
 * Settings' selection handler).
 */
class CerPresetFinder extends EntityFieldQuery {

  public $result = array();

  protected $entity;

  public function __construct(EntityDrupalWrapper $entity) {
    $this->entity = $entity;

    $this
      ->entityCondition('entity_type', 'cer')
      ->addTag('cer_presets')
      ->addMetaData('entity', $entity);
  }

  public function execute() {
    $lineage = $this->entity->cer->lineage->value();

    $this->result['cer'] = $this
      ->fieldCondition('cer_enabled', 'value', TRUE)
      ->fieldCondition('cer_left', 'path', $lineage, 'STARTS_WITH')
      ->_load(parent::execute());

    $this->fieldConditions = array();

    $this->result['cer__invert'] = $this
      ->fieldCondition('cer_enabled', 'value', TRUE)
      ->fieldCondition('cer_bidirectional', 'value', TRUE)
      ->fieldCondition('cer_right', 'path', $lineage, 'STARTS_WITH')
      ->_load(parent::execute());
      
    $result = $this->result['cer'];
    foreach ($this->result['cer__invert'] as $preset) {
      $result[] = $preset->invert();
    }
    usort($result, array($this, '_sort'));

    return $result;
  }

  private function _load(array $result) {
    return isset($result['cer']) ? entity_load('cer', array_keys($result['cer'])) : array();
  }

  private function _sort(CerPreset $a, CerPreset $b) {
    $a_weight = $a->wrapper->cer_weight->value();
    $b_weight = $b->wrapper->cer_weight->value();

    if ($a_weight > $b_weight) {
      return 1;
    }
    elseif ($b_weight > $a_weight) {
      return -1;
    }
    else {
      return 0;
    }
  }

}
