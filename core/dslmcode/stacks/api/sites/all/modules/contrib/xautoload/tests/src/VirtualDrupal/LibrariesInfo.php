<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class LibrariesInfo {

  /**
   * @var DrupalStatic
   */
  private $drupalStatic;

  /**
   * @var HookSystem
   */
  private $hookSystem;

  /**
   * @param DrupalStatic $drupalStatic
   * @param HookSystem $hookSystem
   */
  function __construct(DrupalStatic $drupalStatic, HookSystem $hookSystem) {
    $this->drupalStatic = $drupalStatic;
    $this->hookSystem = $hookSystem;
  }

  /**
   * @see libraries_info()
   *
   * @param string|null $name
   *
   * @return mixed
   */
  function &getLibrariesInfo($name = NULL) {
    // This static cache is re-used by libraries_detect() to save memory.
    $libraries = &$this->drupalStatic->get('libraries_info');

    if (!isset($libraries)) {
      $libraries = array();
      // Gather information from hook_libraries_info().
      foreach ($this->hookSystem->moduleImplements('libraries_info') as $module) {
        foreach (PureFunctions::moduleInvoke($module, 'libraries_info') as $machine_name => $properties) {
          $properties['module'] = $module;
          $libraries[$machine_name] = $properties;
        }
      }

      // Gather information from hook_libraries_info() in enabled themes.
      // @see drupal_alter()
      // SKIPPED

      // Gather information from .info files.
      // .info files override module definitions.
      // SKIPPED

      // Provide defaults.
      foreach ($libraries as $machine_name => &$properties) {
        $this->librariesInfoDefaults($properties, $machine_name);
      }

      // Allow modules to alter the registered libraries.
      $this->hookSystem->drupalAlter('libraries_info', $libraries);

      // Invoke callbacks in the 'info' group.
      // SKIPPED
    }

    if (isset($name)) {
      if (!empty($libraries[$name])) {
        return $libraries[$name];
      }
      else {
        $false = FALSE;
        return $false;
      }
    }

    return $libraries;
  }

  /**
   * @see libraries_info_defaults()
   *
   * @param array $library
   * @param string $name
   *
   * @return array
   */
  private function librariesInfoDefaults(&$library, $name) {
    $library += array(
      'machine name' => $name,
      'name' => $name,
      'vendor url' => '',
      'download url' => '',
      'path' => '',
      'library path' => NULL,
      'version callback' => 'libraries_get_version',
      'version arguments' => array(),
      'files' => array(),
      'dependencies' => array(),
      'variants' => array(),
      'versions' => array(),
      'integration files' => array(),
      'callbacks' => array(),
    );
    $library['callbacks'] += array(
      'info' => array(),
      'pre-detect' => array(),
      'post-detect' => array(),
      'pre-dependencies-load' => array(),
      'pre-load' => array(),
      'post-load' => array(),
    );

    // Add our own callbacks before any others.
    array_unshift($library['callbacks']['info'], 'libraries_prepare_files');
    array_unshift($library['callbacks']['post-detect'], 'libraries_detect_dependencies');

    return $library;
  }

  /**
   * @see libraries_get_path()
   *
   * @param string $name
   * @param string|bool $base_path
   *
   * @return string|bool
   */
  public function librariesGetPath($name, $base_path = FALSE) {
    $libraries = &$this->drupalStatic->get('libraries_get_path');

    if (!isset($libraries)) {
      $libraries = $this->librariesGetLibraries();
    }

    $path = ($base_path ? base_path() : '');
    if (!isset($libraries[$name])) {
      return FALSE;
    }
    else {
      $path .= $libraries[$name];
    }

    return $path;
  }

  /**
   * @see libraries_get_libraries()
   */
  private function librariesGetLibraries() {
    $searchdir = array();
    # $profile = drupal_get_path('profile', drupal_get_profile());
    # $config = conf_path();

    // Similar to 'modules' and 'themes' directories in the root directory,
    // certain distributions may want to place libraries into a 'libraries'
    // directory in Drupal's root directory.
    # $searchdir[] = 'libraries';

    // Similar to 'modules' and 'themes' directories inside an installation
    // profile, installation profiles may want to place libraries into a
    // 'libraries' directory.
    # $searchdir[] = "$profile/libraries";

    // Always search sites/all/libraries.
    # $searchdir[] = 'sites/all/libraries';

    // Also search sites/<domain>/*.
    # $searchdir[] = "$config/libraries";

    // Custom location to search
    $searchdir[] = dirname(dirname(__DIR__)) . '/fixtures/.libraries';

    // Retrieve list of directories.
    $directories = array();
    $nomask = array('CVS');
    foreach ($searchdir as $dir) {
      if (is_dir($dir) && $handle = opendir($dir)) {
        while (FALSE !== ($file = readdir($handle))) {
          if (!in_array($file, $nomask) && $file[0] != '.') {
            if (is_dir("$dir/$file")) {
              $directories[$file] = "$dir/$file";
            }
          }
        }
        closedir($handle);
      }
    }

    return $directories;
  }

  public function resetLibrariesInfo() {
    $this->drupalStatic->resetKey('libraries_info');
  }
}
