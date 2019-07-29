<?php

/**
 * @file
 * Install, update and uninstall functions for the print_epub module.
 *
 * @ingroup print
 */

/**
 * Implements hook_enable().
 */
function print_epub_enable() {
  // Module weight.
  db_update('system')
    ->fields(array(
      'weight' => 4,
    ))
    ->condition('type', 'module')
    ->condition('name', 'print_epub')
    ->execute();
}

/**
 * Implements hook_uninstall().
 */
function print_epub_uninstall() {
  variable_del('print_epub_display_sys_urllist');
  variable_del('print_epub_filename');
  variable_del('print_epub_images_via_file');
  variable_del('print_epub_link_text');
  variable_del('print_epub_link_text_enabled');
  variable_del('print_epub_epub_tool');

  variable_del('print_epub_book_link');
  variable_del('print_epub_link_class');
  variable_del('print_epub_link_pos');
  variable_del('print_epub_link_teaser');
  variable_del('print_epub_link_use_alias');
  variable_del('print_epub_show_link');
  variable_del('print_epub_sys_link_pages');
  variable_del('print_epub_sys_link_visibility');

  $settings = db_query("SELECT name FROM {variable} WHERE name LIKE 'print\_epub\_display\_%'");
  foreach ($settings as $variable) {
    variable_del($variable->name);
  }
}


/**
 * Implements hook_requirements().
 */
function print_epub_requirements($phase) {
  $requirements = array();
  $t = get_t();
  switch ($phase) {
    // At runtime, make sure that a EPUB generation tool is selected.
    case 'runtime':
      $print_epub_epub_tool = variable_get('print_epub_epub_tool', PRINT_EPUB_EPUB_TOOL_DEFAULT);
      if (empty($print_epub_epub_tool)) {
        $requirements['print_epub_tool'] = array(
          'title' => $t('Printer, email and EPUB versions - EPUB generation library'),
          'value' => $t('No EPUB tool selected'),
          'description' => $t('Please configure it in the !url.', array('!url' => l($t('EPUB settings page'), 'admin/config/user-interface/print/epub'))),
          'severity' => REQUIREMENT_ERROR,
        );
      }
      else {
        $tool = explode('|', $print_epub_epub_tool);

        if (!is_file($tool[1]) || !is_readable($tool[1])) {
          $requirements['print_epub_tool'] = array(
            'title' => $t('Printer, email and EPUB versions - EPUB generation library'),
            'value' => $t('File not found'),
            'description' => $t('The currently selected EPUB generation library (%file) is no longer accessible.', array('%file' => $tool[1])),
            'severity' => REQUIREMENT_ERROR,
          );
        }
      }
      break;
  }
  return $requirements;
}

/**
 * Implements hook_schema().
 */
function print_epub_schema() {
  $schema['print_epub_node_conf'] = array(
    'description' => 'EPUB version node-specific configuration settings',
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

  $schema['print_epub_page_counter'] = array(
    'description' => 'EPUB version access counter',
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
function print_epub_update_7000(&$sandbox) {
  $renamed_deltas = array(
    'print_epub' => array(
      '0' => 'print_epub-top',
    ),
  );

  update_fix_d7_block_deltas($sandbox, $renamed_deltas, array());

  if (variable_get('print_epub_filename', '') == '[site-name] - [title] - [mod-yyyy]-[mod-mm]-[mod-dd]') {
    variable_set('print_epub_filename', '[site:name] - [node:title] - [node:changed:custom:Y-m-d]');
  }
}

/**
 * Enable block and help area links.
 */
function print_epub_update_7202(&$sandbox) {
  $link_pos = variable_get('print_epub_link_pos', drupal_json_decode('{ "link": "link", "block": "block", "help": "help" }'));
  $link_pos['block'] = 'block';
  $link_pos['help'] = 'help';
  variable_set('print_epub_link_pos', $link_pos);
}

/**
 * Increase size of the path field in the print_epub_page_counter table.
 */
function print_epub_update_7203(&$sandbox) {
  db_drop_primary_key('print_epub_page_counter');
  db_change_field('print_epub_page_counter', 'path', 'path',
    array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => TRUE,
      'description' => 'Page path',
    ),
    array('primary key' => array('path')));
}
