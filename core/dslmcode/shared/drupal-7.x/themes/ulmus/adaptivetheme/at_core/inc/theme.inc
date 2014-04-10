<?php

/**
 * @file
 * Custom theme functions and theme function overrides.
 *
 * If you need to add or modify theme functions do it in your sub-theme.
 */

/**
 * Implements hook_theme()
 *
 * @param $existing
 * @param $type
 * @param $theme
 * @param $path
 *
 * @see http://api.drupal.org/api/drupal/modules!system!system.api.php/function/hook_theme/7
 */
function adaptivetheme_theme($existing, $type, $theme, $path) {
  return array(
    'menubar' => array(
      'render element' => 'element',
    ),
  );
}

/**
 * Returns HTML for a menubar.
 *
 * The contents is normally one of Drupals magic menu variables, such as the
 * Main menu or User menu (secondary menu), but could be any menu you wish to
 * wrap in navigation menu type markup and classes.
 *
 * @param $vars
 * An array containing:
 *  - $menubar_id: CSS id for theming the menubar
 *  - $menu: Holds the themed menu (normally using theme_links())
 *  - the usual $classes, $attributes, $content attributes etc
 *
 * @see adaptivetheme_preprocess_menubar()
 * @see adaptivetheme_process_menubar()
 */
function adaptivetheme_menubar($vars) {
  $output = '';
  $output .= '<div id="' . $vars['menubar_id'] . '" class="' . $vars['classes'] . '"' . $vars['attributes'] . '>';
  $output .= '<nav ' . $vars['content_attributes'] . '>';
  $output .= $vars['menu'];
  $output .= '</nav></div>';
  return $output;
}

/**
 * Helper function for theming main and secondary variables.
 * Provides 7.x-2.x backward compatibility, not used in 7.x-3.x, instead we now
 * use a proper theme function so themers can override it.
 *
 * @param $menu
 * @param $type
 */
function _theme_menu_variables($menu, $type) {
  $output = '<div id="' . $type . '-menu-bar" class="nav"><nav class="clearfix">' . $menu . '</nav></div>';
  return $output;
}

/**
 * Returns HTML for a breadcrumb trail.
 *
 * Adaptivetheme renders breadcrumbs as an ordered list (<ol>...</ol>), wrapping
 * crumbs in li elements and the seperators in span elements. Additionally .crumb,
 * .crumb-first and .crumb-last classes are printed on the li elements. We also
 * remove some silly breadcrumbs from various pages.
 *
 * @param $vars
 *   An associative array containing:
 *   - breadcrumb: An array containing the breadcrumb links.
 */
function adaptivetheme_breadcrumb($vars) {
  global $theme_key;
  $theme_name = $theme_key;
  $breadcrumb = $vars['breadcrumb'];

  if (at_get_setting('breadcrumb_display', $theme_name) == 1) {

    if (at_get_setting('breadcrumb_home', $theme_name) == 0) {
      array_shift($breadcrumb);
    }

    // Remove the rather pointless breadcrumbs for reset password and user
    // register pages, they link to the page you are on, doh!
    if (arg(0) === 'user' && (arg(1) === 'password' || arg(1) === 'register')) {
      array_pop($breadcrumb);
    }

    if (!empty($breadcrumb)) {

      $separator = filter_xss_admin(at_get_setting('breadcrumb_separator', $theme_name));

      // Push the page title onto the end of the breadcrumb array
      if (at_get_setting('breadcrumb_title', $theme_name) == 1) {
        if ($page_title = drupal_get_title()) {
          $breadcrumb[] = '<span class="crumb-title">' . $page_title . '</span>';
        }
      }

      $class = 'crumb';
      end($breadcrumb);
      $last = key($breadcrumb);

      $output = '';
      if (at_get_setting('breadcrumb_label', $theme_name) == 1) {
        $output = '<div id="breadcrumb" class="clearfix"><nav class="breadcrumb-wrapper with-breadcrumb-label clearfix" role="navigation" aria-labelledby="breadcrumb-label">';
        $output .= '<h2 id="breadcrumb-label" class="breadcrumb-label">' . t('You are here') . '</h2>';
      }
      else {
        $output = '<div id="breadcrumb" class="clearfix"><nav class="breadcrumb-wrapper clearfix" role="navigation" aria-labelledby="breadcrumb-label">';
        $output .= '<h2 id="breadcrumb-label" class="element-invisible">' . t('You are here') . '</h2>';
      }
      $output .= '<ol id="crumbs" class="clearfix">';
      foreach ($breadcrumb as $key => $crumb) {
        if ($key == $last && count($breadcrumb) != 1) {
          $class = 'crumb crumb-last';
        }
        if ($key == 0) {
          $output .= '<li class="' . $class . ' crumb-first">' . $crumb . '</li>';
        }
        else {
          $output .= '<li class="' . $class . '"><span class="crumb-separator">' . $separator . '</span>' . $crumb . '</li>';
        }
      }
      $output .= '</ol></nav></div>';

      return $output;
    }
  }
  else {
    return;
  }
}

/**
 * Returns HTML for status and/or error messages, grouped by type.
 *
 * Adaptivetheme adds a div wrapper with CSS id.
 *
 * An invisible heading identifies the messages for assistive technology.
 * Sighted users see a colored box. See http://www.w3.org/TR/WCAG-TECHS/H69.html
 * for info.
 *
 * @param $vars
 *   An associative array containing:
 *   - display: (optional) Set to 'status' or 'error' to display only messages
 *     of that type.
 */
function adaptivetheme_status_messages($vars) {
  $display = drupal_get_messages($vars['display']);
  $output = '';

  if (count($display) > 0) {
    $status_heading = array(
      'status' => t('Status message'),
      'error' => t('Error message'),
      'warning' => t('Warning message'),
    );
    foreach ($display as $type => $messages) {
      $output .= "<div class=\"messages $type\">";
      if (!empty($status_heading[$type])) {
        $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>";
      }
      if (count($messages) > 1) {
        $output .= " <ul>";
        foreach ($messages as $message) {
          $output .= '  <li class="message-item">' . $message . "</li>";
        }
        $output .= " </ul>";
      }
      else {
        $output .= $messages[0];
      }
      $output .= "</div>";
    }
    if ($output != ''){
      $output = "<div id=\"messages\">" . $output . "</div>";
    }
  }

  return $output;
}

/**
 * Returns HTML for a list or nested list of items.
 *
 * Adaptivetheme overrides this in order to insert extra classes into list
 * items, including first, last and odd/even zebra classes.
 *
 * @param $vars
 *   An associative array containing:
 *   - items: An array of items to be displayed in the list. If an item is a
 *     string, then it is used as is. If an item is an array, then the "data"
 *     element of the array is used as the contents of the list item. If an item
 *     is an array with a "children" element, those children are displayed in a
 *     nested list. All other elements are treated as attributes of the list
 *     item element.
 *   - title: The title of the list.
 *   - type: The type of list to return (e.g. "ul", "ol").
 *   - attributes: The attributes applied to the list element.
 */
function adaptivetheme_item_list($vars) {
  global $theme_key;
  $theme_name = $theme_key;

  $items = $vars['items'];
  $title = $vars['title'];
  $type = $vars['type'];
  $attributes = $vars['attributes'];

  // If a class exists use it on the wrapper, for Drupal core this mainly applies
  // to the pager, so you get the wrapper class .item-list-pager
  if (isset($attributes['class'])) {
    $output = '<div class="item-list item-list-' . $attributes['class'][0] . '">';
  }
  else {
    $output = '<div class="item-list">';
  }

  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }

      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }

      if (at_get_setting('extra_item_list_classes', $theme_name) == 1) {
        if ($i & 1) {
          $attributes['class'][] = 'odd';
        }
        else {
          $attributes['class'][] = 'even';
        }
        if ($i == 0) {
          $attributes['class'][] = 'first';
        }
        if ($i == $num_items - 1) {
          $attributes['class'][] = 'last';
        }
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>"; // no new line!
    }
    $output .= "</$type>";
  }
  $output .= '</div>';

  return $output;
}

// Dont run this if the DHTML module is running, it borks its output!
if (!function_exists('dhtml_menu_init')) {
  /**
   * Returns HTML for a wrapper for a menu sub-tree.
   *
   * Adaptivetheme overrides this to insert the clearfix class.
   *
   * @param $vars
   *   An associative array containing:
   *   - tree: An HTML string containing the tree's items.
   *
   * @see template_preprocess_menu_tree()
   */
  function adaptivetheme_menu_tree($vars) {
    return '<ul class="menu clearfix">' . $vars['tree'] . '</ul>';
  }

  /**
   * Returns HTML for a menu link and submenu.
   *
   * Adaptivetheme overrides this to insert extra classes including a depth
   * class and a menu id class. It can also wrap menu items in span elements.
   *
   * @param $vars
   *   An associative array containing:
   *   - element: Structured array data for a menu link.
   */
  function adaptivetheme_menu_link(array $vars) {
    global $theme_key;
    $theme_name = $theme_key;

    $element = $vars['element'];
    $sub_menu = '';

    if ($element['#below']) {
      $sub_menu = drupal_render($element['#below']);
    }

    if (at_get_setting('extra_menu_classes', $theme_name) == 1 && !empty($element['#original_link'])) {
      if (!empty($element['#original_link']['depth'])) {
        $element['#attributes']['class'][] = 'menu-depth-' . $element['#original_link']['depth'];
      }
      if (!empty($element['#original_link']['mlid'])) {
        $element['#attributes']['class'][] = 'menu-item-' . $element['#original_link']['mlid'];
      }
    }

    if (at_get_setting('menu_item_span_elements', $theme_name) == 1 && !empty($element['#title'])) {
      $element['#title'] = '<span>' . $element['#title'] . '</span>';
      $element['#localized_options']['html'] = TRUE;
    }

    if (at_get_setting('unset_menu_titles', $theme_name) == 1 /* && !empty($element['#localized_options']['attributes']['title']) */) {
      unset($element['#localized_options']['attributes']['title']);
    }

    // Possible feature to show menu descriptions in span elements
    //if ($element['#original_link']['menu_name'] == "main-menu" && isset($element['#localized_options']['attributes']['title'])){
    //  $element['#title'] = '<span class="title">' . $element['#title'] . '</span>';
    //  $element['#title'] .= '<span class="description">' . $element['#localized_options']['attributes']['title'] . '</span>';
    //  $element['#localized_options']['html'] = TRUE;
    //}

    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>";
  }
}

/**
 * Returns HTML for a set of links.
 *
 * @param $vars
 *   An associative array containing:
 *   - links: An associative array of links to be themed. The key for each link
 *     is used as its CSS class. Each link should be itself an array, with the
 *     following elements:
 *     - title: The link text.
 *     - href: The link URL. If omitted, the 'title' is shown as a plain text
 *       item in the links list.
 *     - html: (optional) Whether or not 'title' is HTML. If set, the title
 *       will not be passed through check_plain().
 *     - attributes: (optional) Attributes for the anchor, or for the <span> tag
 *       used in its place if no 'href' is supplied. If element 'class' is
 *       included, it must be an array of one or more class names.
 *     If the 'href' element is supplied, the entire link array is passed to l()
 *     as its $options parameter.
 *   - attributes: A keyed array of attributes for the UL containing the
 *     list of links.
 *   - heading: (optional) A heading to precede the links. May be an associative
 *     array or a string. If it's an array, it can have the following elements:
 *     - text: The heading text.
 *     - level: The heading level (e.g. 'h2', 'h3').
 *     - class: (optional) An array of the CSS classes for the heading.
 *     When using a string it will be used as the text of the heading and the
 *     level will default to 'h2'. Headings should be used on navigation menus
 *     and any list of links that consistently appears on multiple pages. To
 *     make the heading invisible use the 'element-invisible' CSS class. Do not
 *     use 'display:none', which removes it from screen-readers and assistive
 *     technology. Headings allow screen-reader and keyboard only users to
 *     navigate to or skip the links. See
 *     http://juicystudio.com/article/screen-readers-display-none.php and
 *     http://www.w3.org/TR/WCAG-TECHS/H42.html for more information.
 */
function adaptivetheme_links($vars) {
  $links = $vars['links'];
  $attributes = $vars['attributes'];
  $heading = $vars['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    if (!empty($heading)) {
      if (is_string($heading)) {
        $heading = array(
          'text' => $heading,
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      if (!empty($heading['id'])) {
        $output .= drupal_attributes(array('id' => $heading['id']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';
    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {

      // Extra menu classes
      if (at_get_setting('extra_menu_classes')) {
        $class = array($key);
        if ($i == 1) {
          $class[] = 'first';
        }
        if ($i == $num_links) {
          $class[] = 'last';
        }
        if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
            && (empty($link['language']) || $link['language']->language == $language_url->language)) {
          $class[] = 'active';
        }
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
      }
      else {
        $output .= '<li>';
      }

      if (isset($link['href'])) {
        if (at_get_setting('menu_item_span_elements')) {
          $link['title'] = '<span>' . $link['title'] . '</span>';
          $link['html'] = TRUE;
        }
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>";
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Returns HTML for a field.
 *
 * Adaptivetheme overrides this in order to better support HTML5 by setting the
 * wrapper as section or div element depending on whether a title is used or not.
 * Fields have no title, instead it treats the field lable as if it were a title
 * and wraps it in h2 elements.
 *
 * This is the default theme implementation to display the value of a field.
 * Theme developers who are comfortable with overriding theme functions may do
 * so in order to customize this markup. This function can be overridden with
 * varying levels of specificity. For example, for a field named 'body'
 * displayed on the 'article' content type, any of the following functions will
 * override this default implementation. The first of these functions that
 * exists is used:
 * - THEMENAME_field__body__article()
 * - THEMENAME_field__article()
 * - THEMENAME_field__body()
 * - THEMENAME_field()
 *
 * Theme developers who prefer to customize templates instead of overriding
 * functions may copy the "field.tpl.php" from the "modules/field/theme" folder
 * of the Drupal installation to somewhere within the theme's folder and
 * customize it, just like customizing other Drupal templates such as
 * page.tpl.php or node.tpl.php. However, it takes longer for the server to
 * process templates than to call a function, so for websites with many fields
 * displayed on a page, this can result in a noticeable slowdown of the website.
 * For these websites, developers are discouraged from placing a field.tpl.php
 * file into the theme's folder, but may customize templates for specific
 * fields. For example, for a field named 'body' displayed on the 'article'
 * content type, any of the following templates will override this default
 * implementation. The first of these templates that exists is used:
 * - field--body--article.tpl.php
 * - field--article.tpl.php
 * - field--body.tpl.php
 * - field.tpl.php
 * So, if the body field on the article content type needs customization, a
 * field--body--article.tpl.php file can be added within the theme's folder.
 * Because it's a template, it will result in slightly more time needed to
 * display that field, but it will not impact other fields, and therefore,
 * is unlikely to cause a noticeable change in website performance. A very rough
 * guideline is that if a page is being displayed with more than 100 fields and
 * they are all themed with a template instead of a function, it can add up to
 * 5% to the time it takes to display that page. This is a guideline only and
 * the exact performance impact depends on the server configuration and the
 * details of the website.
 *
 * @param $vars
 *   An associative array containing:
 *   - label_hidden: A boolean indicating to show or hide the field label.
 *   - title_attributes: A string containing the attributes for the title.
 *   - label: The label for the field.
 *   - content_attributes: A string containing the attributes for the content's
 *     div.
 *   - items: An array of field items.
 *   - item_attributes: An array of attributes for each item.
 *   - classes: A string containing the classes for the wrapping div.
 *   - attributes: A string containing the attributes for the wrapping div.
 *
 * @see template_preprocess_field()
 * @see template_process_field()
 * @see field.tpl.php
 */
function adaptivetheme_field($vars) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $output .= '<h2 class="field-label"' . $vars['title_attributes'] . '>' . $vars['label'] . ':&nbsp;</h2>';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $vars['content_attributes'] . '>';
  foreach ($vars['items'] as $delta => $item) {
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $vars['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';

  // Render the top-level wrapper element.
  $tag = $vars['tag'];
  $output = "<$tag class=\"" . $vars['classes'] . '"' . $vars['attributes'] . '>' . $output . "</$tag>";

  return $output;
}

/**
 * Returns HTML for a taxonomy field.
 *
 * Output taxonomy term fields as unordered lists.
 */
function adaptivetheme_field__taxonomy_term_reference($vars) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $output .= '<h2 class="field-label"' . $vars['title_attributes'] . '>' . $vars['label'] . ':&nbsp;</h2>';
  }

  // Render the items.
  $output .= '<ul class="field-items"' . $vars['content_attributes'] . '>';
  foreach ($vars['items'] as $delta => $item) {
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<li class="' . $classes . '"' . $vars['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
  }

  $output .= '</ul>';

  // Render the top-level wrapper element.
  $tag = $vars['tag'];
  $output = "<$tag class=\"" . $vars['classes'] . '"' . $vars['attributes'] . '>' . $output . "</$tag>";

  return $output;
}

/**
 * Returns HTML for an image field.
 *
 * Output image fields as figure with figcaption for captioning.
 */
function adaptivetheme_field__image($vars) {
  global $theme_key;
  $theme_name = $theme_key;

  // Check if image settings are enabled
  $image_settings_enabled = at_get_setting('enable_image_settings', $theme_name) === 1 ? TRUE : FALSE;

  // Check if captions are enabled for full and/or teaser view modes
  if ($image_settings_enabled == TRUE) {
    $caption_full = at_get_setting('image_caption_full', $theme_name) === 1 ? TRUE : FALSE;
    $caption_teaser = at_get_setting('image_caption_teaser', $theme_name) === 1 ? TRUE : FALSE;
  }

  $output = '';

  // Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $output .= '<h2 class="field-label"' . $vars['title_attributes'] . '>' . $vars['label'] . ':&nbsp;</h2>';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $vars['content_attributes'] . '>';

  foreach ($vars['items'] as $delta => $item) {

    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<figure class="clearfix ' . $classes . '"' . $vars['item_attributes'][$delta] .'>';
    $output .= drupal_render($item);

    // Captions
    if (isset($item['#item']['title']) && !empty($item['#item']['title']) && $image_settings_enabled == TRUE) {

      // Ouch this is ugly, please tell me how to get the actual width of the image.
      // image_style_load($item['#image_style']); will return the image style dimensions,
      // but not the actual image width, which can be different, say when images
      // scale, but I cannot decipher where these dimensions come from when
      // the item is rendered.
      preg_match('/< *img[^>]*width *= *["\']?([^"\']*)/i', $item['#children'], $matches);
      $width = isset($matches[1]) ? $matches[1] . 'px' : 'auto';
      $styles = 'style="width:' . $width . ';"';

      if ($vars['field_view_mode'] == 'full') {
        if ($caption_full == TRUE) {
          $output .= '<figcaption class="caption full-caption"' . $styles .'>' . $item['#item']['title'] . '</figcaption>';
        }
      }
      if ($vars['field_view_mode'] == 'teaser') {
        if ($caption_teaser == TRUE) {
          $output .= '<figcaption class="caption teaser-caption"' . $styles .'>' . $item['#item']['title'] . '</figcaption>';
        }
      }
    }

    $output .= '</figure>';
  }

  $output .= '</div>';

  // Render the top-level wrapper element.
  $tag = $vars['tag'];
  $output = "<$tag class=\"" . $vars['classes'] . '"' . $vars['attributes'] . '>' . $output . "</$tag>";

  return $output;
}


/**
 * Table no_striping boilerplate.
 */
/*
function adaptivetheme_preprocess_table(&$variables) {
  $rows = $variables['rows'];
  foreach ($rows as $number => $row) {
    $variables['rows'][$number]['no_striping'] = TRUE;
  }
}
*/
