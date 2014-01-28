<?php

/**
 * Implements theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function cis_theme_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $breadcrumbs = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $breadcrumbs .= '<ul class="breadcrumbs">';
    // courses view shows courses twice for some reason
    if (arg(0) == 'courses') {
      array_pop($breadcrumb);
    }
    foreach ($breadcrumb as $key => $value) {
      $breadcrumbs .= '<li>' . $value . '</li>';
    }

    //$title = strip_tags(drupal_get_title());
    // just menu item title instead of drupal title
    $item = menu_get_item();
    $title = $item['title'];
    $breadcrumbs .= '<li class="current"><a href="#">' . $title. '</a></li>';
    $breadcrumbs .= '</ul>';

    return $breadcrumbs;
  }
}

/**
 * Implements theme_links() targeting the main menu specifically
 * Outputs Foundation Nav bar http://foundation.zurb.com/docs/navigation.php
 * 
 */
//function cis_theme_links__system_main_menu($variables) {
//  // Get all the main menu links
//  $menu_links = menu_tree_output(menu_tree_all_data('main-menu'));
//  
//  // Initialize some variables to prevent errors
//  $output = '';
//  $sub_menu = '';
//
//  foreach ($menu_links as $key => $link) {
//    // Add special class needed for Foundation dropdown menu to work
//    !empty($link['#below']) ? $link['#attributes']['class'][] = 'has-flyout' : '';
//
//    // Render top level and make sure we have an actual link
//    if (!empty($link['#href'])) {
//      $output .= '<li' . drupal_attributes($link['#attributes']) . '>' . l($link['#title'], $link['#href']);
//      // Get sub navigation links if they exist
//      foreach ($link['#below'] as $key => $sub_link) {
//        if (!empty($sub_link['#href'])) {
//          $sub_menu .= '<li>' . l($sub_link['#title'], $sub_link['#href']) . '</li>';
//        }
//        
//      }
//      $output .= !empty($link['#below']) ? '<a href="#" class="flyout-toggle"><span> </span></a><ul class="flyout">' . $sub_menu . '</ul>' : '';
//      
//      // Reset dropdown to prevent duplicates
//      unset($sub_menu);
//      $sub_menu = '';
//      
//      $output .=  '</li>';
//    }
//  }
//  return '<ul class="nav-bar">' . $output . '</ul>';
//}

/**
 * Implements template_preprocess_html().
 * 
 */
//function cis_theme_preprocess_html(&$variables) {
//  // Add conditional CSS for IE. To use uncomment below and add IE css file
//  drupal_add_css(path_to_theme() . '/css/ie.css', array('weight' => CSS_THEME, 'browsers' => array('!IE' => FALSE), 'preprocess' => FALSE));
//  
//  // Need legacy support for IE downgrade to Foundation 2 or use JS file below
//  // drupal_add_js('http://ie7-js.googlecode.com/svn/version/2.1(beta4)/IE7.js', 'external'); 
//}

/**
 * Implements template_process_html().
 *
 * Override or insert variables into the page template for HTML output.
 */
function cis_theme_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

/*
 * Implements template_process_page().
 */
function cis_theme_process_page(&$variables, $hook) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

/**
 * Implements template_preprocess_page
 */
function cis_theme_preprocess_page(&$variables) {
  // special tpl for the pages/about page
  // this method avoids the need for declaring a nid
  if (request_path() == 'pages/about') {
    $variables['theme_hook_suggestions'][] = 'page__pages__about';
  }
  // walk tree looking for deeper items
  $menu = menu_tree_all_data(variable_get('menu_secondary_links_source', 'main-menu'));
  foreach ($menu as $key => $value) {
    if ($value['link']['href'] == arg(0)) {
      $active_menu = $value['below'];
      break;
    }
  }
  // only render if we have a 3rd level of nav
  if (isset($active_menu)) {
    $menu_links = menu_tree_output($active_menu);
    // Initialize some variables to prevent errors
    $output = '';
    $sub_menu = '';
    $small_link = '';
  
    foreach ($menu_links as $key => $link) {
      // Add special class needed for Foundation dropdown menu to work
      $small_link = $link; //duplicate version that won't get the dropdown class, save for later
      !empty($link['#below']) ? $link['#attributes']['class'][] = 'has-dropdown' : '';
  
      // Render top level and make sure we have an actual link
      if (!empty($link['#href'])) {
  
        $output .= '<li' . drupal_attributes($link['#attributes']) . '>' . l($link['#title'], $link['#href']);
        // Uncomment if we don't want to repeat the links under the dropdown for large-screen
        // $small_link['#attributes']['class'][] = 'show-for-small';
        $sub_menu = '<li' . drupal_attributes($small_link['#attributes']) . '>' . l($link['#title'], $link['#href']);
        // Get sub navigation links if they exist
        foreach ($link['#below'] as $key => $sub_link) {
          if (!empty($sub_link['#href'])) {
          $sub_menu .= '<li>' . l($sub_link['#title'], $sub_link['#href']) . '</li>';
          }
        }
        $output .= !empty($link['#below']) ? '<ul class="dropdown">' . $sub_menu . '</ul>' : '';
  
        // Reset dropdown to prevent duplicates
        unset($sub_menu);
        unset($small_link);
        $small_link = '';
        $sub_menu = '';
  
        $output .=  '</li>';
      }
    }
    // only output level 3 if we have a level 2
    if (isset($variables['secondary_menu'])) {
      $variables['third_menu_links'] = '<h3 class="element-invisible">Local level Menu</h3><ul id="third-menu" class="third link-list">' . $output . '</ul>';
    }
  }
}

/**
 * Implements template_preprocess_node
 *
 */
//function cis_theme_preprocess_node(&$variables) {
//}

/**
 * Implements hook_preprocess_block()
 */
//function cis_theme_preprocess_block(&$variables) {
//  // Add wrapping div with global class to all block content sections.
//  $variables['content_attributes_array']['class'][] = 'block-content';
//  
//  // Convenience variable for classes based on block ID
//  $block_id = $variables['block']->module . '-' . $variables['block']->delta;
//  
//  // Add classes based on a specific block
//  switch ($block_id) {
//    // System Navigation block
//    case 'system-navigation':
//      // Custom class for entire block
//      $variables['classes_array'][] = 'system-nav';
//      // Custom class for block title
//      $variables['title_attributes_array']['class'][] = 'system-nav-title';
//      // Wrapping div with custom class for block content
//      $variables['content_attributes_array']['class'] = 'system-nav-content';
//      break;
//    
//    // User Login block
//    case 'user-login':
//      // Hide title
//      $variables['title_attributes_array']['class'][] = 'element-invisible';
//      break;
//
//    // Example of adding Foundation classes
//    case 'block-foo': // Target the block ID
//      // Set grid column or mobile classes or anything else you want.
//      $variables['classes_array'][] = 'six columns';
//      break;
//  }
//
//  // Add template suggestions for blocks from specific modules.
//  switch($variables['elements']['#block']->module) {
//    case 'menu':
//      $variables['theme_hook_suggestions'][] = 'block__nav';
//    break;
//  }
//}

/**
 * Implements hook_preprocess_views_view().
 */
function cis_theme_preprocess_views_view(&$variables) {
  // target the faculty and course displays as they have specialized exposed filters
  if (in_array($variables['name'], array('courses_overview', 'cis_faculty'))) {
    // form elements weren't responding to array alters
    // this class hides the labels but will render for accessibility to screen-readers
    $variables['exposed'] = str_replace('<label for="edit-field-display-name-value"', '<label class="element-invisible" for="edit-field-display-name-value"', $variables['exposed']);
    $variables['exposed'] = str_replace('<label for="edit-title"', '<label class="element-invisible" for="edit-title"', $variables['exposed']);
    $variables['exposed'] = str_replace('<label for="">', '<label class="element-invisible" for="edit-title-1">', $variables['exposed']);
  }
}

/**
 * Implements template_preprocess_panels_pane().
 *
 */
//function cis_theme_preprocess_panels_pane(&$variables) {
//}

/**
 * Implements template_preprocess_views_views_fields().
 *
 */
//function cis_theme_preprocess_views_view_fields(&$variables) {
//}

/**
 * Status messages in reveal modal
 *
 */
//function cis_theme_status_messages($variables) {
//  $display = $variables['display'];
//  $output = ''; 
//
//  $status_heading = array(
//    'status' => t('Status message'), 
//    'error' => t('Error message'), 
//    'warning' => t('Warning message'),
//  );  
//  foreach (drupal_get_messages($display) as $type => $messages) {
//    $output .= "<div class=\"messages $type\">\n";
//    if (!empty($status_heading[$type])) {
//      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
//    }   
//    if (count($messages) > 1) {
//      $output .= " <ul>\n";
//      foreach ($messages as $message) {
//        $output .= '  <li>' . $message . "</li>\n";
//      }   
//      $output .= " </ul>\n";
//    }   
//    else {
//      $output .= $messages[0];
//    }   
//    $output .= "</div>\n";
//  }
//  if ($output != '') {
//    drupal_add_js("jQuery(document).ready(function() { jQuery('#status-messages').foundation('reveal','open');
//            });", array('type' => 'inline', 'scope' => 'footer'));
//    $output = '<div id="status-messages" class="reveal-modal" >'. $output;
//    $output .= '<a class="close-reveal-modal">&#215;</a>';
//    $output .= "</div>\n";
//    $output .= '<div class="reveal-modal-bg"></div>';
//  }
//  return $output;
//}

/**
 * Implements theme_form_element_label()
 * Use foundation tooltips
 */
//function cis_theme_form_element_label($variables) {
//  if (!empty($variables['element']['#title'])) {
//    $variables['element']['#title'] = '<span class="secondary label">' . $variables['element']['#title'] . '</span>';
//  }
//  if (!empty($variables['element']['#description'])) {
//    $variables['element']['#description'] = ' <span class="has-tip tip-top radius" data-width="250" title="' . $variables['element']['#description'] . '">' . t('More information?') . '</span>';
//  }
//  return theme_form_element_label($variables);
//}

/**
 * Implements hook_preprocess_button().
 */
//function cis_theme_preprocess_button(&$variables) {
//  $variables['element']['#attributes']['class'][] = 'button';
//  if (isset($variables['element']['#parents'][0]) && $variables['element']['#parents'][0] == 'submit') {
//    $variables['element']['#attributes']['class'][] = 'secondary';
//  }
//}

/**
 * Implements hook_form_alter()
 * Example of using foundation sexy buttons
 */
//function cis_theme_form_alter(&$form, &$form_state, $form_id) {
//  // Sexy submit buttons
//  if (!empty($form['actions']) && !empty($form['actions']['submit'])) {
//    $form['actions']['submit']['#attributes'] = array('class' => array('primary', 'button', 'radius'));
//  }
//}

// Sexy preview buttons
//function cis_theme_form_comment_form_alter(&$form, &$form_state) {
//  $form['actions']['preview']['#attributes']['class'][] = array('class' => array('secondary', 'button', 'radius'));
//}
