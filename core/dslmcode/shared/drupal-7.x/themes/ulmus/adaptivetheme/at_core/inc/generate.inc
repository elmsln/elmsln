<?php

/**
 * @file
 * Generate or get classes, mainly classes used on the body element and called
 * via themename_preprocess_html().
 */

/**
 * Return an array of classes to be used for body classes in html.tpl.php
 *
 * @param $vars, passed in the adaptivetheme_preprocess_html()
 * @param $theme_name, the active theme.
 */
function at_generate_html_classes(&$vars, $theme_name) {
  $classes_array = &drupal_static(__FUNCTION__, array());
  if (empty($classes_array)) {

    // Add a body class if the site name is hidden - state driven dynamic
    // classes are very useful and AT does this a lot
    if (at_get_setting('toggle_name', $theme_name) === 0) {
      $classes_array[] = 'site-name-hidden';
    }

    // Add debugging classes
    if (at_get_setting('expose_regions', $theme_name) === 1 || at_get_setting('load_all_panels', $theme_name) === 1) {
       $classes_array[] = 'debug-regions';
    }
    if (at_get_setting('load_all_panels', $theme_name) === 1 && drupal_is_front_page()) {
       $classes_array[] = 'debug-panels';
    }

    // Base theme classes, I use these to aid in debugging clients themes, you
    // could use them to hook a specific minor version. Note that version is
    // only included in Drupal.org archives, its missing when you clone GIT.
    $info = at_get_info('adaptivetheme');
    if (isset($info['release'])) {
      $classes_array[] = 'atr-' . $info['release'];
    }
    if (isset($info['version'])) {
      $classes_array[] = 'atv-' . $info['version'];
    }

    // Extra Classes
    if (at_get_setting('extra_page_classes', $theme_name) === 1) {

      // Set a class based on the language
      if (function_exists('locale')) {
        $classes_array[] = 'lang-' . $vars['language']->language;
      }

      // Site name class, for multi site installs that need to target styles
      // at each site seperately (mitigates things like block-id clashes)
      if (!empty($vars['head_title_array']['name'])) {
        $head_title = check_plain($vars['head_title_array']['name']);
        $classes_array[] = 'site-name-' . drupal_html_class($head_title);
      }

      // Classes for theming based on section
      if (!$vars['is_front']) {
        $path = drupal_get_path_alias(check_plain($_GET['q']));
        list($section, ) = explode('/', $path, 2);
        $classes_array[] = drupal_html_class('section-' . $section);
      }
    }

    // Set classes for views and panels pages
    $vars['menu_item'] = menu_get_item();
    switch ($vars['menu_item']['page_callback']) {
      case 'views_page':
        // Is this a Views page?
        $classes_array[] = 'page-views';
        break;
      case 'page_manager_page_execute':
      case 'page_manager_node_view':
      case 'page_manager_contact_site':
        // Is this a Panels page?
        $classes_array[] = 'page-panels';
        break;
    }
  }

  return $classes_array;
}

/**
 * Return an array of classes to be used for page classes in page.tpl.php
 *
 * @param $vars, passed in the adaptivetheme_preprocess_page()
 * @param $theme_name, the active theme.
 */
function at_generate_page_classes(&$vars, $theme_name) {
  $classes_array = &drupal_static(__FUNCTION__, array());
  if (empty($classes_array)) {

    // Site name classes
    if (isset($vars['hide_site_name']) && $vars['hide_site_name'] === FALSE) {
      if (at_get_setting('enable_heading_settings', $theme_name) === 1) {
        $site_name_settings_array = array(
          'site_name_case',
          'site_name_weight',
          'site_name_alignment',
          'site_name_shadow',
        );
        foreach ($site_name_settings_array as $site_name_setting) {
          if ($site_name_setting = at_get_setting($site_name_setting, $theme_name)) {
            $classes_array[] = $site_name_setting;
          }
        }
      }
    }

    // Slogan classes
    if (isset($vars['site_slogan'])) {
      if (at_get_setting('enable_heading_settings', $theme_name) === 1) {
        $site_slogan_settings_array= array(
          'site_slogan_case',
          'site_slogan_weight',
          'site_slogan_alignment',
          'site_slogan_shadow',
        );
        foreach ($site_slogan_settings_array as $site_slogan_setting) {
          if ($site_slogan_setting = at_get_setting($site_slogan_setting, $theme_name)) {
            $classes_array[] = $site_slogan_setting;
          }
        }
      }
    }

    // Block title classes
    if (at_get_setting('enable_heading_settings', $theme_name) === 1) {
      $block_title_settings_array = array(
        'block_title_case',
        'block_title_weight',
        'block_title_alignment',
        'block_title_shadow',
      );
      foreach ($block_title_settings_array as $setting) {
        if ($block_title_setting = at_get_setting($setting, $theme_name)) {
          $classes_array[] = $block_title_setting;
        }
      }
    }

    // Node title classes
    if (at_get_setting('enable_heading_settings', $theme_name) === 1) {
      $node_title_settings_array = array(
        'node_title_case',
        'node_title_weight',
        'node_title_alignment',
        'node_title_shadow',
      );
      foreach ($node_title_settings_array as $setting) {
        if ($node_title_setting = at_get_setting($setting, $theme_name)) {
          $classes_array[] = $node_title_setting;
        }
      }
    }

    // Comment title classes
    if (at_get_setting('comments_hide_title', $theme_name) !== 1) {
      if (at_get_setting('enable_heading_settings', $theme_name) === 1) {
        $comment_title_settings_array = array(
          'comment_title_case',
          'comment_title_weight',
          'comment_title_alignment',
          'comment_title_shadow',
        );
        foreach ($comment_title_settings_array as $setting) {
          if ($comment_title_setting = at_get_setting($setting, $theme_name)) {
            $classes_array[] = $comment_title_setting;
          }
        }
      }
    }

    // Page title classes
    if (at_get_setting('enable_heading_settings', $theme_name) === 1) {
      $page_title_settings_array = array(
        'page_title_case',
        'page_title_weight',
        'page_title_alignment',
        'page_title_shadow',
      );
      foreach ($page_title_settings_array as $setting) {
        if ($page_title_setting = at_get_setting($setting, $theme_name)) {
          $classes_array[] = $page_title_setting;
        }
      }
    }

    // Page class for at menu toggle
    if (at_get_setting('enable_menu_toggle', $theme_name) === 1) {
      $classes_array[] = 'at-mt';
    }
  }

  return $classes_array;
}

/**
 * Add classes for platforms and browsers.
 * This is very simple and can never replace something like WURFL or Mobile
 * Smart, in the future I intend to build a module to replace this.
 * Note - this is too dangerous to namespace since legacy themes use it.
 *
 * @param null $ua
 */
function css_browser_selector($ua = NULL) {
  if ($ua == NULL && !isset($_SERVER['HTTP_USER_AGENT'])) {
    return;
  }
  $ua = ($ua) ? strtolower($ua) : strtolower($_SERVER['HTTP_USER_AGENT']);

  $g = 'gecko';
  $w = 'webkit';
  $s = 'safari';
  $o = 'opera';

  $b = array();
  if (!preg_match('/opera|webtv/i', $ua) && preg_match('/msie\s(\d)/', $ua, $array)) {
    $b[] = 'ie ie' . $array[1];
  }
  elseif (strstr($ua, 'firefox')) {
    $b[] = $g . ' firefox';
  }
  elseif (strstr($ua, 'gecko/')) {
    $b[] = $g;
  }
  elseif (preg_match('/opera(\s|\/)(\d+)/', $ua, $array)) {
    $b[] = $o;
  }
  elseif (strstr($ua, 'konqueror')) {
    $b[] = 'konqueror';
  }
  elseif (strstr($ua, 'chrome')) {
    $b[] = $w . ' chrome';
  }
  elseif (strstr($ua, 'applewebkit/')) {
    $b[] = (preg_match('/version\/(\d+)/i', $ua, $array)) ? $w . ' ' . $s . ' ' . $s . $array[1] : $w . ' ' . $s;
  }
  elseif (strstr($ua, 'mozilla/')) {
    $b[] = $g;
  }
  if (strstr($ua, 'j2me')) {
    $b[] = 'mobile';
  }
  elseif (strstr($ua, 'iphone')) {
    $b[] = 'iphone';
  }
  elseif (strstr($ua, 'ipod')) {
    $b[] = 'ipod';
  }
  elseif (strstr($ua, 'ipad')) {
    $b[] = 'ipad';
  }
  elseif (strstr($ua, 'android')) {
    $b[] = 'android';
  }
  elseif (strstr($ua, 'googletv')) {
    $b[] = 'googletv';
  }
  elseif (strstr($ua, 'xoom')) {
    $b[] = 'xoom';
  }
  elseif (strstr($ua, 'nuvifone')) {
    $b[] = 'nuvifone';
  }
  elseif (strstr($ua, 'symbian')) {
    $b[] = 'symbian';
  }
  elseif (strstr($ua, 'blackberry')) {
    $b[] = 'blackberry';
  }
  elseif (strstr($ua, 'windows phone os 7')) {
    $b[] = 'windows-phone-7';
  }
  elseif (strstr($ua, 'windows ce')) {
    $b[] = 'windows-ce';
  }
  elseif (strstr($ua, 'iemobile')) {
    $b[] = 'iemobile';
  }
  elseif (strstr($ua, 'palm')) {
    $b[] = 'palm';
  }
  elseif (strstr($ua, 'webos')) {
    $b[] = 'webos';
  }
  elseif (strstr($ua, 'kindle')) {
    $b[] = 'kindle';
  }
  elseif (strstr($ua, 'mac')) {
    $b[] = 'mac';
  }
  elseif (strstr($ua, 'darwin')) {
    $b[] = 'mac';
  }
  elseif (strstr($ua, 'webtv')) {
    $b[] = 'webtv';
  }
  elseif (strstr($ua, 'win')) {
    $b[] = 'win';
  }
  elseif (strstr($ua, 'freebsd')) {
    $b[] = 'freebsd';
  }
  elseif (strstr($ua, 'x11') || strstr($ua, 'linux')) {
    $b[] = 'linux';
  }
  return join(' ', $b);
}

/**
 * Returns the active color scheme.
 *
 * Process the color info and return the active color scheme. We use this to
 * load a body class for the active color scheme, very useful for CSS tweaks
 * required for a particular scheme. This is not enabled by default, you have to
 * call it in template_preprocess_html(). Mostly ripped from Color module.
 * Note - this is too dangerous to namespace since legacy themes use it.
 *
 * @param $theme_name
 */
function get_color_scheme_name($theme_name) {
  $scheme_name = &drupal_static(__FUNCTION__, array());
  if (empty($scheme_name)) {
    if (module_exists('color')) {

      $info = color_get_info($theme_name);
      $info['schemes'][''] = array('title' => t('Custom'), 'colors' => array());
      $schemes = array();

      foreach ($info['schemes'] as $key => $scheme) {
        $schemes[$key] = $scheme['colors'];
      }

      $current_scheme = variable_get('color_' . $theme_name . '_palette', array());

      foreach ($schemes as $key => $scheme) {
        if ($current_scheme == $scheme) {
          $scheme_name = $key;
          break;
        }
      }
      if (empty($scheme_name)) {
        if (empty($current_scheme)) {
          $scheme_name = 'default';
        }
        else {
          $scheme_name = 'custom';
        }
      }
    }
  }

  return $scheme_name;
}

/**
 * Generate default classes for Panels layouts
 * Done because for some unknown reason setting these
 * in template_preprocess does not work, aka the variable
 * does not appear in the panel layout preprocess function.
 */
function at_panels_classes_array() {
  $output = array(
    'at-panel',
    'panel-display',
    'clearfix',
  );

  return $output;
}
