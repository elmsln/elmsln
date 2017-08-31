<?php

/**
 * Handles all communication with the database.
 */
class H5peditorDrupalStorage implements H5peditorStorage {

  /**
   * Load language file(JSON) from database.
   * This is used to translate the editor fields(title, description etc.)
   *
   * @param string $machineName The machine readable name of the library(content type)
   * @param int $majorVersion Major part of version number
   * @param int $minorVersion Minor part of version number
   * @param string $languageCode Language code
   * @return string Translation in JSON format
   */
  public function getLanguage($machineName, $majorVersion, $minorVersion, $languageCode) {
    $lang = db_query(
        "SELECT language_json
           FROM {h5p_libraries_languages} hlt
           JOIN {h5p_libraries} hl
             ON hl.library_id = hlt.library_id
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
   * "Callback" for mark the given file as a permanent file.
   * Used when saving content that has new uploaded files.
   *
   * @param string $path To new file
   */
  public function keepFile($path) {
    // Find URI
    $uri = str_replace(file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath() . '/', 'public://', $path);

    // No longer mark the file as a tmp file
    db_delete('file_managed')->condition('uri', $uri)->execute();
  }

  /**
   * Decides which content types the editor should have.
   *
   * Two usecases:
   * 1. No input, will list all the available content types.
   * 2. Libraries supported are specified, load additional data and verify
   * that the content types are available. Used by e.g. the Presentation Tool
   * Editor that already knows which content types are supported in its
   * slides.
   *
   * @param array $libraries List of library names + version to load info for
   * @return array List of all libraries loaded
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
           AND semantics IS NOT NULL", // TODO: Consider if semantics is really needed (DB performance-wise)
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
       ORDER BY title"); // TODO: Consider if semantics is really needed (DB performance-wise)
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

  /**
   * Allow for other plugins to decide which styles and scripts are attached.
   * This is useful for adding and/or modifing the functionality and look of
   * the content types.
   *
   * @param array $files
   *  List of files as objects with path and version as properties
   * @param array $libraries
   *  List of libraries indexed by machineName with objects as values. The objects
   *  have majorVersion and minorVersion as properties.
   */
  public function alterLibraryFiles(&$files, $libraries) {
    $mode = 'editor';
    $library_list = _h5p_dependencies_to_library_list($libraries);
    drupal_alter('h5p_scripts', $files['scripts'], $library_list, $mode);
    drupal_alter('h5p_styles', $files['styles'], $library_list, $mode);
  }

  /**
   * Saves a file temporarily with a given name
   *
   * @param $data
   * @param $move_file Only move the uploaded file
   *
   * @return bool|false|string Real absolute path of the temporary folder
   */
  public static function saveFileTemporarily($data, $move_file = FALSE) {
    $temp_id = uniqid('h5p-');
    $temporary_file_path = 'public://' . variable_get('h5p_default_path', 'h5p') . '/temp/' . $temp_id;
    file_prepare_directory($temporary_file_path, FILE_CREATE_DIRECTORY);
    $name = $temp_id . '.h5p';
    $target = $temporary_file_path . DIRECTORY_SEPARATOR . $name;
    if ($move_file) {
      $file = move_uploaded_file($data, $target);
    }
    else {
      $file = file_unmanaged_save_data($data, $target);
    }
    if (!$file) {
      return FALSE;
    }

    // Set session variables necessary for finding the files
    $_SESSION['h5p_upload_folder'] = drupal_realpath($temporary_file_path);
    $_SESSION['h5p_upload'] = drupal_realpath($target);

    return (object) array(
      'dir' => drupal_realpath($temporary_file_path),
      'fileName' => $name
    );
  }

  /**
   * Marks a file for later cleanup, useful when files are not instantly cleaned
   * up. E.g. for files that are uploaded through the editor.
   *
   * @param H5peditorFile $file
   * @param $contentId
   */
  public static function markFileForCleanup($file, $content_id = null) {
    // Determine URI
    $uri = 'public://';
    $file_type = $file->getType();
    $file_name = $file->getName();
    if ($content_id) {
      $h5pPath = variable_get('h5p_default_path', 'h5p');
      $uri .= "{$h5pPath}/content/{$content_id}/{$file_type}s/{$file_name}";
    }
    else {
      $uri .= "h5peditor/{$file_type}s/{$file_name}";
    }

    global $user;

    // Keep track of temporary files so they can be cleaned up later by Drupal
    $file_managed = (object) array(
      'uid' => $user->uid,
      'filename' => $file->getName(),
      'uri' => $uri,
      'filemime' => $file->type,
      'filesize' => $file->size,
      'status' => 0,
      'timestamp' => REQUEST_TIME,
    );
    file_save($file_managed);
  }

  /**
   * Clean up temporary files
   *
   * @param string $filePath Path to file or directory
   */
  public static function removeTemporarilySavedFiles($filePath) {
    if (is_dir($filePath)) {
      H5PCore::deleteFileTree($filePath);
    }
    else {
      unlink($filePath);
    }
    // Maintain session variables
    unset($_SESSION['h5p_upload'], $_SESSION['h5p_upload_folder']);
  }
}
