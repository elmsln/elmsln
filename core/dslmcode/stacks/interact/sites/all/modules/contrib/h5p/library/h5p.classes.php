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
   * Stores contentData
   *
   * @param int $contentId
   *  Framework specific id identifying the content
   * @param string $contentJson
   *  The content data that is to be stored
   * @param array $mainJsonData
   *  The data extracted from the h5p.json file
   * @param int $contentMainId
   *  Any contentMainId defined by the framework, for instance to support revisioning
   */
  public function saveContentData($contentId, $contentJson, $mainJsonData, $mainLibraryId, $contentMainId = NULL);

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
   * Loads and decodes library semantics.
   *
   * @param string $machineName
   * @param int $majorVersion
   * @param int $minorVersion
   * @return array|FALSE
   *  Array representing the library with dependency descriptions
   *  FALSE if the library doesn't exist
   */
  public function getLibrarySemantics($machineName, $majorVersion, $minorVersion);

  /**
   * Delete all dependencies belonging to given library
   *
   * @param int $libraryId
   *  Library Id
   */
  public function deleteLibraryDependencies($libraryId);

  /**
   * Get all the data we need to export H5P
   *
   * @param int $contentId
   * ContentID of the node we are going to export
   * @return array
   * An array with all the data needed to export the h5p in the following format:
   *  'contentId' => string/int,
   *  'mainLibrary' => string (machine name for main library),
   *  'embedType' => string,
   *  'libraries' => array(
   *    'machineName' => string,
   *    'majorVersion' => int,
   *    'minorVersion' => int,
   *    'preloaded' => int(0|1),
   * 'editorLibraries' => array(
   *    'machineName' => string,
   *    'majorVersion' => int,
   *    'minorVersion' => int,
   *    'preloaded' => int(0|1),
   */
  public function getExportData($contentId);
  /**
   * Check if export is enabled.
   */
  public function isExportEnabled();
  
  /**
   * Defines getEditorLibraries.
   *
   * @param $machineName Library identifier.
   * @param $majorVersion Library identfier.
   * @param $minorVersion Library identfier.
   * @return array Editor libraries?
   */
  public function getEditorLibraries($machineName, $majorVersion, $minorVersion, $complete = FALSE);
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
  public function isValidPackage() {
    // Create a temporary dir to extract package in.
    $tmpDir = $this->h5pF->getUploadedH5pFolderPath();
    $tmp_path = $this->h5pF->getUploadedH5pPath();

    $valid = TRUE;

    // Extract and then remove the package file.
    $zip = new ZipArchive;
    if ($zip->open($tmp_path) === true) {
      $zip->extractTo($tmpDir);
      $zip->close();
    }
    else {
      $this->h5pF->setErrorMessage($this->h5pF->t('The file you uploaded is not a valid HTML5 Package.'));
      $this->h5pC->delTree($tmpDir);
      return;
    }
    unlink($tmp_path);

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
        $mainH5pData = $this->getJsonData($filePath);
        if ($mainH5pData === FALSE) {
          $valid = FALSE;
          $this->h5pF->setErrorMessage($this->h5pF->t('Could not find or parse the main h5p.json file'));
        }
        else {
          $validH5p = $this->isValidH5pData($mainH5pData, $file, $this->h5pRequired, $this->h5pOptional);
          if ($validH5p) {
            $mainH5pExists = TRUE;
          }
          else {
            $valid = FALSE;
            $this->h5pF->setErrorMessage($this->h5pF->t('Could not find or parse the main h5p.json file'));
          }
        }
      }
      // Check for h5p.jpg?
      elseif (strtolower($file) == 'h5p.jpg') {
        $imageExists = TRUE;
      }
      // Content directory holds content.
      elseif ($file == 'content') {
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

        if ($libraryH5PData) {
          $libraries[$file] = $libraryH5PData;
        }
        else {
          $valid = FALSE;
        }
      }
    }
    if (!$contentExists) {
      $this->h5pF->setErrorMessage($this->h5pF->t('A valid content folder is missing'));
      $valid = FALSE;
    }
    if (!$mainH5pExists) {
      $this->h5pF->setErrorMessage($this->h5pF->t('A valid main h5p.json file is missing'));
      $valid = FALSE;
    }
    if ($valid) {
      $this->h5pC->librariesJsonData = $libraries;
      $this->h5pC->mainJsonData = $mainH5pData;
      $this->h5pC->contentJsonData = $contentJsonData;

      $libraries['mainH5pData'] = $mainH5pData; // Check for the dependencies in h5p.json as well as in the libraries
      $missingLibraries = $this->getMissingLibraries($libraries);
      foreach ($missingLibraries as $missing) {
        if ($this->h5pF->getLibraryId($missing['machineName'], $missing['majorVersion'], $missing['minorVersion'])) {
          unset($missingLibraries[$missing['machineName']]);
        }
      }
      if (!empty($missingLibraries)) {
        foreach ($missingLibraries as $library) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Missing required library @library', array('@library' => $this->h5pC->libraryToString($library))));
        }
        if (!$this->h5pF->mayUpdateLibraries()) {
           $this->h5pF->setInfoMessage($this->h5pF->t("Note that the libraries may exist in the file you uploaded, but you're not allowed to upload new libraries. Contact the site administrator about this."));
        }
      }
      $valid = empty($missingLibraries) && $valid;
    }
    if (!$valid) {
      $this->h5pC->delTree($tmpDir);
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
      if (isset($libraries[$dependency['machineName']])) {
        if (!$this->h5pC->isSameVersion($libraries[$dependency['machineName']], $dependency)) {
          $missing[$dependency['machineName']] = $dependency;
        }
      }
      else {
        $missing[$dependency['machineName']] = $dependency;
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
  public function savePackage($contentId, $contentMainId = NULL) {
    // Save the libraries we processed during validation
    $library_saved = FALSE;
    $mayUpdateLibraries = $this->h5pF->mayUpdateLibraries();
    foreach ($this->h5pC->librariesJsonData as $key => &$library) {
      $libraryId = $this->h5pF->getLibraryId($key, $library['majorVersion'], $library['minorVersion']);
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

      $current_path = $this->h5pF->getUploadedH5pFolderPath() . DIRECTORY_SEPARATOR . $key;
      $destination_path = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR . 'libraries' . DIRECTORY_SEPARATOR . $this->h5pC->libraryToString($library, TRUE);
      $this->h5pC->delTree($destination_path);
      rename($current_path, $destination_path);

      $library_saved = TRUE;
    }

    foreach ($this->h5pC->librariesJsonData as $key => &$library) {
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
      }
    }
    // Move the content folder
    $current_path = $this->h5pF->getUploadedH5pFolderPath() . DIRECTORY_SEPARATOR . 'content';
    $destination_path = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR . 'content' . DIRECTORY_SEPARATOR . $contentId;
    rename($current_path, $destination_path);

    // Save what libraries is beeing used by this package/content
    $librariesInUse = array();
    $this->getLibraryUsage($librariesInUse, $this->h5pC->mainJsonData);
    $this->h5pF->saveLibraryUsage($contentId, $librariesInUse);
    $this->h5pC->delTree($this->h5pF->getUploadedH5pFolderPath());

    // Save the data in content.json
    $contentJson = file_get_contents($destination_path . DIRECTORY_SEPARATOR . 'content.json');
    $mainLibraryId = $librariesInUse[$this->h5pC->mainJsonData['mainLibrary']]['library']['libraryId'];
    $this->h5pF->saveContentData($contentId, $contentJson, $this->h5pC->mainJsonData, $mainLibraryId, $contentMainId);

    return $library_saved;
  }

  /**
   * Delete an H5P package
   *
   * @param int $contentId
   *  The content id
   */
  public function deletePackage($contentId) {
    $this->h5pC->delTree($this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR . 'content' . DIRECTORY_SEPARATOR . $contentId);
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
    $this->h5pC->copyTree($source_path, $destination_path);

    $this->h5pF->copyLibraryUsage($contentId, $copyFromId, $contentMainId);
  }

  /**
   * Identify what libraries are beeing used taking all dependencies into account
   *
   * @param array $librariesInUse
   *  List of libraries in use, indexed by machineName
   * @param array $jsonData
   *  library.json og h5p.json data holding dependency information
   * @param boolean $dynamic
   *  Whether or not the current library is a dynamic dependency
   */
  public function getLibraryUsage(&$librariesInUse, $jsonData, $dynamic = FALSE, $editor = FALSE) {
    if (isset($jsonData['preloadedDependencies'])) {
      foreach ($jsonData['preloadedDependencies'] as $preloadedDependency) {
        $library = $this->h5pF->loadLibrary($preloadedDependency['machineName'], $preloadedDependency['majorVersion'], $preloadedDependency['minorVersion']);
        $librariesInUse[$preloadedDependency['machineName']] = array(
          'library' => $library,
          'preloaded' => $dynamic ? 0 : 1,
        );
        $this->getLibraryUsage($librariesInUse, $library, $dynamic, $editor);
      }
    }
    if (isset($jsonData['dynamicDependencies'])) {
      foreach ($jsonData['dynamicDependencies'] as $dynamicDependency) {
        if (!isset($librariesInUse[$dynamicDependency['machineName']])) {
          $library = $this->h5pF->loadLibrary($dynamicDependency['machineName'], $dynamicDependency['majorVersion'], $dynamicDependency['minorVersion']);
          $librariesInUse[$dynamicDependency['machineName']] = array(
            'library' => $library,
            'preloaded' => 0,
          );
        }
        $this->getLibraryUsage($librariesInUse, $library, TRUE, $editor);
      }
    }
    if (isset($jsonData['editorDependencies']) && $editor) {
      foreach ($jsonData['editorDependencies'] as $editorDependency) {
        if (!isset($librariesInUse[$editorDependency['machineName']])) {
          $library = $this->h5pF->loadLibrary($editorDependency['machineName'], $editorDependency['majorVersion'], $editorDependency['minorVersion']);
          $librariesInUse[$editorDependency['machineName']] = array(
            'library' => $library,
            'preloaded' => $dynamic ? 0 : 1,
          );
        }
        $this->getLibraryUsage($librariesInUse, $library, $dynamic, TRUE);
      }
    }
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
   * @param int/string $contentId
   *  Identifier for this H5P
   * @param String $title
   *  Title of H5P
   * @param string $language
   *  Language code for H5P
   * @return string
   *  Path to .h5p file
   */
  public function getExportPath($contentId, $title, $language) {
    $h5pDir = $this->h5pF->getH5pPath() . DIRECTORY_SEPARATOR;
    $tempPath = $h5pDir . 'temp' . DIRECTORY_SEPARATOR . $contentId;
    $zipPath = $h5pDir . 'exports' . DIRECTORY_SEPARATOR . $contentId . '.h5p';
    // Check if h5p-package already exists.
    if (!file_exists($zipPath)) {
      // Temp dir to put the h5p files in
      @mkdir($tempPath);
      $exportData = $this->h5pF->getExportData($contentId);
      // Create content folder
      if ($this->h5pC->copyTree($h5pDir . 'content' . DIRECTORY_SEPARATOR . $contentId, $tempPath . DIRECTORY_SEPARATOR . 'content') === FALSE) {
        return FALSE;
      }
      file_put_contents($tempPath . DIRECTORY_SEPARATOR . 'content' . DIRECTORY_SEPARATOR . 'content.json', $exportData['jsonContent']);
      
      // Make embedTypes into an array
      $embedTypes = explode(', ', $exportData['embedType']);

      // Build h5p.json
      $h5pJson = array (
        'title' => $title,
        'language' => $language ? $language : 'und',
        'mainLibrary' => $exportData['mainLibrary'],
        'embedTypes' => $embedTypes,
      );
      
      // Copies libraries to temp dir and create mention in h5p.json
      foreach($exportData['libraries'] as $library) {
        // Set preloaded and dynamic dependencies
        if ($library['preloaded']) {
          $preloadedDependencies[] = array(
            'machineName' => $library['machineName'],
            'majorVersion' => $library['majorVersion'],
            'minorVersion' => $library['minorVersion'],
          );
        } else {
          $dynamicDependencies[] = array(
            'machineName' => $library['machineName'],
            'majorVersion' => $library['majorVersion'],
            'minorVersion' => $library['minorVersion'],
          );
        }
      }
      
      // Add preloaded and dynamic dependencies if they exist
      if (isset($preloadedDependencies)) { $h5pJson['preloadedDependencies'] = $preloadedDependencies; }
      if (isset($dynamicDependencies)) { $h5pJson['dynamicDependencies'] = $dynamicDependencies; }

      // Save h5p.json
      $results = print_r(json_encode($h5pJson), true);
      file_put_contents($tempPath . DIRECTORY_SEPARATOR . 'h5p.json', $results);
      
      // Add the editor libraries to the list of libraries
      // TODO: Comment in when mering in 6.x-1.x changes.
      //$exportData['libraries'] = $this->addEditorLibraries($exportData['libraries'], $exportData['editorLibraries']);
      
      // Getting all dependencies:
      $editorDependencies = array();
      $this->h5pC->getStorage()->getLibraryUsage($editorDependencies, $h5pJson, FALSE, TRUE);
      
      // Copies libraries to temp dir and create mention in h5p.json
      foreach($editorDependencies as $lib) {
        $library = $lib['library'];
        $source = $h5pDir . 'libraries' . DIRECTORY_SEPARATOR . $library['machineName'] . '-' . $library['majorVersion'] . '.' . $library['minorVersion'];
        $destination = $tempPath . DIRECTORY_SEPARATOR . $library['machineName'];
        $this->h5pC->copyTree($source, $destination);
      }

      // Create new zip instance.
      $zip = new ZipArchive();
      $zip->open($zipPath, ZIPARCHIVE::CREATE);

      // Get all files and folders in $tempPath
      $iterator = new RecursiveIteratorIterator(new RecursiveDirectoryIterator($tempPath . DIRECTORY_SEPARATOR));
      // Add files to zip
      foreach ($iterator as $key=>$value) {
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
      $this->h5pC->delTree($tempPath);
    }

    return str_replace(DIRECTORY_SEPARATOR, '/', $zipPath);
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
    'minorVersion' => 0
  );
  public static $styles = array(
    'styles/h5p.css',
  );
  public static $scripts = array(
    'js/jquery.js',
    'js/h5p.js',
  );

  public static $defaultContentWhitelist = 'json png jpg jpeg gif bmp tif tiff svg eot ttf woff otf webm mp4 ogg mp3 txt pdf rtf doc docx xls xlsx ppt pptx odt ods odp xml csv diff patch swf';
  public static $defaultLibraryWhitelistExtras = 'js css';

  public $h5pF;
  public $storage;
  public $validator;
  public $contentValidator;
  public $exporter;
  public $librariesJsonData;
  public $contentJsonData;
  public $mainJsonData;
  
  /* This could be used by all other classes in core to get an instance of all other
   * core classes. Another, probably better solution, is to make all other classes abstract,
   * containing only static functions. */
  public static $instance;

  /**
   * Constructor for the H5PCore
   *
   * @param object $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   */
  public function __construct($framework) {
    $this->h5pF = $framework;
    $this->storage = new H5PStorage($framework, $this);
    $this->validator = new H5PValidator($framework, $this);
    $this->contentValidator = new H5PContentValidator($framework, $this);
    $this->exporter = new H5PExport($framework, $this);
    
    H5PCore::$instance = $this;
  }

  public function getStorage() {
    return $this->storage;
  }
  
  public function getValidator() {
    return $this->validator;
  }
  
  public function getContentValidator() {
    return $this->contentValidator;
  }
  
  public function getExporter() {
    return $this->exporter;
  }
  
  public function getInterface() {
    return $this->h5pF;
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
  public function delTree($dir) {
    if (!is_dir($dir)) {
      return;
    }
    $files = array_diff(scandir($dir), array('.','..'));
    foreach ($files as $file) {
      (is_dir("$dir/$file")) ? $this->delTree("$dir/$file") : unlink("$dir/$file");
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
  public function copyTree($source, $destination) {
    $dir = opendir($source);

    if ($dir === FALSE) {
      $this->h5pF->setErrorMessage($this->h5pF->t('Unable to copy tree, no such directory: @dir', array('@dir' => $source)));
      return FALSE;
    }

    @mkdir($destination);
    while (false !== ($file = readdir($dir))) {
        if (($file != '.') && ($file != '..')) {
            if (is_dir($source . DIRECTORY_SEPARATOR . $file)) {
              $this->copyTree($source . DIRECTORY_SEPARATOR . $file, $destination . DIRECTORY_SEPARATOR . $file);
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
  public function libraryToString($library, $folderName = FALSE) {
    return $library['machineName'] . ($folderName ? '-' : ' ') . $library['majorVersion'] . '.' . $library['minorVersion'];
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
  public function libraryFromString($libraryString) {
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
}

/**
 * Functions for validating basic types from H5P library semantics.
 */
class H5PContentValidator {
  public $h5pF;
  public $h5pC;
  private $typeMap;
  private $semanticsCache;

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
    // Cache for semantics used within this validation to avoid unneccessary
    // json_decodes if a library is used multiple times.
    $this->semanticsCache = array();
  }

  /**
   * Validate the given value from content with the matching semantics
   * object from semantics
   *
   * Function will recurse via external functions for container objects like
   * 'list', 'group' and 'library'.
   *
   * @param object $value
   *   Object to be verified. May be a string or an array. (normal or keyed)
   * @param object $semantics
   *   Semantics object from semantics.json for main library. Further
   *   semantics will be loaded from H5PFramework if any libraries are
   *   found within the value data.
   */
  public function validateBySemantics(&$value, $semantics) {
    $fakebaseobject = (object) array(
      'type' => 'group',
      'fields' => $semantics,
    );
    $this->validateGroup($value, $fakebaseobject, FALSE);
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
    if (isset($semantics->regexp)) {
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
    $validkeys = array_merge(array('path', 'mime'), $typevalidkeys);
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
   *
   * Will recurse into validating the library's semantics too.
   */
  public function validateLibrary(&$value, $semantics) {
    // Check if provided library is within allowed options
    if (in_array($value->library, $semantics->options)) {
      if (isset($this->semanticsCache[$value->library])) {
        $librarySemantics = $this->semanticsCache[$value->library];
      }
      else {
        $libspec = $this->h5pC->libraryFromString($value->library);
        $librarySemantics = $this->h5pF->getLibrarySemantics($libspec['machineName'], $libspec['majorVersion'], $libspec['minorVersion']);
        $this->semanticsCache[$value->library] = $librarySemantics;
      }
      $this->validateBySemantics($value->params, $librarySemantics);
      $validkeys = array('library', 'params');
      if (isset($semantics->extraAttributes)) {
        $validkeys = array_merge($validkeys, $semantics->extraAttributes);
      }
      $this->filterParams($value, $validkeys);
    }
    else {
      $this->h5pF->setErrorMessage($this->h5pF->t('Library used in content is not a valid library according to semantics'));
      $value = new stdClass();
    }
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
}
?>
