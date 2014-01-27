<?php

/**
 * Menu callback to configure module settings.
 */
function clone_settings($form, &$form_state) {

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  $form['basic']['clone_method'] = array(
    '#type' => 'radios',
    '#title' => t('Method to use when cloning a node'),
    '#options' => array('prepopulate' => t('Pre-populate the node form fields'), 'save-edit' => t('Save as a new node then edit')),
    '#default_value' => variable_get('clone_method', 'prepopulate'),
  );
  $form['basic']['clone_nodes_without_confirm'] = array(
    '#type' => 'radios',
    '#title' => t('Confirmation mode when using the "Save as a new node then edit" method'),
    '#default_value' => (int)variable_get('clone_nodes_without_confirm', 0),
    '#options' => array(t('Require confirmation (recommended)'), t('Bypass confirmation')),
    '#description' => t('A new node may be saved immediately upon clicking the "clone" tab when viewing a node, bypassing the normal confirmation form.'),
  );
  $form['basic']['clone_menu_links'] = array(
    '#type' => 'radios',
    '#title' => t('Clone menu links'),
    '#options' => array(0 => t('No'), 1 => t('Yes')),
    '#default_value' => (int) variable_get('clone_menu_links', 0),
    '#description' => t('Should any menu link for a node also be cloned?'),
  ); 
  $form['basic']['clone_use_node_type_name'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use node type name in clone link'),
    '#default_value' => (int) variable_get('clone_use_node_type_name', 0),
    '#description' => t('If checked, the link to clone the node will contain the node type name, for example, "Clone this article", otherwise it will read "Clone content".'),
  );

  $form['publishing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Should the publishing options ( e.g. published, promoted, etc) be reset to the defaults?'),
  );
  $types = node_type_get_names();

  foreach ($types as $type => $name) {
    $form['publishing']['clone_reset_'. $type] = array(
      '#type' => 'checkbox',
      '#title' => t('@s: reset publishing options when cloned', array('@s' => $name)),
      '#default_value' => variable_get('clone_reset_'. $type, FALSE),
    );
  }

  // Need the variable default key to be something that's never a valid node type.
  $form['omit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types that are not to be cloned - omitted due to incompatibility'),
  );
  $form['omit']['clone_omitted'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Omitted content types'),
    '#default_value' => variable_get('clone_omitted', array()),
    '#options' => $types,
    '#description' => t('Select any node types which should <em>never</em> be cloned. Typically you should will want to select here all node types for which cloning fails (e.g. image nodes).'),
  );

  return system_settings_form($form);
}

/**
 *  Menu callback: prompt the user to confirm the operation
 */
function clone_node_check($node) {

  $method = variable_get('clone_method', 'prepopulate');
  
  switch ($method) {
    case 'save-edit':
      if (variable_get('clone_nodes_without_confirm', FALSE)) {
        $new_nid = clone_node_save($node->nid);
        drupal_goto('node/'. $new_nid .'/edit');
      }
      else {
        return drupal_get_form('clone_node_confirm', $node);
      }
      break;
    case 'prepopulate':
    default:
      return clone_node_prepopulate($node);
      break;
  }
}

/**
 *  form builder: prompt the user to confirm the operation
 */
function clone_node_confirm($form, &$form_state, $node) {

    $form['nid'] = array('#type' => 'value', '#value' => $node->nid);
    return confirm_form($form,
      t('Are you sure you want to clone %title?', array('%title' =>  $node->title)),
      'node/'. $node->nid, '<p>'. t('This action will create a new node. You will then be redirected to the edit page for the new node.') .'</p>',
      t('Clone'), t('Cancel'));
}

/**
 *  Handle confirm form submission
 */
function clone_node_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $new_nid = clone_node_save($form_state['values']['nid']);
  }
  $form_state['redirect'] = 'node/'. $new_nid .'/edit';
}


/**
 * Create a new menu link cloned from another node.
 *
 * Returns NULL if no existing link, or links are not to be cloned.
 */
function clone_node_clone_menu_link($node) {
  if (variable_get('clone_menu_links', FALSE) && function_exists('menu_node_prepare')) {
    // This will fetch the existing menu link if the node had one.
    menu_node_prepare($node);

    if (!empty($node->menu['mlid'])) {
      $old_link = $node->menu;
      $link['link_title'] = t('Clone of !title', array('!title' => $old_link['link_title']));
      $link['plid'] = $old_link['plid'];
      $link['menu_name'] = $old_link['menu_name'];
      $link['weight'] = $old_link['weight'];
      $link['module'] = $old_link['module'];
      return $link;
    }
  }
  return NULL;
}

/**
 *  Clones a node - prepopulate a node editing form
 */
function clone_node_prepopulate($original_node) {
  if (isset($original_node->nid)) {
    global $user;

    if (clone_is_permitted($original_node->type)) {
      $node = clone $original_node;

      $node->nid = NULL;
      $node->vid = NULL;
      $node->tnid = NULL;
      // Anyonmymous users don't have a name.
      // @see: drupal_anonymous_user().
      $node->name = isset($user->name) ? $user->name : NULL;
      $node->uid = $user->uid;
      $node->created = NULL;
      $node->menu = clone_node_clone_menu_link($original_node);
      if (isset($node->book['mlid'])) {
        $node->book['mlid'] = NULL;
        $node->book['has_children'] = 0;
      }
      $node->path = NULL;
      $node->files = array();
      $node->title = t('Clone of !title', array('!title' => $node->title));
      // Add an extra property as a flag.
      $node->clone_from_original_nid = $original_node->nid;
      drupal_set_title($node->title);

      if (variable_get('clone_reset_'. $node->type, FALSE)) {
        $node_options = variable_get('node_options_'. $node->type, array('status', 'promote'));
        // Fill in the default values.
        foreach (array('status', 'moderate', 'promote', 'sticky', 'revision') as $key) {
          // Cast to int since that's how they come out of the DB.
          $node->$key = (int) in_array($key, $node_options);
        }
      }
      // Let other modules do special fixing up.
      $context = array('method' => 'prepopulate', 'original_node' => $original_node);
      drupal_alter('clone_node', $node, $context);
      // Make sure the file defining the node form is loaded.
      $form_state = array();
      $form_state['build_info']['args'] = array($node);
      form_load_include($form_state, 'inc', 'node', 'node.pages');
      return drupal_build_form($node->type .'_node_form', $form_state);
    }
  }
}

/**
 *  Clones a node by directly saving it.
 */
function clone_node_save($nid) {
  if (is_numeric($nid)) {
    global $user;

    $node = node_load($nid);
    if (isset($node->nid) && clone_is_permitted($node->type)) {
      $original_node = clone $node;

      $node->nid = NULL;
      $node->vid = NULL;
      $node->tnid = NULL;
      // Anyonmymous users don't have a name.
      // @see: drupal_anonymous_user().
      $node->name = isset($user->name) ? $user->name : NULL;
      $node->uid = $user->uid;
      $node->created = NULL;
      $node->menu = clone_node_clone_menu_link($original_node);
      if (isset($node->book['mlid'])) {
        $node->book['mlid'] = NULL;
        $node->book['has_children'] = 0;
      }
      $node->path = NULL;
      $node->files = array();
      $node->title = t('Clone of !title', array('!title' => $node->title));
      // Add an extra property as a flag.
      $node->clone_from_original_nid = $original_node->nid;

      if (variable_get('clone_reset_'. $node->type, FALSE)) {
        $node_options = variable_get('node_options_'. $node->type, array('status', 'promote'));
        // Fill in the default values.
        foreach (array('status', 'moderate', 'promote', 'sticky', 'revision') as $key) {
          // Cast to int since that's how they need to be saved to the DB.
          $node->$key = (int) in_array($key, $node_options);
        }
      }
      // Let other modules do special fixing up.
      $context = array('method' => 'save-edit', 'original_node' => $original_node);
      drupal_alter('clone_node', $node, $context);

      node_save($node);
      return $node->nid;
    }
  }
}

