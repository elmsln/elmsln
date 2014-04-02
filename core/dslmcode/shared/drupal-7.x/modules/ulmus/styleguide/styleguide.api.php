<?php

/**
 * Register a style guide element for display.
 *
 * hook_styleguide() defines an array of items to render for theme
 * testing. Each item is rendered as an element on the style guide page.
 *
 * Each item should be keyed with a unique identifier. This value will be
 * used to create a named anchor link on the Style Guide page.
 *
 * Options:
 *   -- 'title' (required). A string indicating the element name. 
 *   -- 'description' (optional). A short description of the item. 
 *   -- 'theme' (optional). A string indicating the theme function to invoke.
 *    If used, you must return a 'variables' array element. Otherwise, you
 *    must return a 'content' string.
 *   -- 'variables' (optional). An array of named vairables to pass to the
 *    theme function. This structure is designed to let you test your theme
 *    functions for syntax.
 *   -- 'content' (optional). A string or renderable array of content to
 *    present. May be used in conjunction with a 'tag' element, or used instead
 *    of a theme callback.
 *   -- 'tag' (optional). A string indicating a valid HTML tag (wihout <>).
 *    This tag will be wrapped around the content. In Drupal 7, this element is
 *    deprecated in favor of theme_html_tag().
 *   -- 'attributes' (optional). An array of attributes to apply to a tag element.
 *   -- 'group' (optional). A string indicating the context of this element.
 *    Groups are organized within the preview interface. If no group is
 *    provided, the item will be assigned to the 'Common' group.
 *
 * @return $items
 *   An array of items to render.
 */
function hook_styleguide() {
  $items['ul'] = array(
    'title' => t('Unordered list'),
    'theme' => 'item_list',
    'variables' => array('items' => styleguide_list(), 'type' => 'ul'),
    'group' => t('Common'),
  );
  $items['text'] = array(
    'title' => t('Text block'),
    'content' => styleguide_paragraph(3),
    'group' => t('Text'),
    'description' => t('A block of three paragraphs'),
  );
  $items['h1'] = array(
    'title' => t('Text block'),
    'tag' => 'h1',
    'content' => styleguide_word(3),
    'group' => t('Text'),
  );
  $items['div-format'] = array(
    'title' => t('Div special'),
    'description' => t('Add the "format" class to emphasize an entire section.'),
    'tag' => 'div',
    'attributes' => array('class' => 'format'),
    'content' => styleguide_paragraph(1),
  );
  return $items;
}

/**
 * Alter styleguide elements.
 *
 * @param &$items
 *   An array of items to be displayed.
 *
 * @return
 *   No return value. Modify $items by reference.
 *
 * @see hook_styleguide()
 */
function hook_styleguide_alter(&$items) {
  // Add a class to the text test.
  $items['text']['content'] = '<div class="mytestclass">' . $items['text']['content'] . '</div>';
  // Remove the headings tests.
  unset($items['headings']);
}

/**
 * Alter display information about a theme for Style Guide.
 *
 * This function accepts the 'info' property of a $theme object. Currently,
 * only the 'description' element of the $theme_info array is used by
 * Style Guide.
 *
 * Note that the 'description' element will be run through t() automatically.
 *
 * @param &$theme_info
 *   Theme information array.
 * @param $theme
 *   The machine name of this theme.
 *
 * @return
 *   No return value. Modify $theme_info by reference.
 */
function styleguide_styleguide_theme_info_alter(&$theme_info, $theme) {
  if ($theme == 'stark') {
    $theme_info['description'] = 'A basic theme for development.';
  }
}
