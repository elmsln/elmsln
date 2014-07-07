<?php
/**
 * @file
 * The hooks that are used by Coffee
 * includes an example of hook_coffee_commands().
 */

/**
 * Implements hook_coffee_commands().
 */
function coffee_coffee_commands() {
  $commands = array();

  // Add in a link for the frontpage.
  $commands[] = array(
    'value' => '',
    'label' => t('Go to front page'),
    'command' => ':front',
  );

  // Display the links of the node/add page.
  // The command is ":add" and includes the link_title to empower the
  // autocompletion.
  $path = 'node/add';
  $item = menu_get_item($path);
  $content_types = system_admin_menu_block($item);

  $command = ':add';
  foreach ($content_types as $content_type) {
    $commands[] = array(
      'value' => $content_type['link_path'],
      'label' => $content_type['link_title'],
      'command' => $command . ' ' . drupal_strtolower($content_type['link_title']),
    );
  }

  return $commands;
}
