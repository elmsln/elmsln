<?php

/**
 * Callback to set a variable based on remote data coming in
 * @return bool if it was successfully cleared
 */
function elmsln_api_elmsln_api_callback_vset() {
  global $_elmsln;
  if (isset($_elmsln['args']['name']) && isset($_elmsln['args']['value'])) {
    // wow that was easy
    variable_set($_elmsln['args']['name'], $_elmsln['args']['value']);
    return array(
      'vset' => TRUE,
      'name' => $_elmsln['args']['name'],
      'value' => $_elmsln['args']['value'],
      'message' => "remote variable updated successfully",
    );
  }
  return FALSE;
}
