<?php
/**
 * @file
 * Contains functions to alter Drupal's markup for the Aurora theme.
 *
 *        _d^^^^^^^^^b_
 *     .d''           ``b.
 *   .p'  @          @   `q.       NOTHING TO DO HERE
 *  .d'    ----------     `b.
 * .d'                     `b.
 * ::                       ::
 * ::                       ::
 * ::                       ::
 * `p.                     .q'
 *  `p.                   .q'
 *    `b.               .d'\
 *     / ^q...........p^    \
 *    /       ''''bbbbbbb    \
 *   /  __    __ \bbbbbbbb   /
 *    \_bbbbbbbb__\________/
 *       bb   bbbbbbbbbbbbbbb
 *                bb|bbbbbbb  ***
 *                 b|bbbbb   ******
 *       _______    |        **000***
 *     /         \  |         **00000**
 *   __|__________\/            ***   **
 *  /  |                         *      *
 * |    \
 * |      \__
 *  \
 *   \__
 *
 * The Aurora theme is a base theme designed to be easily extended by sub
 * themes. You should not modify this or any other file in the Aurora theme
 * folder. Instead, you should create a sub-theme and make your changes there.
 * In fact, if you're reading this, you may already off on the wrong foot.
 *
 * See the project page for more information:
 *   http://drupal.org/project/aurora
 */


//////////////////////////////
// Includes
//////////////////////////////
require_once dirname(__FILE__) . '/includes/theme.inc';
require_once dirname(__FILE__) . '/includes/pager.inc';
require_once dirname(__FILE__) . '/includes/messages.inc';

function aurora_preprocess_maintenance_page(&$vars, $hook) {
  // When a variable is manipulated or added in preprocess_html or
  // preprocess_page, that same work is probably needed for the maintenance page
  // as well, so we can just re-use those functions to do that work here.
  aurora_preprocess_html($vars);
}

function aurora_process_maintenance_page(&$vars, $hook) {
  // When a variable is manipulated or added in preprocess_html or
  // preprocess_page, that same work is probably needed for the maintenance page
  // as well, so we can just re-use those functions to do that work here.
  aurora_process_html($vars);
}


//////////////////////////////
// HTML5 Project Sideport
//////////////////////////////

/**
 * Implements hook_preprocess_html()
 */
function aurora_preprocess_html(&$vars) {
  // Viewport!
  $viewport = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'initial-scale=1.0',
    ),
  );
  drupal_add_html_head($viewport, 'viewport');

  // Force IE to use most up-to-date render engine.
  $xua = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'X-UA-Compatible',
      'content' => 'IE=edge',
    ),
  );

  drupal_add_html_head($xua, 'x-ua-compatible');

  $vars['minie'] = theme_get_setting('aurora_min_ie_support');

  //////////////////////////////
  // HTML5 Base Theme Forwardport
  //
  // Backports the following changes made to Drupal 8:
  // - #1077566: Convert html.tpl.php to HTML5.
  //////////////////////////////
  // Initializes attributes which are specific to the html and body elements.
  $vars['html_attributes_array'] = array();
  $vars['rdf_attributes_array'] = array();
  $vars['body_attributes_array'] = array();

  // HTML element attributes.
  $vars['html_attributes_array']['lang'] = $GLOBALS['language']->language;
  $vars['html_attributes_array']['dir'] = $GLOBALS['language']->direction ? 'rtl' : 'ltr';

  // Update RDF Namespacing
  if (module_exists('rdf')) {
    // Adds RDF namespace prefix bindings in the form of an RDFa 1.1 prefix
    // attribute inside the html element.
    $prefixes = array();
    foreach (rdf_get_namespaces() as $prefix => $uri) {
      $vars['rdf_attributes_array']['prefix'][] = $prefix . ': ' . $uri . "\n";
    }
  }

  //////////////////////////////
  // LiveReload Integration
  //////////////////////////////
  $livereload_port = theme_get_setting('aurora_livereload');
  if ($livereload_port) {
    if ($livereload_port == 'snugug') {
      $livereload_port = theme_get_setting('aurora_livereload_port');
      if (is_null($livereload_port)) {
        $livereload_port = 35729;
      }
    }

    drupal_add_js("document.write('<script src=\"http://' + (location.host || 'localhost').split(':')[0] + ':$livereload_port/livereload.js?snipver=1\"></' + 'script>')", array('type' => 'inline', 'scope' => 'footer', 'weight' => 9999));
  }

  //////////////////////////////
  // Add in TypeKit Code.
  //////////////////////////////
  if (theme_get_setting('aurora_typekit_id')) {
    drupal_add_js('(function(){var e={kitId:"' . theme_get_setting('aurora_typekit_id') . '",scriptTimeout:3e3},t=document.getElementsByTagName("html")[0];t.className+=" wf-loading";var n=setTimeout(function(){t.className=t.className.replace(/(\s|^)wf-loading(\s|$)/g," "),t.className+=" wf-inactive"},e.scriptTimeout),r=document.createElement("script"),i=!1;r.src="//use.typekit.net/"+e.kitId+".js",r.type="text/javascript",r.async="true",r.onload=r.onreadystatechange=function(){var t=this.readyState;if(i||t&&t!="complete"&&t!="loaded")return;i=!0,clearTimeout(n);try{Typekit.load(e)}catch(r){}};var s=document.getElementsByTagName("script")[0];s.parentNode.insertBefore(r,s)})()', array('type' => 'inline', 'force header' => true));
  }

}

/**
 * Implements hook_process_html().
 */
function aurora_process_html(&$vars) {

  //////////////////////////////
  // RWD Debug Integration
  //////////////////////////////
  if (theme_get_setting('aurora_viewport_width') || theme_get_setting('aurora_modernizr_debug')) {

    $debug_output = '<div id="aurora-debug">';

    if (theme_get_setting('aurora_viewport_width')) {
      $debug_output .= '<div id="aurora-viewport-width"></div>';
    }
    if (theme_get_setting('aurora_modernizr_debug')) {
      $debug_output .= '<div id="aurora-modernizr-debug" class="open"></div>';
    }

    $debug_output .= '</div>';

    if (!empty($vars['page_bottom'])) {
      $vars['page_bottom'] .= $debug_output;
    }
    else {
      $vars['page_bottom'] = $debug_output;
    }
  }

  //////////////////////////////
  // HTML5 Base Theme Forwardport
  //
  // Backports the following changes made to Drupal 8:
  // - #1077566: Convert html.tpl.php to HTML5.
  //////////////////////////////
  // Flatten out html_attributes and body_attributes.
  $vars['html_attributes'] = drupal_attributes($vars['html_attributes_array']);
  $vars['rdf_attributes'] = drupal_attributes($vars['rdf_attributes_array']);
  $vars['body_attributes'] = drupal_attributes($vars['body_attributes_array']);
}
/**
 * Return a themed breadcrumb trail.
 *
 * @param $vars
 *   - title: An optional string to be used as a navigational heading to give
 *     context for breadcrumb links to screen-reader users.
 *   - title_attributes_array: Array of HTML attributes for the title. It is
 *     flattened into a string within the theme function.
 *   - breadcrumb: An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 *
 * Lifted from Zen, because John is the man.
 */
function aurora_breadcrumb(&$vars) {
  return theme_breadcrumb($vars);
}

/**
  * Implements hook_process_html_tag
  *
  * - From http://sonspring.com/journal/html5-in-drupal-7#_pruning
  */
function aurora_process_html_tag(&$vars) {
  if (theme_get_setting('aurora_html_tags')) {
    $el = &$vars['element'];

    // Remove type="..." and CDATA prefix/suffix.
    unset($el['#attributes']['type'], $el['#value_prefix'], $el['#value_suffix']);

    // Remove media="all" but leave others unaffected.
    if (isset($el['#attributes']['media']) && $el['#attributes']['media'] === 'all') {
      unset($el['#attributes']['media']);
    }
  }
}

//////////////////////////////
// HTML5 Base Theme Forwardport
//////////////////////////////
/**
 * Implements the hook_preprocess_comment().
 *
 * Backports the following variable changes to Drupal 8:
 * - #1189816: Convert comment.tpl.php to HTML5.
 */
function aurora_preprocess_comment(&$variables) {
  $variables['user_picture'] = theme_get_setting('toggle_comment_user_picture') ? theme('user_picture', array('account' => $variables['comment'])) : '';
}

/**
 * Implements hook_preprocess_user_profile_category().
 *
 * Backports the following changes to made Drupal 8:
 * - #1190218: Convert user-profile-category.tpl.php to HTML5.
 */
function aurora_preprocess_user_profile_category(&$variables) {
  $variables['classes_array'][] = 'user-profile-category-' . drupal_html_class($variables['title']);
}

/**
 * Implements hook_css_alter().
 *
 * Backports the following CSS changes made to Drupal 8:
 * - #1216950: Clean up the CSS for Block module.
 * - #1216948: Clean up the CSS for Aggregator module.
 * - #1216972: Clean up the CSS for Color module.
 *
 */
function aurora_css_alter(&$css) {
  // Path to the theme's CSS directory.
  $dir = drupal_get_path('theme', 'aurora') . '/css';

  // Swap out aggregator.css with the aggregator.theme.css provided by this
  // theme.
  $aggregator = drupal_get_path('module', 'aggregator');
  if (isset($css[$aggregator . '/aggregator.css'])) {
    $css[$aggregator . '/aggregator.css']['data'] = $dir . '/aggregator/aggregator.theme.css';
  }
  if (isset($css[$aggregator . '/aggregator-rtl.css'])) {
    $css[$aggregator . '/aggregator-rtl.css']['data'] = $dir . '/aggregator/aggregator.theme-rtl.css';
  }

  // Swap out block.css with the block.admin.css provided by this theme.
  $block = drupal_get_path('module', 'block');
  if (isset($css[$block . '/block.css'])) {
    $css[$block . '/block.css']['data'] = $dir . '/block/block.admin.css';
  }

  // Swap out color.css with the color.admin.css provided by this theme.
  $color = drupal_get_path('module', 'color');
  if (isset($css[$color . '/color.css'])) {
    $css[$color . '/color.css']['data'] = $dir . '/color/color.admin.css';
  }
  if (isset($css[$color . '/color-rtl.css'])) {
    $css[$color . '/color-rtl.css']['data'] = $dir . '/color/color.admin-rtl.css';
  }

}

/**
 * Implements hook_preprocess_node().
 *
 * Backports the following changes made to Drupal 8:
 * - #1077602: Convert node.tpl.php to HTML5.
 */
function aurora_preprocess_node(&$variables) {
  // Add article ARIA role.
  $variables['attributes_array']['role'] = 'article';
}

function aurora_preprocess_panels_pane(&$vars) {
  $subtype = $vars['pane']->subtype;
  $layout = $vars['display']->layout;
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $layout;
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $subtype;
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $layout . '__' . $subtype;
}

function aurora_panels_default_style_render_region($vars) {
  $output = '';
  $output .= implode("\n", $vars['panes']);
  return $output;
}


//////////////////////////////
// Blockify Theme Overrides
//////////////////////////////

// /**
//   * Implements theme_blockify_logo
//   */
// function aurora_blockify_logo(&$vars) {
//   return '';
// }

function aurora_preprocess_block(&$vars) {
  // Logo Block
  if ($vars['block']->delta == 'blockify-logo') {
    $vars['theme_hook_suggestions'][] = 'block__logo';

    $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

    // Strip the base_path from the beginning of the logo path.
    $path = preg_replace('|^' . base_path() . '|', '', theme_get_setting('logo'));

    $image = array(
      '#theme' => 'image',
      '#path' => $path,
      '#alt' => t('!site_name Logo', array(
        '!site_name' => $site_name,
      ))
    );

    $vars['logo'] = $image;
    $vars['sitename'] = $site_name;
  }
  // Site Name Block
  else if ($vars['block']->delta == 'blockify-site-name') {
    $vars['theme_hook_suggestions'][] = 'block__site_name';

    $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

    $vars['sitename'] = $site_name;
  }
  // Site Slogan Block
  else if ($vars['block']->delta == 'blockify-site-slogan') {
    $vars['theme_hook_suggestions'][] = 'block__site_slogan';

    $slogan = filter_xss_admin(variable_get('site_slogan', 'Drupal'));

    $vars['slogan'] = $slogan;
  }
  // Page Title
  else if ($vars['block']->delta == 'blockify-page-title') {
    $vars['theme_hook_suggestions'][] = 'block__page_title';

    $vars['title'] = drupal_get_title();
  }
  else if ($vars['block']->delta == 'blockify-messages') {
    $vars['theme_hook_suggestions'][] = 'block__messages';
  }
  // Breadcrumbs
  else if ($vars['block']->delta == 'blockify-breadcrumb') {
    $vars['theme_hook_suggestions'][] = 'block__breadcrumbs';

    $breadcrumbs = drupal_get_breadcrumb();

    $vars['breadcrumbs'] = theme('breadcrumb', array('breadcrumb' => $breadcrumbs));
  }
  // Tabs
  else if ($vars['block']->delta == 'blockify-tabs') {
    $vars['theme_hook_suggestions'][] = 'block__tabs';

    $primary = menu_primary_local_tasks();
    $secondary = menu_secondary_local_tasks();

    $tabs = array(
      'primary' => $primary,
      'secondary' => $secondary,
    );

    $tabs = theme('menu_local_tasks', $tabs);

    $vars['tabs'] = $tabs;
  }
  // Actions
  else if ($vars['block']->delta == 'blockify-actions') {
    $vars['theme_hook_suggestions'][] = 'block__actions';

    $actions = menu_local_actions();
    $vars['actions'] = $actions;
  }
  // Feed Icons
  else if ($vars['block']->delta == 'blockify-feed-icons') {
    $vars['theme_hook_suggestions'][] = 'block__feed_icons';

    $icons = drupal_get_feeds();
    $vars['icons'] = $icons;
  }
}
