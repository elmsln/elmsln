<?php

/**
 * @file
 * Documentation for Menu Attributes API.
 */

/**
 * Inform the menu_attributes module about custom attributes.
 *
 * @return
 *   An array of attributes to be controlled by Menu Attributes, keyed by
 *   attribute name. Each attribute record should be an array with the following
 *   key/value pairs:
 *   - label: The human-readable name of the attribute.
 *   - description: The attribute description for the link.
 *   - item_description: The attribute description for the item.
 *   - form: A Form API array. Some default values for this array are provided
 *     in menu_attributes_get_menu_attribute_info().
 *   - scope: An array of scope options, MENU_ATTRIBUTES_LINK or
 *     MENU_ATTRIBUTES_ITEM or both. If no scope is provided, both will
 *     be assumed.
 *
 * @see menu_attributes_menu_attribute_info()
 * @see menu_attributes_get_menu_attribute_info()
 */
function hook_menu_attribute_info() {
  // Add a Tabindex attribute.
  $info['tabindex'] = array(
    'label' => t('Tabindex'),
    'description' => t('Specifies the tab order for the link.'),
    'item_description' => t('Specifies the tab order for the item.'),
    'form' => array(
      '#maxlength' => 3,
      '#size' => 2,
    ),
    'scope' => array(MENU_ATTRIBUTES_LINK),
  );

  return $info;
}

/**
 * Alter the list of menu item attributes.
 *
 * @param $attributes
 *   An array of attributes to be controlled by Menu Attributes, keyed by
 *   attribute name.
 *
 * @see hook_menu_attribute_info()
 * @see menu_attributes_get_menu_attribute_info()
 */
function hook_menu_attribute_info_alter(array &$attributes) {
  // Remove the Access Key attribute.
  unset($attributes['accesskey']);
}
