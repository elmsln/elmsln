<?php

// HAX API

/**
 * Implements hook_hax_tool().
 *
 * This allows you to add new tools to the toolbar for use in hax.
 * It requires your returned items to follow a certain structure:
 * - machine_name
 * --- group: group to display in the toolbar
 * --- name: Name for the item
 * --- description: Longer description of what it does
 * --- type: row, column or content
 * --- icon: icon for the button
 * --- action: action to take, insert simply injects markup
 * --- markup: optional, markup to insert
 * @return array  an array of tools for rendering in the hax toolbar
 */
function hook_hax_tool() {
  $tools['hax-core-template-1'] = array(
    'group' => t('Layout'),
    'name' => t('Template 1'),
    'description' => t('A simple layout element with an image'),
    'type' => 'container',
    'icon' => 'https://raw.githubusercontent.com/elmsln/elmsln-logos/master/icons/elmsln-emoji_128.gif',
    'action' => 'insert',
    'markup' => _hax_load_template('hax-core-template1'),
  );
  return $tools;
}

/**
 * Implements hook_hax_tool_alter().
 */
function hook_hax_tool_alter(&$tools) {
  // make changes to all tools you want here
}

/**
 * Implements hook_hax_toolbar_groups_alter()
 */
function hook_hax_toolbar_groups_alter(&$toolbar) {

}

