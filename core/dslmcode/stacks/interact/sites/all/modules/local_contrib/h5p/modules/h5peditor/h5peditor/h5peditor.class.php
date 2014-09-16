<?php

class H5peditor {

  public static $styles = array(
    'styles/css/application.css',
  );
  public static $scripts = array(
    'scripts/h5peditor.js',
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
    'scripts/h5peditor-library.js',
    'scripts/h5peditor-select.js',
    'scripts/h5peditor-dimensions.js',
    'scripts/h5peditor-coordinates.js',
    'scripts/h5peditor-none.js',
    'ckeditor/ckeditor.js',
  );
  private $h5p, $storage, $files_directory, $basePath;

  /**
   * Constructor.
   *
   * @param object $storage
   * @param string $files_directory
   */
  function __construct($h5p, $storage, $filesDirectory, $basePath) {
    $this->h5p = $h5p;
    $this->storage = $storage;
    $this->files_directory = $filesDirectory;
    $this->basePath = $basePath;
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
    $this->content_directory = $this->files_directory . '/h5p/content/' . $id . '/';

    $sub_directories = array('', 'files', 'images', 'videos', 'audios');
    foreach ($sub_directories AS $sub_directory) {
      $sub_directory = $this->content_directory . $sub_directory;
      if (!is_dir($sub_directory) && !@mkdir($sub_directory)) {
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
    $newLibraries = array($newLibrary['machineName'] => $newLibrary);
    $oldLibraries = array($oldLibrary);

    // Find new libraries and files.
    $this->processSemantics($newFiles, $newLibraries, $this->h5p->loadLibrarySemantics($newLibrary['machineName'], $newLibrary['majorVersion'], $newLibrary['minorVersion']), $newParameters);

    $librariesUsed = $newLibraries; // Copy

    foreach ($newLibraries as $library) {
      $libraryFull = $this->h5p->loadLibrary($library['machineName'], $library['majorVersion'], $library['minorVersion']);
      $librariesUsed[$library['machineName']]['library'] = $libraryFull;
      $librariesUsed[$library['machineName']]['type'] = 'preloaded';
      $this->h5p->findLibraryDependencies($librariesUsed, $libraryFull);
    }

    // TODO: Prevent usage of Drupal here.
    $h5pStorage = _h5p_get_instance('storage');
    $h5pStorage->h5pF->deleteLibraryUsage($contentId);
    $h5pStorage->h5pF->saveLibraryUsage($contentId, $librariesUsed);

    if ($oldLibrary) {
      // Find old files and libraries.
      $this->processSemantics($oldFiles, $oldLibraries, $this->h5p->loadLibrarySemantics($oldLibrary['name'], $oldLibrary['majorVersion'], $oldLibrary['minorVersion']), $oldParameters);

      // Remove old files.
      for ($i = 0, $s = count($oldFiles); $i < $s; $i++) {
        if (!in_array($oldFiles[$i], $newFiles) && substr($oldFiles[$i], 0, 7) != 'http://') {
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
   * @param array $schema
   * @param array $params
   */
  private function processSemantics(&$files, &$libraries, $semantics, &$params) {
    for ($i = 0, $s = count($semantics); $i < $s; $i++) {
      $field = $semantics[$i];
      if (!isset($params->{$field->name})) {
        continue;
      }
      $this->processField($field, $params->{$field->name}, $files, $libraries);
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
  private function processField(&$field, &$params, &$files, &$libraries) {
    static $h5peditor_path;
    if (!$h5peditor_path) {
      $h5peditor_path = $this->files_directory . '/h5peditor/';
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
          $libraryData = h5peditor_get_library_property($params->library);
          $libraries[$libraryData['machineName']] = $libraryData;
          $this->processSemantics($files, $libraries, $this->h5p->loadLibrarySemantics($libraryData['machineName'], $libraryData['majorVersion'], $libraryData['minorVersion']), $params->params);
        }
        break;

      case 'group':
        if (isset($params)) {
          if (count($field->fields) == 1) {
            $params = (object) array($field->fields[0]->name => $params);
          }
          $this->processSemantics($files, $libraries, $field->fields, $params);
        }
        break;

      case 'list':
        if (is_array($params)) {
          for ($j = 0, $t = count($params); $j < $t; $j++) {
            $this->processField($field->field, $params[$j], $files, $libraries);
          }
        }
        break;
    }
  }

  /**
   * TODO: Consider moving to core.
   */
  public function getLibraryLanguage($machineName, $majorVersion, $minorVersion) {
    if ($this->h5p->development_mode & H5PDevelopment::MODE_LIBRARY) {
      // Try to get language development library first.
      $language = $this->h5p->h5pD->getLanguage($machineName, $majorVersion, $minorVersion);
    }
    
    if (isset($language) === FALSE) {
      $language = $this->storage->getLanguage($machineName, $majorVersion, $minorVersion);
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
    
    $editorLibraries = array();
    foreach ($dependencies as $dependency) {
      if ($dependency['type'] !== 'editor') {
        continue; // Only load editor libraries.
      }
      $dependency['library']['dropCss'] = $dependency['dropCss'];
      $editorLibraries[$dependency['library']['libraryId']] = $dependency['library'];
    }
    
    return $editorLibraries;
  }

  /**
   * Get all scripts, css and semantics data for a library
   *
   * @param string $library_name
   *  Name of the library we want to fetch data for
   */
  public function getLibraryData($machineName, $majorVersion, $minorVersion) {
    $libraryData = new stdClass();
    
    $libraries = $this->findEditorLibraries($machineName, $majorVersion, $minorVersion);
    $libraryData->semantics = $this->h5p->loadLibrarySemantics($machineName, $majorVersion, $minorVersion);
    $libraryData->language = $this->storage->getLanguage($machineName, $majorVersion, $minorVersion);

    $files = $this->h5p->getDependenciesFiles($libraries);
    
    // Javascripts
    if (!empty($files['scripts'])) {
      foreach ($files['scripts'] as $script) {
        if (!isset($libraryData->javascript[$script])) {
          $libraryData->javascript[$script] = '';
        }
        $libraryData->javascript[$script] .= "\n" . file_get_contents($script);
      }
    }
    
    // Stylesheets
    if (!empty($files['styles'])) {
      foreach ($files['styles'] as $css) {
        H5peditor::buildCssPath(NULL, $this->basePath . dirname($css) . '/');
        $libraryData->css[$css] = preg_replace_callback('/url\([\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\)/i', 'H5peditor::buildCssPath', file_get_contents($css));
      }
    }

    // Add translations for libraries.
    foreach ($libraries as $library) {
      $language = $this->getLibraryLanguage($library['machineName'], $library['majorVersion'], $library['minorVersion']);
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
