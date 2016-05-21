<?php
/**
 * @file
 * assessment_quiz.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function assessment_quiz_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_quiz:node/add/quiz
  $menu_links['menu-elmsln-add_quiz:node/add/quiz'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/quiz',
    'router_path' => 'node/add/quiz',
    'link_title' => 'Quiz',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_quiz:node/add/quiz',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Quiz');

  return $menu_links;
}
