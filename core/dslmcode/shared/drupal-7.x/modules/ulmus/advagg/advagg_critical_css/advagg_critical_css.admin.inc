<?php

/**
 * @file
 * Admin page callbacks for the advagg critical css module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup advagg_forms
 *
 * @see system_settings_form()
 */
function advagg_critical_css_admin_settings_form() {
  drupal_set_title(t('AdvAgg: Critical CSS'));
  advagg_display_message_if_requirements_not_met();

  $form = array();

  $default_theme = variable_get('theme_default', 'bartik');
  $global_theme = $GLOBALS['theme'];
  $themes = array_keys(list_themes());

  $form['#attached']['css'][] = array(
    'data' => ".form-item-lookup{padding-bottom:0;margin-bottom:0;}",
    'type' => 'inline',
  );
  $form['add_item']['theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => array_combine($themes, $themes),
    '#default_value' => $default_theme,
    '#description' => t('Theme Default: %default, Current Theme: %current', array(
      '%default' => $default_theme,
      '%current' => $global_theme,
    )),
  );
  $form['add_item']['user'] = array(
    '#type' => 'select',
    '#title' => t('User type'),
    '#default_value' => 0,
    '#options' => array(
      'anonymous' => t('anonymous'),
      'authenticated' => t('authenticated'),
      'all' => t('all'),
    ),
  );
  $type_options = array(
    0 => t('Disabled'),
    2 => t('URL'),
    8 => t('Node Type'),
  );
  $form['add_item']['type'] = array(
    '#type' => 'select',
    '#title' => t('Type of lookup'),
    '#default_value' => 2,
    '#options' => $type_options,
  );

  $form['add_item']['lookup'] = array(
    '#type' => 'textfield',
    '#title' => t('Value to lookup'),
    '#maxlength' => 255,
    '#states' => array(
      'disabled' => array(
        ':input[name="type"]' => array('value' => 0),
      ),
    ),
  );
  $form['add_item']['lookup_container_disabled'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name="type"]' => array('value' => 0),
      ),
    ),
  );
  $form['add_item']['lookup_container_disabled']['disabled'] = array(
    '#markup' => '<br>',
  );
  $form['add_item']['lookup_container_current_path'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name="type"]' => array('value' => 2),
      ),
    ),
  );
  $form['add_item']['lookup_container_current_path']['current_path'] = array(
    '#markup' => t('%front is the front page; can use internal URLs like %internal or an alias like %here', array(
      '%front' => '<front>',
      '%internal' => 'node/2',
      '%here' => current_path(),
    )),
  );
  $form['add_item']['lookup_container_node_type'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name="type"]' => array('value' => 8),
      ),
    ),
  );
  $form['add_item']['lookup_container_node_type']['node_type'] = array(
    '#markup' => t('Node type is the machine name of the node; list of node types: @node_types', array(
      '@current_path' => 'https://api.drupal.org/api/drupal/includes%21path.inc/function/current_path/7.x',
      '@request_path' => 'https://api.drupal.org/api/drupal/includes%21bootstrap.inc/function/request_path/7.x',
      '@request_uri' => 'https://api.drupal.org/api/drupal/includes%21bootstrap.inc/function/request_uri/7.x',
      '@node_types' => implode(', ', array_keys(node_type_get_names())),
    )),
  );

  $form['add_item']['css'] = array(
    '#type' => 'textarea',
    '#title' => t('Critical CSS'),
    '#description' => t('Can be generated via <a href="@url">https://www.sitelocity.com/critical-path-css-generator</a>. If this field is empty this entry will be deleted.', array(
      '@url' => 'https://www.sitelocity.com/critical-path-css-generator',
    )),
    '#default_value' => '',
  );
  $form['add_item']['dns'] = array(
    '#type' => 'textarea',
    '#title' => t('Hostnames to lookup'),
    '#description' => t('Hosts that will be connected to.'),
    '#default_value' => '',
  );
  $form['add_item']['pre'] = array(
    '#type' => 'textarea',
    '#title' => t('Urls to Preload'),
    '#description' => t('Assets for the browser that should be downloaded at a high priority.'),
    '#default_value' => '',
  );

  // Lookup saved data.
  $query = db_select('advagg_critical_css', 'acc')
    ->fields('acc')
    ->comment('Query called from ' . __FUNCTION__ . '()');
  $results = $query->execute();
  // Put results into array.
  $counter = 0;
  foreach ($results as $row) {
    $counter++;
    $row = (array) $row;

    foreach ($form['add_item'] as $key => $values) {
      // Fix the states array for type.
      if (!empty($values['#states'])) {
        foreach ($values['#states'] as $states_key => $states_values) {
          $states_value = reset($values['#states'][$states_key]);
          $values['#states'][$states_key] = array(":input[name=\"{$counter}_type\"]" => $states_value);
        }
      }
      $form['existing_items'][$counter]["{$counter}_{$key}"] = $values;
      if (isset($row[$key])) {
        $form['existing_items'][$counter]["{$counter}_{$key}"]['#default_value'] = $row[$key];
      }
    }

    // Add in css to move the text hint up.
    $form['#attached']['css'][] = array(
      'data' => ".form-item-{$counter}-lookup{padding-bottom:0;margin-bottom:0;}",
      'type' => 'inline',
    );

    // Add fieldset.
    $filename = advagg_url_to_filename($row['lookup'], FALSE);
    $base = drupal_get_path('theme', $row['theme']) . "/critical-css/{$row['user']}/";
    if ($row['type'] == 2) {
      $base .= "urls/$filename";
    }
    elseif ($row['type'] == 8) {
      $base .= "type/$filename";
    }
    else {
      $base = '';
    }
    $form['existing_items'][$counter] += array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('@type @theme @user @lookup', array(
        '@theme' => $row['theme'],
        '@type' => $type_options[$row['type']],
        '@user' => $row['user'],
        '@lookup' => $row['lookup'],
      )),
    );

    if (!empty($base)) {
      $form['existing_items'][$counter]['#description'] = t('If you wish to store this configuration in a file<br>Critical CSS: <code>@css</code>', array(
        '@css' => "$base.css",
      ));
      if (!empty($row['dns'])) {
        $form['existing_items'][$counter]['#description'] .= t('<br>Hostnames: <code>@dns</code>', array(
          '@dns' => "$base.dns",
        ));
      }
      if (!empty($row['pre'])) {
        $form['existing_items'][$counter]['#description'] .= t('<br>Preload: <code>@pre</code>', array(
          '@pre' => "$base.pre",
        ));
      }
    }
  }

  // Add top level fieldsets.
  $form['add_item'] += array(
    '#type' => 'fieldset',
    '#title' => t('Add Critical CSS'),
    '#collapsible' => TRUE,
    '#collapsed' => $results->rowCount(),
  );
  if (!empty($form['existing_items'])) {
    $form['existing_items'] += array(
      '#type' => 'fieldset',
      '#title' => t('Edit Critical CSS'),
    );
  }

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_critical_css_admin_settings_form_submit';

  // Most code below taken from system_settings_form().
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['actions']['disable'] = array(
    '#type' => 'submit',
    '#value' => t('Disable All From Database'),
    '#submit' => array('advagg_critical_css_admin_settings_form_submit_disable'),
  );
  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  // By default, render the form using theme_system_settings_form().
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }
  return $form;
}

/**
 * Submit callback, process the advagg_critical_css form.
 *
 * Also clear out the advagg cache bin.
 *
 * @ingroup advagg_forms_callback
 */
function advagg_critical_css_admin_settings_form_submit_disable($form, &$form_state) {
  $query = db_select('advagg_critical_css', 'acc')
    ->fields('acc')
    ->comment('Query called from ' . __FUNCTION__ . '()');
  $results = $query->execute();
  // Put results into array.
  $insert_update = array();
  foreach ($results as $row) {
    $row = (array) $row;
    $new_row = $row;
    $new_row['type'] = 0;
    $insert_update[] = array(
      $row,
      $new_row,
    );
  }
  advagg_critical_css_table_insert_update($insert_update);
}

/**
 * Submit callback, process the advagg_critical_css form.
 *
 * Also clear out the advagg cache bin.
 *
 * @ingroup advagg_forms_callback
 */
function advagg_critical_css_admin_settings_form_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  form_state_values_clean($form_state);

  // Rearrange form values into key value pairs.
  $items = advagg_critical_css_get_rows_from_form($form_state['values']);
  // Get default values.
  $default_values = advagg_find_all_recommended_admin_values($form_state['complete form'], '#default_value');
  unset($default_values['form_token']);
  $default_items = advagg_critical_css_get_rows_from_form($default_values);

  // Get diff, see what items need to be saved.
  $diff = advagg_critical_css_diff_multi($default_items, $items);
  $changed_items = array();
  foreach ($diff as $key => $values) {
    $changed_items[$key] = $items[$key];
  }

  // Get items to insert/update and delete.
  list($insert_update, $delete) = advagg_critical_css_get_db_operations_arrays($changed_items, $default_items);
  advagg_critical_css_table_insert_update($insert_update);
  advagg_critical_css_table_delete($delete);

  // Clear caches.
  advagg_cache_clear_admin_submit();
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Translate from state values into a nested array strucutre.
 *
 * @param array $form_state_values
 *   From state values; from $form_state['values'].
 *
 * @return array
 *   Nested array strucutre, each index is a row in the db.
 */
function advagg_critical_css_get_rows_from_form(array $form_state_values) {
  $items = array();
  $counter = 0;
  foreach ($form_state_values as $key => $values) {
    // Get the index from the start of the form name.
    $matches = array();
    // 1_type turns into $counter = 1 and $key = type.
    preg_match('/^(\d)_(.*)/', $key, $matches);
    if (!empty($matches)) {
      $counter = $matches[1];
      $key = $matches[2];
    }
    $items[$counter][$key] = $values;
  }
  return $items;
}

/**
 * Given a list of items see what ones need to be inserted/updated or deleted.
 *
 * @param array $items
 *   Array of values, representing a row in the db.
 *
 * @return array
 *   Nested array strucutre, index 0 is the insert update, 1 is the deleted.
 */
function advagg_critical_css_get_db_operations_arrays(array $items, array $old_items) {
  $insert_update = array();
  $delete = array();
  foreach ($items as $key => $values) {
    // If the css is empty then this needs to be deleted.
    if (empty($values['css'])) {
      // Do not delete the new items entry (0); it's not in the db currently.
      if (!empty($key)) {
        $delete[$key] = $values;
      }
    }
    else {
      // Pass along the old key value pairs for db_merge.
      if (!empty($old_items[$key])) {
        $keys = $old_items[$key] + $values;
      }
      else {
        $keys = $values;
      }
      $insert_update[$key] = array($keys, $values);
    }
  }
  return array($insert_update, $delete);
}

/**
 * Given a list of items see what ones need to be inserted/updated or deleted.
 *
 * @param array $defaults
 *   Array of default values, representing a row in the db.
 * @param mixed $new_values
 *   Array of edited values, representing a row in the db.
 *
 * @return array
 *   Nested array strucutre; only the diff.
 */
function advagg_critical_css_diff_multi(array $defaults, $new_values) {
  $result = array();

  foreach ($defaults as $key => $val) {
    if (is_array($val) && isset($new_values[$key])) {
      $tmp = advagg_critical_css_diff_multi($val, $new_values[$key]);
      if ($tmp) {
        $result[$key] = $tmp;
      }
    }
    elseif (!isset($new_values[$key])) {
      $result[$key] = NULL;
    }
    elseif ($val != $new_values[$key]) {
      $result[$key] = $new_values[$key];
    }
    if (isset($new_values[$key])) {
      unset($new_values[$key]);
    }
  }

  $result = $result + $new_values;
  return $result;
}
