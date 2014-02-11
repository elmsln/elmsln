<?php

/**
 * @file
 * Administrative functions for Display Suite search.
 */

/**
 * Menu callback: Display Suite search settings.
 */
function ds_search_settings($form, $form_state) {

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
  );

  $engine_options = array();
  foreach (module_implements('search_info') as $module) {
    if ($module != 'ds_search' && $module != 'user') {
      $engine_options[$module] = drupal_ucfirst(str_replace('_', ' ', $module));
    }
  }

  $form['general']['ds_search_type'] = array(
    '#type' => 'select',
    '#title' => t('Search engine'),
    '#description' => t('Select the search engine as the query backend.'),
    '#options' => $engine_options,
    '#default_value' => variable_get('ds_search_type', 'node'),
  );

  $form['general']['ds_search_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Search path'),
    '#field_prefix' => 'search/',
    '#description' => t('Make sure you don\'t override an existing search path.'),
    '#default_value' => variable_get('ds_search_path', 'content'),
    '#required' => TRUE,
  );

  $entity_view_modes = ds_entity_view_modes('node');
  foreach ($entity_view_modes as $key => $view_mode) {
    $view_mode_options[$key] = $view_mode['label'];
  }
  $form['general']['ds_search_view_mode'] = array(
    '#type' => 'select',
    '#title' => t('View mode'),
    '#description' => 'Select another view mode in favor of the default search view mode.',
    '#default_value' => variable_get('ds_search_view_mode', 'search_result'),
    '#options' => $view_mode_options,
  );

  $form['general']['ds_search_file_render'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use default search theming for files'),
    '#description' => t('File/attachment results are best supported when the file entity module is enabled. Toggle the checkbox in case it is not available or you want to use default search theming.'),
    '#default_value' => variable_get('ds_search_file_render', FALSE),
  );

  $form['general']['ds_search_variables'] = array(
    '#type' => 'radios',
    '#options' => array(
      'none' => t('None'),
      'search_totals' => t('Total results'),
      'search_totals_plus_keywords' => t('Total results + keywords'),
      'search_totals_from_to_end' => t('Totals + start to end')
    ),
    '#title' => t('Extra variables'),
    '#description' => t('Choose an extra variable to display on the results screen.'),
    '#default_value' => variable_get('ds_search_variables', 'none'),
  );

  $form['general']['ds_search_show_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show title'),
    '#description' => t('Display the "Search results" title.'),
    '#default_value' => variable_get('ds_search_show_title'),
  );

  $form['general']['ds_search_language'] = array(
    '#type' => 'checkbox',
    '#title' => t('Language'),
    '#description' => t('Search in the language the site is currently in. Enable this if you have at least 2 languages.'),
    '#default_value' => variable_get('ds_search_language'),
  );

  $form['general']['ds_search_highlight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Highlight search word'),
    '#description' => t('Use jQuery to highlight the word in the results.'),
    '#default_value' => variable_get('ds_search_highlight'),
  );

  $form['general']['ds_search_highlight_selector'] = array(
    '#type' => 'textfield',
    '#title' => t('HTML selector'),
    '#description' => t('Enter the css selector, if not sure, leave this by default.'),
    '#default_value' => variable_get('ds_search_highlight_selector', '.view-mode-search_result'),
    '#states' => array(
      'visible' => array(
        'input[name="ds_search_highlight"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['general']['ds_search_group_by_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Group by type.'),
    '#description' => t('Group the search results per page by type. Note that this only works if you only display nodes on the search result page.'),
    '#default_value' => variable_get('ds_search_group_by_type'),
  );

  // Group by type order.
  $form['ds_search_group_by_type_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Group by type settings'),
    '#description' => t('Set the order of the node types which can be grouped. Node types which are not enabled will be showed into a "Other group". Note that this does not work with Apache Solr multisite support.'),
    '#theme' => 'ds_search_group_by_type_settings',
    '#states' => array(
      'visible' => array(
        'input[name="ds_search_group_by_type"]' => array('checked' => TRUE),
      ),
    ),
  );

  $node_types = node_type_get_names();
  $ds_search_group_by_type_settings = variable_get('ds_search_group_by_type_settings');
  foreach ($node_types as $name => $label) {

    $form['ds_search_group_by_type_settings'][$name]['name'] = array(
      '#markup' => check_plain($label),
    );

    $form['ds_search_group_by_type_settings'][$name]['status'] = array(
      '#type' => 'checkbox',
      '#title' => t('Weight for @title', array('@title' => $label)),
      '#title_display' => 'invisible',
      '#default_value' => isset($ds_search_group_by_type_settings[$name]) ? $ds_search_group_by_type_settings[$name]['status'] : TRUE,
      '#parents' => array('ds_search_group_by_type_settings', $name, 'status'),
    );

    $form['ds_search_group_by_type_settings'][$name]['label'] = array(
      '#type' => 'textfield',
      '#size' => 30,
      '#title' => t('Group label for @title', array('@title' => $label)),
      '#title_display' => 'invisible',
      '#description' => t('Group label. The label will be translatable. Leave empty for no label.'),
      '#default_value' => isset($ds_search_group_by_type_settings[$name]) ? $ds_search_group_by_type_settings[$name]['label'] : t('Results for @type', array('@type' => drupal_strtolower($node_types[$name]))),
      '#parents' => array('ds_search_group_by_type_settings', $name, 'label'),
    );

    $wrapper_options = array(
      'fieldset' => t('Fieldset'),
      'markup' => t('Div with H3 headline'),
    );
    $form['ds_search_group_by_type_settings'][$name]['wrapper'] = array(
      '#type' => 'select',
      '#options' => $wrapper_options,
      '#title' => t('Wrapper for @title', array('@title' => $label)),
      '#title_display' => 'invisible',
      '#default_value' => isset($ds_search_group_by_type_settings[$name]) ? $ds_search_group_by_type_settings[$name]['wrapper'] : 'fieldset',
      '#parents' => array('ds_search_group_by_type_settings', $name, 'wrapper'),
    );

    $weight = isset($ds_search_group_by_type_settings[$name]) ? $ds_search_group_by_type_settings[$name]['weight'] : 0;
    $form['ds_search_group_by_type_settings'][$name]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight for @title', array('@title' => $label)),
      '#title_display' => 'invisible',
      '#delta' => 30,
      '#default_value' => $weight,
      '#parents' => array('ds_search_group_by_type_settings', $name, 'weight'),
    );
    $form['ds_search_group_by_type_settings'][$name]['#weight'] = $weight;
  }

  $form['ds_search_group_by_type_settings']['ds_search_group_by_type_other'] = array(
    '#type' => 'textfield',
    '#title' => t('Other label'),
    '#description' => t('The label of the other group. Leave empty for no label.'),
    '#default_value' => variable_get('ds_search_group_by_type_other', 'Other'),
    '#states' => array(
      'visible' => array(
        'input[name="ds_search_group_by_type"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['ds_search_group_by_type_settings']['ds_search_group_by_type_other_wrapper'] = array(
    '#type' => 'select',
    '#options' => $wrapper_options,
    '#title' => t('Other wrapper'),
    '#description' => t('The wrapper of the other group.'),
    '#default_value' => variable_get('ds_search_group_by_type_other_wrapper', 'fieldset'),
    '#states' => array(
      'visible' => array(
        'input[name="ds_search_group_by_type"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['node'] = array(
    '#type' => 'fieldset',
    '#title' => t('Drupal core'),
    '#states' => array(
      'visible' => array(
        'select[name="ds_search_type"]' => array('value' => 'node'),
      ),
    ),
  );

  $form['node']['ds_search_node_form_alter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Advanced'),
    '#description' => t('Enable the advanced search form.'),
    '#default_value' => variable_get('ds_search_node_form_alter'),
  );

  $form['node']['ds_search_node_limit'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('ds_search_node_limit', 10),
    '#title' => t('Node search limit'),
    '#description' => t('The number of items to display per page. Enter 0 for no limit.'),
  );

  if (module_exists('apachesolr')) {

    $form['apachesolr_search'] = array(
      '#type' => 'fieldset',
      '#title' => t('Apache Solr'),
      '#states' => array(
        'visible' => array(
          'select[name="ds_search_type"]' => array('value' => 'apachesolr_search'),
        ),
      ),
    );

    $form['apachesolr_search']['ds_search_apachesolr_hide_current_filters'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide Retain filters'),
      '#description' => t('Hide the "Retain current filters" checkbox on search results.'),
      '#default_value' => variable_get('ds_search_apachesolr_hide_current_filters'),
    );

    $form['apachesolr_search']['ds_search_apachesolr_current_filters_default'] = array(
      '#type' => 'checkbox',
      '#title' => t('Remember filters'),
      '#description' => t('Remember the filters when you hide the "Retain current filters" checkbox.'),
      '#default_value' => variable_get('ds_search_apachesolr_current_filters_default'),
      '#states' => array(
        'visible' => array(
          'input[name="ds_search_apachesolr_hide_current_filters"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['apachesolr_search']['ds_search_apachesolr_multisite'] = array(
      '#type' => 'checkbox',
      '#title' => t('Multisite support'),
      '#description' => t('Enable this in case multiple sites share one index. Note that sometimes you need to make sure that your formatters are creating absolute paths for links or images. Implementing hook_url_outbound_alter() is a good option in which you can set $options[\'absolute\'] to TRUE.'),
      '#default_value' => variable_get('ds_search_apachesolr_multisite'),
    );

    $form['apachesolr_search']['ds_search_apachesolr_multisite_boost'] = array(
      '#type' => 'checkbox',
      '#title' => t('Sort by site'),
      '#description' => t('Enable this to rank the results of the current site first, than all the rest.'),
      '#default_value' => variable_get('ds_search_apachesolr_multisite_boost'),
      '#states' => array(
        'visible' => array(
          'input[name="ds_search_apachesolr_multisite"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['apachesolr_search']['ds_search_apachesolr_multisite_group'] = array(
      '#type' => 'checkbox',
      '#title' => t('Group results by site'),
      '#default_value' => variable_get('ds_search_apachesolr_multisite_group'),
      '#states' => array(
        'visible' => array(
          'input[name="ds_search_apachesolr_multisite"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['apachesolr_search']['ds_search_apachesolr_multisite_group_config'] = array(
      '#type' => 'textarea',
      '#title' => t('Group by site configuration'),
      '#default_value' => variable_get('ds_search_apachesolr_multisite_group_config'),
      '#description' => t('Enter sites line by line with following configuration: site-hash|label|wrapper. The <em>site-hash</em> is per site which you can get from Solr. The <em>label</em> is translatable per site. Use !total_per_site in this label for number of results per site. Depending on the number, you will either get "1 result" or "x results" which are translatable. The <em>wrapper</em> can either be "fieldset" or "div".'),
      '#states' => array(
        'visible' => array(
          'input[name="ds_search_apachesolr_multisite_group"]' => array('checked' => TRUE),
          'input[name="ds_search_apachesolr_multisite"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  $active = variable_get('search_active_modules', array('node', 'user'));
  if (isset($active['user']) && $active['user'] !== 0) {
    $form['user'] = array(
      '#type' => 'fieldset',
      '#title' => t('User search'),
    );

    $form['user']['ds_user_override_search_page'] = array(
      '#type' => 'checkbox',
      '#title' => t('Override user search page'),
      '#description' => t('Toggle this checkbox if you want Display Suite to render user search results.'),
      '#default_value' => variable_get('ds_user_override_search_page'),
    );
  }

  $form = system_settings_form($form);
  $form['#submit'][] = 'ds_search_settings_submit';
  return $form;
}

/**
 * Submit callback: Search settings submit.
 */
function ds_search_settings_submit($form, $form_state) {
  // Rebuild the menu.
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * Returns HTML for the Group by type settings.
 */
function theme_ds_search_group_by_type_settings($variables) {
  $element = $variables['element'];

  // Type order (tabledrag).
  $rows = array();
  foreach (element_children($element, TRUE) as $name) {

    if (!isset($element[$name]['name'])) {
      continue;
    }

    $element[$name]['weight']['#attributes']['class'][] = 'type-order-weight';
    $rows[] = array(
      'data' => array(
        drupal_render($element[$name]['name']),
        drupal_render($element[$name]['status']),
        drupal_render($element[$name]['label']),
        drupal_render($element[$name]['wrapper']),
        drupal_render($element[$name]['weight']),
      ),
      'class' => array('draggable'),
    );
  }

  $header = array(t('Type'), t('Status'), t('Group label'), t('Wrapper'), t('Weight'));
  $output = drupal_render_children($element);
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'group-by-order')));
  drupal_add_tabledrag('group-by-order', 'order', 'sibling', 'type-order-weight', NULL, NULL, TRUE);

  return $output;
}
