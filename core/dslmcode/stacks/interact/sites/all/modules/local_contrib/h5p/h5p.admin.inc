<?php
/**
 * Menu callback - Form builder function for settings.
 */
function h5p_admin_settings($form, &$form_state) {
  $form['h5p_default_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Default h5p package path'),
    '#default_value' => variable_get('h5p_default_path', 'h5p'),
    '#description' => t('Subdirectory in the directory %dir where files will be stored. Do not include trailing slash.', array('%dir' => file_stream_wrapper_get_instance_by_uri('public://')->realpath())),
  );

  $h5p_nodes_exists = db_query("SELECT 1 FROM {node} WHERE type = :type", array(':type' => 'h5p_content'))->fetchField();

  $form['h5p_revisioning'] = array(
    '#type' => 'checkbox',
    '#title' => t('Save content files for each revision'),
    '#default_value' => variable_get('h5p_revisioning', '1'),
    '#description' => t("Disable this feature to save disk space. This value can't be changed if there are existing h5p nodes."),
    '#disabled' => $h5p_nodes_exists,
  );

  $form['h5p_export'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable export of all H5P content'),
    '#default_value' => variable_get('h5p_export', '1'),
    '#description' => t("With this feature enabled all H5P content will be downloadable as H5P files. The H5P Editor module must be enabled for export to work."),
  );
  
  // Disable/enable the H5P icon below each H5P
  $form['h5p_icon_in_action_bar'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the H5P icon below each H5P'),
    '#default_value' => variable_get('h5p_icon_in_action_bar', '1'),
    '#description' => t("The H5P icon is a link to h5p.org"),
  );
  
  // make sure core is loaded
  _h5p_get_instance('core');
  $form['h5p_whitelist'] = array(
    '#type' => 'textfield',
    '#maxlength' => 8192,
    '#title' => t('White list of accepted files.'),
    '#default_value' => variable_get('h5p_whitelist', H5PCore::$defaultContentWhitelist),
    '#description' => t("List accepted content file extensions for uploaded H5Ps. List extensions separated by space, eg. 'png jpg jpeg gif webm mp4 ogg mp3'. Changing this list has security implications. Do not change it if you don't know what you're doing. Adding php to the list is for instance a security risk."),
  );

  $form['h5p_library_whitelist_extras'] = array(
    '#type' => 'textfield',
    '#maxlength' => 8192,
    '#title' => t('White list of extra accepted files in libraries.'),
    '#default_value' => variable_get('h5p_library_whitelist_extras', H5PCore::$defaultLibraryWhitelistExtras),
    '#description' => t("Libraries might need to accept more files that should be allowed in normal contents. Add extra files here. Changing this list has security implications. Do not change it if you don't know what you're doing. Adding php to the list is for instance a security risk."),
  );

  $form['h5p_dev_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable H5P development mode'),
    '#default_value' => variable_get('h5p_dev_mode', '0'),
    '#description' => t("With this feature enabled libraries with the same patch version will overwrite existing libraries in the database, and semantics.json will be read from file."),
  );

  $form['h5p_content_dev_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable H5P content development mode'),
    '#default_value' => variable_get('h5p_content_dev_mode', '0'),
    '#description' => t("With this feature enabled content.json will be read from file. Changes to the content made using the editor won't be visible when this mode is actice."),
  );
  
  /*$form['h5p_library_development'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable library development directory'),
    '#default_value' => variable_get('h5p_library_development', 0),
    '#description' => t('Check to enabled development of libraries in the %dev folder.', array('%dev' => _h5p_get_h5p_path() . '/development')),
  );*/

  // Make changes to the settings before passing them off to
  // system_settings_form_submit().
  $form['#submit'][] = 'h5p_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Form validation handler for admin settings form.
 */
function h5p_admin_settings_validate($form, &$form_state) {
  // Try to create directories and warn the user of errors.
  $h5p_default_path = $form_state['values']['h5p_default_path'];
  $path = file_stream_wrapper_get_instance_by_uri('public://')->realpath() . '/' . $h5p_default_path;
  $temp_path = $path . '/' . 'temp';

  if (!file_prepare_directory($path, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    form_set_error('h5p_default_path', t('You have specified an invalid directory.'));
  }
  if (!file_prepare_directory($temp_path, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    form_set_error('h5p_default_path', t('You have specified an invalid directory.'));
  }
}

/**
 * Form submit handler for h5p admin settings form.
 */
function h5p_admin_settings_submit($form, &$form_state) {
  // Ensure that 'h5p_default_path' variable contains no trailing slash.
  $form_state['values']['h5p_default_path'] = rtrim($form_state['values']['h5p_default_path'], '/\\');
  // Ensure that the h5p white list is always stored in lower case.
  $form_state['values']['h5p_whitelist'] = mb_strtolower($form_state['values']['h5p_whitelist']);
}

/**
 * Creates the library list page
 * 
 * @return {string} Html
 */
function h5p_library_list() {
  _h5p_check_settings();
  $settings = array();
  
  $libraries = array();
  
  $h5p_drupal = _h5p_get_instance('interface');
  
  // Get the libraries
  $res = db_query('SELECT * FROM {h5p_libraries} ORDER BY title ASC');
  foreach ($res as $library) {
    // Get usage:
    $library_usage = $h5p_drupal->getLibraryUsage($library->library_id);
    
    $settings['h5p']['libraries']['listData'][] = array(
      'name' => $library->title . ' (' . $library->major_version . '.' . $library->minor_version . '.' . $library->patch_version . ')',
      'machineName' => $library->machine_name,
      'contentCount' => $library_usage['content'],
      'libraryDependencyCount' => $library_usage['libraries'],
      'detailsUrl' => url('admin/content/h5p/libraries/' . $library->library_id),
      'deleteUrl' => url('admin/content/h5p/libraries/' . $library->library_id . '/delete', array('query' => drupal_get_destination()))
    );
  }
  
  // All translations are made server side
  $settings['h5p']['libraries']['listHeaders'] = array(t('Name'), t('Machine name'), t('Usage counter'), t('Library dependencies'), ''); 

  // Include libraries and more to Drupal setting
  drupal_add_js($settings, 'setting');
  
  // Add the needed css and javascript
  $module_path = drupal_get_path('module', 'h5p');
  _h5p_admin_add_generic_css_and_js($module_path);
  drupal_add_js($module_path . '/library/js/h5p-library-list.js');
  
  // Create the container which all admin content 
  // will appends it's data to. This id is used by h5pintegration
  // to find where to put the admin content. 
  $upload_form = drupal_get_form('h5p_library_upload_form');
  return '<h3 class="h5p-admin-header">' . t('Add libraries') . '</h3>' . drupal_render($upload_form) . '<h3 class="h5p-admin-header">' . t('Installed libraries') . '</h3><div id="h5p-admin-container"></div>';
}

/**
 * Creates the library list page
 * 
 * @param {string} $library_id The id of the library to be displayed
 * 
 * @return {string} Html string
 */
function h5p_library_details($library_id) {
  $settings = array();
  
  $library = db_query('SELECT * FROM {h5p_libraries} where library_id = :id', array('id' => $library_id))->fetchObject();
  
  // Build library info
  $settings['h5p']['library']['info'] = array(
    t('Name') => $library->title,
    t('Machine name') => $library->machine_name,
    t('Version') => $library->major_version . '.' . $library->minor_version . '.' . $library->patch_version,
    t('Runnable') => $library->runnable ? t('Yes') : t('No'),
    t('Fullscreen') => $library->fullscreen ? t('Yes') : t('No'),
  );
  
  // Build the translations needed
  $settings['h5p']['library']['translations'] = array(
    'contentCount' => t('Content count'),
    'noContent' => t('No content is using this library'),
    'contentHeader' => t('Content using this library'),
    'pageSizeSelectorLabel' => t('Elements per page'),
    'filterPlaceholder' => t('Filter content'),
    'pageXOfY' => t('Page $x of $y'),
  ); 

  // Build a list of the content using this library
  $nodes_res = db_query('SELECT DISTINCT n.nid, n.title FROM {h5p_nodes_libraries} l join {h5p_nodes} hn on l.content_id = hn.content_id join {node} n on hn.nid = n.nid  where library_id = :id order by n.title', array(':id' => $library_id));
  foreach($nodes_res as $node) {
    $settings['h5p']['library']['content'][] = array(
      'title' => $node->title, 
      'url' => url('node/' . $node->nid),
    );
  }
  
  // Include all above in Drupal setting
  drupal_add_js($settings, 'setting');
  
  $module_path = drupal_get_path('module', 'h5p');
  _h5p_admin_add_generic_css_and_js($module_path);
  drupal_add_js($module_path . '/library/js/h5p-library-details.js');
  
  // Create the container which all admin content
  // will appends it's data to. This id is used by h5pintegration
  // to find where to put the admin content.
  return '<div id="h5p-admin-container"></div>';
}

/**
 * 
 * @param string $library_id
 */
function h5p_library_delete($library_id) {
  
  // Is library deletable ?
  $h5p_drupal = _h5p_get_instance('interface');
  $library_usage = $h5p_drupal->getLibraryUsage($library_id);
  if ($library_usage['content'] === 0 && $library_usage['libraries'] === 0) {
    // Create form:
    return drupal_get_form('h5p_library_delete_form', $library_id, _h5p_library_details_title($library_id));
  }
  else {
    // May not delete this one
    return t('Library is in use by content, or is dependent by other librarie(s), and can therefore not be deleted');
  }
}

/**
 * Helper function - adds h5p admin css and js
 * 
 * @param {string} $module_path The H5P path 
 */
function _h5p_admin_add_generic_css_and_js($module_path) {
  drupal_add_js($module_path . '/js/h5pintegration.js');
  foreach (H5PCore::$adminScripts as $script) {
    drupal_add_js($module_path . '/library/' . $script);
  }
  drupal_add_css($module_path . '/library/styles/h5p-admin.css');
}

/**
 * Library upload form.
 */
function h5p_library_upload_form($form_state) {
  $form['#attributes'] = array(
    'enctype' => 'multipart/form-data',
    'class' => 'h5p-admin-upload-libraries-form'
  );

  $form['h5p'] = array(
    '#title' => t('H5P'),
    '#type' => 'file',
    '#description' => t('All the libraries from the selected package will be added.')
  );
  
  $form['submit'] = array(
    '#value' => t('Upload'),
    '#type' => 'submit',
  );

  return $form;
}

/**
 * Form validation.
 */
function h5p_library_upload_form_validate($form, &$form_state) {
  $validators = array(
    'file_validate_extensions' => array('h5p'),
  );
  // New uploads need to be saved in temp in order to be viewable
  // during node preview.
  $temporary_file_path = 'public://' . variable_get('h5p_default_path', 'h5p') . '/temp/' . uniqid('h5p-');
  file_prepare_directory($temporary_file_path, FILE_CREATE_DIRECTORY);

  if ($file = file_save_upload('h5p', $validators, $temporary_file_path)) {    
    // These has to be set instead of sending parameteres to the validation function.
    $_SESSION['h5p_upload'] = drupal_realpath($file->uri);
    $_SESSION['h5p_upload_folder'] = drupal_realpath($temporary_file_path);
    
    $validator = _h5p_get_instance('validator');
    if ($validator->isValidPackage(TRUE) === FALSE) {
      form_set_error('h5p', t('The uploaded file was not a valid h5p package'));
      // Maintain session variables.
      unset($_SESSION['h5p_upload'], $_SESSION['h5p_upload_folder']);
    }
  }
  elseif (!isset($form['#node']->nid) && empty($form_state['values']['h5p']) && empty($_SESSION['h5p_upload'])) {
    form_set_error('h5p', t('You must upload a h5p file.'));
  }
}

/**
 * Form submit handler.
 */
function h5p_library_upload_form_submit($form, &$form_state) {
  // Save package
  $h5p_core = _h5p_get_instance('storage');
  if ($h5p_core->savePackage(NULL, NULL, TRUE) === TRUE) {
    _h5p_clear_js_and_css_cache();
  }
  
  // Maintain session variables.
  unset($_SESSION['h5p_upload'], $_SESSION['h5p_upload_folder']);
}
