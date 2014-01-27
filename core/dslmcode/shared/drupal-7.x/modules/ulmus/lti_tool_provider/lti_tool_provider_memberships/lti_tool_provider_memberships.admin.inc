<?php

/**
 * @file
 * Admin forms and menu page callbacks for LTI Tool Provider Memberships module.
 */

/**
 * Admin form for the subgroup mapping.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_memberships_subgroup_mapping($form, &$form_state) {
  $form = array();
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Configure LTI Memberships groups.'),
    '#weight' => -8,
  );
  $form['subgroups'] = array(
    '#type' => 'checkbox',
    '#title' => t('Request LTI Memberships groups details from consumer.'),
    '#default_value' => isset($form_state['values']['subgroups']) ? $form_state['values']['subgroups'] : variable_get('lti_tool_provider_memberships_subgroups'),
    '#weight' => -7,
    '#ajax' => array(
      'callback' => 'lti_tool_provider_memberships_subgroups_checkbox_callback',
      'wrapper' => 'subgroups-detail',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['subgroups-detail'] = array(
    '#prefix' => '<div id="subgroups-detail">',
    '#suffix' => '</div>',
    '#weight' => -6,
  );
  if (!empty($form['subgroups']['#default_value']) && $form['subgroups']['#default_value'] != 0) {
    $new_bundles = lti_tool_provider_memberships_get_group_bundles();
    $old_bundle = variable_get('lti_tool_provider_memberships_subgroup_mapping_bundle');
    $form['subgroups-detail']['bundle'] = array(
      '#type' => 'select',
      '#title' => t('LTI Memberships groups to Drupal subgroup mapping'),
      '#description' => t('Optionally select the Drupal OG subgroup bundle corresponding to an LTI memberships group. These groups will be provisioned as needed.'),
      '#options' => $new_bundles,
      '#weight' => -5,
      '#ajax' => array(
        'callback' => 'lti_tool_provider_memberships_subgroups_checkbox_callback',
        'wrapper' => 'subgroups-detail',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );
    $form['subgroups-detail']['bundle']['#default_value'] = isset($form_state['values']['bundle']) ? $form_state['values']['bundle'] : $old_bundle;
    if (!empty($form['subgroups-detail']['bundle']['#default_value']) && $form['subgroups-detail']['bundle']['#default_value'] != 'none:None') {
      // Attribute Mapping.
      $form['subgroups-detail']['mapping_description'] = array(
        '#type' => 'item',
        '#title' => t('Subgroup attribute mapping'),
        '#description' => t('Choose the subgroup attributes to be mapped from the LTI Memberships group variables. Note: Title and group_id must be mapped but not necessarily to each other, and the LTI context group reference must also be mapped to an entityreference field.'),
        '#weight' => -4,
      );
      $saved_settings = variable_get('lti_tool_provider_memberships_subgroup_mapping', array());
      $form['subgroups-detail']['mapping'] = array(
        '#tree' => TRUE,
        '#theme' => 'table',
        '#header' => array(t('LTI Memberships Group Variable'), t('Drupal Subgroup Attribute')),
        '#rows' => array(),
        '#weight' => -3,
      );
      foreach (lti_tool_provider_memberships_subgroup_mapping_details() as $key => $detail) {
        if (($form['subgroups']['#default_value'] == 0) && ($detail != 'group_id')) {
          unset($form_state['values']['mapping'][$key]);
        }
        else {
          $variable = array(
            '#type' => 'item',
            '#title' => check_plain($detail),
          );
          $attribute = array(
            '#type' => 'select',
            '#options' => ($detail == 'LTI context group reference') ?
              lti_tool_provider_memberships_retrieve_entity_field_types($form['subgroups-detail']['bundle']['#default_value']) :
              lti_tool_provider_og_retrieve_entity_field_types($form['subgroups-detail']['bundle']['#default_value']),
          );
          if (isset($form_state['values'][$detail])) {
            $attribute['#default_value'] = $form_state['values'][$detail];
          }
          else {
            $attribute['#default_value'] = isset($saved_settings[$detail]) ? $saved_settings[$detail] : 0;
          }
          $form['subgroups-detail']['mapping'][] = array(
            'variable' => &$variable,
            'attribute' => &$attribute,
          );
          $form['subgroups-detail']['mapping']['#rows'][] = array(
            array('data' => &$variable),
            array('data' => &$attribute),
          );
          unset($variable);
          unset($attribute);
        }
      }
      $form['subgroups-detail']['roles_description'] = array(
        '#type' => 'item',
        '#title' => t('LTI Memberships group role mapping'),
        '#description' => t('Choose the subgroup roles to be mapped from the LTI roles.'),
        '#weight' => -2,
      );
      list($entity, $bundle) = explode(':', $form['subgroups-detail']['bundle']['#default_value']);
      $select_roles = og_roles($entity, $bundle);
      // Remove OG_ANONYMOUS_ROLE in $select_roles.
      if (($key = array_search(OG_ANONYMOUS_ROLE, $select_roles)) !== FALSE) {
        unset($select_roles[$key]);
      }
      $old_bundle = variable_get('lti_tool_provider_memberships_subgroup_mapping_bundle');
      if ($old_bundle == $form['subgroups-detail']['bundle']['#default_value']) {
        $old_role_array = variable_get('lti_tool_provider_memberships_subgroup_role_array');
      }
      // Role Mapping.
      $form['subgroups-detail']['roles'] = array(
        '#tree' => TRUE,
        '#theme' => 'table',
        '#header' => array(t('LTI Roles'), t('Subgroup Roles')),
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
        $form['subgroups-detail']['roles'][] = array(
          'lti_role' => &$lti_role,
          'group_role' => &$group_role,
        );
        $form['subgroups-detail']['roles']['#rows'][] = array(
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
    '#value' => t('Save Subgroup Mapping'),
    '#submit' => array('lti_tool_provider_memberships_subgroup_mapping_submit'),
    '#weight' => 10,
  );
  return $form;
}

/**
 * AJAX callback for the subgroup mapping form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_memberships_subgroups_checkbox_callback($form, &$form_state) {
  return $form['subgroups-detail'];
}

/**
 * Validation callback.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_memberships_subgroup_mapping_validate($form, &$form_state) {
  if ($form_state['values']['subgroups'] == 0 || !isset($form_state['values']['bundle'])) {
    return;
  }
  $entity_bundle = $form_state['values']['bundle'];
  list($entity, $bundle) = explode(':', $entity_bundle);
  if ($entity == 'none') {
    return;
  }
  $check_isset_title = FALSE;
  $check_isset_group_id = FALSE;
  $check_isset_context_ref = FALSE;
  $check_repeat = FALSE;
  $fields = lti_tool_provider_og_retrieve_entity_field_types($entity_bundle);
  $counters = array();
  foreach (lti_tool_provider_memberships_subgroup_mapping_details() as $key => $detail) {
    if (isset($form_state['values']['mapping'][$key]['attribute'])) {
      if ($form_state['input']['mapping'][$key]['attribute'] == 'title') {
        $check_isset_title = TRUE;
      }
      if ($detail == 'group_id' && $form_state['input']['mapping'][$key]['attribute'] != 'none') {
        $check_isset_group_id = TRUE;
      }
      if ($detail == 'LTI context group reference' && $form_state['input']['mapping'][$key]['attribute'] != 'none') {
        $check_isset_context_ref = TRUE;
      }
      $value = $form_state['input']['mapping'][$key]['attribute'];
      if (isset($counters[$value])) {
        $counters[$value]++;
      }
      else {
        $counters[$value] = 1;
      }
    }
  }
  foreach ($counters as $counter => $count) {
    if ($counter != 'none' && $count > 1) {
      $check_repeat = TRUE;
      break;
    }
  }
  if (!$check_isset_group_id) {
    form_set_error('mapping][0', t('You must map group_id variable to a field.'));
  }
  if (!$check_isset_context_ref) {
    form_set_error('mapping][2', t('You must map LTI context group reference to an entityreference field.'));
  }
  if ($check_repeat) {
    form_set_error('mapping', t('You may not map more than one variable to the same field.'));
  }
  if ($entity == 'node' && isset($form_state['values']['subgroups']) && $form_state['values']['subgroups'] == 1 && !$check_isset_title) {
    form_set_error('mapping', t('Title must be mapped from one of group_id or title.'));
  }
  return;
}

/**
 * Submit handler for subgroup mapping form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function lti_tool_provider_memberships_subgroup_mapping_submit($form, &$form_state) {
  variable_set('lti_tool_provider_memberships_subgroups', $form_state['values']['subgroups']);
  if ($form_state['values']['subgroups']) {
    variable_set('lti_tool_provider_memberships_subgroup_mapping_bundle', $form_state['values']['bundle']);
    if ($form_state['values']['bundle'] != 'none:None') {
      $settings = array();
      foreach (lti_tool_provider_memberships_subgroup_mapping_details() as $key => $detail) {
        if (isset($form_state['input']['mapping'][$key]['attribute'])) {
          $settings[$detail] = $form_state['input']['mapping'][$key]['attribute'];
        }
      }
      variable_set('lti_tool_provider_memberships_subgroup_mapping', $settings);
      $group_roles = array();
      foreach (lti_tool_provider_get_lti_roles() as $key => $role) {
        $group_roles[$role] = $form_state['input']['roles'][$key]['group_role'];
      }
      variable_set('lti_tool_provider_memberships_subgroup_role_array', $group_roles);
    }
  }
  drupal_set_message(t('LTI group mapping saved.'));
}

/**
 * Create an options array for a select list of node group bundles.
 *
 * @return array
 *   An options array of group bundles.
 */
function lti_tool_provider_memberships_get_group_bundles() {
  // Add none:None and set the entity types as the first key
  // in the bundle array.
  $bundles = og_get_all_group_bundle();
  $new_bundles = array();
  $new_bundles['none']['none:None'] = t('None');
  foreach ($bundles as $entity => $bundle) {
    if ($entity == 'node') {
      foreach ($bundle as $key => $value) {
        $new_bundles[$entity][$entity . ':' . $key] = $value;
      }
    }
  }
  return $new_bundles;
}

/**
 * Get the LTI variables relating to the context.
 *
 * @return array
 *   An array containing the variable names.
 */
function lti_tool_provider_memberships_subgroup_mapping_details() {
  return array(
    'group_id',
    'title',
    'LTI context group reference',
  );
}

/**
 * Retrieve the field labels and types from the entity.
 *
 * Return as an array suitable for a select list.
 *
 * @param string $group_bundle
 *   The string of the form "entity:bundle".
 *
 * @return array
 *   An array containing all the retrieved fields prepended with an entry
 *   for none, and if the entity type is node, an entry for Title.
 */
function lti_tool_provider_memberships_retrieve_entity_field_types($group_bundle) {
  list($entity, $bundle) = explode(':', $group_bundle);
  $fields = field_info_instances($entity, $bundle);
  $result = array('none' => t('None'));
  foreach ($fields as $field) {
    $info = field_info_field($field['field_name']);
    if ($info['type'] == 'entityreference') {
      $result[$field['field_name']] = $field['label'] . ' (' . $field['field_name'] . ')';
    }
  }
  return $result;
}
