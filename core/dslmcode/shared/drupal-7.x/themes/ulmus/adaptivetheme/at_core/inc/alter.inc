<?php

/**
 * @file
 * General alters.
 */

/**
 * hook_html_head_alter()
 */
function adaptivetheme_html_head_alter(&$head_elements) {
  global $theme_key;
  $theme_name = $theme_key;

  // charset utf-8
  $head_elements['system_meta_content_type']['#attributes'] = array('charset' => 'utf-8');

  // IE Document Mode
  if ($adaptivetheme_meta_ie_document_mode = at_get_setting('adaptivetheme_meta_ie_document_mode', $theme_name)) {
    $head_elements['adaptivetheme_meta_ie_document_mode'] = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => "X-UA-Compatible",
        'content' => $adaptivetheme_meta_ie_document_mode,
      ),
      '#weight' => -999, // 1 less than the charset
    );
  }

  // cleartype
  if (at_get_setting('adaptivetheme_meta_clear_type', $theme_name) === 1) {
    $head_elements['adaptivetheme_meta_clear_type'] = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => "cleartype",
        'content' => "on",
      ),
      '#weight' => -998,
    );
  }

  // Don't add these if responsive styles are disabled
  if (at_get_setting('disable_responsive_styles', $theme_name) === 0) {

    // Viewport
    if ($adaptivetheme_meta_viewport = at_get_setting('adaptivetheme_meta_viewport', $theme_name)) {
      $head_elements['adaptivetheme_meta_viewport'] = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'viewport',
          'content' => check_plain($adaptivetheme_meta_viewport),
        ),
        '#weight' => 1,
      );
    }

    // MobileOptimized
    if ($adaptivetheme_meta_mobileoptimized = at_get_setting('adaptivetheme_meta_mobileoptimized', $theme_name)) {
      $head_elements['adaptivetheme_meta_mobileoptimized'] = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => "MobileOptimized",
          'content' => check_plain($adaptivetheme_meta_mobileoptimized),
        ),
        '#weight' => 2,
      );
    }

    // HandheldFriendly
    if ($adaptivetheme_meta_handheldfriendly = at_get_setting('adaptivetheme_meta_handheldfriendly', $theme_name)) {
      $head_elements['adaptivetheme_meta_handheldfriendly'] = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => "HandheldFriendly",
          'content' => check_plain($adaptivetheme_meta_handheldfriendly),
        ),
        '#weight' => 3,
      );
    }

    // apple-mobile-web-app-capable
    if ($adaptivetheme_meta_apple_mobile_web_app_capable = at_get_setting('adaptivetheme_meta_apple_mobile_web_app_capable', $theme_name)) {
      $head_elements['adaptivetheme_meta_apple_mobile_web_app_capable'] = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => "apple-mobile-web-app-capable",
          'content' => check_plain($adaptivetheme_meta_apple_mobile_web_app_capable),
        ),
        '#weight' => 4,
      );
    }
  }

  // Apple touch icons - low, medium and high (see the Apple docs on touch icons)
  if (at_get_setting('enable_apple_touch_icons') === 1) {
    $path_to_theme = drupal_get_path('theme', $theme_name);

    $rel = 'apple-touch-icon';
    if (at_get_setting('enable_apple_touch_icon_precomposed') === 1) {
      $rel = 'apple-touch-icon-precomposed';
    }

    // Apple default icon and Nokia shortcut icon.
    $icon_path_default = check_plain(at_get_setting('icon_path_default', $theme_name));
    if (!empty($icon_path_default)) {
      $default_icon_path = $path_to_theme . '/' . $icon_path_default;
      $default_icon_url = file_create_url($default_icon_path);
      $head_elements['adaptivetheme_touch_icon_nokia'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -97,
        '#attributes' => array(
          'href' => $default_icon_url,
          'rel' => "shortcut icon",
        ),
      );
      $head_elements['adaptivetheme_touch_icon_default'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -98,
        '#attributes' => array(
          'href' => $default_icon_url,
          'rel' => $rel,
        ),
      );
    }
    // iPad (standard display).
    $apple_touch_icon_path_ipad = check_plain(at_get_setting('apple_touch_icon_path_ipad', $theme_name));
    if (!empty($apple_touch_icon_path_ipad)) {
      $ipad_icon_path = $path_to_theme . '/' . $apple_touch_icon_path_ipad;
      $ipad_icon_url = file_create_url($ipad_icon_path);
      $head_elements['adaptivetheme_touch_icon_ipad'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -99,
        '#attributes' => array(
          'href' => $ipad_icon_url,
          'rel' => $rel,
          'sizes' => "76x76",
        ),
      );
    }
    // iPhone retina.
    $apple_touch_icon_path_iphone_retina = check_plain(at_get_setting('apple_touch_icon_path_iphone_retina', $theme_name));
    if (!empty($apple_touch_icon_path_iphone_retina)) {
      $iphone_retina_icon_path = $path_to_theme . '/' . $apple_touch_icon_path_iphone_retina;
      $iphone_retina_icon_url = file_create_url($iphone_retina_icon_path);
      $head_elements['adaptivetheme_touch_icon_iphone_retina'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -100,
        '#attributes' => array(
          'href' => $iphone_retina_icon_url,
          'rel' => $rel,
          'sizes' => "120x120",
        ),
      );
    }
    // iPad retina.
    $apple_touch_icon_path_ipad_retina = check_plain(at_get_setting('apple_touch_icon_path_ipad_retina', $theme_name));
    if (!empty($apple_touch_icon_path_ipad_retina)) {
      $ipad_retina_icon_path = $path_to_theme . '/' . $apple_touch_icon_path_ipad_retina;
      $ipad_retina_icon_url = file_create_url($ipad_retina_icon_path);
      $head_elements['adaptivetheme_touch_icon_ipad_retina'] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#weight' => -100,
        '#attributes' => array(
          'href' => $ipad_retina_icon_url,
          'rel' => $rel,
          'sizes' => "152x152",
        ),
      );
    }
  }
}

/**
 * hook_js_alter()
 */
function adaptivetheme_js_alter(&$javascript) {
  global $theme_key;

  // Use our own vesion of vertical-tabs.js for better error handling
  // @see http://drupal.org/node/607752
  if (isset($javascript['misc/vertical-tabs.js'])) {
    $file = drupal_get_path('theme', 'adaptivetheme') . '/scripts/vertical-tabs.js';
    $javascript['misc/vertical-tabs.js'] = drupal_js_defaults($file);
  }

  // Combine JS files into one per type, this is a bit mad and
  // we probably shouldn't encourage such things :)
  if (at_get_setting('combine_js_files', $theme_key) === 1) {
    uasort($javascript, 'drupal_sort_css_js');
    $weight = 0;
    foreach ($javascript as $name => $script) {
      $javascript[$name]['group'] = -100;
      $javascript[$name]['weight'] = ++$weight;
      $javascript[$name]['every_page'] = 1;
    }
  }
}

/**
 * hook_css_alter()
 */
function adaptivetheme_css_alter(&$css) {
  global $theme_key;

  // Never allow this to run in our admin theme and only if the extension is enabled.
  if (at_get_setting('enable_exclude_css') === 1 && $theme_key !== 'adaptivetheme_admin') {

    // Get $css_data from the cache
    if ($cache = cache_get('at_get_css_files')) {
      $css_data = $cache->data;
    }
    else {
      $css_data = at_get_css_files($theme_key);
    }

    // We need the right theme name to get the theme settings
    $_get_active_theme_data = array_pop($css_data);
    if ($_get_active_theme_data['type'] == 'theme') {
      $theme_name = $_get_active_theme_data['source'];
    }
    else {
      $theme_name = $theme_key;
    }

    // Get the theme setting and unset files
    foreach ($css_data as $key => $value) {
      $setting = 'unset_css_' . preg_replace('/[^a-zA-Z0-9-]+/', '_', $key);
      if (at_get_setting($setting, $theme_name) === 1) {
        if (isset($css[$key])) {
          unset($css[$key]);
        }
      }
    }

    // Unset -rtl.css files if language dir is RTL, in some contexts dir is
    // unset, but I don't know if this is a core bug or not.
    if (isset($language->dir) && $language->dir === 'rtl') {
      foreach ($css_data as $key => $value) {
        $setting = 'unset_css_' . preg_replace('/[^a-zA-Z0-9-]+/', '_', $key);
        if (at_get_setting($setting, $theme_name) === 1) {
          $key = str_replace('.css', '-rtl.css', $key);
          if (isset($css[$key])) {
            unset($css[$key]);
          }
        }
      }
    }
  }

  // Combine CSS files into one per type, this is not perfect
  if (at_get_setting('combine_css_files', $theme_key) === 1) {
    uasort($css, 'drupal_sort_css_js');
    $print = array();
    $weight = 0;
    foreach ($css as $name => $style) {
      // Leave  the conditional stylesheets untouched
      if ($css[$name]['browsers']['!IE']) {
        $css[$name]['group'] = 0;
        $css[$name]['weight'] = $weight++;
        $css[$name]['every_page'] = TRUE;
      }
      if ($css[$name]['media'] == 'print') {
        $print[$name] = $css[$name];
        unset($css[$name]);
      }
    }
    $css = array_merge($css, $print);
  }
}

/**
 * hook_page_alter()
 */
function adaptivetheme_page_alter(&$page) {
  global $theme_key;
  $theme_name = $theme_key;

  // Get the menu item
  $menu_item = menu_get_item();

  // Theme taxonomy term pages sensibly, remove redundant and potentially empty
  // markup and wrap the node list in section elements with a class for theming.
  if ($menu_item['tab_root'] == 'taxonomy/term/%') {
    unset($page['content']['system_main']['term_heading']['#prefix']);
    unset($page['content']['system_main']['term_heading']['#suffix']);
    $page['content']['system_main']['nodes']['#prefix'] = '<section class="nodes">';
    $page['content']['system_main']['nodes']['#suffix'] = '</section>';
  }

  if (at_get_setting('enable_extensions', $theme_name) === 1) {
    if (at_get_setting('enable_markup_overides', $theme_name) === 1) {
      // Remove block system main, just from the front page
      if (drupal_is_front_page()) {
        if (at_get_setting('unset_block_system_main_front', $theme_name) === 1) {
          $page['content']['system_main']['#access'] = FALSE; // Brutal but effective
        }
      }
    }
  }

  // Get all the regions with blocks
  $block_regions = &drupal_static(__FUNCTION__, array());

  if (empty($blocks_regions)) {
    $block_regions = system_region_list($GLOBALS['theme'], REGIONS_VISIBLE);
  }

  // Setup the detection environment
  $detection = variable_get('at_detection', 0);
  if ($detection == 1) {
    $browscap_detect = variable_get('at_browscap_detect', 0);
    $mobile_detect = variable_get('at_mobile_detect', 0);
    $browser = at_get_browser();
    $page['is_mobile'] = $browser['is_mobile'];
    $page['is_tablet'] = $browser['is_tablet'];
  }
  else {
    $page['is_mobile'] = FALSE;
    $page['is_tablet'] = FALSE;
  }

  // Look in each visible region for blocks
  foreach ($block_regions as $region => $name) {
    if (!empty($page[$region])) {

      // Find the last block in the region
      $blocks = array_reverse(element_children($page[$region]));
      while ($blocks && !isset($page[$region][$blocks[0]]['#block'])) {
        array_shift($blocks);
      }

      if ($blocks) {

        // Set a bool for the last class for blocks feature
        $page[$region][$blocks[0]]['#block']->last_in_region = TRUE;

        // Alter regions and block visibility. Note that ideally this would all
        // be better in hook_page_build(), however themes can't fire that hook.
        if (at_get_setting('enable_extensions', $theme_name) === 1) {
          if (at_get_setting('enable_context_regions') === 1) {

            // UNSET
            if (at_get_setting('unset_' . $region) === 1) {
              if (at_get_setting('unset_options_' . $region) == 'unset_smalltouch') {
                if ($page['is_mobile'] === TRUE && $page['is_tablet'] === FALSE) {
                  unset($page[$region]);
                }
              }
              else {
                // this is the all option
                if ($page['is_mobile'] === TRUE) {
                  unset($page[$region]);
                }
              }
            }

            // MOVE
            if (at_get_setting('move_region_' . $region) === 1) {
              if (at_get_setting('move_options_' . $region) == 'move_smalltouch') {
                if ($page['is_mobile'] === TRUE && $page['is_tablet'] === FALSE) {
                  $page = at_move_regions($page, $region, $blocks);
                }
              }
              else {
                // this is the all option
                if ($page['is_mobile'] === TRUE) {
                  $page = at_move_regions($page, $region, $blocks);
                }
              }
            }
          }
        }
      }
    }
  }

  // Run the panels test
  if (theme_get_setting('load_all_panels') === 1) {
    if (drupal_is_front_page()) {
      $page['content']['#markup'] = at_debug_panels();
      if (theme_get_setting('load_all_panels_no_sidebars') === 1) {
        unset($page['sidebar_first']);
        unset($page['sidebar_second']);
      }
    }
  }

  //kpr($page);
}

// Abstrat move regions processing
function at_move_regions($page, $region, $blocks) {
  // Get the target region if set, check blocks can move and its not set to unset
  if (($target_region = at_get_setting('move_' . $region)) && ($target_region !== 'do_not_move') && (at_get_setting('unset_' . $region) !== 1)) {

    // Sanitize possible vector
    $target_region = check_plain($target_region);

    // Initialize the classes array
    $classes = array();

    // Move each block
    foreach ($blocks as $block) {

      // If the $target_region is empty the region markup does not print
      // so we need to generate it manually. This is bad because it
      // cannot account for region specific template suggestions and
      // Adaptivethemes own region prefix and suffix wrappers.
      if (empty($page[$target_region])) {
        $classes[] = 'region';
        $classes[] = 'region-' . str_replace('_', '-', $target_region);
        if ($target_region == 'sidebar_first' || $target_region == 'sidebar_second') {
          $classes[] = 'sidebar';
        }
        $classes = implode(' ', $classes);
        $page[$target_region]['#prefix'] = '<div class="' .  $classes . '"><div class="region-inner clearfix">';
        $page[$target_region]['#suffix'] = '</div></div>';
      }

      // Move the blocks to the target region
      $page[$target_region][$block] = $page[$region][$block];

      // Unset the original block
      unset($page[$region][$block]);
    }

    // Unset the region, all blocks are now moved
    unset($page[$region]);
  }

  return $page;
}

/**
 * hook_form_FORM_alter()
 */
function adaptivetheme_form_alter(&$form, &$form_state, $form_id) {
  // Collapse Noggin fieldset by default
  if ($form_id == 'system_theme_settings') {
    if (module_exists('noggin')) {
      $form['noggin']['#collapsible'] = TRUE;
      $form['noggin']['#collapsed'] = TRUE;
    }
  }
}

/**
 * hook_form_FORM_ID_alter()
 * Modify the Advanced Search Form
 */
function adaptivetheme_form_search_form_alter(&$form, $form_state) {
  // The problem with Drupals standard Advanced search form is that each
  // criterion group is wrapped in a DIV, whereas it should be a fieldset with
  // a legend, this is better semantics and improves accessibility by
  // logically grouping field items. We make this optional via a theme setting,
  // beacuse some people bitched that it broke some modules that require
  // crappy markup.
  if (at_get_setting('adv_search_extra_fieldsets') === 1) {
    if (isset($form['module']) && $form['module']['#value'] == 'node' && user_access('use advanced search')) {
      // Keyword boxes:
      $form['advanced'] = array(
        '#type' => 'fieldset',
        '#title' => t('Advanced search'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#attributes' => array('class' => array('search-advanced')),
      );
      $form['advanced']['keywords-fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Keywords'),
        '#collapsible' => FALSE,
      );
      $form['advanced']['keywords-fieldset']['keywords'] = array(
        '#prefix' => '<div class="criterion">',
        '#suffix' => '</div>',
      );
      $form['advanced']['keywords-fieldset']['keywords']['or'] = array(
        '#type' => 'textfield',
        '#title' => t('Containing any of the words'),
        '#size' => 30,
        '#maxlength' => 255,
      );
      $form['advanced']['keywords-fieldset']['keywords']['phrase'] = array(
        '#type' => 'textfield',
        '#title' => t('Containing the phrase'),
        '#size' => 30,
        '#maxlength' => 255,
      );
      $form['advanced']['keywords-fieldset']['keywords']['negative'] = array(
        '#type' => 'textfield',
        '#title' => t('Containing none of the words'),
        '#size' => 30,
        '#maxlength' => 255,
      );
      // Node types:
      $types = array_map('check_plain', node_type_get_names());
      $form['advanced']['types-fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Types'),
        '#collapsible' => FALSE,
      );
      $form['advanced']['types-fieldset']['type'] = array(
        '#type' => 'checkboxes',
        '#prefix' => '<div class="criterion">',
        '#suffix' => '</div>',
        '#options' => $types,
      );
      $form['advanced']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Advanced search'),
        '#prefix' => '<div class="action advanced-search-submit">',
        '#suffix' => '</div>',
        '#weight' => 99,
      );
      // Languages:
      $language_options = array();
      foreach (language_list('language') as $key => $entity) {
        $language_options[$key] = $entity->name;
      }
      if (count($language_options) > 1) {
        $form['advanced']['lang-fieldset'] = array(
          '#type' => 'fieldset',
          '#title' => t('Languages'),
          '#collapsible' => FALSE,
          '#collapsed' => FALSE,
        );
        $form['advanced']['lang-fieldset']['language'] = array(
          '#type' => 'checkboxes',
          '#prefix' => '<div class="criterion">',
          '#suffix' => '</div>',
          '#options' => $language_options,
        );
      }
      $form['#validate'][] = 'node_search_validate';
    }
  }
}

/**
 * hook_form_FORM_ID_alter()
 * Modify the User Login Block Form
 */
function adaptivetheme_form_user_login_block_alter(&$form, &$form_state, $form_id) {
  global $theme_key;
  $theme_name = $theme_key;
  if (at_get_setting('enable_extensions', $theme_name) === 1) {
    if (at_get_setting('enable_markup_overides', $theme_name) === 1) {
      if (at_get_setting('login_block_remove_links', $theme_name) === 1) {
        // Remove the links
        if (isset($form['links'])) {
          unset($form['links']);
        }
      }
      if (at_get_setting('login_block_remove_openid', $theme_name) === 1) {
        if (module_exists('openid')) {
          // Remove OpenID elements
          unset($form['openid_links']);
          unset($form['openid_identifier']);
          unset($form['openid.return_to']);
        }
      }
      if (at_get_setting('horizontal_login_block', $theme_name) === 1) {
        // Move the links to the end of the form, so they are after the submit,
        // OpenID really messes up the weight and I can't be bothered fighting
        // Drupal to deal with it.
        if (isset($form['links'])) {
          $form['links']['#weight'] = 100;
        }
      }
    }
  }
}

/**
 * hook_form_BASE_FORM_ID_alter()
 * Modify field classes on node forms.
 */
function adaptivetheme_form_node_form_alter(&$form, &$form_state, $form_id) {
  // Remove if #1245218 is backported to D7 core.
  foreach (array_keys($form) as $item) {
    if (strpos($item, 'field_') === 0) {
      if (!empty($form[$item]['#attributes']['class'])) {
        foreach ($form[$item]['#attributes']['class'] as &$class) {
          if (strpos($class, 'field-type-') === 0 || strpos($class, 'field-name-') === 0) {
            // Make the class different from that used in theme_field().
            $class = $class . '-form';
          }
        }
      }
    }
  }
}

/**
 * Set a class on the iframe body element for WYSIWYG editors. This allows you
 * to easily override the background for the iframe body element.
 * This only works for the WYSIWYG module: http://drupal.org/project/wysiwyg
 */
function adaptivetheme_wysiwyg_editor_settings_alter(&$settings, &$context) {
  $settings['bodyClass'] = 'wysiwygeditor';
}

/**
 * Output for the debug panels test. This is pretty sucky because its
 * hard coded and therefor does not include any custom Panels layout
 * plugins you might include in a subtheme, bad eh?
 */
function at_debug_panels() {
  $output = <<<EOF
<div class="all-panel-layouts debug-panels">

    <h1>Panels/Gpanels Layout Test</h1>
    <p>To disable this test uncheck the theme setting <em>Debuggers > Load all panels in the front page content region</em></p>

    <div class="at-panel panel-display one-column clearfix">
      <div class="region region-one-main">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display two-50 clearfix">
      <div class="region region-two-50-top region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-50-first">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-50-second">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-50-bottom region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display two-33-66 clearfix">
      <div class="region region-two-33-66-top region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-33-66-first">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-33-66-second">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-33-66-bottom region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display two-66-33 clearfix">
      <div class="region region-two-66-33-top region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-66-33-first">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-66-33-second">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-two-66-33-bottom region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display two-brick clearfix">
      <div class="region region-two-brick-top region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="panel-row row-1 clearfix">
        <div class="region region-two-brick-left-above">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-two-brick-right-above">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
      <div class="region region-two-brick-middle region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="panel-row row-2 clearfix">
        <div class="region region-two-brick-left-below">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-two-brick-right-below">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
      <div class="region region-two-brick-bottom region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display three-3x33 clearfix">
      <div class="region region-three-33-top region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-33-first">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-33-second">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-33-third">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-33-bottom region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display three-25-50-25 clearfix">
      <div class="region region-three-25-50-25-top region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-25-50-25-first">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-25-50-25-second">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-25-50-25-third">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-25-50-25-bottom region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display three-25-25-50 clearfix">
      <div class="region region-three-25-25-50-top region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-25-25-50-first">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-25-25-50-second">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-25-25-50-third">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-25-25-50-bottom region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display three-50-25-25 clearfix">
      <div class="region region-three-50-25-25-top region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-50-25-25-first">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-50-25-25-second">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-50-25-25-third">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="region region-three-50-25-25-bottom region-conditional-stack">
        <div class="region-inner clearfix">
        </div>
      </div>
    </div>

    <div class="at-panel panel-display four-4x25 clearfix">
      <div class="panel-row row-1 clearfix">
        <div class="region region-four-first">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-four-second">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
      <div class="panel-row row-2 clearfix">
        <div class="region region-four-third">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-four-fourth">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
    </div>

    <div class="at-panel panel-display five-5x20 clearfix">
      <div class="panel-row row-1 clearfix">
        <div class="region region-five-first">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-five-second">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
      <div class="panel-row row-2 clearfix">
        <div class="region region-five-third">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-five-fourth">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-five-fifth">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
    </div>

    <div class="at-panel panel-display six-6x16 multicolumn clearfix">
      <div class="panel-row row-1 clearfix">
        <div class="region region-six-first">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-six-second">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
      <div class="panel-row row-2 clearfix">
        <div class="region region-six-third">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-six-fourth">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
      <div class="panel-row row-3 clearfix">
        <div class="region region-six-fifth">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-six-sixth">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
    </div>

    <div class="at-panel panel-panel three-inset-left clearfix">
      <div class="region region-three-inset-left-sidebar">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="inset-wrapper clearfix">
        <div class="region region-three-inset-left-top region-conditional-stack">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-three-inset-left-middle">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-three-inset-left-inset">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-three-inset-left-bottom region-conditional-stack">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
    </div>

    <div class="at-panel panel-panel three-inset-right clearfix">
      <div class="region region-three-inset-right-sidebar">
        <div class="region-inner clearfix">
        </div>
      </div>
      <div class="inset-wrapper clearfix">
        <div class="region region-three-inset-right-top region-conditional-stack">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-three-inset-right-middle">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-three-inset-right-inset">
          <div class="region-inner clearfix">
          </div>
        </div>
        <div class="region region-three-inset-right-bottom region-conditional-stack">
          <div class="region-inner clearfix">
          </div>
        </div>
      </div>
    </div>
</div>
EOF;

  return $output;
}
