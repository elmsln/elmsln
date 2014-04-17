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
  public function getLanguage($machineName, $majorVersion, $minorVersion) {
    global $language;
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
        ':lang' => $language->language,
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
    $id = db_insert('file_managed')
      ->fields(array(
        'uid' => $user->uid,
        'filename' => $filename[count($filename) - 1],
        'uri' => $path,
        'filemime' => $file->type,
        'filesize' => $file->size,
        'status' => ~ FILE_STATUS_PERMANENT,
        'timestamp' => REQUEST_TIME,
      ))
      ->execute();
  }

  /**
   * TODO
   */
  public function keepFile($oldPath, $newPath) {
    // TODO: Add to file usage?
    $path = file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath() . '/';
    db_update('file_managed')
    ->fields(array(
      'uri' => str_replace($path, 'public://', $newPath),
      'status' => FILE_STATUS_PERMANENT,
    ))
    ->condition('uri', str_replace($path, 'public://', $oldPath))
    ->execute();
  }

  /**
   * TODO
   */
  public function removeFile($path) {
    db_delete('file_managed')
    ->condition('uri', $path)
    ->execute();
  }

  /**
   * TODO
   */
  public function getLibraries($libraries = NULL) {
    if ($libraries !== NULL) {
      // Get details for the specified libraries only.
      foreach ($libraries as $library) {
        $details = db_query(
          "SELECT title, runnable 
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
          $library->title = $details->title;
          $library->runnable = $details->runnable;
        }
      }
      
      return $libraries;
    }
    
    $libraries = array();

    $libraries_result = db_query(
      "SELECT machine_name AS machineName, 
              title, 
              major_version as majorVersion, 
              minor_version as minorVersion 
       FROM {h5p_libraries} 
       WHERE runnable = 1 
       AND semantics IS NOT NULL 
       ORDER BY title");
    foreach ($libraries_result as $library) {
      // Make sure we only display the newest version of a library.
      foreach ($libraries as $key => $existingLibrary) {
        if ($library->machineName === $existingLibrary->machineName) {
          
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
      
      // Add new library
      $libraries[] = $library;
    }
    
    return $libraries;
  }
}
