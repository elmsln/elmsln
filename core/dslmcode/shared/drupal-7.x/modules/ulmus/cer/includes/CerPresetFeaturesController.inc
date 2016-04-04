<?php

/**
 * Contains the controller class for exporting CER presets via Features.
 */

class CerPresetFeaturesController extends EntityDefaultFeaturesController {

  /**
   * Overridden.
   */
  public function export($data, &$export, $module = '') {
    $pipe = parent::export($data, $export, $module);

    // Every field in both chains may need to export additional things (the
    // field base and instance definitions at least, plus any extra dependencies).
    // All that logic is delegated to CerFieldChain.
    foreach (entity_load_multiple_by_name($this->type, $data) as $preset) {
      $pipe = array_merge_recursive($pipe, $preset->wrapper->cer_left->chain->value()->export());
      $pipe = array_merge_recursive($pipe, $preset->wrapper->cer_right->chain->value()->export());
    }

    return $pipe;
  }

}
