<?php
/**
 * @file Rubric page callbacks
 */

/**
 * Callback to form to quickly generate a rubric.
 */
function rubric_feature_generator_form($form, &$form_state) {
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Rubric title'),
    '#default_value' => '',
    '#required' => TRUE,
  );

  $options = array();
  for ($i=1; $i<6; $i++) {
    $options[$i] = $i;
  }
  $form['categories'] = array(
    '#type' => 'select',
    '#title' => t('Criteria'),
    '#default_value' => 2,
    '#options' => $options,
    '#required' => TRUE,
    '#description' => t('Number of criteria to produce per category.'),
  );
  $form['criteria'] = array(
    '#type' => 'select',
    '#title' => t('Criteria'),
    '#default_value' => 2,
    '#options' => $options,
    '#required' => TRUE,
    '#description' => t('Number of criteria to produce per category.'),
  );
  $form['levels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Evaluation levels'),
    '#description' => t('Name the default levels of evaluation to produce'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );
  for ($i=0; $i<6; $i++) {
    $form['levels']['level-' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Level @num text', array('@num' => ($i+1))),
      '#default_value' => '',
      '#required' => FALSE,
    );
    $form['levels']['points-' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Level @num Points', array('@num' => ($i+1))),
      '#default_value' => '',
      '#required' => FALSE,
    );
  }
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate rubric'),
    '#weight' => 10,
    '#submit' => array('rubric_feature_generator_form_submit'),
  );
  return $form;
}

/**
 * Implementation of hook_form_submit().
 */
function rubric_feature_generator_form_submit($form, $form_state) {
  dpm($form_state['values']);
  $val = $form_state['values'];

  // establish default rubric place holder to work on
  $rubric = new stdClass();
  $rubric->type = 'elms_rubric';
  $rubric->status = 1;
  $rubric->language = LANGUAGE_NONE;
  $rubric->uid = $GLOBALS['user']->uid;
  $rubric->title = $val['title'];
  node_save($rubric);

  for ($i=0; $i<$val['categories']; $i++) {
    $category = entity_create('field_collection_item', array('field_name' => 'field_rubric_categories'));
    // associate category to the course
    $category->setHostEntity('node', $rubric);
    // set title
    $category->field_category_title[LANGUAGE_NONE][0]['value'] = t('Category @num', array('@num' => ($i+1)));
    // drill down into criteria
    for ($j=0; $j<$val['criteria']; $j++) {
      $criteria = entity_create('field_collection_item', array('field_name' => 'field_rubric_criteria'));
      // associate category to the course
      $criteria->setHostEntity('field_collection_item', $category);
      // set title
      $criteria->field_criteria_title[LANGUAGE_NONE][0]['value'] = t('Criteria @num', array('@num' => ($j+1)));
      // build out the level field collections
      for ($k=0; $k<6; $k++) {
        if (isset($val['level-' . $k]) && !empty($val['level-' . $k])) {
          $level = entity_create('field_collection_item', array('field_name' => 'field_rubric_levels'));
          // associate category to the course
          $level->setHostEntity('field_collection_item', $criteria);
          // set title
          $level->field_level_title[LANGUAGE_NONE][0]['value'] = $val['level-' . $k];
          $level->field_level_points[LANGUAGE_NONE][0]['value'] = (isset($val['points-' . $k])?$val['points-' . $k]:0);
          $level->save();
        }
      }
      $criteria->save();
    }
    $category->save();
  }
  drupal_goto('node/' . $rubric->nid);
}
