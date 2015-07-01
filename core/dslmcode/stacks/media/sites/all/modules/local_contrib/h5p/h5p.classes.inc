<?php

class H5PDrupal implements H5PFrameworkInterface {

  /**
   * Implements getPlatformInfo
   */
  public function getPlatformInfo() {
    // Could call system_get_info(), but performance-wise it
    // does not seem to be smart
    $h5p_info = unserialize(db_query("SELECT info FROM {system} WHERE name = 'h5p'")->fetchField());

    return array(
      'name' => 'drupal',
      'version' => VERSION,
      'h5pVersion' => isset($h5p_info->version) ? $h5p_info->version : NULL,
    );
  }

  /**
   * Implements fetchExternalData
   */
  public function fetchExternalData($url) {
    $response = drupal_http_request($url);
    return isset($response->error) ? NULL : $response->data;
  }

  /**
   * Implements setLibraryTutorialUrl
   *
   * Set the tutorial URL for a library. All versions of the library is set
   *
   * @param string $machineName
   * @param string $tutorialUrl
   */
  public function setLibraryTutorialUrl($machineName, $tutorialUrl) {
    db_update('h5p_libraries')
    ->fields(array(
      'tutorial_url' => $tutorialUrl,
    ))
    ->condition('machine_name', $machineName)
    ->execute();
  }

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
  private function getH5pPath() {
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
   * Implements loadLibraries
   */
  public function loadLibraries() {
    $res = db_query('SELECT library_id as id, machine_name as name, title, major_version, minor_version, patch_version, runnable, restricted FROM {h5p_libraries} ORDER BY title ASC, major_version ASC, minor_version ASC');

    $libraries = array();
    foreach ($res as $library) {
      $libraries[$library->name][] = $library;
    }

    return $libraries;
  }

  /**
   * Implementation of getUnsupportedLibraries
   */
  public function getUnsupportedLibraries() {
    return variable_get('h5p_unsupported_libraries');
  }

  /**
   * Implementation of setUnsupportedLibraries
   */
  public function setUnsupportedLibraries($libraries) {
    variable_set('h5p_unsupported_libraries', $libraries);
  }

  /**
   * Implements getAdminUrl
   */
  public function getAdminUrl() {
    return url('admin/content/h5p');
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
   * Implements getLibraryUsage
   *
   * Get number of content/nodes using a library, and the number of
   * dependencies to other libraries
   *
   * @param int $libraryId
   * @return array The array contains two elements, keyed by 'content' and 'libraries'.
   *               Each element contains a number
   */
  public function getLibraryUsage($libraryId, $skipContent = FALSE) {
    $usage = array();

    $usage['content'] = $skipContent ? -1 : intval(db_query(
      'SELECT COUNT(distinct n.nid)
      FROM {h5p_libraries} l JOIN {h5p_nodes_libraries} nl ON l.library_id = nl.library_id JOIN {h5p_nodes} n ON nl.content_id = n.content_id
      WHERE l.library_id = :id', array(':id' => $libraryId))->fetchField());

    $usage['libraries'] = intval(db_query("SELECT COUNT(*) FROM {h5p_libraries_libraries} WHERE required_library_id = :id", array(':id' => $libraryId))->fetchField());

    return $usage;
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
      if ($libraryData['runnable']) {
        if (!variable_get('h5p_first_runnable_saved', 0)) {
          variable_set('h5p_first_runnable_saved', 1);
        }
      }
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
        'semantics' => $libraryData['semantics']
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

  public function lockDependencyStorage() {
    if (db_driver() === 'mysql') {
      // Only works for mysql, other DBs will have to use transactions.

      // db_transaction often deadlocks, we do it more brutally...
      db_query('LOCK TABLES {h5p_libraries_libraries} write, {h5p_libraries} as hl read');
    }
  }

  public function unlockDependencyStorage() {
    if (db_driver() === 'mysql') {
      db_query('UNLOCK TABLES');
    }
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
   * Implements deleteLibrary. Will delete a library's data both in the database and file system
   */
  public function deleteLibrary($libraryId) {
    $library = db_query("SELECT * FROM {h5p_libraries} WHERE library_id = :id", array(':id' => $libraryId))->fetchObject();

    // Delete files
    H5PCore::deleteFileTree(_h5p_get_h5p_path() . '/libraries/' . $library->machine_name . '-' . $library->major_version . '.' . $library->minor_version);

    // Delete data in database (won't delete content)
    db_delete('h5p_libraries_libraries')->condition('library_id', $libraryId)->execute();
    db_delete('h5p_libraries_languages')->condition('library_id', $libraryId)->execute();
    db_delete('h5p_libraries')->condition('library_id', $libraryId)->execute();
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
   * Implements updateContent
   */
  public function updateContent($content, $contentMainId = NULL) {
    $content_id = db_query("SELECT content_id FROM {h5p_nodes} WHERE content_id = :content_id", array(':content_id' => $content['id']))->fetchField();
    if ($content_id === FALSE) {
      // This can happen in Drupal when module is reinstalled. (since the ID is predetermined)
      $this->insertContent($content, $contentMainId);
      return;
    }

    // Update content
    db_update('h5p_nodes')
      ->fields(array(
        'json_content' => $content['params'],
        'embed_type' => 'div', // TODO: Determine from library?
        'main_library_id' => $content['library']['libraryId'],
        'filtered' => '',
        'disable' => $content['disable']
      ))
      ->condition('content_id', $content_id)
      ->execute();
  }

  /**
   * Implements insertContent
   */
  public function insertContent($content, $contentMainId = NULL) {
    // Insert
    db_insert('h5p_nodes')
      ->fields(array(
        'content_id' => $content['id'],
        'nid' => $contentMainId,
        'json_content' => $content['params'],
        'embed_type' => 'div', // TODO: Determine from library?
        'main_library_id' => $content['library']['libraryId'],
        'filtered' => '',
        'disable' => $content['disable']
      ))
      ->execute();

    return $content['id'];
  }

  /**
   * Implements resetContentUserData
   */
  public function resetContentUserData($contentId) {
    // Reset user datas for this content
    db_update('h5p_content_user_data')
      ->fields(array(
        'timestamp' => time(),
        'data' => 'RESET'
      ))
      ->condition('content_main_id', $contentId)
      ->condition('delete_on_content_change', 1)
      ->execute();
  }

  /**
   * Implements getWhitelist
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
    db_query(
      "INSERT INTO {h5p_nodes_libraries} (content_id, library_id, dependency_type, drop_css, weight)
      SELECT :toId, hnl.library_id, hnl.dependency_type, hnl.drop_css, hnl.weight
      FROM {h5p_nodes_libraries} hnl
      WHERE hnl.content_id = :fromId", array(':toId' => $contentId, ':fromId' => $copyFromId)
    );
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
    foreach ($librariesInUse as $dependency) {
      if (!empty($dependency['library']['dropLibraryCss'])) {
        $dropLibraryCssList = array_merge($dropLibraryCssList, explode(', ', $dependency['library']['dropLibraryCss']));
      }
    }
    foreach ($librariesInUse as $dependency) {
      $dropCss = in_array($dependency['library']['machineName'], $dropLibraryCssList) ? 1 : 0;
      db_insert('h5p_nodes_libraries')
        ->fields(array(
          'content_id' => $contentId,
          'library_id' => $dependency['library']['libraryId'],
          'dependency_type' => $dependency['type'],
          'drop_css' => $dropCss,
          'weight' => $dependency['weight'],
        ))
        ->execute();
    }
  }

  /**
   * Implements loadLibrary
   */
  public function loadLibrary($machineName, $majorVersion, $minorVersion) {
    $library = db_query(
        "SELECT library_id,
                machine_name,
                title,
                major_version,
                minor_version,
                patch_version,
                embed_types,
                preloaded_js,
                preloaded_css,
                drop_library_css,
                fullscreen,
                runnable,
                semantics,
                tutorial_url
          FROM {h5p_libraries}
          WHERE machine_name = :machine_name
          AND major_version = :major_version
          AND minor_version = :minor_version",
        array(
          ':machine_name' => $machineName,
          ':major_version' => $majorVersion,
          ':minor_version' => $minorVersion
        ))
        ->fetchObject();

    if ($library === FALSE) {
      return FALSE;
    }
    $library = H5PCore::snakeToCamel($library);

    $result = db_query(
      "SELECT hl.machine_name AS name,
              hl.major_version AS major,
              hl.minor_version AS minor,
              hll.dependency_type AS type
        FROM {h5p_libraries_libraries} hll
        JOIN {h5p_libraries} hl ON hll.required_library_id = hl.library_id
        WHERE hll.library_id = :library_id",
      array(':library_id' => $library['libraryId']));

    foreach ($result as $dependency) {
      $library[$dependency->type . 'Dependencies'][] = array(
        'machineName' => $dependency->name,
        'majorVersion' => $dependency->major,
        'minorVersion' => $dependency->minor,
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

  private function getSemanticsFromFile($machineName, $majorVersion, $minorVersion) {
    $semanticsPath = drupal_realpath('public://' . variable_get('h5p_default_path', 'h5p') . '/libraries/' . $machineName . '-' . $majorVersion . '.' . $minorVersion . '/semantics.json');
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
   * Implements loadLibrarySemantics().
   */
  public function loadLibrarySemantics($machineName, $majorVersion, $minorVersion) {
    if ($this->isInDevMode()) {
      $semantics = $this->getSemanticsFromFile($machineName, $majorVersion, $minorVersion);
    }
    else {
      $semantics = db_query(
          "SELECT semantics
            FROM {h5p_libraries}
            WHERE machine_name = :machine_name
            AND major_version = :major_version
            AND minor_version = :minor_version",
          array(
            ':machine_name' => $machineName,
            ':major_version' => $majorVersion,
            ':minor_version' => $minorVersion
          ))->fetchField();
    }
    return ($semantics === FALSE ? NULL : $semantics);
  }

  /**
   * Implements alterLibrarySemantics().
   */
  public function alterLibrarySemantics(&$semantics, $name, $majorVersion, $minorVersion) {
    drupal_alter('h5p_semantics', $semantics, $name, $majorVersion, $minorVersion);
  }

  /**
   * Implements loadContent().
   */
  public function loadContent($id) {
    $content = db_query(
        "SELECT hn.content_id AS id,
                hn.json_content AS params,
                hn.embed_type,
                n.title,
                n.language,
                hl.library_id,
                hl.machine_name AS library_name,
                hl.major_version AS library_major_version,
                hl.minor_version AS library_minor_version,
                hl.embed_types AS library_embed_types,
                hl.fullscreen AS library_fullscreen,
                hn.filtered,
                hn.disable
          FROM {h5p_nodes} hn
          JOIN {node} n ON n.nid = hn.nid
          JOIN {h5p_libraries} hl ON hl.library_id = hn.main_library_id
          WHERE content_id = :id",
        array(
          ':id' => $id
        ))
        ->fetchObject();
    return ($content === FALSE ? NULL : H5PCore::snakeToCamel($content));
  }

  /**
   * Implements loadContentDependencies().
   */
  public function loadContentDependencies($id, $type = NULL) {
    $query =
        "SELECT hl.library_id,
                hl.machine_name,
                hl.major_version,
                hl.minor_version,
                hl.patch_version,
                hl.preloaded_css,
                hl.preloaded_js,
                hnl.drop_css,
                hnl.dependency_type
          FROM {h5p_nodes_libraries} hnl
          JOIN {h5p_libraries} hl ON hnl.library_id = hl.library_id
          WHERE hnl.content_id = :id";
    $queryArgs = array(':id' => $id);

    if ($type !== NULL) {
      $query .= " AND hnl.dependency_type = :dt";
      $queryArgs[':dt'] = $type;
    }
    $query .= " ORDER BY hnl.weight";
    $result = db_query($query, $queryArgs);

    $dependencies = array();
    while ($dependency = $result->fetchObject()) {
      $dependencies[] = H5PCore::snakeToCamel($dependency);
    }

    return $dependencies;
  }

  /**
   * Get stored setting.
   *
   * @param string $name
   *   Identifier for the setting
   * @param string $default
   *   Optional default value if settings is not set
   * @return mixed
   *   Whatever has been stored as the setting
   */
  public function getOption($name, $default = NULL) {
    return variable_get('h5p_' . $name, $default);
  }

  /**
   * Stores the given setting.
   * For example when did we last check h5p.org for updates to our libraries.
   *
   * @param string $name
   *   Identifier for the setting
   * @param mixed $value Data
   *   Whatever we want to store as the setting
   */
  public function setOption($name, $value) {
    variable_set('h5p_' . $name, $value);
  }

  /**
   * This will set the filtered parameters for the given content.
   *
   * @param int $content_id
   * @param string $parameters filtered
   */
  public function setFilteredParameters($content_id, $parameters = '') {
    db_update('h5p_nodes')
    ->fields(array(
      'filtered' => $parameters,
    ))
    ->condition('content_id', $content_id)
    ->execute();
  }

  /**
   * Will clear filtered params for all the content that uses the specified
   * library. This means that the content dependencies will have to be rebuilt,
   * and the parameters refiltered.
   *
   * @param int $library_id
   */
  public function clearFilteredParameters($library_id) {
    db_update('h5p_nodes')
    ->fields(array(
      'filtered' => '',
    ))
    ->condition('main_library_id', $library_id)
    ->execute();

    _drupal_flush_css_js();
    drupal_clear_js_cache();
    drupal_clear_css_cache();
  }

  /**
   * Get number of contents that has to get their content dependencies rebuilt
   * and parameters refiltered.
   *
   * @return int
   */
  public function getNumNotFiltered() {
    return intval(db_query("SELECT COUNT(content_id) FROM {h5p_nodes} WHERE filtered = '' AND main_library_id > 0")->fetchField());
  }

  /**
   * Implements getNumContent.
   */
  public function getNumContent($library_id) {
    return intval(db_query('SELECT COUNT(content_id) FROM {h5p_nodes} WHERE main_library_id = :id', array(':id' => $library_id))->fetchField());
  }
}
