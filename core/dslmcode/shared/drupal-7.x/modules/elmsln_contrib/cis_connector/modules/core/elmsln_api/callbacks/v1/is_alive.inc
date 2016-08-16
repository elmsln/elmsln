<?php

/**
 * Callback to clear a cache bin from remote
 * @return bool if it was successfully cleared
 */
function elmsln_api_elmsln_api_callback_is_alive() {
  global $_elmsln;
  // just getting here implies that drupal exists at this location
  return array(
    'is_alive' => TRUE,
    'message' => 'This site is alive',
  );
}
