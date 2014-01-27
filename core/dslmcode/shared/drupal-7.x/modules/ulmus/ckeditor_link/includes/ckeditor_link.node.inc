<?php
/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 */

/**
 * Implementation of hook_ckeditor_link_TYPE_autocomplete().
 */
function ckeditor_link_ckeditor_link_node_autocomplete($string, $limit) {
  $matches = array();

  $node_types = array_keys(array_filter(variable_get('ckeditor_link_autocomplete_node_types', array('- any -' => '- any -'))));
  if (count($node_types)) {
    $query = db_select('node', 'n')
      ->fields('n', array('nid', 'title'))
      ->condition('n.title', '%'. db_like($string) .'%', 'LIKE')
      ->orderBy('n.title')
      ->orderBy('n.type')
      ->range(0, $limit)
      ->addTag('node_access');
    if (!in_array('- any -', $node_types)) {
      $query->condition('n.type', $node_types, 'IN');
    }
    $result = $query->execute();
    foreach ($result as $node) {
      $matches['node/'. $node->nid] = $node->title;
    }
  }

  return $matches;
}

/**
 * Implementation of hook_ckeditor_link_TYPE_revert().
 */
function ckeditor_link_ckeditor_link_node_revert($path, &$langcode) {
  if (!preg_match('`^node/(\d+)$`', $path, $matches)) {
    return;
  }

  $nid = $matches[1];
  $query = db_select('node', 'n')
    ->fields('n', array('title', 'language'))
    ->condition('n.nid', $nid)
    ->addTag('node_access');
  if ($node = $query->execute()->fetchObject()) {
    if ($node->language != LANGUAGE_NONE) {
      $langcode = LANGUAGE_NONE;
    }
    return $node->title;
  }

  return FALSE;
}

/**
 * Implementation of hook_ckeditor_link_TYPE_url().
 */
function ckeditor_link_ckeditor_link_node_url($path, $langcode) {
  if (!preg_match('`^node/(\d+)$`', $path, $matches)) {
    return;
  }

  $nid = $matches[1];

  $languages = ckeditor_link_get_languages();
  if ($languages) {
    $language = db_query('SELECT language FROM {node} WHERE nid = :nid', array(':nid' => $nid))->fetchField();
    if ($language && ($language != LANGUAGE_NONE) && isset($languages[$language])) {
      $langcode = $language;
    }
  }

  return ckeditor_link_url("node/$nid", $langcode);
}

/**
 * Implementation of hook_ckeditor_link_TYPE_settings().
 */
function ckeditor_link_ckeditor_link_node_settings() {
  $form['node'] = array(
    '#type' => 'fieldset',
    '#title' => t('Nodes'),
  );
  $form['node']['ckeditor_link_autocomplete_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#options' => array('- any -' => t('<em>Any content type</em>')) + array_map('check_plain', node_type_get_names()),
    '#default_value' => variable_get('ckeditor_link_autocomplete_node_types', array('- any -' => '- any -')),
    '#description' => t('Select the content types to be available as autocomplete suggestions.'),
  );

  return $form;
}
