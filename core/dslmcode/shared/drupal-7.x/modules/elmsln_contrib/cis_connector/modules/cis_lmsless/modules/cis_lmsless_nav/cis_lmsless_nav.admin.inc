<?php
/**
 * @file
 * Administrative page callbacks for the CIS LMS-less Nav module.
 */

/**
 * drupal_get_form callback for hook_menu 'admin/config/elmsln/cis-lmsless-nav/add-link'
 */
function cis_lmsless_nav_admin_add_link_form($form, &$form_state) {
  // get the default form elements for the link
  $form = _cis_lmsless_nav_admin_form_elements();

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );

  return $form;
}

/**
 * drupal_get_form callback for hook_menu 'admin/config/elmsln/cis-lmsless-nav/edit-link'
 */
function cis_lmsless_nav_admin_edit_link_form($form, &$form_state, $link_key) {
  // load the existing links array
  $cis_lmsless_nav_links = variable_get('cis_lmsless_nav_links', NULL);
  $form = array();

  // if there are existing links in the variable
  if ($cis_lmsless_nav_links) {
    // load the default add link form
    $form = _cis_lmsless_nav_admin_form_elements();
    if (isset($cis_lmsless_nav_links[$link_key])) {
      // loop through each of the links attributes and put them into their
      // respective form fields as default values
      foreach ($cis_lmsless_nav_links[$link_key] as $link_attr_name => $link_attr_value) {
        $form['cis_lmsless_nav_links'][$link_attr_name]['#default_value'] = $link_attr_value;
      }
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
    // pass the link to via form_state
    $form_state['link_key'] = $link_key;

    return $form;
  }
  else {
    return t('This is not a valid link.');
  }
}

/**
 * Page Callback for hook_menu 'admin/config/elmsln/cis-lmsless-nav/delete-link/%'
 */
function cis_lmsless_nav_admin_delete_link_form($form, &$form_state, $link_key) {
  // load the existing links array
  $cis_lmsless_nav_links = variable_get('cis_lmsless_nav_links', NULL);
  $form = array();

  // if there are existing links in the variable
  if (isset($cis_lmsless_nav_links[$link_key])) {
    drupal_set_title(t('Are you sure you want to delete !title?', array('!title' => $cis_lmsless_nav_links[$link_key]['title'])));
  }

  $form['prefix'] = array(
    '#type' => 'markup',
    '#markup' => '<div>' . t('This action can not be undone.') . '</div>',
  );
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );
  // pass the link to via form_state
  $form_state['link_key'] = $link_key;

  return $form;
}

/**
 * Submit handler for cis_lmsless_nav_admin_add_link_form()
 */
function cis_lmsless_nav_admin_add_link_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/config/elmsln/cis-lmsless-nav';
  // add the new link to the variable array
  _cis_lmsless_nav_update_links_variable($form, $form_state);
}

/**
 * Submit handler for cis_lmsless_nav_admin_add_link_form()
 */
function cis_lmsless_nav_admin_edit_link_form_submit($form, &$form_state) {
  if (isset($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == 'Save') {
    $form_state['redirect'] = 'admin/config/elmsln/cis-lmsless-nav';
    // update the existing link in the variable array
    _cis_lmsless_nav_update_links_variable($form, $form_state, 'update');
  }
  if (isset($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == 'Delete') {
    $form_state['redirect'] = 'admin/config/elmsln/cis-lmsless-nav/delete-link/' . $form_state['link_key'];
  }
}

function cis_lmsless_nav_admin_delete_link_form_submit($form, &$form_state) {
  if (isset($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == 'Cancel') {
    $form_state['redirect'] = 'admin/config/elmsln/cis-lmsless-nav/edit-link/' . $form_state['link_key'];
  }
  if (isset($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == 'Delete') {
    $form_state['redirect'] = 'admin/config/elmsln/cis-lmsless-nav';
    _cis_lmsless_nav_update_links_variable($form, $form_state, 'delete');
  }
}

/**
 * Helper function that contains the default form elements for
 * adding and editing links
 */
function _cis_lmsless_nav_admin_form_elements() {
  $form['cis_lmsless_nav_links']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Link title'),
    '#required' => TRUE,
  );
  $form['cis_lmsless_nav_links']['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Link path'),
    '#required' => TRUE,
  );
  $form['cis_lmsless_nav_links']['group'] = array(
    '#type' => 'textfield',
    '#title' => t('Group name'),
    '#required' => TRUE,
  );
  $form['cis_lmsless_nav_links']['machine_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Icon name'),
    '#description' => t('Machine name of the icon you would like to display next to the link. Leave blank for no icon.'),
  );
  $form['cis_lmsless_nav_links']['icon_library'] = array(
    '#type' => 'select',
    '#title' => t('Icon Library'),
    '#options' => array(
      'foundation_access' => 'Foundation Access',
      'material' => 'Material',
      ),
    '#default_value' => 'foundation_access',
    '#description' => t('The library in which this icon resides.'),
    '#states' => array(
      'visible' => array(
        ':input[name="machine_name"]' => array('empty' => FALSE),
      ),
    ),
  );
  $form['cis_lmsless_nav_links']['weight'] = array(
    'weight' => array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => 0,
      '#delta' => 10,
    ),
  );

  return $form;
}

/**
 * Helper function that will create, update or delete links in the cis_lmsless_nav_links
 * variable.
 *
 * @param  array  $form
 * @param  array  $form_state
 * @param  string $action     CRUD update that you wish to preform
 *                            - create
 *                            - update
 *                            - delete
 */
function _cis_lmsless_nav_update_links_variable($form, $form_state, $action = 'create') {
  // load the links that are currently in the variable
  $cis_lmsless_nav_links = variable_get('cis_lmsless_nav_links', array());

  // deleting a link
  if (isset($form_state['link_key']) && $action == 'delete') {
    unset($cis_lmsless_nav_links[$form_state['link_key']]);
  }
  else {
    // assemble the new link into a structured array
    $new_link = array(
      'title' => $form_state['values']['title'],
      'path' => $form_state['values']['path'],
      'group' => $form_state['values']['group'],
      'machine_name' => '',
      'icon_library' => '',
      'weight' => $form_state['values']['group'],
    );
    // if the user has added an icon then add that to the link array
    if (isset($form_state['values']['machine_name']) && $form_state['values']['machine_name'] != '') {
      $new_link['machine_name'] = $form_state['values']['machine_name'];
      $new_link['icon_library'] = $form_state['values']['icon_library'];
    }

    // updating an existing link
    if (isset($form_state['link_key']) && $action == 'update') {
      $link_key = $form_state['link_key'];
      $cis_lmsless_nav_links[$link_key] = $new_link;
    }
    // creating a new link
    elseif ($action == 'create') {
      $cis_lmsless_nav_links[] = $new_link;
    }
  }

  // set the variable
  variable_set('cis_lmsless_nav_links', $cis_lmsless_nav_links);
}