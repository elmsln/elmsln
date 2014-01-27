<?php

/**
 * @file
 * Admin forms and menu page callbacks for LTI Tool Provider OG module.
 */

/**
 * Admin form for the group mapping.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_og_group_mapping($form, &$form_state) {
  $form = array();
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Choose a group bundle, configure LTI context variable to group attribute mapping and group role mapping.'),
    '#weight' => -9,
  );
  $new_bundles = lti_tool_provider_og_get_group_bundles();
  $old_bundle = variable_get('lti_tool_provider_og_group_mapping_bundle');
  $form['bundle'] = array(
    '#type' => 'select',
    '#title' => t('LTI Context to Drupal group mapping'),
    '#description' => t('Please select the Drupal group bundle corresponding to an LTI course.'),
    '#options' => $new_bundles,
    '#weight' => -8,
    '#ajax' => array(
      'callback' => 'lti_tool_provider_og_group_mapping_select_callback',
      'wrapper' => 'group-detail',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  // The group_detail section of the form is ajax reloaded when the bundle
  // or the creat_course checkbox changes.
  $form['bundle']['#default_value'] = isset($form_state['values']['bundle']) ? $form_state['values']['bundle'] : $old_bundle;
  $parts = explode(':', $form['bundle']['#default_value']);
  $is_node_type = (reset($parts) == 'node') ? TRUE : FALSE;
  $form['group_detail'] = array(
    '#prefix' => '<div id="group-detail">',
    '#suffix' => '</div>',
    '#weight' => -7,
  );
  if (!empty($form['bundle']['#default_value']) && $form['bundle']['#default_value'] != 'none:None') {
    if ($is_node_type) {
      $form['group_detail']['create_course'] = array(
        '#type' => 'checkbox',
        '#title' => t('Automatically create groups. Note: Only available for node group bundles and LTI user must have appropriate "Create content type" permission.'),
        '#default_value' => isset($form_state['values']['create_course']) ? $form_state['values']['create_course'] : variable_get('lti_tool_provider_og_provision_groups'),
        '#weight' => -6,
        '#ajax' => array(
          'callback' => 'lti_tool_provider_og_group_mapping_select_callback',
          'wrapper' => 'group-detail',
          'method' => 'replace',
          'effect' => 'fade',
        ),
      );
      if ($form['group_detail']['create_course']['#default_value'] == 1) {
        $form['group_detail']['create_course_anon'] = array(
          '#type' => 'checkbox',
          '#title' => t('Create groups with anon rather than LTI user. Note: LTI user does NOT need "Create content type" permission.'),
          '#default_value' => isset($form_state['values']['create_course_anon']) ? $form_state['values']['create_course_anon'] : variable_get('lti_tool_provider_og_provision_groups_anon'),
          '#weight' => -5,
        );
      }
    }
    $form['group_detail']['mapping_description'] = array(
      '#prefix' => '<div id="select-mapping-div">',
      '#suffix' => '</div>',
      '#type' => 'item',
      '#title' => t('LTI group attribute mapping'),
      '#description' => t('Choose the group attributes to be mapped from the LTI context variables. Note: Title and context_id must be mapped but not necessarily to each other.'),
      '#weight' => -4,
    );
    if ($is_node_type && $form['group_detail']['create_course']['#default_value'] == 0) {
      $form['group_detail']['mapping_description']['#description'] = 'Choose the group attribute to be mapped from the LTI context_id.';
    }
    $saved_settings = variable_get('lti_tool_provider_og_group_mapping', array());
    $form['group_detail']['mapping'] = array(
      '#tree' => TRUE,
      '#theme' => 'table',
      '#header' => array(t('LTI Context Variable'), t('Group Attribute')),
      '#rows' => array(),
      '#weight' => -1,
    );
    foreach (lti_tool_provider_context_mapping_details() as $key => $detail) {
      if ((!$is_node_type || $form['group_detail']['create_course']['#default_value'] == 0) && ($detail != 'context_id')) {
        unset($form_state['values']['mapping'][$key]);
      }
      else {
        $variable = array(
          '#type' => 'item',
          '#title' => check_plain($detail),
        );
        $attribute = array(
          '#type' => 'select',
          '#options' => lti_tool_provider_og_retrieve_entity_field_types($form['bundle']['#default_value']),
        );
        if (isset($form_state['values'][$detail])) {
          $attribute['#default_value'] = $form_state['values'][$detail];
        }
        else {
          $attribute['#default_value'] = isset($saved_settings[$detail]) ? $saved_settings[$detail] : 0;
        }
        $form['group_detail']['mapping'][] = array(
          'variable' => &$variable,
          'attribute' => &$attribute,
        );
        $form['group_detail']['mapping']['#rows'][] = array(
          array('data' => &$variable),
          array('data' => &$attribute),
        );
        unset($variable);
        unset($attribute);
      }
    }
    $form['group_detail']['mapping']['#weight'] = -3;
    if ($form['bundle']['#default_value'] != 'none:None') {
      $form['group_detail']['roles_description'] = array(
        '#type' => 'item',
        '#title' => t('LTI group role mapping'),
        '#description' => t('Choose the group roles to be mapped from the LTI roles.'),
        '#weight' => -2,
      );
      list($entity, $bundle) = explode(':', $form['bundle']['#default_value']);
      $select_roles = og_roles($entity, $bundle);
      // Remove OG_ANONYMOUS_ROLE in $select_roles.
      if (($key = array_search(OG_ANONYMOUS_ROLE, $select_roles)) !== FALSE) {
        unset($select_roles[$key]);
      }
      $old_bundle = variable_get('lti_tool_provider_og_group_mapping_bundle');
      if ($old_bundle == $form['bundle']['#default_value']) {
        $old_role_array = variable_get('lti_tool_provider_og_group_role_array');
      }

      $form['group_detail']['roles'] = array(
        '#tree' => TRUE,
        '#theme' => 'table',
        '#header' => array(t('LTI Roles'), t('Group Roles')),
        '#rows' => array(),
        '#weight' => -1,
      );
      foreach (lti_tool_provider_get_lti_roles() as $role) {
        $lti_role = array(
          '#type' => 'item',
          '#title' => check_plain($role),
        );
        $group_role = array(
          '#type' => 'select',
          '#options' => $select_roles,
        );
        if (isset($old_role_array[$role]) && isset($select_roles[$old_role_array[$role]])) {
          $group_role['#default_value'] = $old_role_array[$role];
        }
        else {
          $group_role['#default_value'] = array_search(DRUPAL_AUTHENTICATED_RID, $select_roles);
        }
        $form['group_detail']['roles'][] = array(
          'lti_role' => &$lti_role,
          'group_role' => &$group_role,
        );
        $form['group_detail']['roles']['#rows'][] = array(
          array('data' => &$lti_role),
          array('data' => &$group_role),
        );
        unset($lti_role);
        unset($group_role);
      }
    }
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Group Mapping'),
    '#submit' => array('lti_tool_provider_og_group_mapping_submit'),
    '#weight' => 10,
  );
  return $form;
}

/**
 * AJAX callback for the group mapping form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_og_group_mapping_select_callback($form, &$form_state) {
  return $form['group_detail'];
}

/**
 * Validation callback.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_og_group_mapping_validate($form, &$form_state) {
  $entity_bundle = $form_state['values']['bundle'];
  list($entity, $bundle) = explode(':', $entity_bundle);
  if ($entity == 'none') {
    return;
  }
  $check_isset_title = FALSE;
  $check_isset_context_id = FALSE;
  $check_repeat = FALSE;
  $fields = lti_tool_provider_og_retrieve_entity_field_types($entity_bundle);
  $counters = array();
  foreach (lti_tool_provider_context_mapping_details() as $key => $detail) {
    if (isset($form_state['values']['mapping'][$key]['attribute'])) {
      if ($detail != 'context_type' && $form_state['input']['mapping'][$key]['attribute'] == 'title') {
        $check_isset_title = TRUE;
      }
      if ($detail == 'context_id' && $form_state['input']['mapping'][$key]['attribute'] != 'none') {
        $check_isset_context_id = TRUE;
      }
      $value = $form_state['input']['mapping'][$key]['attribute'];
      if (isset($counters[$value])) {
        $counters[$value]++;
      }
      else {
        $counters[$value] = 0;
      }
    }
  }
  foreach ($counters as $counter => $count) {
    if ($counter != 'none' && $count > 1) {
      $check_repeat = TRUE;
      break;
    }
  }
  if (!$check_isset_context_id) {
    form_set_error('group_detail', t('You must map context_id variable to a field.'));
  }
  if ($check_repeat) {
    form_set_error('group_detail', t('You may not map more than one variable to the same field.'));
  }
  if ($entity == 'node' && isset($form_state['values']['create_course']) && $form_state['values']['create_course'] == 1 && !$check_isset_title) {
    form_set_error('group_detail', t('Title must be mapped from one of context_id, context_label or context_title.'));
  }
  return;
}

/**
 * Submit handler for group mapping form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_og_group_mapping_submit($form, &$form_state) {
  variable_set('lti_tool_provider_og_group_mapping_bundle', $form_state['values']['bundle']);
  if ($form_state['values']['bundle'] == 'none:None') {
    variable_set('lti_tool_provider_og_provision_groups', 0);
  }
  else {
    variable_set('lti_tool_provider_og_provision_groups', $form_state['values']['create_course']);
    variable_set('lti_tool_provider_og_provision_groups_anon', $form_state['values']['create_course_anon']);
    $settings = array();
    foreach (lti_tool_provider_context_mapping_details() as $key => $detail) {
      if (isset($form_state['input']['mapping'][$key]['attribute'])) {
        $settings[$detail] = $form_state['input']['mapping'][$key]['attribute'];
      }
    }
    variable_set('lti_tool_provider_og_group_mapping', $settings);
    $group_roles = array();
    foreach (lti_tool_provider_get_lti_roles() as $key => $role) {
      $group_roles[$role] = $form_state['input']['roles'][$key]['group_role'];
    }
    variable_set('lti_tool_provider_og_group_role_array', $group_roles);
  }
  drupal_set_message(t('LTI group mapping saved.'));
}
