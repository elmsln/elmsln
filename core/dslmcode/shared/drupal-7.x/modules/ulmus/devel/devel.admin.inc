<?php

/**
 * @file
 * Functions for Devel administrative pages.
 */

/**
 * Form constructor for the settings form.
 *
 * @ingroup forms
 */
function devel_admin_settings() {
  _devel_display_block_help_message();

  $form['queries'] = array('#type' => 'fieldset', '#title' => t('Query log'));

  $description = t('Display a log of the database queries needed to generate the current page, and the execution time for each. Also, queries which are repeated during a single page view are summed in the # column, and printed in red since they are candidates for caching.');
  if (!devel_is_compatible_optimizer()) {
    $description = t('You must disable or upgrade the php Zend Optimizer extension in order to enable this feature. The minimum required version is 3.2.8. Earlier versions of Zend Optimizer are <a href="!url">horribly buggy and segfault your Apache</a> ... ', array('!url' => url('http://drupal.org/node/126098'))) . $description;
  }
  $form['queries']['devel_query_display'] = array('#type' => 'checkbox',
    '#title' => t('Display query log'),
    '#default_value' => variable_get('devel_query_display', 0),
    '#description' => $description,
    '#disabled' => !devel_is_compatible_optimizer(),
  );
  $form['queries']['settings'] = array(
    '#type' => 'container',
      '#states' => array(
        // Hide the query log settings when not displaying query log.
        'invisible' => array(
          'input[name="devel_query_display"]' => array('checked' => FALSE),
        ),
      ),
  );
  $form['queries']['settings']['devel_show_query_args_first'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show query arguments'),
    '#default_value' => variable_get('devel_show_query_args_first', FALSE),
    '#description' => t('Show arguments rather than the query placeholders in the logged query.'),
  );
  $form['queries']['settings']['devel_query_sort'] = array('#type' => 'radios',
    '#title' => t('Sort query log'),
    '#default_value' =>   variable_get('devel_query_sort', DEVEL_QUERY_SORT_BY_SOURCE),
    '#options' => array(t('by source'), t('by duration')),
    '#description' => t('The query table can be sorted in the order that the queries were executed or by descending duration.'),
  );
  $form['queries']['settings']['devel_execution'] = array('#type' => 'textfield',
    '#title' => t('Slow query highlighting'),
    '#default_value' => variable_get('devel_execution', 5),
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('Enter an integer in milliseconds. Any query which takes longer than this many milliseconds will be highlighted in the query log. This indicates a possibly inefficient query, or a candidate for caching.'),
  );

  $form['devel_api_url'] = array('#type' => 'textfield',
    '#title' => t('API Site'),
    '#default_value' => variable_get('devel_api_url', 'api.drupal.org'),
    '#description' => t('The base URL for your developer documentation links. You might change this if you run <a href="!url">api.module</a> locally.', array('!url' => url('http://drupal.org/project/api'))));
  $form['devel_timer'] = array('#type' => 'checkbox',
    '#title' => t('Display page timer'),
    '#default_value' => variable_get('devel_timer', 0),
    '#description' => t('Display page execution time in the query log box.'),
  );

  $form['devel_memory'] = array('#type' => 'checkbox',
    '#title' => t('Display memory usage'),
    '#default_value' => variable_get('devel_memory', 0),
    '#description' => t('Display how much memory is used to generate the current page. This will show memory usage when devel_init() is called and when devel_exit() is called.'),
  );
  $form['devel_redirect_page'] = array('#type' => 'checkbox',
    '#title' => t('Display redirection page'),
    '#default_value' => variable_get('devel_redirect_page', 0),
    '#description' => t('When a module executes drupal_goto(), the query log and other developer information is lost. Enabling this setting presents an intermediate page to developers so that the log can be examined before continuing to the destination page.'),
  );
  $form['devel_page_alter'] = array('#type' => 'checkbox',
    '#title' => t('Display $page array'),
    '#default_value' => variable_get('devel_page_alter', FALSE),
    '#description' => t('Display $page array from <a href="http://api.drupal.org/api/function/hook_page_alter/7">hook_page_alter()</a> in the messages area of each page.'),
  );
  $form['devel_raw_names'] = array('#type' => 'checkbox',
    '#title' => t('Display machine names of permissions and modules'),
    '#default_value' => variable_get('devel_raw_names', FALSE),
    '#description' => t('Display the language-independent machine names of the permissions in mouse-over hints on the !Permissions page and the module base file names on the @Permissions and !Modules pages.', array('!Permissions' => l(t('Permissions'), 'admin/people/permissions'), '@Permissions' => t('Permissions'), '!Modules' => l(t('Modules'), 'admin/modules'))),
  );

  $error_handlers = devel_get_handlers();
  $form['devel_error_handlers'] = array(
    '#type' => 'select',
    '#title' => t('Error handlers'),
    '#options' => array(
      DEVEL_ERROR_HANDLER_NONE => t('None'),
      DEVEL_ERROR_HANDLER_STANDARD => t('Standard Drupal'),
      DEVEL_ERROR_HANDLER_BACKTRACE_DPM => t('Krumo backtrace in the message area'),
      DEVEL_ERROR_HANDLER_BACKTRACE_KRUMO => t('Krumo backtrace above the rendered page'),
    ),
    '#multiple' => TRUE,
    '#default_value' => empty($error_handlers) ? DEVEL_ERROR_HANDLER_NONE : $error_handlers,
    '#description' => t('Select the error handler(s) to use, in case you <a href="@choose">choose to show errors on screen</a>.', array('@choose' => url('admin/config/development/logging'))) . '<ul>' .
                      '<li>' . t('<em>None</em> is a good option when stepping through the site in your debugger.') . '</li>' .
                      '<li>' . t('<em>Standard Drupal</em> does not display all the information that is often needed to resolve an issue.') . '</li>' .
                      '<li>' . t('<em>Krumo backtrace</em> displays nice debug information when any type of error is noticed, but only to users with the %perm permission.', array('%perm' => t('Access developer information'))) . '</li></ul>' .
                      t('Depending on the situation, the theme, the size of the call stack and the arguments, etc., some handlers may not display their messages, or display them on the subsequent page. Select <em>Standard Drupal</em> <strong>and</strong> <em>Krumo backtrace above the rendered page</em> to maximize your chances of not missing any messages.') . '<br />' .
                      t('Demonstrate the current error handler(s):') . ' ' . l('notice+warning', $_GET['q'], array('query' => array('demo' => 'warning'))) . ', ' . l('notice+warning+error', $_GET['q'], array('query' => array('demo' => 'error'))) . ' ' . t('(The presentation of the @error is determined by PHP.)', array('@error' => 'error')),
  );
  $form['devel_error_handlers']['#size'] = count($form['devel_error_handlers']['#options']);
  if (empty($_POST) && !empty($_GET['demo'])) {
    devel_demonstrate_error_handlers($_GET['demo']);
  }

  $options = drupal_map_assoc(array('default', 'blue', 'green', 'orange', 'white', 'disabled'));
  $form['devel_krumo_skin'] = array(
    '#type' => 'radios',
    '#title' => t('Krumo display'),
    '#description' => t('Select a skin for your debug messages or select <em>disabled</em> to display object and array output in standard PHP format.'),
    '#options' => $options,
    '#default_value' => variable_get('devel_krumo_skin', 'default'),
  );

  $form['devel_rebuild_theme_registry'] = array(
   '#type' => 'checkbox',
   '#title' => t('Rebuild the theme registry on every page load'),
   '#description' => t('While creating new templates and theme_ overrides the theme registry needs to be rebuilt.'),
   '#default_value' => variable_get('devel_rebuild_theme_registry', FALSE),
  );

  $form['devel_use_uncompressed_jquery'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use uncompressed jQuery'),
    '#default_value' => variable_get('devel_use_uncompressed_jquery', FALSE),
    '#description' => t("Use a human-readable version of jQuery instead of the minified version that ships with Drupal, to make JavaScript debugging easier."),
  );

  return system_settings_form($form);
}

/**
 * Displays a helpful message if Menu module is not installed.
 */
function _devel_display_block_help_message() {
  if (!module_exists('menu')) {
    $devel_block_alert = t('Devel block alert: The Devel block requires the Core Menu module. The Devel block will become available once you <a href="!url">enable Menu</a>.',
      array('!url' => url('admin/modules'))
    );
    $variables = array(
      '!admin_menu_url' => url('https://drupal.org/project/admin_menu', array('external' => TRUE)),
      '!admin_menu_name' => 'Administration Menu',
      '!admin_menu_config_url' => url('admin/config/administration/admin_menu'),
      '!icon_menu' => t('Icon menu'),
    );
    if (!module_exists('admin_menu')) {
      $devel_block_alert .= '<br />' . t('Alternatively, you can install <a href="!admin_menu_url">!admin_menu_name</a> which supports displaying the Devel menu items in its !icon_menu.', $variables);
    }
    else {
      $admin_menu_components = variable_get('admin_menu_components', array());
      if (empty($admin_menu_components['admin_menu.icon']) || !user_access('access administration menu')) {
        $devel_block_alert .= '<br />' . t("Alternatively, if you <a href='!admin_menu_config_url'>enable !admin_menu_name's !icon_menu</a> you will find the Devel menu items there.", $variables);
      } else {
        // Don't bother with a message in the 'normal' case.
        return;
      }
    }
    drupal_set_message($devel_block_alert, 'warning');
  }
}

/**
 * Demonstrates the active error handler.
 *
 * Generates some warnings or errors so that the reaction of the current error
 * handler can be observed.
 *
 * @param $severity
 *   The severity level that the error handler should demonstrate.
 */
function devel_demonstrate_error_handlers($severity) {
  switch ($severity) {
    case 'warning':
      $undefined = $undefined;
      1/0;
      break;
    case 'error':
      $undefined = $undefined;
      1/0;
      devel_undefined_function();
      break;
  }
}
