<?php

/**
 * @file
 * Theme function that overrides the default for roles page.
 */

/**
 * Returns HTML for the role order and new role form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_role_export_user_admin_roles($variables) {
  $form = $variables['form'];

  $header = array(t('Name'), t('Machine name'), t('Weight'), array('data' => t('Operations'), 'colspan' => 2));
  foreach (element_children($form['roles']) as $rid) {
    $name = $form['roles'][$rid]['#role']->name;
    $machine_name = $form['roles'][$rid]['#role']->machine_name;
    $row = array();
    if (in_array($rid, array(DRUPAL_ANONYMOUS_RID, DRUPAL_AUTHENTICATED_RID))) {
      $row[] = t('@name <em>(locked)</em>', array('@name' => $name));
      $row[] = '';
      $row[] = drupal_render($form['roles'][$rid]['weight']);
      $row[] = '';
      $row[] = l(t('edit permissions'), 'admin/people/permissions/' . $rid);
    }
    else {
      $row[] = check_plain($name);
      $row[] = check_plain($machine_name);
      $row[] = drupal_render($form['roles'][$rid]['weight']);
      $row[] = l(t('edit role'), 'admin/people/permissions/roles/edit/' . $rid);
      $row[] = l(t('edit permissions'), 'admin/people/permissions/' . $rid);
    }
    $rows[] = array('data' => $row, 'class' => array('draggable'));
  }
  $rows[] = array(array('data' => drupal_render($form['name']) . drupal_render($form['machine_name']) . drupal_render($form['add']), 'colspan' => 5, 'class' => 'edit-name'));

  drupal_add_tabledrag('user-roles', 'order', 'sibling', 'role-weight');

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'user-roles')));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Form validation handler for user_admin_roles form.
 *
 * Checks that the machine name is not empty if the role name is not empty.
 */
function role_export_roles_form_validate($form, &$form_state) {
  if (!empty($form_state['values']['name']) && empty($form_state['values']['machine_name'])) {
    form_set_error('machine_name', t('Machine-readable name field is required.'));
  }
}
