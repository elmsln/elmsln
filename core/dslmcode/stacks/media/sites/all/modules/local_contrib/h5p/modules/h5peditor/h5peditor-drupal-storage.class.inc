<?php

/**
 * Handles all communication with the database.
 */
class H5peditorDrupalStorage implements H5peditorStorage {

  /**
   * Empty contructor.
   */
  function __construct() { }

  /**
   * TODO
   */
  public function getLanguage($machineName, $majorVersion, $minorVersion, $languageCode) {
    $lang = db_query(
      "SELECT language_json
      FROM {h5p_libraries_languages} hlt
      JOIN {h5p_libraries} hl ON hl.library_id = hlt.library_id
      WHERE hl.machine_name = :name
      AND hl.major_version = :major
      AND hl.minor_version = :minor
      AND hlt.language_code = :lang",
      array(
        ':name' => $machineName,
        ':major' => $majorVersion,
        ':minor' => $minorVersion,
        ':lang' => $languageCode,
      ))->fetchField();

    return ($lang === FALSE ? NULL : $lang);
  }

  /**
   * TODO
   */
  public function addTmpFile($file) {
    global $user;
    $path = str_replace(file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath() . '/', 'public://', $file->path);
    $filename = explode('/', $file->name);
    $file_managed = (object) array(
      'uid' => $user->uid,
      'filename' => $filename[count($filename) - 1],
      'uri' => $path,
      'filemime' => $file->type,
      'filesize' => $file->size,
      'status' => 0,
      'timestamp' => REQUEST_TIME,
    );
    file_save($file_managed);
  }

  /**
   * TODO
   */
  public function keepFile($oldPath, $newPath) {
    $oldCleanedPath = str_replace(DIRECTORY_SEPARATOR, '/', $oldPath);
    $newCleanedPath = str_replace(DIRECTORY_SEPARATOR, '/', $newPath);
    // TODO: Add to file usage?
    $path = file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath() . '/';
    db_update('file_managed')
    ->fields(array(
      'uri' => str_replace($path, 'public://', $newCleanedPath),
      'status' => FILE_STATUS_PERMANENT,
    ))
    ->condition('uri', str_replace($path, 'public://', $oldCleanedPath))
    ->execute();
  }

  /**
   * Delete file from drupal management.
   * @param string $path Relative path to file
   */
  public function removeFile($path) {

    // Get file from file managed
    $clean_path = str_replace('\\', '/', $path);
    $file_uri = file_build_uri(substr($clean_path, strpos($clean_path, 'h5p/'), strlen($clean_path)));
    $fid = db_query("SELECT fid FROM {file_managed} WHERE uri = :path",
      array(':path' => $file_uri))->fetchField();
    if ($fid !== false) {

      // Delete file and database record
      $file_object = file_load($fid);
      file_delete($file_object);
    }
  }

  /**
   * TODO
   *
   * This does alot of the same as getLibraries in h5p-php-library. Should we just use that instead?
   */
  public function getLibraries($libraries = NULL) {
    $super_user = user_access('create restricted h5p content types');

    if ($libraries !== NULL) {
      // Get details for the specified libraries only.
      $librariesWithDetails = array();
      foreach ($libraries as $library) {
        $details = db_query(
          "SELECT title, runnable, restricted, tutorial_url
           FROM {h5p_libraries}
           WHERE machine_name = :name
           AND major_version = :major
           AND minor_version = :minor
           AND semantics IS NOT NULL",
          array(
            ':name' => $library->name,
            ':major' => $library->majorVersion,
            ':minor' => $library->minorVersion
          ))
          ->fetchObject();
        if ($details !== FALSE) {
          $library->tutorialUrl = $details->tutorial_url;
          $library->title = $details->title;
          $library->runnable = $details->runnable;
          $library->restricted = $super_user ? FALSE : ($details->restricted === '1' ? TRUE : FALSE);
          $librariesWithDetails[] = $library;
        }
      }

      return $librariesWithDetails;
    }

    $libraries = array();

    $libraries_result = db_query(
      "SELECT machine_name AS name,
              title,
              major_version,
              minor_version,
              restricted,
              tutorial_url
       FROM {h5p_libraries}
       WHERE runnable = 1
       AND semantics IS NOT NULL
       ORDER BY title");
    foreach ($libraries_result as $library) {
      // Convert result object properties to camelCase.
      $library = H5PCore::snakeToCamel($library, true);

      // Make sure we only display the newest version of a library.
      foreach ($libraries as $existingLibrary) {
        if ($library->name === $existingLibrary->name) {

          // Mark old ones
          // This is the newest
          if (($library->majorVersion === $existingLibrary->majorVersion && $library->minorVersion > $existingLibrary->minorVersion) ||
              ($library->majorVersion > $existingLibrary->majorVersion)) {
            $existingLibrary->isOld = TRUE;
          }
          else {
            $library->isOld = TRUE;
          }
        }
      }

      $library->restricted = $super_user ? FALSE : ($library->restricted === '1' ? TRUE : FALSE);

      // Add new library
      $libraries[] = $library;
    }

    return $libraries;
  }

  public function alterLibraryFiles(&$files, $libraries) {
    $mode = 'editor';
    $library_list = _h5p_dependencies_to_library_list($libraries);
    drupal_alter('h5p_scripts', $files['scripts'], $library_list, $mode);
    drupal_alter('h5p_styles', $files['styles'], $library_list, $mode);
  }
}
