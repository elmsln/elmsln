<?php

/**
 * Callback to clear a cache bin from remote
 * @param  string $bin the cache bin to clear, usually cis_connector
 * @return bool if it was successfully cleared
 */
function elmsln_api_elmsln_api_callback_clear_cache_bin($bin) {
  // convert to cache bin name
  $bin = 'cache_' . $bin;
  if (db_table_exists($bin)) {
    $db = db_delete($bin)->execute();
    return array(
        'cleared' => TRUE,
        'bin' => $bin,
        'message' => "$bin cleared successfully",
      );
  }
  return FALSE;
}
