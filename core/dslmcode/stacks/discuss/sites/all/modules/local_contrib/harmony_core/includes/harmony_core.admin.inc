<?php

/**
 * @file
 * harmony_core.admin.inc
 * Page and form callbacks for administration of the Thread and Post entity types.
 */

/**
 * Page callback for the landing structure settings page.
 */
function harmony_core_harmony_structure_settings() {
  return '';
}

function harmony_core_thread_entity_form($form, &$form_state, $bundle = array(), $op = 'edit') {

}

function harmony_core_post_entity_form($form, &$form_state, $bundle = array(), $op = 'edit') {
  $form['text'] = array(
    '#markup' => '<p>' . t('Nothing to see here, why not manage some fields?') . '</p>',
  );

  return $form;
}

/**
 * General Harmony settings form.
 */
function harmony_core_admin_general() {
  $form = array();

  return system_settings_form($form);
}

/**
 * Return a basic form that facilitates the rebuild actions.
 */
function harmony_core_admin_rebuild_data() {
  $form = array();

  $form['guidance_text'] = array(
    '#markup' => '<p>' . t('From this page you can rebuild supporting data used by Harmony entities.') .'</p><p>' . t("If your site has a lot of content and expect these rebuild commands to take a while, you should probably put the site in <a href=\"@maintenance-url\">Maintenance mode</a> until they're done.", array('@maintenance-url' => url('admin/config/development/maintenance'))) . '</p>',
  );

  $rebuild_actions = harmony_core_rebuild_actions();
  foreach ($rebuild_actions as $id => $rebuild_action) {
    $form[$id] = array(
      '#type' => 'fieldset',
      '#title' => $rebuild_action['fieldset title'],
    );

    $form[$id]['guidance_text'] = array(
      '#markup' => '<p>' . $rebuild_action['guidance text'] . '</p>',
    );

    $form[$id]["{$id}_button"] = array(
      '#type' => 'submit',
      '#value' => t('Rebuild @action', array('@action' => $rebuild_action['title'])),
      '#submit' => array('harmony_core_admin_rebuild_redirect'),
      '#rebuild_confirm_action' => $id,
    );
  }

  return $form;
}

/**
 * Redirect to a confirmation page for a rebuild action.
 */
function harmony_core_admin_rebuild_redirect($form, &$form_state) {
  drupal_goto('admin/harmony/config/general/rebuild/confirm/' . check_plain($form_state['clicked_button']['#rebuild_confirm_action']));
}

/**
 * Confirmation for for rebuilds.
 */
function harmony_core_admin_rebuild_confirm($form, $form_state, $action_id) {
  $rebuild_actions = harmony_core_rebuild_actions();
  $action = !empty($rebuild_actions[$action_id]) ? $rebuild_actions[$action_id] : NULL;

  if (!$action) {
    return array(
      '#markup' => '<p>' . t('Action not found.') . '</p>',
    );
  }

  $form['action_id'] = array(
    '#type' => 'value',
    '#value' => $action_id,
  );

  $form['action'] = array(
    '#type' => 'value',
    '#value' => $action,
  );

  // Add in any options for the rebuild command.
  if (!empty($action['arguments'])) {
    foreach ($action['arguments'] as $argument_id => $argument) {
      $form[$argument_id] = $argument;
    }
  }

  return confirm_form(
    $form,
    t('Are you sure you want to rebuild @title?', array('@title' => $action['title'])),
    'admin/harmony/config/general/rebuild',
    '',
    t('Rebuild @title', array('@title' => $action['title'])),
    t('Cancel')
  );
}

/**
 * Confirm submit handler which also kicks off the batch operation.
 *
 * @see harmony_core_admin_rebuild_confirm()
 */
function harmony_core_admin_rebuild_confirm_submit($form, &$form_state) {
  $action_id = $form_state['values']['action_id'];

  harmony_core_admin_rebuild_execute($action_id, $form_state['values']);

  $form_state['redirect'] = 'admin/harmony/config/general/rebuild';
}

/**
 * Returns a system form for disabling new Harmony forum content.
 */
function harmony_core_admin_disable_new_content() {
  $form = array();

  $form['guidance_text'] = array(
    '#markup' => '<p>' . t('Disabling new content is intended as a temporary measure and allows you to prevent new forum content from being created. A typical reason for this might be a SPAM attack.') . '</p>',
  );

  $form['harmony_core_disable_new_content'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable new content from being created'),
    '#description' => t('This will prevent users from creating new threads or posts regardless of permissions.'),
    '#default_value' => variable_get('harmony_core_disable_new_content', FALSE),
  );

  $form['warning'] = array(
    '#type' => 'fieldset',
    '#title' => t('Warning message'),
    '#states' => array(
      'visible' => array(
        ':input[id="edit-harmony-core-disable-new-content"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['warning']['harmony_core_disable_new_content_warning_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display a warning message to all users?'),
    '#default_value' => variable_get('harmony_core_disable_new_content_warning_enabled', FALSE),
  );

  $form['warning']['harmony_core_disable_new_content_warning_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Warning message text'),
    '#description' => t('The text to display in the drupal set message warning to users without access to this page.'),
    '#default_value' => variable_get('harmony_core_disable_new_content_warning_message', 'The creation of new threads and posts has been temporarily disabled.'),
    '#states' => array(
      'visible' => array(
        ':input[id="edit-harmony-core-disable-new-content-warning-enabled"]' => array('checked' => TRUE),
      ),
    ),
  );

  return system_settings_form($form);
}
