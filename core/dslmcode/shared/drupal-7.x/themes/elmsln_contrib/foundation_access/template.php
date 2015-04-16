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
}

/**
 * Implements template_preprocess_node.
 */
function foundation_access_preprocess_node(&$variables) {
}

// Active Book Outline (Sidebar)

/**
 * Implements menu_tree__cis_service_connection_high_active_outline().
 */
function foundation_access_menu_tree__cis_service_connection_high_active_outline($variables) {
  return '<ul class="tabs outline-nav-tabs" data-tab role="tablist">' . $variables['tree'] . '</ul>';
}

/**
 * Implements menu_link__cis_service_connection_high_active_outline().
 */
function foundation_access_menu_link__cis_service_connection_high_active_outline($variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $return = '';
  $id = 'zfa-menu-panel-' . $element['#original_link']['mlid'];
  if ($element['#original_link']['p3'] == 0) {
    if (empty($element['#attributes']['class'])) {
        $element['#attributes']['class'] = array();
    }
    $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($element['#title'])) . '-' . $element['#original_link']['mlid'];
    // test for active class, meaning this should be expanded by default
    if (in_array('active-trail', $element['#attributes']['class'])) {
      $element['#attributes']['class'][] = 'active';
      $aria = 'true';
      $tab = '0';
    }
    else {
      $aria = 'false';
      $tab = '-1';
    }
    $return .= '
    <li class="tab-title ' . implode(' ', $element['#attributes']['class']) . '" role="presentational">
      <a href="#' . $short . '-panel" role="tab" tabindex="' . $tab . '" aria-selected="' . $aria . '" controls="' . $short . '-panel">' . $element['#title'] . '</a>
    </li>';
  }
  return $return;
}

/**
 * Implements menu_tree__cis_service_connection_all_active_outline().
 */
function foundation_access_menu_tree__cis_service_connection_all_active_outline($variables) {
  return $variables['tree'];
}

/**
 * Implements menu_link__cis_service_connection_all_active_outline().
 */
function foundation_access_menu_link__cis_service_connection_all_active_outline($variables) {
  static $counter = 1;
  // @todo supply this from elsewhere
  //$word_depth = array('Unit', 'Lesson');
  $word = 'Lesson';
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
    // ending elements
    $options = $element['#localized_options'];
    $options['html'] = TRUE;
    $return .= '<li>' . l('<div class="icon-assignment-black outline-nav-icon" data-grunticon-embed></div>' . $element['#title'], $element['#href'], $options) . '</li>';
  }
  else {
    if (empty($element['#attributes']['class'])) {
      $element['#attributes']['class'] = array();
    }
    // highest level we just render everything below
    if ($element['#original_link']['p3'] == 0) {
      $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($element['#title'])) . '-' . $element['#original_link']['mlid'];
      // test for active class, meaning this should be expanded by default
      if (in_array('active-trail', $element['#attributes']['class'])) {
        $element['#attributes']['class'][] = 'expanded';
        $active = ' active';
      }
      else {
        $active = '';
      }
      $return .= '
      <li class="accordion-navigation">' . "\n" .
      '<a href="#' . $short . '-panel">' . "\n" .
      '<h2>' . $word . ' ' . $counter . '</h2>' . "\n" .
      '<h3>' . $element['#title'] . '</h3>' . "\n" .
      '</a>' . "\n" .
      '<div id="' . $short . '-panel" class="content">' . "\n" .
      '<ul class="accordion sub-tier-1 off-canvas-list content-outline-navigation ' . implode(' ', $element['#attributes']['class']) . '" data-accordion="">' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
      $counter++;
    }
    elseif ($element['#original_link']['p4'] == 0) {
      $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($element['#title'])) . '-' . $element['#original_link']['mlid'];
      $nid = str_replace('node/', '', $element['#href']);
      // test for active class, meaning this should be expanded by default
      if (in_array('active-trail', $element['#attributes']['class'])) {
        $element['#attributes']['class'][] = 'expanded';
        $element['#attributes']['class'][] = 'active';
      }
      $return .= '<li class="has-submenu ' . implode(' ', $element['#attributes']['class']) . '"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed></div><span class="outline-nav-text">' . $element['#title'] . '</span></a>' . "\n" .
      '<ul class="left-submenu level-1-sub">'  . "\n" .
      '<h2>' . $word . ' ' . $counter . '</h2>' . "\n" .
      '<h3>' . $element['#title'] . '</h3>' . "\n" .
      _foundation_access_contextual_menu($short, $nid) .
      '<li class="back">'  . "\n" .
      '<a href="#">' . t('Back') . '</a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
    }
    else {
      $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($element['#title'])) . '-' . $element['#original_link']['mlid'];
      $nid = str_replace('node/', '', $element['#href']);
      // test for active class, meaning this should be expanded by default
      if (in_array('active-trail', $element['#attributes']['class'])) {
        $element['#attributes']['class'][] = 'expanded';
        $element['#attributes']['class'][] = 'active';
      }
      $return .= '<li class="has-submenu ' . implode(' ', $element['#attributes']['class']) . '"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed></div><span class="outline-nav-text">' . $element['#title'] . '</span></a>' . "\n" .
      '<ul class="left-submenu level-2-sub">'  . "\n" .
      '<h2>' . $word . ' ' . $counter . '</h2>' . "\n" .
      '<h3>' . $element['#title'] . '</h3>' . "\n" .
      _foundation_access_contextual_menu($short, $nid) .
      '<li class="back">'  . "\n" .
      '<a href="#">' . t('Back') . '</a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
    }
  }
  return $return;
}

/**
 * Helper function to generate the contextual menu structure
 * @param  [type] $short [description]
 * @param  [type] $nid   [description]
 * @return [type]        [description]
 */
function _foundation_access_contextual_menu($short, $nid) {
  $output = '<div id="off-canvas-admin-menu-' . $short . '" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
          <ul class="button-group">
            <li>' . l(t('Edit outline here'), "node/$nid/outline/children") .'</li>
            <li>' . l(t('Print outline here'), "book/export/html/$nid") .'</li>
            <li>' . l(t('Duplicate outline'), "node/$nid/outline/copy") . '</li>
            <hr>
            <li><a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">Course Settings</a></li>
          </ul>
        </div>
        <div id="off-canvas-add-menu-' . $short . '" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
          <ul class="button-group">
            <li><a href="#">Add a new lesson</a></li>
            <hr>
            <li><a href="#">Add a new unit</a></li>
          </ul>
        </div>' .
      '<nav class="top-bar" data-topbar role="navigation">
    <section class="right top-bar-section">
      <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="off-canvas-admin-menu-' . $short . '" aria-controls="offcanvas-admin-menu" aria-expanded="false">
    <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
      </a>
  </section>
  <section class="right top-bar-section">
      <a href="#" class="off-canvas-toolbar-item toolbar-menu-icon" data-dropdown="off-canvas-add-menu-' . $short . '" aria-controls="add-button" aria-expanded="false">
    <div class="icon-plus-black off-canvas-toolbar-item-icon"></div>
    </a>
  </section>
  </nav>';
  return $output;
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
