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
 *
 * While this is how you can author your own keychain, there is a function in
 * the elmsln/scripts/install/elmsln-install.sh that automatically produces
 * one of these.  It is recommended you use this and then modify from there when
 * building and deploying production networks.
 */
function hook_cis_service_registry() {
  // service module that makes our implementation specific
  return array(
    'distro_name' => array(
      'variable' => 'value',
      ),
    // this example is from how CIS uses this
    'cis' => array(// Course Information System distribution
      'protocol' => 'https',// base protocol for address calls; commonly https or http
      'service_address' => 'data.online.example.com',// address to make calls over, this can be the same as address but for added security an alternate domain is recommended
      'address' => 'online.example.com',// address to connect to for CIS data
      'user' => 'SERVICE_CIS_YZ',// special user account with HTTP authentication access
      'pass' => 'password',// password for that connection account
      'mail' => 'account@example.com',// email address for associated account connection
      'instance' => FALSE,// if this is a per instance distro or single system
      'default_title' => 'Course Information System',// default title
      'ignore' => TRUE,// optional: if this should be ignored when aligning with the registry
    ),
    // this example is from how MOOC would use this
    'mooc' => array(
      'protocol' => 'https',
      'service_address' => 'data.courses.example.com',
      'address' => 'courses.example.com',
      'user' => 'SERVICE_MOOC_YZ',
      'pass' => 'password',
      'mail' => 'account@example.com',
      'instance' => TRUE,
      'default_title' => 'Course Outline',
      // optional: jobs for this distro should be ssh'ed into another server
      // this allows for multiple ELMSLN deployments to act as one!
      // you'll need to establish SSH key binding between the systems
      // ahead of time in order to take advantage of this capability
      'ssh' => array(
        'options' => '-p 22', // options to use for the server
        'user' => 'username', // username to use for the connection
        'host' => 'courses.example.com', // server address to ssh into
      ),
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
 * Implements hook_cis_prerequest_alter().
 *
 * Provide access to the properties of a request prior to issuing the call.
 * This can be used to debug calls or dynamically reroute certain calls
 * elsewhere
 *
 * @param  string  &$request['url']     url used to issue the call
 * @param  array   &$request['options'] httprl options used to issue the call
 * @param  string  &$request['bucket']  bucket used to issue the call
 * @param  boolean &$request['cached']  whether to use local cache for response
 *
 * @see  cis_devel.module for an example
 */
function hook_cis_prerequest_alter(&$request) {
  $request['cached'] = FALSE;
}

/**
 * Implements hook_cis_postrequest_alter().
 *
 * Provide calls issued and the data returned from the request.
 * This can be used to influence the data after its been received from
 * the source determined by the other parameters in the call.
 *
 * @param  array   &$request['data']    response from th webservice call
 * @param  string  &$request['url']     url used to issue the call
 * @param  array   &$request['options'] httprl options used to issue the call
 * @param  string  &$request['bucket']  bucket used to issue the call
 * @param  boolean &$request['cached']  whether to use local cache for response
 *
 * @see  cis_devel.module for an example
 */
function hook_cis_postrequest_alter(&$request) {
  // @ignore production_code
  dpm($request);
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
