<?php
/**
 * @file
 * CIS Connector API documentation.
 *
 * This demonstrates some ways you can implement the CIS connect
 * API using real use cases from the original site instance at
 * penn state.
 */

/**
 * Implements hook_cis_service_registry().
 *
 * distro_name - machine name bucket for settings, distro provides namespace
 * variable - a value to store in the registry with its value
 *
 * Typically this function is only invoked when implementing in large scale
 * implementations of distributions that all talk to each other.
 * It is the backbone of the Suite of tools approach to LMS design.
 */
function hook_cis_service_registry() {
  // service module that makes our implementation specific
  return array(
    'distro_name' => array(
      'variable' => 'value',
      ),
    // this example is from how CIS uses this
    'cis' => array(// Course Information System distribution
      'protocol' => 'http',// base protocol for address calls; commonly https or http
      'service_address' => 'datachannel.example.com',// address to make calls over, this can be the same as address but for added security an alternate domain is recommended
      'address' => 'www.example.com',// address to connect to for CIS data
      'user' => 'account',// special user account with HTTP authentication access
      'pass' => 'password',// password for that connection account
      'mail' => 'account@example.com',// optional email address for associated account connection
      'instance' => FALSE,// if this is a per instance distro or single system
    ),
  );
}

/**
 * Implements hook_cis_service_registry_alter().
 *
 * alter information provided by other registry statements
 */
function hook_cis_service_registry_alter(&$registry) {
  // divert to a different connection address on a specific site
  $registry['cis']['address'] = 'www.example2.com';
}

/**
 * Implements hook_cis_connected_entity().
 *
 * Define which and how entities can be used remotely.
 */
function hook_cis_connected_entity() {
  $items = array(
    // namespace helps allow for per bundle like node type1 / type2
    // to be defined by other modules independently
    'namespace' => array(
      // entity type
      'type' => 'entity type',
      // bundle of that entity
      'bundle' => 'bundle type',
      // which cis buckets to write to
      'buckets' => array('bucket1', 'bucket2'),
      // how to save the item
      // CIS_CONNECTOR_ENTITY_REMOTE_ONLY is for remote only
      // CIS_CONNECTOR_ENTITY_BOTH is for saving locally and shipping off remotely
      'save' => CIS_CONNECTOR_ENTITY_REMOTE_ONLY,
      // additional options for
      'options' => array('blocking' => FALSE),
    ),
  );
  return $items;
}

/**
 * Implements hook_cis_connected_entity_alter().
 *
 * @param $items
 *   All collected items to be transmitted to a remote source.
 */
function hook_cis_connected_entity_alter(&$items) {
  // allow for modification of the items array
  $items['namespace']['options'] = array();
}

/**
 * Implements hook_cis_remote_entities_insert_alter().
 *
 * @param $return
 *   Do something with the returned data, typically
 *   the `nid` or `uuid` created in the remote bucket.
 * @param $bucket
 *   which bucket this is in reference to.
 */
function hook_cis_remote_entities_insert(&$return, $bucket) {
  // turn this into a direct link for a node
  $tmp = drupal_json_decode($return);
  $settings = _cis_connector_build_registry($bucket);
  $url = $settings['protocol'] . '://' . $settings['address'] . '/node/' . $return['nid'];
  $return = l(t('click to access item'), $url);
}
