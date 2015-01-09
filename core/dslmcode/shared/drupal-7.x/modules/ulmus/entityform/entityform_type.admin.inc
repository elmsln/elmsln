<?php
define('ENTITYFORM_TYPE_DEFAULT_PROP_TEXT', 'Leave this field blank to use default setting. Use &lt;none&gt; to show no text');
/**
 * @file
 * Entityform type editing UI.
 */

/**
 * UI controller.
 */
class EntityformTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage entityform entity types, including adding and removing fields and the display of fields.';
    $items[$this->path]['type'] = MENU_NORMAL_ITEM;
    $items[$this->path . '/manage/%entity_object/edit']['context'] = MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE;
    return $items;
  }

  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $row = parent::overviewTableRow($conditions, $id, $entity, $additional_cols);
    $row[] = l(t('Submissions'), $this->path . '/manage/' . $id . '/submissions');
    $row[] = l(t('Submit Link'), entity_ui_controller('entityform')->submit_path($id));
    return $row;
  }

  public function overviewTable($conditions = array()) {
    $render = parent::overviewTable($conditions);
    $render['#header'][] = t('Submissions');
    $render['#header'][] = t('Submit Link');
    return $render;
  }
}

/**
 * Generates the entityform type editing form.
 */
function entityform_type_form($form, &$form_state, $entityform_type, $op = 'edit') {

  if ($op == 'clone') {
    $entityform_type->label .= ' (cloned)';
    $entityform_type->type = '';
  }
  if ($op == 'add') {
    // Clear so most defaults.  Allows entityform type to use defaults.
    $entityform_type->clear_text_props();
  }
  $form = _entityform_type_settings_elements($entityform_type, $op);
  entityform_type_prepare_edit($entityform_type);
  $form['#entityform_type'] = $entityform_type;
  $form['label'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => $entityform_type->label,
    '#description' => t('The human-readable name of this Entityform Type.  This text will be displayed as part of the list in the Entityform Types page.  This name must be unqiue.'),
    '#required' => TRUE,
    '#size' => 30,
    '#weight' => -50,
    '#maxlength' => 255,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($entityform_type->type) ? $entityform_type->type : '',
    '#maxlength' => 32,
    //    '#disabled' => $entityform_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'entityform_type_load',
      'source' => array('label'),
    ),
    '#weight' => -49,
    '#description' => t('A unique machine-readable name for this entityform type. It must only contain lowercase letters, numbers, and underscores.'),
    // Don't allow changing machine name.
    '#access' => empty($entityform_type->type),
  );
  $form['data']['#tree'] = TRUE;

  $form['data']['redirect_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect path'),
    '#default_value' => empty($entityform_type->data['redirect_path']) ? '' : $entityform_type->data['redirect_path'],
    '#description' => t('What relative path should the user be redirected to on a correct submission?  Leave blank for default action.'),
  );
  $form['data']['instruction_pre'] = array(
    '#type' => 'text_format',
    '#title' => t('Intro form instructions'),
    '#default_value' => empty($entityform_type->data['instruction_pre']['value']) ? '' : $entityform_type->data['instruction_pre']['value'],
    '#format' => empty($entityform_type->data['instruction_pre']['format']) ? NULL : $entityform_type->data['instruction_pre']['format'],
    '#description' => t('These user instructions will appear at the top of every page within this form.'),
  );
  if (module_exists('menu')) {
    // Menu Settings
    $link = $entityform_type->menu;

    $form['menu'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu settings'),
      '#access' => user_access('administer menu'),
      '#collapsible' => TRUE,
      '#collapsed' => !$link['link_title'],
      '#group' => 'additional_settings',
      '#attached' => array(
        'js' => array(drupal_get_path('module', 'menu') . '/menu.js'),
      ),
      '#tree' => TRUE,
      '#weight' => 80,
      '#attributes' => array('class' => array('menu-link-form')),
    );
    $form['menu']['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Provide a menu link'),
      '#default_value' => (int) (bool) $link['mlid'],
    );
    $form['menu']['link'] = array(
      '#type' => 'container',
      '#parents' => array('menu'),
      '#states' => array(
        'invisible' => array(
          'input[name="menu[enabled]"]' => array('checked' => FALSE),
        ),
      ),
    );

    // Populate the element with the link data.
    foreach (array(
               'mlid',
               'module',
               'hidden',
               'has_children',
               'customized',
               'options',
               'expanded',
               'hidden'
             ) as $key) {
      $form['menu']['link'][$key] = array(
        '#type' => 'value',
        '#value' => $link[$key]
      );
    }

    $form['menu']['link']['link_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Menu link title'),
      '#default_value' => $link['link_title'],
    );

    $form['menu']['link']['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => isset($link['options']['attributes']['title']) ? $link['options']['attributes']['title'] : '',
      '#rows' => 1,
      '#description' => t('Shown when hovering over the menu link.'),
    );

    $default = ($link['mlid'] ? $link['menu_name'] . ':' . $link['plid'] : '');
    // If the current parent menu item is not present in options, use the first
    // available option as default value.
    // @todo User should not be allowed to access menu link settings in such a
    // case.
    $options = _menu_get_options(menu_get_menus(), menu_get_menus(), $link);
    if (!isset($options[$default])) {
      $array = array_keys($options);
      $default = reset($array);
    }
    $form['menu']['link']['parent'] = array(
      '#type' => 'select',
      '#title' => t('Parent item'),
      '#default_value' => $default,
      '#options' => $options,
      '#attributes' => array('class' => array('menu-parent-select')),
    );
    $form['menu']['link']['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#delta' => 50,
      '#default_value' => $link['weight'],
      '#description' => t('Menu links with smaller weights are displayed before links with larger weights.'),
    );
  }
  // Register #process function so the fieldsets aren't save in form values.
  $form['data']['#force_parents'] = array('data');
  $form['data']['#process'][] = '_entityform_remove_fieldsets_from_tree';

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save entityform type'),
    '#weight' => 40,
  );
  if (module_exists('path')) {
    $form['paths'] = array(
      '#type' => 'fieldset',
      '#title' => t('URL path settings'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($path['alias']),
      '#group' => 'additional_settings',
      '#attributes' => array(
        'class' => array('path-form'),
      ),
      '#access' => user_access('create url aliases') || user_access('administer url aliases'),
      '#weight' => 100,
      '#tree' => TRUE,
      '#element_validate' => array('_entityform_paths_form_element_validate'),
    );
    $path_types = _entityform_type_get_path_types($entityform_type->type);
    foreach ($path_types as $key => $path_type) {
      $form['paths'][$key]['alias'] = array(
        '#type' => 'textfield',
        '#title' => check_plain($path_type['title']),
        '#default_value' => isset($entityform_type->paths[$key]) ? $entityform_type->paths[$key]['alias'] : '',
        '#maxlength' => 255,
        '#description' => t($path_type['description']),
      );
    }
    $form['additional_settings'] = array(
      '#type' => 'vertical_tabs',
      '#weight' => 99,
    );
  }
  if (module_exists('token')) {
    $form['tokens'] = array(
      '#title' => t('Available Tokens'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#weight' => '39',
    );
    $form['tokens']['token_tree'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('global_types', 'entityform_type', 'entityform'),
      '#dialog' => TRUE,
    );
  }
  else {
    $form['tokens'] = array(
      '#markup' => '<p>' . t('Enable the <a href="@drupal-token">Token module</a> to view the available token browser.', array('@drupal-token' => 'http://drupal.org/project/token')) . '</p>',
    );
  }

  return $form;
}

/**
 * Prepare Entityform Type to be edited.
 * @param EntityformType $entityform_type
 */
function entityform_type_prepare_edit(&$entityform_type) {
  if (module_exists('menu') && empty($entityform_type->menu)) {
    $item = array();
    $mlid = db_query_range("SELECT mlid FROM {menu_links} WHERE link_path = :path AND module = 'entityform' ORDER BY mlid ASC", 0, 1, array(
      ':path' => _entityform_type_get_submit_url($entityform_type->type),
    ))->fetchField();
    if ($mlid) {
      $item = menu_link_load($mlid);
    }
    // Set default values.
    $entityform_type->menu = $item + array(
        'link_title' => '',
        'mlid' => 0,
        'plid' => 0,
        'menu_name' => '',
        'weight' => 0,
        'options' => array(),
        'module' => 'entityform',
        'expanded' => 0,
        'hidden' => 0,
        'has_children' => 0,
        'customized' => 0,
      );
  }
}

/**
 * Entityform global setting form
 * @param array $form
 * @param array $form_state
 * @return array
 */
function entityform_settings($form, &$form_state) {
  //choose the default View for viewing for submissions
  $defaults = entity_get_controller('entityform_type')->create(array(), TRUE);
  $form = _entityform_type_settings_elements($defaults, 'defaults');
  $form['#entityform_type'] = $defaults;

  // Call Drupal.menu_update_parent_list() to filter the list of
  // available default parent menu items based on the selected menus.
  drupal_add_js(
    '(function ($) { Drupal.menu_update_parent_list(); })(jQuery);',
    array('scope' => 'footer', 'type' => 'inline')
  );
  $form['entityform_type_defaults']['data'] = $form['data'];
  $form['entityform_type_defaults']['#tree'] = TRUE;
  $form['entityform_type_defaults']['#type'] = 'value';
  unset($form['data']);

  // Register #process function so the fieldsets aren't save in form values.
  $form['entityform_type_defaults']['data']['#process'][] = '_entityform_remove_fieldsets_from_tree';
  $form['entityform_type_defaults']['data']['#force_parents'] = array(
    'entityform_type_defaults',
    'data',
  );
  //collaspe all fieldsets
  foreach (element_children($form['entityform_type_defaults']['data']) as $key) {
    if (isset($form['entityform_type_defaults']['data'][$key]['#type']) && $form['entityform_type_defaults']['data'][$key]['#type'] == 'fieldset') {
      $form['entityform_type_defaults']['data'][$key]['#collapsed'] = TRUE;
    }
  }
  return system_settings_form($form);
}

/**
 * Create Form elements that are shared between EntityformType add/edit form and EntityformType default settings form
 * This allows default settings to set for most form settings.
 * @param $entityform_type
 * @param $op
 * @return array
 *   Form elements
 */
function _entityform_type_settings_elements($entityform_type, $op) {
  $default_value_message = $op != 'defaults' ? ' ' . ENTITYFORM_TYPE_DEFAULT_PROP_TEXT : '';
  //****************DRAFT FIELDSET SETTINGS *********************//
  $form['data']['draft_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Draft settings'),
    '#collapsible' => TRUE,
    '#group' => 'additional_settings',
    '#weight' => 60,
  );
  $form['data']['draft_set']['draftable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Draftable'),
    '#default_value' => !empty($entityform_type->data['draftable']),
    '#description' => t('Should users be able to save a draft of this form?'),
  );
  $form['data']['draft_set']['draft_redirect_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Draft Redirect path'),
    '#default_value' => empty($entityform_type->data['draft_redirect_path']) ? '' : $entityform_type->data['draft_redirect_path'],
    '#description' => t('What relative path should the user be redirected to on draft submission?  Leave blank for default action.'),
  );
  $form['data']['draft_set']['draft_button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Override draft button text'),
    '#default_value' => empty($entityform_type->data['draft_button_text']) ? '' : $entityform_type->data['draft_button_text'],
    '#description' => t('Text to use for draft save button.') . $default_value_message,
  );
  $form['data']['draft_set']['draft_save_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Draft save text'),
    '#default_value' => empty($entityform_type->data['draft_save_text']['value']) ? '' : $entityform_type->data['draft_save_text']['value'],
    '#format' => empty($entityform_type->data['draft_save_text']['format']) ? NULL : $entityform_type->data['draft_save_text']['format'],
    '#description' => t('This text will be displayed to the user when the form is saved as a draft.') . $default_value_message,
  );
  // @todo Any need for this sit now Rules removed??
  //****************FORM OVERRIDE FIELDSET SETTINGS *********************//
  // New elements must also be added to EntityformTypeController->get_default_text_values().
  $form['data']['formoverride_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form overrides'),
    '#collapsible' => TRUE,
    '#group' => 'additional_settings',
    '#weight' => 120,
  );
  $form['data']['formoverride_set']['submit_button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Submit Button Text'),
    '#default_value' => empty($entityform_type->data['submit_button_text']) ? '' : $entityform_type->data['submit_button_text'],
    '#description' => t('Text to use for submit button.') . $default_value_message,
  );
  $form['data']['formoverride_set']['submit_confirm_msg'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission Confirmation Text'),
    '#default_value' => empty($entityform_type->data['submit_confirm_msg']) ? '' : $entityform_type->data['submit_confirm_msg'],
    '#description' => t('Text to use for Submission Conformation.') . $default_value_message,
  );
  $form['data']['formoverride_set']['your_submissions'] = array(
    '#type' => 'textfield',
    '#title' => t('Your Submissions Text'),
    '#default_value' => empty($entityform_type->data['your_submissions']) ? '' : $entityform_type->data['your_submissions'],
    '#description' => t('Text to use for "Your Submissions".') . $default_value_message,
  );
  $form['data']['formoverride_set']['disallow_resubmit_msg'] = array(
    '#type' => 'textfield',
    '#title' => t('Form Disallow Resubmit Text'),
    '#default_value' => empty($entityform_type->data['disallow_resubmit_msg']) ? '' : $entityform_type->data['disallow_resubmit_msg'],
    '#description' => t('Text to use for "Your already submitted this form".') . $default_value_message,
  );
  $form['data']['formoverride_set']['delete_confirm_msg'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission Delete Text'),
    '#default_value' => empty($entityform_type->data['delete_confirm_msg']) ? '' : $entityform_type->data['delete_confirm_msg'],
    '#description' => t('Text to use for "Delete Conformation".') . $default_value_message,
  );
  $form['data']['formoverride_set']['page_title_view'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission View Title'),
    '#default_value' => empty($entityform_type->data['page_title_view']) ? '' : $entityform_type->data['page_title_view'],
    '#description' => t('Text to use for page title of submission view.') . $default_value_message,
  );

  //****************SUBMISSION PAGE FIELDSET SETTINGS *********************//
  $form['data']['submission_page_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Submission page settings'),
    '#collapsible' => TRUE,
    '#group' => 'additional_settings',
    '#weight' => 20,
  );
  $form['data']['submission_page_set']['preview_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Preview Page'),
    '#default_value' => empty($entityform_type->data['preview_page']) ? 0 : $entityform_type->data['preview_page'],
    '#description' => t('Show a Preview page.'),
  );
  $form['data']['submission_page_set']['submission_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Submission page title'),
    '#default_value' => empty($entityform_type->data['submission_page_title']) ? '' : $entityform_type->data['submission_page_title'],
    '#description' => t('Page title for correct submission.') . $default_value_message,
  );

  $form['data']['submission_page_set']['submission_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Submission reply'),
    '#default_value' => empty($entityform_type->data['submission_text']['value']) ? '' : $entityform_type->data['submission_text']['value'],
    '#format' => empty($entityform_type->data['submission_text']['format']) ? NULL : $entityform_type->data['submission_text']['format'],
    '#description' => t('This text will be displayed to the user when a correct form is submitted.') . $default_value_message,
  );
  $form['data']['submission_page_set']['submission_show_submitted'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show submission information'),
    '#default_value' => !empty($entityform_type->data['submission_show_submitted']),
    '#description' => t('Show submitted data on submission page?'),
  );
  //****************SUBMISSION VIEWS FIELDSET SETTINGS *********************//
  // Let Each entityform use a different View for viewing Submission
  $form['data']['submissions_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Submissions views'),
    '#collapsible' => TRUE,
    '#group' => 'additional_settings',
    '#weight' => 40,
  );
  $view_options = _entityform_get_entityform_views_options();
  if ($op != 'defaults') {
    $view_options['default'] = t('Use Default');
  }
  $user_view_options = $view_options;
  $user_view_options[''] = t('None');
  $submission_view = $entityform_type->data['submissions_view'];
  $user_submission_view = isset($entityform_type->data['user_submissions_view']) ? $entityform_type->data['user_submissions_view'] : '';
  $parts = explode(':', $submission_view);
  $submission_view = $parts[0];
  if ($op == 'defaults') {
    //If selected Views are no longer available select defaults.
    if (!array_key_exists($submission_view, $view_options)) {
      $submission_view = 'entityforms';
    }
    if (!array_key_exists($user_submission_view, $user_view_options)) {
      $submission_view = 'user_entityforms';
    }
  }
  $form['data']['submissions_set']['submissions_view'] = array(
    '#type' => 'select',
    '#title' => t('View for submissions reports'),
    '#description' => t('Select the View that should be used Submission reports.'),
    '#default_value' => $submission_view,
    '#options' => $view_options,
  );
  $user_view_description = 'Select the View that should be used to show users their previous submissions.';
  $user_view_description .= ' If "None" is selected then the users will not see a previous submissions link.';
  $form['data']['submissions_set']['user_submissions_view'] = array(
    '#type' => 'select',
    '#title' => t('View for current user\'s submissions'),
    '#description' => t($user_view_description),
    '#default_value' => $user_submission_view,
    '#options' => $user_view_options,
  );
  $form['entityform_default_submission_view']['#options'] = _entityform_get_entityform_views_options();
  //****************ACCESS FIELDSET SETTINGS *********************//
  $form['data']['access_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Access settings'),
    '#collapsible' => TRUE,
    '#group' => 'additional_settings',
    '#weight' => -50,
  );
  $form['data']['access_set']['form_status'] = array(
    '#type' => 'select',
    '#title' => t('Form status'),
    '#options' => array(
      ENTITYFORM_STATUS_OPEN => t('Open for new submissions'),
      ENTITYFORM_STATUS_CLOSED => t('Closed form new form submissions'),
    ),
    '#default_value' => empty($entityform_type->data['form_status']) ? 'open' : $entityform_type->data['form_status'],
    '#description' => t('Can users submit this form?  Open means the users can submit this form.  Closed means the user can not submit the form.'),
  );
  $form['data']['access_set']['roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#options' => user_roles(),
    '#default_value' => empty($entityform_type->data['roles']) ? array() : $entityform_type->data['roles'],
    '#description' => t('Please select the Role(s) that can submit this form.'),
    '#required' => TRUE,
    '#multiple' => TRUE,
  );
  $form['data']['access_set']['resubmit_action'] = array(
    '#type' => 'select',
    '#title' => t('Resubmit action'),
    '#options' => array(
      'new' => t('Allow new submission'),
      'old' => t('Edit old submission'),
      'disallow' => t("Don't allow"),
      'confirm' => t('Goto Confirm page'),
    ),
    '#default_value' => empty($entityform_type->data['resubmit_action']) ? 'new' : $entityform_type->data['resubmit_action'],
    '#description' => t('Action to take if logged in user has already submitted form.'),
  );
  return $form;
}

/**
 * Form element validation handler for URL alias form element.
 */
function _entityform_paths_form_element_validate($element, &$form_state, $complete_form) {
  $previous_paths = array();
  $original_entityform_type = $form_state['entityform_type'];
  foreach ($form_state['values']['paths'] as $path_type => $path) {
    // Trim the submitted value.
    $alias = trim($path['alias']);
    if (!empty($alias)) {
      form_set_value($element[$path_type]['alias'], $alias, $form_state);

      $path = $form_state['values']['paths'][$path_type];
      if (in_array($path['alias'], $previous_paths)) {
        form_error($element[$path_type]['alias'], "Aliases must be unique.");
        return;
      }
      $previous_paths[] = $path['alias'];

      // Ensure that the submitted alias does not exist yet.
      $query = db_select('url_alias')
        ->condition('alias', $path['alias'])
        ->condition('language', LANGUAGE_NONE);
      if (!empty($original_entityform_type->paths[$path_type])) {
        $query->condition('source', $original_entityform_type->paths[$path_type]['source'], '<>');
      }
      $query->addExpression('1');
      $query->range(0, 1);
      if ($query->execute()->fetchField()) {
        form_error($element[$path_type]['alias'], t('The alias is already in use.'));
        return;
      }
    }
  }

}

/*
 * Email form validate function.
 *
 * Should contain either no value or emails separated by commas
 */
function _entityform_form_email_list_validate($element, &$form_state, $form) {
  $emails = explode(', ', $element['#value']);
  foreach ($emails as $email) {
    $email = trim($email);
    if (!empty($email) && !valid_email_address($email)) {
      form_error($element, t('Please enter valid email addresses.'));
      return;
    }
  }
}


/**
 * Form API submit callback for the type form.
 */
function entityform_type_form_submit(&$form, &$form_state) {
  $entityform_type = entity_ui_form_submit_build_entity($form, $form_state);
  if (empty($entityform_type->is_new)) {
    $form_state['redirect'] = 'admin/structure/entityform_types';
  }
  else {
    drupal_set_message(t('The Entityform @label has been created. Add fields to this form below', array('@label' => $entityform_type->label)));
    $form_state['redirect'] = "admin/structure/entityform_types/manage/{$entityform_type->type}/fields";
  }
  $entityform_type->save();
}


/**
 * Form API submit callback for the delete button.
 */
function entityform_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/entityform_types/manage/' . $form_state['entityform_type']->type . '/delete';
}