<?php

/**
 * Implements hook_html_head_alter().
 */
function ember_html_head_alter(&$head_elements) {
  $head_elements['viewport'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width,initial-scale=1,maximum-scale=1,user-scalable=0'),
  );
}

/*add a ember class to the header to give targetability for css enhancements */
function ember_preprocess_html(&$variables) {
 $variables['classes_array'][] = 'ember';
}

/**
 * Override or insert variables into the page template.
 */
function ember_process_page(&$vars) {
  if (theme_get_setting('display_breadcrumbs') == 1) {
    unset($vars['breadcrumb']);
  }
}

/**
 * Display the list of available node types for node creation.
 */
function ember_node_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<ul class="admin-list">';
    foreach ($content as $item) {
      $output .= '<li class="clearfix">';
      $output .= '<span class="label">' . l($item['title'], $item['href'], $item['localized_options']) . '</span>';
      $output .= '<div class="description">' . filter_xss_admin($item['description']) . '</div>';
      $output .= '</li>';
    }
    $output .= '</ul>';
  }
  else {
    $output = '<p>' . t('You have not created any content types yet. Go to the <a href="@create-content">content type creation page</a> to add a new content type.', array('@create-content' => url('admin/structure/types/add'))) . '</p>';
  }
  return $output;
}

/**
 * Overrides theme_admin_block_content().
 *
 * Use unordered list markup in both compact and extended mode.
 */
function ember_admin_block_content($variables) {
  $content = $variables['content'];
  $output = '';
  if (!empty($content)) {
    $output = system_admin_compact_mode() ? '<ul class="admin-list compact">' : '<ul class="admin-list">';
    foreach ($content as $item) {
      $output .= '<li class="leaf">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);
      if (isset($item['description']) && !system_admin_compact_mode()) {
        $output .= '<div class="description">' . filter_xss_admin($item['description']) . '</div>';
      }
      $output .= '</li>';
    }
    $output .= '</ul>';
  }
  return $output;
}

/**
 * Override of theme_tablesort_indicator().
 *
 * Use our own image versions, so they show up as black and not gray on gray.
 */
function ember_tablesort_indicator($variables) {
  $style = $variables['style'];
  $theme_path = drupal_get_path('theme', 'ember');
  if ($style == 'asc') {
    return theme('image', array('path' => $theme_path . '/images/arrow-asc.png', 'alt' => t('sort ascending'), 'width' => 13, 'height' => 13, 'title' => t('sort ascending')));
  }
  else {
    return theme('image', array('path' => $theme_path . '/images/arrow-desc.png', 'alt' => t('sort descending'), 'width' => 13, 'height' => 13, 'title' => t('sort descending')));
  }
}

/**
 * Implements hook_css_alter().
 */
function ember_css_alter(&$css) {
  // Use Ember's jQuery UI styles instead of the defaults.
  $jquery = array('core', 'dialog', 'tabs', 'theme');
  foreach($jquery as $module) {
    if (isset($css['misc/ui/jquery.ui.' . $module . '.css'])) {
      $css['misc/ui/jquery.ui.' . $module . '.css']['data'] = drupal_get_path('theme', 'ember') . '/styles/jquery.ui.' . $module . '.css';
    }
  }

  // If the media module is installed, Replace it with Ember's.
  if (module_exists('media')) {
    $media_path = drupal_get_path('module', 'media') . '/css/media.css';
    if(isset($css[$media_path])) {
      $css[$media_path]['data'] = drupal_get_path('theme', 'ember') . '/styles/media.css';
    }
  }

  // If the responsive vertical tabs module is installed, add ember themeing overrides to it
  if (module_exists('responsive_vertical_tabs')) {
    $rvt_theme_path = drupal_get_path('module', 'responsive_vertical_tabs') . '/css/vertical-tabs-theme.css';
    if(isset($css[$rvt_theme_path])) {
      $css[$rvt_theme_path]['data'] = drupal_get_path('theme', 'ember') . '/styles/vertical-tabs-theme.css';
    }
  }
}


/**
 * Overrides theme_links__ctools_dropbutton().
 *
 * This override adds a wrapper div so that we can maintain appropriate
 * vertical spacing.
 */
function ember_links__ctools_dropbutton($variables) {
  // Check to see if the number of links is greater than 1;
  // otherwise just treat this like a button.
  if (!empty($variables['links'])) {
    $is_drop_button = (count($variables['links']) > 1);

    // Add needed files
    if ($is_drop_button) {
      ctools_add_js('dropbutton');
      ctools_add_css('dropbutton');
    }
    ctools_add_css('button');

    // Provide a unique identifier for every button on the page.
    static $id = 0;
    $id++;

    // Wrapping div
    $class = 'ctools-no-js';
    $class .= ($is_drop_button) ? ' ctools-dropbutton' : '';
    $class .= ' ctools-button';
    if (!empty($variables['class'])) {
      $class .= ($variables['class']) ? (' ' . implode(' ', $variables['class'])) : '';
    }

    $output = '';

    $output .= '<div class="' . $class . '" id="ctools-button-' . $id . '">';

    // Add a twisty if this is a dropbutton
    if ($is_drop_button) {
      $variables['title'] = ($variables['title'] ? check_plain($variables['title']) : t('open'));

      $output .= '<div class="ctools-link">';
      if ($variables['image']) {
        $output .= '<a href="#" class="ctools-twisty ctools-image">' . $variables['title'] . '</a>';
      }
      else {
        $output .= '<a href="#" class="ctools-twisty ctools-text">' . $variables['title'] . '</a>';
      }
      $output .= '</div>'; // ctools-link
    }

    // The button content
    $output .= '<div class="ctools-content">';

    // Check for attributes. theme_links expects an array().
    $variables['attributes'] = (!empty($variables['attributes'])) ? $variables['attributes'] : array();

    // Remove the inline and links classes from links if they exist.
    // These classes are added and styled by Drupal core and mess up the default
    // styling of any link list.
    if (!empty($variables['attributes']['class'])) {
      $classes = $variables['attributes']['class'];
      foreach ($classes as $key => $class) {
        if ($class === 'inline' || $class === 'links') {
          unset($variables['attributes']['class'][$key]);
        }
      }
    }

    // Call theme_links to render the list of links.
    $output .= theme_links(array('links' => $variables['links'], 'attributes' => $variables['attributes'], 'heading' => ''));
    $output .= '</div>'; // ctools-content
    $output .= '</div>'; // ctools-dropbutton

    // Wrap the output in our container.
    $output = '<div class="ctools-dropbutton-wrapper">' . $output . '</div>';

    return $output;
  }
  else {
    return '';
  }
}
