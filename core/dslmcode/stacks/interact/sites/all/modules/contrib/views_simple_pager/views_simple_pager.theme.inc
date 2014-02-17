<?php

/**
 * @file
 * 
 * Contains the theme callbacks for our module
 */

/**
 * Theme callback for 'views_simple_pager'
 */
function theme_views_simple_pager($vars) {
  global $pager_page_array, $pager_total;

  $tags = $vars['tags'];
  $element = $vars['element'];
  $parameters = $vars['parameters'];
  $options = $vars['options'];
  
  $prev_label = (!empty($options['prev_label'])) ? $options['prev_label'] : 'previous';
  $next_label = (!empty($options['next_label'])) ? $options['next_label'] : 'next';

  // Yes, I realize that calling t() on user-entered content is a general no-no, but we might get lucky and pick up something like "older" or "newer" from the translation tables  
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t($prev_label)), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t($next_label)), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }
    
    // See if the reverse_links option is set
    if ($options['reverse_links']) {
      $items = array_reverse($items);
    }
    
    return theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pager')),
    ));
  }
}
