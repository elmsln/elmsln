<?php

/**
 * Callback to clear a cache bin from remote
 * @param  string $bin the cache bin to clear, usually cis_connector
 * @return bool if it was successfully cleared
 */
function cis_section_elmsln_api_callback_sync_roster() {
  global $_elmsln;
  _cis_section_sync_roster();
  return array(
    'roster_synced' => TRUE,
    'message' => "Roster synced successfully",
  );
}
