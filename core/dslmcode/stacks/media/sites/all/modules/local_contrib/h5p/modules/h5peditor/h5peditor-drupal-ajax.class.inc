<?php

/**
 * Handles Ajax functions that must be implemented separately for each of the
 * H5P plugins
 */
class H5PEditorDrupalAjax implements H5PEditorAjaxInterface {

  /**
   * Gets latest library versions that exists locally
   *
   * @return array Latest version of all local libraries
   */
  public function getLatestLibraryVersions() {

    // Retrieve latest major version
    $max_major_version = "
      SELECT hl.machine_name, max(hl.major_version) AS major_version
      FROM {h5p_libraries} hl
      WHERE hl.runnable = 1
      GROUP BY hl.machine_name
    ";

    // Find latest minor version among the latest major versions
    $max_minor_version = "
      SELECT hl2.machine_name, hl2.major_version, max(hl2.minor_version) AS minor_version
      FROM ({$max_major_version}) hl1
      JOIN {h5p_libraries} hl2
      ON hl1.machine_name = hl2.machine_name
      AND hl1.major_version = hl2.major_version
      GROUP BY hl2.machine_name, hl2.major_version
    ";

    // Find latest patch version among the rows with latest major and minor version
    $local_libraries = db_query("
      SELECT hl4.library_id as id, hl4.machine_name, hl4.title, hl4.major_version,
        hl4.minor_version, hl4.patch_version, hl4.has_icon, hl4.restricted
      FROM {h5p_libraries} hl4
      JOIN ({$max_minor_version}) hl3
      ON hl4.machine_name = hl3.machine_name
      AND hl4.major_version = hl3.major_version
      AND hl4.minor_version = hl3.minor_version
    ")->fetchAll();

    return $local_libraries;
  }

  /**
   * Get locally stored Content Type Cache. If machine name is provided
   * it will only get the given content type from the cache
   *
   * @param $machineName
   *
   * @return array|object|null Returns results from querying the database
   */
  public function getContentTypeCache($machineName = NULL) {

    // Get only the specified content type from cache
    if ($machineName !== NULL) {
      return db_query(
        "SELECT id, is_recommended
         FROM {h5p_libraries_hub_cache}
        WHERE machine_name = :name",
        array(':name' => $machineName)
      )->fetchObject();
    }

    // Get all cached content types
    return db_query("SELECT * FROM {h5p_libraries_hub_cache}")->fetchAll();
  }

  /**
   * Create a list of the recently used libraries
   *
   * @return array machine names. The first element in the array is the most
   * recently used.
   */
  public function getAuthorsRecentlyUsedLibraries() {
    global $user;
    $recently_used = array();

    // Get recently used:
    $result = db_query("
      SELECT library_name, max(created_at) AS max_created_at
      FROM {h5p_events}
      WHERE type='content' AND sub_type = 'create' AND user_id = :uid
      GROUP BY library_name
      ORDER BY max_created_at DESC
    ", array(':uid' => $user->uid));

    foreach ($result as $row) {
      $recently_used[] = $row->library_name;
    }

    return $recently_used;
  }

  /**
   * Checks if the provided token is valid for this endpoint
   *
   * @param string $token The token that will be validated for.
   *
   * @return bool True if successful validation
   */
  public function validateEditorToken($token) {
    return H5PCore::validToken('editorajax', $token);
  }
}
