<?php

/**
 * Implements hook_styleguide().
 */
function book_styleguide() {
  $flat = &drupal_static('book_get_flat_menu', array());
  $flat = array(
    1 => array(
      2 => array(
        'mlid' => 2,
        'plid' => 0,
        'title' => styleguide_word(5, 'ucfirst'),
        'access' => TRUE,
        'hidden' => FALSE,
        'has_children' => TRUE,
        'in_active_trail' => FALSE,
        'href' => '',
        'menu_name' => '',
        'depth' => 0,
      ),
      3 => array(
        'mlid' => 3,
        'plid' => 2,
        'title' => styleguide_word(5, 'ucfirst'),
        'access' => TRUE,
        'hidden' => FALSE,
        'has_children' => FALSE,
        'in_active_trail' => FALSE,
        'href' => '',
        'menu_name' => '',
        'depth' => 1,
      ),
      4 => array(
        'mlid' => 4,
        'plid' => 1,
        'title' => styleguide_word(5, 'ucfirst'),
        'access' => TRUE,
        'hidden' => FALSE,
        'has_children' => FALSE,
        'in_active_trail' => FALSE,
        'href' => '',
        'menu_name' => '',
        'depth' => 1,
      ),
      5 => array(
        'mlid' => 5,
        'plid' => 1,
        'title' => styleguide_word(5, 'ucfirst'),
        'access' => TRUE,
        'hidden' => FALSE,
        'has_children' => FALSE,
        'in_active_trail' => FALSE,
        'href' => '',
        'menu_name' => '',
        'depth' => 1,
      ),
    ),
  );

  $items['book_navigation'] = array(
    'title' => t('Book navigation'),
    'theme' => 'book_navigation',
    'variables' => array('book_link' => array(
      'bid' => 0,
      'link_title' => styleguide_word(5, 'ucfirst'),
      'depth' => 1,
      'mlid' => 1,
      'plid' => 2,
      'has_children' => TRUE,
    )),
    'group' => t('Book'),
  );
  return $items;
}
