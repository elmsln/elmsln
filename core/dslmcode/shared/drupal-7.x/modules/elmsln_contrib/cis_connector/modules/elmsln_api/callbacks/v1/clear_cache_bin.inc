<?php

/**
 * Callback to clear a cache bin from remote
 * @param  string $bin the cache bin to clear, usually cis_connector
 * @return bool if it was successfully cleared
 */
function elmsln_api_elmsln_api_callback_clear_cache_bin() {
  global $_elmsln;
  // @todo try and use elmsln instead
  // convert to cache bin name
  if (isset($_POST['bin'])) {
    $bin = $_POST['bin'];
  }
  else if (isset($_GET['bin'])) {
    $bin = $_GET['bin'];
  }
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
