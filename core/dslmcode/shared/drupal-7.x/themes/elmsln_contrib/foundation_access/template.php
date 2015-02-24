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
    if ($element['#original_link']['p3'] == 0) {
      if (empty($element['#attributes']['class'])) {
        $element['#attributes']['class'] = array();
      }
      $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($element['#title']));
      // test for active class, meaning this should be expanded by default
      if (in_array('active-trail', $element['#attributes']['class'])) {
        $element['#attributes']['class'][] = 'active';
        $aria = 'true';
      }
      else {
        $aria = 'false';
      }
      $return .= '<section role="tabpanel" aria-hidden="' . $aria . '" class="content" id="' . $short . '-panel">
      <ul class="off-canvas-list content-outline-navigation ' . implode(' ', $element['#attributes']['class']) . '">
      <h2>' . $element['#title'] . '</h2>
      <h3>Subtitle</h3>' . $sub_menu . "</ul>\n</section>";
      // @todo fill the H3 with something meaningful
    }
    elseif ($element['#original_link']['p4'] == 0) {
      $return .= '<li class="has-submenu"><a href="#"><div class="icon-content-white outline-nav-icon" data-grunticon-embed></div><span class="outline-nav-text">' . $element['#title'] . '</span></a>
        <ul class="left-submenu level-1-sub">
          <h2>' . $element['#title'] . '</h2>
          <h3>Subtitle</h3>
          <li class="back">
          <a href="#">' . t('Back') . '</a></li>' . $sub_menu . '</ul></li>';
      // @todo fill the H3 with something meaningful
    }
    else {
      $return .= '<li class="has-submenu">' . l($element['#title'], $element['#href'], $element['#localized_options']) . '
            <ul class="left-submenu">
                <li class="back"><a href="#">' . t('Back') . '</a></li>
                ' . $sub_menu . '
            </ul>
        </li>';
    }
  }
  return $return;
}
