<?php

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

/**
 * Implements template_preprocess_page.
 */
function foundation_access_preprocess_page(&$variables) {
  // make sure we have lmsless enabled so we don't WSOD
  $variables['cis_lmsless'] = array('active' => array('title' => ''));
  if (module_exists('cis_lmsless')) {
    $variables['cis_lmsless'] = _cis_lmsless_theme_vars();
  }
  if (_cis_connector_role_grouping('staff') || _cis_connector_role_grouping('teacher')) {
    $variables['tabs_extras'][100][] = '<a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">' . t('Course Settings') . '</a>';
  }
  // wrap non-node content in an article tag
  if (isset($variables['page']['content']['system_main']['main'])) {
    $variables['page']['content']['system_main']['main']['#markup'] = '<article class="large-12 columns view-mode-full">' . $variables['page']['content']['system_main']['main']['#markup'] . '</article>';
  }
}

/**
 * Implements menu_link__main_menu.
 */
function foundation_access_menu_link__main_menu(&$variables) {
  return _foundation_access_menu_outline($variables);
}

/**
 * Implements menu_tree__main_menu.
 */
function foundation_access_menu_tree__main_menu($variables) {
  return '<ul class="off-canvas-list has-submenu content-outline-navigation">' . $variables['tree'] . '</ul>';
}

/**
 * Implements menu_tree__menu_course_tools_menu.
 */
function foundation_access_menu_tree__menu_course_tools_menu($variables) {
  return '<ul class="has-submenu">' . $variables['tree'] . '</ul>';
}

/**
 * Helper to generate a menu link in a consistent way at the bottom.
 */
function _foundation_access_single_menu_link($element) {
  $options = $element['#localized_options'];
  $options['html'] = TRUE;
  // default is a page icon
  $icon = 'page';
  // allow for modification of the item
  drupal_alter('foundation_access_menu_item_icon', $icon, $element);
  return '<li>' . l('<div class="icon-' . $icon . '-black outline-nav-icon"></div>' . $element['#title'], $element['#href'], $options) . '</li>';
}

/**
 * Callback to do most of the work for rendering a nested slide out menu
 * @return string             rendered html structure for this menu
 */
function _foundation_access_menu_outline($variables, $word = FALSE, $number = FALSE) {
  static $counter = 1;
  $element = $variables['element'];
  $sub_menu = '';
  $return = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $id = 'zfa-menu-panel-' . $element['#original_link']['mlid'];
  // account for no link'ed items
  if ($element['#href'] == '<nolink>') {
    $output = '<a href="#">' . $element['#title'] . '</a>';
  }
  // account for sub menu things being rendered differently
  if (empty($sub_menu)) {
    // ending element
    $return .= _foundation_access_single_menu_link($element);
  }
  else {
    // ensure class array is at least set
    if (empty($element['#attributes']['class'])) {
      $element['#attributes']['class'] = array();
    }
    // active trail set classes based on that since its a core class
    if (in_array('active-trail', $element['#attributes']['class'])) {
      $element['#attributes']['class'][] = 'expanded';
      $element['#attributes']['class'][] = 'active';
    }
    // calculate relative depth
    $depth = $element['#original_link']['depth'] - 2;
    // generate a short name
    $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($element['#title'])) . '-' . $element['#original_link']['mlid'];
    // extract nid
    $nid = str_replace('node/', '', $element['#href']);
    // test for active class, meaning this should be expanded by default
    if ($element['#original_link']['p3'] == 0) {
      $return .= '
      <li class="has-submenu level-' . $depth . '-top ' . implode(' ', $element['#attributes']['class']) . '">' . "\n" .
      '<a href="#' . $short . '-panel">' . "\n";
      $labeltmp = _foundation_access_auto_label_build($word, $number, $counter);
      if (!empty($labeltmp)) {
        $return .= '<h2>' . $labeltmp . '</h2>' . "\n";
      }
      $return .= '<h3>' . $element['#title'] . '</h3>' . "\n" .
      '</a>' . "\n" .
      '<ul class="left-submenu level-' . $depth . '-sub">'  . "\n" .
      '<div>'  . "\n";
      $labeltmp = _foundation_access_auto_label_build($word, $number, $counter);
      if (!empty($labeltmp)) {
        $return .= '<h2>' . $labeltmp . '</h2>' . "\n";
      }
      $return .= '<h3>' . _foundation_access_single_menu_link($element) . '</h3>' . "\n" .
      '</div>'  . "\n" .
      '<li class="back">'  . "\n" .
      '<a href="#" class="kill-content-before middle-align-wrap center-align-wrap"><div class="icon-arrow-left-black back-arrow-left-btn"></div><span>' . t('Back') . '</span></a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
      $counter++;
    }
    else {
      $return ='<li class="has-submenu level-' . $depth . '-top ' . implode(' ', $element['#attributes']['class']) . '"><a href="#"><div class="icon-content-black outline-nav-icon"></div><span class="outline-nav-text">' . $element['#title'] . '</span></a>' . "\n" .
      '<ul class="left-submenu level-' . $depth . '-sub">'  . "\n" .
      '<div>'  . "\n";
      $labeltmp = _foundation_access_auto_label_build($word, $number, $counter);
      if (!empty($labeltmp)) {
        $return .= '<h2>' . $labeltmp . '</h2>' . "\n";
      }
      $return .= '<h3>' . _foundation_access_single_menu_link($element) . '</h3>' . "\n" .
      '</div>'  . "\n" .
      '<li class="back">'  . "\n" .
      '<a href="#" class="kill-content-before middle-align-wrap center-align-wrap"><div class="icon-arrow-left-black back-arrow-left-btn"></div><span>' . t('Back') . '</span></a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
    }
  }
  return $return;
}

/**
 * Generate an auto labeled element correctly
 * @param  string $word     word for the high level organizer
 * @param  int    $number   whether to show the counter
 * @param  int    $counter  position in the counter for the high level
 * @return string           assembled label for this level
 */
function _foundation_access_auto_label_build($word, $number, $counter) {
  $labeltmp = '';
  if ($word) {
    $labeltmp = $word;
    if ($number) {
      $labeltmp .= ' ' . $counter;
    }
  }
  else {
    if ($number) {
      $labeltmp = $counter;
    }
  }
  return $labeltmp;
}

/**
 * Implements hook_form_alter().
 */
function foundation_access_form_alter(&$form, &$form_state, $form_id) {
  // Search Block Fixes
  if (isset($form['#form_id']) && $form['#form_id'] == 'search_block_form') {
    // unset zurb core stuff
    unset($form['search_block_form']['#prefix']);
    unset($form['search_block_form']['#suffix']);
    unset($form['actions']['submit']['#prefix']);
    unset($form['actions']['submit']['#suffix']);
    // add in custom placeholder to input field
    $form['search_block_form']['#attributes']['placeholder'] = t('Search..');
    // hidden prefix for accessibility
    $form['search_block_form']['#prefix'] = '<h2 class="element-invisible">' . t('Search form') . '</h2>';
    // add on our classes
    $form['search_block_form']['#attributes']['class'] = array('etb-nav_item_search_input');
    $form['actions']['submit']['#attributes']['class'] = array('etb-nav_item_search_btn', 'element-invisible');
    $form['#attributes']['class'] = array('etb-nav_item_search');
  }
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

  $output = '';
  $output .= '<li' . $li_class . '>';
  $output .= l($link_text, $link['href'], $link['localized_options']);
  $output .= "</li>\n";
  return  $output;
}

/**
 * Implements hook_html_head_alter()
 */
function foundation_access_html_head_alter(&$head_elements) {
  $args = arg();
  // account for print module and book print out
  if ($args[0] == 'book' && $args[1] = 'export' && $args[2] == 'html') {
    // parse returned locations array and manually add to html head
    $head_elements['fa_print'] = array(
      '#type' => 'html_tag',
      '#tag' => 'link',
      '#attributes' => array(
        'type' => 'text/css',
        'rel' => 'stylesheet',
        'href' => base_path() . drupal_get_path('theme', 'foundation_access') . '/css/app.css',
      ),
    );
  }
}
