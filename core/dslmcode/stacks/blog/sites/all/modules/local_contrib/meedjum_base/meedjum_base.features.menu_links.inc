<?php
/**
 * @file
 * meedjum_base.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function meedjum_base_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:feed
  $menu_links['main-menu:feed'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'feed',
    'router_path' => 'feed',
    'link_title' => 'Feed',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
  );
  // Exported menu link: main-menu:http://drupal.org/
  $menu_links['main-menu:http://drupal.org/'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'http://drupal.org/',
    'router_path' => '',
    'link_title' => 'Drupal.org',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
  );
  // Exported menu link: main-menu:http://linkedin.com/
  $menu_links['main-menu:http://linkedin.com/'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'http://linkedin.com/',
    'router_path' => '',
    'link_title' => 'LinkedIn',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
  );
  // Exported menu link: main-menu:http://twitter.com/
  $menu_links['main-menu:http://twitter.com/'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'http://twitter.com/',
    'router_path' => '',
    'link_title' => 'Twitter',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
  );
  // Exported menu link: main-menu:mailto:example@example.com
  $menu_links['main-menu:mailto:example@example.com'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'mailto:example@example.com',
    'router_path' => '',
    'link_title' => 'Email',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Drupal.org');
  t('Email');
  t('Feed');
  t('LinkedIn');
  t('Twitter');


  return $menu_links;
}
