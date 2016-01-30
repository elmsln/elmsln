<?php

/**
 * Callback to clear a cache bin from remote
 * @return bool if it was successfully cleared
 */
function elmsln_api_elmsln_api_callback_clear_cache_bin() {
  global $_elmsln;
  // ensure it's set
  if (isset($_elmsln['args']['bin'])) {
    // convert to cache bin name
    $bin = 'cache_' . $_elmsln['args']['bin'];
    // make sure the bin exists
    if (db_table_exists($bin)) {
      $db = db_delete($bin)->execute();
      return array(
        'cleared' => TRUE,
        'bin' => $bin,
        'message' => "$bin cleared successfully",
      );
    }
  }
  return FALSE;
}
