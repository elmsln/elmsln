<?php
/**
 * Menu callback - Form builder function for settings.
 */
function h5p_admin_settings($form, &$form_state) {
  $form['h5p_allow_communication_with_h5p_org'] = array(
    '#type' => 'checkbox',
    '#title' => t('I wish to aid in the development of H5P by contributing anonymous usage data'),
    '#default_value' => variable_get('h5p_allow_communication_with_h5p_org', '1'),
    '#description' => t('Disabling this option will prevent your site from fetching the newest H5P updates. Read more about <a href="@url">which data is collected</a> on h5p.org.', array('@url' => 'https://h5p.org/tracking-the-usage-of-h5p')),
  );

  $path = drupal_get_path('module', 'h5p');
  $form['h5p_display_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display Options'),
    '#attributes' => array(
      'class' => array('h5p-action-bar-settings')
    ),
    '#attached' => array(
      'js' => array(
        $path . '/library/js/jquery.js',
        $path . '/library/js/disable.js'
      )
    )
  );

  $labels = _h5p_get_disable_labels();
  foreach (H5PCore::$disable as $bit => $name) {
    $name = ($bit & H5PCore::DISABLE_DOWNLOAD ? 'export' : $name);
    $form['h5p_display_options']['h5p_' . $name] = array(
      '#type' => 'checkbox',
      '#title' => $labels[$bit],
      '#default_value' => variable_get('h5p_' . $name, TRUE)
    );
  }
  // TODO: Should we remove existing H5P files when export gets disabled?

  // Disable/enable the H5P icon below each H5P
  $form['h5p_display_options']['h5p_icon_in_action_bar'] = array(
    '#type' => 'checkbox',
    '#title' => t('About H5P button'),
    '#default_value' => variable_get('h5p_icon_in_action_bar', TRUE)
  );

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

  $form['h5p_library_development'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable library development directory (For programmers only)'),
    '#default_value' => variable_get('h5p_library_development', 0),
    '#description' => t('Check to enable development of libraries in the %dev folder. ONLY ENABLE THIS OPTION IF YOU KNOW WHAT YOU ARE DOING! YOUR SITES H5P DATA WILL BE RUINED BY ENABLING THIS OPTION', array('%dev' => _h5p_get_h5p_path() . '/development')),
  );

  $form['h5p_save_content_state'] = array(
    '#type' => 'checkbox',
    '#title' => t('Save content state'),
    '#default_value' => variable_get('h5p_save_content_state', 0),
    '#description' => t('Automatically save the current state of interactive content for each user. This means that the user may pick up where he left off.'),
  );

  $form['h5p_save_content_frequency'] = array(
    '#type' => 'textfield',
    '#title' => t('Save content state frequency'),
    '#default_value' => variable_get('h5p_save_content_frequency', 30),
    '#description' => t("In seconds, how often do you wish the user to auto save their progress. Increasee this number if you're having issues with many ajax request."),
  );

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

  if (!is_numeric($form_state['values']['h5p_save_content_frequency']) || $form_state['values']['h5p_save_content_frequency'] < 0) {
    form_set_error('h5p_save_content_frequency', t('You must specify a positive number.'));
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

  if($form_state['values']['h5p_allow_communication_with_h5p_org'] == 0) {
    h5p_fetch_libraries_metadata(TRUE);
  }
}

/**
 * Creates the library list page
 *
 * @return {string} Html
 */
function h5p_library_list() {
  _h5p_check_settings();

  $core = _h5p_get_instance('core');
  $numNotFiltered = $core->h5pF->getNumNotFiltered();
  $libraries = $core->h5pF->loadLibraries();

  // Add settings for each library
  $settings = array();
  $i = 0;
  foreach ($libraries as $versions) {
    foreach ($versions as $library) {
      $usage = $core->h5pF->getLibraryUsage($library->id, $numNotFiltered ? TRUE : FALSE);
      if ($library->runnable) {
        $upgrades = $core->getUpgrades($library, $versions);
        $upgradeUrl = empty($upgrades) ? FALSE : url('admin/content/h5p/libraries/' . $library->id . '/upgrade', array('query' => drupal_get_destination()));

        $restricted = ($library->restricted === '1' ? TRUE : FALSE);
        $restricted_url = url('admin/content/h5p/libraries/' . $library->id . '/restrict', array(
          'query' => array(
            'token' => H5PCore::createToken('library_' . $i),
            'token_id' => $i,
            'restrict' => ($library->restricted === '1' ? 0 : 1)
          )
        ));
      }
      else {
        $upgradeUrl = NULL;
        $restricted = NULL;
        $restricted_url = NULL;
      }

      $settings['libraryList']['listData'][] = array(
        'title' => $library->title . ' (' . H5PCore::libraryVersion($library) . ')',
        'restricted' => $restricted,
        'restrictedUrl' => $restricted_url,
        'numContent' => $core->h5pF->getNumContent($library->id),
        'numContentDependencies' => $usage['content'] === -1 ? '' : $usage['content'],
        'numLibraryDependencies' => $usage['libraries'],
        'upgradeUrl' => $upgradeUrl,
        'detailsUrl' => url('admin/content/h5p/libraries/' . $library->id),
        'deleteUrl' => url('admin/content/h5p/libraries/' . $library->id . '/delete', array('query' => drupal_get_destination()))
      );

      $i++;
    }
  }

  // All translations are made server side
  $settings['libraryList']['listHeaders'] = array(t('Title'), t('Restricted'), t('Instances'), t('Instance Dependencies'), t('Library dependencies'), t('Actions'));

  // Make it possible to rebuild all caches.
  if ($numNotFiltered) {
    $settings['libraryList']['notCached'] = h5p_get_not_cached_settings($numNotFiltered);
  }

  // Add the needed css and javascript
  $module_path = drupal_get_path('module', 'h5p');
  _h5p_admin_add_generic_css_and_js($module_path, $settings);
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
    'message' => t('Not all content has gotten their cache rebuilt. This is required to be able to delete libraries, and to display how many contents that uses the library.'),
    'progress' => format_plural($num, '1 content need to get its cache rebuilt.', '@count contents needs to get their cache rebuilt.'),
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
  $settings['libraryInfo']['info'] = array(
    t('Name') => $library->title,
    t('Machine name') => $library->machine_name,
    t('Version') => H5PCore::libraryVersion($library),
    t('Runnable') => $library->runnable ? t('Yes') : t('No'),
    t('Fullscreen') => $library->fullscreen ? t('Yes') : t('No'),
  );

  // Build the translations needed
  $settings['libraryInfo']['translations'] = array(
    'contentCount' => t('Content count'),
    'noContent' => t('No content is using this library'),
    'contentHeader' => t('Content using this library'),
    'pageSizeSelectorLabel' => t('Elements per page'),
    'filterPlaceholder' => t('Filter content'),
    'pageXOfY' => t('Page $x of $y'),
  );

  $h5p_drupal = _h5p_get_instance('interface');
  $numNotFiltered = $h5p_drupal->getNumNotFiltered();
  if ($numNotFiltered) {
    $settings['libraryInfo']['notCached'] = h5p_get_not_cached_settings($numNotFiltered);
  }
  else {
    // Build a list of the content using this library
    $nodes_res = db_query('SELECT DISTINCT n.nid, n.title FROM {h5p_nodes_libraries} l join {h5p_nodes} hn on l.content_id = hn.content_id join {node} n on hn.nid = n.nid  where library_id = :id order by n.title', array(':id' => $library_id));
    foreach($nodes_res as $node) {
      $settings['libraryInfo']['content'][] = array(
        'title' => $node->title,
        'url' => url('node/' . $node->nid),
      );
    }
  }

  $module_path = drupal_get_path('module', 'h5p');
  _h5p_admin_add_generic_css_and_js($module_path, $settings);
  drupal_add_js($module_path . '/library/js/h5p-library-details.js');

  // Create the container which all admin content
  // will appends it's data to. This id is used by h5pintegration
  // to find where to put the admin content.
  return '<div id="h5p-admin-container"></div>';
}

/**
 * Display library delete page with form.
 *
 * @param string $library_id
 */
function h5p_library_delete($library_id) {

  // Is library deletable ?
  $h5p_drupal = _h5p_get_instance('interface');
  $notCached = $h5p_drupal->getNumNotFiltered();
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
 * Library delete form
 */
function h5p_library_delete_form($form, &$form_state, $library_id, $library_name) {
  $form['library_id'] = array(
    '#type' => 'hidden',
    '#value' => $library_id
  );

  $form['info'] = array(
    '#markup' => '<div>' . t('Are you sure you would like to delete the @library_name H5P library?', array('@library_name' => $library_name)) . '</div>'
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete')
  );

  return $form;
}

/**
 * Handle library delete submission.
 */
function h5p_library_delete_form_submit($form, &$form_state) {
  // Do the actual deletion:
  _h5p_get_instance('core')->deleteLibrary($form_state['values']['library_id']);
}

/**
 * Helper function - adds h5p admin css and js
 *
 * @param {string} $module_path The H5P path
 */
function _h5p_admin_add_generic_css_and_js($module_path, $settings = NULL) {
  foreach (H5PCore::$adminScripts as $script) {
    drupal_add_js($module_path . '/library/' . $script);
  }

  if ($settings === NULL) {
    $settings = array();
  }

  $settings['containerSelector'] = '#h5p-admin-container';
  $settings['l10n'] = array(
    'NA' => t('N/A'),
    'viewLibrary' => t('View library details'),
    'deleteLibrary' => t('Delete library'),
    'upgradeLibrary' => t('Upgrade library content')
  );

  drupal_add_js('H5PAdminIntegration = ' . json_encode($settings) . ';', 'inline');
  drupal_add_css($module_path . '/library/styles/h5p.css');
  drupal_add_css($module_path . '/library/styles/h5p-admin.css');

  drupal_add_js(array(
    'h5p' => h5p_get_core_settings()
  ), 'setting');
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
  $contents = db_query("SELECT content_id FROM {h5p_nodes} WHERE filtered = ''");
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

  $results = db_query('SELECT hl2.library_id as id, hl2.machine_name as name, hl2.title, hl2.major_version, hl2.minor_version, hl2.patch_version FROM {h5p_libraries} hl1 JOIN {h5p_libraries} hl2 ON hl1.machine_name = hl2.machine_name WHERE hl1.library_id = :id ORDER BY hl2.title ASC, hl2.major_version ASC, hl2.minor_version ASC', array(':id' => $library_id));
  $versions = array();
  foreach ($results as $result) {
    $versions[$result->id] = $result;
  }
  $library = $versions[$library_id];
  $upgrades = $core->getUpgrades($library, $versions);

  drupal_set_title(t('Upgrade @library content', array('@library' => $library->title . ' (' . H5PCore::libraryVersion($library) . ')')));
  if (count($versions) < 2) {
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
  $settings = array(
    'libraryInfo' => array(
      'message' => t('You are about to upgrade %num. Please select upgrade version.', array('%num' => $contents_plural)),
      'inProgress' => t('Upgrading to %ver...'),
      'error' => t('An error occurred while processing parameters:'),
      'errorData' => t('Could not load data for library %lib.'),
      'errorScript' => t('Could not load upgrades script for %lib.'),
      'errorContent' => t('Could not upgrade content %id:'),
      'errorParamsBroken' => t('Parameters are broken.'),
      'done' => t('You have successfully upgraded %num.', array('%num' => $contents_plural)) . ($return ? ' ' . l(t('Return'), $return) : ''),
      'library' => array(
        'name' => $library->name,
        'version' => $library->major_version . '.' . $library->minor_version,
      ),
      'libraryBaseUrl' => url('admin/content/h5p/upgrade/library'),
      'scriptBaseUrl' => base_path() . drupal_get_path('module', 'h5p') . '/library/js',
      'buster' => '?' . variable_get('css_js_query_string', ''),
      'versions' => $upgrades,
      'contents' => $contents,
      'buttonLabel' => t('Upgrade'),
      'infoUrl' => url('admin/content/h5p/libraries/' . $library_id . '/upgrade'),
      'total' => $contents,
      'token' => H5PCore::createToken('contentupgrade'), // Use token to avoid unauthorized updating
    )
  );

  // Add JavaScripts
  $module_path = drupal_get_path('module', 'h5p');
  _h5p_admin_add_generic_css_and_js($module_path, $settings);
  drupal_add_js($module_path . '/library/js/h5p-version.js');
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
  if (!H5PCore::validToken('contentupgrade', filter_input(INPUT_POST, 'token'))) {
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
  $out->token = H5PCore::createToken('contentupgrade');

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
          'json_content' => $param,
          'filtered' => ''
        ))
        ->condition('content_id', $id)
        ->execute();

      // Log content upgrade successful
      $title = db_query("SELECT title FROM {node} WHERE nid = :id", array(':id' => $id))->fetchField();
      new H5PEvent('content', 'upgrade',
        $id,
        $title,
        $to_library->name,
        $to_library->major_version . '.' . $to_library->minor_version);

      // Clear content cache
      $interface->updateContentFields($id, array(
        'filtered' => ''
      ));
    }
  }

  // Get number of contents for this library
  $out->left = $interface->getNumContent($library_id);

  if ($out->left) {
    // Find the 10 first contents using library and add to params
    $contents = db_query('SELECT content_id AS id, json_content AS params FROM {h5p_nodes} WHERE main_library_id = :id LIMIT 40', array(':id' => $library_id));
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

  $upgrades_script = _h5p_get_h5p_path() . (isset($dev_lib) ? '/'. $dev_lib['path'] : '/libraries/' . $library->name . '-' . $library->version->major . '.' . $library->version->minor) . '/upgrades.js';
  if (file_exists($upgrades_script)) {
    $library->upgradesScript = base_path() . $upgrades_script;
  }

  drupal_add_http_header('Cache-Control', 'no-cache');
  drupal_add_http_header('Content-type', 'application/json');
  print json_encode($library);
}

function h5p_restrict_library_callback($library_id) {
  $restricted = filter_input(INPUT_GET, 'restrict');
  $restrict = ($restricted === '1');

  $token_id = filter_input(INPUT_GET, 'token_id');
  if (!H5PCore::validToken('library_' . $token_id, filter_input(INPUT_GET, 'token')) || (!$restrict && $restricted !== '0')) {
    return MENU_ACCESS_DENIED;
  }

  db_update('h5p_libraries')
    ->fields(array(
      'restricted' => $restricted
    ))
    ->condition('library_id', $library_id)
    ->execute();

  print json_encode(array(
    'url' => url('admin/content/h5p/libraries/' . $library_id . '/restrict', array(
      'query' => array(
        'token' => H5PCore::createToken('library_' . $token_id),
        'token_id' => $token_id,
        'restrict' => ($restrict ? 0 : 1),
      )
    )),
  ));
}
