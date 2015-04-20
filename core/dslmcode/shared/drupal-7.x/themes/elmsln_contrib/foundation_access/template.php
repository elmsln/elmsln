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
  $variables['tabs_extras'] = '<hr>
    <li>' . l(t('Download Page'), 'book/export/html/' . arg(1)) . '</li>';
  if (user_access('access contextual links')) {
    $variables['tabs_extras'] = '<hr>
    <li class="cis_accessibility_check"></li>
    <hr>
    <li><a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">Course Settings</a></li>';
  }
}

/**
 * Implements template_preprocess_node.
 */
function foundation_access_preprocess_node(&$variables) {
}

/**
 * Implements template_preprocess_region.
 */
function foundation_access_preprocess_region(&$variables) {
  // add in the chevron contextual options for the high level
  if ($variables['region'] == 'left_menu' && function_exists('_cis_service_connection_active_outline') && user_access('access contextual links')) {
    $node = _cis_service_connection_active_outline();
     $variables['button_group'] =
     '<div id="off-canvas-admin-menu" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
     <ul class="button-group">
       <li>' . l(t('Edit course outline'), 'admin/content/book/' . $node->nid) . '</li>
       <li>' . l(t('Print course outline'), 'book/export/html/' . $node->nid) . '</li>
       <li>' . l(t('Save As new outline'), 'admin/content/book/copy/' . $node->nid) . '</li>
       <hr>
       <li><a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">Course Settings</a></li>
     </ul>
     </div>
    <nav class="top-bar" data-topbar role="navigation">
      <section class="right top-bar-section">
        <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="off-canvas-admin-menu" aria-controls="offcanvas-admin-menu" aria-expanded="false">
          <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
        </a>
     </section>
    </nav>';
  }
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
  $word = t('Lesson');
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
    $return .= '<li>' . l('<div class="icon-assignment-black outline-nav-icon"></div>' . $element['#title'], $element['#href'], $options) . '</li>';
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
      '<a href="#' . $short . '-panel">' . "\n" .
      '<h2>' . $word . ' ' . $counter . '</h2>' . "\n" .
      '<h3>' . $element['#title'] . '</h3>' . "\n" .
      '</a>' . "\n" .
      '<ul class="left-submenu level-' . $depth . '-sub">'  . "\n" .
      _foundation_access_contextual_menu($short, $nid) .
      '<h2>' . $word . ' ' . $counter . '</h2>' . "\n" .
      '<h3>' . $element['#title'] . '</h3>' . "\n" .
      '<li class="back">'  . "\n" .
      '<a href="#" class="kill-content-before"><div class="icon-arrow-left-black back-arrow-left-btn"></div>' . t('Back') . '</a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
      $counter++;
    }
    else {
      $return ='<li class="has-submenu level-' . $depth . '-top ' . implode(' ', $element['#attributes']['class']) . '"><a href="#"><div class="icon-content-black outline-nav-icon"></div><span class="outline-nav-text">' . $element['#title'] . '</span></a>' . "\n" .
      '<ul class="left-submenu level-' . $depth . '-sub">'  . "\n" .
      _foundation_access_contextual_menu($short, $nid) .
      '<h2>' . $word . ' ' . $counter . '</h2>' . "\n" .
      '<h3>' . $element['#title'] . '</h3>' . "\n" .
      '<li class="back">'  . "\n" .
      '<a href="#" class="kill-content-before"><div class="icon-arrow-left-black back-arrow-left-btn"></div>' . t('Back') . '</a></li>' . "\n" .
      $sub_menu . "\n</ul>\n</li>";
    }
  }
  return $return;
}

/**
 * Helper function to generate the contextual menu structure
 * @param  string $short machine name unique to the page
 * @param  int $nid   node id
 * @return rendered output
 */
function _foundation_access_contextual_menu($short, $nid) {
  if (user_access('access contextual links'))
  $render_array = array(
    'short' => $short,
    'cis_links' => menu_contextual_links('cis_lmsless', 'node', array($nid)),
    '#theme_wrappers' => array('cis_lmsless_contextual_container'),
  );
  return render($render_array);
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
