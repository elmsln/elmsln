<?php

/**
 * @file
 * Logic for advanced mode ("File Conveyor mode" in the UI).
 */


//----------------------------------------------------------------------------
// Public functions.

/**
 * Gets the servers on which a file is available when advanced mode is enabled.
 *
 * @param $path
 *   The path to get the servers for.
 */
function cdn_advanced_get_servers($path) {
  static $absolute_path_prefix;

  if (!isset($absolute_path_prefix)) {
    $absolute_path_prefix = realpath('.');
  }

  $db = _cdn_advanced_get_db_connection();

  // In case no connection to the database could be made, pretend the file was
  // not found in the synced files database.
  if (!$db) {
    return array();
  }

  // Get the real path to the file.
  // TRICKY: we used to do this here:
  //   $input_file = realpath('./' . $path);
  // But this fails when a file has been deleted by File Conveyor. This new
  // approach only works when no symbolic links are used.
  $input_file = $absolute_path_prefix . '/' . $path;

  // Retrieve the URLs of the file on the CDN.
  $sql = "SELECT url, server
          FROM synced_files
          WHERE input_file = :input_file";
  $stmt = $db->prepare($sql);
  $stmt->bindParam(':input_file', $input_file, PDO::PARAM_STR);
  $stmt->execute();
  $servers = $stmt->fetchAll(PDO::FETCH_ASSOC);

  return $servers;
}


//----------------------------------------------------------------------------
// Private functions.

/**
 * Get a connection to the database.
 *
 * @return
 *   A database connection (through PDO), or FALSE in case of failure.
 */
function _cdn_advanced_get_db_connection() {
  static $db;

  $synced_files_db = variable_get(CDN_ADVANCED_SYNCED_FILES_DB_VARIABLE, FALSE);

  if ($synced_files_db === FALSE || !file_exists($synced_files_db) || filesize($synced_files_db) == 0) {
    $db = FALSE;
  }
  elseif (!isset($db)) {
    try {
      $db = new PDO('sqlite:' . variable_get(CDN_ADVANCED_SYNCED_FILES_DB_VARIABLE, ''));
    } catch (PDOException $e) {
      watchdog('cdn', "Could not open synced files DB: %error.", array('%error' => $e));
      $db = FALSE;
    }
  }

  return $db;
}
