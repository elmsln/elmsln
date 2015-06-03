<?php

/**
 * @file
 * Display Suite Extras administrative functions.
 */

/**
 * Menu callback: Display Suite extras settings.
 */
function ds_extras_settings($form) {

  $form['additional_settings'] = array(
    '#type' => 'vertical_tabs',
    '#theme_wrappers' => array('vertical_tabs'),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  $form['additional_settings']['fs1'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field Templates'),
  );

  $form['additional_settings']['fs1']['ds_extras_field_template'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Field Templates'),
    '#description' => t('Customize the labels and the HTML output of your fields.'),
    '#default_value' => variable_get('ds_extras_field_template', FALSE),
  );

  $theme_functions = module_invoke_all('ds_field_theme_functions_info');
  $form['additional_settings']['fs1']['ft-default'] = array(
    '#type' => 'select',
    '#title' => t('Default Field Template'),
    '#options' => $theme_functions,
    '#default_value' => variable_get('ft-default', 'theme_field'),
    '#description' => t('Default will output the field as defined in Drupal Core.<br />Reset will strip all HTML.<br />Minimal adds a simple wrapper around the field.<br/>There is also an Expert Field Template that gives full control over the HTML, but can only be set per field.<br /><br />You can override this setting per field on the "Manage display" screens or when creating fields on the instance level.<br /><br /><strong>Template suggestions</strong><br />You can create .tpl files as well for these field theme functions, e.g. field--reset.tpl.php, field--minimal.tpl.php<br /><br /><label>CSS classes</label>You can add custom CSS classes on the <a href="!url">classes form</a>. Display Suite UI needs to be enabled for this. These classes can be added to fields using the Default Field Template.<br /><br /><label>Advanced</label>You can create your own custom field templates which need to be defined with hook_ds_field_theme_functions_info(). See ds.api.php for an example.', array('!url' => url('admin/structure/ds/classes'))),
    '#states' => array(
      'visible' => array(
        'input[name="additional_settings[fs1][ds_extras_field_template]"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['additional_settings']['fs1']['ft-kill-colon'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide colon'),
    '#default_value' => variable_get('ft-kill-colon', FALSE),
    '#description' => t('Hide the colon on the reset field template.'),
    '#states' => array(
      'visible' => array(
        'select[name="additional_settings[fs1][ft-default]"]' => array('value' => 'theme_ds_field_reset'),
        'input[name="additional_settings[fs1][ds_extras_field_template]"]' => array('checked' => TRUE),
      ),
    ),
  );


  $form['additional_settings']['fs2'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra fields'),
  );

  $form['additional_settings']['fs2']['ds_extras_fields_extra'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable extra fields'),
    '#description' => t('Make fields from other modules available on the "Manage display" screens.'),
    '#default_value' => variable_get('ds_extras_fields_extra', FALSE),
  );

  $form['additional_settings']['fs2']['ds_extras_fields_extra_list'] = array(
    '#type' => 'textarea',
    '#description' => t('Enter fields line by line, where each line is a combination of entity type, bundle and field name. E.g. node|article|tweetbutton. It might be possible that the actual content of the field depends on configuration of that field/module.'),
    '#default_value' => variable_get('ds_extras_fields_extra_list', FALSE),
    '#states' => array(
      'visible' => array(
        'input[name="additional_settings[fs2][ds_extras_fields_extra]"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['additional_settings']['fs4'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other'),
  );

  $form['additional_settings']['fs4']['ds_extras_switch_view_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('View mode per node'),
    '#description' => t('Change view modes for individual nodes. A new tab \'Display settings\' will appear on the content create form.<br />You can also pass the name of a view mode through the URL, eg node/x?v=full.<br />If you install the Page manager module and override the node view, Page manager will win.'),
    '#default_value' => variable_get('ds_extras_switch_view_mode', FALSE),
  );

  $form['additional_settings']['fs4']['ds_extras_hide_page_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Page title options'),
    '#description' => t('Hide or manually set the page title of the "Full content" view mode.'),
    '#default_value' => variable_get('ds_extras_hide_page_title', FALSE),
  );

  $form['additional_settings']['fs4']['ds_extras_hide_page_sidebars'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Drupal blocks/regions'),
    '#description' => t('Add ability to disable all sidebar regions displayed in the theme. Note that some themes support this setting better than others. If in doubt, try with stock themes to see.'),
    '#default_value' => variable_get('ds_extras_hide_page_sidebars', FALSE),
  );

  $form['additional_settings']['fs4']['ds_extras_field_permissions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Field permissions'),
    '#description' => t('Enables view permissions on all Display Suite fields.'),
    '#default_value' => variable_get('ds_extras_field_permissions', FALSE),
  );

  $form['additional_settings']['fs4']['ds_extras_region_to_block'] = array(
    '#type' => 'checkbox',
    '#title' => t('Region to block'),
    '#description' => t('Create additional regions exposed as block. Note: this will not work on the default view mode.'),
    '#default_value' => variable_get('ds_extras_region_to_block', FALSE),
  );

  if (module_exists('views')) {
    $form['additional_settings']['fs4']['ds_extras_vd'] = array(
      '#type' => 'checkbox',
      '#title' => t('Views displays'),
      '#description' => t('Manage the layout of your Views layout with Field UI at !url.', array('!url' => l(url('admin/structure/ds/vd', array('absolute' => TRUE)), 'admin/structure/ds/vd'))),
      '#default_value' => variable_get('ds_extras_vd', FALSE),
    );
  }

  if (module_exists('flag')) {
    $form['additional_settings']['fs4']['ds_extras_flag'] = array(
      '#type' => 'checkbox',
      '#title' => t('Flag'),
      '#description' => t('Expose flags as fields on nodes.'),
      '#default_value' => variable_get('ds_extras_flag', FALSE),
    );
  }

  $form['additional_settings']['fs4']['ds_extras_switch_field'] = array(
    '#type' => 'checkbox',
    '#title' => t('View mode switcher'),
    '#description' => t('Adds a field with links to switch view modes inline with Ajax. Only works for nodes at this time. It does not work in combination with the reset layout.'),
    '#default_value' => variable_get('ds_extras_switch_field', FALSE),
  );

  $form['additional_settings']['fs4']['ds_extras_hidden_region'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hidden region'),
    '#description' => t('Add a hidden region to the layouts. Fields will be built but not printed.'),
    '#default_value' => variable_get('ds_extras_hidden_region', FALSE),
  );

  $form['#attached']['js'][] = drupal_get_path('module', 'ds_extras') . '/js/ds_extras.admin.js';

  $form = system_settings_form($form);
  $form['#submit'][] = 'ds_extras_settings_submit';
  return $form;
}

/**
 * Validate callback: Extras settings screen.
 */
function ds_extras_settings_validate($form, &$form_state) {
  foreach ($form_state['values']['additional_settings'] as $tab => $value) {
    if (is_array($value)) {
      foreach ($value as $variable => $val) {
        $form_state['values'][$variable] = $val;
      }
    }
    unset($form_state['values']['additional_settings'][$tab]);
  }
  unset($form_state['values']['additional_settings']);
}

/**
 * Submit callback: Extras settings screen.
 */
function ds_extras_settings_submit($form, &$form_state) {
  cache_clear_all('ds_fields:', 'cache', TRUE);
  cache_clear_all('entity_info:', 'cache', TRUE);
  cache_clear_all('theme_registry:', 'cache', TRUE);
  cache_clear_all('module_implements', 'cache_bootstrap');
  cache_clear_all('field_info_fields', 'cache_field');
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * Alter Manage display screen.
 */
function ds_extras_field_ui_alter(&$form, &$form_state) {
  // Attach js.
  $form['#attached']['js'][] = drupal_get_path('module', 'ds_extras') . '/js/ds_extras.admin.js';

  // Views displays.
  if ($form['#entity_type'] == 'ds_views') {
    // Add an additional submit callback so we can ditch the extra title
    // which is added by ds_extras_field_extra_fields().
    $form['#submit'] = array_merge(array('ds_extras_vd_field_ui_submit'), $form['#submit']);
  }

  // Page title functionality, currently only works on nodes, users and taxonomy terms.
  if (variable_get('ds_extras_hide_page_title', FALSE) && isset($form['#ds_layout']) && (in_array($form['#entity_type'], array('node', 'user', 'taxonomy_term', 'profile2')) && ($form['#view_mode'] == 'full' || $form['#view_mode'] == 'revision' ||  (variable_get('ds_extras_switch_view_mode', FALSE) && $form['#entity_type'] == 'node')) || $form['#entity_type'] == 'ds_views' || $form['#entity_type'] == 'profile2')) {
    $form['additional_settings']['ds_page_title'] = array(
      '#type' => 'fieldset',
      '#title' => t('Custom page title'),
    );
    $form['additional_settings']['ds_page_title']['ds_page_title_options'] = _ds_extras_page_title_options($form['#ds_layout']->settings, $form['#entity_type']);
  }

  // Disable page regions.
  if (variable_get('ds_extras_hide_page_sidebars', FALSE) && isset($form['#ds_layout']) && $form['#view_mode'] != 'form') {
    $form['additional_settings']['ds_layouts']['hide_sidebars'] = array(
      '#type' => 'checkbox',
      '#title' => t('Disable Drupal blocks/regions'),
      '#default_value' => isset($form['#ds_layout']->settings['hide_sidebars']) ? $form['#ds_layout']->settings['hide_sidebars'] : FALSE,
      '#weight' => 3,
    );
  }

  // Region to block only fires if there is a layout and we're working on the
  // a view mode which is not equal to default.
  if (isset($form['#ds_layout']) && $form['#view_mode'] != 'default' && variable_get('ds_extras_region_to_block', FALSE)) {

    $layout = $form['#ds_layout'];

    // Get the entity_type, bundle and view mode.
    $entity_type = $form['#entity_type'];
    $bundle = $form['#bundle'];
    $view_mode = $form['#view_mode'];

    $region_blocks_options = array();
    $region_blocks = variable_get('ds_extras_region_blocks', array());
    foreach ($region_blocks as $key => $block) {
      if ($block['info'] == "{$entity_type}_{$bundle}_{$view_mode}") {
        $region_blocks_options[$key] = t('Remove') . ' ' . $block['title'];
      }
    }

    $form['additional_settings']['region_to_block'] = array(
      '#type' => 'fieldset',
      '#title' => t('Block regions'),
      '#description' => t('Create additional regions in this layout which will be exposed as blocks. Note that preprocess fields will fail to print.')
    );

    $form['additional_settings']['region_to_block']['new_block_region'] = array(
      '#type' => 'textfield',
      '#title' => t('Region name'),
      '#description' => t('Enter a name to create a new region.'),
    );
    $form['additional_settings']['region_to_block']['new_block_region_key'] = array(
      '#title' => t('Machine name'),
      '#type' => 'machine_name',
      '#default_value' => '',
      '#maxlength' => 32,
      '#required' => FALSE,
      '#description' => t('The machine-readable name of this block region. This name must contain only lowercase letters and underscores. This name must be unique.'),
      '#disabled' => FALSE,
      '#machine_name' => array(
        'exists' => 'ds_extras_region_to_block_unique',
        'source' => array('additional_settings', 'region_to_block', 'new_block_region'),
      ),
    );

    if (!empty($region_blocks_options)) {
      $form['additional_settings']['region_to_block']['remove_block_region'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Existing block regions'),
        '#options' => $region_blocks_options,
        '#description' => t('Check the regions you want to remove.'),
      );
    }

    $form['#submit'][] = 'ds_extras_block_submit';
  }
}

/**
 * Field template settings form
 */
function ds_extras_field_template_settings_form(array &$form, array &$form_state, array $context) {
  $functions = module_invoke_all('ds_field_theme_functions_info');
  $default_field_function = variable_get('ft-default', 'theme_field');
  $key = $context['instance']['field_name'];

  $field_settings = isset($form_state['formatter_settings'][$key]) ? $form_state['formatter_settings'][$key]['ft'] : array();

  $field_function = isset($field_settings['func']) ? $field_settings['func'] : $default_field_function;
  $field_classes = _ds_classes('ds_classes_fields');

  $form['ft'] = array(
    '#weight' => 20,
  );

  // Functions.
  $form['ft']['func'] = array(
    '#title' => t('Choose a Field Template'),
    '#type' => 'select',
    '#options' => $functions,
    '#default_value' => $field_function,
    '#attributes' => array(
      'class' => array('ds-extras-field-template'),
    ),
  );

  // Field classes.
  if (!empty($field_classes)) {
    $field_classes_select = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $field_classes,
      '#title' => t('Choose additional CSS classes for the field'),
      '#default_value' => isset($field_settings['classes']) ? explode(' ', $field_settings['classes']) : array(),
      '#prefix' => '<div class="field-classes">',
      '#suffix' => '</div>',
    );
    $form['ft']['classes'] = $field_classes_select;
  }
  else {
    $form['ft']['classes'] = array(
      '#type' => 'value',
      '#value' => array(''),
    );
  }

  // Add prefix
  $form['ft']['prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Prefix'),
    '#size' => '100',
    '#description' => t('You can enter any html in here.'),
    '#default_value' => isset($field_settings['prefix']) ? $field_settings['prefix'] : '',
    '#prefix' => '<div class="field-prefix">',
    '#suffix' => '</div>',
  );

  // Wrappers and label.
  $wrappers = array(
    'lb' => array('title' => t('Label')),
    'lbw' => array('title' => t('Label wrapper')),
    'ow' => array('title' => t('Outer wrapper')),
    'fis' => array('title' => t('Field items')),
    'fi' => array('title' => t('Field item')),
  );

  foreach ($wrappers as $wrapper_key => $value) {

    $classes = array(
      'field-name-' . strtr($key, '_', '-'),
    );
    $form['ft'][$wrapper_key] = array(
      '#type' => 'checkbox',
      '#title' => $value['title'],
      '#prefix' => '<div class="ft-group ' . $wrapper_key . '">',
      '#default_value' => isset($field_settings[$wrapper_key]) ? $field_settings[$wrapper_key] : FALSE,
    );
    $form['ft'][$wrapper_key . '-el'] = array(
      '#type' => 'textfield',
      '#title' => t('Element'),
      '#size' => '10',
      '#description' => t('E.g. div, span, h2 etc.'),
      '#default_value' => isset($field_settings[$wrapper_key . '-el']) ? $field_settings[$wrapper_key . '-el'] : '',
      '#states' => array(
        'visible' => array(
          ':input[name$="[ft][' . $wrapper_key . ']"]' => array('checked' => TRUE),
        ),
      ),
    );
    $form['ft'][$wrapper_key . '-cl'] = array(
      '#type' => 'textfield',
      '#title' => t('Classes'),
      '#size' => '10',
      '#default_value' => isset($field_settings[$wrapper_key . '-cl']) ? $field_settings[$wrapper_key . '-cl'] : '',
      '#description' => t('E.g.') .' ' . implode(', ', $classes),
      '#states' => array(
        'visible' => array(
          ':input[name$="[ft][' . $wrapper_key . ']"]' => array('checked' => TRUE),
        ),
      ),
    );
    $form['ft'][$wrapper_key . '-at'] = array(
      '#type' => 'textfield',
      '#title' => t('Attributes'),
      '#size' => '20',
      '#default_value' => isset($field_settings[$wrapper_key . '-at']) ? $field_settings[$wrapper_key . '-at'] : '',
      '#description' => t('E.g. name="anchor"'),
      '#states' => array(
        'visible' => array(
          ':input[name$="[ft][' . $wrapper_key . ']"]' => array('checked' => TRUE),
        ),
      ),
    );

    // Hide colon.
    if ($wrapper_key == 'lb') {
      $form['ft']['lb-col'] = array(
        '#type' => 'checkbox',
        '#title' => t('Hide label colon'),
        '#default_value' => isset($field_settings['lb-col']) ? $field_settings['lb-col'] : FALSE,
        '#attributes' => array(
          'class' => array('colon-checkbox'),
        ),
      );
    }
    if ($wrapper_key == 'fi') {
      $form['ft']['fi-odd-even'] = array(
        '#type' => 'checkbox',
        '#title' => t('Add odd/even classes'),
        '#default_value' => isset($field_settings['fi-odd-even']) ? $field_settings['fi-odd-even'] : FALSE,
        '#states' => array(
          'visible' => array(
            ':input[name$="[ft][' . $wrapper_key . ']"]' => array('checked' => TRUE),
          ),
        ),
      );
      $form['ft']['fi-first-last'] = array(
        '#type' => 'checkbox',
        '#title' => t('Add first/last classes'),
        '#default_value' => isset($field_settings['fi-first-last']) ? $field_settings['fi-first-last'] : FALSE,
        '#states' => array(
          'visible' => array(
            ':input[name$="[ft][' . $wrapper_key . ']"]' => array('checked' => TRUE),
          ),
        ),
      );
    }
    if ($wrapper_key != 'lbw') {
      $form['ft'][$wrapper_key . '-def-at'] = array(
        '#type' => 'checkbox',
        '#title' => t('Add default attributes'),
        '#default_value' => isset($field_settings[$wrapper_key . '-def-at']) ? $field_settings[$wrapper_key . '-def-at'] : FALSE,
        '#suffix' => ($wrapper_key == 'ow') ? '' : '</div>',
        '#states' => array(
          'visible' => array(
            ':input[name$="[ft][' . $wrapper_key . ']"]' => array('checked' => TRUE),
          ),
        ),
      );
    }
    else {
      $form['ft'][$wrapper_key . '-def-at'] = array(
        '#markup' => '</div><div class="clearfix"></div>',
      );
    }

    // Default classes for outer wrapper.
    if ($wrapper_key == 'ow') {
      $form['ft'][$wrapper_key . '-def-cl'] = array(
        '#type' => 'checkbox',
        '#title' => t('Add default classes'),
        '#default_value' => isset($field_settings[$wrapper_key . '-def-cl']) ? $field_settings[$wrapper_key . '-def-cl'] : FALSE,
        '#suffix' => '</div>',
        '#states' => array(
          'visible' => array(
            ':input[name$="[ft][' . $wrapper_key . ']"]' => array('checked' => TRUE),
          ),
        ),
      );
    }
  }

  // Add suffix
  $form['ft']['suffix'] = array(
    '#type' => 'textfield',
    '#title' => t('Suffix'),
    '#size' => '100',
    '#description' => t('You can enter any html in here.'),
    '#default_value' => isset($field_settings['suffix']) ? $field_settings['suffix'] : '',
    '#prefix' => '<div class="field-prefix">',
    '#suffix' => '</div>',
  );

  // Another label needs some other stuff.
  unset($form['ft']['lb']['#description']);
  $form['ft']['lb']['#type'] = 'textfield';
  $form['ft']['lb']['#size'] = '10';
  $form['ft']['lb']['#attributes'] = array('class' => array('label-change'));
  $form['ft']['lb']['#default_value'] = isset($field_settings['lb']) ? $field_settings['lb'] : '';

  // Let other modules make modifications to the settings form as needed.
  drupal_alter('ds_field_theme_functions_settings_form_alter', $form, $field_settings);
}

/**
 * Implements hook_ds_field_format_summary().
 */
function ds_extras_ds_field_format_summary($field) {
  if (isset($field['formatter_settings'])) {
    foreach ($field['formatter_settings'] as $key => $value) {
      if (!empty($value)) {
        return t('Configured');
        break;
      }
    }
  }
  return t('Not configured');
}

/**
 * Implements hook_ds_field_settings_form().
 */
function ds_extras_ds_field_settings_form($field) {
  $form = array();

  // Switch field.
  if (variable_get('ds_extras_switch_field') && $field['name'] == 'ds_switch_field') {
    $entity_type = $field['entity_type'];
    $bundle = $field['bundle'];
    $view_mode = $field['view_mode'];
    $settings = isset($field['formatter_settings']['vms']) ? $field['formatter_settings']['vms'] : array();
    $view_modes = ds_entity_view_modes($entity_type);

    $form['info'] = array(
      '#markup' => t('Enter a label for the link for the view modes you want to switch to.<br />Leave empty to hide link. They will be localized.'),
    );

    foreach ($view_modes as $key => $value) {

      $view_mode_settings = field_view_mode_settings($entity_type, $bundle);
      $visible = !empty($view_mode_settings[$key]['custom_settings']);

      if ($visible) {
        $form['vms'][$key] = array(
          '#type' => 'textfield',
          '#default_value' => isset($settings[$key]) ? $settings[$key] : '',
          '#size' => 20,
          '#title' => check_plain($value['label']),
        );
      }
    }
  }

  return $form;
}

/**
 * Submit callback after Field UI submission of a views display.
 */
function ds_extras_vd_field_ui_submit($form, &$form_state) {
  // Add the 'type' key to the extra title key so we can ditch the notice.
  $form_state['values']['fields']['title']['type'] = 'hidden';
}

/**
 * Submit callback: manage block regions.
 */
function ds_extras_block_submit($form, &$form_state) {

  // Create new region.
  if (!empty($form_state['values']['additional_settings']['region_to_block']['new_block_region'])) {

    // Get the entity_type, bundle and view mode.
    $entity_type = $form['#entity_type'];
    $bundle = $form['#bundle'];
    $view_mode = $form['#view_mode'];

    $block = array(
      'title' => $form_state['values']['additional_settings']['region_to_block']['new_block_region'],
      'info' => "{$entity_type}_{$bundle}_{$view_mode}",
    );

    $block_key = $form_state['values']['additional_settings']['region_to_block']['new_block_region_key'];
    $region_blocks = variable_get('ds_extras_region_blocks', array());
    $region_blocks[$block_key] = $block;
    variable_set('ds_extras_region_blocks', $region_blocks);
  }

  // Remove a region.
  if (isset($form_state['values']['additional_settings']['region_to_block']['remove_block_region'])) {
    $variable_set = FALSE;
    $region_blocks = variable_get('ds_extras_region_blocks', array());
    $remove = $form_state['values']['additional_settings']['region_to_block']['remove_block_region'];
    foreach ($remove as $key => $value) {
      if ($value != 0 && $key == $value) {
        $variable_set = TRUE;
        if (module_exists('block')) {
          db_delete('block')
            ->condition('delta', $key)
            ->condition('module', 'ds_extras')
            ->execute();
        }
        unset($region_blocks[$key]);
      }
    }

    if ($variable_set) {
      variable_set('ds_extras_region_blocks', $region_blocks);
    }
  }
}

/**
 * Return unique region to block.
 */
function ds_extras_region_to_block_unique($name) {
  $region_blocks = variable_get('ds_extras_region_blocks', array());
  $value = strtr($name, array('-' => '_'));
  return isset($region_blocks[$value]) ? TRUE : FALSE;
}

/**
 * Helper function to show the page title options.
 */
function _ds_extras_page_title_options($settings, $entity_type) {

  $return['page_option_type'] = array(
    '#type' => 'select',
    '#title' => t('Page title'),
    '#options' => array(
      '0' => t('Show'),
      '1' => t('Hide'),
      '2' => t('Manually set'),
    ),
    '#default_value' => isset($settings['hide_page_title']) ? $settings['hide_page_title'] : FALSE,
    '#weight' => 100,
  );

  // Display Suite Views currently only supports hiding the page title.
  if ($entity_type == 'ds_views') {
    unset($return['page_option_type']['#options'][2]);
  }

  $contexts = ds_get_entity_context($entity_type);
  $rows = array();
  foreach ($contexts as $context) {
    foreach (ctools_context_get_converters('%' . check_plain($context->keyword) . ':', $context) as $keyword => $title) {
      $rows[] = array(
        check_plain($keyword),
        t('@identifier: @title', array('@title' => $title, '@identifier' => $context->identifier)),
      );
    }
  }

  $return['page_option_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($settings['page_option_title']) ? $settings['page_option_title'] : '',
    '#description' => t('The title, you may use substitutions in this title.'),
    '#weight' => 101,
    '#access' => $entity_type != 'ds_views',
    '#states' => array(
      'visible' => array(
        array(':input[name="page_option_type"]' => array('value' => '2')),
        array(':input[name="additional_settings[ds_page_title][ds_page_title_options][page_option_type]"]' => array('value' => '2')),
      ),
    ),
  );

  $header = array(t('Keyword'), t('Value'));
  $return['page_option_contexts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Substitutions'),
    // Doesn't work because of http://drupal.org/node/1015798
    //'#collapsible' => TRUE,
    //'#collapsed' => TRUE,
    '#value' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#weight' => 102,
    '#access' => $entity_type != 'ds_views',
    '#states' => array(
      'visible' => array(
        array(':input[name="page_option_type"]' => array('value' => '2')),
        array(':input[name="additional_settings[ds_page_title][ds_page_title_options][page_option_type]"]' => array('value' => '2')),
      ),
    ),
  );

  return $return;
}
