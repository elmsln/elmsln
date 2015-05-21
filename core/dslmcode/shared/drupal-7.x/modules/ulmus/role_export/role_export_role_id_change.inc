<?php


/**
 * Implements hook_role_export_role_id_change().
 */
function block_role_export_role_id_change($role, $newrid) {
  // update all blocks that had the old role reference
  $num_updated = db_update('block_role')
  ->fields(array(
    'rid' => $newrid,
  ))
  ->condition('rid', $role->rid, '=')
  ->execute();
  // if we updated anything, report it
  if ($num_updated > 0) {
    drupal_set_message(t('@num blocks were updated so the rid change would be maintained.', array('@num' => $num_updated)), 'status');
  }
}

/**
 * Implements hook_role_export_role_id_change().
 */
function masquerade_role_export_role_id_change($role, $newrid) {
  // change a variable to the new
  $change_made = FALSE;
  $admin_roles = variable_get('masquerade_admin_roles', array());
  foreach ($admin_roles as $key => $status) {
    if ($role->rid == $status) {
      $admin_roles[$newrid] = $newrid;
      unset($admin_roles[$key]);
      $change_made = TRUE;
    }
  }
  // only resave if we made a change
  if ($change_made) {
    drupal_set_message(t('Variable masquerade_admin_roles was updated so the rid change would be maintained.'), 'status');
    variable_set('masquerade_admin_roles', $admin_roles);
  }
}

/**
 * Implements hook_role_export_role_id_change().
 */
function views_role_export_role_id_change($role, $newrid) {
  $views = views_get_all_views();
  foreach ($views as $view) {
    $change_made = FALSE;
    // loop through the displays
    if (!empty($view->display)) {
      foreach ($view->display as &$display) {
        // hunt out an access based on role for the view
        if (isset($display->display_options['access']['role'][$role->rid])) {
          unset($display->display_options['access']['role'][$role->rid]);
          $display->display_options['access']['role'][$newrid] = $newrid;
          $change_made = TRUE;
        }
        // hunt out rid based user filters
        if (isset($display->display_options['filters']['rid']['value'][$role->rid])) {
          unset($display->display_options['filters']['rid']['value'][$role->rid]);
          $display->display_options['filters']['rid']['value'][$newrid] = $newrid;
          $change_made = TRUE;
        }
      }
    }
    // only resave if we made a change
    if ($change_made) {
      drupal_set_message(t('View @hname (@mname) was updated so the rid change would be maintained.', array('@hname' => $view->human_name, '@mname' => $view->name)), 'status');
      views_save_view($view);
    }
  }
}

/**
 * Implements hook_role_export_role_id_change().
 */
function rules_role_export_role_id_change($role, $newrid) {
  // load all rules configurations in the system
  $rules = entity_load('rules_config');
  foreach ($rules as $rule) {
    // check this rule's conditions for role matches
    foreach($rule->conditions() as $condition) {
      if (isset($condition->settings['roles'][$role->rid])) {
        unset($condition->settings['roles'][$role->rid]);
        $condition->settings['roles'][$newrid] = $newrid;
        $condition->save();
        drupal_set_message(t('Rule @hname (@mname) condition was updated so the rid change would be maintained.', array('@hname' => $rule->label, '@mname' => $rule->name)), 'status');
      }
    }
    // now look into the actions
    foreach($rule->actions() as $action) {
      if (isset($action->settings['roles'][$role->rid])) {
        unset($action->settings['roles'][$role->rid]);
        $action->settings['roles'][$newrid] = $newrid;
        $action->save();
        drupal_set_message(t('Rule @hname (@mname) action was updated so the rid change would be maintained.', array('@hname' => $rule->label, '@mname' => $rule->name)), 'status');
      }
    }
  }
}
