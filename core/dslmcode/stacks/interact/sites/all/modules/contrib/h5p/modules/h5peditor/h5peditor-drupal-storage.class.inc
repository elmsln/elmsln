<?php

class H5peditorDrupalStorage implements H5peditorStorage {

  function __construct() { }

  public function getSemantics($machineName, $majorVersion, $minorVersion) {
    $coreInterface = _h5p_get_instance('interface');
    return $coreInterface->getLibrarySemantics($machineName, $majorVersion, $minorVersion);
  }

  public function getLanguage($machineName, $majorVersion, $minorVersion) {
    global $language;
    $lang = db_query(
      "SELECT language_json
      FROM {h5p_libraries_languages} hlt
      JOIN {h5p_libraries} hl ON hl.library_id = hlt.library_id
      WHERE hl.machine_name = :hl_machine_name
      AND hl.major_version = :hl_major_version
      AND hl.minor_version = :hl_minor_version
      AND hlt.language_code = :hlt_language_code",
      array(':hl_machine_name' => $machineName, ':hl_major_version' => $majorVersion, ':hl_minor_version' => $minorVersion, ':hlt_language_code' => $language->language))->fetchField();
    return $lang;
  }

  public function getFilePaths($libraryId) {
    $result = db_query(
      "SELECT hl.preloaded_css, hl.preloaded_js, hl.library_id, hl.machine_name as machineName, hl.major_version as majorVersion, hl.minor_version as minorVersion
      FROM {h5p_libraries} hl
      WHERE hl.library_id = :hl_library_id", array(':hl_library_id' => $libraryId));
    $file_paths = array(
      'js' => array(),
      'css' => array(),
    );
    $h5p_path = _h5p_get_h5p_path();
    $h5p_core = _h5p_get_instance('core');
    while ($paths = $result->fetchAssoc()) {
      if (!empty($paths['preloaded_js'])) {
        foreach (explode(',', $paths['preloaded_js']) as $js_path) {
          $file_paths['js'][] = $h5p_path . '/libraries/' . $h5p_core->libraryToString($paths, TRUE) . '/' . trim($js_path);
        }
      }
      if (!empty($paths['preloaded_css'])) {
        foreach (explode(',', $paths['preloaded_css']) as $css_path) {
          $file_paths['css'][] = $h5p_path . '/libraries/' . $h5p_core->libraryToString($paths, TRUE) . '/' . trim($css_path);
        }
      }
    }
    return $file_paths;
  }

  public function addTempFile($file) {
    global $user;
    $path = str_replace(file_stream_wrapper_get_instance_by_uri('public://')->realpath(), 'public://', $file->path);
    $id = db_insert('file_managed')
    ->fields(array(
      'uid' => $user->uid,
      'filename' => $file->name,
      'uri' => $path,
      'filemime' => $file->type,
      'filesize' => $file->size,
      'status' => ~ FILE_STATUS_PERMANENT,
      'timestamp' => REQUEST_TIME,
    ))
    ->execute();
  }

  public function keepFile($oldPath, $newPath) {
    db_update('file_managed')
    ->fields(array(
      'uri' => str_replace(file_stream_wrapper_get_instance_by_uri('public://')->realpath(), 'public://', $newPath),
      'status' => FILE_STATUS_PERMANENT,
    ))
    ->condition('uri', str_replace(file_stream_wrapper_get_instance_by_uri('public://')->realpath(), 'public://', $oldPath))
    ->execute();
  }

  public function removeFile($path) {
    db_delete('file_managed')
    ->condition('uri', $path)
    ->execute();
  }


  public function getLibraries() {
    $libraries = array();

    if (isset($_POST['libraries'])) {
      // Get details for the specified libraries.
      foreach ($_POST['libraries'] as $libraryName) {
        $matches = array();
        preg_match_all('/(.+)\s(\d)+\.(\d)$/', $libraryName, $matches);
        if ($matches) {
          $library = db_query(
            "SELECT machine_name AS name, title, major_version as majorVersion, minor_version as minorVersion, runnable
            FROM {h5p_libraries}
            WHERE machine_name = :machine_name
            AND major_version = :major_version
            AND minor_version = :minor_version
            AND semantics IS NOT NULL",
            array(':machine_name' => $matches[1][0], ':major_version' => $matches[2][0], ':minor_version' => $matches[3][0]))
            ->fetch();
          if ($library) {
            $library->uberName = $libraryName;
            $libraries[] = $library;
          }
        }
      }
    }
    else {
      // Get some books from the library.
      $libraries_result = db_query(
        "SELECT machine_name AS machineName, title, major_version as majorVersion, minor_version as minorVersion
        FROM {h5p_libraries}
        WHERE runnable = :runnable AND semantics IS NOT NULL",
        array(':runnable' => 1));
      foreach ($libraries_result as $library) {
        $libraries[] = $library;
      }
    }

    return json_encode($libraries);
  }
  
  public function getEditorLibraries($machineName, $majorVersion, $minorVersion) {
    $i = _h5p_get_instance('interface');
    // Just pipe trough. Tmp hack until H5PEditor class has an instance of H5P class.
    return $i->getEditorLibraries($machineName, $majorVersion, $minorVersion);
  }
}
