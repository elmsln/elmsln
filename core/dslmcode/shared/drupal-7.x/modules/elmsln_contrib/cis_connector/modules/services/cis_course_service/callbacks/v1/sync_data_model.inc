<?php

/**
 * Callback to sync sections and roster of users with network.
 */
function cis_course_service_elmsln_api_callback_sync_data_model() {
  global $_elmsln;
  // update the section data model to match
  if (isset($_elmsln['args']['sections'])) {
    foreach ($_elmsln['args']['sections'] as $section_id => $section_status) {
      if ($nid = _cis_section_load_section_by_id($section_id)) {
        // this case can be triggered if the dates get updated downstream in CIS
        // or if we create something ahead of the semester
        $section = node_load($nid);
        // see if the section status has changed
        if ($section->field_cis_active['und'][0]['value'] != $section_status) {
          $section->field_cis_active['und'][0]['value'] = $section_status;
          node_save($section);
        }
      }
      else {
        $section = new stdClass();
        $section->type = 'section';
        node_object_prepare($section);
        $section->title = $section_id;
        $section->field_section_id['und'][0]['value'] = $section_id;
        $section->field_cis_active['und'][0]['value'] = $section_status;
        $section->language = LANGUAGE_NONE;
        $section->uid = 1;
        node_save($section);
      }
    }
    // build accounts from the roster
    if (isset($_elmsln['args']['roster'])) {
      // attempt to deserialize
      $roster = @unserialize($_elmsln['args']['roster']);
      $processed = _cis_section_create_accounts($roster);
      // account for REALLY big call structures requiring multiple jobs
      // in this event, we should add ourselves back onto the stack
      // thus allowing the call to process further until it's completed
      // at which point the next child down would do the same!
      // This only comes into play with REALLY big structures
      if (!$processed) {
        if (isset($_elmsln['args']['__snake_stack']) && !empty($_elmsln['args']['__snake_stack'])) {
          array_unshift($_elmsln['args']['__snake_stack'], elmsln_core_get_profile_key());
        }
        else {
          $_elmsln['args']['__snake_stack'] = array(elmsln_core_get_profile_key());
        }
      }
    }
    return array(
      'sync_data_model' => TRUE,
      'message' => "Course service synced successfully",
    );
  }
  return array(
    'sync_data_model' => FALSE,
    'message' => "Course service sync failed",
  );
}
