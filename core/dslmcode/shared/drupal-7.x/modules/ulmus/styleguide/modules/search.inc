<?php

/**
 * @file
 * Style Guide plugin file for the Search module.
 */

/**
 * Implements hook_styleguide().
 */

function search_styleguide() {
  global $user;
  $items = array();

  $items['search_block_form'] = array(
    'title' => t('Search block form'),
    'content' => drupal_get_form('search_block_form'),
    'group' => t('Search')
  );
  $items['search_no_results'] = array(
    'title' => t('Search, no results'),
    'content' => theme('search_results', array('results' => array())),
    'group' => t('Search')
  );
  // Generate some sample results.
  $results = array();
  for ($i = 0; $i < 5; $i++) {
    $node = array(
      'link' => '#',
      'title' => styleguide_sentence(),
      'user' => theme('username', array('account' => $user)),
      'date' => time(),
      'extra' => array(styleguide_word(2)),
      'snippet' => styleguide_word(25),
      'language' => 'und',
    );
    $results[] = $node;
  }
  $items['search_results'] = array(
    'title' => t('Search, results'),
    'content' => theme('search_results', array('results' => $results)),
    'group' => t('Search')
  );

  return $items;
}
