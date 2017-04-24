<?php
/**
 * @file
 * API hooks exposed by the Authcache Enum module.
 */

/**
 * Return information about keys for anonymous users.
 *
 * @return array
 *   A list of all possible keys for anonymous users.
 */
function hook_authcache_enum_anonymous_keys() {
  global $base_root;

  return variable_get('authcache_key_generator_keys', $base_root);
}

/**
 * Modify the list of keys for anonymous users.
 */
function hook_authcache_enum_anonymous_keys_alter(&$keys) {
}

/**
 * Return information about key properties.
 *
 * This hook is kept for backwards compatibility reasons, but will be removed
 * in the future. Use hook_authcache_enum_key_property_info() instead.
 *
 * @deprecated
 * @see hook_authcache_enum_key_property_info()
 */
function hook_authcache_enum_key_properties() {
}

/**
 * Return information about key properties.
 *
 * @return array
 *   An associative array of key-value pairs. Where keys are the names of
 *   key properties and values are associative arrays of the following
 *   structure:
 *   - name: The translated human readable property name
 *   - choices: An array of all possible values for this property
 *
 * @see hook_authcache_enum_key_property_info_alter()
 */
function hook_authcache_enum_key_property_info() {
  return array(
    'js' => array(
      'name' => t('Browser supports JavaScript'),
      'choices' => array(TRUE, FALSE),
    ),
  );
}

/**
 * Modify the key properties used for authcache key enumeration.
 *
 * @see hook_authcache_enum_key_property_info().
 */
function hook_authcache_enum_key_property_info_alter(&$property_info) {
}

/**
 * Modify available keys and property records.
 *
 * @param array &$properties
 *   An associative array where keys correspond to authcache keys and values
 *   represent the property record the key is derived from.
 */
function hook_authcache_enum_key_properties_alter(&$properties) {
}
