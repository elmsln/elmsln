<?php

/**
 * Field handler to render metadata attributes
 *
 * @todo: Patch file entity to provide this?
 */
class getid3_metadata_handler extends views_handler_field_custom {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['alter']['#access'] = FALSE;
  }
  function render($values) {
    $file = file_load($values->fid);
    return $file->metadata;
  }
}
