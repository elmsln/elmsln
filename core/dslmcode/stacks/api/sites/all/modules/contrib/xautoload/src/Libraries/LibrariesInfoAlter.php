<?php


namespace Drupal\xautoload\Libraries;


class LibrariesInfoAlter {

  /**
   * Empty constructor.
   *
   * Required for versions of PHP under 5.3.3, to prevent fallback to
   * librariesInfoAlter() as the default constructor.
   */
  function __construct() {

  }

  /**
   * @param array $info
   *
   * @see hook_libraries_info_alter()
   * @see xautoload_libraries_info_alter()
   */
  function librariesInfoAlter(&$info) {
    foreach ($info as $library_name => &$library_info) {
      if (1
        && isset($library_info['xautoload'])
        && is_callable($library_info['xautoload'])
      ) {
        $this->alterLibraryInfo($library_info, $library_name);
      }
    }
  }

  /**
   * @param array $library_info
   * @param string $library_name
   */
  private function alterLibraryInfo(&$library_info, $library_name) {
    $callable = $library_info['xautoload'];
    if ($callable instanceof \Closure) {
      // Wrap the closure so it can be serialized.
      $callable = new SerializableClosureWrapper(
        $library_info['xautoload'],
        // The module name and library name allow the closure to be recovered on
        // unserialize.
        $library_info['module'],
        $library_name);
      $library_info['xautoload'] = $callable;
    }
    # $library_info['callbacks']['pre-load'][] = new LibrariesPreLoadCallback($callable);
  }

} 
