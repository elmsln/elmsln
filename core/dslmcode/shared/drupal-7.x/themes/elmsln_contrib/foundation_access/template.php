<?php

/**
 * Implements hook_menu_link_alter().
 *
 * Allow Foundation Access to affect the menu links table
 * so that we can allow other projects to store an icon
 * representation of what we're working on or status information
 * about it.
 *
 */
function foundation_access_menu_link_alter(&$item) {
  // this allows other projects to influence the icon seletion for menu items
  $icon = 'page';
  // #href proprety expected for use in the FA menu item icon
  $item['#href'] = $item['link_path'];
  // support for the primary theme used with MOOC platform
  drupal_alter('foundation_access_menu_item_icon', $icon, $item);
  // store the calculated icon here
  $item['options']['fa_icon'] = $icon;
}

/**
 * Adds CSS classes based on user roles
 * Implements template_preprocess_html().
 *
 */
function foundation_access_preprocess_html(&$variables) {
  // loop through our system specific colors
  $colors = array('primary', 'secondary', 'required', 'optional');
  $css = '';
  foreach ($colors as $current) {
    $color = theme_get_setting('foundation_access_' . $current . '_color');
    // see if we have something that could be valid hex
    if (strlen($color) == 6 || strlen($color) == 3) {
      $color = '#' . $color;
      $css .= '.foundation_access-' . $current . '_color{color:$color;}';
      // specialized additions for each wheel value
      switch ($current) {
        case 'primary':
          $css .= ".etb-book h1,.etb-book h2 {color: $color !important;}";
        break;
        case 'secondary':
          $css .= ".etb-book h3,.etb-book h4,.etb-book h5 {color: $color !important;}";
        break;
        case 'required':
          $css .= "div.textbook_box_required li:hover:before{border-color: $color !important;} div.textbook_box_required li:before {background: $color !important;} div.textbook_box_required { border: 2px solid $color !important;} .textbook_box_required h3 {color: $color !important;}";
        break;
        case 'optional':
          $css .= "div.textbook_box_optional li:hover:before{border-color: $color !important;} div.textbook_box_optional li:before {background: $color !important;} div.textbook_box_optional { border: 2px solid $color !important;} .textbook_box_optional h3 {color: $color !important;}";
        break;
      }
    }
  }
  drupal_add_css($css, array('type' => 'inline'));
  drupal_add_css('//fonts.googleapis.com/css?family=Droid+Serif:400,700,400italic,700italic|Open+Sans:300,600,700)', array('type' => 'external'));
  // theme path shorthand should be handled here
  $variables['theme_path'] = base_path() . drupal_get_path('theme', 'foundation_access');
  foreach($variables['user']->roles as $role){
    $variables['classes_array'][] = 'role-' . drupal_html_class($role);
  }
  // add page level variables into scope for the html tpl file
  $variables['site_name'] = check_plain(variable_get('site_name', 'ELMSLN'));
  $variables['logo'] = theme_get_setting('logo');
  $variables['logo_img'] = '';
  // make sure we have a logo before trying to render a real one to screen
  if (!empty($variables['logo'])) {
    $variables['logo_img'] = l(theme('image', array(
      'path' => $variables['logo'],
      'alt' => strip_tags($variables['site_name']) . ' ' . t('logo'),
      'title' => strip_tags($variables['site_name']) . ' ' . t('Home'),
      'attributes' => array(
        'class' => array('logo'),
      ),
    )), '<front>', array('html' => TRUE));
  }
}

/**
 * Implements template_preprocess_page.
 */
function foundation_access_preprocess_page(&$variables) {
  // make sure we have lmsless enabled so we don't WSOD
  $variables['cis_lmsless'] = array('active' => array('title' => ''));
  // support for lmsless since we don't require it
  if (module_exists('cis_lmsless')) {
    $variables['cis_lmsless'] = _cis_lmsless_theme_vars();
  }
  // support for cis_shortcodes
  if (module_exists('cis_shortcodes')) {
    $block = cis_shortcodes_block_view('cis_shortcodes_block');
    if (!empty($block['content'])) {
      $variables['cis_shortcodes'] = $block['content'];
    }
  }
  // support for entity_iframe
  if (module_exists('entity_iframe')) {
    $block = entity_iframe_block_view('entity_iframe_block');
    if (!empty($block['content'])) {
      $variables['cis_shortcodes'] .= $block['content'];
    }
  }
  // show staff / instructors the course tools menu
  if (_cis_connector_role_groupings(array('staff','teacher'))) {
    $variables['tabs_extras'][100][] = '<hr>';
    $variables['tabs_extras'][100][] = '<a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">' . t('Course Settings') . '</a>';
  }
  // wrap non-node content in an article tag
  if (isset($variables['page']['content']['system_main']['main'])) {
    $variables['page']['content']['system_main']['main']['#markup'] = '<article class="large-12 columns view-mode-full">' . $variables['page']['content']['system_main']['main']['#markup'] . '</article>';
  }
}

/**
 * Implements template_menu_link.
 */
function foundation_access_menu_link(&$variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $title = $element['#title'];
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  // special handling for node based menu items
  if ($element['#original_link']['router_path'] == 'node/%') {
    $element['#localized_options']['html'] = TRUE;

    if ($element['#below']) {
      $element['#localized_options']['attributes']['class'][] = 'has-children';
    }
    // see if we have a localized override
    if (isset($element['#localized_options']['fa_icon'])) {
      $icon = $element['#localized_options']['fa_icon'];
    }
    // prefix node based titles with an icon
    $title = '<div class="icon-' . $icon . '-black outline-nav-icon"></div>' . $title;
  }
  $output = l($title, $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements menu_tree__menu_cis_add.
 */
function foundation_access_menu_tree__menu_cis_add($variables) {
  return '<ul id="add-menu-drop" data-dropdown-content class="f-dropdown" role="menu" aria-hidden="false" tabindex="-1" class="menu">' . $variables['tree'] . '</ul>';
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
  // ensure class array is at least set
  if (empty($element['#attributes']['class'])) {
    $element['#attributes']['class'] = array();
  }
  $classes = implode(' ', $element['#attributes']['class']);
  $options['attributes']['class'] = $element['#attributes']['class'];
  $icon = 'page';
  if (isset($options['fa_icon'])) {
    $icon = $options['fa_icon'];
  }
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

/**
 * Implements theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function foundation_access_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $breadcrumbs = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $breadcrumbs .= '<ul class="breadcrumbs">';
    foreach ($breadcrumb as $key => $value) {
      $breadcrumbs .= '<li>' . strip_tags(htmlspecialchars_decode($value), '<br><br/><a></a><span></span>') . '</li>';
    }

    $title = strip_tags(drupal_get_title());
    $breadcrumbs .= '<li class="current"><a href="#">' . $title . '</a></li>';
    $breadcrumbs .= '</ul>';

    return $breadcrumbs;
  }
}
