<?php
/**
 * @file
 * Administrative page callbacks for the CIS LMS-less Nav module.
 */

/**
 * CIS LMS-less admin configuration form.
 */
function cis_lmsless_nav_admin_form($form, &$form_state) {
  $form['table'] = array(
    '#type' => 'markup',
    '#markup' => _cis_lmsless_nav_admin_form_table($form, $form_state),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

function _cis_lmsless_nav_admin_form_table(&$form, &$form_state) {
  $links = variable_get('cis_lmsless_nav_links', NULL);

    if (!is_null($links) && !empty($links)) {
      $output = '';
      drupal_add_tabledrag('cis-lmsless-nav-admin-form-table', 'order', 'sibling', 'cis_lmsless_nav_weight', NULL, NULL, FALSE);
      $table = array();
      $header = array(
        array('data' => t('title')),
        array('data' => t('path')),
        array('data' => t('group')),
        array('data' => t('machine_name')),
        array('data' => t('icon_library')),
        array('data' => t('edit')),
        array('data' => t('delete')),
        array('data' => t('weight')),
      );
      $rows = array();

      foreach ($links as $link_key => $link_array) {
        // Add row weights
        $form[$link_key]['weight'] = array(
          '#type' => 'weight',
          '#title' => t('Weight'),
          '#default_value' => $link_key,
          '#attributes' => array(
            'class' => array('cis_lmsless_nav_weight'),
          ),
          '#delta' => 10,
          '#title_display' => 'invisible'
        );

        $rows[$link_key]['data'][] = theme('indentation', array('size' => 0)) . $link_array['title'];
        $rows[$link_key]['data'][] = $link_array['path'];
        $rows[$link_key]['data'][] = $link_array['group'];
        $rows[$link_key]['data'][] = $link_array['machine_name'];
        $rows[$link_key]['data'][] = $link_array['icon_library'];
        $rows[$link_key]['data'][] = l('edit', 'admin/config/elmsln/cis-lmsless-nav/edit-link/' . $link_key);
        $rows[$link_key]['data'][] = l('delete', 'admin/config/elmsln/cis-lmsless-nav/delete-link/' . $link_key);
        $rows[$link_key]['data'][] = drupal_render_children($form[$link_key]['weight']);
        $rows[$link_key]['class'] = array('draggable');
      }

      $output .= l('Add new link', 'admin/config/elmsln/cis-lmsless-nav/add-link');
      $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'cis-lmsless-nav-admin-form-table')));
      return render($output);
    }
    else {
      $output = t('There are no links currently set. ') . l('Add new link', 'admin/config/elmsln/cis-lmsless-nav/add-link');
      return $output;
    }
}

/**
 * Implements hook_form().
 */
function cis_lmsless_nav_admin_config_page_form($node, &$form_state) {
  $links = variable_get('cis_lmsless_nav_links', NULL);

  foreach ($links as $key => $link) {
    $form[$key]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $key,
      '#attributes' => array(
        'class' => array('weight'),
      ),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

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

function _cis_lmsless_nav_array_unshift_assoc(&$arr, $key, $val) {
    $arr = array_reverse($arr, true);
    $arr[$key] = $val;
    $arr = array_reverse($arr, true);
    return count($arr);
}