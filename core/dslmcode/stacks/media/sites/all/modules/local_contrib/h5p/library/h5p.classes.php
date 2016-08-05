<?php
/**
 * Interface defining functions the h5p library needs the framework to implement
 */
interface H5PFrameworkInterface {

  /**
   * Returns info for the current platform
   *
   * @return array
   *   An associative array containing:
   *   - name: The name of the platform, for instance "Wordpress"
   *   - version: The version of the platform, for instance "4.0"
   *   - h5pVersion: The version of the H5P plugin/module
   */
  public function getPlatformInfo();


  /**
   * Fetches a file from a remote server using HTTP GET
   *
   * @param $url
   * @param $data
   * @return string The content (response body). NULL if something went wrong
   */
  public function fetchExternalData($url, $data);

  /**
   * Set the tutorial URL for a library. All versions of the library is set
   *
   * @param string $machineName
   * @param string $tutorialUrl
   */
  public function setLibraryTutorialUrl($machineName, $tutorialUrl);

  /**
   * Show the user an error message
   *
   * @param string $message
   *   The error message
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
   * @param array $replacements
   *   An associative array of replacements to make after translation. Incidences
   *   of any key in this array are replaced with the corresponding value. Based
   *   on the first character of the key, the value is escaped and/or themed:
   *    - !variable: inserted as is
   *    - @variable: escape plain text to HTML
   *    - %variable: escape text and theme as a placeholder for user-submitted
   *      content
   * @return string Translated string
   * Translated string
   */
  public function t($message, $replacements = array());

  /**
   * Get the Path to the last uploaded h5p
   *
   * @return string
   *   Path to the folder where the last uploaded h5p for this session is located.
   */
  public function getUploadedH5pFolderPath();

  /**
   * Get the path to the last uploaded h5p file
   *
   * @return string
   *   Path to the last uploaded h5p
   */
  public function getUploadedH5pPath();

  /**
   * Get a list of the current installed libraries
   *
   * @return array
   *   Associative array containing one entry per machine name.
   *   For each machineName there is a list of libraries(with different versions)
   */
  public function loadLibraries();

  /**
   * Returns the URL to the library admin page
   *
   * @return string
   *   URL to admin page
   */
  public function getAdminUrl();

  /**
   * Get id to an existing library.
   * If version number is not specified, the newest version will be returned.
   *
   * @param string $machineName
   *   The librarys machine name
   * @param int $majorVersion
   *   Optional major version number for library
   * @param int $minorVersion
   *   Optional minor version number for library
   * @return int
   *   The id of the specified library or FALSE
   */
  public function getLibraryId($machineName, $majorVersion = NULL, $minorVersion = NULL);

  /**
   * Get file extension whitelist
   *
   * The default extension list is part of h5p, but admins should be allowed to modify it
   *
   * @param boolean $isLibrary
   *   TRUE if this is the whitelist for a library. FALSE if it is the whitelist
   *   for the content folder we are getting
   * @param string $defaultContentWhitelist
   *   A string of file extensions separated by whitespace
   * @param string $defaultLibraryWhitelist
   *   A string of file extensions separated by whitespace
   */
  public function getWhitelist($isLibrary, $defaultContentWhitelist, $defaultLibraryWhitelist);

  /**
   * Is the library a patched version of an existing library?
   *
   * @param object $library
   *   An associative array containing:
   *   - machineName: The library machineName
   *   - majorVersion: The librarys majorVersion
   *   - minorVersion: The librarys minorVersion
   *   - patchVersion: The librarys patchVersion
   * @return boolean
   *   TRUE if the library is a patched version of an existing library
   *   FALSE otherwise
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
   *   Associative array containing:
   *   - libraryId: The id of the library if it is an existing library.
   *   - title: The library's name
   *   - machineName: The library machineName
   *   - majorVersion: The library's majorVersion
   *   - minorVersion: The library's minorVersion
   *   - patchVersion: The library's patchVersion
   *   - runnable: 1 if the library is a content type, 0 otherwise
   *   - fullscreen(optional): 1 if the library supports fullscreen, 0 otherwise
   *   - embedTypes(optional): list of supported embed types
   *   - preloadedJs(optional): list of associative arrays containing:
   *     - path: path to a js file relative to the library root folder
   *   - preloadedCss(optional): list of associative arrays containing:
   *     - path: path to css file relative to the library root folder
   *   - dropLibraryCss(optional): list of associative arrays containing:
   *     - machineName: machine name for the librarys that are to drop their css
   *   - semantics(optional): Json describing the content structure for the library
   *   - language(optional): associative array containing:
   *     - languageCode: Translation in json format
   * @param bool $new
   * @return
   */
  public function saveLibraryData(&$libraryData, $new = TRUE);

  /**
   * Insert new content.
   *
   * @param array $content
   *   An associative array containing:
   *   - id: The content id
   *   - params: The content in json format
   *   - library: An associative array containing:
   *     - libraryId: The id of the main library for this content
   * @param int $contentMainId
   *   Main id for the content if this is a system that supports versions
   */
  public function insertContent($content, $contentMainId = NULL);

  /**
   * Update old content.
   *
   * @param array $content
   *   An associative array containing:
   *   - id: The content id
   *   - params: The content in json format
   *   - library: An associative array containing:
   *     - libraryId: The id of the main library for this content
   * @param int $contentMainId
   *   Main id for the content if this is a system that supports versions
   */
  public function updateContent($content, $contentMainId = NULL);

  /**
   * Resets marked user data for the given content.
   *
   * @param int $contentId
   */
  public function resetContentUserData($contentId);

  /**
   * Save what libraries a library is depending on
   *
   * @param int $libraryId
   *   Library Id for the library we're saving dependencies for
   * @param array $dependencies
   *   List of dependencies as associative arrays containing:
   *   - machineName: The library machineName
   *   - majorVersion: The library's majorVersion
   *   - minorVersion: The library's minorVersion
   * @param string $dependency_type
   *   What type of dependency this is, the following values are allowed:
   *   - editor
   *   - preloaded
   *   - dynamic
   */
  public function saveLibraryDependencies($libraryId, $dependencies, $dependency_type);

  /**
   * Give an H5P the same library dependencies as a given H5P
   *
   * @param int $contentId
   *   Id identifying the content
   * @param int $copyFromId
   *   Id identifying the content to be copied
   * @param int $contentMainId
   *   Main id for the content, typically used in frameworks
   *   That supports versions. (In this case the content id will typically be
   *   the version id, and the contentMainId will be the frameworks content id
   */
  public function copyLibraryUsage($contentId, $copyFromId, $contentMainId = NULL);

  /**
   * Deletes content data
   *
   * @param int $contentId
   *   Id identifying the content
   */
  public function deleteContentData($contentId);

  /**
   * Delete what libraries a content item is using
   *
   * @param int $contentId
   *   Content Id of the content we'll be deleting library usage for
   */
  public function deleteLibraryUsage($contentId);

  /**
   * Saves what libraries the content uses
   *
   * @param int $contentId
   *   Id identifying the content
   * @param array $librariesInUse
   *   List of libraries the content uses. Libraries consist of associative arrays with:
   *   - library: Associative array containing:
   *     - dropLibraryCss(optional): comma separated list of machineNames
   *     - machineName: Machine name for the library
   *     - libraryId: Id of the library
   *   - type: The dependency type. Allowed values:
   *     - editor
   *     - dynamic
   *     - preloaded
   */
  public function saveLibraryUsage($contentId, $librariesInUse);

  /**
   * Get number of content/nodes using a library, and the number of
   * dependencies to other libraries
   *
   * @param int $libraryId
   *   Library identifier
   * @return array
   *   Associative array containing:
   *   - content: Number of content using the library
   *   - libraries: Number of libraries depending on the library
   */
  public function getLibraryUsage($libraryId);

  /**
   * Loads a library
   *
   * @param string $machineName
   *   The library's machine name
   * @param int $majorVersion
   *   The library's major version
   * @param int $minorVersion
   *   The library's minor version
   * @return array|FALSE
   *   FALSE if the library does not exist.
   *   Otherwise an associative array containing:
   *   - libraryId: The id of the library if it is an existing library.
   *   - title: The library's name
   *   - machineName: The library machineName
   *   - majorVersion: The library's majorVersion
   *   - minorVersion: The library's minorVersion
   *   - patchVersion: The library's patchVersion
   *   - runnable: 1 if the library is a content type, 0 otherwise
   *   - fullscreen(optional): 1 if the library supports fullscreen, 0 otherwise
   *   - embedTypes(optional): list of supported embed types
   *   - preloadedJs(optional): comma separated string with js file paths
   *   - preloadedCss(optional): comma separated sting with css file paths
   *   - dropLibraryCss(optional): list of associative arrays containing:
   *     - machineName: machine name for the librarys that are to drop their css
   *   - semantics(optional): Json describing the content structure for the library
   *   - preloadedDependencies(optional): list of associative arrays containing:
   *     - machineName: Machine name for a library this library is depending on
   *     - majorVersion: Major version for a library this library is depending on
   *     - minorVersion: Minor for a library this library is depending on
   *   - dynamicDependencies(optional): list of associative arrays containing:
   *     - machineName: Machine name for a library this library is depending on
   *     - majorVersion: Major version for a library this library is depending on
   *     - minorVersion: Minor for a library this library is depending on
   *   - editorDependencies(optional): list of associative arrays containing:
   *     - machineName: Machine name for a library this library is depending on
   *     - majorVersion: Major version for a library this library is depending on
   *     - minorVersion: Minor for a library this library is depending on
   */
  public function loadLibrary($machineName, $majorVersion, $minorVersion);

  /**
   * Loads library semantics.
   *
   * @param string $machineName
   *   Machine name for the library
   * @param int $majorVersion
   *   The library's major version
   * @param int $minorVersion
   *   The library's minor version
   * @return string
   *   The library's semantics as json
   */
  public function loadLibrarySemantics($machineName, $majorVersion, $minorVersion);

  /**
   * Makes it possible to alter the semantics, adding custom fields, etc.
   *
   * @param array $semantics
   *   Associative array representing the semantics
   * @param string $machineName
   *   The library's machine name
   * @param int $majorVersion
   *   The library's major version
   * @param int $minorVersion
   *   The library's minor version
   */
  public function alterLibrarySemantics(&$semantics, $machineName, $majorVersion, $minorVersion);

  /**
   * Delete all dependencies belonging to given library
   *
   * @param int $libraryId
   *   Library identifier
   */
  public function deleteLibraryDependencies($libraryId);

  /**
   * Start an atomic operation against the dependency storage
   */
  public function lockDependencyStorage();

  /**
   * Stops an atomic operation against the dependency storage
   */
  public function unlockDependencyStorage();


  /**
   * Delete a library from database and file system
   *
   * @param stdClass $library
   *   Library object with id, name, major version and minor version.
   */
  public function deleteLibrary($library);

  /**
   * Load content.
   *
   * @param int $id
   *   Content identifier
   * @return array
   *   Associative array containing:
   *   - contentId: Identifier for the content
   *   - params: json content as string
   *   - embedType: csv of embed types
   *   - title: The contents title
   *   - language: Language code for the content
   *   - libraryId: Id for the main library
   *   - libraryName: The library machine name
   *   - libraryMajorVersion: The library's majorVersion
   *   - libraryMinorVersion: The library's minorVersion
   *   - libraryEmbedTypes: CSV of the main library's embed types
   *   - libraryFullscreen: 1 if fullscreen is supported. 0 otherwise.
   */
  public function loadContent($id);

  /**
   * Load dependencies for the given content of the given type.
   *
   * @param int $id
   *   Content identifier
   * @param int $type
   *   Dependency types. Allowed values:
   *   - editor
   *   - preloaded
   *   - dynamic
   * @return array
   *   List of associative arrays containing:
   *   - libraryId: The id of the library if it is an existing library.
   *   - machineName: The library machineName
   *   - majorVersion: The library's majorVersion
   *   - minorVersion: The library's minorVersion
   *   - patchVersion: The library's patchVersion
   *   - preloadedJs(optional): comma separated string with js file paths
   *   - preloadedCss(optional): comma separated sting with css file paths
   *   - dropCss(optional): csv of machine names
   */
  public function loadContentDependencies($id, $type = NULL);

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
  public function getOption($name, $default = NULL);

  /**
   * Stores the given setting.
   * For example when did we last check h5p.org for updates to our libraries.
   *
   * @param string $name
   *   Identifier for the setting
   * @param mixed $value Data
   *   Whatever we want to store as the setting
   */
  public function setOption($name, $value);

  /**
   * This will update selected fields on the given content.
   *
   * @param int $id Content identifier
   * @param array $fields Content fields, e.g. filtered or slug.
   */
  public function updateContentFields($id, $fields);

  /**
   * Will clear filtered params for all the content that uses the specified
   * library. This means that the content dependencies will have to be rebuilt,
   * and the parameters re-filtered.
   *
   * @param int $library_id
   */
  public function clearFilteredParameters($library_id);

  /**
   * Get number of contents that has to get their content dependencies rebuilt
   * and parameters re-filtered.
   *
   * @return int
   */
  public function getNumNotFiltered();

  /**
   * Get number of contents using library as main library.
   *
   * @param int $libraryId
   * @return int
   */
  public function getNumContent($libraryId);

  /**
   * Determines if content slug is used.
   *
   * @param string $slug
   * @return boolean
   */
  public function isContentSlugAvailable($slug);

  /**
   * Generates statistics from the event log per library
   *
   * @param string $type Type of event to generate stats for
   * @return array Number values indexed by library name and version
   */
  public function getLibraryStats($type);

  /**
   * Aggregate the current number of H5P authors
   * @return int
   */
  public function getNumAuthors();

  /**
   * Stores hash keys for cached assets, aggregated JavaScripts and
   * stylesheets, and connects it to libraries so that we know which cache file
   * to delete when a library is updated.
   *
   * @param string $key
   *  Hash key for the given libraries
   * @param array $libraries
   *  List of dependencies(libraries) used to create the key
   */
  public function saveCachedAssets($key, $libraries);

  /**
   * Locate hash keys for given library and delete them.
   * Used when cache file are deleted.
   *
   * @param int $library_id
   *  Library identifier
   * @return array
   *  List of hash keys removed
   */
  public function deleteCachedAssets($library_id);

  /**
   * Get the amount of content items associated to a library
   * return int
   */
  public function getLibraryContentCount();
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
   * @param H5PFrameworkInterface $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   * @param H5PCore $H5PCore
   */
  public function __construct($H5PFramework, $H5PCore) {
    $this->h5pF = $H5PFramework;
    $this->h5pC = $H5PCore;
    $this->h5pCV = new H5PContentValidator($this->h5pF, $this->h5pC);
  }

  /**
   * Validates a .h5p file
   *
   * @param bool $skipContent
   * @param bool $upgradeOnly
   * @return bool TRUE if the .h5p file is valid
   * TRUE if the .h5p file is valid
   */
  public function isValidPackage($skipContent = FALSE, $upgradeOnly = FALSE) {
    // Check dependencies, make sure Zip is present
    if (!class_exists('ZipArchive')) {
      $this->h5pF->setErrorMessage($this->h5pF->t('Your PHP version does not support ZipArchive.'));
      return FALSE;
    }

    // Create a temporary dir to extract package in.
    $tmpDir = $this->h5pF->getUploadedH5pFolderPath();
    $tmpPath = $this->h5pF->getUploadedH5pPath();

    // Extract and then remove the package file.
    $zip = new ZipArchive;

    // Only allow files with the .h5p extension:
    if (strtolower(substr($tmpPath, -3)) !== 'h5p') {
      $this->h5pF->setErrorMessage($this->h5pF->t('The file you uploaded is not a valid HTML5 Package (It does not have the .h5p file extension)'));
      H5PCore::deleteFileTree($tmpDir);
      return FALSE;
    }

    if ($zip->open($tmpPath) === true) {
      $zip->extractTo($tmpDir);
      $zip->close();
    }
    else {
      $this->h5pF->setErrorMessage($this->h5pF->t('The file you uploaded is not a valid HTML5 Package (We are unable to unzip it)'));
      H5PCore::deleteFileTree($tmpDir);
      return FALSE;
    }
    unlink($tmpPath);

    // Process content and libraries
    $valid = TRUE;
    $libraries = array();
    $files = scandir($tmpDir);
    $mainH5pData = null;
    $libraryJsonData = null;
    $contentJsonData = null;
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
          // validateContentFiles adds potential errors to the queue
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
          // where machineName, majorVersion and minorVersion is read from library.json
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
        // When upgrading, we only add the already installed libraries, and
        // the new dependent libraries
        $upgrades = array();
        foreach ($libraries as $libString => &$library) {
          // Is this library already installed?
          if ($this->h5pF->getLibraryId($library['machineName']) !== FALSE) {
            $upgrades[$libString] = $library;
          }
        }
        while ($missingLibraries = $this->getMissingLibraries($upgrades)) {
          foreach ($missingLibraries as $libString => $missing) {
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
      foreach ($missingLibraries as $libString => $missing) {
        if ($this->h5pC->getLibraryId($missing, $libString)) {
          unset($missingLibraries[$libString]);
        }
      }

      if (!empty($missingLibraries)) {
        foreach ($missingLibraries as $libString => $library) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Missing required library @library', array('@library' => $libString)));
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
   * @return boolean|array
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
      $libString = H5PCore::libraryToString($dependency);
      if (!isset($libraries[$libString])) {
        $missing[$libString] = $dependency;
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

    // Check the library's required API version of Core.
    // If no requirement is set this implicitly means 1.0.
    if (isset($h5pData['coreApi']) && !empty($h5pData['coreApi'])) {
      if (($h5pData['coreApi']['majorVersion'] > H5PCore::$coreApi['majorVersion']) ||
          ( ($h5pData['coreApi']['majorVersion'] == H5PCore::$coreApi['majorVersion']) &&
            ($h5pData['coreApi']['minorVersion'] > H5PCore::$coreApi['minorVersion']) )) {

        $this->h5pF->setErrorMessage(
            $this->h5pF->t('The system was unable to install the <em>%component</em> component from the package, it requires a newer version of the H5P plugin. This site is currently running version %current, whereas the required version is %required or higher. You should consider upgrading and then try again.',
                array(
                  '%component' => (isset($h5pData['title']) ? $h5pData['title'] : $library_name),
                  '%current' => H5PCore::$coreApi['majorVersion'] . '.' . H5PCore::$coreApi['minorVersion'],
                  '%required' => $h5pData['coreApi']['majorVersion'] . '.' . $h5pData['coreApi']['minorVersion']
                )
            )
        );

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
        $result[$key] = self::arrayCopy($val);
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
   * @param H5PFrameworkInterface|object $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   * @param H5PCore $H5PCore
   */
  public function __construct(H5PFrameworkInterface $H5PFramework, H5PCore $H5PCore) {
    $this->h5pF = $H5PFramework;
    $this->h5pC = $H5PCore;
  }

  /**
   * Saves a H5P file
   *
   * @param null $content
   * @param int $contentMainId
   *  The main id for the content we are saving. This is used if the framework
   *  we're integrating with uses content id's and version id's
   * @param bool $skipContent
   * @param array $options
   * @return bool TRUE if one or more libraries were updated
   * TRUE if one or more libraries were updated
   * FALSE otherwise
   */
  public function savePackage($content = NULL, $contentMainId = NULL, $skipContent = FALSE, $options = array()) {
    if ($this->h5pF->mayUpdateLibraries()) {
      // Save the libraries we processed during validation
      $this->saveLibraries();
    }

    if (!$skipContent) {
      $basePath = $this->h5pF->getUploadedH5pFolderPath();
      $current_path = $basePath . DIRECTORY_SEPARATOR . 'content';

      // Save content
      if ($content === NULL) {
        $content = array();
      }
      if (!is_array($content)) {
        $content = array('id' => $content);
      }

      // Find main library version
      foreach ($this->h5pC->mainJsonData['preloadedDependencies'] as $dep) {
        if ($dep['machineName'] === $this->h5pC->mainJsonData['mainLibrary']) {
          $dep['libraryId'] = $this->h5pC->getLibraryId($dep);
          $content['library'] = $dep;
          break;
        }
      }

      $content['params'] = file_get_contents($current_path . DIRECTORY_SEPARATOR . 'content.json');

      if (isset($options['disable'])) {
        $content['disable'] = $options['disable'];
      }
      $contentId = $this->h5pC->saveContent($content, $contentMainId);
      $this->contentId = $contentId;

      try {
        // Save content folder contents
        $this->h5pC->fs->saveContent($current_path, $contentId);
      }
      catch (Exception $e) {
        $this->h5pF->setErrorMessage($this->h5pF->t($e->getMessage()));
      }

      // Remove temp content folder
      H5PCore::deleteFileTree($basePath);
    }
  }

  /**
   * Helps savePackage.
   *
   * @return int Number of libraries saved
   */
  private function saveLibraries() {
    // Keep track of the number of libraries that have been saved
    $newOnes = 0;
    $oldOnes = 0;

    // Go through libraries that came with this package
    foreach ($this->h5pC->librariesJsonData as $libString => &$library) {
      // Find local library identifier
      $libraryId = $this->h5pC->getLibraryId($library, $libString);

      // Assume new library
      $new = TRUE;
      if ($libraryId) {
        // Found old library
        $library['libraryId'] = $libraryId;

        if ($this->h5pF->isPatchedLibrary($library)) {
          // This is a newer version than ours. Upgrade!
          $new = FALSE;
        }
        else {
          $library['saveDependencies'] = FALSE;
          // This is an older version, no need to save.
          continue;
        }
      }

      // Indicate that the dependencies of this library should be saved.
      $library['saveDependencies'] = TRUE;

      // Save library meta data
      $this->h5pF->saveLibraryData($library, $new);

      // Save library folder
      $this->h5pC->fs->saveLibrary($library);

      // Remove cached assets that uses this library
      if ($this->h5pC->aggregateAssets && isset($library['libraryId'])) {
        $removedKeys = $this->h5pF->deleteCachedAssets($library['libraryId']);
        $this->h5pC->fs->deleteCachedAssets($removedKeys);
      }

      // Remove tmp folder
      H5PCore::deleteFileTree($library['uploadDirectory']);

      if ($new) {
        $newOnes++;
      }
      else {
        $oldOnes++;
      }
    }

    // Go through the libraries again to save dependencies.
    foreach ($this->h5pC->librariesJsonData as &$library) {
      if (!$library['saveDependencies']) {
        continue;
      }

      // TODO: Should the table be locked for this operation?

      // Remove any old dependencies
      $this->h5pF->deleteLibraryDependencies($library['libraryId']);

      // Insert the different new ones
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
      $this->h5pF->clearFilteredParameters($library['libraryId']);
    }

    // Tell the user what we've done.
    if ($newOnes && $oldOnes) {
      $message = $this->h5pF->t('Added %new new H5P libraries and updated %old old.', array('%new' => $newOnes, '%old' => $oldOnes));
    }
    elseif ($newOnes) {
      $message = $this->h5pF->t('Added %new new H5P libraries.', array('%new' => $newOnes));
    }
    elseif ($oldOnes) {
      $message = $this->h5pF->t('Updated %old H5P libraries.', array('%old' => $oldOnes));
    }

    if (isset($message)) {
      $this->h5pF->setInfoMessage($message);
    }
  }

  /**
   * Delete an H5P package
   *
   * @param $content
   */
  public function deletePackage($content) {
    $this->h5pC->fs->deleteContent($content['id']);
    $this->h5pC->fs->deleteExport(($content['slug'] ? $content['slug'] . '-' : '') . $content['id'] . '.h5p');
    $this->h5pF->deleteContentData($content['id']);
  }

  /**
   * Copy/clone an H5P package
   *
   * May for instance be used if the content is being revisioned without
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
    $this->h5pC->fs->cloneContent($copyFromId, $contentId);
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
   * @param H5PFrameworkInterface|object $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   * @param H5PCore $H5PCore
   *  Reference to an instance of H5PCore
   */
  public function __construct(H5PFrameworkInterface $H5PFramework, H5PCore $H5PCore) {
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

    // Get path to temporary folder, where export will be contained
    $tmpPath = $this->h5pC->fs->getTmpPath();
    mkdir($tmpPath, 0777, true);

    try {
      // Create content folder and populate with files
      $this->h5pC->fs->exportContent($content['id'], "{$tmpPath}/content");
    }
    catch (Exception $e) {
      $this->h5pF->setErrorMessage($this->h5pF->t($e->getMessage()));
      H5PCore::deleteFileTree($tmpPath);
      return FALSE;
    }

    // Update content.json with content from database
    file_put_contents("{$tmpPath}/content/content.json", $content['params']);

    // Make embedType into an array
    $embedTypes = explode(', ', $content['embedType']);

    // Build h5p.json
    $h5pJson = array (
      'title' => $content['title'],
      'language' => (isset($content['language']) && strlen(trim($content['language'])) !== 0) ? $content['language'] : 'und',
      'mainLibrary' => $content['library']['name'],
      'embedTypes' => $embedTypes,
    );

    // Add dependencies to h5p
    foreach ($content['dependencies'] as $dependency) {
      $library = $dependency['library'];

      try {
        $exportFolder = NULL;

        // Determine path of export library
        if (isset($this->h5pC) && isset($this->h5pC->h5pD)) {

          // Tries to find library in development folder
          $isDevLibrary = $this->h5pC->h5pD->getLibrary(
              $library['machineName'],
              $library['majorVersion'],
              $library['minorVersion']
          );

          if ($isDevLibrary !== NULL) {
            $exportFolder = "/" . $library['path'];
          }
        }

        // Export required libraries
        $this->h5pC->fs->exportLibrary($library, $tmpPath, $exportFolder);
      }
      catch (Exception $e) {
        $this->h5pF->setErrorMessage($this->h5pF->t($e->getMessage()));
        H5PCore::deleteFileTree($tmpPath);
        return FALSE;
      }

      // Do not add editor dependencies to h5p json.
      if ($dependency['type'] === 'editor') {
        continue;
      }

      // Add to h5p.json dependencies
      $h5pJson[$dependency['type'] . 'Dependencies'][] = array(
        'machineName' => $library['machineName'],
        'majorVersion' => $library['majorVersion'],
        'minorVersion' => $library['minorVersion']
      );
    }

    // Save h5p.json
    $results = print_r(json_encode($h5pJson), true);
    file_put_contents("{$tmpPath}/h5p.json", $results);

    // Get a complete file list from our tmp dir
    $files = array();
    self::populateFileList($tmpPath, $files);

    // Get path to temporary export target file
    $tmpFile = $this->h5pC->fs->getTmpPath();

    // Create new zip instance.
    $zip = new ZipArchive();
    $zip->open($tmpFile, ZipArchive::CREATE | ZipArchive::OVERWRITE);

    // Add all the files from the tmp dir.
    foreach ($files as $file) {
      // Please note that the zip format has no concept of folders, we must
      // use forward slashes to separate our directories.
      $zip->addFile($file->absolutePath, $file->relativePath);
    }

    // Close zip and remove tmp dir
    $zip->close();
    H5PCore::deleteFileTree($tmpPath);

    try {
      // Save export
      $this->h5pC->fs->saveExport($tmpFile, $content['slug'] . '-' . $content['id'] . '.h5p');
    }
    catch (Exception $e) {
      $this->h5pF->setErrorMessage($this->h5pF->t($e->getMessage()));
    }

    unlink($tmpFile);

    return true;
  }

  /**
   * Recursive function the will add the files of the given directory to the
   * given files list. All files are objects with an absolute path and
   * a relative path. The relative path is forward slashes only! Great for
   * use in zip files and URLs.
   *
   * @param string $dir path
   * @param array $files list
   * @param string $relative prefix. Optional
   */
  private static function populateFileList($dir, &$files, $relative = '') {
    $strip = strlen($dir) + 1;
    $contents = glob($dir . DIRECTORY_SEPARATOR . '*');
    if (!empty($contents)) {
      foreach ($contents as $file) {
        $rel = $relative . substr($file, $strip);
        if (is_dir($file)) {
          self::populateFileList($file, $files, $rel . '/');
        }
        else {
          $files[] = (object) array(
            'absolutePath' => $file,
            'relativePath' => $rel
          );
        }
      }
    }
  }

  /**
   * Delete .h5p file
   *
   * @param array $content object
   */
  public function deleteExport($content) {
    $this->h5pC->fs->deleteExport(($content['slug'] ? $content['slug'] . '-' : '') . $content['id'] . '.h5p');
  }

  /**
   * Add editor libraries to the list of libraries
   *
   * These are not supposed to go into h5p.json, but must be included with the rest
   * of the libraries
   *
   * TODO This is a private function that is not currently being used
   *
   * @param array $libraries
   *  List of libraries keyed by machineName
   * @param array $editorLibraries
   *  List of libraries keyed by machineName
   * @return array List of libraries keyed by machineName
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
    'minorVersion' => 8
  );
  public static $styles = array(
    'styles/h5p.css',
    'styles/h5p-confirmation-dialog.css',
    'styles/h5p-core-button.css'
  );
  public static $scripts = array(
    'js/jquery.js',
    'js/h5p.js',
    'js/h5p-event-dispatcher.js',
    'js/h5p-x-api-event.js',
    'js/h5p-x-api.js',
    'js/h5p-content-type.js',
    'js/h5p-confirmation-dialog.js'
  );
  public static $adminScripts = array(
    'js/jquery.js',
    'js/h5p-utils.js',
  );

  public static $defaultContentWhitelist = 'json png jpg jpeg gif bmp tif tiff svg eot ttf woff woff2 otf webm mp4 ogg mp3 txt pdf rtf doc docx xls xlsx ppt pptx odt ods odp xml csv diff patch swf md textile';
  public static $defaultLibraryWhitelistExtras = 'js css';

  public $librariesJsonData, $contentJsonData, $mainJsonData, $h5pF, $fs, $development_mode, $h5pD, $disableFileCheck;
  const SECONDS_IN_WEEK = 604800;

  private $exportEnabled;

  // Disable flags
  const DISABLE_NONE = 0;
  const DISABLE_FRAME = 1;
  const DISABLE_DOWNLOAD = 2;
  const DISABLE_EMBED = 4;
  const DISABLE_COPYRIGHT = 8;
  const DISABLE_ABOUT = 16;

  // Map flags to string
  public static $disable = array(
    self::DISABLE_FRAME => 'frame',
    self::DISABLE_DOWNLOAD => 'download',
    self::DISABLE_EMBED => 'embed',
    self::DISABLE_COPYRIGHT => 'copyright'
  );

  /**
   * Constructor for the H5PCore
   *
   * @param H5PFrameworkInterface $H5PFramework
   *  The frameworks implementation of the H5PFrameworkInterface
   * @param string|\H5PFileStorage $path H5P file storage directory or class.
   * @param string $url To file storage directory.
   * @param string $language code. Defaults to english.
   * @param boolean $export enabled?
   * @param int $development_mode mode.
   */
  public function __construct(H5PFrameworkInterface $H5PFramework, $path, $url, $language = 'en', $export = FALSE, $development_mode = H5PDevelopment::MODE_NONE) {
    $this->h5pF = $H5PFramework;

    $this->fs = ($path instanceof \H5PFileStorage ? $path : new \H5PDefaultStorage($path));

    $this->url = $url;
    $this->exportEnabled = $export;
    $this->development_mode = $development_mode;

    $this->aggregateAssets = FALSE; // Off by default.. for now

    if ($development_mode & H5PDevelopment::MODE_LIBRARY) {
      $this->h5pD = new H5PDevelopment($this->h5pF, $path . '/', $language);
    }

    $this->detectSiteType();
    $this->fullPluginPath = preg_replace('/\/[^\/]+[\/]?$/', '' , dirname(__FILE__));

    // Standard regex for converting copied files paths
    $this->relativePathRegExp = '/^((\.\.\/){1,2})(.*content\/)?(\d+|editor)\/(.+)$/';
  }

  /**
   * Save content and clear cache.
   *
   * @param array $content
   * @param null|int $contentMainId
   * @return int Content ID
   */
  public function saveContent($content, $contentMainId = NULL) {
    if (isset($content['id'])) {
      $this->h5pF->updateContent($content, $contentMainId);
    }
    else {
      $content['id'] = $this->h5pF->insertContent($content, $contentMainId);
    }

    // Some user data for content has to be reset when the content changes.
    $this->h5pF->resetContentUserData($contentMainId ? $contentMainId : $content['id']);

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
   * Filter content run parameters, rebuild content dependency cache and export file.
   *
   * @param Object|array $content
   * @return Object NULL on failure.
   */
  public function filterParameters(&$content) {
    if (isset($content['filtered']) && $content['filtered'] !== '') {
      return $content['filtered'];
    }

    // Validate and filter against main library semantics.
    $validator = new H5PContentValidator($this->h5pF, $this);
    $params = (object) array(
      'library' => H5PCore::libraryToString($content['library']),
      'params' => json_decode($content['params'])
    );
    if (!$params->params) {
      return NULL;
    }
    $validator->validateLibrary($params, (object) array('options' => array($params->library)));

    $params = json_encode($params->params);

    // Update content dependencies.
    $content['dependencies'] = $validator->getDependencies();

    // Sometimes the parameters are filtered before content has been created
    if ($content['id']) {
      $this->h5pF->deleteLibraryUsage($content['id']);
      $this->h5pF->saveLibraryUsage($content['id'], $content['dependencies']);

      if (!$content['slug']) {
        $content['slug'] = $this->generateContentSlug($content);

        // Remove old export file
        $this->fs->deleteExport($content['id'] . '.h5p');
      }

      if ($this->exportEnabled) {
        // Recreate export file
        $exporter = new H5PExport($this->h5pF, $this);
        $exporter->createExportFile($content);
      }

      // Cache.
      $this->h5pF->updateContentFields($content['id'], array(
        'filtered' => $params,
        'slug' => $content['slug']
      ));
    }
    return $params;
  }

  /**
   * Generate content slug
   *
   * @param array $content object
   * @return string unique content slug
   */
  private function generateContentSlug($content) {
    $slug = H5PCore::slugify($content['title']);

    $available = NULL;
    while (!$available) {
      if ($available === FALSE) {
        // If not available, add number suffix.
        $matches = array();
        if (preg_match('/(.+-)([0-9]+)$/', $slug, $matches)) {
          $slug = $matches[1] . (intval($matches[2]) + 1);
        }
        else {
          $slug .=  '-2';
        }
      }
      $available = $this->h5pF->isContentSlugAvailable($slug);
    }

    return $slug;
  }

  /**
   * Find the files required for this content to work.
   *
   * @param int $id for content.
   * @param null $type
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
   * @param string $prefix Optional. Make paths relative to another dir.
   */
  private function getDependencyAssets($dependency, $type, &$assets, $prefix = '') {
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
        'path' => $prefix . '/' . $dependency['path'] . '/' . trim(is_array($file) ? $file['path'] : $file),
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
      $url = $asset->path;

      // Add URL prefix if not external
      if (strpos($asset->path, '://') === FALSE) {
        $url = $this->url . $url;
      }

      // Add version/cache buster if set
      if (isset($asset->version)) {
        $url .= $asset->version;
      }

      $urls[] = $url;
    }

    return $urls;
  }

  /**
   * Return file paths for all dependencies files.
   *
   * @param array $dependencies
   * @param string $prefix Optional. Make paths relative to another dir.
   * @return array files.
   */
  public function getDependenciesFiles($dependencies, $prefix = '') {
    // Build files list for assets
    $files = array(
      'scripts' => array(),
      'styles' => array()
    );

    $key = null;

    // Avoid caching empty files
    if (empty($dependencies)) {
      return $files;
    }

    if ($this->aggregateAssets) {
      // Get aggregated files for assets
      $key = self::getDependenciesHash($dependencies);

      $cachedAssets = $this->fs->getCachedAssets($key);
      if ($cachedAssets !== NULL) {
        return array_merge($files, $cachedAssets); // Using cached assets
      }
    }

    // Using content dependencies
    foreach ($dependencies as $dependency) {
      if (isset($dependency['path']) === FALSE) {
        $dependency['path'] = 'libraries/' . H5PCore::libraryToString($dependency, TRUE);
        $dependency['preloadedJs'] = explode(',', $dependency['preloadedJs']);
        $dependency['preloadedCss'] = explode(',', $dependency['preloadedCss']);
      }
      $dependency['version'] = "?ver={$dependency['majorVersion']}.{$dependency['minorVersion']}.{$dependency['patchVersion']}";
      $this->getDependencyAssets($dependency, 'preloadedJs', $files['scripts'], $prefix);
      $this->getDependencyAssets($dependency, 'preloadedCss', $files['styles'], $prefix);
    }

    if ($this->aggregateAssets) {
      // Aggregate and store assets
      $this->fs->cacheAssets($files, $key);

      // Keep track of which libraries have been cached in case they are updated
      $this->h5pF->saveCachedAssets($key, $dependencies);
    }

    return $files;
  }

  private static function getDependenciesHash(&$dependencies) {
    // Build hash of dependencies
    $toHash = array();

    // Use unique identifier for each library version
    foreach ($dependencies as $dep) {
      $toHash[] = "{$dep['machineName']}-{$dep['majorVersion']}.{$dep['minorVersion']}.{$dep['patchVersion']}";
    }

    // Sort in case the same dependencies comes in a different order
    sort($toHash);

    // Calculate hash sum
    return hash('sha1', implode('', $toHash));
  }

  /**
   * Load library semantics.
   *
   * @param $name
   * @param $majorVersion
   * @param $minorVersion
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
   * @param $name
   * @param $majorVersion
   * @param $minorVersion
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
   * @param stdClass $libraryId
   */
  public function deleteLibrary($libraryId) {
    $this->h5pF->deleteLibrary($libraryId);
  }

  /**
   * Recursive. Goes through the dependency tree for the given library and
   * adds all the dependencies to the given array in a flat format.
   *
   * @param $dependencies
   * @param array $library To find all dependencies for.
   * @param int $nextWeight An integer determining the order of the libraries
   *  when they are loaded
   * @param bool $editor Used internally to force all preloaded sub dependencies
   *  of an editor dependency to be editor dependencies.
   * @return int
   */
  public function findLibraryDependencies(&$dependencies, $library, $nextWeight = 1, $editor = FALSE) {
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
          $nextWeight = $this->findLibraryDependencies($dependencies, $dependencyLibrary, $nextWeight, $type === 'editor');
          $dependencies[$dependencyKey]['weight'] = $nextWeight++;
        }
        else {
          // This site is missing a dependency!
          $this->h5pF->setErrorMessage($this->h5pF->t('Missing dependency @dep required by @lib.', array('@dep' => H5PCore::libraryToString($dependency), '@lib' => H5PCore::libraryToString($library))));
        }
      }
    }
    return $nextWeight;
  }

  /**
   * Check if a library is of the version we're looking for
   *
   * Same version means that the majorVersion and minorVersion is the same
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
      return false;
    }
    $files = array_diff(scandir($dir), array('.','..'));
    foreach ($files as $file) {
      (is_dir("$dir/$file")) ? self::deleteFileTree("$dir/$file") : unlink("$dir/$file");
    }
    return rmdir($dir);
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
   * @param $contentEmbedType
   * @param $libraryEmbedTypes
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
   * Determine which versions content with the given library can be upgraded to.
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
   * Detects if the site was accessed from localhost,
   * through a local network or from the internet.
   */
  public function detectSiteType() {
    $type = $this->h5pF->getOption('site_type', 'local');

    // Determine remote/visitor origin
    if ($type === 'network' ||
        ($type === 'local' &&
         isset($_SERVER['REMOTE_ADDR']) &&
         !preg_match('/^localhost$|^127(?:\.[0-9]+){0,2}\.[0-9]+$|^(?:0*\:)*?:?0*1$/i', $_SERVER['REMOTE_ADDR']))) {
      if (isset($_SERVER['REMOTE_ADDR']) && filter_var($_SERVER['REMOTE_ADDR'], FILTER_VALIDATE_IP, FILTER_FLAG_NO_PRIV_RANGE)) {
        // Internet
        $this->h5pF->setOption('site_type', 'internet');
      }
      elseif ($type === 'local') {
        // Local network
        $this->h5pF->setOption('site_type', 'network');
      }
    }
  }

  /**
   * Get a list of installed libraries, different minor versions will
   * return separate entries.
   *
   * @return array
   *  A distinct array of installed libraries
   */
  public function getLibrariesInstalled() {
    $librariesInstalled = array();
    $libs = $this->h5pF->loadLibraries();

    foreach($libs as $libName => $library) {
      foreach($library as $libVersion) {
        $librariesInstalled[$libName.' '.$libVersion->major_version.'.'.$libVersion->minor_version] = $libVersion->patch_version;
      }
    }

    return $librariesInstalled;
  }

  /**
   * Easy way to combine similar data sets.
   *
   * @param array $inputs Multiple arrays with data
   * @return array
   */
  public function combineArrayValues($inputs) {
    $results = array();
    foreach ($inputs as $index => $values) {
      foreach ($values as $key => $value) {
        $results[$key][$index] = $value;
      }
    }
    return $results;
  }

  /**
   * Fetch a list of libraries' metadata from h5p.org.
   * Save URL tutorial to database. Each platform implementation
   * is responsible for invoking this, eg using cron
   * @param bool $fetchingDisabled
   */
  public function fetchLibrariesMetadata($fetchingDisabled = FALSE) {
    // Gather data
    $uuid = $this->h5pF->getOption('site_uuid', '');
    $platform = $this->h5pF->getPlatformInfo();
    $data = array(
      'api_version' => 2,
      'uuid' => $uuid,
      'platform_name' => $platform['name'],
      'platform_version' => $platform['version'],
      'h5p_version' => $platform['h5pVersion'],
      'disabled' => $fetchingDisabled ? 1 : 0,
      'local_id' => hash('crc32', $this->fullPluginPath),
      'type' => $this->h5pF->getOption('site_type', 'local'),
      'num_authors' => $this->h5pF->getNumAuthors(),
      'libraries' => json_encode($this->combineArrayValues(array(
        'patch' => $this->getLibrariesInstalled(),
        'content' => $this->h5pF->getLibraryContentCount(),
        'loaded' => $this->h5pF->getLibraryStats('library'),
        'created' => $this->h5pF->getLibraryStats('content create'),
        'createdUpload' => $this->h5pF->getLibraryStats('content create upload'),
        'deleted' => $this->h5pF->getLibraryStats('content delete'),
        'resultViews' => $this->h5pF->getLibraryStats('results content'),
        'shortcodeInserts' => $this->h5pF->getLibraryStats('content shortcode insert')
      )))
    );

    // Send request
    $protocol = (extension_loaded('openssl') ? 'https' : 'http');
    $result = $this->h5pF->fetchExternalData("{$protocol}://h5p.org/libraries-metadata.json", $data);
    if (empty($result)) {
      return;
    }

    // Process results
    $json = json_decode($result);
    if (empty($json)) {
      return;
    }

    // Handle libraries metadata
    if (isset($json->libraries)) {
      foreach ($json->libraries as $machineName => $libInfo) {
        $this->h5pF->setLibraryTutorialUrl($machineName, $libInfo->tutorialUrl);
      }
    }

    // Handle new uuid
    if ($uuid === '' && isset($json->uuid)) {
      $this->h5pF->setOption('site_uuid', $json->uuid);
    }

    // Handle latest version of H5P
    if (!empty($json->latest)) {
      $this->h5pF->setOption('update_available', $json->latest->releasedAt);
      $this->h5pF->setOption('update_available_path', $json->latest->path);
    }
  }

  /**
   *
   */
  public function getGlobalDisable() {
    $disable = self::DISABLE_NONE;

    // Allow global settings to override and disable options
    if (!$this->h5pF->getOption('frame', TRUE)) {
      $disable |= self::DISABLE_FRAME;
    }
    else {
      if (!$this->h5pF->getOption('export', TRUE)) {
        $disable |= self::DISABLE_DOWNLOAD;
      }
      if (!$this->h5pF->getOption('embed', TRUE)) {
        $disable |= self::DISABLE_EMBED;
      }
      if (!$this->h5pF->getOption('copyright', TRUE)) {
        $disable |= self::DISABLE_COPYRIGHT;
      }
      if (!$this->h5pF->getOption('icon', TRUE)) {
        $disable |= self::DISABLE_ABOUT;
      }
    }

    return $disable;
  }

  /**
   * Determine disable state from sources.
   *
   * @param array $sources
   * @param int $current
   * @return int
   */
  public function getDisable(&$sources, $current) {
    foreach (H5PCore::$disable as $bit => $option) {
      if ($this->h5pF->getOption(($bit & H5PCore::DISABLE_DOWNLOAD ? 'export' : $option), TRUE)) {
        if (!isset($sources[$option]) || !$sources[$option]) {
          $current |= $bit; // Disable
        }
        else {
          $current &= ~$bit; // Enable
        }
      }
    }
    return $current;
  }

  /**
   * Small helper for getting the library's ID.
   *
   * @param array $library
   * @param string [$libString]
   * @return int Identifier, or FALSE if non-existent
   */
  public function getLibraryId($library, $libString = NULL) {
    if (!$libString) {
      $libString = self::libraryToString($library);
    }

    if (!isset($libraryIdMap[$libString])) {
      $libraryIdMap[$libString] = $this->h5pF->getLibraryId($library['machineName'], $library['majorVersion'], $library['minorVersion']);
    }

    return $libraryIdMap[$libString];
  }

  /**
   * Convert strings of text into simple kebab case slugs.
   * Very useful for readable urls etc.
   *
   * @param string $input
   * @return string
   */
  public static function slugify($input) {
    // Down low
    $input = strtolower($input);

    // Replace common chars
    $input = str_replace(
      array('æ',  'ø',  'ö', 'ó', 'ô', 'Ò',  'Õ', 'Ý', 'ý', 'ÿ', 'ā', 'ă', 'ą', 'œ', 'å', 'ä', 'á', 'à', 'â', 'ã', 'ç', 'ć', 'ĉ', 'ċ', 'č', 'é', 'è', 'ê', 'ë', 'í', 'ì', 'î', 'ï', 'ú', 'ñ', 'ü', 'ù', 'û', 'ß',  'ď', 'đ', 'ē', 'ĕ', 'ė', 'ę', 'ě', 'ĝ', 'ğ', 'ġ', 'ģ', 'ĥ', 'ħ', 'ĩ', 'ī', 'ĭ', 'į', 'ı', 'ĳ',  'ĵ', 'ķ', 'ĺ', 'ļ', 'ľ', 'ŀ', 'ł', 'ń', 'ņ', 'ň', 'ŉ', 'ō', 'ŏ', 'ő', 'ŕ', 'ŗ', 'ř', 'ś', 'ŝ', 'ş', 'š', 'ţ', 'ť', 'ŧ', 'ũ', 'ū', 'ŭ', 'ů', 'ű', 'ų', 'ŵ', 'ŷ', 'ź', 'ż', 'ž', 'ſ', 'ƒ', 'ơ', 'ư', 'ǎ', 'ǐ', 'ǒ', 'ǔ', 'ǖ', 'ǘ', 'ǚ', 'ǜ', 'ǻ', 'ǽ',  'ǿ'),
      array('ae', 'oe', 'o', 'o', 'o', 'oe', 'o', 'o', 'y', 'y', 'y', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'c', 'c', 'c', 'c', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'u', 'n', 'u', 'u', 'u', 'es', 'd', 'd', 'e', 'e', 'e', 'e', 'e', 'g', 'g', 'g', 'g', 'h', 'h', 'i', 'i', 'i', 'i', 'i', 'ij', 'j', 'k', 'l', 'l', 'l', 'l', 'l', 'n', 'n', 'n', 'n', 'o', 'o', 'o', 'r', 'r', 'r', 's', 's', 's', 's', 't', 't', 't', 'u', 'u', 'u', 'u', 'u', 'u', 'w', 'y', 'z', 'z', 'z', 's', 'f', 'o', 'u', 'a', 'i', 'o', 'u', 'u', 'u', 'u', 'u', 'a', 'ae', 'oe'),
      $input);

    // Replace everything else
    $input = preg_replace('/[^a-z0-9]/', '-', $input);

    // Prevent double hyphen
    $input = preg_replace('/-{2,}/', '-', $input);

    // Prevent hyphen in beginning or end
    $input = trim($input, '-');

    // Prevent to long slug
    if (strlen($input) > 91) {
      $input = substr($input, 0, 92);
    }

    // Prevent empty slug
    if ($input === '') {
      $input = 'interactive';
    }

    return $input;
  }

  /**
   * Makes it easier to print response when AJAX request succeeds.
   *
   * @param mixed $data
   * @since 1.6.0
   */
  public static function ajaxSuccess($data = NULL) {
    $response = array(
      'success' => TRUE
    );
    if ($data !== NULL) {
      $response['data'] = $data;
    }
    self::printJson($response);
  }

  /**
   * Makes it easier to print response when AJAX request fails.
   * Will exit after printing error.
   *
   * @param string $message
   * @since 1.6.0
   */
  public static function ajaxError($message = NULL) {
    $response = array(
      'success' => FALSE
    );
    if ($message !== NULL) {
      $response['message'] = $message;
    }
    self::printJson($response);
  }

  /**
   * Print JSON headers with UTF-8 charset and json encode response data.
   * Makes it easier to respond using JSON.
   *
   * @param mixed $data
   */
  private static function printJson($data) {
    header('Cache-Control: no-cache');
    header('Content-type: application/json; charset=utf-8');
    print json_encode($data);
  }

  /**
   * Get a new H5P security token for the given action.
   *
   * @param string $action
   * @return string token
   */
  public static function createToken($action) {
    if (!isset($_SESSION['h5p_token'])) {
      // Create an unique key which is used to create action tokens for this session.
      $_SESSION['h5p_token'] = uniqid();
    }

    // Timefactor
    $time_factor = self::getTimeFactor();

    // Create and return token
    return substr(hash('md5', $action . $time_factor . $_SESSION['h5p_token']), -16, 13);
  }

  /**
   * Create a time based number which is unique for each 12 hour.
   * @return int
   */
  private static function getTimeFactor() {
    return ceil(time() / (86400 / 2));
  }

  /**
   * Verify if the given token is valid for the given action.
   *
   * @param string $action
   * @param string $token
   * @return boolean valid token
   */
  public static function validToken($action, $token) {
    $time_factor = self::getTimeFactor();
    return $token === substr(hash('md5', $action . $time_factor . $_SESSION['h5p_token']), -16, 13) || // Under 12 hours
           $token === substr(hash('md5', $action . ($time_factor - 1) . $_SESSION['h5p_token']), -16, 13); // Between 12-24 hours
  }
}

/**
 * Functions for validating basic types from H5P library semantics.
 * @property bool allowedStyles
 */
class H5PContentValidator {
  public $h5pF;
  public $h5pC;
  private $typeMap, $libraries, $dependencies, $nextWeight;
  private static $allowed_styleable_tags = array('span', 'p', 'div');

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
    $this->nextWeight = 1;

    // Keep track of the libraries we load to avoid loading it multiple times.
    $this->libraries = array();

    // Keep track of all dependencies for the given content.
    $this->dependencies = array();
  }

  /**
   * Get the flat dependency tree.
   *
   * @return array
   */
  public function getDependencies() {
    return $this->dependencies;
  }

  /**
   * Validate given text value against text semantics.
   * @param $text
   * @param $semantics
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

      // Determine allowed style tags
      $stylePatterns = array();
      // All styles must be start to end patterns (^...$)
      if (isset($semantics->font)) {
        if (isset($semantics->font->size) && $semantics->font->size) {
          $stylePatterns[] = '/^font-size: *[0-9.]+(em|px|%) *;?$/i';
        }
        if (isset($semantics->font->family) && $semantics->font->family) {
          $stylePatterns[] = '/^font-family: *[a-z0-9," ]+;?$/i';
        }
        if (isset($semantics->font->color) && $semantics->font->color) {
          $stylePatterns[] = '/^color: *(#[a-f0-9]{3}[a-f0-9]{3}?|rgba?\([0-9, ]+\)) *;?$/i';
        }
        if (isset($semantics->font->background) && $semantics->font->background) {
          $stylePatterns[] = '/^background-color: *(#[a-f0-9]{3}[a-f0-9]{3}?|rgba?\([0-9, ]+\)) *;?$/i';
        }
        if (isset($semantics->font->spacing) && $semantics->font->spacing) {
          $stylePatterns[] = '/^letter-spacing: *[0-9.]+(em|px|%) *;?$/i';
        }
        if (isset($semantics->font->height) && $semantics->font->height) {
          $stylePatterns[] = '/^line-height: *[0-9.]+(em|px|%|) *;?$/i';
        }
      }

      // Alignment is allowed for all wysiwyg texts
      $stylePatterns[] = '/^text-align: *(center|left|right);?$/i';

      // Strip invalid HTML tags.
      $text = $this->filter_xss($text, $tags, $stylePatterns);
    }
    else {
      // Filter text to plain text.
      $text = htmlspecialchars($text, ENT_QUOTES, 'UTF-8', FALSE);
    }

    // Check if string is within allowed length
    if (isset($semantics->maxLength)) {
      if (!extension_loaded('mbstring')) {
        $this->h5pF->setErrorMessage($this->h5pF->t('The mbstring PHP extension is not loaded. H5P need this to function properly'), 'error');
      }
      else {
        $text = mb_substr($text, 0, $semantics->maxLength);
      }
    }

    // Check if string is according to optional regexp in semantics
    if (!($text === '' && isset($semantics->optional) && $semantics->optional) && isset($semantics->regexp)) {
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
   *  The path containing content files to validate.
   * @param bool $isLibrary
   * @return bool TRUE if all files are valid
   * TRUE if all files are valid
   * FALSE if one or more files fail validation. Error message should be set accordingly by validator.
   */
  public function validateContentFiles($contentPath, $isLibrary = FALSE) {
    if ($this->h5pC->disableFileCheck === TRUE) {
      return TRUE;
    }

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
        if (!extension_loaded('mbstring')) {
          $this->h5pF->setErrorMessage($this->h5pF->t('The mbstring PHP extension is not loaded. H5P need this to function properly'), 'error');
          $valid = FALSE;
        }
        else if (!preg_match($wl_regex, mb_strtolower($file))) {
          $this->h5pF->setErrorMessage($this->h5pF->t('File "%filename" not allowed. Only files with the following extensions are allowed: %files-allowed.', array('%filename' => $file, '%files-allowed' => $whitelist)), 'error');
          $valid = FALSE;
        }
      }
    }
    return $valid;
  }

  /**
   * Validate given value against number semantics
   * @param $number
   * @param $semantics
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
      $testNumber = $number - (isset($semantics->min) ? $semantics->min : 0);
      $rest = $testNumber % $semantics->step;
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
   * @param $bool
   * @return bool
   */
  public function validateBoolean(&$bool) {
    return is_bool($bool);
  }

  /**
   * Validate select values
   * @param $select
   * @param $semantics
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
      // Multi-choice generates array of values. Test each one against valid
      // options, if we are strict.  First make sure we are working on an
      // array.
      if (!is_array($select)) {
        $select = array($select);
      }

      foreach ($select as $key => &$value) {
        if ($strict && !isset($options[$value])) {
          $this->h5pF->setErrorMessage($this->h5pF->t('Invalid selected option in multi-select.'));
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
   * Validate given list value against list semantics.
   * Will recurse into validating each item in the list according to the type.
   * @param $list
   * @param $semantics
   */
  public function validateList(&$list, $semantics) {
    $field = $semantics->field;
    $function = $this->typeMap[$field->type];

    // Check that list is not longer than allowed length. We do this before
    // iterating to avoid unnecessary work.
    if (isset($semantics->max)) {
      array_splice($list, $semantics->max);
    }

    if (!is_array($list)) {
      $list = array();
    }

    // Validate each element in list.
    foreach ($list as $key => &$value) {
      if (!is_int($key)) {
        array_splice($list, $key, 1);
        continue;
      }
      $this->$function($value, $field);
      if ($value === NULL) {
        array_splice($list, $key, 1);
      }
    }

    if (count($list) === 0) {
      $list = NULL;
    }
  }

  /**
   * Validate a file like object, such as video, image, audio and file.
   * @param $file
   * @param $semantics
   * @param array $typeValidKeys
   */
  private function _validateFilelike(&$file, $semantics, $typeValidKeys = array()) {
    // Do not allow to use files from other content folders.
    $matches = array();
    if (preg_match($this->h5pC->relativePathRegExp, $file->path, $matches)) {
      $file->path = $matches[5];
    }

    // Make sure path and mime does not have any special chars
    $file->path = htmlspecialchars($file->path, ENT_QUOTES, 'UTF-8', FALSE);
    if (isset($file->mime)) {
      $file->mime = htmlspecialchars($file->mime, ENT_QUOTES, 'UTF-8', FALSE);
    }

    // Remove attributes that should not exist, they may contain JSON escape
    // code.
    $validKeys = array_merge(array('path', 'mime', 'copyright'), $typeValidKeys);
    if (isset($semantics->extraAttributes)) {
      $validKeys = array_merge($validKeys, $semantics->extraAttributes); // TODO: Validate extraAttributes
    }
    $this->filterParams($file, $validKeys);

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
      $this->validateGroup($file->copyright, $this->getCopyrightSemantics());
    }
  }

  /**
   * Validate given file data
   * @param $file
   * @param $semantics
   */
  public function validateFile(&$file, $semantics) {
    $this->_validateFilelike($file, $semantics);
  }

  /**
   * Validate given image data
   * @param $image
   * @param $semantics
   */
  public function validateImage(&$image, $semantics) {
    $this->_validateFilelike($image, $semantics, array('width', 'height', 'originalImage'));
  }

  /**
   * Validate given video data
   * @param $video
   * @param $semantics
   */
  public function validateVideo(&$video, $semantics) {
    foreach ($video as &$variant) {
      $this->_validateFilelike($variant, $semantics, array('width', 'height', 'codecs', 'quality'));
    }
  }

  /**
   * Validate given audio data
   * @param $audio
   * @param $semantics
   */
  public function validateAudio(&$audio, $semantics) {
    foreach ($audio as &$variant) {
      $this->_validateFilelike($variant, $semantics);
    }
  }

  /**
   * Validate given group value against group semantics.
   * Will recurse into validating each group member.
   * @param $group
   * @param $semantics
   * @param bool $flatten
   */
  public function validateGroup(&$group, $semantics, $flatten = TRUE) {
    // Groups with just one field are compressed in the editor to only output
    // the child content. (Exemption for fake groups created by
    // "validateBySemantics" above)
    $function = null;
    $field = null;

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
            if (isset($semantics->optional) && $semantics->optional) {
              $field->optional = TRUE;
            }
            $function = $this->typeMap[$field->type];
            $found = TRUE;
            break;
          }
        }
        if ($found) {
          if ($function) {
            $this->$function($value, $field);
            if ($value === NULL) {
              unset($group->$key);
            }
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
          // $this->h5pF->setErrorMessage($this->h5pF->t('H5P internal error: no validator exists for @key', array('@key' => $key)));
          unset($group->$key);
        }
      }
    }
    if (!(isset($semantics->optional) && $semantics->optional)) {
      if ($group === NULL) {
        // Error no value. Errors aren't printed...
        return;
      }
      foreach ($semantics->fields as $field) {
        if (!(isset($field->optional) && $field->optional)) {
          // Check if field is in group.
          if (! property_exists($group, $field->name)) {
            //$this->h5pF->setErrorMessage($this->h5pF->t('No value given for mandatory field ' . $field->name));
          }
        }
      }
    }
  }

  /**
   * Validate given library value against library semantics.
   * Check if provided library is within allowed options.
   *
   * Will recurse into validating the library's semantics too.
   * @param $value
   * @param $semantics
   */
  public function validateLibrary(&$value, $semantics) {
    if (!isset($value->library)) {
      $value = NULL;
      return;
    }
    if (!in_array($value->library, $semantics->options)) {
      $this->h5pF->setErrorMessage($this->h5pF->t('Library used in content is not a valid library according to semantics'));
      $value = NULL;
      return;
    }

    if (!isset($this->libraries[$value->library])) {
      $libSpec = H5PCore::libraryFromString($value->library);
      $library = $this->h5pC->loadLibrary($libSpec['machineName'], $libSpec['majorVersion'], $libSpec['minorVersion']);
      $library['semantics'] = $this->h5pC->loadLibrarySemantics($libSpec['machineName'], $libSpec['majorVersion'], $libSpec['minorVersion']);
      $this->libraries[$value->library] = $library;
    }
    else {
      $library = $this->libraries[$value->library];
    }

    $this->validateGroup($value->params, (object) array(
      'type' => 'group',
      'fields' => $library['semantics'],
    ), FALSE);
    $validKeys = array('library', 'params', 'subContentId');
    if (isset($semantics->extraAttributes)) {
      $validKeys = array_merge($validKeys, $semantics->extraAttributes);
    }
    $this->filterParams($value, $validKeys);
    if (isset($value->subContentId) && ! preg_match('/^\{?[a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12}\}?$/', $value->subContentId)) {
      unset($value->subContentId);
    }

    // Find all dependencies for this library
    $depKey = 'preloaded-' . $library['machineName'];
    if (!isset($this->dependencies[$depKey])) {
      $this->dependencies[$depKey] = array(
        'library' => $library,
        'type' => 'preloaded'
      );

      $this->nextWeight = $this->h5pC->findLibraryDependencies($this->dependencies, $library, $this->nextWeight);
      $this->dependencies[$depKey]['weight'] = $this->nextWeight++;
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
   * @param array $allowed_tags
   *   An array of allowed tags.
   *
   * @param bool $allowedStyles
   * @return mixed|string An XSS safe version of $string, or an empty string if $string is not
   * An XSS safe version of $string, or an empty string if $string is not
   * valid UTF-8.
   * @ingroup sanitation
   */
  private function filter_xss($string, $allowed_tags = array('a', 'em', 'strong', 'cite', 'blockquote', 'code', 'ul', 'ol', 'li', 'dl', 'dt', 'dd'), $allowedStyles = FALSE) {
    if (strlen($string) == 0) {
      return $string;
    }
    // Only operate on valid UTF-8 strings. This is necessary to prevent cross
    // site scripting issues on Internet Explorer 6. (Line copied from
    // drupal_validate_utf8)
    if (preg_match('/^./us', $string) != 1) {
      return '';
    }

    $this->allowedStyles = $allowedStyles;

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
   * @param bool $store
   *   Whether to store $m.
   * @return string If the element isn't allowed, an empty string. Otherwise, the cleaned up
   * If the element isn't allowed, an empty string. Otherwise, the cleaned up
   * version of the HTML element.
   */
  private function _filter_xss_split($m, $store = FALSE) {
    static $allowed_html;

    if ($store) {
      $allowed_html = array_flip($m);
      return $allowed_html;
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

    if (!preg_match('%^<\s*(/\s*)?([a-zA-Z0-9\-]+)([^>]*)>?|(<!--.*?-->)$%', $string, $matches)) {
      // Seriously malformed.
      return '';
    }

    $slash = trim($matches[1]);
    $elem = &$matches[2];
    $attrList = &$matches[3];
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
    $attrList = preg_replace('%(\s?)/\s*$%', '\1', $attrList, -1, $count);
    $xhtml_slash = $count ? ' /' : '';

    // Clean up attributes.

    $attr2 = implode(' ', $this->_filter_xss_attributes($attrList, (in_array($elem, self::$allowed_styleable_tags) ? $this->allowedStyles : FALSE)));
    $attr2 = preg_replace('/[<>]/', '', $attr2);
    $attr2 = strlen($attr2) ? ' ' . $attr2 : '';

    return "<$elem$attr2$xhtml_slash>";
  }

  /**
   * Processes a string of HTML attributes.
   *
   * @param $attr
   * @param array|bool|object $allowedStyles
   * @return array Cleaned up version of the HTML attributes.
   * Cleaned up version of the HTML attributes.
   */
  private function _filter_xss_attributes($attr, $allowedStyles = FALSE) {
    $attrArr = array();
    $mode = 0;
    $attrName = '';
    $skip = false;

    while (strlen($attr) != 0) {
      // Was the last operation successful?
      $working = 0;
      switch ($mode) {
        case 0:
          // Attribute name, href for instance.
          if (preg_match('/^([-a-zA-Z]+)/', $attr, $match)) {
            $attrName = strtolower($match[1]);
            $skip = ($attrName == 'style' || substr($attrName, 0, 2) == 'on');
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
              $attrArr[] = $attrName;
            }
            $attr = preg_replace('/^\s+/', '', $attr);
          }
          break;

        case 2:
          // Attribute value, a URL after href= for instance.
          if (preg_match('/^"([^"]*)"(\s+|$)/', $attr, $match)) {
            if ($allowedStyles && $attrName === 'style') {
              // Allow certain styles
              foreach ($allowedStyles as $pattern) {
                if (preg_match($pattern, $match[1])) {
                  // All patterns are start to end patterns, and CKEditor adds one span per style
                  $attrArr[] = 'style="' . $match[1] . '"';
                  break;
                }
              }
              break;
            }

            $thisVal = $this->filter_xss_bad_protocol($match[1]);

            if (!$skip) {
              $attrArr[] = "$attrName=\"$thisVal\"";
            }
            $working = 1;
            $mode = 0;
            $attr = preg_replace('/^"[^"]*"(\s+|$)/', '', $attr);
            break;
          }

          if (preg_match("/^'([^']*)'(\s+|$)/", $attr, $match)) {
            $thisVal = $this->filter_xss_bad_protocol($match[1]);

            if (!$skip) {
              $attrArr[] = "$attrName='$thisVal'";
            }
            $working = 1; $mode = 0;
            $attr = preg_replace("/^'[^']*'(\s+|$)/", '', $attr);
            break;
          }

          if (preg_match("%^([^\s\"']+)(\s+|$)%", $attr, $match)) {
            $thisVal = $this->filter_xss_bad_protocol($match[1]);

            if (!$skip) {
              $attrArr[] = "$attrName=\"$thisVal\"";
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
      $attrArr[] = $attrName;
    }
    return $attrArr;
  }

// TODO: Remove Drupal related stuff in docs.

  /**
   * Processes an HTML attribute value and strips dangerous protocols from URLs.
   *
   * @param $string
   *   The string with the attribute value.
   * @param bool $decode
   *   (deprecated) Whether to decode entities in the $string. Set to FALSE if the
   *   $string is in plain text, TRUE otherwise. Defaults to TRUE. This parameter
   *   is deprecated and will be removed in Drupal 8. To process a plain-text URI,
   *   call _strip_dangerous_protocols() or check_url() instead.
   * @return string Cleaned up and HTML-escaped version of $string.
   * Cleaned up and HTML-escaped version of $string.
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
   * @return string A plain-text URI stripped of dangerous protocols. As with all plain-text
   * A plain-text URI stripped of dangerous protocols. As with all plain-text
   * strings, this return value must not be output to an HTML page without
   * check_plain() being called on it. However, it can be passed to functions
   * expecting plain-text strings.
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
      $colonPos = strpos($uri, ':');
      if ($colonPos > 0) {
        // We found a colon, possibly a protocol. Verify.
        $protocol = substr($uri, 0, $colonPos);
        // If a colon is preceded by a slash, question mark or hash, it cannot
        // possibly be part of the URL scheme. This must be a relative URL, which
        // inherits the (safe) protocol of the base document.
        if (preg_match('![/?#]!', $protocol)) {
          break;
        }
        // Check if this is a disallowed protocol. Per RFC2616, section 3.2.3
        // (URI Comparison) scheme comparison must be case-insensitive.
        if (!isset($allowed_protocols[strtolower($protocol)])) {
          $uri = substr($uri, $colonPos + 1);
        }
      }
    } while ($before != $uri);

    return $uri;
  }

  public function getCopyrightSemantics() {
    static $semantics;

    if ($semantics === NULL) {
      $semantics = (object) array(
        'name' => 'copyright',
        'type' => 'group',
        'label' => $this->h5pF->t('Copyright information'),
        'fields' => array(
          (object) array(
            'name' => 'title',
            'type' => 'text',
            'label' => $this->h5pF->t('Title'),
            'placeholder' => 'La Gioconda',
            'optional' => TRUE
          ),
          (object) array(
            'name' => 'author',
            'type' => 'text',
            'label' => $this->h5pF->t('Author'),
            'placeholder' => 'Leonardo da Vinci',
            'optional' => TRUE
          ),
          (object) array(
            'name' => 'year',
            'type' => 'text',
            'label' => $this->h5pF->t('Year(s)'),
            'placeholder' => '1503 - 1517',
            'optional' => TRUE
          ),
          (object) array(
            'name' => 'source',
            'type' => 'text',
            'label' => $this->h5pF->t('Source'),
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
            'label' => $this->h5pF->t('License'),
            'default' => 'U',
            'options' => array(
              (object) array(
                'value' => 'U',
                'label' => $this->h5pF->t('Undisclosed')
              ),
              (object) array(
                'value' => 'CC BY',
                'label' => $this->h5pF->t('Attribution 4.0')
              ),
              (object) array(
                'value' => 'CC BY-SA',
                'label' => $this->h5pF->t('Attribution-ShareAlike 4.0')
              ),
              (object) array(
                'value' => 'CC BY-ND',
                'label' => $this->h5pF->t('Attribution-NoDerivs 4.0')
              ),
              (object) array(
                'value' => 'CC BY-NC',
                'label' => $this->h5pF->t('Attribution-NonCommercial 4.0')
              ),
              (object) array(
                'value' => 'CC BY-NC-SA',
                'label' => $this->h5pF->t('Attribution-NonCommercial-ShareAlike 4.0')
              ),
              (object) array(
                'value' => 'CC BY-NC-ND',
                'label' => $this->h5pF->t('Attribution-NonCommercial-NoDerivs 4.0')
              ),
              (object) array(
                'value' => 'GNU GPL',
                'label' => $this->h5pF->t('General Public License v3')
              ),
              (object) array(
                'value' => 'PD',
                'label' => $this->h5pF->t('Public Domain')
              ),
              (object) array(
                'value' => 'ODC PDDL',
                'label' => $this->h5pF->t('Public Domain Dedication and Licence')
              ),
              (object) array(
                'value' => 'CC PDM',
                'label' => $this->h5pF->t('Public Domain Mark')
              ),
              (object) array(
                'value' => 'C',
                'label' => $this->h5pF->t('Copyright')
              )
            )
          )
        )
      );
    }

    return $semantics;
  }
}
