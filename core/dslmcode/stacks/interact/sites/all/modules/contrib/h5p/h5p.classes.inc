<?php

class H5PDrupal implements H5PFrameworkInterface {
  /**
   * Implements setErrorMessage
   */
  public function setErrorMessage($message) {
    if (user_access('create h5p_content content')) {
      drupal_set_message($message, 'error');
    }
  }

  /**
   * Implements setInfoMessage
   */
  public function setInfoMessage($message) {
    if (user_access('create h5p_content content')) {
      drupal_set_message($message);
    }
  }

  /**
   * Implements t
   */
  public function t($message, $replacements = array()) {
    return t($message, $replacements);
  }

  /**
   * Implements getH5PPath
   */
  public function getH5pPath() {
    return _h5p_get_h5p_path();
  }

  /**
   * Implements getUploadedH5PFolderPath
   */
  public function getUploadedH5pFolderPath() {
    return $_SESSION['h5p_upload_folder'];
  }

  /**
   * Implements getUploadedH5PPath
   */
  public function getUploadedH5pPath() {
    return $_SESSION['h5p_upload'];
  }

  /**
   * Implements getLibraryId
   */
  public function getLibraryId($machineName, $majorVersion, $minorVersion) {
    $library_id = db_query(
      "SELECT library_id
      FROM {h5p_libraries}
      WHERE machine_name = :machine_name
      AND major_version = :major_version
      AND minor_version = :minor_version",
      array(':machine_name' => $machineName, ':major_version' => $majorVersion, ':minor_version' => $minorVersion))
      ->fetchField();
    return $library_id;
  }

  /**
   * Implements isPatchedLibrary
   */
  public function isPatchedLibrary($library) {
    $operator = $this->isInDevMode() ? '<=' : '<';
    $result = db_query(
      "SELECT 1
      FROM {h5p_libraries}
      WHERE machine_name = :machineName
      AND major_version = :majorVersion
      AND minor_version = :minorVersion
      AND patch_version $operator :patchVersion",
      array(
        ':machineName' => $library['machineName'],
        ':majorVersion' => $library['majorVersion'],
        ':minorVersion' => $library['minorVersion'],
        ':patchVersion' => $library['patchVersion']
      )
    )->fetchField();
    return $result === '1';
  }

  /**
   * Implements isInDevMode
   */
  public function isInDevMode() {
    return (bool) variable_get('h5p_dev_mode', '0');
  }

  /**
   * Implements mayUpdateLibraries
   */
  public function mayUpdateLibraries() {
    return user_access('update h5p libraries');
  }

  /**
   * Implements saveLibraryData
   */
  public function saveLibraryData(&$libraryData, $new = TRUE) {
    $preloadedJs = $this->pathsToCsv($libraryData, 'preloadedJs');
    $preloadedCss =  $this->pathsToCsv($libraryData, 'preloadedCss');
    $dropLibraryCss = '';

    if (isset($libraryData['dropLibraryCss'])) {
      $libs = array();
      foreach ($libraryData['dropLibraryCss'] as $lib) {
        $libs[] = $lib['machineName'];
      }
      $dropLibraryCss = implode(', ', $libs);
    }

    $embedTypes = '';
    if (isset($libraryData['embedTypes'])) {
      $embedTypes = implode(', ', $libraryData['embedTypes']);
    }
    if (!isset($libraryData['semantics'])) {
      $libraryData['semantics'] = '';
    }
    if (!isset($libraryData['fullscreen'])) {
      $libraryData['fullscreen'] = 0;
    }
    if ($new) {
      $libraryId = db_insert('h5p_libraries')
      ->fields(array(
        'machine_name' => $libraryData['machineName'],
        'title' => $libraryData['title'],
        'major_version' => $libraryData['majorVersion'],
        'minor_version' => $libraryData['minorVersion'],
        'patch_version' => $libraryData['patchVersion'],
        'runnable' => $libraryData['runnable'],
        'fullscreen' => $libraryData['fullscreen'],
        'embed_types' => $embedTypes,
        'preloaded_js' => $preloadedJs,
        'preloaded_css' => $preloadedCss,
        'drop_library_css' => $dropLibraryCss,
        'semantics' => $libraryData['semantics'],
      ))
      ->execute();
      $libraryData['libraryId'] = $libraryId;
    }
    else {
      db_update('h5p_libraries')
      ->fields(array(
        'title' => $libraryData['title'],
        'patch_version' => $libraryData['patchVersion'],
        'runnable' => $libraryData['runnable'],
        'fullscreen' => $libraryData['fullscreen'],
        'embed_types' => $embedTypes,
        'preloaded_js' => $preloadedJs,
        'preloaded_css' => $preloadedCss,
        'drop_library_css' => $dropLibraryCss,
        'semantics' => $libraryData['semantics'],
      ))
      ->condition('library_id', $libraryData['libraryId'])
      ->execute();
      $this->deleteLibraryDependencies($libraryData['libraryId']);
    }
    db_delete('h5p_libraries_languages')
    ->condition('library_id', $libraryData['libraryId'])
    ->execute();
    if (isset($libraryData['language'])) {
      foreach ($libraryData['language'] as $languageCode => $languageJson) {
        $id = db_insert('h5p_libraries_languages')
        ->fields(array(
          'library_id' => $libraryData['libraryId'],
          'language_code' => $languageCode,
          'language_json' => $languageJson,
        ))
        ->execute();
      }
    }
  }

  /**
   * Convert list of file paths to csv
   *
   * @param array $libraryData
   *  Library data as found in library.json files
   * @param string $key
   *  Key that should be found in $libraryData
   * @return string
   *  file paths separated by ', '
   */
  private function pathsToCsv($libraryData, $key) {
    if (isset($libraryData[$key])) {
      $paths = array();
      foreach ($libraryData[$key] as $file) {
        $paths[] = $file['path'];
      }
      return implode(', ', $paths);
    }
    return '';
  }

  /**
   * Implements deleteLibraryDependencies
   */
  public function deleteLibraryDependencies($libraryId) {
    db_delete('h5p_libraries_libraries')
    ->condition('library_id', $libraryId)
    ->execute();
  }

  /**
   * Implements saveLibraryDependencies
   */
  public function saveLibraryDependencies($libraryId, $dependencies, $dependency_type) {
    foreach ($dependencies as $dependency) {
      $query = db_select('h5p_libraries', 'hl');
      $query->addExpression($libraryId);
      $query->addField('hl', 'library_id');
      $query->addExpression("'" . $dependency_type . "'");
      $query->condition('machine_name', $dependency['machineName']);
      $query->condition('major_version', $dependency['majorVersion']);
      $query->condition('minor_version', $dependency['minorVersion']);
      
      db_insert('h5p_libraries_libraries')
        /*
         * TODO: The order of the required_library_id and library_id below is reversed,
         * to match the order of the fields in the select statement. We should rather
         * try to control the order of the fields in the select statement or something.
         */
        ->fields(array('required_library_id', 'library_id', 'dependency_type'))
        ->from($query)
        ->execute();
    }
  }

  /**
   * Implements saveContentData
   */
  public function saveContentData($contentId, $contentJson, $mainJsonData, $mainLibraryId, $contentMainId = NULL) {
    $embedTypes = '';
    if (isset($mainJsonData['embedTypes'])) {
      $embedTypes = implode(', ', $mainJsonData['embedTypes']);
    }
    $id = db_insert('h5p_nodes')
    ->fields(array(
      'content_id' => $contentId,
      'nid' => $contentMainId,
      'json_content' => $contentJson,
      'embed_type' => $embedTypes,
      'main_library_id' => $mainLibraryId,
    ))
    ->execute();
  }

  /**
   * Implement getWhitelist
   */
  public function getWhitelist($isLibrary, $defaultContentWhitelist, $defaultLibraryWhitelist) {
    $whitelist = variable_get('h5p_whitelist', $defaultContentWhitelist);
    if ($isLibrary) {
      $whitelist .= ' ' . variable_get('h5p_library_whitelist_extras', $defaultLibraryWhitelist);
    }
    return $whitelist;
  }

  /**
   * Implements copyLibraryUsage
   */
  public function copyLibraryUsage($contentId, $copyFromId, $contentMainId = NULL) {
    $query = db_select('h5p_nodes_libraries', 'hnl');
    $query->addField('hnl', 'library_id');
    $query->addField('hnl', 'preloaded');
    $query->addField('hnl', 'drop_css');
    $query->addExpression($contentId);
    $query->condition('content_id', $copyFromId);
    
    db_insert('h5p_nodes_libraries')
      ->fields(array('library_id', 'preloaded', 'drop_css', 'content_id'))
      ->from($query)
      ->execute();
  }

  /**
   * Implements deleteContentData
   */
  public function deleteContentData($contentId) {
    db_delete('h5p_nodes')
    ->condition('content_id', $contentId)
    ->execute();
    $this->deleteLibraryUsage($contentId);
  }

  /**
   * Implements deleteLibraryUsage
   */
  public function deleteLibraryUsage($contentId) {
    db_delete('h5p_nodes_libraries')
    ->condition('content_id', $contentId)
    ->execute();
  }

  /**
   * Implements saveLibraryUsage
   */
  public function saveLibraryUsage($contentId, $librariesInUse) {
    $dropLibraryCssList = array();
    foreach ($librariesInUse as $machineName => $library) {
      if (!empty($library['library']['dropLibraryCss'])) {
        $dropLibraryCssList = array_merge($dropLibraryCssList, explode(', ', $library['library']['dropLibraryCss']));
      }
    }
    foreach ($librariesInUse as $machineName => $library) {
      $dropCss = in_array($machineName, $dropLibraryCssList) ? 1 : 0;
      db_merge('h5p_nodes_libraries')
        ->key(array(
          'content_id' => $contentId,
          'library_id' => $library['library']['libraryId']
        ))
        ->fields(array(
        'content_id' => $contentId,
        'library_id' => $library['library']['libraryId'],
        'preloaded' => $library['preloaded'],
        'drop_css' => $dropCss,
      ))
      ->execute();
    }
  }

  /**
   * Implements loadLibrary
   */
  public function loadLibrary($machineName, $majorVersion, $minorVersion) {
    $library = db_query(
      "SELECT library_id as libraryId, machine_name as machineName, title, major_version as majorVersion, minor_version as minorVersion,
        patch_version as patchVersion, embed_types as embedTypes, preloaded_js as preloadedJs, preloaded_css as preloadedCss, drop_library_css as dropLibraryCss,
        fullscreen, runnable, semantics
      FROM {h5p_libraries}
      WHERE machine_name = :machine_name
      AND major_version = :major_version
      AND minor_version = :minor_version", array(':machine_name' => $machineName, ':major_version' => $majorVersion, ':minor_version' => $minorVersion))
      ->fetchAssoc();
    $result = db_query(
      "SELECT hl.machine_name as machineName, hl.major_version as majorVersion, hl.minor_version as minorVersion, hll.dependency_type as dependencyType
      FROM {h5p_libraries_libraries} hll
      JOIN {h5p_libraries} hl ON hll.required_library_id = hl.library_id
      WHERE hll.library_id = :library_id", array(':library_id' => $library['libraryId']));
    foreach ($result as $dependency) {
      $library[$dependency->dependencyType . 'Dependencies'][] = array(
        'machineName' => $dependency->machineName,
        'majorVersion' => $dependency->majorVersion,
        'minorVersion' => $dependency->minorVersion,
      );
    }
    if ($this->isInDevMode()) {
      $semantics = $this->getSemanticsFromFile($library['machineName'], $library['majorVersion'], $library['minorVersion']);
      if ($semantics) {
        $library['semantics'] = $semantics;
      }
    }
    return $library;
  }

  /**
   * Implements getLibrarySemantics
   *
   * Calls modules implementing hook_alter_h5p_semantics().
   */
  public function getLibrarySemantics($machineName, $majorVersion, $minorVersion) {
    if ($this->isInDevMode()) {
      $semantics = $this->getSemanticsFromFile($machineName, $majorVersion, $minorVersion);
    }
    else {
      $semantics = db_query(
        "SELECT semantics
        FROM {h5p_libraries}
        WHERE machine_name = :machine_name
        AND major_version = :major_version
        AND minor_version = :minor_version", array(':machine_name' => $machineName, ':major_version' => $majorVersion, ':minor_version' => $minorVersion))->fetchField();
    }
    $semantics = json_decode($semantics);
    if (!empty($semantics)) {
      drupal_alter('h5p_semantics', $semantics);
    }

    return $semantics;
  }

  /**
   * Reads semantics for a library from the library.json file instead of the database
   * 
   * @param string $machineName
   *  Machine readable name of the library
   * @param int $majorVersion
   *  Major version for the library
   * @param int $minorVersion
   *  Minor version for the library
   * @return sting|boolean
   *  Semantics as string if successfull
   *  FALSE as boolean if not successfull
   *  
   */
  private function getSemanticsFromFile($machineName, $majorVersion, $minorVersion) {
    $semanticsPath = file_stream_wrapper_get_instance_by_uri('public://')->realpath() . '/' . variable_get('h5p_default_path', 'h5p') . '/libraries/' . $machineName . '-' . $majorVersion . '.' . $minorVersion . '/semantics.json';
    if (file_exists($semanticsPath)) {
      $semantics = file_get_contents($semanticsPath);
      if (!json_decode($semantics, TRUE)) {
        drupal_set_message(t('Invalid json in semantics for %library', array('%library' => $machineName)), 'warning');
      }
      return $semantics;
    }
    return FALSE;
  }

  /**
   * Implements getExportData
   *
   * @param int $contentId
   * ContentID of the node we are going to export
   **/
  public function getExportData($contentId) {
    $content = db_query(
      "SELECT main_library_id, embed_type, json_content
      FROM {h5p_nodes}
      WHERE content_id = :content_id", array(':content_id' => $contentId))
      ->fetchAssoc();

    $mainLibraryId = $content['main_library_id'];

    // Use library ids to get library info.
    $res = db_query(
      "SELECT hl.machine_name as machine_name, hl.major_version as major_version, hl.minor_version as minor_version,
      hnl.preloaded as preloaded, hl.library_id as library_id
      FROM {h5p_libraries} hl
      JOIN {h5p_nodes_libraries} hnl ON hl.library_id =  hnl.library_id
      WHERE hnl.content_id = :hnl_content_id", array(':hnl_content_id' => $contentId));

    while ($libs = $res->fetchAssoc()) {
      $librariesInfo[$libs['machine_name']] = array(
        'machineName' => $libs['machine_name'],
        'majorVersion' => $libs['major_version'],
        'minorVersion' => $libs['minor_version'],
        'preloaded' => $libs['preloaded'],
      );

      // Save the main libary machine name.
      if ($libs['library_id'] == $mainLibraryId) {
        $mainLibraryMachineName = $libs['machine_name'];
        $mainLibrary = $librariesInfo[$mainLibraryMachineName];
      }
    }

    $editorLibraries = $this->getEditorLibraries($mainLibraryMachineName, $mainLibrary['majorVersion'], $mainLibrary['minorVersion'], TRUE);
    
    $export = array(
      'contentId' => $contentId,
      'mainLibrary' => $mainLibraryMachineName,
      'embedType' => $content['embed_type'],
      'libraries' => $librariesInfo,
      'editorLibraries' => $editorLibraries,
      'jsonContent' => $content['json_content'],
    );

    return $export;
  }
  
  /**
   * Check if h5p export is enabled.
   *
   * @return bool
   */
  public function isExportEnabled() {
    return (bool) variable_get('h5p_export', 1);
  }
  
  /**
   * Implements getEditorLibraries.
   *
   * TODO: Perhaps this should be part of some dependency function? 
   */
  public function getEditorLibraries($machineName, $majorVersion, $minorVersion, $complete = FALSE) {
    $editorLibraries = array();

    $result = db_query("
      SELECT hll.required_library_id AS libraryId, hl2.machine_name AS machineName, hl2.major_version AS majorVersion, hl2.minor_version AS minorVersion
      FROM {h5p_libraries} hl
      JOIN {h5p_libraries_libraries} hll ON hll.library_id = hl.library_id
      JOIN {h5p_libraries} hl2 ON hl2.library_id = hll.required_library_id
      WHERE hl.machine_name = :hl_machine_name
      AND hl.major_version = :hl_major_version
      AND hl.minor_version = :hl_minor_version
      AND hll.dependency_type = :hll_dependency_type
    ", array(':hl_machine_name' => $machineName, ':hl_major_version' => $majorVersion, ':hl_minor_version' => $minorVersion, ':hll_dependency_type' => 'editor'));

    $jsonData = array('preloadedDependencies' => array());
    while ($editorLibrary = $result->fetchAssoc()) {
      $editorLibraries[$editorLibrary['libraryId']] = $editorLibrary;

      $jsonData['preloadedDependencies'][$editorLibrary['libraryId']] = array(
        'machineName' => $editorLibrary['machineName'],
        'majorVersion' => $editorLibrary['majorVersion'],
        'minorVersion' => $editorLibrary['minorVersion'],
      );
    }

    $libraries = array();
    $storage = _h5p_get_instance('storage');
    $storage->getLibraryUsage($libraries, $jsonData, FALSE, $complete);
    
    foreach ($libraries as $library) {
      if ($library['preloaded']) {
        $editorLibraries[$library['library']['libraryId']] = $library['library'];
      }
    }

    return $editorLibraries;
  }
}
