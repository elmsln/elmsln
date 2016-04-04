<?php
/**
 * @file CLE Gradebook module to provide the grid
 */

define('CLE_GRADEBOOK_USERNAME_FIELD', 'username');

/**
 * Callback for gradebook display.
 * @return string rendered output
 */
function assessment_gradebook_grid_form($form, &$form_state) {
  $form['#method'] = 'GET';
  // attach our modal window
  _assessment_gradebook_attach_modal();
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
  if (!isset($query['sections'])) {
    // get groupid from section if we have it
    if ($gid = _cis_section_load_section_by_id(_cis_connector_section_context())) {
      $query['sections'] = array($gid);
    }
  }
  // @todo verify this strips out sections automatically
  $sections = _cis_connector_assemble_entity_list('node', 'section', 'nid', 'title');
  $snodes = entity_load('node', array_keys($sections));
  // mark sections as inactive if they are
  foreach ($sections as $key => &$title) {
    if (!isset($snodes[$key]->field_cis_active['und'][0]) || !$snodes[$key]->field_cis_active['und'][0]['value']) {
      $title .= ' (' . t('inactive') . ')';
    }
  }
  // placeholder for filters area on the form
  $form['filters'] = array();
  // allow for switching sections you are viewing
  $form['filters']['sections'] = array(
    '#title' => t('Section'),
    '#options' => $sections,
    '#type' => 'select',
    '#required' => '1',
    '#multiple' => '1',
    '#chosen' => TRUE,
  );
  // force a section to be selected if we couldn't identify a default somehow
  if (empty($query['sections'])) {
    // don't present the other options til section(s) are selected for filtering
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#submit' => array('assessment_gradebook_grid_form_submit'),
    );
    return $form;
  }
  else {
    $field_conditions = array('og_user_node' => array('target_id', $query['sections'], 'IN'));
  }
  // pull together the users
  $students = _cis_connector_assemble_entity_list('user', 'user', 'uid', 'name', $field_conditions);
  $form['filters']['students'] = array(
    '#title' => t('Student'),
    '#options' =>  array('-all-' => t('All')) + $students,
    '#type' => 'select',
    '#required' => '0',
    '#chosen' => TRUE,
    '#multiple' => '1',
  );
  // pull assignments you should use
  $alist = array();
  foreach ($snodes as $snode) {
    foreach ($snode->field_cle_assignments['und'] as $atmp) {
      $alist[$atmp['target_id']] = $atmp['target_id'];
    }
  }
  // pull together the assignments
  $assignments = _cis_connector_assemble_entity_list('node', 'cle_assignment', 'nid', 'title', array(), array('nid' => array($alist, 'IN')), array('field' => array('field_number' => 'value')));
  $form['filters']['assignments'] = array(
    '#title' => t('Assignment'),
    '#options' => array('-all-' => t('All')) + $assignments,
    '#type' => 'select',
    '#required' => '0',
    '#chosen' => TRUE,
    '#multiple' => '1',
  );
  // submission status filter
  // @todo make this like the old system, just move dots around
  $field = field_info_field('field_submission_state');
  $form['filters']['field_submission_state'] = array(
    '#required' => '0',
    '#multiple' => '1',
    '#chosen' => TRUE,
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Submission Status'),
  );

  // assessment status filter
  // @todo make this like the old system, just move dots around
  $field = field_info_field('field_cle_status');
  $form['filters']['field_cle_status'] = array(
    '#required' => '0',
    '#multiple' => '1',
    '#chosen' => TRUE,
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Assessment status'),
  );

  // establish defaults for all form items at this point based on query
  foreach ($form['filters'] as $key => &$item) {
    // make sure query is in the address
    if (isset($query[$key])) {
      // check for goof where there might be all and a filtered thing
      if (count($query[$key]) > 1) {
        $find = array_search('-all-', $query[$key]);
        if ($find === 0 || $find == TRUE) {
          unset($query[$key][$find]);
        }
      }
      // set a default value to this key value to maintain defaults
      $item['#default_value'] = $query[$key];
      // ensure we don't have the -all- flag selected
      if ($query[$key][0] != '-all-') {
        // insane but set this filter's array of possible values
        // to a tmp storage value
        $tmp = $$key;
        $filtered = array();
        // loop through arguments that came in for this query filter
        foreach ($query[$key] as $tmpkey) {
          // maintain just the key value pair from those selected in the
          // filter that's passed through the addres. This might be the most
          // ridiculous little snippet i've ever written but it reduces code
          // needed and allow for effectively filtering on anything very
          // easily!
          if (isset($filtered[$tmpkey])) {
            $filtered[$tmpkey] = $tmp[$tmpkey];
          }
        }
        // whatever the filter was, reset the possible values of the array
        // based on this change
        $$key = $filtered;
      }
    }
    else {
      $item['#default_value'] = '-all-';
    }
  }

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
    $submissions = _cis_connector_assemble_entity_list('node', 'cle_submission', array('field_assignment', 'target_id'), 'nid', $field_conditions, array('uid' => $uid));
    $row = array(CLE_GRADEBOOK_USERNAME_FIELD => $user);
    // set a record per result
    foreach ($assignments as $key => $name) {
      // if we have an assignment nid key match, load result there
      if (isset($submissions[$key])) {
        // check for matching assessments
        $id = _cis_connector_assemble_entity_list('assessment_entity', 'submission_evaluation', 'assessment_entity_id', 'assessment_entity_id', array('field_cle_associated_submission' => array('target_id', $submissions[$key], '=')));
        // make sure we have an assessment entity first
        if (!empty($id)) {
          $assessment = entity_load_single('assessment_entity', array_pop($id));
        }
        else {
          $assessment = NULL;
        }
        // now pull in the status from the submission
        $submission = entity_load_single('node', $submissions[$key]);
        $status_image = _assessment_gradebook_assessment_status($submission, $assessment, 'image');
        $row[$key] = ctools_modal_text_button($status_image, 'cle/gradebook/render/nojs/' . $submissions[$key] . '/' . $uid,_assessment_gradebook_assessment_status($submission, $assessment, 'alt'), 'ctools-modal-cle-gradebook-modal disable-scroll');
      }
      else {
        $row[$key] = _assessment_gradebook_assessment_status(NULL, NULL, 'image');
      }
    }
    $rows[] = array('data' => $row);
  }
  // pull table together to render after the form settings
  $table = theme(
    'table',
    array(
      'header' => $header,
      'rows' => $rows,
      'caption' => t('Gradebook of studio submissions')
    )
  );
  // make filters collapsible
  $form['filters'] += array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#collapsible' => TRUE,
  );
  // make legend to show what the colors mean
  $form['legend'] = array(
    '#type' => 'fieldset',
    '#title' => t('Legend'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $indicators = _assessment_gradebook_get_status_indicators();
  foreach ($indicators as &$button) {
    $button['icon'] = "<img src=\"" . base_path() . $button['icon'] . "\" title=\"" . $button['title'] . "\" alt=\"" . $button['title'] . "\" width=\"16px\" height=\"16px\">";
  }
  $legend = theme(
    'table',
    array(
      'header' => array(t('Icon'), t('Meaning')),
      'rows' => $indicators,
      'caption' => t('Submission status legend')
    )
  );
  // append the table to the legend
  $form['legend']['table'] = array(
    '#markup' => $legend,
  );
  // get so we submit to ourselves the data we can review for query building
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('assessment_gradebook_grid_form_submit'),
  );
  // append the grid to the form
  $form['grid'] = array(
    '#markup' => $table,
  );
  return $form;
}
