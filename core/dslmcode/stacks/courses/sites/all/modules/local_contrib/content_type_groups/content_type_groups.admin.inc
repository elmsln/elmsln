<?php
/**
 * @file
 * Admin page callback file for the Content type groups module.
 */

function content_type_groups_admin() {

  $output = '';

  $header = array(
    t('Name'),
    t('Content Types'),
    array('data' => t('Operations'), 'colspan' => 2),
  );

  $rows = array();
  $content_type_groups = ContentTypeGroup::fetch(TRUE);
  foreach ($content_type_groups as $group) {
    $columns = array();
    $columns[] = $group->name;
    $columns[] = count($group->content_types)
      ? implode(', ', $group->typeList())
      : 'No content types defined for this group.';
    $columns[] = l(t('edit'), 'admin/structure/types/groups/manage/' . $group->type);
    $columns[] = l(t('delete'), 'admin/structure/types/groups/manage/' . $group->type . '/delete');
    $rows[] = $columns;
  }

  $build['content_type_groups_table'] = array(
    '#theme'  => 'table',
    '#header' => $header,
    '#rows'   => $rows,
    '#empty'  => t('No content type groups available. <a href="@link">Add content type group</a>.', array('@link' => url('admin/structure/types/groups/add'))),
  );

  return $build;
}

/**
 * Form builder; Returns form for adding a new content type group.
 *
 * @ingroup forms
 * @see user_filter_form_submit()
 */
function content_type_groups_group_form($form, &$form_state, $group = NULL) {

  // If editing an existing group, get its info
  $locked = (bool) $group;
  $group = new ContentTypeGroup($group);

  // Display name for admin interface
  $form['name'] = array(
    '#title'         => t('Name'),
    '#type'          => 'textfield',
    '#default_value' => $group->name,
    '#description'   => t('The human-readable name of this content type group. This text will be displayed as part of the list on the <em>Add new content type group</em> page. It is recommended that this name begin with a capital letter and contain only letters, numbers, and spaces. This name must be unique.'),
    '#required'      => TRUE,
    '#size'          => 30,
  );

  // Machine name for referencing in Views/Features
  $form['type'] = array(
    '#type'          => 'machine_name',
    '#default_value' => $group->type,
    '#disabled'      => $locked,
    '#description'   => t('A unique machine-readable name for this content type group. It must only contain lowercase letters, numbers, and underscores. This name will be used for referencing this content type group, in which underscores will be converted into hyphens.'),
    '#maxlength'     => 32,
    '#machine_name'  => array(
      'exists' => 'content_type_groups_group_load',
    ),
  );

  // Build a table tree of the existing content types
  $form['items'] = array(
    '#tree' => TRUE,
  );

  // Create a list of sortable content types, sorted by weight
  $existing_types = $group->typeList(TRUE);
  $all_types = node_type_get_names();
  foreach ($existing_types as $machine_name => $data) {
    $form['content_types'][$machine_name] = array(
      'checked-' . $machine_name => array(
        '#type'          => 'checkbox',
        '#default_value' => 1,
        '#attributes'    => array('class' => array('check')),
      ),
      'name' => array(
        '#markup' => $data['name'],
      ),
      'weight-' . $machine_name => array(
        '#type'          => 'weight',
        '#delta'         => count($all_types) + 1,
        '#default_value' => $existing_types[$machine_name]['weight'],
        '#attributes'    => array('class' => array('weight')),
      ),
    );
    unset($all_types[$machine_name]);
  }
  $last_type = end($existing_types);
  $last_weight = $last_type['weight'];
  foreach ($all_types as $machine_name => $name) {
    $last_weight++;
    $form['content_types'][$machine_name] = array(
      'checked-' . $machine_name => array(
        '#type'          => 'checkbox',
        '#default_value' => 0,
        '#attributes'    => array('class' => array('check')),
      ),
      'name' => array(
        '#markup' => $name,
      ),
      'weight-' . $machine_name => array(
        '#type'          => 'weight',
        '#delta'         => count($all_types) + 1,
        '#default_value' => $last_weight,
        '#attributes'    => array('class' => array('weight')),
      ),
    );
  }

  // Add the subgroup fields
  /*
  $form['subgroup'] = array(
    'checked' => array(
      '#type'          => 'hidden',
      '#default_value' => 0,
      '#attributes'    => array('class' => array('check')),
    ),
    'name' => array(
      '#type'    => 'select',
      '#title'   => t('Add subgroup'),
      '#options' => array_merge(array('' => t('- Select a content type -')), ContentTypeGroup::fetch()),
    ),
    'weight' => array(
      '#type'          => 'weight',
      '#delta'         => count($existing_types) + 1,
      '#default_value' => count($existing_types) + 1,
      '#attributes'    => array('class' => array('weight')),
    ),

  );
  */

  // Action buttons
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save'),
  );
  $form['actions']['delete'] = array(
    '#type'  => 'button',
    '#value' => t('Delete'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/structure/types/groups'),
  );

  return $form;

}

/**
 * Callback for #machine_name exists for content_type_groups_group_form.
 */
function content_type_groups_group_load($machine_name) {
  $group = new ContentTypeGroup($machine_name);
  return $group->name !== NULL;
}

/**
 * Submit handler for form content_type_groups_group_form
 */
function content_type_groups_group_form_submit($form, &$form_state) {

  $group = new ContentTypeGroup($form_state['values']['type']);
  $group->name = $form_state['values']['name'];
  $group->content_types = array();
  foreach ($form_state['values'] as $field => $val) {
    if (strpos($field, 'checked-') === 0 && $val == 1) {
      $content_type = substr($field, 8); // Get the rest of the field name after 'checked-'
      $group->addContentType($content_type, $form_state['values']['weight-' . $content_type]);
    }
  }
  $group->save();

  drupal_set_message(t('Content type group %group has been saved.', array('%group' => $group->name)));
  //$form_state['redirect'] = 'admin/structure/types/groups';

}

/**
 * Menu callback: delete single content type group.
 */
function content_type_groups_group_delete_confirm($form, &$form_state, $group) {

  $group = new ContentTypeGroup($group);

  $form['type'] = array('#type' => 'value', '#value' => $group->type);
  $form['name'] = array('#type' => 'value', '#value' => $group->name);

  $message = t('Are you sure you want to delete the content type group %group?', array('%group' => $group->name));
  $caption = '';

  $caption .= '<p>' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, $message, 'admin/structure/types/groups', $caption, t('Delete'));
}

/**
 * Process content type group delete confirm submissions.
 */
function content_type_groups_group_delete_confirm_submit($form, &$form_state) {

  $group = new ContentTypeGroup($form_state['values']['type']);
  $group->delete();

  $t_args = array('%name' => $form_state['values']['name']);
  drupal_set_message(t('The content type %name has been deleted.', $t_args));
  watchdog('content type groups', 'Deleted content type groupv%name.', $t_args, WATCHDOG_NOTICE);

  $form_state['redirect'] = 'admin/structure/types/groups';

}