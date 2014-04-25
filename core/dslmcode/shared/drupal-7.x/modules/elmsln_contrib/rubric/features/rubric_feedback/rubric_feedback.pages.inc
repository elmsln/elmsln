<?php
/**
 * @file Rubric feedback page callbacks
 */

/**
 * Callback to form to quickly generate a rubric.
 */
function rubric_feedback_ui_form($form, &$form_state, $rubric_id, $submission_id) {
  // add in css / js required as glue
  drupal_add_css(drupal_get_path('module', 'rubric_feedback') . '/css/rubric_feedback.css');
  drupal_add_js(drupal_get_path('module', 'rubric_feedback') . '/js/rubric_feedback.js');
  // student assignment in question
  $form['submission-container'] = array(
    '#type' => 'fieldset',
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
    '#title' => t('Student submission'),
  );
  $submission_node = node_load($submission_id);
  $submission = node_view($submission_node);
  // drop inline rating of elements via this UI if rate is in use
  if (module_exists('rate')) {
    foreach ($submission as $key => $data) {
      if (strpos($key, 'rate_') === 0) {
        unset($submission[$key]);
      }
    }
  }
  // unset links and contextual links
  unset($submission['links']);
  unset($submission['#contextual_links']);
  $form['submission-container']['submission'] = $submission;
  // render the rubric node in question
  $form['rubric-container'] = array(
    '#type' => 'fieldset',
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
    '#title' => t('Assessment rubric'),
  );
  // load rubric node and render array
  $rubric_node = node_load($rubric_id);
  $rubric_render = node_view($rubric_node);
  // kill links and contextual links
  unset($rubric_render['links']);
  unset($rubric_render['#contextual_links']);
  $form['rubric-container']['rubric'] = $rubric_render;

  // render the assessment form that's filled out
  $form['assessment'] = array(
    '#type' => 'fieldset',
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
    '#title' => t('Assessment overview'),
  );
  // drill down and convert structure of the rubric into a well displayed table
  foreach ($rubric_node->field_rubric_categories['und'] as $cat) {
    $category = entity_load_single('field_collection_item', $cat['value']);
    $rows[] = array($category->field_category_title['und'][0]['value'], '', '', 100);
    foreach ($category->field_rubric_criteria['und'] as $crit) {
      $criteria = entity_load_single('field_collection_item', $crit['value']);
      // @todo replace with $criteria->field_criteria_possible_points['und'][0]['value'] when we calculate that on the fly
      $rows[] = array('', $criteria->field_criteria_title['und'][0]['value'], 0, '');
    }
  }
  $rows[] = array(t('Total'), '', 50, 200);
  $header = array(t('Category'), t('Criteria'), t('Points'), t('Possible'));
  $form['assessment']['assessment_table'] = array(
    '#rows' => $rows,
    '#header' => $header,
    '#theme' => 'table',
  );
  $form['assessment']['feedback'] = array(
    '#type' => 'textarea',
    '#title' => t('Feedback'),
    '#default_value' => '',
    '#required' => TRUE,
  );
  $form['assessment']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save assessment'),
    '#weight' => 10,
    '#submit' => array('rubric_feedback_ui_form_submit'),
  );

  return $form;
}

/**
 * Implementation of hook_form_submit().
 */
function rubric_feedback_ui_form_submit($form, $form_state) {
  $val = $form_state['values'];
  // establish default rubric place holder to work on
  $assessment = new stdClass();
  $assessment->type = 'rubric_submission_assessment';
  $assessment->status = 1;
  $assessment->language = LANGUAGE_NONE;
  $assessment->uid = $GLOBALS['user']->uid;
  // @todo set title to a generated value
  $assessment->title = $val['title'];
  // @todo associate clicks submitted via form here
  // start loop through cetegories and build out from there
  for ($i=0; $i<$val['categories']; $i++) {
  }
  // save everything
  node_save($assessment);
  drupal_goto('node/' . $rubric->nid);
}
