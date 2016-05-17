<?php

/**
 * Callback to sync course, section and roster data from network.
 */
function cis_course_authority_elmsln_api_callback_sync_data_model() {
  global $_elmsln;
  // make sure we have a roster
  if (
      isset($_elmsln['args']['__course_context']) &&
      isset($_elmsln['args']['roster']) &&
      isset($_elmsln['args']['courses']) &&
      isset($_elmsln['args']['sections'])
    ) {
    $course = $_elmsln['args']['__course_context'];
    $roster = $_elmsln['args']['roster'];
    $courses = $_elmsln['args']['courses'];
    $sections = $_elmsln['args']['sections'];
    // load local courses
    $local_courses = _cis_connector_assemble_entity_list('node', 'cis_course', 'field_cis_course_uuid', 'nid');
    // see if courses exist locally, if not produce
    foreach ($courses as $machine_name => $course_data) {
      // uuid match, load the course
      if (isset($local_courses[$course_data['uuid']])) {
        $course = node_load($local_courses[$course_data['uuid']]);
      }
      else {
        // make a course
        $course = new stdClass();
        $course->type = 'cis_course';
        $course->title = $course_data['title'];
        // machine name to match remote so we know how to build the links
        $course->field_course_machine_name[LANGUAGE_NONE][0]['value'] = $course_data['machine_name'];
        // set the local uuid linked field value to that we get from the remote
        $course->field_cis_course_uuid[LANGUAGE_NONE][0]['value'] = $course_data['uuid'];
        $course->language = LANGUAGE_NONE;
        $course->is_new = TRUE;
        node_object_prepare($course);
        // build out via submit then save
        if($course = node_submit($course)) {
          // force these to be saved by user 1 just so they have some user affiliation
          $course->uid = 1;
          node_save($course);
        }
      }
    }
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
        $section->field_section_course_ref['und'][0]['target_id'] = $course->nid;
        $section->language = LANGUAGE_NONE;
        $section->uid = 1;
        node_save($section);
        // need to make sure the course references this section
        $course->field_course_sections_ref['und'][] = array('target_id' => $section->nid);
        node_save($course);
      }
    }
    // build accounts from the roster
    _cis_section_create_accounts($roster);
    return array(
      'sync_data_model' => TRUE,
      'message' => "Course authority synced successfully",
    );
  }
  return array(
    'sync_data_model' => FALSE,
    'message' => "Course authority sync failed",
  );
}
