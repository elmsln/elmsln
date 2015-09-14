<?php

/**
 * @file
 * Renderable elements adminstrative functions.
 */

/**
 * List callback to display all builds.
 */
function rel_builds_overview() {
  $rows = array();
  $builds = rel_get_builds(TRUE);

  foreach ($builds as $build_id => $rel_build) {

    $operations = array();
    $operations[] = l(t('Manage build'), $rel_build->path);

    if ($rel_build->export_type != 2) {
      $operations[] = l(t('Unregister'), 'rel-unregister/nojs/' . $build_id, array('query' => drupal_get_destination()));
    }
    else {
      $operations[] = t('Locked');
    }

    $rows[] = array(
      0 => $rel_build->label,
      1 => implode(' - ', $operations),
    );
  }

  if (!empty($rows)) {
    $variables = array(
      'header' => array(t('Build id'), t('Operations')),
      'rows' => $rows,
    );
    $build['list'] = array('#markup' => theme('table', $variables));
  }
  else {
    $build['list'] = array('#markup' => t('No builds found.'));
  }

  return $build;
}

/**
 * Menu callback: enable or disable registration for forms.
 */
function rel_register_admin_form($form) {

  $form['rel_build_form_registration'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enable form registration',
    '#default_value' => variable_get('rel_build_form_registration', TRUE),
    '#description' => t('This option enables "Manage form display" links on forms throughout your site. These links are used to add these forms to the list of "Renderable Elements" listed in the "Renderable Elements" tab. Once a form has been added, you can use the "Renderable Elements" tab to manage the form display options and to unregister the form.<br /><br />It is recommended that you enable this option when registering forms and then disable this option after you have added the forms to the "Renderable Elements" list. When enabled, this option may conflict with other modules. Disabling this options after forms have been registered will not remove them from the "Renderable Elements" list in the "Renderable Elements" tab.<br /><br />You may prevent these links using specific exclusion rules below.'),
  );

  $form['rel_build_registration_ignore'] = array(
    '#type' => 'textarea',
    '#title' => t('Ignore registration on specific pages'),
    '#description' => t('Specify pages by using their paths. Enter one path per line. The \'*\' character is a wildcard. Example paths are blog for the blog page and blog/* for every personal blog. &lt;front&gt; is the front page.'),
    '#default_value' => variable_get('rel_build_registration_ignore'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit callback.
 */
function rel_register_admin_form_submit($form, $form_state) {
  // Save the values.
  variable_set('rel_build_form_registration', $form_state['values']['rel_build_form_registration']);
  variable_set('rel_build_registration_ignore', $form_state['values']['rel_build_registration_ignore']);

  // Clear module implements cache.
  cache_clear_all('module_implements', 'cache_bootstrap');

  // Confirm message.
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Menu callback: register a form.
 */
function rel_build_register($js, $build_id = '') {

  // Run in modal.
  if ($js) {

    // Include CTools modal.
    ctools_include('modal');
    ctools_include('ajax');

    $form_state = array(
      'title' => t('Register a build'),
      'ajax' => $js,
      'build_id' => $build_id,
    );

    $commands = ctools_modal_form_wrapper('rel_build_register_form', $form_state);

    if (!empty($form_state['executed'])) {
      $commands = array();
      $commands[] = ctools_modal_command_dismiss(t('%build_id has been registered as a renderable element.', array('%build_id' => $build_id)));
      $commands[] = ajax_command_invoke('.rel-register-link', 'RelRefreshPage');
    }

    print ajax_render($commands);
    ajax_footer();
    exit;
  }
  else {
    return drupal_get_form('rel_build_register_form', $build_id);
  }
}


/**
 * Menu callback: register a form.
 */
function rel_build_unregister($js, $build_id = '') {

  // Run in modal.
  if ($js) {

    // Include CTools modal.
    ctools_include('modal');
    ctools_include('ajax');

    $form_state = array(
      'title' => t('Unregister a build'),
      'ajax' => $js,
      'build_id' => $build_id,
    );
    $commands = ctools_modal_form_wrapper('rel_build_unregister_form', $form_state);

    if (!empty($form_state['executed'])) {
      $commands = array();
      $commands[] = ctools_modal_command_dismiss(t('%build_id has been unregistered as a renderable element.', array('%build_id' => $build_id)));
      $commands[] = ajax_command_invoke('.rel-register-link', 'RelRefreshPage');
    }

    print ajax_render($commands);
    ajax_footer();
    exit;
  }
  else {
    return drupal_get_form('rel_build_unregister_form', $build_id);
  }
}

/**
 * Registration form.
 */
function rel_build_register_form($form, &$form_state, $build_id = '') {

  if (isset($form_state['build_id'])) {
    $build_id = $form_state['build_id'];
  }

  if (empty($build_id) || !isset($_SESSION['rel_builds'][$build_id])) {
    return array(
      'info' => array('#markup' => (t('Build is empty.')))
    );
  }

  $build = rel_build_load($build_id);
  if ($build) {
    return array(
      'info' => array('#markup' => (t('Build %build_id has already been registered.', array('%build_id' => $build_id))))
    );
  }

  $form['info'] = array(
    '#markup' => t('Select which elements you want to manage for %build_id.', array('%build_id' => $build_id)),
  );

  // Values and actions.
  $form['#build_id'] = $build_id;
  $form['#entity_type'] = $_SESSION['rel_builds'][$build_id]['entity_type'];
  $form['#bundle'] = $_SESSION['rel_builds'][$build_id]['bundle'];
  $form['#view_mode'] = $_SESSION['rel_builds'][$build_id]['view_mode'];
  $form['#context'] = $_SESSION['rel_builds'][$build_id]['context'];
  $form['#path'] = $_SESSION['rel_builds'][$build_id]['path'];

  // CSS.
  $form['#attached']['css'][] = drupal_get_path('module', 'rel') . '/rel.admin.css';

  // Drupal title
  if ($form['#context'] == 'form') {
    drupal_set_title(t('Manage form display'), PASS_THROUGH);
  }

  // Table select.
  $header = array(
    'label' => t('Element'),
    'key' => t('Machine name'),
    'parent' => t('Group')
  );
  foreach ($_SESSION['rel_builds'][$build_id]['elements'] as $key => $element) {
    $parent_el = '';
    if (!empty($element['parent'])) {
      $parent_el = $_SESSION['rel_builds'][$build_id]['elements'][$element['parent']];
    }
    $options[$key] = array(
      'label' => $element['label'],
      'key' => $key,
      'parent' => !empty($parent_el) ? $parent_el['label'] : '',
    );
  }

  // Highlight special elements.
  $special_options = rel_build_register_form_special_options();
  foreach ($special_options as $key => $value) {
    if (isset($options[$key])) {
      $options[$key]['#attributes'] = array('class' => array($value));
    }
  }

  $form['elements'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No elements available.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  if (isset($_GET['destination'])) {
    $form['actions']['cancel'] = array(
      '#type' => 'link',
      '#title' => t('Cancel'),
      '#href' => $_GET['destination'],
      '#options' => array(),
    );
  }

  return $form;
}

function rel_build_register_form_special_options() {
  return array(
    'options' => 'dangerous',
    'status' => 'dangerous',
  );
}

/**
 * Registration validate callback.
 */
function rel_build_register_form_validate($form, &$form_state) {
  // Make sure at least one element is registered.
  if (!is_array($form_state['values']['elements']) || !count(array_filter($form_state['values']['elements']))) {
    form_set_error('', t('No elements selected.'));
  }
}

/**
 * Registration submit callback.
 */
function rel_build_register_form_submit($form, &$form_state) {

  // Get values.
  $build_id = $form['#build_id'];
  $entity_type = $form['#entity_type'];
  $bundle = $form['#bundle'];
  $view_mode = $form['#view_mode'];
  $context = $form['#context'];
  $path = $form['#path'];

  // Create build.
  $rel_build = new stdClass;
  $rel_build->build_id = $build_id;
  $rel_build->api_version = 1;
  $rel_build->label = $build_id;
  $rel_build->entity_type = $form['#entity_type'];
  $rel_build->bundle = $form['#bundle'];
  $rel_build->view_mode = $form['#view_mode'];
  $rel_build->context = $form['#context'];
  $rel_build->path = $form['#path'];

  $elements = array();
  foreach ($form_state['values']['elements'] as $key => $value) {
    if ($key === $value) {
      $elements[$key] = $_SESSION['rel_builds'][$build_id]['elements'][$key];
    }
  }
  $rel_build->elements = $elements;
  $rel_build->duplicate = array();

  // Let other modules act on the registration of the build before save.
  drupal_alter('rel_build_register_alter', $rel_build);

  // Save the record.
  drupal_write_record('rel_builds', $rel_build);

  // Let other modules act on the registration of the build after save.
  module_invoke_all('rel_build_register', $rel_build);

  // Friendly message.
  drupal_set_message(t('%build_id has been registered as a renderable element.', array('%build_id' => $build_id)));

  // Clear caches.
  drupal_flush_all_caches();
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * Unregistration form.
 */
function rel_build_unregister_form($form, $form_state, $build_id = '') {

  if (isset($form_state['build_id'])) {
    $build_id = $form_state['build_id'];
  }

  if (empty($build_id)) {
    return array(
      'info' => array('#markup' => (t('Build is empty.')))
    );
  }

  $build = rel_build_load($build_id);
  if (!$build) {
    return array(
      'info' => array('#markup' => (t('Build %build_id is not registered.', array('%build_id' => $build_id))))
    );
  }

  $title = t('Are you sure you want to unregister build %build_id ?', array('%build_id' => $build_id));
  drupal_set_title($title, PASS_THROUGH);

  if (isset($form_state['ajax']) && $form_state['ajax']) {
    $form['question'] = array(
      '#markup' => $title,
    );
  }

  // Values and actions.
  $form['#build_id'] = $build_id;
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm'),
  );
  $form['actions']['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Cancel'),
    '#href' => $_GET['destination'],
    '#options' => array(),
  );

  return $form;
}

/**
 * Unregistration submit callback.
 */
function rel_build_unregister_form_submit($form, &$form_state) {

  $build_id = $form['#build_id'];
  $build = rel_build_load($build_id);

  db_delete('rel_builds')
    ->condition('build_id', $build_id)
    ->execute();

  // Cleanup field bundle settings.
  $field_bundle_settings = field_bundle_settings($build->entity_type, $build->bundle);
  if (isset($field_bundle_settings['extra_fields'][$build->context])) {
    unset($field_bundle_settings['extra_fields'][$build->context]);
    field_bundle_settings($build->entity_type, $build->bundle, $field_bundle_settings);
  }

  // Let other modules act on the unregistration of the build.
  module_invoke_all('rel_build_unregister', $build);

  // Friendly message.
  drupal_set_message(t('%build_id has been unregistered as a renderable element.', array('%build_id' => $build_id)));

  // Clear caches.
  drupal_flush_all_caches();
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * Page callback to manage a custom build.
 *
 * @param $form
 *   The configuration of the build.
 */
function rel_build_manage_custom($rel_build) {

  // Use drupal_build_form instead of drupal_get_form.
  $form_state = array();
  $arguments = array('rel_build', $rel_build->build_id, 'form');
  $form_state['build_info']['args'] = $arguments;
  $form_state['no_fapi_fields'] = TRUE;
  $form_state['rel_build'] = TRUE;

  form_load_include($form_state, 'inc', 'field_ui', 'field_ui.admin');
  $build = drupal_build_form('field_ui_field_overview_form', $form_state);

  // Ignore field group clone.
  if (module_exists('field_group') && $rel_build->entity_type == 'rel_build') {
    $build['additional_settings']['field_group']['#access'] = FALSE;
  }

  drupal_set_title(t('Manage build of !label', array('!label' => $rel_build->label)));

  // Add necessary variables.
  if ($rel_build->context == 'form') {
    $build['#view_mode'] = 'form';
    $build['#attached']['css'][] = drupal_get_path('module', 'rel') . '/rel.admin.css';
  }

  return $build;
}

/**
 * Menu callback; present a form for removing a group.
 */
function rel_delete_group_form($form, &$form_state, $build, $group = '') {

  if (empty($group)) {
    drupal_set_message(t('The group was empty.'));
    drupal_goto($build->path);
  }

  $group = field_group_load_field_group($group, $build->entity_type, $build->bundle, $build->view_mode);
  if (!$group) {
    drupal_set_message(t('The group was empty.'));
    drupal_goto($build->path);
  }

  $form['#group'] = $group;
  $form['#redirect'] = array($build->path);
  $output = confirm_form($form,
    t('Are you sure you want to delete the group %group?', array('%group' => t($group->label))),
    $build->path,
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel'),
    'confirm'
  );

  return $output;
}

/**
 * Remove group from bundle.
 */
function rel_delete_group_form_submit($form, &$form_state) {
  module_load_include('inc', 'field_group', 'field_group.field_ui');
  field_group_delete_form_submit($form, $form_state);
}

