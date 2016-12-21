<?php

/**
 * @file
 * Contains administrative pages for creating, editing, and deleting flags.
 */

/**
 * Flag administration page. Display a list of existing flags.
 */
function flag_admin_page() {
  $flags = flag_get_flags();
  $default_flags = flag_get_default_flags(TRUE);
  $flag_admin_listing = drupal_get_form('flag_admin_listing', $flags);
  return theme('flag_admin_page', array(
    'flags' => $flags,
    'default_flags' => $default_flags,
    'flag_admin_listing' => $flag_admin_listing,
  ));
}

/**
 * A form for ordering the weights of all the active flags in the system.
 */
function flag_admin_listing($form, &$form_state, $flags) {
  $form['#flags'] = $flags;
  $form['#tree'] = TRUE;

  foreach ($flags as $flag) {
    $form['flags'][$flag->name]['weight'] = array(
      '#type' => 'weight',
      '#delta' => count($flags) + 5,
      '#default_value' => $flag->weight,
      '#attributes' => array('class' => array('flag-weight')),
    );
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );

  if (count($flags) == 1) {
    // Don't show weights with only one flag.
    unset($form['flags'][$flag->name]['weight']);
  }
  elseif (count($flags) > 1) {
    // Only show the form button if there are several flags.
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save flag order'),
    );
  }

  return $form;
}

/**
 * Submit handler for the flag_admin_listing form. Save flag weight ordering.
 */
function flag_admin_listing_submit($form, &$form_state) {
  foreach ($form['#flags'] as $flag) {
    if ($flag->weight != $form_state['values']['flags'][$flag->name]['weight']) {
      $flag->weight = $form_state['values']['flags'][$flag->name]['weight'];
      $flag->save();
    }
  }
}

/**
 * Theme the output of the normal, database flags into a table.
 */
function theme_flag_admin_listing($variables) {
  $form = $variables['form'];
  $flags = $form['#flags'];

  $output = '';

  foreach ($flags as $flag) {
    $ops = array(
      'flags_edit' => array('title' => t('edit'), 'href' => $flag->admin_path('edit')),
      'flags_fields' => array('title' => t('manage fields'), 'href' => $flag->admin_path('fields')),
      'flags_delete' => array('title' => t('delete'), 'href' => $flag->admin_path('delete')),
      'flags_export' => array('title' => t('export'), 'href' => $flag->admin_path('export')),
    );
    if (!module_exists('field_ui')) {
      unset($ops['flags_fields']);
    }
    $permission = "flag $flag->name";
    $roles = user_roles(FALSE, $permission);
    $row = array();
    $row[] = check_plain($flag->title) . ' <small>(' . t('Machine name: @name', array('@name' => $flag->name)) . ')</small>';
    if (count($flags) > 1) {
      $row[] = drupal_render($form['flags'][$flag->name]['weight']);
    }
    $row[] = $flag->entity_type;
    $row[] = empty($roles) ? '<em>' . t('No roles') . '</em>' : implode(', ', $roles);
    $row[] = $flag->types ? implode(', ', $flag->types) : '-';
    $row[] = $flag->global ? t('Yes') : t('No');
    $row[] = theme('links', array('links' => $ops));

    $rows[] = array(
      'data' => $row,
      'class' => array('draggable'),
    );
  }
  if (!$flags) {
    $rows[] = array(
      array('data' => t('No flags are currently defined.'), 'colspan' => 7),
    );
  }
  elseif (count($flags) > 1) {
    drupal_add_tabledrag('flag-admin-listing-table', 'order', 'sibling', 'flag-weight');
  }

  $header = array(t('Flag'));
  if (count($flags) > 1) {
    $header[] = t('Weight');
  }
  $header = array_merge($header, array(
    t('Flag type'),
    t('Roles'),
    t('Entity bundles'),
    t('Global?'),
    t('Operations'),
  ));
  $output .= theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'flag-admin-listing-table'),
  ));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Theme the list of disabled flags into a table.
 */
function theme_flag_admin_listing_disabled($variables) {
  $flags = $variables['flags'];
  $default_flags = $variables['default_flags'];
  $output = '';

  // Build a list of disabled, module-based flags.
  $rows = array();
  foreach ($default_flags as $name => $flag) {
    if (!isset($flags[$name])) {
      $ops = array();
      if (!$flag->is_compatible()) {
        $flag_updates_needed = TRUE;
        $ops['flags_update'] = array(
          'title' => '<strong>' . t('update code') . '</strong>',
          'href' => $flag->admin_path('update'),
          'html' => TRUE,
        );
      }
      else {
        $ops['flags_enable'] = array('title' => t('enable'), 'href' => $flag->admin_path('edit'));
      }
      // $flag->roles['flag'] not exist on older flags.
      $roles = array_flip(array_intersect(array_flip(user_roles()), !empty($flag->roles['flag']) ? $flag->roles['flag'] : array()));
      $rows[] = array(
        $flag->name,
        $flag->module,
        $flag->entity_type ? $flag->entity_type : t('Unknown'),
        theme('links', array('links' => $ops)),
      );
    }
  }

  if (isset($flag_updates_needed)) {
    drupal_set_message(t('Some flags provided by modules need to be updated to a new format before they can be used with this version of Flag. See the disabled flags for a list of flags that need updating.'), 'warning');
  }

  if (!empty($rows)) {
    $header = array(
      t('Disabled Flags'),
      t('Module'),
      t('Flag type'),
      t('Operations'),
    );
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
  }

  return $output;
}

/**
 * Theme the output for the main flag administration page.
 */
function theme_flag_admin_page($variables) {
  $flags = $variables['flags'];
  $default_flags = $variables['default_flags'];

  $output = '';

  $output .= drupal_render($variables['flag_admin_listing']);
  $output .= theme('flag_admin_listing_disabled', array('flags' => $flags, 'default_flags' => $default_flags));

  if (!module_exists('views')) {
    $output .= '<p>' . t('The <a href="@views-url">Views</a> module is not installed, or not enabled. It is recommended that you install the Views module to be able to easily produce lists of flagged content.', array('@views-url' => url('http://drupal.org/project/views'))) . '</p>';
  }
  else {
    $output .= '<p>';
    $output .= t('Lists of flagged content can be displayed using views. You can configure these in the <a href="@views-url">Views administration section</a>.', array('@views-url' => url('admin/structure/views')));
    if (flag_get_flag('bookmarks')) {
      $output .= ' ' . t('Flag module automatically provides a few <a href="@views-url">default views for the <em>bookmarks</em> flag</a>. You can use these as templates by cloning these views and then customizing as desired.', array('@views-url' => url('admin/structure/views', array('query' => array('tag' => 'flag')))));
    }
    $output .= ' ' . t('The <a href="@flag-handbook-url">Flag module handbook</a> contains extensive <a href="@customize-url">documentation on creating customized views</a> using flags.', array('@flag-handbook-url' => 'http://drupal.org/handbook/modules/flag', '@customize-url' => 'http://drupal.org/node/296954'));
    $output .= '</p>';
  }

  if (!module_exists('flag_actions')) {
    $output .= '<p>' . t('Flagging an item may trigger <em>actions</em>. However, you don\'t have the <em>Flag actions</em> module <a href="@modules-url">enabled</a>, so you won\'t be able to enjoy this feature.', array('@actions-url' => url(FLAG_ADMIN_PATH . '/actions'), '@modules-url' => url('admin/modules'))) . '</p>';
  }
  else {
    $output .= '<p>' . t('Flagging an item may trigger <a href="@actions-url">actions</a>.', array('@actions-url' => url(FLAG_ADMIN_PATH . '/actions'))) . '</p>';
  }

  if (!module_exists('rules')) {
    $output .= '<p>' . t('Flagging an item may trigger <em>rules</em>. However, you don\'t have the <a href="@rules-url">Rules</a> module enabled, so you won\'t be able to enjoy this feature. The Rules module is a more extensive solution than Flag actions.', array('@rules-url' => url('http://drupal.org/node/407070'))) . '</p>';
  }
  else {
    $output .= '<p>' . t('Flagging an item may trigger <a href="@rules-url">rules</a>.', array('@rules-url' => url('admin/config/workflow/rules'))) . '</p>';
  }

  $output .= '<p>' . t('To learn about the various ways to use flags, please check out the <a href="@handbook-url">Flag module handbook</a>.', array('@handbook-url' => 'http://drupal.org/handbook/modules/flag')) . '</p>';

  return $output;
}

/**
 * Menu callback for adding a new flag.
 *
 * @param string|NULL $entity_type
 *  The entity type for the new flag, taken from the path argument. If not
 *  present (i.e., '/add'), a form showing all possible flag types is shown.
 *  Otherwise, this shows a form for adding af flag the given type.
 *
 * @see flag_add_form()
 * @see flag_form()
 */
function flag_add_page($entity_type = NULL) {
  if (isset($entity_type)) {
    $flag = flag_flag::factory_by_entity_type($entity_type);
    // Mark the flag as new.
    $flag->is_new = TRUE;
    $type_info = flag_fetch_definition($entity_type);
    drupal_set_title(t('Add new @type flag', array('@type' => $type_info['title'])));
    return drupal_get_form('flag_form', $flag);
  }

  drupal_set_title(t('Select flag type'));
  return drupal_get_form('flag_add_form');
}

/**
 * Present a form for creating a new flag, setting the type of flag.
 */
function flag_add_form($form, &$form_state) {
  $types = array();
  foreach (flag_fetch_definition() as $type => $info) {
    $types[$type] = $info['title'] . '<div class="description">' . $info['description'] . '</div>';
  }

  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Flag type'),
    '#default_value' => 'node',
    '#description' => t('The type of object this flag will affect. This cannot be changed once the flag is created.'),
    '#required' => TRUE,
    '#options' => $types,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Continue'),
  );

  return $form;
}

function flag_add_form_validate($form, &$form_state) {
  $flag = flag_flag::factory_by_entity_type($form_state['values']['type']);
  if (get_class($flag) == 'flag_broken') {
    form_set_error('type', t("This flag type, %type, isn't valid.", array('%type' => $form_state['values']['type'])));
  }
}

function flag_add_form_submit($form, &$form_state) {
  $form_state['redirect'] = FLAG_ADMIN_PATH . '/add/' . $form_state['values']['type'];
}

/**
 * Add/Edit flag page.
 */
function flag_form($form, &$form_state, $flag) {
  $form['#flag'] = $flag;
  $form['#flag_name'] = $flag->name;

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $flag->title,
    '#description' => t('A short, descriptive title for this flag. It will be used in administrative interfaces to refer to this flag, and in page titles and menu items of some <a href="@insite-views-url">views</a> this module provides (theses are customizable, though). Some examples could be <em>Bookmarks</em>, <em>Favorites</em>, or <em>Offensive</em>.', array('@insite-views-url' => url('admin/structure/views'))),
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -3,
  );

  $form['name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Machine name'),
    '#default_value' => $flag->name,
    '#description' => t('The machine-name for this flag. It may be up to 32 characters long and may only contain lowercase letters, underscores, and numbers. It will be used in URLs and in all API calls.'),
    '#maxlength' => 32,
    '#weight' => -2,
    '#machine_name' => array(
      'exists' => 'flag_get_flag',
      'source' => array('title'),
    ),
  );

  $form['global'] = array(
    '#type' => 'checkbox',
    '#title' => t('Global flag'),
    '#default_value' => $flag->global,
    '#description' => t('If checked, flag is considered "global" and each entity is either flagged or not. If unchecked, each user has individual flags on entities.'),
    '#weight' => -1,
  );
  // Don't allow the 'global' checkbox to be changed when flaggings exist:
  // there are too many unpleasant consequences in either direction.
  // @todo: Allow this, but with a confirmation form, assuming anyone actually
  // needs this feature.
  if (!empty($flag->fid) && flag_get_flag_counts($flag->name)) {
    $form['global']['#disabled'] = TRUE;
    $form['global']['#description'] .= '<br />' . t('This setting cannot be changed when flaggings exist for this flag.');
  }

  $form['messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Messages'),
  );

  $form['messages']['flag_short'] = array(
    '#type' => 'textfield',
    '#title' => t('Flag link text'),
    '#default_value' => !empty($flag->flag_short) ? $flag->flag_short : t('Flag this item'),
    '#description' => t('The text for the "flag this" link for this flag.'),
    '#required' => TRUE,
  );

  $form['messages']['flag_long'] = array(
    '#type' => 'textfield',
    '#title' => t('Flag link description'),
    '#default_value' => $flag->flag_long,
    '#description' => t('The description of the "flag this" link. Usually displayed on mouseover.'),
  );

  $form['messages']['flag_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Flagged message'),
    '#default_value' => $flag->flag_message,
    '#description' => t('Message displayed after flagging content. If JavaScript is enabled, it will be displayed below the link. If not, it will be displayed in the message area.'),
  );

  $form['messages']['unflag_short'] = array(
    '#type' => 'textfield',
    '#title' => t('Unflag link text'),
    '#default_value' => !empty($flag->unflag_short) ? $flag->unflag_short : t('Unflag this item'),
    '#description' => t('The text for the "unflag this" link for this flag.'),
    '#required' => TRUE,
  );

  $form['messages']['unflag_long'] = array(
    '#type' => 'textfield',
    '#title' => t('Unflag link description'),
    '#default_value' => $flag->unflag_long,
    '#description' => t('The description of the "unflag this" link. Usually displayed on mouseover.'),
  );

  $form['messages']['unflag_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Unflagged message'),
    '#default_value' => $flag->unflag_message,
    '#description' => t('Message displayed after content has been unflagged. If JavaScript is enabled, it will be displayed below the link. If not, it will be displayed in the message area.'),
  );

  $form['messages']['tokens_help'] = array(
    '#title' => t('Token replacement'),
    '#type' => 'fieldset',
    '#description' =>
    '<p>' . t('The above six texts may contain any of the tokens listed below. For example, <em>"Flag link text"</em> could be entered as:') . '</p>' .
    theme('item_list', array(
      'items' => array(
        t('Add &lt;em&gt;[node:title]&lt;/em&gt; to your favorites'),
        t('Add this [node:type] to your favorites'),
        t('Vote for this proposal ([node:flag-vote-count] people have already done so)'),
      ),
      'attributes' => array('class' => array('token-examples')),
    )) .
    '<p>' . t('These tokens will be replaced with the appropriate fields from the node (or user, or comment).') . '</p>' .
    theme('flag_tokens_browser', array('types' => $flag->get_labels_token_types())),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['access'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flag access'),
    '#tree' => FALSE,
    '#weight' => 10,
  );

  // Flag classes will want to override this form element.
  $form['access']['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Flaggable types'),
    '#options' => array(),
    '#default_value' => $flag->types,
    '#description' => t('Check any sub-types that this flag may be used on.'),
    '#required' => TRUE,
    '#weight' => 10,
  );

  // Disabled access breaks checkboxes unless #value is hard coded.
  if (!empty($flag->locked['types'])) {
    $form['access']['types']['#value'] = $flag->types;
  }

  // Load the user permissions into the flag.
  if (isset($flag->fid)) {
    $flag->fetch_roles();
  }
  elseif (isset($flag->import_roles)) {
    // Convert the roles data from old API 2 flags that have been run through
    // the update system.
    // @see FlagUpdate_2::update()
    $flag->roles = $flag->import_roles;
  }
  else {
    // For new flags, provide a reasonable default value.
    $flag->roles = array(
      'flag' => array(DRUPAL_AUTHENTICATED_RID),
      'unflag' => array(DRUPAL_AUTHENTICATED_RID),
    );
  }

  $form['access']['roles'] = array(
    '#title' => t('Roles that may use this flag'),
    '#description' => t('Users may only unflag content if they have access to flag the content initially. Checking <em>authenticated user</em> will allow access for all logged-in users.'),
    '#theme' => 'flag_form_roles',
    '#theme_wrappers' => array('form_element'),
    '#weight' => -2,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'flag') . '/theme/flag-admin.js'),
      'css' => array(drupal_get_path('module', 'flag') . '/theme/flag-admin.css'),
    ),
  );
  if (module_exists('session_api')) {
    $form['access']['roles']['#description'] .= ' ' . t('Support for anonymous users is being provided by <a href="http://drupal.org/project/session_api">Session API</a>.');
  }
  else {
    $form['access']['roles']['#description'] .= ' ' . t('Anonymous users may flag content if the <a href="http://drupal.org/project/session_api">Session API</a> module is installed.');
  }

  $form['access']['roles']['flag'] = array(
    '#type' => 'checkboxes',
    '#options' => user_roles(!module_exists('session_api')),
    '#default_value' => $flag->roles['flag'],
    '#parents' => array('roles', 'flag'),
  );
  $form['access']['roles']['unflag'] = array(
    '#type' => 'checkboxes',
    '#options' => user_roles(!module_exists('session_api')),
    '#default_value' => $flag->roles['unflag'],
    '#parents' => array('roles', 'unflag'),
  );

  $form['access']['unflag_denied_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Unflag not allowed text'),
    '#default_value' => $flag->unflag_denied_text,
    '#description' => t('If a user is allowed to flag but not unflag, this text will be displayed after flagging. Often this is the past-tense of the link text, such as "flagged".'),
    '#weight' => -1,
  );

  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display options'),
    '#description' => t('Flags are usually controlled through links that allow users to toggle their behavior. You can choose how users interact with flags by changing options here. It is legitimate to have none of the following checkboxes ticked, if, for some reason, you wish <a href="@placement-url">to place the the links on the page yourself</a>.', array('@placement-url' => 'http://drupal.org/node/295383')),
    '#tree' => FALSE,
    '#weight' => 20,
    '#after_build' => array('flag_link_type_options_states'),
  );

  $form['display']['link_type'] = array(
    '#type' => 'radios',
    '#title' => t('Link type'),
    '#options' => _flag_link_type_options(),
    '#after_build' => array('flag_check_link_types'),
    '#default_value' => $flag->link_type,
    // Give this a high weight so additions by the flag classes for entity-
    // specific options go above.
    '#weight' => 18,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'flag') . '/theme/flag-admin.js'),
    ),
    '#attributes' => array(
      'class' => array('flag-link-options'),
    ),
  );
  // Add the descriptions to each ratio button element. These attach to the
  // elements when FormAPI expands them.
  foreach (_flag_link_type_descriptions() as $key => $description) {
    $form['display']['link_type'][$key]['#description'] = $description;
  }

  $form['display']['link_options_intro'] = array(
    // This is a hack to allow a markup element to use FormAPI states.
    // @see http://www.bywombats.com/blog/06-25-2011/using-containers-states-enabled-markup-form-elements
    '#type' => 'container',
    '#children' => '<p id="link-options-intro">' . t('The selected link type may require these additional settings:') . '</p>',
    '#weight' => 20,
  );

  $form['display']['link_options_confirm'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options for the "Confirmation form" link type'),
    // Any "link type" provider module must put its settings fields inside
    // a fieldset whose HTML ID is link-options-LINKTYPE, where LINKTYPE is
    // the machine-name of the link type. This is necessary for the
    // radiobutton's JavaScript dependency feature to work.
    '#id' => 'link-options-confirm',
    '#weight' => 21,
  );

  $form['display']['link_options_confirm']['flag_confirmation'] = array(
    '#type' => 'textfield',
    '#title' => t('Flag confirmation message'),
    '#default_value' => isset($flag->flag_confirmation) ? $flag->flag_confirmation : '',
    '#description' => t('Message displayed if the user has clicked the "flag this" link and confirmation is required. Usually presented in the form of a question such as, "Are you sure you want to flag this content?"'),
    // This will get changed to a state by flag_link_type_options_states().
    '#required' => TRUE,
  );

  $form['display']['link_options_confirm']['unflag_confirmation'] = array(
    '#type' => 'textfield',
    '#title' => t('Unflag confirmation message'),
    '#default_value' => isset($flag->unflag_confirmation) ? $flag->unflag_confirmation : '',
    '#description' => t('Message displayed if the user has clicked the "unflag this" link and confirmation is required. Usually presented in the form of a question such as, "Are you sure you want to unflag this content?"'),
    // This will get changed to a state by flag_link_type_options_states().
    '#required' => TRUE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save flag'),
    // We put this button on the form before calling $flag->options_form()
    // to give the flag handler a chance to remove it (e.g. flag_broken).
    '#weight' => 999,
  );

  // Add our process handler to disable access to locked properties.
  $form['#process'][] = 'flag_form_locked_process';

  // Allow the flag handler to make additions and changes to the form.
  // Note that the flag_broken handler will completely empty the form array!
  $flag->options_form($form);

  return $form;
}

/**
 * FormAPI after_build function to set states on link type options fieldsets.
 *
 * We do this in an after build so we handle further link types fieldsets from
 * other modules that provide link types.
 *
 * This expects a link type's fieldset to be $form['display'][link_options_TYPE]
 * so that can be matched up with the radio button value.
 */
function flag_link_type_options_states($element) {
  $intro_element_values_array = array();
  foreach (element_children($element) as $key) {
    if (isset($element[$key]['#type']) && $element[$key]['#type'] == 'fieldset' && substr($key, 0, 12) == 'link_options') {
      // Trim the radio value from the fieldset key. This assumed the fieldset
      // key is 'link_options_TYPE'.
      $radio_value = substr($key, 13);
      $element[$key]['#states'] = array(
        'visible' => array(
          ':input[name="link_type"]' => array('value' => $radio_value),
        ),
      );

      // If an element in a link type options fieldset is required, then we
      // remove this, as this would break the form, by demanding the user
      // enter a value for a form element they possibly can't see!
      // Instead, we set the required property as a state.
      foreach (element_children($element[$key]) as $child_key) {
        if (!empty($element[$key][$child_key]['#required'])) {
          $element[$key][$child_key]['#required'] = FALSE;
          $element[$key][$child_key]['#states']['required'] = array(
            ':input[name="link_type"]' => array('value' => $radio_value),
          );
        }
      }

      // Gather up the radio values for the format we need for a multiple
      // value state.
      $intro_element_values_array[] = array('value' => $radio_value);
    }
  }

  $element['link_options_intro']['#states'] = array(
    'visible' => array(
      ':input[name="link_type"]' => $intro_element_values_array,
    ),
  );

  return $element;
}

/**
 * Form process handler for locking flag properties.
 *
 * Flags defined in code may define an array of properties in $flag->locked that
 * are to be locked and may not be edited by the user.
 */
function flag_form_locked_process($element, &$form_state, $form) {
  $flag = $form['#flag'];

  // Disable access to a form element whose name matches a locked flag property.
  if (isset($element['#name']) && !empty($flag->locked[$element['#name']])) {
    $element['#access'] = FALSE;
  }

  // Recurse into the form array.
  foreach (element_children($element) as $key) {
    // Workaround for Core inconvenience: setting #process here prevents an
    // element's essential #process handlers from its hook_element_info()
    // definition from being set in form_builder().
    // @see http://drupal.org/node/1779496
    if (isset($element[$key]['#type']) && ($info = element_info($element[$key]['#type']))) {
      if (isset($info['#process'])) {
        $element[$key]['#process'] = $info['#process'];
      }
    }

    $element[$key]['#process'][] = 'flag_form_locked_process';
  }

  return $element;
}

/**
 * Add/Edit flag form validate.
 */
function flag_form_validate($form, &$form_state) {
  $form_state['values']['title'] = trim($form_state['values']['title']);
  $form_values = $form_state['values'];

  $flag = $form['#flag'];
  $flag->form_input($form_values);
  $errors = $flag->validate();
  foreach ($errors as $field => $field_errors) {
    foreach ($field_errors as $error) {
      form_set_error($field, $error['message']);
    }
  }
}

/**
 * Add/Edit flag form submit.
 */
function flag_form_submit($form, &$form_state) {
  $flag = $form['#flag'];

  $form_state['values']['title'] = trim($form_state['values']['title']);
  $flag->form_input($form_state['values']);

  $flag->save();
  $flag->enable();
  drupal_set_message(t('Flag @title has been saved.', array('@title' => $flag->get_title())));
  // We clear caches more vigorously if the flag was new.
  _flag_clear_cache($flag->entity_type, !empty($flag->is_new));

  if (!empty($flag->is_new)) {
    field_attach_create_bundle('flagging', $flag->name);
  }

  // Save permissions.
  // This needs to be done after the flag cache has been cleared, so that
  // the new permissions are picked up by hook_permission().
  // This may need to move to the flag class when we implement extra permissions
  // for different flag types: http://drupal.org/node/879988

  // If the flag machine name as changed, clean up all the obsolete permissions
  // and notify FieldAPI.
  if ($flag->name != $form['#flag_name']) {
    $old_name = $form['#flag_name'];
    $permissions = array("flag $old_name", "unflag $old_name");
    foreach (array_keys(user_roles()) as $rid) {
      user_role_revoke_permissions($rid, $permissions);
    }

    field_attach_rename_bundle('flagging', $old_name, $flag->name);
  }

  foreach (array_keys(user_roles(!module_exists('session_api'))) as $rid) {
    // Create an array of permissions, based on the checkboxes element name.
    $permissions = array(
      "flag $flag->name" => $flag->roles['flag'][$rid],
      "unflag $flag->name" => $flag->roles['unflag'][$rid],
    );
    user_role_change_permissions($rid, $permissions);
  }
  // @todo: when we add database caching for flags we'll have to clear the
  // cache again here.

  $form_state['redirect'] = FLAG_ADMIN_PATH;
}

/**
 * Output the access options for roles in a table.
 */
function theme_flag_form_roles($variables) {
  $element = $variables['element'];

  $header = array(
    array('class' => array('checkbox'), 'data' => t('Flag')),
    array('class' => array('checkbox'), 'data' => t('Unflag')),
    t('Role'),
  );
  $rows = array();
  foreach (element_children($element['flag']) as $role) {
    $row = array();
    $role_name = $element['flag'][$role]['#title'];
    unset($element['flag'][$role]['#title']);
    unset($element['unflag'][$role]['#title']);
    $element['flag'][$role]['#attributes']['class'] = array('flag-access');
    $element['unflag'][$role]['#attributes']['class'] = array('unflag-access');
    $row[] = array('class' => array('checkbox'), 'data' => drupal_render($element['flag'][$role]));
    $row[] = array('class' => array('checkbox'), 'data' => drupal_render($element['unflag'][$role]));
    $row[] = $role_name;
    $rows[] = $row;
  }

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(
      'class' => array('flag-admin-table'),
      'id' => 'flag-roles',
    ),
  ));
}

/**
 * Delete flag page.
 */
function flag_delete_confirm($form, &$form_state, $flag) {
  $form['#flag'] = $flag;

  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $flag->get_title())),
    !empty($_GET['destination']) ? $_GET['destination'] : FLAG_ADMIN_PATH,
    isset($flag->module) ? t('This flag is provided by the %module module. It will lose any customizations and be disabled.', array('%module' => $flag->module)) : t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

function flag_delete_confirm_submit($form, &$form_state) {
  $flag = $form['#flag'];
  if ($form_state['values']['confirm']) {
    $flag->delete();
    $flag->disable();
    _flag_clear_cache($flag->entity_type, TRUE);
  }
  drupal_set_message(t('Flag @name has been deleted.', array('@name' => $flag->get_title())));
  $form_state['redirect'] = FLAG_ADMIN_PATH;
}

/**
 * FormAPI after_build function to check that the link type exists.
 */
function flag_check_link_types($element) {
  $link_types = flag_get_link_types();
  if (!isset($link_types[$element['#value']])) {
    drupal_set_message(t('This flag uses a link type of %type, which does not exist.', array('%type' => $element['#value'])), 'error');
  }
  return $element;
}

/**
 * Clears various caches when one or more flags are modified.
 *
 * @param string|array $entity_types
 *  The entity types for the flags. May be a single value or an array.
 * @param bool $is_insert_or_delete
 *  Whether the modified flag is being inserted (saved for the first time) or
 *  deleted. This results in a more vigorous clearing of caches. In
 *  particular, when no flags exist yet, no Field admin UI paths exist and these
 *  need to be created.
 */
function _flag_clear_cache($entity_types, $is_insert_or_delete = FALSE) {
  if (!is_array($entity_types)) {
    $entity_types = array($entity_types);
  }

  // Reset our flags cache, thereby making the following code aware of the
  // modifications.
  drupal_static_reset('flag_get_flags');

  if ($is_insert_or_delete) {
    // A new or deleted flag means we are changing bundles on the Flagging
    // entity, and thus need to clear the entity info cache.
    entity_info_cache_clear();
  }

  // Clear FieldAPI's field_extra cache, so our changes to pseudofields are
  // noticed. It's rather too much effort to both a) check whether the
  // pseudofield setting has changed either way, and b) specifically clear just
  // the bundles that are (or were!!) affected, so we just clear for all bundles
  // on our entity type regardlesss.
  foreach ($entity_types as $entity_type) {
    cache_clear_all("field_info:bundle_extra:$entity_type:", 'cache_field', TRUE);
  }

  if (module_exists('views')) {
    views_invalidate_cache();
  }

  // The title of a flag may appear in the menu (indirectly, via our "default
  // views"), so we need to clear the menu cache. This call also clears the
  // page cache, which is desirable too because the flag labels may have
  // changed.
  menu_rebuild();
}
