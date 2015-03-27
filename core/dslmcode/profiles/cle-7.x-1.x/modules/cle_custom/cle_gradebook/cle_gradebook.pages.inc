<?php
/**
 * @file CLE Gradebook module to provide the grid
 */

define('CLE_GRADEBOOK_USERNAME_FIELD', 'username');

/**
 * Callback for gradebook display.
 * @return string rendered output
 */
function cle_gradebook_grid_form($form, &$form_state) {
  // attach our modal window
  _cle_gradebook_attach_modal();
  // @todo cache the batsnot out of this thing since it's a heavy query
  // @todo need to submit to itself so we can process this
  // load current path and params from url
  $rows = array();
  $path = current_path();
  $query = drupal_get_query_parameters();
  // establish defaults when they don't exist
  if (!isset($query['orderby'])) {
    $query['orderby'] = CLE_GRADEBOOK_USERNAME_FIELD;
  }
  if (!isset($query['section'])) {
    // get groupid from section if we have it
    if ($gid = _cis_section_load_section_by_id(_cis_connector_section_context())) {
      $query['section'] = $gid;
    }
  }
  // @todo verify this strips out sections automatically
  $secids = _cis_connector_assemble_entity_list('node', 'section', 'nid', 'title');
  $sections = entity_load('node', array_keys($secids));
  // mark sections as inactive if they are
  foreach ($secids as $key => &$title) {
    if (!isset($sections[$key]->field_cis_active['und'][0]) || !$sections[$key]->field_cis_active['und'][0]['value']) {
      $title .= ' (' . t('inactive') . ')';
    }
  }
  // placeholder for filters area on the form
  $form['filters'] = array();
  // allow for switching sections you are viewing
  $form['filters']['section'] = array(
    '#title' => t('Section'),
    '#options' => array('-all-' => t('All')) + $secids,
    '#type' => 'select',
    '#required' => '0',
  );
  // filter lower values based on what sections we are viewing
  if ($query['section'] == '-all-') {
    $field_conditions = array('og_user_node' => array('target_id', array_keys($secids), 'IN'));
  }
  else {
    $field_conditions = array('og_user_node' => array('target_id', $query['section']));
  }
  // pull together the users
  $students = _cis_connector_assemble_entity_list('user', 'user', 'uid', 'name', $field_conditions);
  $form['filters']['students'] = array(
    '#title' => t('Student'),
    '#options' =>  array('-all-' => t('All')) + $students,
    '#type' => 'select',
    '#required' => '0',
  );
  // pull together the assignments
  // @todo filter assignments to those selected by the section in question
  $assignments = _cis_connector_assemble_entity_list('node', 'cle_assignment', 'nid', 'title');
  $form['filters']['assignments'] = array(
    '#title' => t('Assignment'),
    '#options' => array('-all-' => t('All')) + $assignments,
    '#type' => 'select',
    '#required' => '0',
  );
  // submission status filter

  $field = field_info_field('field_submission_state');
  $form['filters']['field_submission_state'] = array(
    '#required' => '0',
    '#multiple' => '1',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Submission Status'),
  );

    // submission status filter
  $field = field_info_field('field_cle_status');
  $form['filters']['field_cle_status'] = array(
    '#required' => '0',
    '#multiple' => '1',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Assessment status'),
  );

  // establish defaults for all form items at this point based on query
  foreach ($form['filters'] as $key => &$item) {
    if (isset($query[$key])) {
      $item['#default_value'] = $query[$key];
      if ($query[$key] != '-all-') {
        $tmp = $$key;
        $$key = array($query[$key] => $tmp[$query[$key]]);
      }
    }
    else {
      $item['#default_value'] = '-all-';
    }
  }
  // get so we submit to ourselves the data we can review for query building
  $form['#method'] = 'GET';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('cle_gradebook_grid_form_submit'),
  );
  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('cle_gradebook_grid_form_reset'),
  );

  // setup the header for the table
  $header = array(CLE_GRADEBOOK_USERNAME_FIELD => l(t('Name'), $path, array('query' => array('orderby' => CLE_GRADEBOOK_USERNAME_FIELD))));
  foreach ($assignments as $key => $name) {
    $header[$key] = l($name, $path, array('query' => array('orderby' => $key)));
  }
  // @todo account for assessment status and if it has been assessed or not

  // field condition match for the state of the submission as marked by student
  if (isset($query['field_submission_state'])) {
    $field_conditions = array('field_submission_state' => array('value', array_keys($query['field_submission_state']), 'IN'));
  }
  else {
    $field_conditions = array();
  }
  // loop through users and pull their assignments
  foreach ($students as $uid => $user) {
    // pull together the submissions
    $subissions = _cis_connector_assemble_entity_list('node', 'cle_submission', array('field_assignment', 'target_id'), 'nid', $field_conditions, array('uid' => $uid));
    $row = array(CLE_GRADEBOOK_USERNAME_FIELD => $user);
    // set a record per result
    foreach ($assignments as $key => $name) {
      // if we have an assignment nid key match, load result there
      if (isset($subissions[$key])) {
        $row[$key] = ctools_modal_text_button($subissions[$key], 'cle/gradebook/render/nojs/' . $subissions[$key], t('View @name in submission viewer', array('@name' => $subissions[$key])), 'ctools-modal-cle-gradebook-modal');
      }
      else {
        $row[$key] = '-';
      }
    }
    $rows[] = array('data' => $row);
  }
  // sort by sortorder
  $sortorder = array();
  foreach ($rows as $key => $row) {
    $sortorder[$key]  = $row[$orderby];
  }
  array_multisort($sortorder, SORT_DESC, SORT_NUMERIC, $rows);
  // pull table together to render after the form settings
  $table = theme(
    'table',
    array(
      'header' => $header,
      'rows' => $rows,
      'caption' => t('Gradebook of studio submissions')
    )
  );
  // append the grid to the form
  $form['grid'] = array(
    '#markup' => $table,
  );
  // make filters collapsible
  $form['filters'] += array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#collapsible' => TRUE,
  );
  return $form;
}
