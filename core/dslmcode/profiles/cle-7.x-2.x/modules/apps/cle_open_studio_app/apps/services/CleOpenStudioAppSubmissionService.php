<?php

class CleOpenStudioAppSubmissionService {

  /**
   * Get a list of submissions
   * This will take into concideration what section the user is in and what section
   * they have access to.
   */
  public function getSubmissions() {
    $items = array();
    $section_id = _cis_connector_section_context();
    $section = _cis_section_load_section_by_id($section_id);
    $field_conditions = array(
      'og_group_ref' => array('target_id', $section, '='),
    );
    $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
    if (isset($filter['submission'])) {
      $property_conditions['nid'] = array($filter['submission'], '=');
    }
    $orderby = array();
    $items = _cis_connector_assemble_entity_list('node', 'cle_submission', 'nid', '_entity', $field_conditions, $property_conditions, $orderby);
    $items = $this->encodeSubmissions($items);
    return $items;
  }

  /**
   * Prepare a list of submissions to be outputed in json
   * 
   * @param array $submissions
   *  An array of submission node objects
   */
  protected function encodeSubmissions($submissions) {
    if (is_array($submissions)) {
      foreach ($submissions as &$submission) {
        $submission = $this->endcodeSubmission($submission);
      }
    }
    return $submissions;
  }

  /**
   * Prepare a single submission to be outputed in json
   * 
   * @param object $submission
   *  A submission node object
   */
  protected function endcodeSubmission($submission) {
    $encoded_submission = new stdClass();
    if (is_object($submission)) {
      $encoded_submission->title = $submission->title;
      $encoded_submission->type = $submission->type;
      $encoded_submission->id = $submission->nid;
      $encoded_submission->attributes->title = $submission->title;
      $encoded_submission->meta->created = Date('c', $submission->created);
      $encoded_submission->meta->updated = Date('c', $submission->updated);
    }
    drupal_alter('cle_open_studio_app_encode_submission');
    return $encoded_submission;
  }
}