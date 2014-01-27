<?php

class EntityReferencePrepopulateInstanceBehavior extends EntityReference_BehaviorHandler_Abstract {

  /**
   * Generate a settings form for this handler.
   */
  public function settingsForm($field, $instance) {
    $field_name = $field['field_name'];

    $form['action'] = array(
      '#type' => 'select',
      '#title' => t('Action'),
      '#options' => array(
        'none' => t('Do nothing'),
        'hide' => t('Hide field'),
        'disable' => t('Disable field'),
      ),
      '#description' => t('Action to take when prepopulating field with values via URL.'),
    );
    $form['action_on_edit'] = array(
      '#type' => 'checkbox',
      '#title' => t('Apply action on edit'),
      '#description' => t('Apply action when editing an existing entity.'),
      '#states' => array(
        'invisible' => array(
          ':input[name="instance[settings][behaviors][prepopulate][action]"]' => array('value' => 'none'),
        ),
      ),
    );
    $form['fallback'] = array(
      '#type' => 'select',
      '#title' => t('Fallback behaviour'),
      '#description' => t('Determine what should happen if no values are provided via URL.'),
      '#options' => array(
        'none' => t('Do nothing'),
        'hide' => t('Hide field'),
        'form_error' => t('Set form error'),
        'redirect' => t('Redirect'),
      ),
    );

    // Get list of permissions.
    $perms = array();
    $perms[0] = t('- None -');
    foreach (module_list(FALSE, FALSE, TRUE) as $module) {
      // By keeping them keyed by module we can use optgroups with the
      // 'select' type.
      if ($permissions = module_invoke($module, 'permission')) {
        foreach ($permissions as $id => $permission) {
          $perms[$module][$id] = strip_tags($permission['title']);
        }
      }
    }

    $form['skip_perm'] = array(
      '#type' => 'select',
      '#title' => t('Skip access permission'),
      '#description' => t('Set a permission that will not be affected by the fallback behavior.'),
      '#options' => $perms,
    );

    $description = t('Determine if values that should be prepopulated should "listen" to the OG-context.');

    if ($disabled = !module_exists('og_context') || !og_is_group_audience_field($field_name)) {
      $description .= '<br / >' . t('Organic groups integration: Enable OG-context and set "Entity selection mode" to "Organic groups" to enable this selection.');
    }

    $form['og_context'] = array(
      '#type' => 'checkbox',
      '#title' => t('OG context'),
      '#description' => $description,
      '#disabled' => $disabled,
    );

    return $form;
  }
}
