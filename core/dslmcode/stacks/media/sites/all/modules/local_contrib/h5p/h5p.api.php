<?php
/**
 * @file
 * Describe hooks provided by the H5P module.
 */

/**
 * Alter a library's semantics
 *
 * May be used to add more fields to a library, change a widget, add more allowed tags for
 * a textfield etc
 *
 * @param array $semantics
 * A libraries definition of the data the library uses
 * @param string $machine_name
 * The libraries machine name
 * @param int $major_version
 * Major version for the library
 * @param int $minor_version
 * Minor version fot the library
 */
function hook_h5p_semantics_alter(&$semantics, $machine_name, $major_version, $minor_version) {
  // In this example implementation we add <h4> as an allowed tag in H5P.Text 1.0
  if ($machine_name == 'H5P.Text' && $major_version == 1 && $minor_version == 0) {
    $semantics[0]->tags[] = 'h4';
  }
}

/**
 * Alter an H5Ps parameters
 *
 * May be used to alter the content itself or the behaviour of the H5P
 *
 * @param type $filtered
 *  json object
 */
function hook_h5p_filtered_params_alter(&$filtered) {
  // Example code from the Quiz module
  // Disables the retry and solutions options at the end of H5P questions
  if (_quiz_is_taking_context()) {
    if (isset($filtered->behaviour)) {
      $quiz = quiz_get_quiz_from_menu();
      if (isset($filtered->behaviour->enableRetry)) {
        $filtered->behaviour->enableRetry = FALSE;
      }
      if (isset($filtered->behaviour->enableSolutionsButton)) {
        $filtered->behaviour->enableSolutionsButton = $quiz->display_feedback && $quiz->feedback_time == QUIZ_FEEDBACK_QUESTION;
      }
    }
  }
}

/**
 * Add styles to H5Ps
 *
 * @param array $styles
 *  Array of objects with properties path and version. Version is on the form
 *  ?ver=1.0.2 and is used as a cache buster
 * @param array $libraries
 *  Array of libraries indexed by the library's machineName and with an array
 *  as value. The value has the properties majorVersion and minorVersion
 * @param string $mode
 *  What mode are we in? Possible values are "editor", "div", "iframe" and "external"
 */
function hook_h5p_styles_alter(&$styles, $libraries, $mode) {
  if (isset($libraries['H5P.MultiChoice']) && $libraries['H5P.MultiChoice']['majorVersion'] == '1') {
    $styles[] = (object) array(
      // Path relative to drupal root
      'path' => drupal_get_path('module', 'mymodule') . '/h5p-overrides.css',
      // Cache buster
      'version' => '?ver=1',
    );
  }
}

/**
 * Add scripts to h5ps
 *
 * @param array $scripts
 *  Array of objects with properties path and version. Version is on the form
 *  ?ver=1.0.2 and is used as a cache buster
 * @param array $libraries
 *  Array of libraries indexed by the library's machineName and with an array
 *  as value. The value has the properties majorVersion and minorVersion
 * @param string $mode
 *  What mode are we in? Possible values are "editor", "div", "iframe" and "external"
 */
function hook_h5p_scripts_alter(&$scripts, $libraries, $mode) {
  if (isset($libraries['H5P.MultiChoice']) && $libraries['H5P.MultiChoice']['majorVersion'] == '1') {
    $scripts[] = (object) array(
      // Path relative to drupal root
      'path' => drupal_get_path('module', 'mymodule') . '/h5p-overrides.js',
      // Cache buster
      'version' => '?ver=1',
    );
  }
}

/**
 * Hook is invoked whenever an H5P library has been installed/updated. It is created
 * to be able to run other actions, not to alter input data.
 *
 * @param array $libraryData
 *  This associative array contains everything found in library.json
 * @param boolean $isNew
 *  If this is a new library, this will be TRUE, otherwise FALSE
 */
function hook_h5p_library_installed($libraryData, $isNew) {
  $machineName = $libraryData['machineName'];
}

?>
