<?php

/**
 * @file
 * A file to contain functions for the magic module to abuse.
 */

/**
 * Returns a themed presentation of all JavaScript code for the current page.
 *
 * References to JavaScript files are placed in a certain order: first, all
 * 'core' files, then all 'module' and finally all 'theme' JavaScript files
 * are added to the page. Then, all settings are output, followed by 'inline'
 * JavaScript code. If running update.php, all preprocessing is disabled.
 *
 * Note that hook_js_alter(&$javascript) is called during this function call
 * to allow alterations of the JavaScript during its presentation. Calls to
 * magic_add_js() from hook_js_alter() will not be added to the output
 * presentation. The correct way to add JavaScript during hook_js_alter()
 * is to add another element to the $javascript array, deriving from
 * drupal_js_defaults(). See locale_js_alter() for an example of this.
 *
 * @param $scope
 *   (optional) The scope for which the JavaScript rules should be returned.
 *   Defaults to 'header'.
 * @param $javascript
 *   (optional) An array with all JavaScript code. Defaults to the default
 *   JavaScript array for the given scope.
 * @param $skip_alter
 *   (optional) If set to TRUE, this function skips calling drupal_alter() on
 *   $javascript, useful when the calling function passes a $javascript array
 *   that has already been altered.
 *
 * @return
 *   All JavaScript code segments and includes for the scope as HTML tags.
 *
 * @see magic_add_js()
 * @see locale_js_alter()
 * @see drupal_js_defaults()
 */
function magic_experimental_js($scope = 'header', $javascript = NULL, $skip_alter = FALSE) {
  if (!isset($javascript)) {
    $javascript = magic_add_js();
  }
  if (empty($javascript)) {
    return '';
  }

  // Allow modules to alter the JavaScript.
  if (!$skip_alter) {
    drupal_alter('js', $javascript);
  }

  // Check to see if Force Header is available and set to true.
  // If it is neither enabled nor set to true, change scope to footer,
  // otherwise, keep it in the header.
  // Done again here because scope may change on alter.
  foreach ($javascript as $js_key => $js_value) {
    if (!empty($js_value['force header'])) {
      $javascript[$js_key]['scope'] = 'header';
    }
    else {
      $javascript[$js_key]['scope'] = 'footer';
    }
  }

  // Check to see if Force Header is available and set to true.
  // If it is neither enabled nor set to true, change scope to footer, otherwise, keep it in the header.
  // Done here because scope may change on alter. Screw Inversion of control.

  // Get Magic Library Head variable for current theme.
  $library_head = theme_get_setting('magic_library_head');
  $footer_js = theme_get_setting('magic_footer_js');

  if ($footer_js) {
    foreach ($javascript as $js_key => $js_value) {
      if (!empty($js_value['force header']) && $js_value['force header']) {
        $javascript[$js_key]['scope'] = 'header';
      }
      else {
        $javascript[$js_key]['scope'] = 'footer';
      }

      if ($js_value['group'] == JS_LIBRARY && $library_head) {
        $javascript[$js_key]['scope'] = 'header';
      }

      if ($js_key === 'settings') {
        $javascript[$js_key]['scope'] = 'header';
      }
    }
  }

  // Filter out elements of the given scope.
  $items = array();
  foreach ($javascript as $key => $item) {
    if ($item['scope'] == $scope) {
      $items[$key] = $item;
    }
  }

  // Sort the JavaScript so that it appears in the correct order.
  uasort($items, 'magic_sort_css_js');

  // In Drupal 8, there's a JS_SETTING group for making setting variables
  // appear last after libraries have loaded. In Drupal 7, this is forced
  // without that group. We do not use the $key => $item type of iteration,
  // because PHP uses an internal array pointer for that, and we're modifying
  // the array order inside the loop.
  foreach (array_keys($items) as $key) {
    if (!empty($items[$key]['type']) && $items[$key]['type'] == 'setting') {
      $item = $items[$key];
      unset($items[$key]);
      $items[$key] = $item;
    }
  }

  // Provide the page with information about the individual JavaScript files
  // used, information not otherwise available when aggregation is enabled.
  $setting['ajaxPageState']['js'] = array_fill_keys(array_keys($items), 1);
  unset($setting['ajaxPageState']['js']['settings']);
  drupal_add_js($setting, 'setting');

  // If we're outputting the header scope, then this might be the final time
  // that drupal_get_js() is running, so add the setting to this output as well
  // as to the drupal_add_js() cache. If $items['settings'] doesn't exist, it's
  // because drupal_get_js() was intentionally passed a $javascript argument
  // stripped of settings, potentially in order to override how settings get
  // output, so in this case, do not add the setting to this output.
  if ($scope == 'header' && isset($items['settings'])) {
    $items['settings']['data'][] = $setting;
  }

  // Render the HTML needed to load the JavaScript.
  $elements = array(
    '#type' => 'scripts',
    '#items' => $items,
  );

  return drupal_render($elements);
}

/**
 * Adds a JavaScript file, setting, or inline code to the page.
 *
 * The behavior of this function depends on the parameters it is called with.
 * Generally, it handles the addition of JavaScript to the page, either as
 * reference to an existing file or as inline code. The following actions can be
 * performed using this function:
 * - Add a file ('file'): Adds a reference to a JavaScript file to the page.
 * - Add inline JavaScript code ('inline'): Executes a piece of JavaScript code
 *   on the current page by placing the code directly in the page (for example,
 *   to tell the user that a new message arrived, by opening a pop up, alert
 *   box, etc.). This should only be used for JavaScript that cannot be executed
 *   from a file. When adding inline code, make sure that you are not relying on
 *   $() being the jQuery function. Wrap your code in
 *   @code (function ($) {... })(jQuery); @endcode
 *   or use jQuery() instead of $().
 * - Add external JavaScript ('external'): Allows the inclusion of external
 *   JavaScript files that are not hosted on the local server. Note that these
 *   external JavaScript references do not get aggregated when preprocessing is
 *   on.
 * - Add settings ('setting'): Adds settings to Drupal's global storage of
 *   JavaScript settings. Per-page settings are required by some modules to
 *   function properly. All settings will be accessible at Drupal.settings.
 *
 * Examples:
 * @code
 *   magic_add_js('misc/collapse.js');
 *   magic_add_js('misc/collapse.js', 'file');
 *   magic_add_js('jQuery(document).ready(function () { alert("Hello!"); });', 'inline');
 *   magic_add_js('jQuery(document).ready(function () { alert("Hello!"); });',
 *     array('type' => 'inline', 'scope' => 'footer', 'weight' => 5)
 *   );
 *   magic_add_js('http://example.com/example.js', 'external');
 *   magic_add_js(array('myModule' => array('key' => 'value')), 'setting');
 * @endcode
 *
 * Calling drupal_static_reset('magic_add_js') will clear all JavaScript added
 * so far.
 *
 * If JavaScript aggregation is enabled, all JavaScript files added with
 * $options['preprocess'] set to TRUE will be merged into one aggregate file.
 * Preprocessed inline JavaScript will not be aggregated into this single file.
 * Externally hosted JavaScripts are never aggregated.
 *
 * The reason for aggregating the files is outlined quite thoroughly here:
 * http://www.die.net/musings/page_load_time/ "Load fewer external objects. Due
 * to request overhead, one bigger file just loads faster than two smaller ones
 * half its size."
 *
 * $options['preprocess'] should be only set to TRUE when a file is required for
 * all typical visitors and most pages of a site. It is critical that all
 * preprocessed files are added unconditionally on every page, even if the
 * files are not needed on a page. This is normally done by calling
 * magic_add_js() in a hook_init() implementation.
 *
 * Non-preprocessed files should only be added to the page when they are
 * actually needed.
 *
 * @param $data
 *   (optional) If given, the value depends on the $options parameter:
 *   - 'file': Path to the file relative to base_path().
 *   - 'inline': The JavaScript code that should be placed in the given scope.
 *   - 'external': The absolute path to an external JavaScript file that is not
 *     hosted on the local server. These files will not be aggregated if
 *     JavaScript aggregation is enabled.
 *   - 'setting': An associative array with configuration options. The array is
 *     merged directly into Drupal.settings. All modules should wrap their
 *     actual configuration settings in another variable to prevent conflicts in
 *     the Drupal.settings namespace. Items added with a string key will replace
 *     existing settings with that key; items with numeric array keys will be
 *     added to the existing settings array.
 * @param $options
 *   (optional) A string defining the type of JavaScript that is being added in
 *   the $data parameter ('file'/'setting'/'inline'/'external'), or an
 *   associative array. JavaScript settings should always pass the string
 *   'setting' only. Other types can have the following elements in the array:
 *   - type: The type of JavaScript that is to be added to the page. Allowed
 *     values are 'file', 'inline', 'external' or 'setting'. Defaults
 *     to 'file'.
 *   - scope: The location in which you want to place the script. Possible
 *     values are 'header' or 'footer'. If your theme implements different
 *     regions, you can also use these. Defaults to 'header'.
 *   - group: A number identifying the group in which to add the JavaScript.
 *     Available constants are:
 *     - JS_LIBRARY: Any libraries, settings, or jQuery plugins.
 *     - JS_DEFAULT: Any module-layer JavaScript.
 *     - JS_THEME: Any theme-layer JavaScript.
 *     The group number serves as a weight: JavaScript within a lower weight
 *     group is presented on the page before JavaScript within a higher weight
 *     group.
 *   - every_page: For optimal front-end performance when aggregation is
 *     enabled, this should be set to TRUE if the JavaScript is present on every
 *     page of the website for users for whom it is present at all. This
 *     defaults to FALSE. It is set to TRUE for JavaScript files that are added
 *     via module and theme .info files. Modules that add JavaScript within
 *     hook_init() implementations, or from other code that ensures that the
 *     JavaScript is added to all website pages, should also set this flag to
 *     TRUE. All JavaScript files within the same group and that have the
 *     'every_page' flag set to TRUE and do not have 'preprocess' set to FALSE
 *     are aggregated together into a single aggregate file, and that aggregate
 *     file can be reused across a user's entire site visit, leading to faster
 *     navigation between pages. However, JavaScript that is only needed on
 *     pages less frequently visited, can be added by code that only runs for
 *     those particular pages, and that code should not set the 'every_page'
 *     flag. This minimizes the size of the aggregate file that the user needs
 *     to download when first visiting the website. JavaScript without the
 *     'every_page' flag is aggregated into a separate aggregate file. This
 *     other aggregate file is likely to change from page to page, and each new
 *     aggregate file needs to be downloaded when first encountered, so it
 *     should be kept relatively small by ensuring that most commonly needed
 *     JavaScript is added to every page.
 *   - weight: A number defining the order in which the JavaScript is added to
 *     the page relative to other JavaScript with the same 'scope', 'group',
 *     and 'every_page' value. In some cases, the order in which the JavaScript
 *     is presented on the page is very important. jQuery, for example, must be
 *     added to the page before any jQuery code is run, so jquery.js uses the
 *     JS_LIBRARY group and a weight of -20, jquery.once.js (a library drupal.js
 *     depends on) uses the JS_LIBRARY group and a weight of -19, drupal.js uses
 *     the JS_LIBRARY group and a weight of -1, other libraries use the
 *     JS_LIBRARY group and a weight of 0 or higher, and all other scripts use
 *     one of the other group constants. The exact ordering of JavaScript is as
 *     follows:
 *     - First by scope, with 'header' first, 'footer' last, and any other
 *       scopes provided by a custom theme coming in between, as determined by
 *       the theme.
 *     - Then by group.
 *     - Then by the 'every_page' flag, with TRUE coming before FALSE.
 *     - Then by weight.
 *     - Then by the order in which the JavaScript was added. For example, all
 *       else being the same, JavaScript added by a call to magic_add_js() that
 *       happened later in the page request gets added to the page after one for
 *       which magic_add_js() happened earlier in the page request.
 *   - defer: If set to TRUE, the defer attribute is set on the &lt;script&gt;
 *     tag. Defaults to FALSE.
 *   - cache: If set to FALSE, the JavaScript file is loaded anew on every page
 *     call; in other words, it is not cached. Used only when 'type' references
 *     a JavaScript file. Defaults to TRUE.
 *   - preprocess: If TRUE and JavaScript aggregation is enabled, the script
 *     file will be aggregated. Defaults to TRUE.
 *
 * @return
 *   The current array of JavaScript files, settings, and in-line code,
 *   including Drupal defaults, anything previously added with calls to
 *   magic_add_js(), and this function call's additions.
 *
 * @see magic_get_js()
 */
function magic_add_js($data = NULL, $options = NULL) {

  $javascript = &drupal_static('drupal_add_js', array());

  // Construct the options, taking the defaults into consideration.
  if (isset($options)) {
    if (!is_array($options)) {
      $options = array('type' => $options);
    }
  }
  else {
    $options = array();
  }
  $options += magic_js_defaults($data);

  // Preprocess can only be set if caching is enabled.
  $options['preprocess'] = $options['cache'] ? $options['preprocess'] : FALSE;

  // Tweak the weight so that files of the same weight are included in the
  // order of the calls to magic_add_js().
  $options['weight'] += count($javascript) / 1000;

  if (isset($data)) {
    // Add jquery.js and drupal.js, as well as the basePath setting, the
    // first time a JavaScript file is added.
    if (empty($javascript)) {
      // url() generates the prefix using hook_url_outbound_alter(). Instead of
      // running the hook_url_outbound_alter() again here, extract the prefix
      // from url().
      url('', array('prefix' => &$prefix));
      $javascript = array(
        'settings' => array(
          'data' => array(
            array('basePath' => base_path()),
            array('pathPrefix' => empty($prefix) ? '' : $prefix),
          ),
          'type' => 'setting',
          'scope' => 'header',
          'group' => JS_LIBRARY,
          'every_page' => TRUE,
          'weight' => 0,
        ),
        'misc/drupal.js' => array(
          'data' => 'misc/drupal.js',
          'type' => 'file',
          'scope' => 'header',
          'group' => JS_LIBRARY,
          'every_page' => TRUE,
          'weight' => -1,
          'preprocess' => TRUE,
          'cache' => TRUE,
          'defer' => FALSE,
        ),
      );
      // Register all required libraries.
      drupal_add_library('system', 'jquery', TRUE);
      drupal_add_library('system', 'jquery.once', TRUE);
    }

    switch ($options['type']) {
      case 'setting':
        // All JavaScript settings are placed in the header of the page with
        // the library weight so that inline scripts appear afterwards.
        $javascript['settings']['data'][] = $data;
        break;

      case 'inline':
        $javascript[] = $options;
        break;

      default: // 'file' and 'external'
        // Local and external files must keep their name as the associative key
        // so the same JavaScript file is not added twice.
        $javascript[$options['data']] = $options;
    }
  }

  // Update JavaScript files to include async, defer, and force header options
  // if they don't already have them.
  foreach ($javascript as $js_key => $js_value) {
    if (empty($js_value['async'])) {
      $javascript[$js_key]['async'] = FALSE;
    }
    if (empty($js_value['defer'])) {
      $javascript[$js_key]['defer'] = FALSE;
    }
    if (empty($js_value['force header'])) {
      $javascript[$js_key]['force header'] = FALSE;
    }
  }

  return $javascript;
}

/**
 * Constructs an array of the defaults that are used for JavaScript items.
 *
 * @param $data
 *   (optional) The default data parameter for the JavaScript item array.
 *
 * @see magic_get_js()
 * @see magic_add_js()
 */
function magic_js_defaults($data = NULL) {
  return array(
    'type' => 'file',
    'group' => JS_DEFAULT,
    'every_page' => FALSE,
    'weight' => 0,
    'scope' => 'footer',
    'defer' => FALSE,
    'async' => FALSE,
    'cache' => TRUE,
    'defer' => FALSE,
    'preprocess' => TRUE,
    'version' => NULL,
    'data' => $data,
  );
}

/**
 * Default callback to group JavaScript items.
 *
 * This function arranges the JavaScript items that are in the #items property
 * of the scripts element into groups. When aggregation is enabled, files within
 * a group are aggregated into a single file, significantly improving page
 * loading performance by minimizing network traffic overhead.
 *
 * This function puts multiple items into the same group if they are groupable
 * and if they are for the same browsers. Items of the 'file' type are groupable
 * if their 'preprocess' flag is TRUE. Items of the 'inline', 'settings', or
 * 'external' type are not groupable.
 *
 * This function also ensures that the process of grouping items does not change
 * their relative order. This requirement may result in multiple groups for the
 * same type and browsers, if needed to accommodate other items in
 * between.
 *
 * @param $javascript
 *   An array of JavaScript items, as returned by drupal_add_js(), but after
 *   alteration performed by drupal_get_js().
 *
 * @return
 *   An array of JavaScript groups. Each group contains the same keys (e.g.,
 *   'data', etc.) as a JavaScript item from the $javascript parameter, with the
 *   value of each key applying to the group as a whole. Each group also
 *   contains an 'items' key, which is the subset of items from $javascript that
 *   are in the group.
 *
 * @see drupal_pre_render_scripts()
 */
function magic_group_js($javascript) {
  $groups = array();
  // If a group can contain multiple items, we track the information that must
  // be the same for each item in the group, so that when we iterate the next
  // item, we can determine if it can be put into the current group, or if a
  // new group needs to be made for it.
  $current_group_keys = NULL;
  $index = -1;

  $ordering_array = array();

  foreach ($javascript as &$item) {
    $item['browsers'] = isset($item['browsers']) ? $item['browsers'] : array();
    $item['browsers'] += array(
      'IE'
    );

    // As these are not native in Drupal, we add in the default values.
    $item += array(
      'defer' => FALSE,
      'async' => FALSE,
      'type' => '',
    );

    // The browsers for which the JavaScript item needs to be loaded is part of
    // the information that determines when a new group is needed, but the order
    // of keys in the array doesn't matter, and we don't want a new group if all
    // that's different is that order.
    ksort($item['browsers']);

    // We are first going to ensure that all the javascript is in the right
    // order.
    $group = $item['group'];

    $weight = $item['weight'];
    // We are chaging the weight of the files, so that ones flagged with
    // every_page are put first.
    $weight += $item['every_page'] ? -10000 : 10000;
    $grouped_items[$group][] = $item;
    $ordering_array[$group][] = $weight;
  }

  // This will sort all the groups to ensure we are in the right order.
  ksort($grouped_items);
  ksort($ordering_array);

  foreach ($grouped_items as $group => $items) {
    // Now we go into each group, and sort by the individual weight. This will
    // also take into effect the every_page tag.
    array_multisort($ordering_array[$group], SORT_NUMERIC, $items);

    foreach ($items as $item) {
      switch ($item['type']) {
        case 'file':
          // Group file items if their 'preprocess' flag is TRUE.
          // Help ensure maximum reuse of aggregate files by only grouping
          // together items that share the same 'group' value and 'every_page'
          // flag. See drupal_add_js() for details about that.
          $group_keys = !empty($item['preprocess']) ? array($item['every_page'], $item['browsers'], $item['defer']) : FALSE;
        break;

        case 'external':
        case 'inline':
        case 'setting':
        default:
          // Do not group external, settings, and inline items.
          $group_keys = FALSE;
        break;
      }

      // If the group keys don't match the most recent group we're working with,
      // then a new group must be made. Also, each inline, external, or setting
      // script will also be in their own group.
      if ((!empty($group_keys) && $group_keys !== $current_group_keys) || $group_keys == FALSE) {
        $index++;
        // We set the base settings to the first object, for reference later on.
        $groups[$index] = $item;
        $current_group_keys = $group_keys;
      }

      $groups[$index]['items'][] = $item;
    }
  }

  return $groups;
}

/**
 * #pre_render callback to add the elements needed for JavaScript tags to be
 * rendered.
 *
 * This function evaluates the aggregation enabled/disabled condition on a group
 * by group basis by testing whether an aggregate file has been made for the
 * group rather than by testing the site-wide aggregation setting. This allows
 * this function to work correctly even if modules have implemented custom
 * logic for grouping and aggregating files.
 *
 * @param $element
 *   A render array containing:
 *   - #items: The JavaScript items as returned by drupal_add_js() and
 *     altered by drupal_get_js().
 *   - #group_callback: A function to call to group #items. Following
 *     this function, #aggregate_callback is called to aggregate items within
 *     the same group into a single file.
 *   - #aggregate_callback: A function to call to aggregate the items within
 *     the groups arranged by the #group_callback function.
 *
 * @return
 *   A render array that will render to a string of JavaScript tags.
 *
 * @see drupal_get_js()
 */
function magic_pre_render_scripts($elements) {

  // Group and aggregate the items.
  if (isset($elements['#group_callback'])) {
    $elements['#groups'] = $elements['#group_callback']($elements['#items']);
  }
  if (isset($elements['#aggregate_callback'])) {
    $elements['#aggregate_callback']($elements['#groups']);
  }

  // A dummy query-string is added to filenames, to gain control over
  // browser-caching. The string changes on every update or full cache
  // flush, forcing browsers to load a new copy of the files, as the
  // URL changed. Files that should not be cached (see drupal_add_js())
  // get REQUEST_TIME as query-string instead, to enforce reload on every
  // page request.
  $default_query_string = variable_get('css_js_query_string', '0');

  // For inline JavaScript to validate as XHTML, all JavaScript containing
  // XHTML needs to be wrapped in CDATA. To make that backwards compatible
  // with HTML 4, we need to comment out the CDATA-tag.
  $embed_prefix = "\n<!--//--><![CDATA[//><!--\n";
  $embed_suffix = "\n//--><!]]>\n";

  // Since JavaScript may look for arguments in the URL and act on them, some
  // third-party code might require the use of a different query string.
  $js_version_string = variable_get('drupal_js_version_query_string', 'v=');

  // Defaults for each SCRIPT element.
  $element_defaults = array(
    '#type' => 'html_tag',
    '#tag' => 'script',
    '#value' => '',
    '#attributes' => array(
      'type' => 'text/javascript',
    ),
  );

  // Loop through each group.
  foreach ($elements['#groups'] as $group) {
    // If a group of files has been aggregated into a single file,
    // $group['data'] contains the URI of the aggregate file. Add a single
    // script element for this file.
    if (!empty($group['type']) && $group['type'] == 'file' && isset($group['data'])) {
      $element = $element_defaults;
      $element['#attributes']['src'] = file_create_url($group['data']);
      $element['#browsers'] = $group['browsers'];
      $elements[] = $element;
    }
    // For non-file types, and non-aggregated files, add a script element per
    // item.
    else {
      foreach ($group['items'] as $item) {
        // Element properties that do not depend on item type.
        $element = $element_defaults;
        if (!empty($item['defer'])) {
          $element['#attributes']['defer'] = 'defer';
        }
        if (!empty($item['async'])) {
          $element['#attributes']['async'] = 'async';
        }
        $element['#browsers'] = $item['browsers'];

        if (!empty($item['type'])) {
          // Element properties that depend on item type.
          switch ($item['type']) {
            case 'setting':
              $element['#value_prefix'] = $embed_prefix;
              $element['#value'] = 'jQuery.extend(Drupal.settings, ' . drupal_json_encode(drupal_array_merge_deep_array($item['data'])) . ");";
              $element['#value_suffix'] = $embed_suffix;
              break;

            case 'inline':
              $element['#value_prefix'] = $embed_prefix;
              $element['#value'] = $item['data'];
              $element['#value_suffix'] = $embed_suffix;
              break;

            case 'file':
              $query_string = empty($item['version']) ? $default_query_string : $js_version_string . $item['version'];
              $query_string_separator = (strpos($item['data'], '?') !== FALSE) ? '&' : '?';
              $element['#attributes']['src'] = file_create_url($item['data']) . $query_string_separator . ($item['cache'] ? $query_string : REQUEST_TIME);
              break;

            case 'external':
              $element['#attributes']['src'] = $item['data'];
              break;
          }
        }

        $elements[] = $element;
      }
    }
  }
  return $elements;
}

/**
 * Default callback to aggregate JavaScript files.
 *
 * Having the browser load fewer JavaScript files results in much faster page
 * loads than when it loads many small files. This function aggregates files
 * within the same group into a single file unless the site-wide setting to do
 * so is disabled (commonly the case during site development). To optimize
 * download, it also compresses the aggregate files by removing comments,
 * whitespace, and other unnecessary content.
 *
 * @param $js_groups
 *   An array of JavaScript groups as returned by drupal_group_js(). For each
 *   group that is aggregated, this function sets the value of the group's
 *   'data' key to the URI of the aggregate file.
 *
 * @see drupal_group_js()
 * @see drupal_pre_render_scripts()
 */
function magic_aggregate_js(&$js_groups) {
  // Only aggregate when the site is configured to do so, and not during an
  // update.
  if (variable_get('preprocess_js', FALSE) && (!defined('MAINTENANCE_MODE') || MAINTENANCE_MODE != 'update')) {
    foreach ($js_groups as $key => $group) {
      if (isset($group['type']) && $group['type'] == 'file' && $group['preprocess']) {
        $js_groups[$key]['data'] = magic_build_js_cache($group['items']);
      }
    }
  }
}

/**
 * Aggregates JavaScript files into a cache file in the files directory.
 *
 * The file name for the JavaScript cache file is generated from the hash of
 * the aggregated contents of the files in $files. This forces proxies and
 * browsers to download new JavaScript when the JavaScript changes.
 *
 * The cache file name is retrieved on a page load via a lookup variable that
 * contains an associative array. The array key is the hash of the names in
 * $files while the value is the cache file name. The cache file is generated
 * in two cases. First, if there is no file name value for the key, which will
 * happen if a new file name has been added to $files or after the lookup
 * variable is emptied to force a rebuild of the cache. Second, the cache file
 * is generated if it is missing on disk. Old cache files are not deleted
 * immediately when the lookup variable is emptied, but are deleted after a set
 * period by drupal_delete_file_if_stale(). This ensures that files referenced
 * by a cached page will still be available.
 *
 * @param $files
 *   An array of JavaScript files to aggregate and compress into one file.
 *
 * @return
 *   The URI of the cache file, or FALSE if the file could not be saved.
 */
function magic_build_js_cache($files) {
  $contents = '';
  $uri = '';
  $map = variable_get('drupal_js_cache_files', array());
  // Create a new array so that only the file names are used to create the hash.
  // This prevents new aggregates from being created unnecessarily.
  $js_data = array();
  foreach ($files as $file) {
    $js_data[] = $file['data'];
  }
  $key = hash('sha256', serialize($js_data));
  if (isset($map[$key])) {
    $uri = $map[$key];
  }

  if (empty($uri) || !file_exists($uri)) {
    // Build aggregate JS file.
    foreach ($files as $path => $info) {
      $info['preprocess'] = isset($info['preprocess']) ? $info['preprocess'] : FALSE;
      if ($info['preprocess']) {
        // Append a ';' and a newline after each JS file to prevent them from running together.
        $contents .= file_get_contents($info['data']) . ";\n";
      }
    }
    // Prefix filename to prevent blocking by firewalls which reject files
    // starting with "ad*".
    $filename = 'js_' . drupal_hash_base64($contents) . '.js';
    // Create the js/ within the files folder.
    $jspath = 'public://js';
    $uri = $jspath . '/' . $filename;
    // Create the JS file.
    file_prepare_directory($jspath, FILE_CREATE_DIRECTORY);
    if (!file_exists($uri) && !file_unmanaged_save_data($contents, $uri, FILE_EXISTS_REPLACE)) {
      return FALSE;
    }
    // If JS gzip compression is enabled, clean URLs are enabled (which means
    // that rewrite rules are working) and the zlib extension is available then
    // create a gzipped version of this file. This file is served conditionally
    // to browsers that accept gzip using .htaccess rules.
    if (variable_get('js_gzip_compression', TRUE) && variable_get('clean_url', 0) && extension_loaded('zlib')) {
      if (!file_exists($uri . '.gz') && !file_unmanaged_save_data(gzencode($contents, 9, FORCE_GZIP), $uri . '.gz', FILE_EXISTS_REPLACE)) {
        return FALSE;
      }
    }
    $map[$key] = $uri;
    variable_set('drupal_js_cache_files', $map);
  }
  return $uri;
}

/**
 * Sorts CSS and JavaScript resources.
 *
 * Callback for uasort() within:
 * - drupal_get_css()
 * - magic_experimental_js()
 *
 * This sort order helps optimize front-end performance while providing modules
 * and themes with the necessary control for ordering the CSS and JavaScript
 * appearing on a page.
 *
 * @param $a
 *   First item for comparison. The compared items should be associative arrays
 *   of member items from drupal_add_css() or magic_add_js().
 * @param $b
 *   Second item for comparison.
 *
 * @see drupal_add_css()
 * @see magic_add_js()
 */
function magic_sort_css_js($a, $b) {
  // First order by group, so that, for example, all items in the CSS_SYSTEM
  // group appear before items in the CSS_DEFAULT group, which appear before
  // all items in the CSS_THEME group. Modules may create additional groups by
  // defining their own constants.
  if (!empty($a['group']) && !empty($b['group'])) {
    if ($a['group'] < $b['group']) {
      return -1;
    }
    elseif ($a['group'] > $b['group']) {
      return 1;
    }
  }

  // Within a group, order all infrequently needed, page-specific files after
  // common files needed throughout the website. Separating this way allows for
  // the aggregate file generated for all of the common files to be reused
  // across a site visit without being cut by a page using a less common file.
  if (!empty($a['every_page']) && !empty($b['every_page'])) {
    if ($a['every_page'] && !$b['every_page']) {
      return -1;
    }
    elseif (!$a['every_page'] && $b['every_page']) {
      return 1;
    }
  }

  // Finally, order by weight.
  if (!empty($a['weight']) && !empty($b['weight'])) {
    if ($a['weight'] < $b['weight']) {
      return -1;
    }
    elseif ($a['weight'] > $b['weight']) {
      return 1;
    }
  }

  else {
    return 0;
  }
}
