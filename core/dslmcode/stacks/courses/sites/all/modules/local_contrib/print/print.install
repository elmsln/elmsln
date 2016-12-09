<?php

/**
 * @file
 * Install, update and uninstall functions for the print module.
 *
 * @ingroup print
 */

/**
 * Implements hook_install().
 */
function print_install() {
  $t = get_t();
  drupal_set_message($t('Printer-friendly Page settings are available under !link',
    array('!link' => l($t('Administration > Configuration > User interface > Printer, email and PDF versions'), 'admin/config/user-interface/print'))
  ));
}

/**
 * Implements hook_enable().
 */
function print_enable() {
  // Module weight.
  db_update('system')
    ->fields(array(
      'weight' => 0,
    ))
    ->condition('type', 'module')
    ->condition('name', 'print')
    ->execute();
}

/**
 * Implements hook_uninstall().
 */
function print_uninstall() {
  variable_del('print_comments');
  variable_del('print_css');
  variable_del('print_footer_options');
  variable_del('print_footer_user');
  variable_del('print_html_display_sys_urllist');
  variable_del('print_html_link_text');
  variable_del('print_html_link_text_enabled');
  variable_del('print_html_new_window');
  variable_del('print_html_sendtoprinter');
  variable_del('print_html_windowclose');
  variable_del('print_keep_theme_css');
  variable_del('print_logo_options');
  variable_del('print_logo_url');
  variable_del('print_newwindow');
  variable_del('print_robots_noarchive');
  variable_del('print_robots_nofollow');
  variable_del('print_robots_noindex');
  variable_del('print_sourceurl_date');
  variable_del('print_sourceurl_enabled');
  variable_del('print_sourceurl_forcenode');
  variable_del('print_urls');
  variable_del('print_urls_anchors');

  variable_del('print_html_book_link');
  variable_del('print_html_link_class');
  variable_del('print_html_link_pos');
  variable_del('print_html_link_teaser');
  variable_del('print_html_link_use_alias');
  variable_del('print_html_show_link');
  variable_del('print_html_sys_link_pages');
  variable_del('print_html_sys_link_visibility');

  $settings = db_query("SELECT name FROM {variable} WHERE name LIKE 'print\_html\_display\_%'");
  foreach ($settings as $variable) {
    variable_del($variable->name);
  }
}

/**
 * Implements hook_schema().
 */
function print_schema() {
  $schema['print_node_conf'] = array(
    'description' => 'Printer-friendly version node-specific configuration settings',
    'fields' => array(
      'nid' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'description' => 'The {node}.nid of the node.',
      ),
      'link' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 1,
        'size' => 'tiny',
        'description' => 'Show link',
      ),
      'comments' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 1,
        'size' => 'tiny',
        'description' => 'Show link in individual comments',
      ),
      'url_list' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 1,
        'size' => 'tiny',
        'description' => 'Show Printer-friendly URLs list',
      ),
    ),
    'primary key' => array('nid'),
  );

  $schema['print_page_counter'] = array(
    'description' => 'Printer-friendly version access counter',
    'fields' => array(
      'path' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
        'description' => 'Page path',
      ),
      'totalcount' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 0,
        'size' => 'big',
        'description' => 'Number of page accesses',
      ),
      'timestamp' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 0,
        'description' => 'Last access',
      ),
    ),
    'primary key' => array('path'),
  );

  return $schema;
}

/**
 * Remove hardcoded numeric deltas from all blocks.
 */
function print_update_7000(&$sandbox) {
  $renamed_deltas = array(
    'print' => array(
      '0' => 'print-links',
      '1' => 'print-top',
    ),
  );

  update_fix_d7_block_deltas($sandbox, $renamed_deltas, array());
}

/**
 * Enable the print UI module.
 */
function print_update_7199(&$sandbox) {
  module_enable(array('print_ui'), FALSE);
}

/**
 * Delete old variables.
 */
function print_update_7200(&$sandbox) {
  variable_del('print_settings');
  variable_del('print_sourceurl_settings');
  variable_del('print_html_settings');
  variable_del('print_robot_settings');

  variable_del('print_html_node_link_pages');
  variable_del('print_html_node_link_visibility');

  variable_del('print_text_links');
  variable_del('print_text_published');
  variable_del('print_text_retrieved');
  variable_del('print_text_source_url');

  $settings = db_query("SELECT name FROM {variable} WHERE name LIKE 'print\_display\_%'");
  foreach ($settings as $variable) {
    $name = $variable->name;

    variable_set(str_replace('print_', 'print_html_', $name), variable_get($name));
    variable_del($name);
  }
}

/**
 * Enable block and help area links.
 */
function print_update_7202(&$sandbox) {
  $link_pos = variable_get('print_html_link_pos', drupal_json_decode('{ "link": "link", "block": "block", "help": "help" }'));
  $link_pos['block'] = 'block';
  $link_pos['help'] = 'help';
  variable_set('print_html_link_pos', $link_pos);
}

/**
 * Increase size of the path field in the print_page_counter table.
 */
function print_update_7203(&$sandbox) {
  db_drop_primary_key('print_page_counter');
  db_change_field('print_page_counter', 'path', 'path',
    array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => TRUE,
      'description' => 'Page path',
    ),
    array('primary key' => array('path')));
}
