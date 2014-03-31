<?php
/**
 * @file
 * API for settings certain service connection data at intervals.
 */
/**
 * Implements hook_set_cis_service_data().
 *
 * @param $delta
 *   An interval in the syncronization of the system. Possible
 *   values are initial, interval, weekly, monthly, yearly with
 *   new deltas able to be defined through custom code.
 * @return array
 *   array of key-pairs for data to set in the CIS service-instance.
 */
function hook_set_cis_service_data($delta) {
  // only set this when the first run happens
  if ($delta == 'initial') {
    return array(
      'field_in_cis_service_content_type' => 'value to set',
    );
  }
}