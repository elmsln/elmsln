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
      $css .= '.foundation_access-' . $current . "_color{color:$color;}";
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
  drupal_add_css($css, array('type' => 'inline', 'group' => CSS_THEME));
  drupal_add_css('//fonts.googleapis.com/css?family=Droid+Serif:400,700,400italic,700italic|Open+Sans:300,600,700)', array('type' => 'external', 'group' => CSS_THEME));
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
        'class' => array('logo__img'),
      ),
    )), '<front>', array('html' => TRUE));
  }
  // add logo style classes to the logo element
  $logo_classes = array();
  $logo_option = theme_get_setting('foundation_access_logo_options');
  if (isset($logo_option) && !is_null($logo_option)) {
    $logo_classes[] = 'logo--' . $logo_option;
  }
  $variables['logo_classes'] = implode(' ', $logo_classes);
  // support in-domain XSS exceptions
  if (module_exists('cis_connector')) {
    $variables['parent_origin'] = _cis_connector_parent_domain();
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
  else {
    $variables['cis_shortcodes'] = '';
  }
  // support for entity_iframe
  if (module_exists('entity_iframe')) {
    $block = entity_iframe_block_view('entity_iframe_block');
    if (!empty($block['content'])) {
      $variables['cis_shortcodes'] .= $block['content'];
    }
  }
  // wrap non-node content in an article tag
  if (isset($variables['page']['content']['system_main']['main'])) {
    $variables['page']['content']['system_main']['main']['#markup'] = '<article class="large-12 columns view-mode-full">' . $variables['page']['content']['system_main']['main']['#markup'] . '</article>';
  }

  /**
   * @todo Get rid of this logic and put it somewhere else
   *       based on the new design.
   */
  // add a sharing url to view the specific section
  if (module_exists('cis_section')) {
    $url_options = array(
      'absolute' => TRUE,
    );
    $current_section = _cis_connector_section_context();
    if (isset($current_section) && $current_section) {
      $url_options['query']['elmsln_active_course'] = $current_section;
    }
    $current_page = url(current_path(), $url_options);

    // establish the fieldset container for shortcodes
    $field['cis_section_share'] = array(
      '#type' => 'fieldset',
      '#collapsed' => FALSE,
      '#collapsible' => TRUE,
      '#title' => t('Share this page'),
    );
    $field['cis_section_share']['cis_section_share_link'] = array(
      '#title' => t('Page URL'),
      '#value' => $current_page,
      '#type' => 'textfield',
      '#weight' => 0,
    );
    $variables['cis_section_share'] = $field;
  }
}

/**
 * Implementation of hook_preprocess_node().
 */
function foundation_access_preprocess_node(&$variables) {
  $type = 'node';
  $bundle = $variables['type'];
  $viewmode = $variables['view_mode'];

  // add the view mode name to the classes array.
  if (isset($viewmode)) {
    $variables['classes_array'][] = str_replace('_', '-', $viewmode);
  }

  // create inheritance templates and preprocess functions for this entity
  if (module_exists('display_inherit')) {
    display_inherit_inheritance_factory($type, $bundle, $viewmode, 'foundation_access', $variables);
  }
}

/**
 * Display Inherit External Video
 */
function foundation_access_preprocess_node__inherit__external_video__mediavideo(&$variables) {
  $variables['poster'] = FALSE;
  $variables['video_url'] = FALSE;
  $variables['thumbnail'] = FALSE;
  $poster_image_uri = '';
  $elements = &$variables['elements'];

  // Assign Poster
  // if the poster field is available use that for the poster imgage
  if (isset($elements['field_poster']['#items'][0])) {
    $poster_image_uri = $elements['field_poster']['#items'][0]['uri'];
  }
  // if not, attempt to use the thumbnail created by the video upload field
  elseif (isset($variables['content']['field_external_media']['#items'][0]['thumbnail_path'])) {
    $poster_image_uri = $variables['content']['field_external_media']['#items'][0]['thumbnail_path'];
  }
  // if we have found a poster then assign it
  if ($poster_image_uri) {
    $variables['poster'] = image_style_url('mediavideo_poster', $poster_image_uri);
  }

  // Set the video url
  if (isset($elements['field_external_media']['#items'][0]['video_url']) && $elements['field_external_media']['#items'][0]['video_url']) {
    $variables['video_url'] = $elements['field_external_media']['#items'][0]['video_url'];
  }

  // Unset the poster if on the Mediavideo viewmode
  if ($variables['view_mode'] == 'mediavideo') {
    $variables['poster'] = NULL;
  }
}

function foundation_access_preprocess_node__inherit__external_video__mediavideo__thumbnail(&$variables) {
  $variables['thumbnail'] = true;
}

/**
 * Display Inherit Image
 */
function foundation_access_preprocess_node__inherit__elmsmedia_image__image(&$variables) {
  $variables['image'] = array();
  $variables['image_caption'] = '';
  $variables['image_cite'] = '';
  $variables['image_lightbox_url'] = '';

  // Assign Image
  if (isset($variables['elements']['field_image'][0])) {
    $variables['image'] = $variables['elements']['field_image'][0];
    $variables['image']['#item']['attributes']['class'][] = 'image__img';
  }

  // Assign Caption
  if (isset($variables['elements']['field_image_caption'][0]['#markup'])) {
    $variables['image_caption'] = $variables['elements']['field_image_caption'][0]['#markup'];
  }

  // Assign Cite
  if (isset($variables['elements']['field_citation'][0]['#markup'])) {
    $variables['image_cite'] = $variables['elements']['field_citation'][0]['#markup'];
  }

  // If the viewmode contains "lightbox" then enable the lightbox option
  if (strpos($variables['view_mode'], 'lightboxed')) {
    $variables['image_lightbox_url'] = image_style_url('image_lightboxed', $variables['image']['#item']['uri']);
  }
}

/**
 * Display Inherit Image
 */
function foundation_access_preprocess_node__inherit__svg(&$variables) {
  $variables['svg_aria_hidden'] = 'false';
  $variables['svg_alttext'] = NULL;
  $node_wrapper = entity_metadata_wrapper('node', $variables['node']);

  try {
    // if there is an accessbile text alternative then set the svg to aria-hidden
    if ($node_wrapper->field_svg_alttext->value()) {
      $variables['svg_aria_hidden'] = 'true';
      $variables['svg_alttext'] = $node_wrapper->field_svg_alttext->value();
    } 
  } 
  catch (EntityMetadataWrapperException $exc) {
    watchdog(
      'foundation_access',
      'EntityMetadataWrapper exception in %function() <pre>@trace</pre>',
      array('%function' => __FUNCTION__, '@trace' => $exc->getTraceAsString()),
      WATCHDOG_ERROR
    );
  }
}


/**
 * Implements template_menu_link.
 */
function foundation_access_menu_link(&$variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $title = check_plain($element['#title']);
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
    if (isset($icon)) {
      $title = '<div class="icon-' . $icon . '-black outline-nav-icon"></div>' . $title;
    }
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
  $title = check_plain($element['#title']);
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
  return '<li>' . l('<div class="icon-' . $icon . '-black outline-nav-icon"></div>' . $title, $element['#href'], $options) . '</li>';
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
  $title = check_plain($element['#title']);
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $id = 'zfa-menu-panel-' . $element['#original_link']['mlid'];
  // account for no link'ed items
  if ($element['#href'] == '<nolink>') {
    $output = '<a href="#">' . $title . '</a>';
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
    $short = preg_replace('/[^a-zA-Z0-9]/', '', strtolower($title)) . '-' . $element['#original_link']['mlid'];
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
      $return .= '<h3>' . $title . '</h3>' . "\n" .
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
      $return ='<li class="has-submenu level-' . $depth . '-top ' . implode(' ', $element['#attributes']['class']) . '"><a href="#"><div class="icon-content-black outline-nav-icon"></div><span class="outline-nav-text">' . $title . '</span></a>' . "\n" .
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
 * Implements theme_menu_local_task().
 */
function foundation_access_menu_local_task(&$variables) {
  $link = $variables['element']['#link'];
  $link_text = check_plain($link['title']);
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

/**
 * Helper function for return a whitelist of allowed tags that can be
 * present in an SVG file.
 */
function _foundation_access_svg_whitelist_tags() {
  $allowed_tags = array(
    'animate',
    'animateColor',
    'animateMotion',
    'animateTransform',
    'mpath',
    'set',
    'circle',
    'ellipse',
    'line',
    'polygon',
    'polyline',
    'rect',
    'a',
    'defs',
    'glyph',
    'g',
    'marker',
    'mask',
    'missing-glyph',
    'pattern',
    'svg',
    'switch',
    'symbol',
    'desc',
    'metadata',
    'title',
    'feBlend',
    'feColorMatrix',
    'feComponentTransfer',
    'feComposite',
    'feConvolveMatrix',
    'feDiffuseLighting',
    'feDisplacementMap',
    'feFlood',
    'feFuncA',
    'feFuncB',
    'feFuncG',
    'feFuncR',
    'feGaussianBlur',
    'feImage',
    'feMerge',
    'feMergeNode',
    'feMorphology',
    'feOffset',
    'feSpecularLighting',
    'feTile',
    'feTurbulence',
    'font',
    'font-face',
    'font-face-format',
    'font-face-name',
    'font-face-src',
    'font-face-uri',
    'hkern',
    'vkern',
    'linearGradient',
    'radialGradient',
    'stop',
    'image',
    'path',
    'text',
    'use',
    'feDistantLight',
    'fePointLight',
    'feSpotLight',
    'altGlyph',
    'altGlyphDef',
    'altGlyphItem',
    'glyphRef',
    'textPath',
    'tref',
    'tspan',
    'clipPath',
    'color-profile',
    'cursor',
    'filter',
    'foreignObject',
    'script',
    'style',
    'view',
  );

  return $allowed_tags;
}