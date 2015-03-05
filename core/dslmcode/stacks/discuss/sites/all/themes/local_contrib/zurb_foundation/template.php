<?php
/**
 * @file
 * Template for the Zurb Foundation Theme
 */

/**
 * Loads additional template files.
 */
function _zurb_foundation_load() {
  $themepath = drupal_get_path('theme', 'zurb_foundation');
  include $themepath . '/inc/elements.inc';
  include $themepath . '/inc/form.inc';
  include $themepath . '/inc/menu.inc';
  include $themepath . '/inc/theme.inc';
}

_zurb_foundation_load();

/**
 * Implements hook_html_head_alter().
 */
function zurb_foundation_html_head_alter(&$head_elements) {
  // HTML5 charset declaration.
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8',
  );

  // Optimize mobile viewport.
  $head_elements['mobile_viewport'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1.0',
    ),
  );

  // Remove image toolbar in IE.
  $head_elements['ie_image_toolbar'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'ImageToolbar',
      'content' => 'false',
    ),
  );
}

/**
 * Implements theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function zurb_foundation_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $breadcrumbs = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $breadcrumbs .= '<ul class="breadcrumbs">';

    foreach ($breadcrumb as $key => $value) {
      $breadcrumbs .= '<li>' . $value . '</li>';
    }

    $title = strip_tags(drupal_get_title());
    $breadcrumbs .= '<li class="current"><a href="#">' . $title . '</a></li>';
    $breadcrumbs .= '</ul>';

    return $breadcrumbs;
  }
}

/**
 * Implements theme_field().
 *
 * Changes to the default field output.
 */
function zurb_foundation_field($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div ' . $variables['title_attributes'] . '>' . $variables['label'] . ':&nbsp;</div>';
  }

  // Quick Edit module requires some extra wrappers to work.
  if (module_exists('quickedit')) {
    $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
    foreach ($variables['items'] as $delta => $item) {
      $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
      $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
    }
    $output .= '</div>';
  }
  else {
    foreach ($variables['items'] as $item) {
      $output .= drupal_render($item);
    }
  }

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}

/**
 * Implements theme_field__field_type().
 */
function zurb_foundation_field__taxonomy_term_reference($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<h2 class="field-label">' . $variables['label'] . ': </h2>';
  }

  // Render the items.
  $output .= ($variables['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<li class="taxonomy-term-reference-' . $delta . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
  }
  $output .= '</ul>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . (!in_array('clearfix', $variables['classes_array']) ? ' clearfix' : '') . '">' . $output . '</div>';

  return $output;
}

/**
 * Implements theme_links() targeting the main menu topbar.
 */
function zurb_foundation_links__topbar_main_menu($variables) {
  // We need to fetch the links ourselves because we need the entire tree.
  $links = menu_tree_output(menu_tree_all_data(variable_get('menu_main_links_source', 'main-menu')));
  $output = _zurb_foundation_links($links);
  $variables['attributes']['class'][] = 'left';

  return '<ul' . drupal_attributes($variables['attributes']) . '>' . $output . '</ul>';
}

/**
 * Implements theme_links() targeting the secondary menu topbar.
 */
function zurb_foundation_links__topbar_secondary_menu($variables) {
  // We need to fetch the links ourselves because we need the entire tree.
  $links = menu_tree_output(menu_tree_all_data(variable_get('menu_secondary_links_source', 'user-menu')));
  $output = _zurb_foundation_links($links);
  $variables['attributes']['class'][] = 'right';

  return '<ul' . drupal_attributes($variables['attributes']) . '>' . $output . '</ul>';
}

/**
 * Helper function to output a Drupal menu as a Foundation Top Bar.
 *
 * @links array
 *   An array of menu links.
 *
 * @return string
 *   A rendered list of links, with no <ul> or <ol> wrapper.
 *
 * @see zurb_foundation_links__system_main_menu()
 * @see zurb_foundation_links__system_secondary_menu()
 */
function _zurb_foundation_links($links) {
  $output = '';

  foreach (element_children($links) as $key) {
    $output .= _zurb_foundation_render_link($links[$key]);
  }

  return $output;
}

/**
 * Helper function to recursively render sub-menus.
 *
 * @link array
 *   An array of menu links.
 *
 * @return string
 *   A rendered list of links, with no <ul> or <ol> wrapper.
 *
 * @see _zurb_foundation_links()
 */
function _zurb_foundation_render_link($link) {
  $output = '';

  // This is a duplicate link that won't get the dropdown class and will only
  // show up in small-screen.
  $small_link = $link;

  if (!empty($link['#below'])) {
    $link['#attributes']['class'][] = 'has-dropdown';
  }

  // Render top level and make sure we have an actual link.
  if (!empty($link['#href'])) {
    $rendered_link = NULL;

    // Foundation offers some of the same functionality as Special Menu Items;
    // ie: Dividers and Labels in the top bar. So let's make sure that we
    // render them the Foundation way.
    if (module_exists('special_menu_items')) {
      if ($link['#href'] === '<nolink>') {
        $rendered_link = '<label>' . $link['#title'] . '</label>';
      }
      else {
        if ($link['#href'] === '<separator>') {
          $link['#attributes']['class'][] = 'divider';
          $rendered_link = '';
        }
      }
    }

    if (!isset($rendered_link)) {
      $rendered_link = theme('zurb_foundation_menu_link', array('link' => $link));
    }

    // Test for localization options and apply them if they exist.
    if (isset($link['#localized_options']['attributes']) && is_array($link['#localized_options']['attributes'])) {
      $link['#attributes'] = array_merge_recursive($link['#attributes'], $link['#localized_options']['attributes']);
    }
    $output .= '<li' . drupal_attributes($link['#attributes']) . '>' . $rendered_link;

    if (!empty($link['#below'])) {
      $sub_menu = '';
      // Build sub nav recursively.
      foreach ($link['#below'] as $sub_link) {
        if (!empty($sub_link['#href'])) {
          $sub_menu .= _zurb_foundation_render_link($sub_link);
        }
      }

      $output .= '<ul class="dropdown">' . $sub_menu . '</ul>';
    }

    $output .= '</li>';
  }

  return $output;
}

/**
 * Theme function to render a single top bar menu link.
 */
function theme_zurb_foundation_menu_link($variables) {
  $link = $variables['link'];
  return l($link['#title'], $link['#href'], $link['#localized_options']);
}

/**
 * Implements hook_preprocess_block().
 */
function zurb_foundation_preprocess_block(&$variables) {
  // Convenience variable for block headers.
  $title_class = &$variables['title_attributes_array']['class'];

  // Generic block header class.
  $title_class[] = 'block-title';

  // In the header region visually hide block titles.
  if ($variables['block']->region == 'header') {
    $title_class[] = 'element-invisible';
  }

  // Add a unique class for each block for styling.
  $variables['classes_array'][] = $variables['block_html_id'];

  // Add classes based on region.
  switch ($variables['elements']['#block']->region) {
    // Clear blocks in this region.
    case 'sidebar_first':
      $variables['classes_array'][] = 'clearfix';
      break;

    // Add a striping class & clear blocks in this region.
    case 'sidebar_second':
      $variables['classes_array'][] = 'block-' . $variables['zebra'];
      $variables['classes_array'][] = 'clearfix';
      break;

    case 'header':
      $variables['classes_array'][] = 'header';
      break;

    default;
  }
}

/**
 * Implements template_preprocess_field().
 */
function zurb_foundation_preprocess_field(&$variables) {
  $variables['title_attributes_array']['class'][] = 'field-label';

  // Edit classes for taxonomy term reference fields.
  if ($variables['field_type_css'] == 'taxonomy-term-reference') {
    $variables['content_attributes_array']['class'][] = 'comma-separated';
  }

  // Convenience variables.
  $name = $variables['element']['#field_name'];
  $bundle = $variables['element']['#bundle'];
  $mode = $variables['element']['#view_mode'];
  $classes = &$variables['classes_array'];
  $title_classes = &$variables['title_attributes_array']['class'];
  $content_classes = &$variables['content_attributes_array']['class'];
  $item_classes = array();

  // Global field classes.
  $classes[] = 'field-wrapper';
  $content_classes[] = 'field-items';
  $item_classes[] = 'field-item';

  // Uncomment the lines below to see variables you can use to target a field.
  // print '<strong>Name:</strong> ' . $name . '<br/>';
  // print '<strong>Bundle:</strong> ' . $bundle  . '<br/>';
  // print '<strong>Mode:</strong> ' . $mode .'<br/>';

  // Add specific classes to targeted fields.
  if (isset($field)) {
    switch ($mode) {
      // All teasers.
      case 'teaser':
        switch ($field) {
          // Teaser read more links.
          case 'node_link':
            $item_classes[] = 'more-link';
            break;

          // Teaser descriptions.
          case 'body':
          case 'field_description':
            $item_classes[] = 'description';
            break;

        }
        break;
    }
  }

  // Apply odd or even classes along with our custom classes to each item.
  foreach ($variables['items'] as $delta => $item) {
    $item_classes[] = $delta % 2 ? 'odd' : 'even';
    $variables['item_attributes_array'][$delta]['class'] = $item_classes;
  }

  // Add class to a specific fields across content types.
  switch ($variables['element']['#field_name']) {
    case 'body':
      $variables['classes_array'] = array('body');
      break;

    case 'field_summary':
      $variables['classes_array'][] = 'text-teaser';
      break;

    case 'field_link':
    case 'field_date':
      // Replace classes entirely, instead of adding extra.
      $variables['classes_array'] = array('text-content');
      break;

    case 'field_image':
      // Replace classes entirely, instead of adding extra.
      $variables['classes_array'] = array('image');
      break;

    default:
      break;
  }
  // Add classes to body based on content type and view mode.
  if ($variables['element']['#field_name'] == 'body') {

    // Add classes to Foobar content type.
    if ($variables['element']['#bundle'] == 'foobar') {
      $variables['classes_array'][] = 'text-secondary';
    }

    // Add classes to other content types with view mode 'teaser';
    elseif ($variables['element']['#view_mode'] == 'teaser') {
      $variables['classes_array'][] = 'text-secondary';
    }

    // The rest is text-content.
    else {
      $variables['classes_array'][] = 'field';
    }
  }
}

/**
 * Implements template_preprocess_html().
 *
 * Adds additional classes.
 */
function zurb_foundation_preprocess_html(&$variables) {
  global $language;

  // Clean up the lang attributes.
  $variables['html_attributes'] = 'lang="' . $language->language . '" dir="' . $language->dir . '"';

  // Add language body class.
  if (function_exists('locale')) {
    $variables['classes_array'][] = 'lang-' . $variables['language']->language;
  }

  // @TODO Custom fonts from Google web-fonts
  // $font = str_replace(' ', '+', theme_get_setting('zurb_foundation_font'));
  // if (theme_get_setting('zurb_foundation_font')) {
  // drupal_add_css(
  // 'http://fonts.googleapis.com/css?family=' . $font ,
  // array('type' => 'external',
  // 'group' => CSS_THEME)
  // );
  // }

  // Classes for body element. Allows advanced theming based on context.
  if (!$variables['is_front']) {

    // Add unique class for each page.
    $path = drupal_get_path_alias($_GET['q']);

    // Add unique class for each website section.
    list($section,) = explode('/', $path, 2);
    $arg = explode('/', $_GET['q']);
    if ($arg[0] == 'node' && isset($arg[1])) {
      if ($arg[1] == 'add') {
        $section = 'node-add';
      }
      elseif (isset($arg[2]) && is_numeric($arg[1]) && ($arg[2] == 'edit' || $arg[2] == 'delete')) {
        $section = 'node-' . $arg[2];
      }
    }
    $variables['classes_array'][] = drupal_html_class('section-' . $section);
  }

  // Store the menu item since it has some useful information.
  $variables['menu_item'] = menu_get_item();
  if ($variables['menu_item']) {
    switch ($variables['menu_item']['page_callback']) {
      case 'views_page':
        $variables['classes_array'][] = 'views-page';
        break;

      case 'page_manager_page_execute':
      case 'page_manager_node_view':
      case 'page_manager_contact_site':
        $variables['classes_array'][] = 'panels-page';
        break;
    }
  }
}

/**
 * Implements template_preprocess_node.
 *
 * Add template suggestions and classes.
 */
function zurb_foundation_preprocess_node(&$variables) {
  // Add node--node_type--view_mode.tpl.php suggestions.
  $variables['theme_hook_suggestions'][] = 'node__' . $variables['type'] . '__' . $variables['view_mode'];

  // Add node--view_mode.tpl.php suggestions.
  $variables['theme_hook_suggestions'][] = 'node__' . $variables['view_mode'];

  // Add a class for the view mode.
  if (!$variables['teaser']) {
    $variables['classes_array'][] = 'view-mode-' . $variables['view_mode'];
  }

  $variables['title_attributes_array']['class'][] = 'node-title';
}

/**
 * Implements template_preprocess_page.
 *
 * Add convenience variables and template suggestions.
 */
function zurb_foundation_preprocess_page(&$variables) {
  // Add page--node_type.tpl.php suggestions.
  if (!empty($variables['node'])) {
    $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
  }

  $variables['logo_img'] = '';
  if (!empty($variables['logo'])) {
    $variables['logo_img'] = theme('image', array(
      'path' => $variables['logo'],
      'alt' => strip_tags($variables['site_name']) . ' ' . t('logo'),
      'title' => strip_tags($variables['site_name']) . ' ' . t('Home'),
      'attributes' => array(
        'class' => array('logo'),
      ),
    ));
  }

  $variables['linked_logo'] = '';
  if (!empty($variables['logo_img'])) {
    $variables['linked_logo'] = l($variables['logo_img'], '<front>', array(
      'attributes' => array(
        'rel' => 'home',
        'title' => strip_tags($variables['site_name']) . ' ' . t('Home'),
      ),
      'html' => TRUE,
    ));
  }

  $variables['linked_site_name'] = '';
  if (!empty($variables['site_name'])) {
    $variables['linked_site_name'] = l($variables['site_name'], '<front>', array(
      'attributes' => array(
        'rel' => 'home',
        'title' => strip_tags($variables['site_name']) . ' ' . t('Home'),
      ),
      'html' => TRUE,
    ));
  }

  // Top bar.
  if ($variables['top_bar'] = theme_get_setting('zurb_foundation_top_bar_enable')) {
    $top_bar_classes = array();

    if (theme_get_setting('zurb_foundation_top_bar_grid')) {
      $top_bar_classes[] = 'contain-to-grid';
    }

    if (theme_get_setting('zurb_foundation_top_bar_sticky')) {
      $top_bar_classes[] = 'sticky';
    }

    if ($variables['top_bar'] == 2) {
      $top_bar_classes[] = 'show-for-small';
    }

    $variables['top_bar_classes'] = implode(' ', $top_bar_classes);
    $variables['top_bar_menu_text'] = check_plain(theme_get_setting('zurb_foundation_top_bar_menu_text'));

    $top_bar_options = array();

    if (!theme_get_setting('zurb_foundation_top_bar_custom_back_text')) {
      $top_bar_options[] = 'custom_back_text:false';
    }

    if ($back_text = check_plain(theme_get_setting('zurb_foundation_top_bar_back_text'))) {
      if ($back_text !== 'Back') {
        $top_bar_options[] = "back_text:'{$back_text}'";
      }
    }

    if (!theme_get_setting('zurb_foundation_top_bar_is_hover')) {
      $top_bar_options[] = 'is_hover:false';
    }

    if (!theme_get_setting('zurb_foundation_top_bar_scrolltop')) {
      $top_bar_options[] = 'scrolltop:false';
    }

    if (theme_get_setting('zurb_foundation_top_bar_mobile_show_parent_link')) {
      $top_bar_options[] = 'mobile_show_parent_link:true';
    }

    $variables['top_bar_options'] = ' data-options="' . implode('; ', $top_bar_options) . '"';
  }

  // Alternative header.
  // This is what will show up if the top bar is disabled or enabled only for
  // mobile.
  if ($variables['alt_header'] = ($variables['top_bar'] != 1)) {
    // Hide alt header on mobile if using top bar in mobile.
    $variables['alt_header_classes'] = $variables['top_bar'] == 2 ? ' hide-for-small' : '';
  }

  // Menus for alternative header.
  $variables['alt_main_menu'] = '';

  if (!empty($variables['main_menu'])) {
    $variables['alt_main_menu'] = theme('links__system_main_menu', array(
      'links' => $variables['main_menu'],
      'attributes' => array(
        'id' => 'main-menu-links',
        'class' => array('links', 'inline-list', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  $variables['alt_secondary_menu'] = '';

  if (!empty($variables['secondary_menu'])) {
    $variables['alt_secondary_menu'] = theme('links__system_secondary_menu', array(
      'links' => $variables['secondary_menu'],
      'attributes' => array(
        'id' => 'secondary-menu-links',
        'class' => array('links', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  // Top bar menus.
  $variables['top_bar_main_menu'] = '';
  if (!empty($variables['main_menu'])) {
    $variables['top_bar_main_menu'] = theme('links__topbar_main_menu', array(
      'links' => $variables['main_menu'],
      'attributes' => array(
        'id' => 'main-menu',
        'class' => array('main-nav'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  $variables['top_bar_secondary_menu'] = '';
  if (!empty($variables['secondary_menu'])) {
    $variables['top_bar_secondary_menu'] = theme('links__topbar_secondary_menu', array(
      'links' => $variables['secondary_menu'],
      'attributes' => array(
        'id' => 'secondary-menu',
        'class' => array('secondary', 'link-list'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  // Messages in modal.
  $variables['zurb_foundation_messages_modal'] = theme_get_setting('zurb_foundation_messages_modal');

  // Convenience variables.
  if (!empty($variables['page']['sidebar_first'])) {
    $left = $variables['page']['sidebar_first'];
  }

  if (!empty($variables['page']['sidebar_second'])) {
    $right = $variables['page']['sidebar_second'];
  }

  // Dynamic sidebars.
  if (!empty($left) && !empty($right)) {
    $variables['main_grid'] = 'medium-6 medium-push-3';
    $variables['sidebar_first_grid'] = 'medium-3 medium-pull-6';
    $variables['sidebar_sec_grid'] = 'medium-3';
  }
  elseif (empty($left) && !empty($right)) {
    $variables['main_grid'] = 'medium-9';
    $variables['sidebar_first_grid'] = '';
    $variables['sidebar_sec_grid'] = 'medium-3';
  }
  elseif (!empty($left) && empty($right)) {
    $variables['main_grid'] = 'medium-9 medium-push-3';
    $variables['sidebar_first_grid'] = 'medium-3 medium-pull-9';
    $variables['sidebar_sec_grid'] = '';
  }
  else {
    $variables['main_grid'] = '';
    $variables['sidebar_first_grid'] = '';
    $variables['sidebar_sec_grid'] = '';
  }

  // Ensure modal reveal behavior if modal messages are enabled.
  if (theme_get_setting('zurb_foundation_messages_modal')) {
    drupal_add_js(drupal_get_path('theme', 'zurb_foundation') . '/js/behavior/reveal.js');
  }
}

/**
 * Implements hook_css_alter().
 */
function zurb_foundation_css_alter(&$css) {
  // Remove defaults.css file.
  unset($css[drupal_get_path('module', 'system') . '/system.menus.css']);

  // Remove Drupal core CSS.
  if (theme_get_setting('zurb_foundation_disable_core_css')) {
    foreach ($css as $path => $values) {
      if (strpos($path, 'modules/') === 0) {
        unset($css[$path]);
      }
    }
  }
}

/**
 * Replace Drupal pagers with Foundation pagers.
 */
function zurb_foundation_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // Current is the page we are currently paged to.
  $pager_current = $pager_page_array[$element] + 1;
  // First is the first page listed by this pager piece (re-quantify).
  $pager_first = $pager_current - $pager_middle + 1;
  // Last is the last page listed by this pager piece (re-quantify)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // Max is the maximum page number.
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array(
    'text' => (isset($tags[0]) ? $tags[0] : t('« first')),
    'element' => $element,
    'parameters' => $parameters,
  ));
  $li_previous = theme('pager_previous', array(
    'text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_next = theme('pager_next', array(
    'text' => (isset($tags[3]) ? $tags[3] : t('next ›')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_last = theme('pager_last', array(
    'text' => (isset($tags[4]) ? $tags[4] : t('last »')),
    'element' => $element,
    'parameters' => $parameters,
  ));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('unavailable'),
          'data' => '<a href="">&hellip;</a>',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'data' => theme('pager_previous', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($pager_current - $i),
              'parameters' => $parameters,
            )),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('current'),
            'data' => '<a href="">' . $i . '</a>',
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'data' => theme('pager_next', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($i - $pager_current),
              'parameters' => $parameters,
            )),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('unavailable'),
          'data' => '<a href="">&hellip;</a>',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array('arrow'),
        'data' => $li_last,
      );
    }

    $pager_links = array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#attributes' => array('class' => array('pagination', 'pager')),
    );

    if (theme_get_setting('zurb_foundation_pager_center')) {
      $pager_links['#prefix'] = '<div class="pagination-centered">';
      $pager_links['#suffix'] = '</div>';
    }

    $pager_links = drupal_render($pager_links);

    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . $pager_links;
  }
}

/**
 * Implements hook_theme().
 */
function zurb_foundation_theme() {
  $return = array();

  $return['zurb_foundation_reveal'] = array(
    'variables' => array(
      // The text to display in the link.
      'text' => '',
      // Whether the text uses HTML.
      'html' => FALSE,
      // Whether the reveal uses AJAX content.
      // This can either be set to true, to use the link's href property or be
      // a URL to load the content from. Note that setting this parameter will
      // override the contents of the "reveal" variable.
      'ajax' => FALSE,
      // The path for the link's href property. This is only really useful if
      // you want to set 'ajax' to TRUE (see above).
      'path' => FALSE,
      // The content for the reveal modal. Can be either a string or a render
      // array.
      'reveal' => '',
      // Extra classes to add to the link.
      'link_classes_array' => array('zurb-foundation-reveal'),
      // Extra classes to add to the reveal modal.
      'reveal_classes_array' => array('expand'),
    ),
    'function' => 'theme_zurb_foundation_reveal',
  );

  $return['zurb_foundation_menu_link'] = array(
    'variables' => array('link' => NULL),
    'function' => 'theme_zurb_foundation_menu_link',
  );
  return $return;
}

/**
 * Helper function to store and return markup for reveal modals on the page.
 *
 * This is necessary because we need to add all of the reveals to the bottom of
 * the page to avoid unexpected behavior. For more information please refer to
 * the official Zurb Foundation documentation.
 *
 * @reveal array
 *   A render array for a reveal modal to store.
 *
 * @return array
 *   An array of all reveal render arrays.
 *
 * @see theme_zurb_foundation_reveal()
 */
function _zurb_foundation_reveal($reveal = NULL) {
  $reveals = &drupal_static(__FUNCTION__);

  if (!isset($reveals)) {
    $reveals = array();
  }

  if (isset($reveal)) {
    $reveals[] = $reveal;
  }

  return $reveals;
}


/**
 * Theme function to create Zurb Foundation reveal modals.
 *
 * @see zurb_foundation_theme()
 * @see zurb_foundation_preprocess_region()
 * @see _zurb_foundation_reveal()
 */
function theme_zurb_foundation_reveal($variables) {
  // Generate unique IDs.
  static $counter = 0;

  // Prepare reveal markup.
  $reveal_id = 'zf-reveal-' . ++$counter;
  $variables['reveal_classes_array'][] = 'reveal-modal';
  $reveal_classes = implode(' ', $variables['reveal_classes_array']);

  // Render reveal contents if applicable.
  if (is_array($variables['reveal'])) {
    $variables['reveal'] = drupal_render($variables['reveal']);
  }

  $reveal = array(
    '#markup' => $variables['reveal'],
    '#prefix' => '<div id="' . $reveal_id . '" class="' . $reveal_classes . '" data-reveal>',
    '#suffix' => '<a class="close-reveal-modal">&#215;</a></div>',
  );

  // Add reveal markup to static storage.
  _zurb_foundation_reveal($reveal);

  $build = array(
    '#theme' => 'link',
    '#text' => $variables['text'],
    '#path' => $variables['path'] ? $variables['path'] : '#',
    '#options' => array(
      'attributes' => array(
        'id' => 'zf-reveal-link-' . $counter,
        'class' => $variables['link_classes_array'],
        'data-reveal-id' => $reveal_id,
      ),
      'html' => $variables['html'],
      'external' => TRUE,
    ),
  );

  // Check for AJAX.
  if ($variables['ajax']) {
    if ($variables['ajax'] === TRUE) {
      $variables['ajax'] = 'true';
    }
    $build['#options']['attributes']['data-reveal-ajax'] = $variables['ajax'];
  }

  return drupal_render($build);
}

/**
 * Add the reveal modal markup (if any) to the page_bottom region.
 */
function _zurb_foundation_add_reveals() {
  $markup = '';

  // Retrieve reveal markup from static storage.
  foreach (_zurb_foundation_reveal() as $reveal) {
    $markup .= "\n" . drupal_render($reveal);
  }

  return $markup;
}

/**
 * Implements hook_theme_registry_alter().
 */
function zurb_foundation_theme_registry_alter(&$theme_registry) {
  // Add our own preprocess function to entities so we can add default classes
  // to our custom Display Suite layouts.
  $entity_info = entity_get_info();
  foreach ($entity_info as $entity => $info) {
    if (isset($entity_info[$entity]['fieldable']) && $entity_info[$entity]['fieldable']) {

      // User uses user_profile for theming.
      if ($entity == 'user') {
        $entity = 'user_profile';
      }

      // Only add preprocess functions if entity exposes theme function.
      if (isset($theme_registry[$entity])) {
        $theme_registry[$entity]['preprocess functions'][] = 'zurb_foundation_entity_variables';
      }
    }
  }

  // Support for File Entity.
  if (isset($theme_registry['file_entity'])) {
    $theme_registry['file_entity']['preprocess functions'][] = 'zurb_foundation_entity_variables';
  }

  // Support for Entity API.
  if (isset($theme_registry['entity'])) {
    $theme_registry['entity']['preprocess functions'][] = 'zurb_foundation_entity_variables';
  }
}

/**
 * Add default classes to Display Suite regions if none are set.
 *
 * This approach was taken from Display Suite.
 *
 * @see zurb_foundation_theme_registry_alter()
 */
function zurb_foundation_entity_variables(&$vars) {
  // Only alter entities that have been rendered by Display Suite.
  if (isset($vars['rendered_by_ds'])) {
    // If Display Suite rendered this, it's safe to assume we have the arguments
    // necessary to grab the layout.
    $layout = ds_get_layout($vars['elements']['#entity_type'], $vars['elements']['#bundle'], $vars['elements']['#view_mode']);
    // Set default for zf_wrapper_classes.
    $vars['zf_wrapper_classes'] = ' row';

    // Each layout has different regions, only set default classes if none of
    // them have custom classes.
    switch ($layout['layout']) {
      case 'zf_1col':
        if (empty($vars['ds_content_classes'])) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['ds_content_classes'] = ' columns';
        }
        break;

      case 'zf_2col':
        if (empty($vars['left_classes']) && empty($vars['right_classes'])) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['left_classes'] = ' medium-6 columns';
          $vars['right_classes'] = ' medium-6 columns';
        }
        break;

      case 'zf_2col_stacked':
        if (
          empty($vars['header_classes']) && empty($vars['left_classes'])
          && empty($vars['right_classes']) && empty($vars['footer_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['header_classes'] = ' columns';
          $vars['left_classes'] = ' medium-6 columns';
          $vars['right_classes'] = ' medium-6 columns';
          $vars['footer_classes'] = ' columns';
        }
        break;

      case 'zf_2col_bricks':
        if (empty($vars['top_classes']) && empty($vars['above_left_classes'])
          && empty($vars['above_right_classes']) && empty($vars['middle_classes'])
          && empty($vars['below_left_classes']) && empty($vars['below_right_classes'])
          && empty($vars['bottom_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['top_classes'] = ' columns';
          $vars['above_left_classes'] = ' medium-6 columns';
          $vars['above_right_classes'] = ' medium-6 columns';
          $vars['middle_classes'] = ' columns';
          $vars['below_left_classes'] = ' medium-6 columns';
          $vars['below_right_classes'] = ' medium-6 columns';
          $vars['bottom_classes'] = ' columns';
        }
        break;

      case 'zf_3col':
        if (empty($vars['left_classes']) && empty($vars['middle_classes'])
          && empty($vars['right_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['left_classes'] = ' medium-4 columns columns';
          $vars['middle_classes'] = ' medium-4 columns columns';
          $vars['right_classes'] = ' medium-4 columns columns';
        }
        break;

      case 'zf_3col_stacked':
        if (
          empty($vars['header_classes']) && empty($vars['left_classes'])
          && empty($vars['middle_classes']) && empty($vars['right_classes'])
          && empty($vars['footer_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['header_classes'] = ' columns';
          $vars['left_classes'] = ' medium-4 columns columns';
          $vars['middle_classes'] = ' medium-4 columns columns';
          $vars['right_classes'] = ' medium-4 columns columns';
          $vars['footer_classes'] = ' columns';
        }
        break;

      case 'zf_3col_bricks':
        if (empty($vars['top_classes']) && empty($vars['above_left_classes'])
          && empty($vars['above_middle_classes']) && empty($vars['above_right_classes'])
          && empty($vars['middle_classes']) && empty($vars['below_left_classes'])
          && empty($vars['below_middle_classes']) && empty($vars['below_right_classes'])
          && empty($vars['bottom_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['top_classes'] = ' columns';
          $vars['above_left_classes'] = ' medium-4 columns columns';
          $vars['above_middle_classes'] = ' medium-4 columns columns';
          $vars['above_right_classes'] = ' medium-4 columns columns';
          $vars['middle_classes'] = ' columns';
          $vars['below_left_classes'] = ' medium-4 columns columns';
          $vars['below_middle_classes'] = ' medium-4 columns columns';
          $vars['below_right_classes'] = ' medium-4 columns columns';
          $vars['bottom_classes'] = ' columns';
        }
        break;

      case 'zf_3row':
        if (empty($vars['header_classes']) && empty($vars['ds_content_classes'])
          && empty($vars['footer_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['header_classes'] = ' columns';
          $vars['ds_content_classes'] = ' columns';
          $vars['footer_classes'] = ' columns';
        }
        break;

      case 'zf_4col':
        if (empty($vars['first_classes']) && empty($vars['second_classes'])
          && empty($vars['third_classes']) && empty($vars['fourth_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['first_classes'] = ' medium-3 columns';
          $vars['second_classes'] = ' medium-3 columns';
          $vars['third_classes'] = ' medium-3 columns';
          $vars['fourth_classes'] = ' medium-3 columns';
        }
        break;

      case 'zf_4col_stacked':
        if (
          empty($vars['header_classes']) && empty($vars['first_classes'])
          && empty($vars['second_classes']) && empty($vars['third_classes'])
          && empty($vars['fourth_classes']) && empty($vars['footer_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['header_classes'] = ' columns';
          $vars['first_classes'] = ' medium-3 columns';
          $vars['second_classes'] = ' medium-3 columns';
          $vars['third_classes'] = ' medium-3 columns';
          $vars['fourth_classes'] = ' medium-3 columns';
          $vars['footer_classes'] = ' columns';
        }
        break;

      case 'zf_4col_bricks':
        if (empty($vars['top_classes']) && empty($vars['above_first_classes'])
          && empty($vars['above_second_classes']) && empty($vars['above_third_classes'])
          && empty($vars['above_fourth_classes']) && empty($vars['middle_classes'])
          && empty($vars['below_first_classes']) && empty($vars['below_second_classes'])
          && empty($vars['below_third_classes']) && empty($vars['below_fourth_classes'])
          && empty($vars['bottom_classes'])
        ) {
          $vars['zf_wrapper_classes'] = 'row';
          $vars['top_classes'] = ' columns';
          $vars['above_first_classes'] = ' medium-3 columns';
          $vars['above_second_classes'] = ' medium-3 columns';
          $vars['above_third_classes'] = ' medium-3 columns';
          $vars['above_fourth_classes'] = ' medium-3 columns';
          $vars['middle_classes'] = ' columns';
          $vars['below_first_classes'] = ' medium-3 columns';
          $vars['below_second_classes'] = ' medium-3 columns';
          $vars['below_third_classes'] = ' medium-3 columns';
          $vars['below_fourth_classes'] = ' medium-3 columns';
          $vars['bottom_classes'] = ' columns';
        }
        break;

    }
  }
}

/**
 * Implements hook_process_html_tag().
 *
 * Prunes HTML tags: http://sonspring.com/journal/html5-in-drupal-7#_pruning
 * Updated per https://www.drupal.org/node/2326309
 */
function zurb_foundation_process_html_tag(&$vars) {
  if (theme_get_setting('zurb_foundation_html_tags')) {
    $el = &$vars['element'];

    // Remove type="..."
    unset($el['#attributes']['type']);

    // Remove CDATA from prefix/suffix where necessary.
    if (isset($el['#value_prefix']) && strpos($el['#value_prefix'], 'CDATA') !== FALSE) {
      unset($el['#value_prefix'], $el['#value_suffix']);
    }

    // Remove media="all" but leave others unaffected.
    if (isset($el['#attributes']['media']) && $el['#attributes']['media'] === 'all') {
      unset($el['#attributes']['media']);
    }
  }
}

/**
 * Helper function to output links.
 *
 * Single link as button or multiple links as dropdown/split buttons.
 *
 * @return string
 *   A string of formatted links
 *
 * @variables array
 *   An array of links
 */
function zurb_foundation_links__magic_button($variables) {
  if (empty($variables['attributes']['class'])) {
    $variables['attributes']['class'] = array();
  }

  if (count($variables['links']) > 1) {
    switch ($variables['type']) {
      case 'split':
        return zurb_foundation_links__split_button($variables);

      case 'dropdown':

      default:
        return zurb_foundation_links__dropdown_button($variables);
    }
  }

  $links = $variables['links'];
  $link = array_shift($links);

  if (!isset($link['#localized_options']['attributes'])) {
    $link['#localized_options']['attributes'] = array();
  }
  $link['#localized_options']['attributes'] = array_merge_recursive($link['#localized_options']['attributes'], $variables['attributes']);
  $link['#localized_options']['attributes']['class'][] = 'button';

  return l($link['#title'], $link['#href'], $link['#localized_options']);
}

/**
 * Implements theme_links() with foundations dropdown button markup.
 *
 * @return string
 *   A string outputting links as dropdown button
 *
 * @variables array
 *   An associative array containing:
 *   - label
 *     - Dropdown button label.
 *   - links
 *     - An array of menu links.
 *   - attributes (optional)
 *     - class: Array of additional classes like large, alert, round
 *     - data-dropdown: Custom dropdown id.
 *
 * Formats links for Dropdown Button http://goo.gl/z4lH3q
 */
function zurb_foundation_links__dropdown_button($variables) {
  if (empty($variables['attributes']['class'])) {
    $variables['attributes']['class'] = array();
  }

  $variables['attributes']['class'][] = 'button';
  $variables['attributes']['class'][] = 'dropdown';

  if (!isset($variables['attributes']['data-dropdown'])) {
    $variables['attributes']['data-dropdown'] = drupal_html_id('ddb');
  }

  if (!isset($variables['label'])) {
    $variables['label'] = t('Dropdown button');
  }

  $title = '<a href="#"' . drupal_attributes($variables['attributes']) . '>' . $variables['label'] . '</a>';

  $output = _zurb_foundation_links($variables['links']);
  return $title . '<ul id="' . $variables['attributes']['data-dropdown'] . '" class="f-dropdown" data-dropdown-content>' . $output . '</ul>';
}

/**
 * Implements theme_links() with foundations split button markup.
 *
 * @return string
 *   An HTML string showing multiple links as a dropdown button
 *
 * @variables array
 *   An associative array containing:
 *   - links
 *     - An array of menu links.
 *   - attributes (optional)
 *     - class: Array of additional classes like large, alert, round
 *     - data-dropdown: Custom dropdown id.
 *
 * Formats links for Split Button http://goo.gl/UXVNgF
 */
function zurb_foundation_links__split_button($variables) {
  $links = $variables['links'];

  if (empty($variables['attributes']['class'])) {
    $variables['attributes']['class'] = array();
  }

  $variables['attributes']['class'][] = 'button';

  if (!isset($variables['attributes']['data-dropdown'])) {
    $variables['attributes']['data-dropdown'] = drupal_html_id('ddb');
  }
  $id = $variables['attributes']['data-dropdown'];
  unset($variables['attributes']['data-dropdown']);

  if (!isset($variables['label'])) {
    $variables['label'] = t('Split button');
  }

  $primary_link = array();
  $primary_link['#title'] = $variables['label'] . '<span data-dropdown="' . $id . '"></span>';
  $primary_link['#localized_options']['attributes']['class'][] = 'split';
  $primary_link['#localized_options']['html'] = TRUE;
  $primary_link['#localized_options']['fragment'] = $id;
  $primary_link['#localized_options']['attributes'] = array_merge_recursive($primary_link['#localized_options']['attributes'], $variables['attributes']);
  $primary_link = l($primary_link['#title'], '', $primary_link['#localized_options']);

  $output = _zurb_foundation_links($links);

  return $primary_link . '<ul id="' . $id . '" class="f-dropdown" data-dropdown-content>' . $output . '</ul>';
}
