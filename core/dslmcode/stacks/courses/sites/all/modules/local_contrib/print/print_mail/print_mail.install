<?php

/**
 * @file
 * Install, update and uninstall functions for the print_mail module.
 *
 * @ingroup print
 */

/**
 * Implements hook_enable().
 */
function print_mail_enable() {
  // Module weight.
  db_update('system')
    ->fields(array(
      'weight' => 1,
    ))
    ->condition('type', 'module')
    ->condition('name', 'print_mail')
    ->execute();

  if (module_exists('mailsystem')) {
    mailsystem_set(array('print_mail' => 'DefaultMailSystem'));
  }
}

/**
 * Implements hook_requirements().
 */
function print_mail_requirements($phase) {
  $requirements = array();
  $t = get_t();
  switch ($phase) {
    // At runtime, make sure that a PDF generation tool is selected.
    case 'runtime':
      if (module_exists('mailsystem')) {
        $mail_system = mailsystem_get();
        if (($mail_system['default-system'] != 'DefaultMailSystem') && (!isset($mail_system['print_mail']) || ($mail_system['print_mail'] != 'DefaultMailSystem'))) {
          $requirements['print_mail_mailsystem'] = array(
            'title' => $t('Printer, email and PDF versions - Send by email'),
            'value' => $t('Incompatible Mail System setting detected'),
            'description' => $t('The send by email module requires the use of the DefaultMailSystem, please configure it in the !url.', array('!url' => l($t('Mail System Settings page'), 'admin/config/system/mailsystem'))),
            'severity' => REQUIREMENT_WARNING,
          );
        }
      }
  }

  return $requirements;
}

/**
 * Implements hook_disable().
 */
function print_mail_disable() {
  if (module_exists('mailsystem')) {
    mailsystem_clear(array('print_mail' => ''));
  }
}

/**
 * Implements hook_uninstall().
 */
function print_mail_uninstall() {
  variable_del('print_mail_display_sys_urllist');
  variable_del('print_mail_hourly_threshold');
  variable_del('print_mail_job_queue');
  variable_del('print_mail_link_text');
  variable_del('print_mail_link_text_enabled');
  variable_del('print_mail_send_option_default');
  variable_del('print_mail_teaser_choice');
  variable_del('print_mail_teaser_default');
  variable_del('print_mail_use_reply_to');
  variable_del('print_mail_user_recipients');

  variable_del('print_mail_book_link');
  variable_del('print_mail_link_class');
  variable_del('print_mail_link_pos');
  variable_del('print_mail_link_teaser');
  variable_del('print_mail_link_use_alias');
  variable_del('print_mail_show_link');
  variable_del('print_mail_sys_link_pages');
  variable_del('print_mail_sys_link_visibility');

  $settings = db_query("SELECT name FROM {variable} WHERE name LIKE 'print\_mail\_display\_%'");
  foreach ($settings as $variable) {
    variable_del($variable->name);
  }
}

/**
 * Implements hook_schema().
 */
function print_mail_schema() {
  $schema['print_mail_node_conf'] = array(
    'description' => 'Send by email node-specific configuration settings',
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

  $schema['print_mail_page_counter'] = array(
    'description' => 'Send by email version access counter',
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
      'sentcount' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 0,
        'size' => 'big',
        'description' => 'Number of sent emails',
      ),
      'sent_timestamp' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 0,
        'description' => 'Last email sent',
      ),
    ),
    'primary key' => array('path'),
  );

  return $schema;
}

/**
 * Remove hardcoded numeric deltas from all blocks.
 */
function print_mail_update_7000(&$sandbox) {
  $renamed_deltas = array(
    'print_mail' => array(
      '0' => 'print_mail-top',
    ),
  );

  update_fix_d7_block_deltas($sandbox, $renamed_deltas, array());
}

/**
 * Disable MimeMailSystem for now.
 */
function print_mail_update_7100(&$sandbox) {
  if (module_exists('mailsystem')) {
    mailsystem_set(array('print_mail' => 'DefaultMailSystem'));
  }
}

/**
 * Update permissions to new spellings.
 */
function print_mail_update_7101(&$sandbox) {
  db_update('role_permission')
    ->fields(array('permission' => 'access send by email'))
    ->condition('permission', 'access send to friend')
    ->execute();
  db_update('role_permission')
    ->fields(array('permission' => 'send unlimited emails'))
    ->condition('permission', 'send unlimited e-mails')
    ->execute();
}

/**
 * Delete old variables.
 */
function print_mail_update_7200(&$sandbox) {
  variable_del('print_mail_settings');

  variable_del('print_mail_node_link_pages');
  variable_del('print_mail_node_link_visibility');

  variable_del('print_mail_text_title');
  variable_del('print_mail_text_confirmation');
  variable_del('print_mail_text_message');
  variable_del('print_mail_text_subject');
  variable_del('print_mail_text_content');
}

/**
 * Enable block and help area links.
 */
function print_mail_update_7202(&$sandbox) {
  $link_pos = variable_get('print_mail_link_pos', drupal_json_decode('{ "link": "link", "block": "block", "help": "help" }'));
  $link_pos['block'] = 'block';
  $link_pos['help'] = 'help';
  variable_set('print_mail_link_pos', $link_pos);
}

/**
 * Increase size of the path field in the print_mail_page_counter table.
 */
function print_mail_update_7203(&$sandbox) {
  db_drop_primary_key('print_mail_page_counter');
  db_change_field('print_mail_page_counter', 'path', 'path',
    array(
      'type' => 'varchar',
      'length' => 255,
      'not null' => TRUE,
      'description' => 'Page path',
    ),
    array('primary key' => array('path')));
}
