<?php
/**
 * @file css_injector.admin.inc
 * Administrative interface for CSS Injector.
 */

/**
 * Form builder function for CSS Injector's main admin page.
 */
function css_injector_admin_form($form, &$form_state) {
  $rules = _css_injector_load_rule(NULL, TRUE);
  $path = drupal_get_path('module', 'css_injector') . '/';
  $form = array();
  $form['#tree'] = TRUE;

  // Adding css stylesheet for icons.
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'css_injector') . '/css_injector.css',
  );

  foreach ($rules as $rule) {
    $form['rules'][$rule['crid']]['#rule'] = $rule;
    $form['rules'][$rule['crid']]['edit'] = array(
      '#type' => 'submit',
      '#value' => t('Edit rule'),
      '#name' => 'edit' . $rule['crid'],
      '#submit' => array('css_injector_admin_edit_button'),
      '#attributes' => array('class' => array('css-inject-edit')),
      '#crid' => $rule['crid'],
    );
    $form['rules'][$rule['crid']]['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete rule'),
      '#name' => 'delete' . $rule['crid'],
      '#submit' => array('css_injector_admin_delete_button'),
      '#attributes' => array('class' => array('css-inject-delete')),
      '#crid' => $rule['crid'],
    );
  }
  return $form;
}

/**
 * Edit button callback for the CSS rule listing form.
 */
function css_injector_admin_edit_button($form, &$form_state) {
  $button = $form_state['triggering_element'];
  $crid = $button['#crid'];
  $form_state['redirect'] = 'admin/config/development/css-injector/edit/' . $crid;
}

/**
 * Delete button callback for the CSS rule listing form.
 * Redirects the user to the confirmation form.
 */
function css_injector_admin_delete_button($form, &$form_state) {
  $button = $form_state['triggering_element'];
  $crid = $button['#crid'];
  $form_state['redirect'] = 'admin/config/development/css-injector/delete/' . $crid;
}

/**
 * Theme function for the CSS Injector admin overview form.
 */
function theme_css_injector_admin_form($variables) {
  $form = $variables['form'];
  $headers = array(t('Title'), t('Location'), t('Actions'));
  $rows = array();
  if (!empty($form['rules'])) {
    foreach (element_children($form['rules']) as $crid) {
      $row = array();
      $rule = $form['rules'][$crid]['#rule'];
      $row[] = check_plain($rule['title']);
      $row[] = _css_injector_rule_uri($rule['crid']);
      $row[] = drupal_render($form['rules'][$crid]);
      $rows[] = $row;
    }
  }

  $link = l(t('Create a new rule'), 'admin/config/development/css-injector/add');
  $row = array();
  if (empty($rows)) {
    $row[] = array(
      'data' => t('No CSS injection rules have been set up yet. !url.', array('!url' => $link)),
      'colspan' => 3,
    );
  }
  else {
    $row[] = array(
      'data' => t('!url.', array('!url' => $link)),
      'colspan' => 3,
    );
  }
  $rows[] = $row;

  $output = theme('table', array('header' => $headers, 'rows' => $rows));
  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Form builder function for the CSS rule edit form.
 */
function css_injector_edit($form, $form_state, $crid = NULL) {
  if (isset($crid)) {
    $rule = _css_injector_load_rule($crid, TRUE);
    $path = _css_injector_rule_uri($rule['crid']);
    if (file_exists($path)) {
      $rule['css_text'] = file_get_contents($path);
    }
    else {
      $rule['css_text'] = '';
    }
  }
  else {
    $rule = array(
      'title' => '',
      'rule_type' => CSS_INJECTOR_PAGES_NOTLISTED,
      'rule_themes' => '',
      'rule_conditions' => '',
      'media' => 'all',
      'preprocess' => 1,
      'css_text' => '',
      'enabled' => 1,
    );
  }

  // Adding css stylesheet for icons.
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'css_injector') . '/ace/ace.js',
    drupal_get_path('module', 'css_injector') . '/syntax_highlighter.js',
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'css_injector') . '/syntax_highlighter.css',
  );

  if (isset($crid)) {
  $form['crid'] = array(
      '#type' => 'value',
      '#value' => $crid,
    );
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $rule['title'],
    '#required' => TRUE,
  );

  $form['css_text'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS code'),
    '#rows' => 10,
    '#default_value' => $rule['css_text'],
    '#required' => TRUE,
  );

  $form['css_text_ace'] = array(
    '#prefix' => '<span class="disable-ace">Disable syntax highlighter</span>',
    '#markup' => '<div class="ace-editor"><div id="editor">' . $rule['css_text'] . '</div></div>',
  );

  // Get info of site themes.
  $themes = array();
  $theme_list = list_themes();
  $default_theme = variable_get('theme_default');
  foreach ($theme_list as $single_theme) {
    $themes[$single_theme->name] = $single_theme->info['name'];
  }
  $rule['rule_themes'] = unserialize($rule['rule_themes']);

  $form['conditional']['rule_themes'] = array(
  '#type' => 'select',
  '#title' => 'Themes to show on',
  '#default_value' => isset($rule['rule_themes']) ? $rule['rule_themes'] : $default_theme,
  '#options' => $themes,
  '#description' => t('Select themes css will be applied to. @theme theme is selected by default.', array('@theme' => $themes[$default_theme])),
  '#multiple' => TRUE,
  );

  // Shamelessly ripped from block.module. Who doesn't use this snippet
  // of code, really?
  $php_access = (user_access('use PHP for settings') && module_exists('php'));
  $options = array(
    CSS_INJECTOR_PAGES_NOTLISTED => t('Add on every page except the listed pages.'),
    CSS_INJECTOR_PAGES_LISTED => t('add on only the listed pages.')
  );
  $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));

  if ($php_access) {
    $options[CSS_INJECTOR_PHP] = t('Add if the following PHP code outputs a nonzero value (PHP-mode, experts only).');
    $description .= ' ' . t('If the PHP-mode is chosen, enter PHP code between %php. Note that executing incorrect PHP-code can break your Drupal site.', array('%php' => '<?php ?>'));
  }
  $form['conditional']['rule_type'] = array(
    '#type' => 'radios',
    '#title' => t('Add the CSS on specific pages'),
    '#options' => $options,
    '#default_value' => $rule['rule_type'],
  );
  $form['conditional']['rule_conditions'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#default_value' => $rule['rule_conditions'],
    '#description' => $description,
  );
  $form['media'] = array(
    '#type' => 'select',
    '#title' => t('Media'),
    '#options' => array(
      'all' => t('All'),
      'screen' => t('Screen'),
      'print' => t('Print'),
      'IE 7' => t('IE7'),
      'IE 8' => t('IE8'),
      'IE 9' => t('IE9'),
    ),
    '#default_value' => $rule['media'],
  );

  $form['preprocess'] = array(
    '#type' => 'checkbox',
    '#title' => t('Preprocess CSS'),
    '#default_value' => $rule['preprocess'],
  );
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable rule'),
    '#default_value' => isset($rule['enabled']) ? $rule['enabled'] : 1,
  );

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('css_injector_edit_save'),
  );
  $form['buttons']['save_and_continue'] = array(
    '#type' => 'submit',
    '#value' => t('Save and Continue Editing'),
    '#submit' => array('css_injector_edit_save_and_continue'),
  );

  if (!empty($rule['crid'])) {
    $form['buttons']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#crid' => $rule['crid'],
      '#submit' => array('css_injector_admin_delete_button'),
    );
  }

  return $form;
}

/**
 * Validation callback for the CSS rule edit form.
 */
function css_injector_edit_validate($form, &$form_state) {
  $directory = drupal_realpath('public://css_injector');
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    form_error($form, t('The directory %directory is not writable', array('%directory' => $directory)));
  }
}

/**
 * Submit button callback for the CSS rule edit form.
 */
function css_injector_edit_save($form, &$form_state) {
  //$themes = implode('//', $form_state['values']['themes']);
  $rule = $form_state['values'];
  $crid = !empty($form_state['values']['crid']) ? $form_state['values']['crid'] : NULL;
  // Serialize themes list before inserting to databse.
  $rule['rule_themes'] = serialize($rule['rule_themes']);
  drupal_write_record('css_injector_rule', $rule, empty($crid) ? array() : 'crid');
  // Unserialize themes list for form state.
  $rule['rule_themes'] = unserialize($rule['rule_themes']);
  $form_state['values']['rule'] = $rule;
  file_unmanaged_save_data($rule['css_text'], _css_injector_rule_uri($rule['crid']), FILE_EXISTS_REPLACE);
  _css_injector_load_rule(NULL, TRUE);

  drupal_set_message(t('Your CSS injection rule %title was saved.', array('%title' => $rule['title'])));
  $form_state['redirect'] = 'admin/config/development/css-injector';
}

/**
 * Save and continue callback for the CSS rule edit form.
 */
function css_injector_edit_save_and_continue($form, &$form_state) {
  css_injector_edit_save($form, $form_state);
  $form_state['redirect'] = 'admin/config/development/css-injector/edit/' . $form_state['values']['rule']['crid'];
}


/**
 * Menu callback -- ask for confirmation of rule deletion.
 */
function css_injector_delete_confirm($form, &$form_state, $crid) {
  $form['crid'] = array(
    '#type' => 'value',
    '#value' => $crid,
  );

  $rule = _css_injector_load_rule($crid);
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $rule['title'])),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/config/development/css-injector',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Execute node deletion.
 */
function css_injector_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    _css_injector_delete_rule($form_state['values']['crid']);
  }

  $form_state['redirect'] = 'admin/config/development/css-injector';
  return;
}
