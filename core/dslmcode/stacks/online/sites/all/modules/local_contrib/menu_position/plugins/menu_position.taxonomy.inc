<?php
/**
 * @file
 * Provides the "Taxonomy" rule plugin for the Menu Position module.
 */

/**
 * Checks if a specific taxonomy term is set in the node.
 *
 * @param $variables
 *   An array containing each of the variables saved in the database necessary
 *   to evaluate this condition of the rule.
 * @return
 *   TRUE if condition applies successfully. Otherwise FALSE.
 */
function menu_position_menu_position_condition_taxonomy($variables) {
  // We can only check for taxonomy terms on an "entity" page.
  if ($variables['context']['entity_type']) {

    // Grab the variables stored statically in the rule.
    $vid = $variables['vid'];
    $tid = $variables['tid'];

    // Determine what kind of entity page this is.
    $entity_type = $variables['context']['entity_type'];
    $bundle_name = $variables['context']['bundle_name'];
    $entity = $variables['context'][$entity_type];

    // Build a list of each taxonomy reference fields.
    $taxonomy_fields = &drupal_static(__FUNCTION__, NULL);
    if (!isset($taxonomy_fields)) {
      $taxonomy_fields = array();
      $field_info = field_info_fields();
      foreach (array_keys(field_info_instances($entity_type, $bundle_name)) as $key) {
        if ($field_info[$key]['type'] == 'taxonomy_term_reference') {
          $taxonomy_fields[$key] = $field_info[$key]['translatable'];
        }
      }
    }

    foreach ($taxonomy_fields as $field => $translatable) {
      $language = $translatable ? $entity->language : LANGUAGE_NONE;
      if (!empty($entity->{$field}[$language])) {
        // Check for matching terms.
        if (!empty($tid)) {
          foreach ($entity->{$field}[$language] as $term) {
            if (in_array($term['tid'], $tid)) {
              return TRUE;
            }
          }
        }
        // Check for any terms from a matching vocabulary.
        else {
          foreach ($entity->{$field}[$language] as $term) {
            if (isset($term['taxonomy_term']->vid) && $term['taxonomy_term']->vid === $vid) {
              return TRUE;
            }
          }
        }
      }
    }
  }
  return FALSE;
}

/**
 * Adds form elements for the "taxonomy" plugin to the rule configuration form.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array. New form elements should be
 *   added directly to this array.
 * @param $form_state
 *   A reference to the current form state.
 */
function menu_position_menu_position_rule_taxonomy_form(&$form, &$form_state) {
  // If this is an existing rule, load the variables stored in the rule for this plugin.
  $variables = !empty($form_state['#menu-position-rule']['conditions']['taxonomy']) ? $form_state['#menu-position-rule']['conditions']['taxonomy'] : array();

  // Load the taxonomy terms.
  if (!empty($variables['tid'])) {
    $terms = array();
    foreach (taxonomy_term_load_multiple($variables['tid']) as $term) {
      $terms[] = $term->name;
    }
    $terms = implode(', ', $terms);
  }
  else {
    $terms = '';
  }

  $form['conditions']['taxonomy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Taxonomy'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'menu_position') . '/plugins/menu_position.taxonomy.js'),
    ),
  );
  $form['conditions']['taxonomy']['description'] = array(
    '#type' => 'item',
    '#description' => t('Apply this rule only on pages that display content having the given vocabulary or taxonomy term.'),
  );
  $vocabularies = taxonomy_vocabulary_get_names();
  $vocabulary_options = array();
  foreach ($vocabularies as $vocabulary) {
    // $vocabulary['machine_name']
    $vocabulary_options[$vocabulary->vid] = $vocabulary->name;
  }
  $form['conditions']['taxonomy']['vid'] = array(
    '#type' => 'select',
    '#title' => t('Vocabulary'),
    '#default_value' => !empty($variables['vid']) ? $variables['vid'] : '0',
    '#options' => array('0' => t('- None -')) + $vocabulary_options,
  );
  $form['conditions']['taxonomy']['vid_or_tid'] = array(
    '#type' => 'radios',
    '#title' => t('In this vocabulary, match:'),
    '#default_value' => !empty($variables['tid']) ? 'tid' : 'vid',
    '#options' => array(
      'vid' => t('any taxonomy term'),
      'tid' => t('only a selected taxonomy term'),
    ),
    '#states' => array(
      //'disabled' => array(
      'invisible' => array(
        ':input[name=vid]' => array('value' => '0'),
      ),
    ),
  );
  $form['#attached']['js'][] = array(
    'data' => array('menu_position_taxonomy_url' => url('menu-position/taxonomy/autocomplete')),
    'type' => 'setting',
  );
  $form['conditions']['taxonomy']['term'] = array(
    '#type' => 'textfield',
    '#maxlength' => 1024,
    '#title' => t('Taxonomy term'),
    '#default_value' => $terms,
    '#autocomplete_path' => 'menu-position/taxonomy/autocomplete/' . (isset($form_state['input']['vid']) ? $form_state['input']['vid'] : $form['conditions']['taxonomy']['vid']['#default_value']),
    '#element_validate' => array('menu_position_taxonomy_autocomplete_validate'),
    '#description' => t('Match at least one of these taxonomy terms.'),
    '#states' => array(
      'visible' => array(
        ':input[name=vid_or_tid]' => array('value' => 'tid'),
        //':input[name=vid_or_tid]' => array('enabled' => TRUE),
      ),
    ),
  );

  // Add a submit handler.
  $form['#submit'][] = 'menu_position_menu_position_rule_taxonomy_form_submit';
}

/**
 * Prepares the "taxonomy" variables to be stored in the rule.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array.
 * @param $form_state
 *   A reference to the current form state, including submitted values.
 */
function menu_position_menu_position_rule_taxonomy_form_submit(&$form, &$form_state) {
  if (!empty($form_state['values']['term']) || $form_state['values']['vid'] != 0) {
    $variables = array(
      'vid' => $form_state['values']['vid'],
      'tid' => array(),
    );
    // Determine if a taxonomy term has been selected.
    if ($form_state['values']['vid_or_tid'] == 'tid' && !empty($form_state['values']['term'])) {
      foreach ($form_state['values']['term'] as $term) {
        $variables['tid'][] = $term['tid'];
      }
    }
    $form_state['values']['conditions']['taxonomy'] = $variables;
  }
}

/**
 * Helper function for autocompletion
 */
function menu_position_taxonomy_autocomplete($vocabulary, $tags_typed = '') {
  // Don't query for terms if no vocabulary is selected.
  if ($vocabulary == 0) {
    drupal_json_output(array());
    return;
  }

  // The user enters a comma-separated list of tags. We only autocomplete the last tag.
  $tags_typed = drupal_explode_tags($tags_typed);
  $tag_last = drupal_strtolower(array_pop($tags_typed));

  $matches = array();
  if ($tag_last != '') {

    $query = db_select('taxonomy_term_data', 't');
    $query->addTag('translatable');
    $query->addTag('term_access');

    // Do not select already entered terms.
    if (!empty($tags_typed)) {
      $query->condition('t.name', $tags_typed, 'NOT IN');
    }
    // Select rows that match by term name.
    $tags_return = $query
      ->fields('t', array('tid', 'name'))
      ->condition('t.vid', array($vocabulary))
      ->condition('t.name', '%' . db_like($tag_last) . '%', 'LIKE')
      ->range(0, 10)
      ->execute()
      ->fetchAllKeyed();

    $prefix = count($tags_typed) ? implode(', ', $tags_typed) . ', ' : '';

    $term_matches = array();
    foreach ($tags_return as $tid => $name) {
      $n = $name;
      // Term names containing commas or quotes must be wrapped in quotes.
      if (strpos($name, ',') !== FALSE || strpos($name, '"') !== FALSE) {
        $n = '"' . str_replace('"', '""', $name) . '"';
      }
      else {
        $term_matches[$prefix . $n] = check_plain($name);
      }
    }
  }

  drupal_json_output($term_matches);
}

/**
 * Form element validate handler for taxonomy term autocomplete element.
 */
function menu_position_taxonomy_autocomplete_validate($element, &$form_state) {
  // Autocomplete widgets do not send their tids in the form, so we must detect
  // them here and process them independently.
  $value = array();

  if ($tags = $element['#value']) {
    // Translate term names into actual terms.
    $typed_terms = drupal_explode_tags($tags);
    foreach ($typed_terms as $typed_term) {
      // See if the term exists in the chosen vocabulary and return the tid;
      // otherwise, create a new 'autocreate' term for insert/update.
      if ($possibilities = taxonomy_term_load_multiple(array(), array('name' => trim($typed_term), 'vid' => array($form_state['values']['vid'])))) {
        $term = array_pop($possibilities);
        $value[] = (array)$term;
      }
      else {
        form_set_error('term', t('%term is not a valid taxonomy term.', array('%term' => $typed_term)));
      }
    }
  }

  if (!empty($value)) {
    form_set_value($element, $value, $form_state);
  }
}
