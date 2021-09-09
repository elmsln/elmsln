<?php
/**
 * Implements template_link.
 */
function haxcms_drupal_theme_link(&$variables) {
    $path = $variables['path'];
    $text = $variables['text'];
    $options = $variables['options'];
    // support for lrn icon
    if (isset($variables['options']['fa_icon']) && $variables['options']['fa_icon'] && !isset($variables['options']['identifier'])) {
      $options['html'] = TRUE;
      $text = '<lrn-icon icon="' . $variables['options']['fa_icon'] . '"></lrn-icon>' . $text;
    }
    // support for has-children chevron
    if (isset($variables['options']['has-children']) && $variables['options']['has-children']) {
      $options['attributes']['icon'] = 'chevron-right';
    }
    // account for admin menu link and don't bother styling it w/ custom elements
    if ($text != 'Edit network links' && isset($options['attributes']['class'][0]) && $options['attributes']['class'][0] == 'admin-menu-destination' || (!isset($variables['options']['identifier']) && (strpos($variables['path'], 'admin') === 0 || strpos($variables['path'], 'devel') === 0 || strpos($variables['path'], 'node/add') === 0 || strpos($variables['path'], 'http://drupal.org') === 0 || strpos($variables['path'], 'update.php') === 0))) {
      return '<lrnsys-button label="' . ($options['html'] ? $text : check_plain($text)) . '" hover-class="grey darken-3 white-text" href="' . check_plain(url($path, $options)) . '"'. drupal_attributes($options['attributes']) . '></lrnsys-button>';
    }
    else {
      return _haxcms_drupal_theme_lrnsys_button($text, $path, $options);
    }
  }
  
  /**
   * Shortcut to correctly render a lrnsys-button tag.
   * @param  string $label   button label
   * @param  string $path    href / location
   * @param  array $options  array of options typically passed into l()
   * @return string          a rendered button
   */
  function _haxcms_drupal_theme_lrnsys_button($label, $path, $options) {
    // good thing for static caching
    if (!isset($options['attributes']['hover-class'])) {
      $colors = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
      $options['attributes']['hover-class'] = $colors['color'] . ' ' . $colors['dark'] . ' white-text';
    }
    if (strpos($path, 'apps/') === 0) {
      $options['attributes']['prefetch'] = true;  
    }
    // support links without a path
    if ($path != NULL) {
      $options['attributes']['href'] = check_plain(url($path, $options));
    }
    // if HTML is set to true then we can't handle this at the moment, stuff in light dom
    if ($options['html']) {
      return '<lrnsys-button ' . drupal_attributes($options['attributes']) . '>' . $label . '</lrnsys-button>';
    }
    else {
      return '<lrnsys-button label="' . check_plain($label) . '" ' . drupal_attributes($options['attributes']) . '></lrnsys-button>';
    }
  }
  
  /**
   * Implements template_menu_link.
   */
  function haxcms_drupal_theme_menu_link(&$variables) {
    static $book_active;
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
    }
    // support for add menu to get floating classes
    if ($element['#original_link']['menu_name'] == 'menu-elmsln-add') {
      // support for passing section context as to what they are looking at currently
      if (_cis_connector_system_type() != 'service' && $element['#original_link']['router_path'] != 'cis-quick-setup') {
        $element['#localized_options']['query']['elmsln_course'] = _cis_connector_course_context();
        $element['#localized_options']['query']['elmsln_section'] = _cis_connector_section_context();
      }
      // set destination to bounce back here when done
      if (_cis_connector_system_type() != 'service') {
        $element['#localized_options']['query']['destination'] = current_path();
      }
      // load up a map of icons and color associations
      $icon_map = _elmsln_core_icon_map();
      $icon = str_replace(' ', '_', drupal_strtolower($title));
      // see if we have an icon
      if (isset($icon_map[$icon])) {
        // see if this is being sent externally
        if (strpos($element['#href'], 'elmsln/redirect') === 0) {
          $element['#localized_options']['attributes']['class'][] = 'elmsln-core-external-context-apply';
        }
        if (isset($icon_map[$icon]['text'])) {
          $textcolor = $icon_map[$icon]['text'];
        }
        else {
          $textcolor = 'white-text';
        }
        $title = '<lrnapp-fab-speed-dial-action icon="' . $icon_map[$icon]['icon'] . '" color="' . $icon_map[$icon]['color'] . '">' . $title . '</lrnapp-fab-speed-dial-action>';
        $element['#localized_options']['html'] = TRUE;
      }
      else {
        $lmsless_classes = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
        $element['#localized_options']['attributes']['class'][] = $lmsless_classes['color'];
        $element['#localized_options']['attributes']['class'][] = 'white-text';
        $element['#localized_options']['attributes']['class'][] = $lmsless_classes['dark'];
      }
    }
    elseif ($element['#original_link']['menu_name'] == 'menu-elmsln-navigation') {
      $lmsless_classes = _cis_lmsless_get_distro_classes(elmsln_core_get_profile_key());
      $element['#attributes']['class'][] = 'tab';
      $element['#localized_options']['attributes']['class'][] = $lmsless_classes['text'];
      $element['#localized_options']['attributes']['target'] = '_self';
    }
    elseif (strpos($element['#original_link']['menu_name'], 'book-toc-') === 0) {
      $element['#attributes']['class'][] = 'elmsln-book-item';
      if ($element['#original_link']['has_children'] == 1) {
        $element['#localized_options']['has-children'] = TRUE;
        $element['#localized_options']['attributes']['class'][] = 'has-children';
      }
      elseif (isset($element['#original_link']['options']['fa_icon']) && !empty($element['#original_link']['options']['fa_icon'])) {
        // overview page renders differently for full screen mode
        if (current_path() == 'mooc/book-toc') {
          $element['#localized_options']['attributes']['class'][] = 'icon-' . $element['#original_link']['options']['fa_icon'];
          $element['#localized_options']['attributes']['class'][] = 'elmsln-icon';
        }
        else {
          $element['#attributes']['class'][] = 'icon-' . $element['#original_link']['options']['fa_icon'];
          $element['#attributes']['class'][] = 'elmsln-icon';
        }
      }
      // look for active trail being hit in a book
      if (array_search('active-trail', $element['#attributes']['class'])) {
        $book_active = TRUE;
      }
      // if we haven't set an active page yet then keep claiming we past it
      if (!isset($book_active)) {
        $element['#attributes']['class'][] = 'past-page';
      }
    }
    $output = l($title, $element['#href'], $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
  }
  
  /**
   * Implements a generic hook_menu_tree callback.
   */
  function haxcms_drupal_theme_menu_tree($variables) {
    return '<ul class="menu">' . $variables['tree'] . '</ul>';
  }
  
  /**
   * Implements menu_tree__menu_elmsln_settings.
   */
  function haxcms_drupal_theme_menu_tree__menu_elmsln_settings($variables) {
    return '<ul class="has-submenu">' . $variables['tree'] . '</ul>';
  }