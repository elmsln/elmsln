<?php


/**
 * This class is not used anywhere in xautoload, but could be used by other
 * modules.
 */
class xautoload_FinderPlugin_CheckIncludePath implements xautoload_FinderPlugin_Interface {

  /**
   * {@inheritdoc}
   */
  function findFile($api, $logical_base_path, $relative_path) {
    $path = $logical_base_path . $relative_path;
    return $api->suggestFile_checkIncludePath($path);
  }
}
