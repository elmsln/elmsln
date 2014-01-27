<?php

/**
 * @file
 * Breakpoints - admin settings
 */

/**
 * Admin form
 */
function breakpoints_admin_breakpoints($form, &$form_state, $breakpoint_group_name = '') {
  $form = array();

  // In case of an export to theme, there will be a variable exported_breakpoints
  if (isset($form_state['exported_breakpoints']) && !empty($form_state['exported_breakpoints'])) {
    $form['exported_breakpoints'] = array(
      '#title' => t('Copy/Paste the following inside your theme.info file.'),
      '#type' => 'textarea',
      '#default_value' => $form_state['exported_breakpoints'],
    );
  }
  // Global is the same as no group name
  $global = FALSE;
  if ($breakpoint_group_name == '' || $breakpoint_group_name == 'global') {
    $breakpoint_group_name = '';
    $global = TRUE;
  }

  $form_state['group_name'] = $breakpoint_group_name;

  $settings = breakpoints_settings();
  $multipliers = array();
  if (isset($settings->multipliers) && !empty($settings->multipliers)) {
    $multipliers = drupal_map_assoc(array_values($settings->multipliers));
    if (array_key_exists('1x', $multipliers)) {
      unset($multipliers['1x']);
    }
  }

  if ($global) {
    $form['info'] = array(
      '#type' => 'markup',
      '#markup' => t("You can manage all your breakpoints on this screen, if one of your themes has breakpoints defined inside the .info file they will be shown here."),
    );

    $info = array();
    $info[] = t("To create a new breakpoint, you have to enter a name and a media query (ex. (min-width: 15em)).");
    $info[] = t("All breakpoints can be enabled or disabled so they cannot be used by other modules.");
    $info[] = t("For each breakpoint you can define what multipliers have to be available (needed to support 'retina' displays).");
    $info[] = t("Breakpoints you created yourself can be deleted.");
    $info[] = t("You can group multiple breakpoints in a group by using '!add', so other modules can easily interact with them.", array('!add' => l(t('Add a new group'), 'admin/config/media/breakpoints/groups/add')));

    $form['more_info'] = array(
      '#type' => 'container',
      '#theme' => 'item_list',
      '#items' => $info,
    );
  }
  else {
    $form['info'] = array(
      '#type' => 'markup',
      '#markup' => t("You can manage the breakpoints of this group here."),
    );
    $info = array();
    $info[] = t("You can change the order of the breakpoints inside this group.");
    $info[] = t("You can enable multipliers for each breakpoint, but this will also affect other groups.");

    $form['more_info'] = array(
      '#type' => 'container',
      '#theme' => 'item_list',
      '#items' => $info,
    );
  }

  $form['#attached']['css'][] = drupal_get_path('module', 'breakpoints') . '/css/breakpoints.admin.css';
  $form['breakpoints'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#theme' => 'breakpoints_admin_breakpoints_table',
    '#multipliers' => $multipliers,
    '#group_name' => $breakpoint_group_name,
  );

  $breakpoints = array();
  $breakpoint_group = breakpoints_breakpoint_group_load($breakpoint_group_name);
  if ($global) {
    $breakpoints = breakpoints_breakpoint_load_all();
  }
  else {
    $weight = 0;
    foreach ($breakpoint_group->breakpoints as $breakpoint_name) {
      $breakpoint = breakpoints_breakpoint_load_by_fullkey($breakpoint_name);
      if ($breakpoint && isset($breakpoint->machine_name)) {
        $breakpoint->global_weight = $breakpoint->weight;
        $breakpoint->weight = $weight++;
        $breakpoints[$breakpoint_name] = $breakpoint;
      }
    }
  }

  foreach ($breakpoints as $key => $breakpoint) {
    if ($breakpoint->source_type == BREAKPOINTS_SOURCE_TYPE_THEME) {
      $bp_group = breakpoints_breakpoint_group_load($breakpoint->source);
      if ($bp_group->overridden && variable_get('breakpoints_hide_overridden_breakpoints', 1) && $global) {
        continue;
      }
    }
    $form['breakpoints'][$key] = array(
      '#breakpoint_data' => $breakpoint,
      'name' => array(
        '#type' => 'textfield',
        '#default_value' => $breakpoint->name,
        '#disabled' => TRUE,
        '#size' => 20,
      ),
      'breakpoint' => array(
        '#type' => 'textfield',
        '#default_value' => $breakpoint->breakpoint,
        '#disabled' => $breakpoint->source_type === 'theme' || !$global,
        '#size' => empty($multipliers) ? 60 : 30,
        '#maxlength' => 255,
      ),
      'weight' => array(
        '#type' => 'textfield',
        '#size' => 4,
        '#default_value' => isset($breakpoint->weight) ? $breakpoint->weight : 0,
        '#attributes' => array('class' => array('breakpoints-weight')),
      ),
    );
    // Add multipliers checkboxes if needed.
    if (!empty($multipliers)) {
      $form['breakpoints'][$key]['multipliers'] = array(
        '#type' => 'checkboxes',
        '#default_value' => (isset($breakpoint->multipliers) && is_array($breakpoint->multipliers)) ? $breakpoint->multipliers : array(),
        '#options' => $multipliers,
      );
    }
    // Add global weight if needed.
    $form['breakpoints'][$key]['global_weight'] = array(
      '#type' => 'value',
      '#value' => isset($breakpoint->global_weight) ? $breakpoint->global_weight : $breakpoint->weight,
    );
  }

  if ($global) {
    // Add empty row
    $form['breakpoints']['new'] = array(
      'name' => array(
        '#type' => 'textfield',
        '#default_value' => '',
        '#size' => 20,
        '#maxlength' => 255,
      ),
      'machine_name' => array(
        '#type' => 'machine_name',
        '#size' => '64',
        '#title' => t('Machine name'),
        '#default_value' => '',
        '#machine_name' => array(
          'exists' => 'breakpoints_breakpoint_name_exists',
          'source' => array('breakpoints', 'new', 'name'),
        ),
        '#required' => FALSE,
        '#maxlength' => 255,
      ),
      'breakpoint' => array(
        '#type' => 'textfield',
        '#default_value' => '',
        '#size' => empty($multipliers) ? 60 : 30,
        '#maxlength' => 255,
      ),
      'weight' => array(
        '#type' => 'textfield',
        '#size' => 4,
        '#default_value' => 0,
        '#attributes' => array('class' => array('breakpoints-weight')),
      ),
    );
    // Add multipliers checkboxes if needed.
    if (!empty($multipliers)) {
      $form['breakpoints']['new']['multipliers'] = array(
        '#type' => 'checkboxes',
        '#default_value' => array(),
        '#options' => $multipliers,
      );
    }
  }

  // Buttons
  $form['buttons'] = array(
    '#type' => 'container',
  );

  // Submit button
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  if (!$global) {
    switch ($breakpoint_group->type) {
      case BREAKPOINTS_SOURCE_TYPE_THEME:
        if (!$breakpoint_group->overridden) {
          $form['buttons']['override'] = array(
            '#type' => 'submit',
            '#value' => t('Override theme breakpoints'),
            '#submit' => array('breakpoints_admin_breakpoints_submit_override'),
          );
          $form['buttons']['reload'] = array(
            '#type' => 'submit',
            '#value' => t('Reload theme breakpoints'),
            '#submit' => array('breakpoints_admin_breakpoints_submit_reload'),
          );
          $form['buttons']['duplicate'] = array(
            '#type' => 'markup',
            '#markup' => l(
              t('Duplicate group'), 'admin/config/media/breakpoints/groups/' . $breakpoint_group_name . '/duplicate',
              array(
                'query' => drupal_get_destination(),
                'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-duplicate-link')),
              )
            ),
          );
        }
        else {
          $form['buttons']['exporttotheme'] = array(
            '#type' => 'submit',
            '#value' => t('Export breakpoints to theme'),
            '#submit' => array('breakpoints_admin_breakpoints_submit_exporttotheme'),
          );
          $form['buttons']['revert'] = array(
            '#type' => 'submit',
            '#value' => t('Revert theme breakpoints'),
            '#submit' => array('breakpoints_admin_breakpoints_submit_revert'),
          );
          $form['buttons']['editlink'] = array(
            '#type' => 'markup',
            '#markup' => l(
              t('Edit group breakpoints'), 'admin/config/media/breakpoints/groups/' . $breakpoint_group_name . '/edit',
              array(
                'query' => drupal_get_destination(),
                'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-edit-link')),
              )
            ),
          );
          $form['buttons']['duplicate'] = array(
            '#type' => 'markup',
            '#markup' => l(
              t('Duplicate group'), 'admin/config/media/breakpoints/groups/' . $breakpoint_group_name . '/duplicate',
              array(
                'query' => drupal_get_destination(),
                'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-duplicate-link')),
              )
            ),
          );
        }
        break;
      case BREAKPOINTS_SOURCE_TYPE_MODULE:
        $form['buttons']['exporttotheme'] = array(
          '#type' => 'submit',
          '#value' => t('Export breakpoints to theme'),
          '#submit' => array('breakpoints_admin_breakpoints_submit_exporttotheme'),
        );
        $form['buttons']['editlink'] = array(
          '#type' => 'markup',
          '#markup' => l(
            t('Edit group breakpoints'), 'admin/config/media/breakpoints/groups/' . $breakpoint_group_name . '/edit',
            array(
              'query' => drupal_get_destination(),
              'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-edit-link')),
            )
          ),
        );
        $form['buttons']['duplicate'] = array(
          '#type' => 'markup',
          '#markup' => l(
            t('Duplicate group'), 'admin/config/media/breakpoints/groups/' . $breakpoint_group_name . '/duplicate',
            array(
              'query' => drupal_get_destination(),
              'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-duplicate-link')),
            )
          ),
        );
        break;
      case BREAKPOINTS_SOURCE_TYPE_CUSTOM:
        $form['buttons']['exporttotheme'] = array(
          '#type' => 'submit',
          '#value' => t('Export breakpoints to theme'),
          '#submit' => array('breakpoints_admin_breakpoints_submit_exporttotheme'),
        );
        $form['buttons']['editlink'] = array(
          '#type' => 'markup',
          '#markup' => l(
            t('Edit group breakpoints'), 'admin/config/media/breakpoints/groups/' . $breakpoint_group_name . '/edit',
            array(
              'query' => drupal_get_destination(),
              'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-edit-link')),
            )
          ),
        );
        $form['buttons']['duplicate'] = array(
          '#type' => 'markup',
          '#markup' => l(
            t('Duplicate group'), 'admin/config/media/breakpoints/groups/' . $breakpoint_group_name . '/duplicate',
            array(
              'query' => drupal_get_destination(),
              'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-duplicate-link')),
            )
          ),
        );
        $form['buttons']['deletelink'] = array(
          '#type' => 'markup',
          '#markup' => l(
            t('Delete this group'), 'admin/config/media/breakpoints/groups/' . $breakpoint_group_name . '/delete',
            array(
              'query' => array('destination' => 'admin/config/media/breakpoints/groups'),
              'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-delete-link')),
            )
          ),
        );
        break;
    }
  }

  return $form;
}

/**
 * Theme form as table.
 */
function theme_breakpoints_admin_breakpoints_table($variables) {
  drupal_add_css(drupal_get_path('module', 'breakpoints') . '/css/breakpoints.admin.css');
  $form = $variables['form'];
  $global = empty($form['#group_name']);
  // Rows.
  $rows = array();
  foreach (element_children($form) as $key) {

    if ($key != 'new') {
      $row = _breakpoints_admin_breakpoints_table_row($form[$key], $key, $global);
      $breakpoint = $form[$key]['#breakpoint_data'];
      $class = 'breakpoints-status-' . ($breakpoint->status ? 'enabled' : 'disabled');
    }
    else {
      $row = _breakpoints_admin_breakpoints_table_new_row($form[$key]);
      $class = 'breakpoints-status-new';
    }

    $rows[] = array(
      'data' => $row,
      'class' => array('draggable', $class),
    );
  }

  // Header.
  $header = array();
  $header[] = array('data' => t('Name'), 'colspan' => 2);
  $header[] = t('Breakpoint, @media ...');
  $header[] = t('Multipliers');
  $header[] = t('Source');
  $header[] = t('Status');
  if ($global) {
    $header[] = array('data' => t('Operations'), 'colspan' => 3);
  }
  $header[] = t('Weight');

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'resp-img-breakpoints')));
  drupal_add_tabledrag('resp-img-breakpoints', 'order', 'sibling', 'breakpoints-weight');
  return $output;
}

/**
 * Helper callback for theme_breakpoints_admin_breakpoints_table().
 */
function _breakpoints_admin_breakpoints_table_row(&$element, $key, $global) {
  $row = array();
  $link_attributes = array(
    'attributes' => array(
      'class' => array('image-style-link'),
    ),
  );
  $breakpoint = $element['#breakpoint_data'];
  $element['weight']['#attributes']['class'] = array('breakpoints-weight');

  $row[] = drupal_render($element['name']);
  $row[] = '';
  $row[] = drupal_render($element['breakpoint']);
  $row[] = drupal_render($element['multipliers']);
  $row[] = $breakpoint->source . ' (' . $breakpoint->source_type . ')';
  $row[] = $breakpoint->status ? t('Enabled') : t('Disabled');

  if ($global) {
    $row[] = l($breakpoint->status ? t('Disable') : t('Enable'), 'admin/config/media/breakpoints/' . ($breakpoint->status ? 'disable' : 'enable') . '/' . $key, $link_attributes);
    $row[] = $breakpoint->source_type == BREAKPOINTS_SOURCE_TYPE_CUSTOM ? l(t('Delete'), 'admin/config/media/breakpoints/delete/' . $key, $link_attributes) : '';
    $row[] = l(t('Export'), 'admin/config/media/breakpoints/export/' . $key, $link_attributes);
  }

  $row[] = drupal_render($element['weight']);
  return $row;
}

/**
 * Helper callback for theme_breakpoints_admin_breakpoints_table().
 */
function _breakpoints_admin_breakpoints_table_new_row(&$element) {
  $row = array();
  $row[] = drupal_render($element['name']);
  $row[] = drupal_render($element['machine_name']);
  $row[] = drupal_render($element['breakpoint']);
  $row[] = drupal_render($element['multipliers']);
  $row[] = '';
  $row[] = '';
  $row[] = '';
  $row[] = '';
  $row[] = '';
  $row[] = drupal_render($element['weight']);
  return $row;
}

/**
 * Admin form validation.
 */
function breakpoints_admin_breakpoints_validate($form, &$form_state) {
  if (strpos($form_state['triggering_element']['#id'], 'remove') === FALSE) {
    $breakpoints = $form_state['values']['breakpoints'];
    if (!empty($breakpoints)) {
      foreach ($breakpoints as $key => $breakpointdata) {
        if (!empty($breakpointdata['name'])) {
          // Breakpoint is required.
          if ($key == 'new') {
            if (empty($breakpointdata['machine_name'])) {
              form_set_error('breakpoints][' . $key . '][machine_name', 'Machine name field is required');
            }
          }
          if (empty($breakpointdata['breakpoint']) && $breakpointdata['breakpoint'] !== '0') {
            form_set_error('breakpoints][' . $key . '][breakpoint', 'Breakpoint field is required');
          }
        }
      }
    }
  }
}

/**
 * Admin form submit.
 */
function breakpoints_admin_breakpoints_submit($form, &$form_state) {
  $breakpoints = $form_state['values']['breakpoints'];
  $group_name = $form_state['group_name'];
  $global_group = $group_name == '';
  $group = breakpoints_breakpoint_group_empty_object();
  if (!$global_group) {
    // sort by weight, needed to store the right order in a group
    uasort($breakpoints, '_breakpoints_sort_by_weight_array');
  }
  $saved_breakpoints = array();
  if (!empty($breakpoints)) {
    foreach ($breakpoints as $breakpointname => $breakpointdata) {
      if (!empty($breakpointdata['name'])) {
        $breakpoint = breakpoints_breakpoint_load_by_fullkey($breakpointname);
        if ($breakpoint && $breakpointname != 'new') {
          // only save the weight when on the global screen.
          if ($global_group) {
            $breakpoint->weight = $breakpointdata['weight'];
          }
          else {
            $breakpoint->weight = $breakpointdata['global_weight'];
          }
          $breakpoint->breakpoint = $breakpointdata['breakpoint'];
          $breakpoint->multipliers = $breakpointdata['multipliers'];
          breakpoints_breakpoint_save($breakpoint);
          $saved_breakpoints[] = $breakpointname;
        }
        else {
          $breakpoint = new stdClass();
          $breakpoint->name = $breakpointdata['name'];
          $breakpoint->breakpoint = $breakpointdata['breakpoint'];
          $breakpoint->source = 'user';
          $breakpoint->source_type = 'custom';
          $breakpoint->weight = $breakpointdata['weight'];
          $breakpoint->status = TRUE;
          $breakpoint->multipliers = $breakpointdata['multipliers'];
          $breakpoint->machine_name = 'custom.user.' . $breakpointdata['machine_name'];
          breakpoints_breakpoint_save($breakpoint);
          $saved_breakpoints[] = breakpoints_breakpoint_config_name($breakpoint);
        }
      }
    }
    if (!$global_group) {
      $group = breakpoints_breakpoint_group_load($group_name);
      if ($group) {
        $group->breakpoints = $saved_breakpoints;
        breakpoints_breakpoint_group_save($group);
      }
    }
  }
}

/**
 * Admin form submit - Override theme breakpoints.
 */
function breakpoints_admin_breakpoints_submit_override($form, &$form_state) {
  $group_name = $form_state['group_name'];
  $group = breakpoints_breakpoint_group_empty_object();
  $global_group = $group_name == '';
  if (!$global_group) {
    $group = breakpoints_breakpoint_group_load($group_name);
    if ($group) {
      breakpoints_breakpoints_group_override($group);
    }
  }
}

/**
 * Admin form submit - Revert theme breakpoints.
 */
function breakpoints_admin_breakpoints_submit_revert($form, &$form_state) {
  $group_name = $form_state['group_name'];
  $global_group = $group_name == '';
  if (!$global_group) {
    $group = breakpoints_breakpoint_group_load($group_name);
    if ($group) {
      breakpoints_breakpoints_group_revert($group);
    }
  }
}

/**
 * Admin form submit - Reload theme breakpoints.
 */
function breakpoints_admin_breakpoints_submit_reload($form, &$form_state) {
  $group_name = $form_state['group_name'];
  $global_group = $group_name == '';
  if (!$global_group) {
    $group = breakpoints_breakpoint_group_load($group_name);
    if ($group) {
      breakpoints_breakpoints_group_reload($group);
    }
  }
}

/**
 * Admin form submit - Export breakpoints to theme.
 */
function breakpoints_admin_breakpoints_submit_exporttotheme($form, &$form_state) {
  $group_name = $form_state['group_name'];
  $global_group = $group_name == '';
  if (!$global_group) {
    $group = breakpoints_breakpoint_group_load($group_name);
    if ($group) {
      $breakpoints = breakpoints_breakpoints_group_exporttotheme($group);
      if ($breakpoints) {
        $export = array();
        foreach ($breakpoints as $breakpoint_name => $breakpoint) {
          $export[] = 'breakpoints[' . $breakpoint_name . '] = ' . $breakpoint;
        }
        $form_state['exported_breakpoints'] = implode("\n", $export);
        $form_state['rebuild'] = TRUE;
      }
    }
  }
}

/**
 * Page callback.
 */
function breakpoints_admin_breakpoint_actions_page($group_name, $action, $breakpoint) {
  if (in_array($action, array('enable', 'disable', 'delete', 'export'))) {
    return drupal_get_form('breakpoints_admin_breakpoint_actions_form', $group_name, $action, $breakpoint);
  }
  return MENU_NOT_FOUND;
}

/**
 * Admin action form: enable, disable, delete, export
 */
function breakpoints_admin_breakpoint_actions_form($form, &$form_state, $group_name, $action, $breakpoint) {
  switch ($action) {
    case 'enable':
    case 'disable':
    case 'delete':
      $form_state['group_name'] = $group_name;
      $form_state['action'] = $action;
      $form_state['breakpoint'] = $breakpoint;
      $question = t('Are you sure you want to %action %breakpoint', array(
            '%action' => $action,
            '%breakpoint' => $breakpoint,
          ));
      if (!empty($group_name)) {
        $path = 'admin/config/media/breakpoints/groups/' . $group_name;
      }
      else {
        $path = 'admin/config/media/breakpoints';
      }
      $form = confirm_form($form, $question, $path, '');
      break;
    case 'export':
      $form = drupal_get_form('breakpoints_admin_breakpoint_export_form', $breakpoint);
      break;
  }
  return $form;
}

/**
 * Admin action form submit
 */
function breakpoints_admin_breakpoint_actions_form_submit($form, &$form_state) {
  $group_name = $form_state['group_name'];
  $action = $form_state['action'];
  $breakpoint = $form_state['breakpoint'];
  switch ($action) {
    case 'delete':
      breakpoints_breakpoint_delete_by_fullkey($breakpoint);
      break;
    case 'enable':
    case 'disable':
      breakpoints_breakpoint_toggle_status($breakpoint);
      break;
  }
  if (!empty($group_name)) {
    $form_state['redirect'] = 'admin/config/media/breakpoints/groups/' . $group_name;
  }
  else {
    $form_state['redirect'] = 'admin/config/media/breakpoints';
  }
}

function breakpoints_add_style_form($form, &$form_state) {
  module_load_include('inc', 'image', 'image.admin');
  $form['style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => array_filter(image_style_options(FALSE), '_breakpoints_filter_styles'),
    '#required' => TRUE,
    '#description' => t('This image style will be cloned to create the responsive style'),
  );

  $form['base_name'] = array(
    '#type' => 'textfield',
    '#size' => '64',
    '#title' => t('Image style base name'),
    '#description' => t('The name is used in URLs for generated images. Use only lowercase alphanumeric characters, underscores (_), and hyphens (-).'),
    '#element_validate' => array('image_style_name_validate'),
    '#required' => TRUE,
  );
  $breakpoints = breakpoints_breakpoint_load_all_active();
  if (isset($breakpoints) && !empty($breakpoints)) {
    $options = array();
    foreach ($breakpoints as $breakpoint) {
      foreach ($breakpoint->multipliers as $multiplier) {
        $options[str_replace('.', '_', $breakpoint->machine_name . '_' . $multiplier)] = $breakpoint->name . ' [' . $breakpoint->breakpoint . ', multiplier:' . $multiplier . ']';
      }
    }
    $form['breakpoints'] = array(
      '#title' => t('breakpoints'),
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => drupal_map_assoc(array_keys($options)),
      '#description' => t('Select the breakpoints to create an image style for'),
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create'),
    );
  }
  else {
    $form['redirect_link'] = array(
      '#markup' => t("You need to create a breakpoint first before creating a responsive style. ") . l('Click here', 'admin/config/media/breakpoints') . t(" to continue with configuring breakpoints."),
    );
  }
  return $form;
}

function breakpoints_add_style_form_validate($form, &$form_state) {
  foreach (array_filter($form_state['values']['breakpoints']) as $breakpoint) {
    if (image_style_load($form_state['values']['base_name'] . $breakpoint)) {
      form_set_error('breakpoints', t('An image style with the name !name already exists', array('!name' => $form_state['values']['base_name'] . $breakpoint)));
    }
  }
}

function breakpoints_add_style_form_submit($form, &$form_state) {
  $base = image_style_load($form_state['values']['style']);
  if (!isset($base['effects'])) {
    $base['effects'] = array();
  }
  foreach (array_filter($form_state['values']['breakpoints']) as $breakpoint) {
    $new_style = array(
      'name' => $form_state['values']['base_name'] . $breakpoint,
    );
    $style = image_style_save($new_style);
    if ($style) {
      foreach ($base['effects'] as $effect) {
        $effect['isid'] = $style['isid'];
        unset($effect['ieid']);
        image_effect_save($effect);
      }
    }
  }
  $form_state['redirect'] = 'admin/config/media/image-styles';
  drupal_set_message(t('The new styles have been created'));
}

function breakpoints_admin_breakpoint_group_edit_form($form, &$form_state, $machine_name = '') {
  $form = array();
  $group = breakpoints_breakpoint_group_load($machine_name);
  $breakpoints = breakpoints_breakpoint_load_all();
  if (empty($breakpoints)) {
    return breakpoints_admin_breakpoint_group_edit_form_no_breakpoints();
  }

  $form_state['#breakpoint_group'] = $group;
  $is_new = $machine_name == '';
  $form_state['#is_new'] = $is_new;

  $form['name'] = array(
    '#type' => 'textfield',
    '#size' => '64',
    '#title' => t('group name'),
    '#required' => TRUE,
    '#default_value' => isset($group->name) ? $group->name : '',
    '#disabled' => !$is_new,
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#size' => '64',
    '#title' => t('Machine name'),
    '#required' => TRUE,
    '#default_value' => isset($group->machine_name) ? $group->machine_name : '',
    '#disabled' => !$is_new,
    '#machine_name' => array(
      'exists' => 'breakpoints_breakpoint_group_name_exists',
    ),
  );

  foreach ($breakpoints as $breakpoint_name => $breakpoint) {
    $options[$breakpoint_name] = $breakpoint->name . ' [' . $breakpoint->breakpoint . ']';
  }

  $form['breakpoints'] = array(
    '#title' => 'Select the breakpoints you want to use in this group',
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => isset($group->breakpoints) ? drupal_map_assoc($group->breakpoints) : array(),
    '#required' => TRUE,
  );

  // Buttons
  $form['buttons'] = array(
    '#type' => 'container',
  );

  // Submit button
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  if (!$is_new && $group->type == BREAKPOINTS_SOURCE_TYPE_CUSTOM) {
    $form['buttons']['deletelink'] = array(
      '#type' => 'markup',
      '#markup' => l(t('Delete this group'), 'admin/config/media/breakpoints/groups/' . $group->machine_name . '/delete', array(
        'query' => drupal_get_destination(),
      )),
    );
  }

  return $form;
}

function breakpoints_admin_breakpoint_group_edit_form_no_breakpoints() {
  $form = array();

  $form['info'] = array(
    '#type' => 'markup',
    '#markup' => t("There're no breakpoints defined, you'll have to !create them first.", array('!create' => l(t('create'), 'admin/config/media/breakpoints'))),
  );

  return $form;
}

function breakpoints_admin_breakpoint_group_edit_form_validate($form, &$form_state) {
  $name = $form_state['values']['machine_name'];
  $label = $form_state['values']['name'];
}

function breakpoints_admin_breakpoint_group_edit_form_submit($form, &$form_state) {
  $machine_name = $form_state['values']['machine_name'];
  $name = $form_state['values']['name'];
  $breakpoints = array();
  foreach ($form_state['values']['breakpoints'] as $breakpoint => $status) {
    if ($status) {
      $breakpoints[] = $breakpoint;
    }
  }
  $is_new = $form_state['#is_new'];

  if ($is_new) {
    $new_group = breakpoints_breakpoint_group_empty_object();
    $new_group->machine_name = $machine_name;
    $new_group->name = $name;
    $new_group->type = BREAKPOINTS_SOURCE_TYPE_CUSTOM;
    $new_group->breakpoints = $breakpoints;
    breakpoints_breakpoint_group_save($new_group);
    menu_rebuild();
    $form_state['redirect'] = 'admin/config/media/breakpoints/groups/' . $machine_name;
    drupal_set_message(t('The new group have been created'));
  }
  else {
    $existing_group = breakpoints_breakpoint_group_load($machine_name);
    $existing_group->breakpoints = $breakpoints;
    breakpoints_breakpoint_group_save($existing_group);
  }
}

/**
 * Delete a group.
 */
function breakpoints_admin_breakpoint_group_delete_form($form, &$form_state, $machine_name) {
  $group = breakpoints_breakpoint_group_load($machine_name);
  $form_state['machine_name'] = $machine_name;
  $question = t('Are you sure you want to delete %group', array(
        '%group' => $group->name,
      ));
  $path = 'admin/config/media/breakpoints/groups';
  return confirm_form($form, $question, $path, '');
}

/**
 * Delete a group.
 */
function breakpoints_admin_breakpoint_group_delete_form_submit($form, &$form_state) {
  $machine_name = $form_state['machine_name'];
  breakpoints_breakpoint_group_delete_by_name($machine_name);
  menu_rebuild();
  $form_state['redirect'] = 'admin/config/media/breakpoints';
}

/**
 * Export a group.
 */
function breakpoints_admin_breakpoint_group_export_form($form, &$form_state, $machine_name) {
  // Create the export code textarea.
  ctools_include('export');
  $group = breakpoints_breakpoint_group_load($machine_name);
  if (!$group || !$machine_name) {
    $group = new stdClass();
  }
  $group_export = breakpoints_breakpoint_group_export($group);

  $form['group_export'] = array(
    '#type' => 'textarea',
    '#title' => t('Breakpoint group code'),
    '#rows' => count(explode("\n", $group_export)),
    '#default_value' => $group_export,
  );

  $breakpoints_export = NULL;
  if (isset($group->breakpoints)) {
    foreach ($group->breakpoints as $breakpoint) {
      if (!is_array($breakpoint) && !is_object($breakpoint)) {
        $breakpoint = breakpoints_breakpoint_load_by_fullkey($breakpoint);
      }
      $breakpoints_export .= ctools_export_object('breakpoints', $breakpoint);
      $breakpoints_export .= "\n";
    }
  }

  $form['breakpoints_export'] = array(
    '#type' => 'textarea',
    '#title' => t('Breakpoints code'),
    '#rows' => count(explode("\n", $breakpoints_export)),
    '#default_value' => $breakpoints_export,
  );

  return $form;
}

/**
 * Import a breakpoint group.
 */
function breakpoints_admin_breakpoint_group_import_form($form, &$form_state) {
  $form['import'] = array(
    '#type' => 'textarea',
    '#rows' => 10,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import')
  );
  return $form;
}

/**
 * Validate a breakpoint group import.
 */
function breakpoints_admin_breakpoint_group_import_form_validate($form, &$form_state) {
  ctools_include('export');
  $code = $form_state['values']['import'];
  $group = ctools_export_crud_import('breakpoint_group', $code);
  if (!breakpoints_breakpoint_group_validate($group)) {
    form_set_error('import', t('Not a valid group object'));
    return;
  }
  if (breakpoints_breakpoint_group_name_exists($group->machine_name)) {
    form_set_error('import', t('A group with machine name %name already exists', array('%name' => $group->machine_name)));
    return;
  }
  foreach ($group->breakpoints as $key => $breakpoint) {
    // check if the breakpoint is a fully loaded object.
    if (is_array($breakpoint) || is_object($breakpoint)) {
      if (!breakpoints_breakpoint_validate($breakpoint)) {
        form_set_error('import',  t('The breakpoint group contains an invalid breakpoint.'));
        return;
      }
    }
  }
  // Manually imported groups are the same as custom made groups.
  $group->type = BREAKPOINTS_SOURCE_TYPE_CUSTOM;
  form_set_value($form['import'], $group, $form_state);
}

/**
 * Import breakpoint group.
 */
function breakpoints_admin_breakpoint_group_import_form_submit($form, &$form_state) {
  $group = $form_state['values']['import'];

  foreach ($group->breakpoints as $key => $breakpoint) {
    // check if the breakpoint is a fully loaded object.
    if (is_array($breakpoint) || is_object($breakpoint)) {
      $breakpoint = (object)$breakpoint;
      // If the breakpoints exist, only overwrite the custom ones.
      if ($existing_breakpoint = breakpoints_breakpoint_load_by_fullkey($breakpoint->machine_name)) {
        if ($breakpoint->source_type == BREAKPOINTS_SOURCE_TYPE_CUSTOM) {
          $breakpoint = (object)array_merge((array)$existing_breakpoint, (array)$breakpoint);
          breakpoints_breakpoint_save($breakpoint);
        }
      }
      else {
        breakpoints_breakpoint_save($breakpoint);
      }
      $group->breakpoints[$key] = $breakpoint->machine_name;
    }
  }
  if (breakpoints_breakpoint_group_save($group)) {
    drupal_set_message(t('Group %group saved.', array('%group' => $group->name)));
    $form_state['redirect'] = 'admin/config/media/breakpoints/groups/' . $group->machine_name;
  }
  else {
    drupal_set_message(t('Something went wrong, we could not save the group', 'error'));
  }
}

/**
 * Export a breakpoint.
 */
function breakpoints_admin_breakpoint_export_form($form, $form_state, $fullkey) {
  // Create the export code textarea.
  ctools_include('export');
  $breakpoint = breakpoints_breakpoint_load_by_fullkey($fullkey);
  if (!$breakpoint) {
    $breakpoint = new stdClass();
  }
  $export = ctools_export_object('breakpoints', $breakpoint);

  $form['export'] = array(
    '#type' => 'textarea',
    '#title' => t('Breakpoint code'),
    '#rows' => 20,
    '#default_value' => $export,
  );
  return $form;
}

/**
 * Import breakpoint.
 */
function breakpoints_admin_breakpoint_import_form($form, $form_state) {
  $form['import'] = array(
    '#type' => 'textarea',
    '#rows' => 10,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import')
  );
  return $form;
}

/**
 * Validate a breakpoint import.
 */
function breakpoints_admin_breakpoint_import_form_validate($form, &$form_state) {
  ctools_include('export');
  $code = $form_state['values']['import'];
  $breakpoint = ctools_export_crud_import('breakpoints', $code);
  if (!breakpoints_breakpoint_validate($breakpoint)) {
    form_set_error('import', t('Not a valid breakpoint object'));
  }
  else {
    if (breakpoints_breakpoint_machine_name_exists($breakpoint->machine_name)) {
      form_set_error('import', t('A breakpoint with machine name %name already exists', array('%name' => $breakpoint->machine_name)));
    }
    else {
      form_set_value($form['import'], $breakpoint, $form_state);
    }
  }
}

/**
 * Import breakpoint.
 */
function breakpoints_admin_breakpoint_import_form_submit($form, &$form_state) {
  $breakpoint = $form_state['values']['import'];
  if (breakpoints_breakpoint_save($breakpoint)) {
    drupal_set_message(t('Breakpoint %breakpoint saved.', array('%breakpoint' => $breakpoint->name)));
    $form_state['redirect'] = 'admin/config/media/breakpoints/';
  }
  else {
    drupal_set_message(t('Something went wrong, we could not save the breakpoint'), 'error');
  }
}

/**
 * Multipliers administration form.
 */
function breakpoints_multipliers_form($form, &$form_state) {
  $settings = breakpoints_settings();
  $multipliers = drupal_map_assoc($settings->multipliers);
  if (isset($multipliers['1x'])) {
    unset($multipliers['1x']);
  }
  $form['multipliers'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#theme' => 'breakpoints_multipliers_table_form',
  );
  $form['multipliers']['1x'] = array(
    '#markup' => '1x',
  );
  foreach ($multipliers as $multiplier) {
    $form['multipliers'][$multiplier] = array(
      '#type' => 'textfield',
      '#title' => '',
      '#required' => FALSE,
      '#default_value' => $multiplier,
    );
  }
  $form['multipliers']['new'] = array(
    '#type' => 'textfield',
    '#title' => '',
    '#required' => FALSE,
    '#default_value' => '',
    '#description' => t('Multiplier like 1.5x, 2x.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function theme_breakpoints_multipliers_table_form($element) {
  $form = $element['form'];
  $header = array(t('Label'), t('Operations'));
  foreach (element_children($form) as $multiplier) {
    $row = array();
    $row[] = drupal_render($form[$multiplier]);
    $row[] = in_array($multiplier, array('new', '1x')) ? '' : l(t('Delete'), 'admin/config/media/breakpoints/multipliers/' . $multiplier . '/delete');
    $rows[] = $row;
  }
  return theme('table', array('header' => $header, 'rows' => $rows));
}

function breakpoints_multipliers_form_validate($form, $form_state) {
  $multipliers = $form_state['values']['multipliers'];
  $saved_multipliers = array(
    '1x' => '1x',
  );
  foreach ($multipliers as $form_key => $multiplier) {
    if ($multiplier == '' && $form_key != 'new') {
      form_set_error('multipliers][' . $form_key, t('Label is required.'));
    }
    if ($multiplier != '') {
      if (isset($saved_multipliers[$multiplier])) {
        form_set_error('multipliers][' . $form_key, t('Label must be unique.'));
      }
      $saved_multipliers[$multiplier] = $multiplier;
    }
  }
}

function breakpoints_multipliers_form_submit($form, &$form_state) {
  $multipliers = array_values(array_filter($form_state['values']['multipliers']));
  array_unshift($multipliers, '1x');
  breakpoints_settings_save($multipliers);
  drupal_set_message(t('Multiplier settings are saved.'));
}

function breakpoints_admin_multiplier_delete_form($form, &$form_state, $multiplier) {
  $path = 'admin/config/media/breakpoints/multipliers';
  if ($multiplier == '1x') {
    $form['multiplier'] = array(
      '#markup' => t('Multiplier %multiplier can not be deleted! !link', array('%multiplier' => $multiplier, '!link' => l(t('Back to overview page.'), $path)))
    );
    return $form;
  }
  $form['multiplier'] = array(
    '#type' => 'value',
    '#value' => $multiplier,
  );
  return confirm_form($form, t('Are you sure you want to delete multiplier %multiplier', array('%multiplier' => $multiplier)), $path);
}

function breakpoints_admin_multiplier_delete_form_submit($form, &$form_state) {
  $settings = breakpoints_settings();
  $multiplier = $form_state['values']['multiplier'];
  $multipliers = drupal_map_assoc($settings->multipliers);
  if (isset($multipliers[$multiplier])) {
    unset($multipliers[$multiplier]);
  }
  breakpoints_settings_save(array_values($multipliers));
  drupal_set_message(t('Multiplier %multiplier was deleted', array('%multiplier' => $multiplier)));
  $form_state['redirect'] = 'admin/config/media/breakpoints/multipliers';
}

function breakpoints_admin_settings_form($form, &$form_state) {
  $form['breakpoints_hide_overridden_breakpoints'] = array(
    '#type' => 'checkbox',
    '#description' => t('When overriding breakpoints defined by a theme, hide them on the overview page'),
    '#title' => t('Hide overridden breakpoints'),
    '#default_value' => variable_get('breakpoints_hide_overridden_breakpoints', 1),
  );
  return system_settings_form($form);
}

/**
 * Duplicate group form.
 */
function breakpoints_admin_breakpoint_group_duplicate_form($form, &$form_state, $breakpoint_group_name) {
  $form = array();

  $src_group = breakpoints_breakpoint_group_load($breakpoint_group_name);
  $form_state['#src_group'] = $src_group;

  $form['#attached']['css'][] = drupal_get_path('module', 'breakpoints') . '/css/breakpoints.admin.css';
  $form['name'] = array(
    '#type' => 'textfield',
    '#size' => '64',
    '#title' => t('New group name'),
    '#required' => TRUE,
    '#default_value' => t('Duplicate of') . ' ' . $src_group->name,
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#size' => '64',
    '#title' => t('Machine name'),
    '#required' => TRUE,
    '#default_value' => '',
    '#machine_name' => array(
      'exists' => 'breakpoints_breakpoint_group_name_exists',
    ),
  );

  // Buttons
  $form['buttons'] = array(
    '#type' => 'container',
  );

  // Submit button
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['buttons']['cancellink'] = array(
    '#type' => 'markup',
    '#markup' => l(
      t('Cancel'), 'admin/config/media/breakpoints/groups/' . $src_group->machine_name,
      array(
        'attributes' => array('class' => array('breakpoints-group-operations-link', 'breakpoints-group-operations-cancel-link')),
      )
    ),
  );

  return $form;
}

/**
 * Duplicate group form validate.
 */
function breakpoints_admin_breakpoint_group_duplicate_form_validate($form, &$form_state) {
}

/**
 * Duplicate group form submit.
 */
function breakpoints_admin_breakpoint_group_duplicate_form_submit($form, &$form_state) {
  $machine_name = $form_state['values']['machine_name'];
  $name = $form_state['values']['name'];
  $src_group = $form_state['#src_group'];
  if ($src_group) {
    breakpoints_breakpoints_group_duplicate($src_group, $name, $machine_name);
    // Clear the Ctools export API cache.
    ctools_include('export');
    ctools_export_load_object_reset('breakpoint_group');
    menu_rebuild();
    $form_state['redirect'] = 'admin/config/media/breakpoints/groups/' . $machine_name;
    drupal_set_message(t('The new group have been created'));
  }
}
