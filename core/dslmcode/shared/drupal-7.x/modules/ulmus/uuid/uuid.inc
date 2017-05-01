<?php

/**
 * @file
 * Handling of universally unique identifiers.
 */

/**
 * Pattern for detecting a valid UUID.
 */
define('UUID_PATTERN', '[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}');

/**
 * Generates an universally unique identifier.
 *
 * This function first checks for the PECL alternative for generating
 * universally unique identifiers. If that doesn't exist, then it falls back on
 * PHP for generating that.
 *
 * @return string
 *   An UUID, made up of 32 hex digits and 4 hyphens.
 */
function uuid_generate() {
  $callback = drupal_static(__FUNCTION__);

  if (empty($callback)) {
    if (function_exists('uuid_create') && !function_exists('uuid_make')) {
      $callback = '_uuid_generate_pecl';
    }
    elseif (function_exists('com_create_guid')) {
      $callback = '_uuid_generate_com';
    }
    else {
      $callback = '_uuid_generate_php';
    }
  }
  return $callback();
}

/**
 * Generates a version 5 compliant UUID.
 *
 * @param string $namespace
 *   Namespace UUID as a hex encoded string.
 * @param string $name
 *   The name for the generating the UUID.
 *
 * @return string
 *   UUID as a hex encoded string.
 *
 * @link http://www.php.net/manual/en/function.uniqid.php#94959 Code lifted from
 * PHP manual comment by Andrew Moore. @endlink
 */
function uuid_generate_v5($namespace, $name) {
  if (!uuid_is_valid($namespace)) {
    return FALSE;
  }

  // Get hexadecimal components of namespace.
  $nhex = str_replace(array('-', '{', '}'), '', $namespace);

  // Binary Value.
  $nstr = '';

  // Convert Namespace UUID to bits.
  for ($i = 0; $i < strlen($nhex); $i += 2) {
    $nstr .= chr(hexdec($nhex[$i] . $nhex[$i + 1]));
  }

  // Calculate hash value.
  $hash = sha1($nstr . $name);

  return sprintf('%08s-%04s-%04x-%04x-%12s',

    // 32 bits for "time_low".
    substr($hash, 0, 8),

    // 16 bits for "time_mid".
    substr($hash, 8, 4),

    // 16 bits for "time_hi_and_version",
    // four most significant bits holds version number 5.
    (hexdec(substr($hash, 12, 4)) & 0x0fff) | 0x5000,

    // 16 bits, 8 bits for "clk_seq_hi_res",
    // 8 bits for "clk_seq_low",
    // two most significant bits holds zero and one for variant DCE1.1.
    (hexdec(substr($hash, 16, 4)) & 0x3fff) | 0x8000,

    // 48 bits for "node".
    substr($hash, 20, 12)
  );
}

/**
 * Generate all missing UUIDs.
 */
function uuid_sync_all() {
  module_invoke_all('uuid_sync');
}

/**
 * Generates a UUID URI for an entity.
 *
 * @param object $entity
 *   The entity to use for generating the UUID URI.
 * @param string $entity_type
 *   The type of entity being used.
 *
 * @return string
 *   The generated UUID URI or normal URI if entity doesn't support UUIDs.
 */
function uuid_entity_uuid_uri($entity, $entity_type) {
  $entity_info = entity_get_info($entity_type);

  if (empty($entity_info['uuid'])) {
    $uri = $entity_info['uri callback']($entity);
    return $uri['path'];
  }

  if (isset($entity_info['uuid uri callback'])) {
    return $entity_info['uuid uri callback']($entity);
  }

  return "uuid/{$entity_type}/" . $entity->{$entity_info['entity keys']['uuid']};
}

/**
 * Converts an ID URI string to an entity data array.
 *
 * @param string $uri
 *   The URI to convert.
 *
 * @return array
 *   The entity data.
 *
 * @see uuid_id_uri_array_to_data()
 */
function uuid_id_uri_to_data($uri) {
  $parts = explode('/', $uri);
  return uuid_id_uri_array_to_data($parts);
}

/**
 * Converts a URI array to entity data array.
 *
 * @param array $uri
 *   The URI parts, often taken from arg().
 *
 * @return array
 *   The entity data.
 */
function uuid_id_uri_array_to_data($uri) {
  $data = array(
    'request' => $uri,
    'entity_type' => $uri[0],
    'id' => $uri[1],
  );

  drupal_alter('uuid_id_uri_data', $data);

  return $data;
}

/**
 * Converts a UUID URI string to an entity data array.
 *
 * @param string $uri
 *   The URI to convert.
 *
 * @return array
 *   The entity data.
 *
 * @see uuid_uri_array_to_data()
 */
function uuid_uri_to_data($uri, $strip_uuid = TRUE) {
  return uuid_uri_array_to_data(explode('/', $uri));
}

/**
 * Converts a URI array to entity data array.
 *
 * @param array $uri
 *   The URI parts, often taken from arg().
 *
 * @return array
 *   The entity data.
 */
function uuid_uri_array_to_data($uri, $strip_uuid = TRUE) {
  if ($strip_uuid) {
    array_shift($uri);
  }

  $data = array(
    'request' => $uri,
    'entity_type' => isset($uri[0]) ? $uri[0] : NULL,
    'uuid' => isset($uri[1]) ? $uri[1] : NULL,
  );

  drupal_alter('uuid_uri_data', $data);

  return $data;
}

/**
 * Generates a UUID using the Windows internal GUID generator.
 *
 * @see http://php.net/com_create_guid
 */
function _uuid_generate_com() {
  // Remove {} wrapper and make lower case to keep result consistent.
  return drupal_strtolower(trim(com_create_guid(), '{}'));
}

/**
 * Generates an universally unique identifier using the PECL extension.
 */
function _uuid_generate_pecl() {
  return uuid_create(UUID_TYPE_DEFAULT);
}

/**
 * Generates a UUID v4 (RFC 4122 section 4.4) using PHP code.
 *
 * @see http://www.rfc-editor.org/rfc/rfc4122.txt
 *
 * The UUID layout and fields are defined in section 4.1.2.
 *
 * Note that there are inconsistencies in the RFC with respect to
 * bit numbering. Network Order is correct, so the most significant bit
 * always appears first (in left-to-right sequence). See errata 3546:
 * http://www.rfc-editor.org/errata_search.php?rfc=4122&eid=3546
 *
 * Based on code from http://php.net/uniqid
 */
function _uuid_generate_php() {
  // We limit each generated number to 16 bits (maximum value 0xffff)
  // because mt_rand() returns a *signed* integer, and hence a 32-bit
  // value can only have a 31-bit magnitude. Constructing a 32-bit
  // number from two 16-bit random numbers guarantees that all 32 bits
  // are random.
  return sprintf('%04x%04x-%04x-4%03x-%04x-%04x%04x%04x',
    // 32 bits for "time_low".
    mt_rand(0, 0xffff), mt_rand(0, 0xffff),
    // 16 bits for "time_mid".
    mt_rand(0, 0xffff),
    // 12 bits after the initial 0100 (version 4) for "time_hi_and_version".
    mt_rand(0, 0x0fff),
    // 16 bits in total for "clk_seq_hi_res" and "clk_seq_low", with the
    // most significant 2 bits of clk_seq_hi_res set to '10'. We do a
    // bitwise OR of a random 14-bit value (maximum 0x3fff) with 0x8000
    // (a 16-bit integer with only the most significant bit set).
    mt_rand(0, 0x3fff) | 0x8000,
    // 48 bits for "node".
    mt_rand(0, 0xffff), mt_rand(0, 0xffff), mt_rand(0, 0xffff)
  );
}

// The if block avoids conflicts with PECL's uuid_is_valid().
if (!function_exists('uuid_is_valid')) {

  /**
   * Check that a string appears to be in the format of a UUID.
   *
   * @param string $uuid
   *   The string to test.
   *
   * @return bool
   *    TRUE if the string is well formed.
   */
  function uuid_is_valid($uuid) {
    return preg_match('/^' . UUID_PATTERN . '$/', $uuid);
  }

}
