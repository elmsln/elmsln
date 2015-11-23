<?php

class H5peditor {

  public static $styles = array(
    'styles/css/application.css',
  );
  public static $scripts = array(
    'scripts/h5peditor.js',
    'scripts/h5peditor-semantic-structure.js',
    'scripts/h5peditor-editor.js',
    'scripts/h5peditor-library-selector.js',
    'scripts/h5peditor-form.js',
    'scripts/h5peditor-text.js',
    'scripts/h5peditor-html.js',
    'scripts/h5peditor-number.js',
    'scripts/h5peditor-textarea.js',
    'scripts/h5peditor-file.js',
    'scripts/h5peditor-av.js',
    'scripts/h5peditor-group.js',
    'scripts/h5peditor-boolean.js',
    'scripts/h5peditor-list.js',
    'scripts/h5peditor-list-editor.js',
    'scripts/h5peditor-library.js',
    'scripts/h5peditor-library-list-cache.js',
    'scripts/h5peditor-select.js',
    'scripts/h5peditor-dimensions.js',
    'scripts/h5peditor-coordinates.js',
    'scripts/h5peditor-none.js',
    'ckeditor/ckeditor.js',
  );
  private $h5p, $storage, $files_directory, $basePath;

  /**
   * Constructor for the core editor library.
   *
   * @param \H5PCore $h5p Instance of core.
   * @param mixed $storage Instance of h5peditor storage.
   * @param string $basePath Url path to prefix assets with.
   * @param string $filesDir H5P files directory.
   * @param string $editorFilesDir Optional custom editor files directory outside h5p files directory.
   */
  function __construct($h5p, $storage, $basePath, $filesDir, $editorFilesDir = NULL) {
    $this->h5p = $h5p;
    $this->storage = $storage;
    $this->basePath = $basePath;
    $this->contentFilesDir = $filesDir . DIRECTORY_SEPARATOR . 'content';
    $this->editorFilesDir = ($editorFilesDir === NULL ? $filesDir . DIRECTORY_SEPARATOR . 'editor' : $editorFilesDir);
  }

  /**
   * Get list of libraries.
   *
   * @return array
   */
  public function getLibraries() {
    if (isset($_POST['libraries'])) {
      // Get details for the specified libraries.
      $libraries = array();
      foreach ($_POST['libraries'] as $libraryName) {
        $matches = array();
        preg_match_all('/(.+)\s(\d)+\.(\d)$/', $libraryName, $matches);
        if ($matches) {
          $libraries[] = (object) array(
            'uberName' => $libraryName,
            'name' => $matches[1][0],
            'majorVersion' => $matches[2][0],
            'minorVersion' => $matches[3][0]
          );
        }
      }
    }

    $libraries = $this->storage->getLibraries(!isset($libraries) ? NULL : $libraries);

    if ($this->h5p->development_mode & H5PDevelopment::MODE_LIBRARY) {
      $devLibs = $this->h5p->h5pD->getLibraries();

      // Replace libraries with devlibs
      for ($i = 0, $s = count($libraries); $i < $s; $i++) {
        $lid = $libraries[$i]->name . ' ' . $libraries[$i]->majorVersion . '.' . $libraries[$i]->minorVersion;
        if (isset($devLibs[$lid])) {
          $libraries[$i] = (object) array(
            'uberName' => $lid,
            'name' => $devLibs[$lid]['machineName'],
            'title' => $devLibs[$lid]['title'],
            'majorVersion' => $devLibs[$lid]['majorVersion'],
            'minorVersion' => $devLibs[$lid]['minorVersion'],
            'runnable' => $devLibs[$lid]['runnable'],
          );
        }
      }
    }

    return json_encode($libraries);
  }

  /**
   * Keep track of temporary files.
   *
   * @param object file
   */
  public function addTmpFile($file) {
    $this->storage->addTmpFile($file);
  }

  /**
   * Create directories for uploaded content.
   *
   * @param int $id
   * @return boolean
   */
  public function createDirectories($id) {
    $this->content_directory = $this->contentFilesDir . DIRECTORY_SEPARATOR . $id . DIRECTORY_SEPARATOR;

    if (!is_dir($this->contentFilesDir)) {
      mkdir($this->contentFilesDir, 0777, true);
    }

    $sub_directories = array('', 'files', 'images', 'videos', 'audios');
    foreach ($sub_directories AS $sub_directory) {
      $sub_directory = $this->content_directory . $sub_directory;
      if (!is_dir($sub_directory) && !mkdir($sub_directory)) {
        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * Move uploaded files, remove old files and update library usage.
   *
   * @param string $oldLibrary
   * @param string $oldParameters
   * @param object $newLibrary
   * @param string $newParameters
   */
  public function processParameters($contentId, $newLibrary, $newParameters, $oldLibrary = NULL, $oldParameters = NULL) {
    $newFiles = array();
    $oldFiles = array();

    // Find new libraries/content dependencies and files.
    // Start by creating a fake library field to process. This way we get all the dependencies of the main library as well.
    $field = (object) array(
      'type' => 'library'
    );
    $libraryParams = (object) array(
      'library' => H5PCore::libraryToString($newLibrary),
      'params' => $newParameters
    );
    $this->processField($field, $libraryParams, $newFiles);

    if ($oldLibrary !== NULL) {
      // Find old files and libraries.
      $this->processSemantics($oldFiles, $this->h5p->loadLibrarySemantics($oldLibrary['name'], $oldLibrary['majorVersion'], $oldLibrary['minorVersion']), $oldParameters);

      // Remove old files.
      for ($i = 0, $s = count($oldFiles); $i < $s; $i++) {
        if (!in_array($oldFiles[$i], $newFiles) &&
            preg_match('/^\w+:\/\//i', $oldFiles[$i]) === 0) {
          $removeFile = $this->content_directory . $oldFiles[$i];
          unlink($removeFile);
          $this->storage->removeFile($removeFile);
        }
      }
    }
  }

  /**
   * Recursive function that moves the new files in to the h5p content folder and generates a list over the old files.
   * Also locates all the librares.
   *
   * @param array $files
   * @param array $libraries
   * @param array $semantics
   * @param array $params
   */
  private function processSemantics(&$files, $semantics, &$params) {
    for ($i = 0, $s = count($semantics); $i < $s; $i++) {
      $field = $semantics[$i];
      if (!isset($params->{$field->name})) {
        continue;
      }
      $this->processField($field, $params->{$field->name}, $files);
    }
  }

  /**
   * Process a single field.
   *
   * @staticvar string $h5peditor_path
   * @param object $field
   * @param mixed $params
   * @param array $files
   * @param array $libraries
   */
  private function processField(&$field, &$params, &$files) {
    static $h5peditor_path;
    if (!$h5peditor_path) {
      $h5peditor_path = $this->editorFilesDir . DIRECTORY_SEPARATOR;
    }
    switch ($field->type) {
      case 'file':
      case 'image':
        if (isset($params->path)) {
          $oldPath = $h5peditor_path . $params->path;
          $newPath = $this->content_directory . $params->path;
          if (file_exists($oldPath)) {
            rename($oldPath, $newPath);
            $this->storage->keepFile($oldPath, $newPath);
          }
          elseif (file_exists($newPath)) {
            $this->storage->keepFile($newPath, $newPath);
          }

          $files[] = $params->path;
        }
        break;

      case 'video':
      case 'audio':
        if (is_array($params)) {
          for ($i = 0, $s = count($params); $i < $s; $i++) {
            $oldPath = $h5peditor_path . $params[$i]->path;
            $newPath = $this->content_directory . $params[$i]->path;
            if (file_exists($oldPath)) {
              rename($oldPath, $newPath);
              $this->storage->keepFile($oldPath, $newPath);
            }
            elseif (file_exists($newPath)) {
              $this->storage->keepFile($newPath, $newPath);
            }
            $files[] = $params[$i]->path;
          }
        }
        break;

      case 'library':
        if (isset($params->library) && isset($params->params)) {
          $library = H5PCore::libraryFromString($params->library);
          $semantics = $this->h5p->loadLibrarySemantics($library['machineName'], $library['majorVersion'], $library['minorVersion']);

          // Process parameters for the library.
          $this->processSemantics($files, $semantics, $params->params);
        }
        break;

      case 'group':
        if (isset($params)) {
          if (count($field->fields) == 1) {
            $params = (object) array($field->fields[0]->name => $params);
          }
          $this->processSemantics($files, $field->fields, $params);
        }
        break;

      case 'list':
        if (is_array($params)) {
          for ($j = 0, $t = count($params); $j < $t; $j++) {
            $this->processField($field->field, $params[$j], $files);
          }
        }
        break;
    }
  }

  /**
   * TODO: Consider moving to core.
   */
  public function getLibraryLanguage($machineName, $majorVersion, $minorVersion, $languageCode) {
    if ($this->h5p->development_mode & H5PDevelopment::MODE_LIBRARY) {
      // Try to get language development library first.
      $language = $this->h5p->h5pD->getLanguage($machineName, $majorVersion, $minorVersion, $languageCode);
    }

    if (isset($language) === FALSE) {
      $language = $this->storage->getLanguage($machineName, $majorVersion, $minorVersion, $languageCode);
    }

    return ($language === FALSE ? NULL : $language);
  }

  /**
   * Return all libraries used by the given editor library.
   *
   * @param string $machineName Library identfier part 1
   * @param int $majorVersion Library identfier part 2
   * @param int $minorVersion Library identfier part 3
   */
  public function findEditorLibraries($machineName, $majorVersion, $minorVersion) {
    $library = $this->h5p->loadLibrary($machineName, $majorVersion, $minorVersion);
    $dependencies = array();
    $this->h5p->findLibraryDependencies($dependencies, $library);

    // Order dependencies by weight
    $orderedDependencies = array();
    for ($i = 1, $s = count($dependencies); $i <= $s; $i++) {
      foreach ($dependencies as $dependency) {
        if ($dependency['weight'] === $i && $dependency['type'] === 'editor') {
          // Only load editor libraries.
          $orderedDependencies[$dependency['library']['libraryId']] = $dependency['library'];
          break;
        }
      }
    }

    return $orderedDependencies;
  }

  /**
   * Get all scripts, css and semantics data for a library
   *
   * @param string $library_name
   *  Name of the library we want to fetch data for
   * @param string $prefix Optional. Files are relative to another dir.
   */
  public function getLibraryData($machineName, $majorVersion, $minorVersion, $languageCode, $path = '', $prefix = '') {
    $libraryData = new stdClass();

    $libraries = $this->findEditorLibraries($machineName, $majorVersion, $minorVersion);
    $libraryData->semantics = $this->h5p->loadLibrarySemantics($machineName, $majorVersion, $minorVersion);
    $libraryData->language = $this->getLibraryLanguage($machineName, $majorVersion, $minorVersion, $languageCode);

    $files = $this->h5p->getDependenciesFiles($libraries, $prefix);
    $this->storage->alterLibraryFiles($files, $libraries);

    if ($path) {
      $path .= '/';
    }

    // Javascripts
    if (!empty($files['scripts'])) {
      foreach ($files['scripts'] as $script) {
        if (preg_match ('/:\/\//', $script->path) === 1) {
          // External file
          $libraryData->javascript[$script->path . $script->version] = "\n" . file_get_contents($script->path);
        }
        else {
          // Local file
          $libraryData->javascript[$this->h5p->url . $script->path . $script->version] = "\n" . file_get_contents($path . $script->path);
        }
      }
    }

    // Stylesheets
    if (!empty($files['styles'])) {
      foreach ($files['styles'] as $css) {
        if (preg_match ('/:\/\//', $css->path) === 1) {
          // External file
          $libraryData->css[$css->path. $css->version] = file_get_contents($css->path);
        }
        else {
          // Local file
          H5peditor::buildCssPath(NULL, $this->h5p->url . dirname($css->path) . '/');
          $libraryData->css[$this->h5p->url . $css->path . $css->version] = preg_replace_callback('/url\([\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\)/i', 'H5peditor::buildCssPath', file_get_contents($path . $css->path));
        }
      }
    }

    // Add translations for libraries.
    foreach ($libraries as $library) {
      $language = $this->getLibraryLanguage($library['machineName'], $library['majorVersion'], $library['minorVersion'], $languageCode);
      if ($language !== NULL) {
        $lang = '; H5PEditor.language["' . $library['machineName'] . '"] = ' . $language . ';';
        $libraryData->javascript[md5($lang)] = $lang;
      }
    }

    return json_encode($libraryData);
  }

  /**
   * This function will prefix all paths within a CSS file.
   * Copied from Drupal 6.
   *
   * @staticvar type $_base
   * @param type $matches
   * @param type $base
   * @return type
   */
  public static function buildCssPath($matches, $base = NULL) {
    static $_base;
    // Store base path for preg_replace_callback.
    if (isset($base)) {
      $_base = $base;
    }

    // Prefix with base and remove '../' segments where possible.
    $path = $_base . $matches[1];
    $last = '';
    while ($path != $last) {
      $last = $path;
      $path = preg_replace('`(^|/)(?!\.\./)([^/]+)/\.\./`', '$1', $path);
    }
    return 'url('. $path .')';
  }
}
