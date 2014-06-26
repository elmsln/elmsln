<?php

/**
 * @file
 * Administrative page callbacks for the responsive_preview module.
 */

/**
 * Form callback: builds the page for administering devices.
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 * @return
 *   An array representing the form definition.
 *
 * @ingroup forms
 * @see responsive_preview_admin_form_validate()
 * @see responsive_preview_admin_form_submit()
 */
function responsive_preview_admin_form($form, &$form_state) {

  $devices = responsive_preview_get_device_definition();

  $form['devices'] = array();

  foreach ($devices as $name => $device) {

    $form['devices'][$name] = array(
      'name' => array(
        '#type' => 'value',
        '#value' => $device['name'],
      ),
      'label' => array(
        '#markup' => check_plain($device['label']),
      ),
      'status' => array(
        '#type' => 'checkbox',
        '#title' => t('Show %title in list', array('%title' => $device['label'])),
        '#title_display' => 'invisible',
        '#default_value' => $device['status'],
      ),
      'dimensions' => array(
        '#markup' => check_plain($device['width'] . 'x' . $device['height'] . ' (' . $device['dppx'] . ' dppx)'),
      ),
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight for @title', array('@title' => $device['label'])),
        '#title_display' => 'invisible',
        '#default_value' => $device['weight'],
        '#attributes' => array('class' => array('weight')),
      ),
      'edit' => array(
        '#type' => 'link',
        '#title' => t('edit'),
        '#href' => 'admin/config/content/responsive-preview/' . $device['name'] . '/edit',
        '#attributes' => array(
          'title' => t('edit @label', array('@label' => $device['label'])),
        ),
      ),
      'delete' => array(
        '#type' => 'link',
        '#title' => t('delete'),
        '#href' => 'admin/config/content/responsive-preview/' . $device['name'] . '/delete',
        '#attributes' => array(
          'title' => t('delete @label', array('@label' => $device['label'])),
        ),
      ),
      '#tree' => TRUE,
      '#parents' => array('devices', $name),
    );
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Form submit handler for responsive_preview_admin_form().
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 * @see responsive_preview_admin_form()
 * @see responsive_preview_admin_formvalidate()
 */
function responsive_preview_admin_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Save')) {
    responsive_preview_update_device_listing_values($form_state['values']['devices']);
  }
}

/**
 * Processes variables for responsive-preview-admin-form.tpl.php.
 *
 * @see responsive-preview-admin-form.tpl.php
 */
function template_preprocess_responsive_preview_admin_form(&$variables) {
  // Move each device defintion to a top-level variable for the template.
  foreach (element_children($variables['form']['devices']) as $i) {
    // Assign by reference so that when the renderables are rendered for each
    // device, the reference will be marked as #printed and will be ignored
    // when the children of the form key are rendered below.
    $device = &$variables['form']['devices'][$i];

    $device['weight']['#attributes']['class'] = array('device-weight');

    $variables['devices'][] = array(
      'label' => drupal_render($device['label']),
      'status' => drupal_render($device['status']),
      'dimensions' => drupal_render($device['dimensions']),
      'weight' => drupal_render($device['weight']),
      'edit_link' => drupal_render($device['edit']),
      'delete_link' => drupal_render($device['delete']),
    );
  }

  // The children must be rendered so that hidden fields are printed as well.
  $variables['form_submit'] = drupal_render_children($variables['form']);
}

/**
 * Form callback: builds the form for adding a device.
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 * @return
 *   An array representing the form definition.
 *
 * @ingroup forms
 * @see responsive_preview_device_add_form_validate()
 * @see responsive_preview_device_add_form_submit()
 */
function responsive_preview_device_add_form($form, &$form_state) {

  $form += responsive_preview_device_configuration_form();

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add device'),
  );

  return $form;
}

/**
 * Form validation handler for responsive_preview_device_add_form().
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 * @see responsive_preview_device_add_form()
 * @see responsive_preview_device_add_form_submit()
 */
function responsive_preview_device_add_form_validate($form, &$form_state) {
  responsive_preview_validate_device_values($form, $form_state);
}

/**
 * Form submit handler for responsive_preview_device_add_form().
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 * @see responsive_preview_device_add_form()
 * @see responsive_preview_device_add_form_validate()
 */
function responsive_preview_device_add_form_submit($form, &$form_state) {
  responsive_preview_update_device_definition($form_state['values']['device']);
  $form_state['redirect'] = 'admin/config/content/responsive-preview';
}

/**
 * Form builder for the device editing form.
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 * @param $name
 *   (Optional) A string that identifies a device by its unique name.
 *
 * @return
 *   An array representing the form definition.
 *
 * @ingroup forms
 * @see responsive_preview_device_edit_form_submit()
 * @see responsive_preview_device_edit_form_validate()
 */
function responsive_preview_device_edit_form($form, &$form_state, $name = '') {
  $devices = responsive_preview_get_device_definition($name);
  $device = $devices[$name];
  if (!empty($device)) {
    $form += responsive_preview_device_configuration_form($device);
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
  }
  else {
    drupal_set_message(t('No device found for %name.', array('%name' => $name)), 'warning');
  }

  return $form;
}

/**
 * Form validation handler for responsive_preview_device_edit_form().
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 * @see responsive_preview_device_edit_form()
 * @see responsive_preview_device_edit_form_submit()
 */
function responsive_preview_device_edit_form_validate($form, &$form_state) {
  responsive_preview_validate_device_values($form, $form_state);
}

/**
 * Form submit handler for responsive_preview_device_edit_form().
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 * @see responsive_preview_device_edit_form()
 * @see responsive_preview_device_edit_form_validate()
 */
function responsive_preview_device_edit_form_submit($form, &$form_state) {
  responsive_preview_update_device_definition($form_state['values']['device'], TRUE);
  $form_state['redirect'] = 'admin/config/content/responsive-preview';
}

/**
 * Form constructor for the device deletion form.
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 * @param $name
 *   (Optional) A string that identifies a device by its unique name.
 *
 * @return
 *   An array representing the form definition.
 *
 * @param $device
 *   The device object.
 *
 * @see responsive_preview_device_delete_form_submit()
 */
function responsive_preview_device_delete_form($form, &$form_state, $name) {
  $devices = responsive_preview_get_device_definition($name);
  $device = $devices[$name];
  $form['name'] = array(
    '#type' => 'hidden',
    '#value' => $device['name'],
  );

  return confirm_form($form, t('Are you sure you want to delete the device %label?', array('%label' => $device['label'])), 'admin/config/content/responsive-preview', '', t('Delete'), t('Cancel'));
}

/**
 * Form submission handler for responsive_preview_device_delete_form().
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 *
 * @see responsive_preview_device_delete_form()
 */
function responsive_preview_device_delete_form_submit($form, &$form_state) {
  $name = $form_state['values']['name'];
  $devices = responsive_preview_get_device_definition();
  $label = $devices[$name]['label'];

  try {
    db_delete('responsive_preview')
      ->condition('name', $form_state['values']['name'])
      ->execute();
  }
  catch (Exception $e) {
    watchdog_exception('responsive_preview', $e);
    throw $e;
  }
  cache_clear_all('responsive_preview', 'cache', TRUE);
  drupal_set_message(t('Device :label has been deleted.', array(':label' => $label)));
  $form_state['redirect'] = 'admin/config/content/responsive-preview';
}

/**
 * Retrieves all or a specific device record.
 *
 * @param $name
 *   (Optional) A string that identifies a device by its unique name.
 *
 * @return
 *   An associative array that represents a list of device definitions.
 */
function responsive_preview_get_device_definition($name = '') {
  if (empty($name) && $cache = cache_get('responsive_preview_devices')) {
    return $cache->data;
  }
  $results = array();
  try {
    $query = db_select('responsive_preview', 'rp')
      ->fields('rp')
      ->orderBy('weight', 'ASC');

    if (!empty($name)) {
      $query->condition('name', $name);
    }

    $results = $query
      ->execute()
      ->fetchAllAssoc('name', PDO::FETCH_ASSOC);
  }
  catch (Exception $e) {
    watchdog_exception('responsive_preview', $e);
    throw $e;
  }
  if (empty($name)) {
    cache_set('responsive_preview_devices', $results, 'cache');
  }

  return $results;
}

/**
 * Updates devices defintions from form values.
 *
 * @param Array $devices
 *   The form values that represent a list of devices.
 *
 * @see responsive_preview_admin_form()
 */
function responsive_preview_update_device_listing_values($devices) {
  $transaction = db_transaction();
  try {
    foreach ($devices as $device) {
      db_update('responsive_preview')
        ->fields(array(
          'status' => $device['status'],
          'weight' => $device['weight'],
        ))
        ->condition('name', $device['name'])
        ->execute();
    }
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog_exception('responsive_preview', $e);
    throw $e;
  }
  drupal_set_message(t('The device settings have been updated.'));
  cache_clear_all('responsive_preview', 'cache', TRUE);
}

/**
 * Adds or a updates the record for a device.
 *
 * @param $device
 *   An associative array that represents the definition of a device.
 * @param $exists
 *   (optional) A Boolean that flags whether this device already exists (TRUE), and thus
 *   should be updated, or if it is new (FALSE) and should be added.
 */
function responsive_preview_update_device_definition($device, $exists = FALSE) {
  $transaction = db_transaction();
  if ($exists) {
    $query = db_update('responsive_preview');
  }
  else {
    $query = db_insert('responsive_preview');
  }
  $label = trim($device['label']);
  try {
    $query->fields(array(
      'label' => $label,
      'name' => trim($device['name']),
      'width' => trim($device['dimensions']['width']),
      'height' => trim($device['dimensions']['height']),
      'dppx' => trim($device['dimensions']['dppx']),
      'orientation' => $device['orientation'],
      'status' => $device['status'],
      'weight' => $device['weight'],
    ));

    // If the device definition already exists, add a condition
    if ($exists) {
      $query->condition('name', $device['name']);
    }

    $query->execute();
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog_exception('responsive_preview', $e);
    throw $e;
  }
  if ($exists) {
    drupal_set_message(t('Device %label has been updated.', array('%label' => $device['label'])));
  }
  else {
    drupal_set_message(t('Device %label has been added.', array('%label' => $device['label'])));
  }
  cache_clear_all('responsive_preview', 'cache', TRUE);
}

/**
 * Builds a form that represents a device definition.
 *
 * @param $device
 *   (Optional) An associative array that represents the definition of a device.
 *
 * @return
 *   An associative array representing the form definition.
 */
function responsive_preview_device_configuration_form($device = array()) {
  $form = array(
    'device' => array(
      '#tree' => TRUE
    )
  );
  $form['device']['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Device name'),
    '#default_value' => !empty($device['label']) ? $device['label'] : NULL,
    '#size' => 30,
    '#required' => TRUE,
    '#maxlength' => 64,
  );
  $form['device']['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => !empty($device['name']) ? $device['name'] : NULL,
    '#required' => TRUE,
    '#size' => 30,
    '#maxlength' => 64,
    '#machine_name' => array(
      'exists' => 'responsive_preview_get_device_definition',
      'source' => array('device', 'label'),
      'replace_pattern' => '[^0-9a-z_\-]',
      'error' => t('Please only use lowercase alphanumeric characters, underscores (_), and hyphens (-) for style names.'),
    ),
  );
  $form['device']['dimensions'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
  );
  $form['device']['dimensions']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => !empty($device['width']) ? $device['width'] : NULL,
    '#field_suffix' => 'px',
    '#size' => 6,
    '#required' => TRUE,
  );
  $form['device']['dimensions']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#default_value' => !empty($device['height']) ? $device['height'] : NULL,
    '#field_suffix' => 'px',
    '#size' => 6,
    '#required' => TRUE,
  );
  $form['device']['dimensions']['dppx'] = array(
    '#type' => 'textfield',
    '#title' => t('Dots per pixel (dppx)'),
    '#description' => t('Size of a single dot in graphical representation. Classic desktop displays have 1dppx, typical modern smartphones and laptops have 2dppx or higher. For example Google Nexus 4 and iPhone 5 has 2dppx, while Google Nexus 7 has 1.325dppx and Samsung Galaxy S4 has 3dppx.'),
    '#default_value' => !empty($device['dppx']) ? $device['dppx'] : NULL,
    '#size' => 4,
    '#required' => TRUE,
  );
  $form['device']['orientation'] = array(
    '#type' => 'select',
    '#title' => t('Default orientation'),
    '#default_value' => !empty($device['orientation']) ? $device['orientation'] : NULL,
    '#options' => array('portrait' => t('Portrait'), 'landscape' => t('Landscape')),
  );
  $form['device']['status'] = array(
    '#type' => 'value',
    '#value' => !empty($device['status']) ? $device['status'] : 1,
  );
  $form['device']['weight'] = array(
    '#type' => 'value',
    '#value' => !empty($device['weight']) ? $device['weight'] : 0,
  );
  return $form;
}

/**
 * Validates values in the form that describe a device definition.
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @param $form_state
 *   An associative array containing the current state of the form.
 */
function responsive_preview_validate_device_values($form, &$form_state) {
  if (!empty($form_state['values']['device']['label'])) {
    if (!preg_match("/^[a-zA-Z0-9_ ]+$/", trim($form_state['values']['device']['label']))) {
      form_set_error('device][label', t('The label must contain only alphanumeric characters, underscores and spaces.'));
    }
  }
  foreach ($form_state['values']['device']['dimensions'] as $type => $value) {
    if (!empty($value)) {
      if (!preg_match("/^[0-9]+$/", trim($value))) {
        form_set_error('device][dimensions][' . $type, t('The @type dimension must contain only numeric characters.', array('@type' => $type)));
      }
    }
  }
}

/**
 * Constructs a title for the device edit form.
 *
 * @param $name
 *   A string that identifies a device by its unique name.
 *
 * @return
 *   A string to use as the form page title.
 */
function responsive_preview_title_callback($name) {
  $devices = responsive_preview_get_device_definition();
  return t('Edit the device @label', array('@label' => $devices[$name]['label']));
}
