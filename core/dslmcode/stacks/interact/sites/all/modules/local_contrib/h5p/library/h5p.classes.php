<?php
/**
 * Interface defining functions the h5p library needs the framework to implement
 */
interface H5PFrameworkInterface {

  /**
   * Show the user an error message
   *
   * @param string $message
   *  The error message
   */
  public function setErrorMessage($message);

  /**
   * Show the user an information message
   *
   * @param string $message
   *  The error message
   */
  public function setInfoMessage($message);

  /**
   * Translation function
   *
   * @param string $message
   *  The english string to be translated.
   * @param type $replacements
   *   An associative array of replacements to make after translation. Incidences
   *   of any key in this array are replaced with the corresponding value. Based
   *   on the first character of the key, the value is escaped and/or themed:
   *    - !variable: inserted as is
   *    - @variable: escape plain text to HTML
   *    - %variable: escape text and theme as a placeholder for user-submitted
   *      content
   * @return string Translated string
   */
  public function t($message, $replacements = array());

  /**
   * Get the Path to the last uploaded h5p
   *
   * @return string Path to the folder where the last uploaded h5p for this session is located.
   */
  public function getUploadedH5pFolderPath();

  /**
   * @return string Path to the folder where all h5p files are stored
   */
  public function getH5pPath();

  /**
   * Get the path to the last uploaded h5p file
   *
   * @return string Path to the last uploaded h5p
   */
  public function getUploadedH5pPath();
  
  /**
   * Get the list of the current installed libraries
   * 
   * @return array Associative array containg one item per machine name. This item contains an array of libraries.
   */
  public function loadLibraries();
  
  /**
   * Saving the unsupported library list
   * 
   * @param array A list of unsupported libraries
   */
  public function setUnsupportedLibraries($libraries);
  
  /**
   * Returns unsupported libraries
   * 
   * @return array A list of the unsupported libraries
   */
  public function getUnsupportedLibraries();
  
  /**
   * Returns the URL to the library admin page
   * 
   * @return string URL to admin page
   */
  public function getAdminUrl();

  /**
   * Get id to an excisting library
   *
   * @param string $machineName
   *  The librarys machine name
   * @param int $majorVersion
   *  The librarys major version
   * @param int $minorVersion
   *  The librarys minor version
   * @return int
   *  The id of the specified library or FALSE
   */
  public function getLibraryId($machineName, $majorVersion, $minorVersion);

  /**
   * Get file extension whitelist
   *
   * The default extension list is part of h5p, but admins should be allowed to modify it
   *
   * @param boolean $isLibrary
   * @param string $defaultContentWhitelist
   * @param string $defaultLibraryWhitelist
   */
  public function getWhitelist($isLibrary, $defaultContentWhitelist, $defaultLibraryWhitelist);
  
  /**
   * Is the library a patched version of an existing library?
   *
   * @param object $library
   *  The library data for a library we are checking
   * @return boolean
   *  TRUE if the library is a patched version of an excisting library
   *  FALSE otherwise
   */
  public function isPatchedLibrary($library);

  /**
   * Is H5P in development mode?
   *
   * @return boolean
   *  TRUE if H5P development mode is active
   *  FALSE otherwise
   */
  public function isInDevMode();

  /**
   * Is the current user allowed to update libraries?
   *
   * @return boolean
   *  TRUE if the user is allowed to update libraries
   *  FALSE if the user is not allowed to update libraries
   */
  public function mayUpdateLibraries();

  /**
   * Store data about a library
   *
   * Also fills in the libraryId in the libraryData object if the object is new
   *
   * @param object $libraryData
   *  Object holding the information that is to be stored
   */
  public function saveLibraryData(&$libraryData, $new = TRUE);
  
  /**
   * Insert new content.
   * 
   * @param object $content
   * @param int $contentMainId
   */
  public function insertContent($content, $contentMainId = NULL);
  
  /**
   * Update old content.
   * 
   * @param object $content
   * @param int $contentMainId
   */
  public function updateContent($content, $contentMainId = NULL);
  
  /**
   * Save what libraries a library is dependending on
   *
   * @param int $libraryId
   *  Library Id for the library we're saving dependencies for
   * @param array $dependencies
   *  List of dependencies in the format used in library.json
   * @param string $dependency_type
   *  What type of dependency this is, for instance it might be an editor dependency
   */
  public function saveLibraryDependencies($libraryId, $dependencies, $dependency_type);

  /**
   * Copies library usage
   *
   * @param int $contentId
   *  Framework specific id identifying the content
   * @param int $copyFromId
   *  Framework specific id identifying the content to be copied
   * @param int $contentMainId
   *  Framework specific main id for the content, typically used in frameworks
   *  That supports versioning. (In this case the content id will typically be
   *  the version id, and the contentMainId will be the frameworks content id
   */
  public function copyLibraryUsage($contentId, $copyFromId, $contentMainId = NULL);

  /**
   * Deletes content data
   *
   * @param int $contentId
   *  Framework specific id identifying the content
   */
  public function deleteContentData($contentId);

  /**
   * Delete what libraries a content item is using
   *
   * @param int $contentId
   *  Content Id of the content we'll be deleting library usage for
   */
  public function deleteLibraryUsage($contentId);

  /**
   * Saves what libraries the content uses
   *
   * @param int $contentId
   *  Framework specific id identifying the content
   * @param array $librariesInUse
   *  List of libraries the content uses. Libraries consist of arrays with:
   *   - libraryId stored in $librariesInUse[<place>]['library']['libraryId']
   *   - libraryId stored in $librariesInUse[<place>]['preloaded']
   */
  public function saveLibraryUsage($contentId, $librariesInUse);

  /**
   * Get number of content/nodes using a library, and the number of 
   * dependencies to other libraries
   * 
   * @param int $library_id
   * @return array The array contains two elements, keyed by 'content' and 'libraries'. 
   *               Each element contains a number
   */
  public function getLibraryUsage($libraryId);

  /**
   * Loads a library
   *
   * @param string $machineName
   * @param int $majorVersion
   * @param int $minorVersion
   * @return array|FALSE
   *  Array representing the library with dependency descriptions
   *  FALSE if the library doesn't exist
   */
  public function loadLibrary($machineName, $majorVersion, $minorVersion);

  /**
   * Loads library semantics.
   *
   * @param string $name library identifier.
   * @param int $majorVersion library identifier.
   * @param int $minorVersion library identifier.
   * @return string semantics.
   */
  public function loadLibrarySemantics($name, $majorVersion, $minorVersion);
  
  /**
   * Makes it possible to alter the semantics, adding custom fields, etc.
   *
   * @param array $semantics
   * @param string $name library identifier.
   * @param int $majorVersion library identifier.
   * @param int $minorVersion library identifier.
   */
  public function alterLibrarySemantics(&$semantics, $name, $majorVersion, $minorVersion);

  /**
   * Delete all dependencies belonging to given library
   *
   * @param int $libraryId
   *  Library Id
   */
  public function deleteLibraryDependencies($libraryId);
  
  /**
   * Delete a library from database and file system
   * 
   * @param int $libraryId Library Id
   */
  public function deleteLibrary($libraryId);
  
  /**
   * Load content.
   *
   * @return object Content, null if not found.
   */
  public function loadContent($id);
  
  /**
   * Load dependencies for the given content of the given type.
   *
   * @param int $id content.
   * @param int $type dependency.
   * @return array
   */
  public function loadContentDependencies($id, $type = NULL);
  
  /**
   * Get data from cache.
   * 
   * @param string $group
   * @param string $key
   */
  public function cacheGet($group, $key);
  
  /**
   * Store data in cache.
   * 
   * @param string $group
   * @param string $key
   * @param mixed $data
   */
  public function cacheSet($group, $key, $data);
  
  /**
   * Delete data from cache.
   * 
   * @param string $group
   * @param string $key
   */
  public function cacheDel($group, $key = NULL);
  
  /**
   * Will invalidate the cache for the content that uses the specified library.
   * This means that the content dependencies has to be rebuilt, and the parameters refiltered.
   * 
   * @param int $library_id
   */
  public function invalidateContentCache($library_id);
  
  /**
   * Get content without cache.
   */
  public function getNotCached();
  
  /**
   * Get number of contents using library as main library.
   * 
   * @param int $library_id
   */
  public function getNumContent($library_id);
}

/**
 * This class is used for validating H5P files
 */
class H5PValidator {
  public $h5pF;
  public $h5pC;

  // Schemas used to validate the h5p files
  private $h5pRequired = array(
    'title' => '/^.{1,255}$/',
    'language' => '/^[a-z]{1,5}$/',
    'preloadedDependencies' => array(
      'machineName' => '/^[\w0-9\-\.]{1,255}$/i',
      'majorVersion' => '/^[0-9]{1,5}$/',
      'minorVersion' => '/^[0-9]{1,5}$/',
    ),
    'mainLibrary' => '/^[$a-z_][0-9a-z_\.$]{1,254}$/i',
    'embedTypes' => array('iframe', 'div'),
  );

  private $h5pOptional = array(
    'contentType' => '/^.{1,255}$/',
    'author' => '/^.{1,255}$/',
    'license' => '/^(cc-by|cc-by-sa|cc-by-nd|cc-by-nc|cc-by-nc-sa|cc-by-nc-nd|pd|cr|MIT|GPL1|GPL2|GPL3|MPL|MPL2)$/',
    'dynamicDependencies' => array(
      'machineName' => '/^[\w0-9\-\.]{1,255}$/i',
      'majorVersion' => '/^[0-9]{1,5}$/',
      'minorVersion' => '/^[0-9]{1,5}$/',
    ),
    'w' => '/^[0-9]{1,4}$/',
    'h' => '/^[0-9]{1,4}$/',
    'metaKeywords' => '/^.{1,}$/',
    'metaDescription' => '/^.{1,}$/',
  );

  // Schemas used to validate the library files
  private $libraryRequired = array(
    'title' => '/^.{1,255}$/',
    'majorVersion' => '/^[0-9]{1,5}$/',
    'minorVersion' => '/^[0-9]{1,5}$/',
    'patchVersion' => '/^[0-9]{1,5}$/',
    'machineName' => '/^[\w0-9\-\.]{1,255}$/i',
    'runnable' => '/^(0|1)$/',
  );

  private $libraryOptional  = array(
    'author' => '/^.{1,255}$/',
    'license' => '/^(cc-by|cc-by-sa|cc-by-nd|cc-by-nc|cc-by-nc-sa|cc-by-nc-nd|pd|cr|MIT|GPL1|GPL2|GPL3|MPL|MPL2)$/',
    'description' => '/^.{1,}$/',
    'dynamicDependencies' => array(
      'machineName' => '/^[\w0-9\-\.]{1,255}$/i',
      'majorVersion' => '/^[0-9]{1,5}$/',
      'minorVersion' => '/^[0-9]{1,5}$/',
    ),
    'preloadedDependencies' => array(
      'machineName' => '/^[\w0-9\-\.]{1,255}$/i',
      'majorVersion' => '/^[0-9]{1,5}$/',
      'minorVersion' => '/^[0-9]{1,5}$/',
    ),
    'editorDependencies' => array(
      'machineName' => '/^[\w0-9\-\.]{1,255}$/i',
      'majorVersion' => '/^[0-9]{1,5}$/',
      'minorVersion' => '/^[0-9]{1,5}$/',
    ),
    'preloadedJs' => array(
      'path' => '/^((\\\|\/)?[a-z_\-\s0-9\.]+)+\.js$/i',
    ),
    'preloadedCss' => array(
      'path' => '/^((\\\|\/)?[a-z_\-\s0-9\.]+)+\.css$/i',
    ),
    'dropLibraryCss' => array(
      'machineName' => '/^[\w0-9\-\.]{1,255}$/i',
    ),
    'w' => '/^[0-9]{1,4}$/',
    'h' => '/^[0-9]{1,4}$/',
    'embedTypes' => array('iframe', 'div'),
    'fullscreen' => '/^(0|1)$/',
    'coreApi' => array(
      'majorVersion' => '/^[0-9]{1,5}$/',
      'minorVersion' => '/^[0-9]{1,5}$/',
    ),
  );

  /**
   * Constructor for the H5PValidator
   *
   * @param object $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   */
  public function __construct($H5PFramework, $H5PCore) {
    $this->h5pF = $H5PFramework;
    $this->h5pC = $H5PCore;
    $this->h5pCV = new H5PContentValidator($this->h5pF, $this->h5pC);
  }

  /**
   * Validates a .h5p file
   *
   * @return boolean
   *  TRUE if the .h5p file is valid
   */
  public function isValidPackage($skipContent = FALSE, $upgradeOnly = FALSE) {
    // Create a temporary dir to extract package in.
    $tmpDir = $this->h5pF->getUploadedH5pFolderPath();
    $tmpPath = $this->h5pF->getUploadedH5pPath();

    $valid = TRUE;

    // Extract and then remove the package file.
    $zip = new ZipArchive;
    
    // Only allow files with the .h5p extension:
    if (strtolower(substr($tmpPath, -3)) !== 'h5p') {
      $this->h5pF->setErrorMessage($this->h5pF->t('The file you uploaded is not a valid HTML5 Package (It does not have the .h5p file extension)'));
      H5PCore::deleteFileTree($tmpDir);
      return;
    }
    
    if ($zip->open($tmpPath) === true) {
      $zip->extractTo($tmpDir);
      $zip->close();
    }
    else {
      $this->h5pF->setErrorMessage($this->h5pF->t('The file you uploaded is not a valid HTML5 Package (We are unable to unzip it)'));
      H5PCore::deleteFileTree($tmpDir);
      return;
    }
    unlink($tmpPath);

    // Process content and libraries
    $libraries = array();
    $files = scandir($tmpDir);
    $mainH5pData;
    $libraryJsonData;
    $mainH5pExists = $imageExists = $contentExists = FALSE;
    foreach ($files as $file) {
      if (in_array(substr($file, 0, 1), array('.', '_'))) {
        continue;
      }
      $filePath = $tmpDir . DIRECTORY_SEPARATOR . $file;
      // Check for h5p.json file.
      if (strtolower($file) == 'h5p.json') {
        if ($skipContent === TRUE) {
          continue;
        }
      
        $mainH5pData = $this->getJsonData($filePath);
        if ($mainH5pData === FALSE) {
          $valid = FALSE;
          $this->h5pF->setErrorMessage($this->h5pF->t('Could not parse the main h5p.json file'));
        }
        else {
          $validH5p = $this->isValidH5pData($mainH5pData, $file, $this->h5pRequired, $this->h5pOptional);
          if ($validH5p) {
            $mainH5pExists = TRUE;
          }
          else {
            $valid = FALSE;
            $this->h5pF->setErrorMessage($this->h5pF->t('The main h5p.json file is not valid'));
          }
        }
      }
      // Check for h5p.jpg?
      elseif (strtolower($file) == 'h5p.jpg') {
        $imageExists = TRUE;
      }
      // Content directory holds content.
      elseif ($file == 'content') {
        // We do a separate skipContent check to avoid having the content folder being treated as a library
        if ($skipContent) {
          continue;
        }
        if (!is_dir($filePath)) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Invalid content folder'));
          $valid = FALSE;
          continue;
        }
        $contentJsonData = $this->getJsonData($filePath . DIRECTORY_SEPARATOR . 'content.json');
        if ($contentJsonData === FALSE) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Could not find or parse the content.json file'));
          $valid = FALSE;
          continue;
        }
        else {
          $contentExists = TRUE;
          // In the future we might let the libraries provide validation functions for content.json
        }

        if (!$this->h5pCV->validateContentFiles($filePath)) {
          // validateContentfiles prints error messages itself
          $valid = FALSE;
          continue;
        }
      }

      // The rest should be library folders
      elseif ($this->h5pF->mayUpdateLibraries()) {
         if (!is_dir($filePath)) {
          // Ignore this. Probably a file that shouldn't have been included.
          continue;
        }

        $libraryH5PData = $this->getLibraryData($file, $filePath, $tmpDir);
        
        if ($libraryH5PData !== FALSE) {
          // Library's directory name must be:
          // - <machineName>
          //     - or -
          // - <machineName>-<majorVersion>.<minorVersion>
          // where mcahineName, majorVersion and minorVersion is read from library.json
          if ($libraryH5PData['machineName'] !== $file && H5PCore::libraryToString($libraryH5PData, TRUE) !== $file) {
            $this->h5pF->setErrorMessage($this->h5pF->t('Library directory name must match machineName or machineName-majorVersion.minorVersion (from library.json). (Directory: %directoryName , machineName: %machineName, majorVersion: %majorVersion, minorVersion: %minorVersion)', array(
                '%directoryName' => $file,
                '%machineName' => $libraryH5PData['machineName'],
                '%majorVersion' => $libraryH5PData['majorVersion'],
                '%minorVersion' => $libraryH5PData['minorVersion'])));
            $valid = FALSE;
            continue;
          }
          $libraryH5PData['uploadDirectory'] = $filePath;
          $libraries[H5PCore::libraryToString($libraryH5PData)] = $libraryH5PData;
        }
        else {
          $valid = FALSE;
        }
      }
    }
    if ($skipContent === FALSE) {
      if (!$contentExists) {
        $this->h5pF->setErrorMessage($this->h5pF->t('A valid content folder is missing'));
        $valid = FALSE;
      }
      if (!$mainH5pExists) {
        $this->h5pF->setErrorMessage($this->h5pF->t('A valid main h5p.json file is missing'));
        $valid = FALSE;
      }
    }
    if ($valid) {
      if ($upgradeOnly) {
        // When upgrading, we opnly add allready installed libraries, 
        // and new dependent libraries
        $upgrades = array();
        foreach ($libraries as &$library) {
          // Is this library already installed?
          if ($this->h5pF->getLibraryId($library['machineName'], $library['majorVersion'], $library['minorVersion']) !== FALSE) {
            $upgrades[H5PCore::libraryToString($library)] = $library;
          }
        }
        while ($missingLibraries = $this->getMissingLibraries($upgrades)) {
          foreach ($missingLibraries as $missing) {
            $libString = H5PCore::libraryToString($missing);
            $library = $libraries[$libString];
            if ($library) {
              $upgrades[$libString] = $library;
            }
          }
        }
        
        $libraries = $upgrades;
      }
      
      $this->h5pC->librariesJsonData = $libraries;
      
      if ($skipContent === FALSE) {
        $this->h5pC->mainJsonData = $mainH5pData;
        $this->h5pC->contentJsonData = $contentJsonData;
        $libraries['mainH5pData'] = $mainH5pData; // Check for the dependencies in h5p.json as well as in the libraries
      }
      
      $missingLibraries = $this->getMissingLibraries($libraries);
      foreach ($missingLibraries as $missing) {
        if ($this->h5pF->getLibraryId($missing['machineName'], $missing['majorVersion'], $missing['minorVersion'])) {
          unset($missingLibraries[H5PCore::libraryToString($missing)]);
        }
      }
      
      if (!empty($missingLibraries)) {
        foreach ($missingLibraries as $library) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Missing required library @library', array('@library' => H5PCore::libraryToString($library))));
        }
        if (!$this->h5pF->mayUpdateLibraries()) {
           $this->h5pF->setInfoMessage($this->h5pF->t("Note that the libraries may exist in the file you uploaded, but you're not allowed to upload new libraries. Contact the site administrator about this."));
        }
      }
      $valid = empty($missingLibraries) && $valid;
    }
    if (!$valid) {
      H5PCore::deleteFileTree($tmpDir);
    }
    return $valid;
  }

  /**
   * Validates a H5P library
   *
   * @param string $file
   *  Name of the library folder
   * @param string $filePath
   *  Path to the library folder
   * @param string $tmpDir
   *  Path to the temporary upload directory
   * @return object|boolean
   *  H5P data from library.json and semantics if the library is valid
   *  FALSE if the library isn't valid
   */
  public function getLibraryData($file, $filePath, $tmpDir) {
    if (preg_match('/^[\w0-9\-\.]{1,255}$/i', $file) === 0) {
      $this->h5pF->setErrorMessage($this->h5pF->t('Invalid library name: %name', array('%name' => $file)));
      return FALSE;
    }
    $h5pData = $this->getJsonData($filePath . DIRECTORY_SEPARATOR . 'library.json');
    if ($h5pData === FALSE) {
      $this->h5pF->setErrorMessage($this->h5pF->t('Could not find library.json file with valid json format for library %name', array('%name' => $file)));
      return FALSE;
    }

    // validate json if a semantics file is provided
    $semanticsPath = $filePath . DIRECTORY_SEPARATOR . 'semantics.json';
    if (file_exists($semanticsPath)) {
      $semantics = $this->getJsonData($semanticsPath, TRUE);
      if ($semantics === FALSE) {
        $this->h5pF->setErrorMessage($this->h5pF->t('Invalid semantics.json file has been included in the library %name', array('%name' => $file)));
        return FALSE;
      }
      else {
        $h5pData['semantics'] = $semantics;
      }
    }

    // validate language folder if it exists
    $languagePath = $filePath . DIRECTORY_SEPARATOR . 'language';
    if (is_dir($languagePath)) {
      $languageFiles = scandir($languagePath);
      foreach ($languageFiles as $languageFile) {
        if (in_array($languageFile, array('.', '..'))) {
          continue;
        }
        if (preg_match('/^(-?[a-z]+){1,7}\.json$/i', $languageFile) === 0) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Invalid language file %file in library %library', array('%file' => $languageFile, '%library' => $file)));
          return FALSE;
        }
        $languageJson = $this->getJsonData($languagePath . DIRECTORY_SEPARATOR . $languageFile, TRUE);
        if ($languageJson === FALSE) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Invalid language file %languageFile has been included in the library %name', array('%languageFile' => $languageFile, '%name' => $file)));
          return FALSE;
        }
        $parts = explode('.', $languageFile); // $parts[0] is the language code
        $h5pData['language'][$parts[0]] = $languageJson;
      }
    }

    $validLibrary = $this->isValidH5pData($h5pData, $file, $this->libraryRequired, $this->libraryOptional);

    $validLibrary = $this->h5pCV->validateContentFiles($filePath, TRUE) && $validLibrary;

    if (isset($h5pData['preloadedJs'])) {
      $validLibrary = $this->isExistingFiles($h5pData['preloadedJs'], $tmpDir, $file) && $validLibrary;
    }
    if (isset($h5pData['preloadedCss'])) {
      $validLibrary = $this->isExistingFiles($h5pData['preloadedCss'], $tmpDir, $file) && $validLibrary;
    }
    if ($validLibrary) {
      return $h5pData;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Use the dependency declarations to find any missing libraries
   *
   * @param array $libraries
   *  A multidimensional array of libraries keyed with machineName first and majorVersion second
   * @return array
   *  A list of libraries that are missing keyed with machineName and holds objects with
   *  machineName, majorVersion and minorVersion properties
   */
  private function getMissingLibraries($libraries) {
    $missing = array();
    foreach ($libraries as $library) {
      if (isset($library['preloadedDependencies'])) {
        $missing = array_merge($missing, $this->getMissingDependencies($library['preloadedDependencies'], $libraries));
      }
      if (isset($library['dynamicDependencies'])) {
        $missing = array_merge($missing, $this->getMissingDependencies($library['dynamicDependencies'], $libraries));
      }
      if (isset($library['editorDependencies'])) {
        $missing = array_merge($missing, $this->getMissingDependencies($library['editorDependencies'], $libraries));
      }
    }
    return $missing;
  }

  /**
   * Helper function for getMissingLibraries, searches for dependency required libraries in
   * the provided list of libraries
   *
   * @param array $dependencies
   *  A list of objects with machineName, majorVersion and minorVersion properties
   * @param array $libraries
   *  An array of libraries keyed with machineName
   * @return
   *  A list of libraries that are missing keyed with machineName and holds objects with
   *  machineName, majorVersion and minorVersion properties
   */
  private function getMissingDependencies($dependencies, $libraries) {
    $missing = array();
    foreach ($dependencies as $dependency) {
      if (!isset($libraries[H5PCore::libraryToString($dependency)])) {
        $missing[H5PCore::libraryToString($dependency)] = $dependency;
      }
    }
    return $missing;
  }

  /**
   * Figure out if the provided file paths exists
   *
   * Triggers error messages if files doesn't exist
   *
   * @param array $files
   *  List of file paths relative to $tmpDir
   * @param string $tmpDir
   *  Path to the directory where the $files are stored.
   * @param string $library
   *  Name of the library we are processing
   * @return boolean
   *  TRUE if all the files excists
   */
  private function isExistingFiles($files, $tmpDir, $library) {
    foreach ($files as $file) {
      $path = str_replace(array('/', '\\'), DIRECTORY_SEPARATOR, $file['path']);
      if (!file_exists($tmpDir . DIRECTORY_SEPARATOR . $library . DIRECTORY_SEPARATOR . $path)) {
        $this->h5pF->setErrorMessage($this->h5pF->t('The file "%file" is missing from library: "%name"', array('%file' => $path, '%name' => $library)));
        return FALSE;
      }
    }
    return TRUE;
  }

  /**
   * Validates h5p.json and library.json data
   *
   * Error messages are triggered if the data isn't valid
   *
   * @param array $h5pData
   *  h5p data
   * @param string $library_name
   *  Name of the library we are processing
   * @param array $required
   *  Validation pattern for required properties
   * @param array $optional
   *  Validation pattern for optional properties
   * @return boolean
   *  TRUE if the $h5pData is valid
   */
  private function isValidH5pData($h5pData, $library_name, $required, $optional) {
    $valid = $this->isValidRequiredH5pData($h5pData, $required, $library_name);
    $valid = $this->isValidOptionalH5pData($h5pData, $optional, $library_name) && $valid;

    // Test library core version requirement.  If no requirement is set,
    // this implicitly means 1.0, which shall work on newer versions
    // too.
    if (isset($h5pData['coreApi']) && !empty($h5pData['coreApi'])) {
      if (($h5pData['coreApi']['majorVersion'] > H5PCore::$coreApi['majorVersion']) ||
          (($h5pData['coreApi']['majorVersion'] == H5PCore::$coreApi['majorVersion']) &&
            ($h5pData['coreApi']['minorVersion'] > H5PCore::$coreApi['minorVersion'])))
      {
        $this->h5pF->setErrorMessage(
          $this->h5pF->t('The library "%library_name" requires H5P %requiredVersion, but only H5P %coreApi is installed.',
          array(
            '%library_name' => $library_name,
            '%requiredVersion' => $h5pData['coreApi']['majorVersion'] . '.' . $h5pData['coreApi']['minorVersion'],
            '%coreApi' => H5PCore::$coreApi['majorVersion'] . '.' . H5PCore::$coreApi['minorVersion']
          )));
        $valid = false;
      }
    }
    return $valid;
  }

  /**
   * Helper function for isValidH5pData
   *
   * Validates the optional part of the h5pData
   *
   * Triggers error messages
   *
   * @param array $h5pData
   *  h5p data
   * @param array $requirements
   *  Validation pattern
   * @param string $library_name
   *  Name of the library we are processing
   * @return boolean
   *  TRUE if the optional part of the $h5pData is valid
   */
  private function isValidOptionalH5pData($h5pData, $requirements, $library_name) {
    $valid = TRUE;

    foreach ($h5pData as $key => $value) {
      if (isset($requirements[$key])) {
        $valid = $this->isValidRequirement($value, $requirements[$key], $library_name, $key) && $valid;
      }
      // Else: ignore, a package can have parameters that this library doesn't care about, but that library
      // specific implementations does care about...
    }

    return $valid;
  }

  /**
   * Validate a requirement given as regexp or an array of requirements
   *
   * @param mixed $h5pData
   *  The data to be validated
   * @param mixed $requirement
   *  The requirement the data is to be validated against, regexp or array of requirements
   * @param string $library_name
   *  Name of the library we are validating(used in error messages)
   * @param string $property_name
   *  Name of the property we are validating(used in error messages)
   * @return boolean
   *  TRUE if valid, FALSE if invalid
   */
  private function isValidRequirement($h5pData, $requirement, $library_name, $property_name) {
    $valid = TRUE;

    if (is_string($requirement)) {
      if ($requirement == 'boolean') {
        if (!is_bool($h5pData)) {
         $this->h5pF->setErrorMessage($this->h5pF->t("Invalid data provided for %property in %library. Boolean expected.", array('%property' => $property_name, '%library' => $library_name)));
         $valid = FALSE;
        }
      }
      else {
        // The requirement is a regexp, match it against the data
        if (is_string($h5pData) || is_int($h5pData)) {
          if (preg_match($requirement, $h5pData) === 0) {
             $this->h5pF->setErrorMessage($this->h5pF->t("Invalid data provided for %property in %library", array('%property' => $property_name, '%library' => $library_name)));
             $valid = FALSE;
          }
        }
        else {
          $this->h5pF->setErrorMessage($this->h5pF->t("Invalid data provided for %property in %library", array('%property' => $property_name, '%library' => $library_name)));
          $valid = FALSE;
        }
      }
    }
    elseif (is_array($requirement)) {
      // We have sub requirements
      if (is_array($h5pData)) {
        if (is_array(current($h5pData))) {
          foreach ($h5pData as $sub_h5pData) {
            $valid = $this->isValidRequiredH5pData($sub_h5pData, $requirement, $library_name) && $valid;
          }
        }
        else {
          $valid = $this->isValidRequiredH5pData($h5pData, $requirement, $library_name) && $valid;
        }
      }
      else {
        $this->h5pF->setErrorMessage($this->h5pF->t("Invalid data provided for %property in %library", array('%property' => $property_name, '%library' => $library_name)));
        $valid = FALSE;
      }
    }
    else {
      $this->h5pF->setErrorMessage($this->h5pF->t("Can't read the property %property in %library", array('%property' => $property_name, '%library' => $library_name)));
      $valid = FALSE;
    }
    return $valid;
  }

  /**
   * Validates the required h5p data in libraray.json and h5p.json
   *
   * @param mixed $h5pData
   *  Data to be validated
   * @param array $requirements
   *  Array with regexp to validate the data against
   * @param string $library_name
   *  Name of the library we are validating (used in error messages)
   * @return boolean
   *  TRUE if all the required data exists and is valid, FALSE otherwise
   */
  private function isValidRequiredH5pData($h5pData, $requirements, $library_name) {
    $valid = TRUE;
    foreach ($requirements as $required => $requirement) {
      if (is_int($required)) {
        // We have an array of allowed options
        return $this->isValidH5pDataOptions($h5pData, $requirements, $library_name);
      }
      if (isset($h5pData[$required])) {
        $valid = $this->isValidRequirement($h5pData[$required], $requirement, $library_name, $required) && $valid;
      }
      else {
        $this->h5pF->setErrorMessage($this->h5pF->t('The required property %property is missing from %library', array('%property' => $required, '%library' => $library_name)));
        $valid = FALSE;
      }
    }
    return $valid;
  }

  /**
   * Validates h5p data against a set of allowed values(options)
   *
   * @param array $selected
   *  The option(s) that has been specified
   * @param array $allowed
   *  The allowed options
   * @param string $library_name
   *  Name of the library we are validating (used in error messages)
   * @return boolean
   *  TRUE if the specified data is valid, FALSE otherwise
   */
  private function isValidH5pDataOptions($selected, $allowed, $library_name) {
    $valid = TRUE;
    foreach ($selected as $value) {
      if (!in_array($value, $allowed)) {
        $this->h5pF->setErrorMessage($this->h5pF->t('Illegal option %option in %library', array('%option' => $value, '%library' => $library_name)));
        $valid = FALSE;
      }
    }
    return $valid;
  }

  /**
   * Fetch json data from file
   *
   * @param string $filePath
   *  Path to the file holding the json string
   * @param boolean $return_as_string
   *  If true the json data will be decoded in order to validate it, but will be
   *  returned as string
   * @return mixed
   *  FALSE if the file can't be read or the contents can't be decoded
   *  string if the $return as string parameter is set
   *  array otherwise
   */
  private function getJsonData($filePath, $return_as_string = FALSE) {
    $json = file_get_contents($filePath);
    if ($json === FALSE) {
      return FALSE; // Cannot read from file.
    }
    $jsonData = json_decode($json, TRUE);
    if ($jsonData === NULL) {
      return FALSE; // JSON cannot be decoded or the recursion limit has been reached.
    }
    return $return_as_string ? $json : $jsonData;
  }

  /**
   * Helper function that copies an array
   *
   * @param array $array
   *  The array to be copied
   * @return array
   *  Copy of $array. All objects are cloned
   */
  private function arrayCopy(array $array) {
    $result = array();
    foreach ($array as $key => $val) {
      if (is_array($val)) {
        $result[$key] = arrayCopy($val);
      }
      elseif (is_object($val)) {
        $result[$key] = clone $val;
      }
      else {
        $result[$key] = $val;
      }
    }
    return $result;
  }
}

/**
 * This class is used for saving H5P files
 */
class H5PStorage {

  public $h5pF;
  public $h5pC;
  
  public $contentId = NULL; // Quick fix so WP can get ID of new content.

  /**
   * Constructor for the H5PStorage
   *
   * @param object $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   */
  public function __construct($H5PFramework, $H5PCore) {
    $this->h5pF = $H5PFramework;
    $this->h5pC = $H5PCore;
  }

  /**
   * Saves a H5P file
   *
   * @param int $contentId
   *  The id of the content we are saving
   * @param int $contentMainId
   *  The main id for the content we are saving. This is used if the framework
   *  we're integrating with uses content id's and version id's
   * @return boolean
   *  TRUE if one or more libraries were updated
   *  FALSE otherwise
   */
  public function savePackage($content = NULL, $contentMainId = NULL, $skipContent = FALSE, $upgradeOnly = FALSE) {
    // Save the libraries we processed during validation
    $library_saved = FALSE;
    $upgradedLibsCount = 0;
    $mayUpdateLibraries = $this->h5pF->mayUpdateLibraries();
    
    foreach ($this->h5pC->librariesJsonData as &$library) {
      $libraryId = $this->h5pF->getLibraryId($library['machineName'], $library['majorVersion'], $library['minorVersion']);
      $library['saveDependencies'] = TRUE;
      
      if (!$libraryId) {
        $new = TRUE;
      }
      elseif ($this->h5pF->isPatchedLibrary($library)) {
        $new = FALSE;
        $library['libraryId'] = $libraryId;
      }
      else {
        $library['libraryId'] = $libraryId;
        // We already have the same or a newer version of this library
        $library['saveDependencies'] = FALSE;
        continue;
      }

      if (!$mayUpdateLibraries) {
        // This shouldn't happen, but just to be safe...
        continue;
      }

      $this->h5pF->saveLibraryData($library, $new);

      $libraries_path = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR . 'libraries';
      if (!is_dir($libraries_path)) {
        mkdir($libraries_path, 0777, true);
      }
      $destination_path = $libraries_path . DIRECTORY_SEPARATOR . H5PCore::libraryToString($library, TRUE);
      H5PCore::deleteFileTree($destination_path);
      rename($library['uploadDirectory'], $destination_path);

      $library_saved = TRUE;
    }

    foreach ($this->h5pC->librariesJsonData as &$library) {
      if ($library['saveDependencies']) {
        $this->h5pF->deleteLibraryDependencies($library['libraryId']);
        if (isset($library['preloadedDependencies'])) {
          $this->h5pF->saveLibraryDependencies($library['libraryId'], $library['preloadedDependencies'], 'preloaded');
        }
        if (isset($library['dynamicDependencies'])) {
          $this->h5pF->saveLibraryDependencies($library['libraryId'], $library['dynamicDependencies'], 'dynamic');
        }
        if (isset($library['editorDependencies'])) {
          $this->h5pF->saveLibraryDependencies($library['libraryId'], $library['editorDependencies'], 'editor');
        }
        
        // Make sure libraries dependencies, parameter filtering and export files gets regenerated for all content who uses this library.
        $this->h5pF->invalidateContentCache($library['libraryId']);
        
        $upgradedLibsCount++;
      }
    }
    
    if (!$skipContent) {
      $current_path = $this->h5pF->getUploadedH5pFolderPath() . DIRECTORY_SEPARATOR . 'content';
      
      // Find out which libraries are used by this package/content
      $librariesInUse = array();
      $this->h5pC->findLibraryDependencies($librariesInUse, $this->h5pC->mainJsonData);
      
      // Save content
      if ($content === NULL) {
        $content = array();
      }
      if (!is_array($content)) {
        $content = array('id' => $content);
      }
      $content['library'] = $librariesInUse['preloaded-' . $this->h5pC->mainJsonData['mainLibrary']]['library'];
      $content['params'] = file_get_contents($current_path . DIRECTORY_SEPARATOR . 'content.json');
      $contentId = $this->h5pC->saveContent($content, $contentMainId);
      $this->contentId = $contentId;

      $contents_path = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR . 'content';
      if (!is_dir($contents_path)) {
        mkdir($contents_path, 0777, true);
      }
      
      // Move the content folder
      $destination_path = $contents_path . DIRECTORY_SEPARATOR . $contentId;
      @rename($current_path, $destination_path);
      
      // Save the content library dependencies
      $this->h5pF->saveLibraryUsage($contentId, $librariesInUse);
      H5PCore::deleteFileTree($this->h5pF->getUploadedH5pFolderPath());
    }
    
    // Update supported library list if neccessary:
    $this->h5pC->validateLibrarySupport(TRUE);
    
    if ($upgradeOnly) {
      // TODO - support translation
      $this->h5pF->setInfoMessage($upgradedLibsCount . ' libraries were upgraded!');
    }

    return $library_saved;
  }
  
  /**
   * Delete an H5P package
   *
   * @param int $contentId
   *  The content id
   */
  public function deletePackage($contentId) {
    H5PCore::deleteFileTree($this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR . 'content' . DIRECTORY_SEPARATOR . $contentId);
    $this->h5pF->deleteContentData($contentId);
  }

  /**
   * Update an H5P package
   *
   * @param int $contentId
   *  The content id
   * @param int $contentMainId
   *  The content main id (used by frameworks supporting revisioning)
   * @return boolean
   *  TRUE if one or more libraries were updated
   *  FALSE otherwise
   */
  public function updatePackage($contentId, $contentMainId = NULL) {
    $this->deletePackage($contentId);
    return $this->savePackage($contentId, $contentMainId);
  }

  /**
   * Copy/clone an H5P package
   *
   * May for instance be used if the content is beeing revisioned without
   * uploading a new H5P package
   *
   * @param int $contentId
   *  The new content id
   * @param int $copyFromId
   *  The content id of the content that should be cloned
   * @param int $contentMainId
   *  The main id of the new content (used in frameworks that support revisioning)
   */
  public function copyPackage($contentId, $copyFromId, $contentMainId = NULL) {
    $source_path = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR . 'content' . DIRECTORY_SEPARATOR . $copyFromId;
    $destination_path = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR . 'content' . DIRECTORY_SEPARATOR . $contentId;
    $this->h5pC->copyFileTree($source_path, $destination_path);

    $this->h5pF->copyLibraryUsage($contentId, $copyFromId, $contentMainId);
  }
}

/**
* This class is used for exporting zips
*/
Class H5PExport {
  public $h5pF;
  public $h5pC;

  /**
   * Constructor for the H5PExport
   *
   * @param object $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   * @param H5PCore
   *  Reference to an insance of H5PCore
   */
  public function __construct($H5PFramework, $H5PCore) {
    $this->h5pF = $H5PFramework;
    $this->h5pC = $H5PCore;
  }
  
  /**
   * Return path to h5p package.
   *
   * Creates package if not already created
   *
   * @param array $content
   * @return string
   */
  public function createExportFile($content) {
    $h5pDir = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR;
    $tempPath = $h5pDir . 'temp' . DIRECTORY_SEPARATOR . $content['id'];
    $zipPath = $h5pDir . 'exports' . DIRECTORY_SEPARATOR . $content['id'] . '.h5p';
    
    // Temp dir to put the h5p files in
    @mkdir($tempPath, 0777, TRUE);
    @mkdir($h5pDir . 'exports', 0777, TRUE);

    // Create content folder
    if ($this->h5pC->copyFileTree($h5pDir . 'content' . DIRECTORY_SEPARATOR . $content['id'], $tempPath . DIRECTORY_SEPARATOR . 'content') === FALSE) {
      return FALSE;
    }
    file_put_contents($tempPath . DIRECTORY_SEPARATOR . 'content' . DIRECTORY_SEPARATOR . 'content.json', $content['params']);

    // Make embedTypes into an array
    $embedTypes = explode(', ', $content['embedType']); // Won't content always be embedded in one way?

    // Build h5p.json
    $h5pJson = array (
      'title' => $content['title'],
      'language' => $content['language'],
      'mainLibrary' => $content['library']['name'],
      'embedTypes' => $embedTypes,
    );

    // Add dependencies to h5p
    foreach ($content['dependencies'] as $dependency) {
      $library = $dependency['library'];
      
      // Copy library to h5p
      $source = isset($library['path']) ? $library['path'] : $h5pDir . 'libraries' . DIRECTORY_SEPARATOR . H5PCore::libraryToString($library, TRUE);
      $destination = $tempPath . DIRECTORY_SEPARATOR . $library['machineName'];
      $this->h5pC->copyFileTree($source, $destination);

      // Do not add editor dependencies to h5p json.
      if ($dependency['type'] === 'editor') {
        continue; 
      }

      $h5pJson[$dependency['type'] . 'Dependencies'][] = array(
        'machineName' => $library['machineName'],
        'majorVersion' => $library['majorVersion'],
        'minorVersion' => $library['minorVersion']
      );
    }

    // Save h5p.json
    $results = print_r(json_encode($h5pJson), true);
    file_put_contents($tempPath . DIRECTORY_SEPARATOR . 'h5p.json', $results);

    // Create new zip instance.
    $zip = new ZipArchive();
    $zip->open($zipPath, ZIPARCHIVE::CREATE);

    // Get all files and folders in $tempPath
    $iterator = new RecursiveIteratorIterator(new RecursiveDirectoryIterator($tempPath . DIRECTORY_SEPARATOR));
    // Add files to zip
    foreach ($iterator as $key => $value) {
      $test = '.';
      // Do not add the folders '.' and '..' to the zip. This will make zip invalid.
      if (substr_compare($key, $test, -strlen($test), strlen($test)) !== 0) {
        // Get files path in $tempPath
        $filePath = explode($tempPath . DIRECTORY_SEPARATOR, $key);
        // Add files to the zip with the intended file-structure
        $zip->addFile($key, $filePath[1]);
      }
    }
    // Close zip and remove temp dir
    $zip->close();
    H5PCore::deleteFileTree($tempPath);
  }

  /**
   * Delete .h5p file
   *
   * @param int/string $contentId
   *  Identifier for the H5P
   */
  public function deleteExport($contentId) {
    $h5pDir = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR;
    $zipPath = $h5pDir . 'exports' . DIRECTORY_SEPARATOR . $contentId . '.h5p';
    if (file_exists($zipPath)) {
      unlink($zipPath);
    }
  }

  /**
   * Add editor libraries to the list of libraries
   *
   * These aren't supposed to go into h5p.json, but must be included with the rest
   * of the libraries
   *
   * @param array $libraries
   *  List of libraries keyed by machineName
   * @param array $editorLibraries
   *  List of libraries keyed by machineName
   * @return List of libraries keyed by machineName
   */
  private function addEditorLibraries($libraries, $editorLibraries) {
    foreach ($editorLibraries as $editorLibrary) {
      $libraries[$editorLibrary['machineName']] = $editorLibrary;      
    }
    return $libraries;
  }
}

/**
 * Functions and storage shared by the other H5P classes
 */
class H5PCore {

  public static $coreApi = array(
    'majorVersion' => 1,
    'minorVersion' => 3
  );
  public static $styles = array(
    'styles/h5p.css',
  );
  public static $scripts = array(
    'js/jquery.js',
    'js/h5p.js',
  );
  public static $adminScripts = array(
    'js/jquery.js',
    'js/h5p-utils.js',
  );

  public static $defaultContentWhitelist = 'json png jpg jpeg gif bmp tif tiff svg eot ttf woff otf webm mp4 ogg mp3 txt pdf rtf doc docx xls xlsx ppt pptx odt ods odp xml csv diff patch swf md textile';
  public static $defaultLibraryWhitelistExtras = 'js css';

  public $librariesJsonData, $contentJsonData, $mainJsonData, $h5pF, $path, $development_mode, $h5pD;
  private $exportEnabled;

  /**
   * Constructor for the H5PCore
   *
   * @param object $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   * @param string $path H5P file storage directory.
   * @param string $language code. Defaults to english.
   * @param boolean $export enabled?
   * @param int $development_mode mode.
   */
  public function __construct($H5PFramework, $path, $language = 'en', $export = FALSE, $development_mode = H5PDevelopment::MODE_NONE) {
    $this->h5pF = $H5PFramework;
    
    $this->h5pF = $H5PFramework;
    $this->path = $path;
    $this->exportEnabled = $export;
    $this->development_mode = $development_mode;
    
    if ($development_mode & H5PDevelopment::MODE_LIBRARY) {
      $this->h5pD = new H5PDevelopment($this->h5pF, $path, $language);
    }
  }

  /**
   * Save content and clear cache.
   * 
   * @param array $content
   * @return int Content ID
   */
  public function saveContent($content, $contentMainId) {
    if (isset($content['id'])) {
      $this->h5pF->updateContent($content, $contentMainId);
    }
    else {
      $content['id'] = $this->h5pF->insertContent($content, $contentMainId); 
    }
    
    $this->h5pF->cacheDel('parameters', $content['id']);
    
    return $content['id'];
  }
  
  /**
   * Load content.
   *
   * @param int $id for content.
   * @return object
   */
  public function loadContent($id) {
    $content = $this->h5pF->loadContent($id);
    
    if ($content !== NULL) {
      $content['library'] = array(
        'id' => $content['libraryId'],
        'name' => $content['libraryName'],
        'majorVersion' => $content['libraryMajorVersion'],
        'minorVersion' => $content['libraryMinorVersion'],
        'embedTypes' => $content['libraryEmbedTypes'],
        'fullscreen' => $content['libraryFullscreen'],
      );
      unset($content['libraryId'], $content['libraryName'], $content['libraryEmbedTypes'], $content['libraryFullscreen']);
      
//      // TODO: Move to filterParameters?
//      if ($this->development_mode & H5PDevelopment::MODE_CONTENT) {
//        // TODO: Remove Drupal specific stuff
//        $json_content_path = file_create_path(file_directory_path() . '/' . variable_get('h5p_default_path', 'h5p') . '/content/' . $id . '/content.json');
//        if (file_exists($json_content_path) === TRUE) {
//          $json_content = file_get_contents($json_content_path);
//          if (json_decode($json_content, TRUE) !== FALSE) {
//            drupal_set_message(t('Invalid json in json content'), 'warning');
//          }
//          $content['params'] = $json_content;
//        }
//      }
    }
    
    return $content;
  }
  
  /**
   * Filter content run parameters, rebuild content dependecy cache and export file.
   * 
   * @param Object $content
   * @return Object NULL on failure.
   */
  public function filterParameters($content) {
    $params = $this->h5pF->cacheGet('parameters', $content['id']);
    if ($params !== NULL) {
      return $params;
    }
    
    // Validate and filter against main library semantics.
    $validator = new H5PContentValidator($this->h5pF, $this);
    $params = (object) array(
      'library' => H5PCore::libraryToString($content['library']),
      'params' => json_decode($content['params'])
    );
    $validator->validateLibrary($params, (object) array('options' => array($params->library)));

    $params = json_encode($params->params);
  
    // Update content dependencies.
    $content['dependencies'] = $validator->getDependencies();
    $this->h5pF->deleteLibraryUsage($content['id']);
    $this->h5pF->saveLibraryUsage($content['id'], $content['dependencies']);
    
    if ($this->exportEnabled) {
      // Recreate export file
      $exporter = new H5PExport($this->h5pF, $this);
      $exporter->createExportFile($content);
      
      // TODO: Should we rather create the file once first accessed, like imagecache?
    }

    // Cache.
    $this->h5pF->cacheSet('parameters', $content['id'], $params);
    return $params;
  }
  
  /**
   * Find the files required for this content to work.
   *
   * @param int $id for content.
   * @return array
   */
  public function loadContentDependencies($id, $type = NULL) {
    $dependencies = $this->h5pF->loadContentDependencies($id, $type);
  
    if ($this->development_mode & H5PDevelopment::MODE_LIBRARY) {
      $developmentLibraries = $this->h5pD->getLibraries();
      
      foreach ($dependencies as $key => $dependency) {
        $libraryString = H5PCore::libraryToString($dependency);
        if (isset($developmentLibraries[$libraryString])) {
          $developmentLibraries[$libraryString]['dependencyType'] = $dependencies[$key]['dependencyType'];
          $dependencies[$key] = $developmentLibraries[$libraryString];
        }
      }
    }
    
    return $dependencies;
  }
  
  /**
   * Get all dependency assets of the given type
   * 
   * @param array $dependency
   * @param string $type
   * @param array $assets
   */
  private function getDependencyAssets($dependency, $type, &$assets) {
    // Check if dependency has any files of this type
    if (empty($dependency[$type]) || $dependency[$type][0] === '') {
      return;
    }
    
    // Check if we should skip CSS.
    if ($type === 'preloadedCss' && (isset($dependency['dropCss']) && $dependency['dropCss'] === '1')) {
      return;
    }
    
    foreach ($dependency[$type] as $file) {
      $assets[] = (object) array(
        'path' => $dependency['path'] . '/' . trim(is_array($file) ? $file['path'] : $file),
        'version' => $dependency['version']
      );
    }
  }
  
  /**
   * Combines path with cache buster / version.
   * 
   * @param array $assets
   * @return array
   */
  public function getAssetsUrls($assets) {
    $urls = array();
    
    foreach ($assets as $asset) {
      $urls[] = $asset->path . $asset->version;
    }
    
    return $urls;
  }
  
  /**
   * Return file paths for all dependecies files.
   *
   * @param array $dependencies
   * @return array files.
   */
  public function getDependenciesFiles($dependencies) {
    $files = array(
      'scripts' => array(),
      'styles' => array()
    );
    foreach ($dependencies as $dependency) {
      if (isset($dependency['path']) === FALSE) {
        $dependency['path'] = $this->path . '/libraries/' . H5PCore::libraryToString($dependency, TRUE);
        $dependency['preloadedJs'] = explode(',', $dependency['preloadedJs']);
        $dependency['preloadedCss'] = explode(',', $dependency['preloadedCss']);
      }
      
      $dependency['version'] = "?ver={$dependency['majorVersion']}.{$dependency['minorVersion']}.{$dependency['patchVersion']}";
      $this->getDependencyAssets($dependency, 'preloadedJs', $files['scripts']);
      $this->getDependencyAssets($dependency, 'preloadedCss', $files['styles']);
    }
    return $files;
  }
  
  /**
   * Load library semantics.
   *
   * @return string
   */
  public function loadLibrarySemantics($name, $majorVersion, $minorVersion) {
    $semantics = NULL;
    if ($this->development_mode & H5PDevelopment::MODE_LIBRARY) {
      // Try to load from dev lib
      $semantics = $this->h5pD->getSemantics($name, $majorVersion, $minorVersion);
    }
    
    if ($semantics === NULL) {
      // Try to load from DB.
      $semantics = $this->h5pF->loadLibrarySemantics($name, $majorVersion, $minorVersion);
    }
    
    if ($semantics !== NULL) {
      $semantics = json_decode($semantics);
      $this->h5pF->alterLibrarySemantics($semantics, $name, $majorVersion, $minorVersion);
    }
    
    return $semantics;
  }
  
  /**
   * Load library.
   *
   * @return array or null.
   */
  public function loadLibrary($name, $majorVersion, $minorVersion) {
    $library = NULL;
    if ($this->development_mode & H5PDevelopment::MODE_LIBRARY) {
      // Try to load from dev
      $library = $this->h5pD->getLibrary($name, $majorVersion, $minorVersion);
      if ($library !== NULL) {
        $library['semantics'] = $this->h5pD->getSemantics($name, $majorVersion, $minorVersion);
      }
    }
    
    if ($library === NULL) {
      // Try to load from DB.
      $library = $this->h5pF->loadLibrary($name, $majorVersion, $minorVersion);
    }
  
    return $library;
  }
  
  /**
   * Deletes a library
   * 
   * @param unknown $libraryId
   */
  public function deleteLibrary($libraryId) {
    $this->h5pF->deleteLibrary($libraryId);
    
    // Force update of unsupported libraries list:
    $this->validateLibrarySupport(TRUE);
  }
  
  /**
   * Recursive. Goes through the dependency tree for the given library and 
   * adds all the dependencies to the given array in a flat format.
   * 
   * @param array $librariesUsed Flat list of all dependencies.
   * @param array $library To find all dependencies for.
   * @param bool $editor Used interally to force all preloaded sub dependencies of an editor dependecy to be editor dependencies.
   */
  public function findLibraryDependencies(&$dependencies, $library, $editor = FALSE) {
    foreach (array('dynamic', 'preloaded', 'editor') as $type) {
      $property = $type . 'Dependencies';
      if (!isset($library[$property])) {
        continue; // Skip, no such dependencies.
      }
      
      if ($type === 'preloaded' && $editor === TRUE) {
        // All preloaded dependencies of an editor library is set to editor.
        $type = 'editor';
      }
      
      foreach ($library[$property] as $dependency) {
        $dependencyKey = $type . '-' . $dependency['machineName'];
        if (isset($dependencies[$dependencyKey]) === TRUE) {
          continue; // Skip, already have this.
        }
        
        $dependencyLibrary = $this->loadLibrary($dependency['machineName'], $dependency['majorVersion'], $dependency['minorVersion']);
        if ($dependencyLibrary) {
          $dependencies[$dependencyKey] = array(
            'library' => $dependencyLibrary,
            'type' => $type
          );
          $this->findLibraryDependencies($dependencies, $dependencyLibrary, $type === 'editor');
        }
        else {
          // This site is missing a dependency!
          $this->h5pF->setErrorMessage($this->h5pF->t('Missing dependency @dep required by @lib.', array('@dep' => H5PCore::libraryToString($dependency), '@lib' => H5PCore::libraryToString($library))));
        }
      }
    }
  }

  /**
   * Check if a library is of the version we're looking for
   *
   * Same verision means that the majorVersion and minorVersion is the same
   *
   * @param array $library
   *  Data from library.json
   * @param array $dependency
   *  Definition of what library we're looking for
   * @return boolean
   *  TRUE if the library is the same version as the dependency
   *  FALSE otherwise
   */
  public function isSameVersion($library, $dependency) {
    if ($library['machineName'] != $dependency['machineName']) {
      return FALSE;
    }
    if ($library['majorVersion'] != $dependency['majorVersion']) {
      return FALSE;
    }
    if ($library['minorVersion'] != $dependency['minorVersion']) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Recursive function for removing directories.
   *
   * @param string $dir
   *  Path to the directory we'll be deleting
   * @return boolean
   *  Indicates if the directory existed.
   */
  public static function deleteFileTree($dir) {
    if (!is_dir($dir)) {
      return;
    }
    $files = array_diff(scandir($dir), array('.','..'));
    foreach ($files as $file) {
      (is_dir("$dir/$file")) ? self::deleteFileTree("$dir/$file") : unlink("$dir/$file");
    }
    return rmdir($dir);
  }

  /**
   * Recursive function for copying directories.
   *
   * @param string $source
   *  Path to the directory we'll be copying
   * @return boolean
   *  Indicates if the directory existed.
   */
  public function copyFileTree($source, $destination) {
    $dir = opendir($source);

    if ($dir === FALSE) {
      $this->h5pF->setErrorMessage($this->h5pF->t('Unable to copy tree, no such directory: @dir', array('@dir' => $source)));
      return FALSE;
    }

    @mkdir($destination);
    while (false !== ($file = readdir($dir))) {
        if (($file != '.') && ($file != '..')) {
            if (is_dir($source . DIRECTORY_SEPARATOR . $file)) {
              $this->copyFileTree($source . DIRECTORY_SEPARATOR . $file, $destination . DIRECTORY_SEPARATOR . $file);
            }
            else {
              copy($source . DIRECTORY_SEPARATOR . $file,$destination . DIRECTORY_SEPARATOR . $file);
            }
        }
    }
    closedir($dir);
  }

  /**
   * Writes library data as string on the form {machineName} {majorVersion}.{minorVersion}
   *
   * @param array $library
   *  With keys machineName, majorVersion and minorVersion
   * @param boolean $folderName
   *  Use hyphen instead of space in returned string.
   * @return string
   *  On the form {machineName} {majorVersion}.{minorVersion}
   */
  public static function libraryToString($library, $folderName = FALSE) {
    return (isset($library['machineName']) ? $library['machineName'] : $library['name']) . ($folderName ? '-' : ' ') . $library['majorVersion'] . '.' . $library['minorVersion'];
  }

  /**
   * Parses library data from a string on the form {machineName} {majorVersion}.{minorVersion}
   *
   * @param string $libraryString
   *  On the form {machineName} {majorVersion}.{minorVersion}
   * @return array|FALSE
   *  With keys machineName, majorVersion and minorVersion.
   *  Returns FALSE only if string is not parsable in the normal library
   *  string formats "Lib.Name-x.y" or "Lib.Name x.y"
   */
  public static function libraryFromString($libraryString) {
    $re = '/^([\w0-9\-\.]{1,255})[\-\ ]([0-9]{1,5})\.([0-9]{1,5})$/i';
    $matches = array();
    $res = preg_match($re, $libraryString, $matches);
    if ($res) {
      return array(
        'machineName' => $matches[1],
        'majorVersion' => $matches[2],
        'minorVersion' => $matches[3]
      );
    }
    return FALSE;
  }
  
  /**
   * Determine the correct embed type to use.
   *
   * @return string 'div' or 'iframe'.
   */
  public static function determineEmbedType($contentEmbedType, $libraryEmbedTypes) {
    // Detect content embed type
    $embedType = strpos(strtolower($contentEmbedType), 'div') !== FALSE ? 'div' : 'iframe';
    
    if ($libraryEmbedTypes !== NULL && $libraryEmbedTypes !== '') {
      // Check that embed type is available for library
      $embedTypes = strtolower($libraryEmbedTypes);
      if (strpos($embedTypes, $embedType) === FALSE) {
        // Not available, pick default.
        $embedType = strpos($embedTypes, 'div') !== FALSE ? 'div' : 'iframe';
      }  
    }
    
    return $embedType;
  }
  
  /**
   * Get the absolute version for the library as a human readable string.
   * 
   * @param object $library
   * @return string
   */
  public static function libraryVersion($library) {
    return $library->major_version . '.' . $library->minor_version . '.' . $library->patch_version;
  }
  
  /**
   * Detemine which versions content with the given library can be upgraded to.
   * 
   * @param object $library
   * @param array $versions
   * @return array
   */
  public function getUpgrades($library, $versions) {
   $upgrades = array();

   foreach ($versions as $upgrade) {
     if ($upgrade->major_version > $library->major_version || $upgrade->major_version === $library->major_version && $upgrade->minor_version > $library->minor_version) {
       $upgrades[$upgrade->id] = H5PCore::libraryVersion($upgrade);
     }
   }

   return $upgrades;
  }
  
  /**
   * Converts all the properties of the given object or array from
   * snake_case to camelCase. Useful after fetching data from the database.
   * 
   * Note that some databases does not support camelCase.
   * 
   * @param mixed $arr input
   * @param boolean $obj return object
   * @return mixed object or array
   */
  public static function snakeToCamel($arr, $obj = false) {
    $newArr = array();

    foreach ($arr as $key => $val) {
      $next = -1;
      while (($next = strpos($key, '_', $next + 1)) !== FALSE) {
        $key = substr_replace($key, strtoupper($key{$next + 1}), $next, 2);
      }

      $newArr[$key] = $val;
    }

    return $obj ? (object) $newArr : $newArr;
  }
  
  /**
   * Check if currently installed H5P libraries are supported by
   * the current versjon of core. Which versions of which libraries are supported is
   * defined in the library-support.json file.
   *
   * @param boolean If TRUE, unsupported libraries list are rebuilt. If FALSE, list is 
   *                rebuilt only if non-existing
   */
  public function validateLibrarySupport($force = false) {
    if (!($this->h5pF->getUnsupportedLibraries() === NULL || $force)) {
      return;
    }
    
    // Read and parse library-support.json
    $jsonString = file_get_contents(realpath(dirname(__FILE__)).'/library-support.json');
    
    if($jsonString !== FALSE) {
      // Get all libraries installed, check if any of them is not supported:
      $libraries = $this->h5pF->loadLibraries();
      $unsupportedLibraries = array();
      $minimumLibraryVersions = array();
      
      $librariesSupported = json_decode($jsonString, true);
      foreach ($librariesSupported as $library) {
        $minimumLibraryVersions[$library['machineName']]['versions'] = $library['minimumVersions'];
        $minimumLibraryVersions[$library['machineName']]['downloadUrl'] = $library['downloadUrl'];
      }
      
      // Iterate over all installed libraries
      foreach ($libraries as $machine_name => $libraryList) {
        // Check if there are any minimum version requirements for this library
        if (isset($minimumLibraryVersions[$machine_name])) {
          $minimumVersions = $minimumLibraryVersions[$machine_name]['versions'];
          // For each version of this library, check if it is supported
          foreach ($libraryList as $library) {
            if (!self::isLibraryVersionSupported($library, $minimumVersions)) {
              // Current version of this library is not supported
              $unsupportedLibraries[] = array (
                'name' => $library->title,
                'downloadUrl' => $minimumLibraryVersions[$machine_name]['downloadUrl'],
                'currentVersion' => array (
                  'major' => $library->major_version,
                  'minor' => $library->minor_version,
                  'patch' => $library->patch_version,
                )
              );
            }
          }
        }
      }
      
      $this->h5pF->setUnsupportedLibraries(empty($unsupportedLibraries) ? NULL : $unsupportedLibraries);
    }
  }
  
  /**
   * Check if a specific version of a library is supported
   * 
   * @param object library
   * @param array An array containing versions
   * @return boolean TRUE if supported, otherwise FALSE
   */
  private static function isLibraryVersionSupported ($library, $minimumVersions) {
    $major_supported = $minor_supported = $patch_supported = false;
    foreach ($minimumVersions as $minimumVersion) {
      // A library is supported if:
      // --- major is higher than any minimumversion
      // --- minor is higher than any minimumversion for a given major
      // --- major and minor equals and patch is >= supported
      $major_supported |= ($library->major_version > $minimumVersion['major']);
    
      if ($library->major_version == $minimumVersion['major']) {
        $minor_supported |= ($library->minor_version > $minimumVersion['minor']);
      }
    
      if ($library->major_version == $minimumVersion['major'] &&
          $library->minor_version == $minimumVersion['minor']) {
        $patch_supported |= ($library->patch_version >= $minimumVersion['patch']);
      }
    }
    
    return ($patch_supported || $minor_supported || $major_supported);
  }
  
  /**
   * Helper function for creating markup for the unsupported libraries list 
   * 
   * TODO: Make help text translatable
   * 
   * @return string Html
   * */
  public function createMarkupForUnsupportedLibraryList($libraries) {
    $html = '<div><span>The following versions of H5P libraries are not supported anymore:<span><ul>';
    
    foreach ($libraries as $library) {
      $downloadUrl = $library['downloadUrl'];
      $libraryName = $library['name'];
      $currentVersion = $library['currentVersion']['major'] . '.' . $library['currentVersion']['minor'] .'.' . $library['currentVersion']['patch'];
      $html .= "<li><a href=\"$downloadUrl\">$libraryName</a> ($currentVersion)</li>";
    }
    
    $html .= '</ul><span><br>These libraries may cause problems on this site. See <a href="http://h5p.org/releases/h5p-core-1.3">here</a> for more info</div>';
    return $html;
  }
}

/**
 * Functions for validating basic types from H5P library semantics.
 */
class H5PContentValidator {
  public $h5pF;
  public $h5pC;
  private $typeMap;
  private $libraries, $dependencies;

  /**
   * Constructor for the H5PContentValidator
   *
   * @param object $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   * @param object $H5PCore
   *  The main H5PCore instance
   */
  public function __construct($H5PFramework, $H5PCore) {
    $this->h5pF = $H5PFramework;
    $this->h5pC = $H5PCore;
    $this->typeMap = array(
      'text' => 'validateText',
      'number' => 'validateNumber',
      'boolean' => 'validateBoolean',
      'list' => 'validateList',
      'group' => 'validateGroup',
      'file' => 'validateFile',
      'image' => 'validateImage',
      'video' => 'validateVideo',
      'audio' => 'validateAudio',
      'select' => 'validateSelect',
      'library' => 'validateLibrary',
    );
    
    // Keep track of the libraries we load to avoid loading it multiple times.
    $this->libraries = array();
    // TODO: Should this possible be done in core's loadLibrary? This might be done multiple places.
    
    // Keep track of all dependencies for the given content.
    $this->dependencies = array();
  }

  /**
   * Get the flat dependecy tree.
   * 
   * @return array
   */
  public function getDependencies() {
    return $this->dependencies;
  }
  
  /**
   * Validate given text value against text semantics.
   */
  public function validateText(&$text, $semantics) {
    if (!is_string($text)) {
      $text = '';
    }
    if (isset($semantics->tags)) {
      // Not testing for empty array allows us to use the 4 defaults without
      // specifying them in semantics.
      $tags = array_merge(array('div', 'span', 'p', 'br'), $semantics->tags);

      // Add related tags for table etc.
      if (in_array('table', $tags)) {
        $tags = array_merge($tags, array('tr', 'td', 'th', 'colgroup', 'thead', 'tbody', 'tfoot'));
      }
      if (in_array('b', $tags) && ! in_array('strong', $tags)) {
        $tags[] = 'strong';
      }
      if (in_array('i', $tags) && ! in_array('em', $tags)) {
        $tags[] = 'em';
      }
      if (in_array('ul', $tags) || in_array('ol', $tags) && ! in_array('li', $tags)) {
        $tags[] = 'li';
      }
      if (in_array('del', $tags) || in_array('strike', $tags) && ! in_array('s', $tags)) {
        $tags[] = 's';
      }
      // Strip invalid HTML tags.
      $text = $this->filter_xss($text, $tags);
    }
    else {
      // Filter text to plain text.
      $text = htmlspecialchars($text, ENT_QUOTES, 'UTF-8', FALSE);
    }

    // Check if string is within allowed length
    if (isset($semantics->maxLength)) {
      $text = mb_substr($text, 0, $semantics->maxLength);
    }

    // Check if string is according to optional regexp in semantics
    if (!($text === '' && $semantics->optional) && isset($semantics->regexp)) {
      // Escaping '/' found in patterns, so that it does not break regexp fencing.
      $pattern = '/' . str_replace('/', '\\/', $semantics->regexp->pattern) . '/';
      $pattern .= isset($semantics->regexp->modifiers) ? $semantics->regexp->modifiers : '';
      if (preg_match($pattern, $text) === 0) {
        // Note: explicitly ignore return value FALSE, to avoid removing text
        // if regexp is invalid...
        $this->h5pF->setErrorMessage($this->h5pF->t('Provided string is not valid according to regexp in semantics. (value: "%value", regexp: "%regexp")', array('%value' => $text, '%regexp' => $pattern)));
        $text = '';
      }
    }
  }

  /**
   * Validates content files
   *
   * @param string $contentPath
   *  The path containg content files to validate.
   * @return boolean
   *  TRUE if all files are valid
   *  FALSE if one or more files fail validation. Error message should be set accordingly by validator.
   */
  public function validateContentFiles($contentPath, $isLibrary = FALSE) {
    // Scan content directory for files, recurse into sub directories.
    $files = array_diff(scandir($contentPath), array('.','..'));
    $valid = TRUE;
    $whitelist = $this->h5pF->getWhitelist($isLibrary, H5PCore::$defaultContentWhitelist, H5PCore::$defaultLibraryWhitelistExtras);

    $wl_regex = '/\.(' . preg_replace('/ +/i', '|', preg_quote($whitelist)) . ')$/i';

    foreach ($files as $file) {
      $filePath = $contentPath . DIRECTORY_SEPARATOR . $file;
      if (is_dir($filePath)) {
        $valid = $this->validateContentFiles($filePath, $isLibrary) && $valid;
      }
      else {
        // Snipped from drupal 6 "file_validate_extensions".  Using own code
        // to avoid 1. creating a file-like object just to test for the known
        // file name, 2. testing against a returned error array that could
        // never be more than 1 element long anyway, 3. recreating the regex
        // for every file.
        if (!preg_match($wl_regex, mb_strtolower($file))) {
          $this->h5pF->setErrorMessage($this->h5pF->t('File "%filename" not allowed. Only files with the following extensions are allowed: %files-allowed.', array('%filename' => $file, '%files-allowed' => $whitelist)), 'error');
          $valid = FALSE;
        }
      }
    }
    return $valid;
  }

  private function bracketTags($tag) {
    return '<'.$tag.'>';
  }

  /**
   * Validate given value against number semantics
   */
  public function validateNumber(&$number, $semantics) {
    // Validate that $number is indeed a number
    if (!is_numeric($number)) {
      $number = 0;
    }
    // Check if number is within valid bounds. Move within bounds if not.
    if (isset($semantics->min) && $number < $semantics->min) {
      $number = $semantics->min;
    }
    if (isset($semantics->max) && $number > $semantics->max) {
      $number = $semantics->max;
    }
    // Check if number is within allowed bounds even if step value is set.
    if (isset($semantics->step)) {
      $testnumber = $number - (isset($semantics->min) ? $semantics->min : 0);
      $rest = $testnumber % $semantics->step;
      if ($rest !== 0) {
        $number -= $rest;
      }
    }
    // Check if number has proper number of decimals.
    if (isset($semantics->decimals)) {
      $number = round($number, $semantics->decimals);
    }
  }

  /**
   * Validate given value against boolean semantics
   */
  public function validateBoolean(&$bool, $semantics) {
    if (!is_bool($bool)) {
      $bool = FALSE;
    }
  }

   /**
   * Validate select values
   */
  public function validateSelect(&$select, $semantics) {
    $strict = FALSE;
    if (isset($semantics->options) && !empty($semantics->options)) {
      // We have a strict set of options to choose from.
      $strict = TRUE;
      $options = array();
      foreach ($semantics->options as $option) {
        $options[$option->value] = TRUE;
      }
    }

    if (isset($semantics->multiple) && $semantics->multiple) {
      // Multichoice generates array of values. Test each one against valid
      // options, if we are strict.  First make sure we are working on an
      // array.
      if (!is_array($select)) {
        $select = array($select);
      }

      foreach ($select as $key => &$value) {
        if ($strict && !isset($options[$value])) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Invalid selected option in multiselect.'));
          unset($select[$key]);
        }
        else {
          $select[$key] = htmlspecialchars($value, ENT_QUOTES, 'UTF-8', FALSE);
        }
      }
    }
    else {
      // Single mode.  If we get an array in here, we chop off the first
      // element and use that instead.
      if (is_array($select)) {
        $select = $select[0];
      }

      if ($strict && !isset($options[$select])) {
        $this->h5pF->setErrorMessage($this->h5pF->t('Invalid selected option in select.'));
        $select = $semantics->options[0]->value;
      }
      $select = htmlspecialchars($select, ENT_QUOTES, 'UTF-8', FALSE);
    }
  }

  /**
   * Validate given list value agains list semantics.
   * Will recurse into validating each item in the list according to the type.
   */
  public function validateList(&$list, $semantics) {
    $field = $semantics->field;
    $function = $this->typeMap[$field->type];

    // Check that list is not longer than allowed length. We do this before
    // iterating to avoid unneccessary work.
    if (isset($semantics->max)) {
      array_splice($list, $semantics->max);
    }

    if (!is_array($list)) {
      $list = array();
    }

    // Validate each element in list.
    foreach ($list as $key => &$value) {
      if (!is_int($key)) {
        unset($list[$key]);
        continue;
      }
      $this->$function($value, $field);
    }
  }

  // Validate a filelike object, such as video, image, audio and file.
  private function _validateFilelike(&$file, $semantics, $typevalidkeys = array()) {
    // Make sure path and mime does not have any special chars
    $file->path = htmlspecialchars($file->path, ENT_QUOTES, 'UTF-8', FALSE);
    if (isset($file->mime)) {
      $file->mime = htmlspecialchars($file->mime, ENT_QUOTES, 'UTF-8', FALSE);
    }

    // Remove attributes that should not exist, they may contain JSON escape
    // code.
    $validkeys = array_merge(array('path', 'mime', 'copyright'), $typevalidkeys);
    if (isset($semantics->extraAttributes)) {
      $validkeys = array_merge($validkeys, $semantics->extraAttributes); // TODO: Validate extraAttributes
    }
    $this->filterParams($file, $validkeys);
    
    if (isset($file->width)) {
      $file->width = intval($file->width);
    }
    
    if (isset($file->height)) {
      $file->height = intval($file->height);
    }
    
    if (isset($file->codecs)) {
      $file->codecs = htmlspecialchars($file->codecs, ENT_QUOTES, 'UTF-8', FALSE);
    }
    
    if (isset($file->quality)) {
      if (!is_object($file->quality) || !isset($file->quality->level) || !isset($file->quality->label)) {
        unset($file->quality);
      }
      else {
        $this->filterParams($file->quality, array('level', 'label'));
        $file->quality->level = intval($file->quality->level);
        $file->quality->label = htmlspecialchars($file->quality->label, ENT_QUOTES, 'UTF-8', FALSE);
      }
    }
    
    if (isset($file->copyright)) {
      $this->validateGroup($file->copyright, H5PContentValidator::getCopyrightSemantics());
    }
  }

  /**
   * Validate given file data
   */
  public function validateFile(&$file, $semantics) {
    $this->_validateFilelike($file, $semantics);
  }

  /**
   * Validate given image data
   */
  public function validateImage(&$image, $semantics) {
    $this->_validateFilelike($image, $semantics, array('width', 'height'));
  }

  /**
   * Validate given video data
   */
  public function validateVideo(&$video, $semantics) {
    foreach ($video as &$variant) {
      $this->_validateFilelike($variant, $semantics, array('width', 'height', 'codecs', 'quality'));
    }
  }

  /**
   * Validate given audio data
   */
  public function validateAudio(&$audio, $semantics) {
    foreach ($audio as &$variant) {
      $this->_validateFilelike($variant, $semantics);
    }
  }

  /**
   * Validate given group value against group semantics.
   * Will recurse into validating each group member.
   */
  public function validateGroup(&$group, $semantics, $flatten = TRUE) {
    // Groups with just one field are compressed in the editor to only output
    // the child content. (Exemption for fake groups created by
    // "validateBySemantics" above)
    if (count($semantics->fields) == 1 && $flatten) {
      $field = $semantics->fields[0];
      $function = $this->typeMap[$field->type];
      $this->$function($group, $field);
    }
    else {
      foreach ($group as $key => &$value) {
        // Find semantics for name=$key
        $found = FALSE;
        foreach ($semantics->fields as $field) {
          if ($field->name == $key) {
            $function = $this->typeMap[$field->type];
            $found = TRUE;
            break;
          }
        }
        if ($found) {
          if ($function) {
            $this->$function($value, $field);
          }
          else {
            // We have a field type in semantics for which we don't have a
            // known validator.
            $this->h5pF->setErrorMessage($this->h5pF->t('H5P internal error: unknown content type "@type" in semantics. Removing content!', array('@type' => $field->type)));
            unset($group->$key);
          }
        }
        else {
          // If validator is not found, something exists in content that does
          // not have a corresponding semantics field. Remove it.
          $this->h5pF->setErrorMessage($this->h5pF->t('H5P internal error: no validator exists for @key', array('@key' => $key)));
          unset($group->$key);
        }
      }
    }
    foreach ($semantics->fields as $field) {
      if (!(isset($field->optional) && $field->optional)) {
        // Check if field is in group.
        if (! property_exists($group, $field->name)) {
          $this->h5pF->setErrorMessage($this->h5pF->t('No value given for mandatory field ' . $field->name));
        }
      }
    }
  }

  /**
   * Validate given library value against library semantics.
   * Check if provided library is within allowed options.
   *
   * Will recurse into validating the library's semantics too.
   */
  public function validateLibrary(&$value, $semantics) {
    if (!isset($value->library) || !in_array($value->library, $semantics->options)) {
      $this->h5pF->setErrorMessage($this->h5pF->t('Library used in content is not a valid library according to semantics'));
      $value = new stdClass();
      return;
    }
    
    if (!isset($this->libraries[$value->library])) {
      $libspec = H5PCore::libraryFromString($value->library);
      $library = $this->h5pC->loadLibrary($libspec['machineName'], $libspec['majorVersion'], $libspec['minorVersion']);
      $library['semantics'] = json_decode($library['semantics']);
      $this->libraries[$value->library] = $library;

      // Find all dependencies for this library
      $depkey = 'preloaded-' . $libspec['machineName'];
      if (!isset($this->dependencies[$depkey])) {
        $this->dependencies[$depkey] = array(
          'library' => $library,
          'type' => 'preloaded'
        );

        $this->h5pC->findLibraryDependencies($this->dependencies, $library);
      }
    }
    else {
      $library = $this->libraries[$value->library];
    }

    $this->validateGroup($value->params, (object) array(
      'type' => 'group',
      'fields' => $library['semantics'],
    ), FALSE);
    $validkeys = array('library', 'params');
    if (isset($semantics->extraAttributes)) {
      $validkeys = array_merge($validkeys, $semantics->extraAttributes);
    }
    $this->filterParams($value, $validkeys);
  }

  /**
   * Check params for a whitelist of allowed properties
   *
   * @param array/object $params
   * @param array $whitelist
   */
  public function filterParams(&$params, $whitelist) {
    foreach ($params as $key => $value) {
      if (!in_array($key, $whitelist)) {
        unset($params->{$key});
      }
    }
  }

  // XSS filters copied from drupal 7 common.inc. Some modifications done to
  // replace Drupal one-liner functions with corresponding flat PHP.

  /**
   * Filters HTML to prevent cross-site-scripting (XSS) vulnerabilities.
   *
   * Based on kses by Ulf Harnhammar, see http://sourceforge.net/projects/kses.
   * For examples of various XSS attacks, see: http://ha.ckers.org/xss.html.
   *
   * This code does four things:
   * - Removes characters and constructs that can trick browsers.
   * - Makes sure all HTML entities are well-formed.
   * - Makes sure all HTML tags and attributes are well-formed.
   * - Makes sure no HTML tags contain URLs with a disallowed protocol (e.g.
   *   javascript:).
   *
   * @param $string
   *   The string with raw HTML in it. It will be stripped of everything that can
   *   cause an XSS attack.
   * @param $allowed_tags
   *   An array of allowed tags.
   *
   * @return
   *   An XSS safe version of $string, or an empty string if $string is not
   *   valid UTF-8.
   *
   * @ingroup sanitization
   */
  private function filter_xss($string, $allowed_tags = array('a', 'em', 'strong', 'cite', 'blockquote', 'code', 'ul', 'ol', 'li', 'dl', 'dt', 'dd')) {
    if (strlen($string) == 0) {
      return $string;
    }
    // Only operate on valid UTF-8 strings. This is necessary to prevent cross
    // site scripting issues on Internet Explorer 6. (Line copied from
    // drupal_validate_utf8)
    if (preg_match('/^./us', $string) != 1) {
      return '';
    }

    // Store the text format.
    $this->_filter_xss_split($allowed_tags, TRUE);
    // Remove NULL characters (ignored by some browsers).
    $string = str_replace(chr(0), '', $string);
    // Remove Netscape 4 JS entities.
    $string = preg_replace('%&\s*\{[^}]*(\}\s*;?|$)%', '', $string);

    // Defuse all HTML entities.
    $string = str_replace('&', '&amp;', $string);
    // Change back only well-formed entities in our whitelist:
    // Decimal numeric entities.
    $string = preg_replace('/&amp;#([0-9]+;)/', '&#\1', $string);
    // Hexadecimal numeric entities.
    $string = preg_replace('/&amp;#[Xx]0*((?:[0-9A-Fa-f]{2})+;)/', '&#x\1', $string);
    // Named entities.
    $string = preg_replace('/&amp;([A-Za-z][A-Za-z0-9]*;)/', '&\1', $string);
    return preg_replace_callback('%
      (
      <(?=[^a-zA-Z!/])  # a lone <
      |                 # or
      <!--.*?-->        # a comment
      |                 # or
      <[^>]*(>|$)       # a string that starts with a <, up until the > or the end of the string
      |                 # or
      >                 # just a >
      )%x', array($this, '_filter_xss_split'), $string);
  }

  /**
   * Processes an HTML tag.
   *
   * @param $m
   *   An array with various meaning depending on the value of $store.
   *   If $store is TRUE then the array contains the allowed tags.
   *   If $store is FALSE then the array has one element, the HTML tag to process.
   * @param $store
   *   Whether to store $m.
   *
   * @return
   *   If the element isn't allowed, an empty string. Otherwise, the cleaned up
   *   version of the HTML element.
   */
  private function _filter_xss_split($m, $store = FALSE) {
    static $allowed_html;

    if ($store) {
      $allowed_html = array_flip($m);
      return;
    }

    $string = $m[1];

    if (substr($string, 0, 1) != '<') {
      // We matched a lone ">" character.
      return '&gt;';
    }
    elseif (strlen($string) == 1) {
      // We matched a lone "<" character.
      return '&lt;';
    }

    if (!preg_match('%^<\s*(/\s*)?([a-zA-Z0-9]+)([^>]*)>?|(<!--.*?-->)$%', $string, $matches)) {
      // Seriously malformed.
      return '';
    }

    $slash = trim($matches[1]);
    $elem = &$matches[2];
    $attrlist = &$matches[3];
    $comment = &$matches[4];

    if ($comment) {
      $elem = '!--';
    }

    if (!isset($allowed_html[strtolower($elem)])) {
      // Disallowed HTML element.
      return '';
    }

    if ($comment) {
      return $comment;
    }

    if ($slash != '') {
      return "</$elem>";
    }

    // Is there a closing XHTML slash at the end of the attributes?
    $attrlist = preg_replace('%(\s?)/\s*$%', '\1', $attrlist, -1, $count);
    $xhtml_slash = $count ? ' /' : '';

    // Clean up attributes.
    $attr2 = implode(' ', $this->_filter_xss_attributes($attrlist));
    $attr2 = preg_replace('/[<>]/', '', $attr2);
    $attr2 = strlen($attr2) ? ' ' . $attr2 : '';

    return "<$elem$attr2$xhtml_slash>";
  }

  /**
   * Processes a string of HTML attributes.
   *
   * @return
   *   Cleaned up version of the HTML attributes.
   */
  private function _filter_xss_attributes($attr) {
    $attrarr = array();
    $mode = 0;
    $attrname = '';

    while (strlen($attr) != 0) {
      // Was the last operation successful?
      $working = 0;

      switch ($mode) {
        case 0:
          // Attribute name, href for instance.
          if (preg_match('/^([-a-zA-Z]+)/', $attr, $match)) {
            $attrname = strtolower($match[1]);
            $skip = ($attrname == 'style' || substr($attrname, 0, 2) == 'on');
            $working = $mode = 1;
            $attr = preg_replace('/^[-a-zA-Z]+/', '', $attr);
          }
          break;

        case 1:
          // Equals sign or valueless ("selected").
          if (preg_match('/^\s*=\s*/', $attr)) {
            $working = 1; $mode = 2;
            $attr = preg_replace('/^\s*=\s*/', '', $attr);
            break;
          }

          if (preg_match('/^\s+/', $attr)) {
            $working = 1; $mode = 0;
            if (!$skip) {
              $attrarr[] = $attrname;
            }
            $attr = preg_replace('/^\s+/', '', $attr);
          }
          break;

        case 2:
          // Attribute value, a URL after href= for instance.
          if (preg_match('/^"([^"]*)"(\s+|$)/', $attr, $match)) {
            $thisval = $this->filter_xss_bad_protocol($match[1]);

            if (!$skip) {
              $attrarr[] = "$attrname=\"$thisval\"";
            }
            $working = 1;
            $mode = 0;
            $attr = preg_replace('/^"[^"]*"(\s+|$)/', '', $attr);
            break;
          }

          if (preg_match("/^'([^']*)'(\s+|$)/", $attr, $match)) {
            $thisval = $this->filter_xss_bad_protocol($match[1]);

            if (!$skip) {
              $attrarr[] = "$attrname='$thisval'";
            }
            $working = 1; $mode = 0;
            $attr = preg_replace("/^'[^']*'(\s+|$)/", '', $attr);
            break;
          }

          if (preg_match("%^([^\s\"']+)(\s+|$)%", $attr, $match)) {
            $thisval = $this->filter_xss_bad_protocol($match[1]);

            if (!$skip) {
              $attrarr[] = "$attrname=\"$thisval\"";
            }
            $working = 1; $mode = 0;
            $attr = preg_replace("%^[^\s\"']+(\s+|$)%", '', $attr);
          }
          break;
      }

      if ($working == 0) {
        // Not well formed; remove and try again.
        $attr = preg_replace('/
          ^
          (
          "[^"]*("|$)     # - a string that starts with a double quote, up until the next double quote or the end of the string
          |               # or
          \'[^\']*(\'|$)| # - a string that starts with a quote, up until the next quote or the end of the string
          |               # or
          \S              # - a non-whitespace character
          )*              # any number of the above three
          \s*             # any number of whitespaces
          /x', '', $attr);
        $mode = 0;
      }
    }

    // The attribute list ends with a valueless attribute like "selected".
    if ($mode == 1 && !$skip) {
      $attrarr[] = $attrname;
    }
    return $attrarr;
  }

// TODO: Remove Drupal related stuff in docs.

  /**
   * Processes an HTML attribute value and strips dangerous protocols from URLs.
   *   
   * @param $string
   *   The string with the attribute value.
   * @param $decode
   *   (deprecated) Whether to decode entities in the $string. Set to FALSE if the
   *   $string is in plain text, TRUE otherwise. Defaults to TRUE. This parameter
   *   is deprecated and will be removed in Drupal 8. To process a plain-text URI,
   *   call _strip_dangerous_protocols() or check_url() instead.
   *
   * @return
   *   Cleaned up and HTML-escaped version of $string.
   */
  private function filter_xss_bad_protocol($string, $decode = TRUE) {
    // Get the plain text representation of the attribute value (i.e. its meaning).
    // @todo Remove the $decode parameter in Drupal 8, and always assume an HTML
    //   string that needs decoding.
    if ($decode) {
      $string = html_entity_decode($string, ENT_QUOTES, 'UTF-8');
    }
    return htmlspecialchars($this->_strip_dangerous_protocols($string), ENT_QUOTES, 'UTF-8', FALSE);
  }

  /**
   * Strips dangerous protocols (e.g. 'javascript:') from a URI.
   *
   * This function must be called for all URIs within user-entered input prior
   * to being output to an HTML attribute value. It is often called as part of
   * check_url() or filter_xss(), but those functions return an HTML-encoded
   * string, so this function can be called independently when the output needs to
   * be a plain-text string for passing to t(), l(), drupal_attributes(), or
   * another function that will call check_plain() separately.
   *
   * @param $uri
   *   A plain-text URI that might contain dangerous protocols.
   *
   * @return
   *   A plain-text URI stripped of dangerous protocols. As with all plain-text
   *   strings, this return value must not be output to an HTML page without
   *   check_plain() being called on it. However, it can be passed to functions
   *   expecting plain-text strings.
   *
   * @see check_url()
   */
  private function _strip_dangerous_protocols($uri) {
    static $allowed_protocols;

    if (!isset($allowed_protocols)) {
      $allowed_protocols = array_flip(array('ftp', 'http', 'https', 'mailto'));
    }

    // Iteratively remove any invalid protocol found.
    do {
      $before = $uri;
      $colonpos = strpos($uri, ':');
      if ($colonpos > 0) {
        // We found a colon, possibly a protocol. Verify.
        $protocol = substr($uri, 0, $colonpos);
        // If a colon is preceded by a slash, question mark or hash, it cannot
        // possibly be part of the URL scheme. This must be a relative URL, which
        // inherits the (safe) protocol of the base document.
        if (preg_match('![/?#]!', $protocol)) {
          break;
        }
        // Check if this is a disallowed protocol. Per RFC2616, section 3.2.3
        // (URI Comparison) scheme comparison must be case-insensitive.
        if (!isset($allowed_protocols[strtolower($protocol)])) {
          $uri = substr($uri, $colonpos + 1);
        }
      }
    } while ($before != $uri);

    return $uri;
  }
  
  public static function getCopyrightSemantics() {
    static $semantics;
    
    if ($semantics === NULL) {
      $semantics = (object) array(
        'name' => 'copyright',
        'type' => 'group',
        'label' => 'Copyright information',
        'fields' => array(
          (object) array(
            'name' => 'title',
            'type' => 'text',
            'label' => 'Title',
            'placeholder' => 'La Gioconda',
            'optional' => TRUE
          ),
          (object) array(
            'name' => 'author',
            'type' => 'text',
            'label' => 'Author',
            'placeholder' => 'Leonardo da Vinci',
            'optional' => TRUE
          ),
          (object) array(
            'name' => 'year',
            'type' => 'text',
            'label' => 'Year(s)',
            'placeholder' => '1503 - 1517',
            'optional' => TRUE
          ),
          (object) array(
            'name' => 'source',
            'type' => 'text',
            'label' => 'Source',
            'placeholder' => 'http://en.wikipedia.org/wiki/Mona_Lisa',
            'optional' => true,
            'regexp' => (object) array(
              'pattern' => '^http[s]?://.+',
              'modifiers' => 'i'
            )
          ),
          (object) array(
            'name' => 'license',
            'type' => 'select',
            'label' => 'License',
            'default' => 'U',
            'options' => array(
              (object) array(
                'value' => 'U',
                'label' => 'Undisclosed'
              ),
              (object) array(
                'value' => 'CC BY',
                'label' => 'Attribution'
              ),
              (object) array(
                'value' => 'CC BY-SA',
                'label' => 'Attribution-ShareAlike'
              ),
              (object) array(
                'value' => 'CC BY-ND',
                'label' => 'Attribution-NoDerivs'
              ),
              (object) array(
                'value' => 'CC BY-NC',
                'label' => 'Attribution-NonCommercial'
              ),
              (object) array(
                'value' => 'CC BY-NC-SA',
                'label' => 'Attribution-NonCommercial-ShareAlike'
              ),
              (object) array(
                'value' => 'CC BY-NC-ND',
                'label' => 'Attribution-NonCommercial-NoDerivs'
              ),
              (object) array(
                'value' => 'GNU GPL',
                'label' => 'General Public License'
              ),
              (object) array(
                'value' => 'PD',
                'label' => 'Public Domain'
              ),
              (object) array(
                'value' => 'ODC PDDL',
                'label' => 'Public Domain Dedication and Licence'
              ),
              (object) array(
                'value' => 'CC PDM',
                'label' => 'Public Domain Mark'
              ),
              (object) array(
                'value' => 'C',
                'label' => 'Copyright'
              )
            )
          )
        )
      );
    }
    
    return $semantics;
  }
}
