<?php

/**
 * Implements template_preprocess_html().
 *
 */
//function foundation_access_preprocess_html(&$variables) {
//  // Add conditional CSS for IE. To use uncomment below and add IE css file
//  drupal_add_css(path_to_theme() . '/css/ie.css', array('weight' => CSS_THEME, 'browsers' => array('!IE' => FALSE), 'preprocess' => FALSE));
//
//  // Need legacy support for IE downgrade to Foundation 2 or use JS file below
//  // drupal_add_js('http://ie7-js.googlecode.com/svn/version/2.1(beta4)/IE7.js', 'external');
//}

/**
 * Implements template_preprocess_page
 *
 */
//function foundation_access_preprocess_page(&$variables) {
//}

/**
 * Implements template_preprocess_node
 *
 */
//function foundation_access_preprocess_node(&$variables) {
//}

/**
 * Implements hook_preprocess_block()
 */
//function foundation_access_preprocess_block(&$variables) {
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
// function foundation_access_preprocess_block(&$variables) {
//  // Add wrapping div with global class to all block content sections.
//  $variables['content_attributes_array']['class'][] = 'block-content';

//  // Convenience variable for classes based on block ID
//  $block_id = $variables['block']->module . '-' . $variables['block']->delta;

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

//    // User Login block
//    case 'user-login':
//      // Hide title
//      $variables['title_attributes_array']['class'][] = 'element-invisible';
//      break;

//    //  // Toolkit block title
//    // case 'block-menu-menu-cis-toolkit':
//    //     // Hide title
//    //     $variables['title_attributes_array']['class'][] = 'element-invisible';
//    //     break;

//    // Example of adding Foundation classes
//    case 'block-foo': // Target the block ID
//      // Set grid column or mobile classes or anything else you want.
//      $variables['classes_array'][] = 'six columns';
//      break;
//  }

//  // Add template suggestions for blocks from specific modules.
//  switch($variables['elements']['#block']->module) {
//    case 'menu':
//      $variables['theme_hook_suggestions'][] = 'block__nav';
//    break;
//  }
// }

//function foundation_access_preprocess_views_view(&$variables) {
//}

/**
 * Implements template_preprocess_panels_pane().
 *
 */
//function foundation_access_preprocess_panels_pane(&$variables) {
//}

/**
 * Implements template_preprocess_views_views_fields().
 *
 */
//function foundation_access_preprocess_views_view_fields(&$variables) {
//}

function foundation_access_preprocess_page(&$variables) {
  // Convenience variables
  if (!empty($variables['page']['sidebar_first'])){
    $left = $variables['page']['sidebar_first'];
  }

  if (!empty($variables['page']['sidebar_second'])) {
    $right = $variables['page']['sidebar_second'];
  }

  // Dynamic sidebars
  if (!empty($left) && !empty($right)) {
    $variables['main_grid'] = 'large-6 large-push-3';
    $variables['sidebar_first_grid'] = 'large-3 large-pull-6';
    $variables['sidebar_sec_grid'] = 'large-3';
  } elseif (empty($left) && !empty($right)) {
    $variables['main_grid'] = 'large-9';
    $variables['sidebar_first_grid'] = '';
    $variables['sidebar_sec_grid'] = 'large-3';
  } elseif (!empty($left) && empty($right)) {
    $variables['main_grid'] = 'medium-8 medium-push-4 large-9 large-push-3';
    $variables['sidebar_first_grid'] = 'medium-4 medium-pull-8 large-3 large-pull-9';
    $variables['sidebar_sec_grid'] = '';
  } else {
    $variables['main_grid'] = 'large-12';
    $variables['sidebar_first_grid'] = '';
    $variables['sidebar_sec_grid'] = '';
  }
}








/**
 * Implements theme_form_element_label()
 * Use foundation tooltips
 */
function foundation_access_form_element_label($variables) {
 if (!empty($variables['element']['#title'])) {
   $variables['element']['#title'] = '<span class="secondary label">' . $variables['element']['#title'] . '</span>';
 }
 if (!empty($variables['element']['#description'])) {
   $variables['element']['#description'] = ' <span data-tooltip="top" class="has-tip tip-top" data-width="250" title="' . $variables['element']['#description'] . '">' . t('More information?') . '</span>';
 }
 return theme_form_element_label($variables);
}

/**
 * Implements hook_preprocess_button().
 */
function foundation_access_preprocess_button(&$variables) {
 $variables['element']['#attributes']['class'][] = 'button';
 if (isset($variables['element']['#parents'][0]) && $variables['element']['#parents'][0] == 'submit') {
   $variables['element']['#attributes']['class'][] = 'secondary';
 }
}

/**
 * Implements hook_form_alter()
 * Example of using foundation sexy buttons
 */
//function foundation_access_form_alter(&$form, &$form_state, $form_id) {
//  // Sexy submit buttons
//  if (!empty($form['actions']) && !empty($form['actions']['submit'])) {
//    $classes = (is_array($form['actions']['submit']['#attributes']['class']))
//      ? $form['actions']['submit']['#attributes']['class']
//      : array();
//    $classes = array_merge($classes, array('secondary', 'button', 'radius'));
//    $form['actions']['submit']['#attributes']['class'] = $classes;
//  }
//}

/**
 * Implements hook_form_FORM_ID_alter()
 * Example of using foundation sexy buttons on comment form
 */
//function foundation_access_form_comment_form_alter(&$form, &$form_state) {
  // Sexy preview buttons
//  $classes = (is_array($form['actions']['preview']['#attributes']['class']))
//    ? $form['actions']['preview']['#attributes']['class']
//    : array();
//  $classes = array_merge($classes, array('secondary', 'button', 'radius'));
//  $form['actions']['preview']['#attributes']['class'] = $classes;
//}


/**
 * Implements template_preprocess_panels_pane().
 */
// function zurb_foundation_preprocess_panels_pane(&$variables) {
// }

/**
* Implements template_preprocess_views_views_fields().
*/
/* Delete me to enable
function foundation_access_preprocess_views_view_fields(&$variables) {
 if ($variables['view']->name == 'nodequeue_1') {

   // Check if we have both an image and a summary
   if (isset($variables['fields']['field_image'])) {

     // If a combined field has been created, unset it and just show image
     if (isset($variables['fields']['nothing'])) {
       unset($variables['fields']['nothing']);
     }

   } elseif (isset($variables['fields']['title'])) {
     unset ($variables['fields']['title']);
   }

   // Always unset the separate summary if set
   if (isset($variables['fields']['field_summary'])) {
     unset($variables['fields']['field_summary']);
   }
 }
}

// */

/**
 * Implements hook_css_alter().
 */
function foundation_access_css_alter(&$css) {
//  // Always remove base theme CSS.
//  $theme_path = drupal_get_path('theme', 'zurb_foundation');
//
//  foreach($css as $path => $values) {
//    if(strpos($path, $theme_path) === 0) {
//      unset($css[$path]);
//    }
//  }
  /* Remove some default Drupal css */
  $exclude = array(
    'modules/aggregator/aggregator.css' => FALSE,
    'modules/block/block.css' => FALSE,
    'modules/book/book.css' => FALSE,
    'modules/comment/comment.css' => FALSE,
    'modules/dblog/dblog.css' => FALSE,
    'modules/field/theme/field.css' => FALSE,
    'modules/file/file.css' => FALSE,
    'modules/filter/filter.css' => FALSE,
    'modules/forum/forum.css' => FALSE,
    'modules/help/help.css' => FALSE,
    'modules/menu/menu.css' => FALSE,
    'modules/node/node.css' => FALSE,
    'modules/openid/openid.css' => FALSE,
    'modules/poll/poll.css' => FALSE,
    'modules/profile/profile.css' => FALSE,
    'modules/search/search.css' => FALSE,
    'modules/statistics/statistics.css' => FALSE,
    'modules/syslog/syslog.css' => FALSE,
    'modules/system/admin.css' => FALSE,
    'modules/system/maintenance.css' => FALSE,
    'modules/system/system.css' => FALSE,
    'modules/system/system.admin.css' => FALSE,
    'modules/system/system.maintenance.css' => FALSE,
    'modules/system/system.messages.css' => FALSE,
    'modules/system/system.theme.css' => FALSE,
    'modules/system/system.menus.css' => FALSE,
    'modules/taxonomy/taxonomy.css' => FALSE,
    'modules/tracker/tracker.css' => FALSE,
    'modules/update/update.css' => FALSE,
    'modules/user/user.css' => FALSE,
    // Flexslider below
    //'sites/all/libraries/flexslider/flexslider.css' => FALSE,
   // drupal_get_path('module', 'views') . '/css/views.css' => FALSE,
    drupal_get_path('module', 'cis_lmsless') . '/css/cis_lmsless.css' => FALSE,
    drupal_get_path('module', 'mooc_helper') . '/css/mooc_helper.css' => FALSE,
);

  $css = array_diff_key($css, $exclude);
}

/**
 * Adds CSS classes based on user roles
 * Implements template_preprocess_html().
 *
 */
function foundation_access_preprocess_html(&$variables) {
  foreach($variables['user']->roles as $role){
    $variables['classes_array'][] = 'role-' . drupal_html_class($role);
  }
}


// user profile menu
function foundation_access_menu_tree__menu_cis_user_profile($variables) {
  return  $variables['tree'];
}
function foundation_access_menu_link__menu_cis_user_profile(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = '<ul class="left active dropdown">' . drupal_render($element['#below']) . '</ul>';
    $element['#attributes']['class'][] = 'has-dropdown';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  // account for no link'ed items
  if ($element['#href'] == '<nolink>') {
    $output = '<a href="#">' . $output . '</a>';
  }
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

// Admin Links Menu
function foundation_access_menu_tree__menu_course_tools_menu($variables) {
  return  $variables['tree'];
}
function foundation_access_menu_link__menu_course_tools_menu(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = '<ul class="left active dropdown">' . drupal_render($element['#below']) . '</ul>';
    $element['#attributes']['class'][] = 'has-dropdown';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  // account for no link'ed items
  if ($element['#href'] == '<nolink>') {
    $output = '<a href="#">' . $output . '</a>';
  }
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

// Active Book Outline (Sidebar)

/**
 * Implements menu_tree__cis_service_connection_active_outline().
 */
function foundation_access_menu_tree__cis_service_connection_active_outline($variables) {
  return '<ul class="nav nav-list">' . $variables['tree'] . '</ul>';
}

/**
 * Implements menu_link__cis_service_connection_active_outline().
 */
function foundation_access_menu_link__cis_service_connection_active_outline($variables) {
  $element = $variables['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = '<ul class="active dropdown">' . drupal_render($element['#below']) . '</ul>';
    $element['#attributes']['class'][] = 'has-dropdown';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  // account for no link'ed items
  if ($element['#href'] == '<nolink>') {
    $output = '<a href="#">' . $output . '</a>';
  }
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements theme_menu_local_tasks().
 */
function foundation_access_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="local-task-tabs-1 button-group round">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="local-task-tabs-2 button-group">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function foundation_access_menu_local_task(&$variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];
  $li_class = (!empty($variables['element']['#active']) ? ' class="active"' : '');

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  // Add section tab styling
  $link['localized_options']['attributes']['class'] = array('small', 'button', 'secondary');

  $output = '';
  $output .= '<li' . $li_class . '>';
  $output .= l($link_text, $link['href'], $link['localized_options']);
  $output .= "</li>\n";
  return  $output;
}
