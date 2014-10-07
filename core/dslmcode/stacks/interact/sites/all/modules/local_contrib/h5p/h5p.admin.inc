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
  // TODO: Should we remove existing H5P files when export gets disabled?
  
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

  // TODO: Create a development section with multiple options?
  $form['h5p_dev_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable H5P development mode'),
    '#default_value' => variable_get('h5p_dev_mode', '0'),
    '#description' => t('Always update uploaded H5P libraries regardless of patch version. Read library data from file (semantics.json).')
  );

//  $form['h5p_content_dev_mode'] = array(
//    '#type' => 'checkbox',
//    '#title' => t('Enable H5P content development mode'),
//    '#default_value' => variable_get('h5p_content_dev_mode', '0'),
//    '#description' => t("With this feature enabled content.json will be read from file. Changes to the content made using the editor won't be visible when this mode is actice."),
//    '#disabled' => TRUE, // Disabled for now, since core is using a Drupal 6-only function
//  );
  
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
  
  $core = _h5p_get_instance('core');
  $notCached = $core->h5pF->getNotCached();
  $libraries = $core->h5pF->loadLibraries();
  
  // Add settings for each library
  $settings = array();
  foreach ($libraries as $versions) {
    foreach ($versions as $library) {
      $usage = $core->h5pF->getLibraryUsage($library->id, $notCached ? TRUE : FALSE);
      if ($library->runnable) {
        $upgrades = $core->getUpgrades($library, $versions);
        $upgradeUrl = empty($upgrades) ? FALSE : url('admin/content/h5p/libraries/' . $library->id . '/upgrade', array('query' => drupal_get_destination()));
      }
      else {
        $upgradeUrl = NULL;
      }
      
      $settings['h5p']['libraries']['listData'][] = array(
        'title' => $library->title . ' (' . H5PCore::libraryVersion($library) . ')',
        'numContent' => $core->h5pF->getNumContent($library->id),
        'numContentDependencies' => $usage['content'],
        'numLibraryDependencies' => $usage['libraries'],
        'upgradeUrl' => $upgradeUrl,
        'detailsUrl' => url('admin/content/h5p/libraries/' . $library->id),
        'deleteUrl' => url('admin/content/h5p/libraries/' . $library->id . '/delete', array('query' => drupal_get_destination()))
      );
    }
  }

  // All translations are made server side
  $settings['h5p']['libraries']['listHeaders'] = array(t('Title'), t('Instances'), t('Instance Dependencies'), t('Library dependencies'), t('Actions')); 
  
  // Make it possible to rebuild all caches.
  if ($notCached) {
    $settings['h5p']['libraries']['notCached'] = h5p_get_not_cached_settings($notCached);
    $settings['h5p']['libraries']['notCached']['message'] .= t('This is required before you can delete any libraries.');
  }
      
  // Include libraries and more to Drupal setting
  drupal_add_js($settings, 'setting');
  
  // Add the needed css and javascript
  $module_path = drupal_get_path('module', 'h5p');
  _h5p_admin_add_generic_css_and_js($module_path);
  drupal_add_js($module_path . '/library/js/h5p-library-list.js');
  
  $upgrade_all_libraries = variable_get('h5p_unsupported_libraries', NULL) === NULL ? '' : '<p>' . t('Click <a href="@url">here</a> to upgrade all installed libraries', array('@url' => url('admin/content/h5p/libraries/upgrade-all'))) . '</p>';
  
  // Create the container which all admin content 
  // will appends it's data to. This id is used by h5pintegration
  // to find where to put the admin content. 
  $upload_form = drupal_get_form('h5p_library_upload_form');
  return '<h3 class="h5p-admin-header">' . t('Add libraries') . '</h3>' . drupal_render($upload_form) . '<h3 class="h5p-admin-header">' . t('Installed libraries') . '</h3>' . $upgrade_all_libraries . '<div id="h5p-admin-container"></div>';
}

/**
 * Settings needed to rebuild cache from UI.
 * 
 * @param int $num
 * @return array
 */
function h5p_get_not_cached_settings($num) {
  return array(
    'num' => $num,
    'url' => url('admin/content/h5p/rebuild-cache'),
    'message' => t('%num need to get their cache rebuilt before content dependencies can be display.', array('%num' => format_plural($num, '1 content instance', '@count content instances'))),
    'button' => t('Rebuild cache')
  );
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
  
  $library = db_query('SELECT title, machine_name, major_version, minor_version, patch_version, runnable, fullscreen FROM {h5p_libraries} where library_id = :id', array('id' => $library_id))->fetchObject();
  
  // Build library info
  $settings['h5p']['library']['info'] = array(
    t('Name') => $library->title,
    t('Machine name') => $library->machine_name,
    t('Version') => H5PCore::libraryVersion($library),
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

  $h5p_drupal = _h5p_get_instance('interface');
  $notCached = $h5p_drupal->getNotCached();
  if ($notCached) {
    $settings['h5p']['library']['notCached'] = h5p_get_not_cached_settings($notCached);
  }
  else {
    // Build a list of the content using this library
    $nodes_res = db_query('SELECT DISTINCT n.nid, n.title FROM {h5p_nodes_libraries} l join {h5p_nodes} hn on l.content_id = hn.content_id join {node} n on hn.nid = n.nid  where library_id = :id order by n.title', array(':id' => $library_id));
    foreach($nodes_res as $node) {
      $settings['h5p']['library']['content'][] = array(
        'title' => $node->title, 
        'url' => url('node/' . $node->nid),
      );
    }
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
  $notCached = $h5p_drupal->getNotCached();
  $library_usage = $h5p_drupal->getLibraryUsage($library_id, $notCached ? TRUE : FALSE);
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
  drupal_add_css($module_path . '/library/styles/h5p.css');
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
    '#description' => t('Here you can upload new libraries or upload updates to existing libraries. Files uploaded here must be in the .h5p file format.')
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
  h5p_validate_h5p_file_upload($form, $form_state);
}

function h5p_validate_h5p_file_upload($form, &$form_state, $upgradeOnly = FALSE){
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
    if ($validator->isValidPackage(TRUE, $upgradeOnly) === FALSE) {
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
  $h5p_core->savePackage(NULL, NULL, TRUE);
  
  // Maintain session variables.
  unset($_SESSION['h5p_upload'], $_SESSION['h5p_upload_folder']);
}

/**
 * Callback for rebuilding all content cache.
 */
function h5p_rebuild_cache() {
  if (filter_input(INPUT_SERVER, 'REQUEST_METHOD') !== 'POST') {
    drupal_set_message(t('HTTP POST is required.'), 'error');
    drupal_set_title(t('Error'));
    return '';
  }
  
  // Do as many as we can in ten seconds.
  $start = microtime(TRUE);
  
  $core = _h5p_get_instance('core');
  $contents = db_query("SELECT hn.content_id FROM h5p_nodes hn LEFT JOIN cache c ON CONCAT('h5p:parameters:', hn.content_id) = c.cid WHERE cid IS NULL");
  $done = 0;
  while ($content_id = $contents->fetchField()) {
    $content = $core->loadContent($content_id);
    $core->filterParameters($content);
    $done++;
    
    if ((microtime(TRUE) - $start) > 10) {
      break;
    }
  }
  
  print ($contents->rowCount() - $done);
}

/**
 * Get a new H5P security token.
 * 
 * @param string $key
 * @return string
 */
function h5p_get_token($key) {
  return $_SESSION['h5p_' . $key] = uniqid('h5p-');
}

/**
 * Verifiy a given H5P security token.
 * 
 * @param string $key
 * @param string $token
 * @return string
 */
function h5p_verify_token($key, $token) {
  return $_SESSION['h5p_' . $key] === $token;
}

/**
 * Callback for the library content upgrade page.
 * 
 * @param int $library_id
 * @return string HTML
 */
function h5p_content_upgrade($library_id) {
  if (filter_input(INPUT_SERVER, 'REQUEST_METHOD') === 'POST') {
    h5p_content_upgrade_progress($library_id);
    return;
  }
  $core = _h5p_get_instance('core');
  
  $versions = db_query('SELECT hl2.library_id as id, hl2.machine_name as name, hl2.title, hl2.major_version, hl2.minor_version, hl2.patch_version FROM {h5p_libraries} hl1 JOIN {h5p_libraries} hl2 ON hl1.machine_name = hl2.machine_name WHERE hl1.library_id = :id ORDER BY hl2.title ASC, hl2.major_version ASC, hl2.minor_version ASC', array(':id' => $library_id));
  foreach ($versions as $library) {
    if ($library->id === $library_id) {
      $upgrades = $core->getUpgrades($library, $versions);
      break;
    }
  }
  
  drupal_set_title(t('Upgrade @library content', array('@library' => $library->title . ' (' . H5PCore::libraryVersion($library) . ')')));
  if ($versions->rowCount() < 2) {
    return t("There are no available upgrades for this library.");
  }
  
  // Get num of contents that can be upgraded
  $contents = $core->h5pF->getNumContent($library_id);
  if (!$contents) {
    return t("There's no content instances to upgrade.");
  }
  
  $contents_plural = format_plural($contents, '1 content instance', '@count content instances');
  
  // Add JavaScript settings
  $return = filter_input(INPUT_GET, 'destination');
  drupal_add_js(array(
    'h5p' => array(
      'library' => array(
        'message' => t('You are about to upgrade %num. Please select upgrade version.', array('%num' => $contents_plural)),
        'inProgress' => t('Upgrading to %ver...'),
        'error' => t('An error occurred while processing parameters:'),
        'errorData' => t('Could not load data for library %lib.'),
        'errorScript' => t('Could not load upgrades script for %lib.'),
        'done' => t('You have successfully upgraded %num.', array('%num' => $contents_plural)) . ($return ? ' ' . l(t('Return'), $return) : ''),
        'library' => array(
          'name' => $library->name,
          'version' => $library->major_version . '.' . $library->minor_version,
        ),
        'libraryBaseUrl' => url('admin/content/h5p/upgrade/library'),
        'versions' => $upgrades,
        'contents' => $contents,
        'buttonLabel' => t('Upgrade'),
        'infoUrl' => url('admin/content/h5p/libraries/' . $library_id . '/upgrade'),
        'total' => $contents,
        'token' => h5p_get_token('content_upgrade'), // Use token to avoid unauthorized updating
      )
    )
  ), 'setting');
  
  // Add JavaScripts
  $module_path = drupal_get_path('module', 'h5p');
  _h5p_admin_add_generic_css_and_js($module_path);
  drupal_add_js($module_path . '/library/js/h5p-content-upgrade.js');
  
  return '<div id="h5p-admin-container">' . t('Please enable JavaScript.') . '</div>';
}

/**
 * AJAX processing for content upgrade script.
 * 
 * @param int $library_id
 * @return string JSON or error
 */
function h5p_content_upgrade_progress($library_id) {
  // Verify security token
  if (!h5p_verify_token('content_upgrade', filter_input(INPUT_POST, 'token'))) {
    print t('Error: Invalid security token!');
    return;
  }
  
  // Get the library we're upgrading to
  $to_library = db_query('SELECT library_id AS id, machine_name AS name, major_version, minor_version FROM {h5p_libraries} WHERE library_id = :id', array(':id' => filter_input(INPUT_POST, 'libraryId')))->fetch();
  if (!$to_library) {
    print t('Error: Your library is missing!');
    return;
  }
  
  // Prepare response
  $out = new stdClass();
  $out->params = array();
  $out->token = h5p_get_token('content_upgrade');
  
  // Prepare our interface
  $interface = _h5p_get_instance('interface');
  
  // Get updated params
  $params = filter_input(INPUT_POST, 'params');
  if ($params !== NULL) {
    // Update params.
    $params = json_decode($params);
    foreach ($params as $id => $param) {
      db_update('h5p_nodes')
        ->fields(array(
          'main_library_id' => $to_library->id,
          'json_content' => $param
        ))
        ->condition('content_id', $id)
        ->execute();
      
      // Clear content cache
      $interface->cacheDel('parameters', $id);
    }
  }
  
  // Get number of contents for this library
  $out->left = $interface->getNumContent($library_id);
  
  if ($out->left) {
    // Find the 10 first contents using library and add to params
    $contents = db_query('SELECT content_id AS id, json_content AS params FROM {h5p_nodes} WHERE main_library_id = :id LIMIT 10', array(':id' => $library_id));
    foreach ($contents as $content) {
      $out->params[$content->id] = $content->params;
    }
  }

  drupal_add_http_header('Cache-Control', 'no-cache');
  drupal_add_http_header('Content-type', 'application/json');
  print json_encode($out);
}

/**
 * AJAX loading of libraries for content upgrade script.
 * 
 * @param string $name
 * @param int $major
 * @param int $minor
 */
function h5p_content_upgrade_library($name, $major, $minor) {
  $library = (object) array(
    'name' => $name,
    'version' => (object) array(
      'major' => $major,
      'minor' => $minor
    )
  );
  
  $core = _h5p_get_instance('core');
  $library->semantics = $core->loadLibrarySemantics($library->name, $library->version->major, $library->version->minor);
  if ($library->semantics === NULL) {
    drupal_not_found();
  }

  if ($core->development_mode & H5PDevelopment::MODE_LIBRARY) {
    $dev_lib = $core->h5pD->getLibrary($library->name, $library->version->major, $library->version->minor);
  }
    
  $upgrades_script = (isset($dev_lib) ? $dev_lib['path'] : _h5p_get_h5p_path() . '/libraries/' . $library->name . '-' . $library->version->major . '.' . $library->version->minor) . '/upgrades.js';
  if (file_exists($upgrades_script)) {
    $library->upgradesScript = base_path() . $upgrades_script;
  }
  
  drupal_add_http_header('Cache-Control', 'no-cache');
  drupal_add_http_header('Content-type', 'application/json');
  print json_encode($library);
}

/**
 * Selective upgrade off all installed libraries (with upgrades.h5p as input)
 */
function h5p_upgrade_all_libraries() {
  // Create form
  return drupal_get_form('h5p_all_libraries_upgrade_upload_form');
}

/**
 * Create upload all libraries form
 */
function h5p_all_libraries_upgrade_upload_form($form_state) {
  $form['#attributes'] = array(
    'enctype' => 'multipart/form-data',
    'class' => 'h5p-admin-upload-libraries-form',
  );

  // TODO - support translation
  $form['info-message'] = array(
    '#markup' => 
      '<div>
        To upgrade all installed libraries, do the following:
        <ol>
          <li>Download <a href="http://h5p.org/sites/default/files/upgrades.h5p">upgrades.h5p</a>
          <li>Click the <em>Select file</em> button below, and select the downloaded upgrades.h5p file
          <li>Click the <em>Upload</em> button 
        </ol> 
      </div>',
  );
  
  $form['h5p'] = array(
    '#title' => t('H5P'),
    '#type' => 'file',
    '#description' => t('Upload the upgrades.h5p (downloaded from h5p.org) here'),
  );

  $form['submit'] = array(
    '#value' => t('Upload'),
    '#type' => 'submit',
  );

  return $form;
}

function h5p_all_libraries_upgrade_upload_form_validate($form, &$form_state) {
  h5p_validate_h5p_file_upload($form, $form_state, TRUE);
}

function h5p_all_libraries_upgrade_upload_form_submit($form, &$form_state) {
  // Save package
  $h5p_core = _h5p_get_instance('storage');
  $h5p_core->savePackage(NULL, NULL, TRUE, TRUE);
  
  // Maintain session variables.
  unset($_SESSION['h5p_upload'], $_SESSION['h5p_upload_folder']);
  
  // Redirect to libraries overview:
  drupal_goto('admin/content/h5p');
}
