<?php

/**
 * @file
 * All Process functions for templates and theme fucntions.
 *
 * If you need to add or modify process functions do it in your sub-theme.
 */

/**
 * Process variables for html.tpl.php
 */
function adaptivetheme_process_html(&$vars) {
  // Flatten attributes arrays
  $vars['html_attributes'] = empty($vars['html_attributes_array']) ? '' : drupal_attributes($vars['html_attributes_array']);

  // $rdf_namespaces is kept to maintain backwards compatibility, and because we
  // only want this to print once in html.tpl.php, and not in every conditional
  // comment for IE.
  $vars['rdf_namespaces'] = empty($vars['rdf_namespaces_array']) ? '' : drupal_attributes($vars['rdf_namespaces_array']);

  // Render polyfills
  if ($vars['polyfills']) {
    $vars['polyfills'] = drupal_render($vars['polyfills']);
  }
}

/**
 * Process variables for the html tag
 */
function adaptivetheme_process_html_tag(&$vars) {
  $tag = &$vars['element'];
  if ($tag['#tag'] === 'style' || $tag['#tag'] === 'script') {
    // Remove redundant type attribute and CDATA comments.
    unset($tag['#attributes']['type'], $tag['#value_prefix'], $tag['#value_suffix']);
    // Remove media="all" but leave others unaffected.
    if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
      unset($tag['#attributes']['media']);
    }
  }
}

/**
 * Process variables for page.tpl.php
 */
function adaptivetheme_process_page(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

  // Attributes
  $vars['page_attributes'] = empty($vars['page_attributes_array']) ? '' : drupal_attributes($vars['page_attributes_array']);
  $vars['header_attributes'] = empty($vars['header_attributes_array']) ? '' : drupal_attributes($vars['header_attributes_array']);
  $vars['branding_attributes'] = empty($vars['branding_attributes_array']) ? '' : drupal_attributes($vars['branding_attributes_array']);
  $vars['hgroup_attributes'] = empty($vars['hgroup_attributes_array']) ? '' : drupal_attributes($vars['hgroup_attributes_array']);
  $vars['site_name_attributes'] = empty($vars['site_name_attributes_array']) ? '' : drupal_attributes($vars['site_name_attributes_array']);
  $vars['site_slogan_attributes'] = empty($vars['site_slogan_attributes_array']) ? '' : drupal_attributes($vars['site_slogan_attributes_array']);
  $vars['content_header_attributes'] = empty($vars['content_header_attributes_array']) ? '' : drupal_attributes($vars['content_header_attributes_array']);
  $vars['footer_attributes'] = empty($vars['footer_attributes_array']) ? '' : drupal_attributes($vars['footer_attributes_array']);

  // Theme the menu bars
  if (!empty($vars['primary_navigation'])) {
    $vars['primary_navigation'] = theme('menubar', array('menu' => $vars['primary_navigation'],'type' => 'primary'));
  }
  if (!empty($vars['secondary_navigation'])) {
    $vars['secondary_navigation'] = theme('menubar', array('menu' => $vars['secondary_navigation'], 'type' => 'secondary'));
  }

  // Generate the wrapper element for the main content
  $vars['tag'] = $vars['title'] ? 'section' : 'div';

  // Process enabled Extensions
  if (at_get_setting('enable_extensions', $theme_name) === 1) {
    if (at_get_setting('enable_markup_overides', $theme_name) === 1) {
      // Add page template suggestions per node type, but make the suggestion weak
      // so other suggestions can easily override it.
      if (at_get_setting('page_content_type_suggestions', $theme_name) === 1) {
        if (isset($vars['node'])) {
          $suggestion = 'page__' . $vars['node']->type;
          array_unshift($vars['theme_hook_suggestions'], $suggestion);
        }
      }
      // Force full width wrapper template suggestion if enabled
      if (at_get_setting('page_full_width_wrappers', $theme_name) === 1) {
        array_unshift($vars['theme_hook_suggestions'], 'page__full_width_wrappers');
      }
      // Remove the frontpage title if set in theme settings
      if (at_get_setting('frontpage_remove_title') === 1 && $vars['is_front'] === TRUE) {
        $vars['title'] = '';
      }
    }
  }

  // Page template suggestions for Panels pages
  if (module_exists('page_manager')) {
    if($panel_page = page_manager_get_current_page()) {
      // add a generic suggestion for all panel pages
      $suggestions[] = 'page__panels';
      // add the panel page machine name to the template suggestions
      $suggestions[] = 'page__' . $panel_page['name'];
      // merge the suggestions in to the existing suggestions (as more specific than the existing suggestions)
      $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'], $suggestions);
    }
  }
}

/**
 * Process variables for region.tpl.php
 */
function adaptivetheme_process_region(&$vars) {
  // Initialize and populate the outer wrapper variables
  $vars['outer_prefix'] = '<div class="' . $vars['classes'] . '">';
  $vars['outer_suffix'] = '</div>';

  // Initialize and populate the inner wrapper variables
  $vars['inner_prefix'] = '<div class="region-inner clearfix">';
  $vars['inner_suffix'] = '</div>';

  // Some regions need different or no markup
  // Use a region template with no wrappers for the main content
  if ($vars['region'] === 'content') {
    $vars['outer_prefix'] = '';
    $vars['outer_suffix'] = '';
    $vars['inner_prefix'] = '';
    $vars['inner_suffix'] = '';
  }
  // Menu bar needs an id, nav class and no inner wrapper
  if ($vars['region'] === 'menu_bar') {
    $vars['outer_prefix'] = '<div id="menu-bar" class="nav clearfix">';
    $vars['inner_prefix'] = '';
    $vars['inner_suffix'] = '';
  }
}

/**
 * Process variables for block.tpl.php
 */
function adaptivetheme_process_block(&$vars) {
  // Now we know all the block $tag's, we can generate our wrapper, $tag is
  // set in preprocess. We cant introduce these in preprocess due to attributes
  // and classes not being flattened untill we hit process.
  $vars['outer_prefix'] = '<' . $vars['tag'] . ' id="' . $vars['block_html_id'] . '" class="' . $vars['classes'] . '" ' . $vars['attributes'] . '>';
  $vars['outer_suffix'] = '</' . $vars['tag'] . '>';

  // Block inner attributes
  $vars['block_inner_attributes'] = empty($vars['block_inner_attributes_array']) ? '' : drupal_attributes($vars['block_inner_attributes_array']);

  // Populate the default inner wrappers
  $vars['inner_prefix'] = '<div' . $vars['block_inner_attributes'] . '>';
  $vars['inner_suffix'] = '</div>';

  // Wrap the content variable in a div with attributes
  $vars['content_processed'] = '<div' . $vars['content_attributes'] . '>' . $vars['content'] . '</div>';

  // The menu bar region gets special treatment for the block template
  if ($vars['block']->region === 'menu_bar') {
    $vars['inner_prefix'] = '';
    $vars['inner_suffix'] = '';
    $vars['content_processed'] = $vars['content']; // remove the default wrapper
  }
  // Navigation or menu blocks get special treatment in these regions
  if ($vars['block']->region === 'leaderboard' || $vars['block']->region === 'header') {
    if ($vars['tag'] == 'nav') {
      $vars['content_processed'] = $vars['content']; // remove the default wrapper
    }
  }

  // Some blocks look bad with wrappers so we strip them
  if ($vars['block']->region === 'content') {
    $vars['inner_prefix'] = '';
    $vars['inner_suffix'] = '';
    $vars['content_processed'] = $vars['content'];
  }
  if ($vars['block']->module === 'panels_mini') {
    $vars['inner_prefix'] = '';
    $vars['inner_suffix'] = '';
  }

  // Provide additional suggestions so the block__menu suggestion can be overridden easily
  $vars['theme_hook_suggestions'][] = 'block__' . $vars['block']->region . '__' . $vars['block']->module;
  $vars['theme_hook_suggestions'][] = 'block__' . $vars['block']->region . '__' . $vars['block']->delta;
}

/**
 * Process variables for node.tpl.php
 */
function adaptivetheme_process_node(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

  // Strip default drupal classes if not required
  if (at_get_setting('extra_article_classes', $theme_name) === 0) {
    $classes = explode(' ', $vars['classes']);
    $striped_classes = array('node-sticky', 'node-promoted', 'node-teaser', 'node-preview');
    foreach ($striped_classes as $class) {
      if (in_array($class, $classes)) {
        $classes = str_replace($class, '', $classes);
      }
    }
    $vars['classes'] = trim(implode(' ', $classes));
  }

  // Flatten the additional wrapper attributes array
  $vars['header_attributes'] = empty($vars['header_attributes_array']) ? '' : drupal_attributes($vars['header_attributes_array']);
  $vars['footer_attributes'] = empty($vars['footer_attributes_array']) ? '' : drupal_attributes($vars['footer_attributes_array']);
  $vars['links_attributes'] = empty($vars['links_attributes_array']) ? '' : drupal_attributes($vars['links_attributes_array']);

  // If a panels layout is being rendered by Display Suite in a node we wrap the
  // the layout in markup to make the themers life a little easier and remove
  // the requirement to add a DS template override.
  if (isset($vars['rendered_by_ds']) && $vars['rendered_by_ds'] == TRUE) {
    $vars['panel_prefix'] = '<article id="node-' . $vars['node']->nid . '" class="' . $vars['classes'] . ' rendered-by-ds clearfix"' . $vars['attributes'] . '>';
    $vars['panel_prefix'] .= render($vars['title_prefix']);
    $vars['panel_prefix'] .= render($vars['title_suffix']);
    $vars['panel_suffix'] = '</article>';
  }
}

/**
 * Process variables for comment.tpl.php
 */
function adaptivetheme_process_comment(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

  // Strip default drupal classes if not required.
  if (at_get_setting('extra_comment_classes', $theme_name) === 0) {
    $classes = explode(' ', $vars['classes']);
    $striped_classes = array('comment-by-anonymous', 'comment-by-node-autho', 'comment-by-viewer', 'comment-new');
    foreach ($striped_classes as $class) {
      if (in_array($class, $classes)) {
        $classes = str_replace($class, '', $classes);
      }
    }
    $vars['classes'] = trim(implode(' ', $classes));
  }

  // Flatten the additional wrapper attributes array
  $vars['header_attributes'] = empty($vars['header_attributes_array']) ? '' : drupal_attributes($vars['header_attributes_array']);
  $vars['footer_attributes'] = empty($vars['footer_attributes_array']) ? '' : drupal_attributes($vars['footer_attributes_array']);
  $vars['links_attributes'] = empty($vars['links_attributes_array']) ? '' : drupal_attributes($vars['links_attributes_array']);
}

/**
 * Process variables for adaptivtheme_menubar()
 */
function adaptivetheme_process_menubar(&$vars) {
  // The default theme implementation is a function, so template_process() does
  // not automatically run, so we need to flatten the classes and attributes
  // here. For best performance, only call drupal_attributes() when needed, and
  // note that template_preprocess_menubar() does not initialize the
  // *_attributes_array variables.
  $vars['classes'] = implode(' ', $vars['classes_array']);
  $vars['attributes'] = empty($vars['attributes_array']) ? '' : drupal_attributes($vars['attributes_array']);
  $vars['content_attributes'] = empty($vars['content_attributes_array']) ? '' : drupal_attributes($vars['content_attributes_array']);
}

/**
 * Process variables for maintenance-page.tpl.php
 */
function adaptivetheme_process_maintenance_page(&$vars) {
  // Render polyfills
  if ($vars['polyfills']) {
    $vars['polyfills'] = drupal_render($vars['polyfills']);
  }
}

/**
 * Process variables for user-profile.tpl.php
 */
function adaptivetheme_process_user_profile(&$vars) {
  // If a panels layout is rendered by Display Suite in a user profile we wrap the
  // the layout in markup to make the themers life a little easier and remove
  // the requirement to add a DS template override.
  if (isset($vars['rendered_by_ds']) && $vars['rendered_by_ds'] == TRUE) {
    $vars['panel_prefix'] = '<article id="user-' . $vars['user']->uid . '" class="' . $vars['classes'] . ' rendered-by-ds clearfix"' . $vars['attributes'] . '>';
    $vars['panel_suffix'] = '</article>';
  }
}
