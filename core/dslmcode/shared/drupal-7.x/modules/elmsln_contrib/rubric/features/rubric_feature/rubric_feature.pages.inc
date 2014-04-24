<?php
/**
 * @file Rubric page callbacks
 */

/**
 * Callback to form to quickly generate a rubric.
 */
function rubric_feature_generator_form($form, &$form_state) {
  drupal_add_css(drupal_get_path('module', 'rubric_feature') . '/css/rubric_feature_generator.css');
  drupal_add_js(drupal_get_path('module', 'rubric_feature') . '/js/rubric_feature_generator.js');
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => '',
    '#required' => TRUE,
  );
  // rubrics beyond 4 options start to get really silly looking
  $options = array();
  for ($i=1; $i<5; $i++) {
    $options[$i] = $i;
  }
  // handle multiple categories
  $form['cat_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Categories'),
    '#description' => t('Titles and total number of categories to generate.'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );
  $form['cat_container']['categories'] = array(
    '#type' => 'select',
    '#title' => t('Categories'),
    '#default_value' => 2,
    '#options' => $options,
    '#required' => TRUE,
    '#description' => t('Number of categories to produce.'),
  );
  for ($i=0; $i<4; $i++) {
    $form['cat_container']['cat-title-' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Category @num title', array('@num' => ($i+1))),
      '#default_value' => '',
      '#required' => FALSE,
    );
  }
  $form['crit_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Criteria'),
    '#description' => t('Titles and total number of criteria to generate.'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );
  $form['crit_container']['criteria'] = array(
    '#type' => 'select',
    '#title' => t('Criteria'),
    '#default_value' => 2,
    '#options' => $options,
    '#required' => TRUE,
    '#description' => t('Number of criteria to produce per category.'),
  );
  for ($i=0; $i<4; $i++) {
    $form['crit_container']['crit-title-' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Criteria @num title', array('@num' => ($i+1))),
      '#default_value' => '',
      '#required' => FALSE,
    );
  }
  $form['levels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Evaluation levels'),
    '#description' => t('Name the default levels of evaluation to produce'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );
  // 3-5 levels is pretty standard
  for ($i=0; $i<5; $i++) {
    $form['levels']['level-' . $i . '-wrapper'] = array(
      '#prefix' => '<div class="rubric-feature-generator-level-wrapper">',
      '#suffix' => '</div>',
    );
    $form['levels']['level-' . $i . '-wrapper']['level-' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Level @num text', array('@num' => ($i+1))),
      '#default_value' => '',
      '#required' => FALSE,
    );
    $form['levels']['level-' . $i . '-wrapper']['points-' . $i] = array(
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
  $val = $form_state['values'];
  // establish default rubric place holder to work on
  $rubric = new stdClass();
  $rubric->type = 'elms_rubric';
  $rubric->status = 1;
  $rubric->language = LANGUAGE_NONE;
  $rubric->uid = $GLOBALS['user']->uid;
  $rubric->title = $val['title'];
  // start loop through cetegories and build out from there
  for ($i=0; $i<$val['categories']; $i++) {
    $categories[$i] = entity_create('field_collection_item', array('field_name' => 'field_rubric_categories'));
    // associate category to the course
    $categories[$i]->setHostEntity('node', $rubric);
    // set title
    $categories[$i]->field_category_title[LANGUAGE_NONE][0]['value'] = (empty($val['cat-title-' . $i])) ? t('Category @num', array('@num' => ($i+1))) : $val['cat-title-' . $i];
    // drill down into criteria
    for ($j=0; $j<$val['criteria']; $j++) {
      $criterias[$j] = entity_create('field_collection_item', array('field_name' => 'field_rubric_criteria'));
      // associate category to the course
      $criterias[$j]->setHostEntity('field_collection_item', $categories[$i]);
      // set title
      $criterias[$j]->field_criteria_title[LANGUAGE_NONE][0]['value'] = (empty($val['crit-title-' . $j])) ? t('Criteria @num', array('@num' => ($j+1))) : $val['crit-title-' . $j];
      // build out the level field collections
      for ($k=0; $k<5; $k++) {
        // make sure the level isn't empty before producing
        if (isset($val['level-' . $k]) && !empty($val['level-' . $k])) {
          $levels[$k] = entity_create('field_collection_item', array('field_name' => 'field_rubric_levels'));
          // associate category to the course
          $levels[$k]->setHostEntity('field_collection_item', $criterias[$j]);
          // set title
          $levels[$k]->field_level_title[LANGUAGE_NONE][0]['value'] = $val['level-' . $k];
          $levels[$k]->field_level_points[LANGUAGE_NONE][0]['value'] = (isset($val['points-' . $k]) ? $val['points-' . $k] : 0);
        }
      }
    }
  }
  // save everything
  node_save($rubric);
  drupal_goto('node/' . $rubric->nid);
}
