<?php

/**
 * Callback to sync sections and roster of users with network.
 */
function cis_course_service_elmsln_api_callback_sync_data_model() {
  global $_elmsln;
  // make sure we have a roster
  if (isset($_elmsln['args']['roster']) && isset($_elmsln['args']['__course_context'])) {
    $roster = $_elmsln['args']['roster'];
    $sections = $_elmsln['args']['sections'];
    // update the section data model to match
    foreach ($sections as $section_id => $section_status) {
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
    _cis_section_create_accounts($roster);

    return array(
      'sync_data_model' => TRUE,
      'message' => "Course service synced successfully",
    );
  }
}
