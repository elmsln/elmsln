<?php

/**
 * The controller class for CerPreset entities.
 */
class CerPresetController extends EntityAPIControllerExportable {

  /**
   * Overridden.
   */
  public function export($entity, $prefix = '') {
    $variables = get_object_vars($entity);
    
    // I really wish Entity API tried to notify the entity that it's being
    // exported so that it could clean itself up first, but it doesn't. So we
    // gotta do this bizness.
    unset($variables['pid'], $variables['wrapper'], $variables['status'], $variables['module'], $variables['label_variables'], $variables['uid']);
    // Features 2.x checks for overriddenness using sorted keys, which means
    // that if the variables aren't key-sorted the presets will always be
    // considered overridden, even if they actually aren't.
    ksort($variables);

    return entity_var_json_export($variables, $prefix);
  }

  /**
   * Overridden.
   */
  protected function attachLoad(&$queried_entities, $revision_id = FALSE) {
    parent::attachLoad($queried_entities, $revision_id);

    foreach ($queried_entities as $preset) {
      // Attach variables used to build the human-readable preset label. These
      // need to be attached after the Field API has done its magic (i.e.,
      // during parent::attachLoad()), since the label depends on field values.
      // @see CerPreset::label().
      $fields = field_attach_view('cer', $preset, 'default');

      $preset->label_variables = array(
        '@left' =>
          render($fields['cer_left'][0]),
        '@right' =>
          render($fields['cer_right'][0]),
        '!operator' =>
          $preset->wrapper->cer_bidirectional->value() ? '<>' : '>',
      );
    }
  }

}
