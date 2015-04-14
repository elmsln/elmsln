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
    $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($element['#title']));
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
    $return .= '<li>' . l('<div class="icon-assignment-white outline-nav-icon" data-grunticon-embed></div>' . $element['#title'], $element['#href'], $options) . '</li>';
  }
  else {
    if (empty($element['#attributes']['class'])) {
      $element['#attributes']['class'] = array();
    }
    // highest level we just render everything below
    if ($element['#original_link']['p3'] == 0) {
      $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($element['#title']));
      // test for active class, meaning this should be expanded by default
      if (in_array('active-trail', $element['#attributes']['class'])) {
        $element['#attributes']['class'][] = 'expanded';
        $active = ' active';
      }
      else {
        $active = '';
      }
      $return .= '<li class="accordion-navigation">' . "\n" .
      '<a href="#' . $short . '-panel">' . $element['#title'] . '</a>'  . "\n" .
      '<div id="' . $short . '-panel" class="content' . $active .'">' . "\n" .
      '<ul class="off-canvas-list content-outline-navigation ' . implode(' ', $element['#attributes']['class']) . '">' . "\n" .
      '<h2>' . $word . ' ' . $counter . '</h2>' . "\n" .
      '<h3>' . $element['#title'] . '</h3>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
      $counter++;
    }
    elseif ($element['#original_link']['p4'] == 0) {
      // test for active class, meaning this should be expanded by default
      if (in_array('active-trail', $element['#attributes']['class'])) {
        $element['#attributes']['class'][] = 'expanded';
        $element['#attributes']['class'][] = 'active';
      }
      $return .= '<li class="has-submenu ' . implode(' ', $element['#attributes']['class']) . '"><a href="#"><div class="icon-content-white outline-nav-icon" data-grunticon-embed></div><span class="outline-nav-text">' . $element['#title'] . '</span></a>' . "\n" .
      '<ul class="left-submenu level-1-sub">'  . "\n" .
      '<h2>' . $word . ' ' . $counter . '</h2>' . "\n" .
      '<h3>' . $element['#title'] . '</h3>' . "\n" .
      '<li class="back">'  . "\n" .
      '<a href="#">' . t('Back') . '</a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
    }
    else {
      // test for active class, meaning this should be expanded by default
      if (in_array('active-trail', $element['#attributes']['class'])) {
        $element['#attributes']['class'][] = 'expanded';
        $element['#attributes']['class'][] = 'active';
      }
      $return .= '<li class="has-submenu ' . implode(' ', $element['#attributes']['class']) . '">' . l($element['#title'], $element['#href'], $element['#localized_options']) . '
            <ul class="left-submenu">
                <li class="back"><a href="#">' . t('Back') . '</a></li>
                ' . $sub_menu . '
            </ul>
        </li>';
    }
  }
  return $return;
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
