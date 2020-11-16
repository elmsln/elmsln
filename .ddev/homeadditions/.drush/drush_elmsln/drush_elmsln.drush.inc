<?php
/**
 * @file
 * drush integration for elmsln deployments
 */

define('ELMSLN_DATA_HOME', 'https://data.elmsln.org');

/**
 * Implementation of hook_drush_help().
 */
function drush_elmsln_drush_help($section) {
  switch ($section) {
    case 'drush:elmsln-call-home':
      return dt('ELMSLN send data back to base');
    case 'drush:elmsln-add-stack-instance-container':
      return dt('ELMSLN create a new stub within the instance stacks to be able to support new tools without getting into git VC hell (potential).');
    case 'drush:elmsln-trigger-innovate':
      return dt('Trigger the innovate script to fire');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function drush_elmsln_drush_command() {
  $items = array();
  $items['elmsln-call-home'] = array(
    'callback' => 'drush_elmsln_call_home',
    'description' => dt('Call home with certain data. Home being the elmsln data bank.'),
    'arguments' => array(
      'type' => dt('Data routine to mine and send back'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['elmsln-add-stack-instance-container'] = array(
    'callback' => 'drush_elmsln_add_stack_instance_container',
    'description' => dt('Add a new stack to the config instances area. This will figure out what needs to be added and provide defaults that make sense.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['elmsln-trigger-innovate'] = array(
    'callback' => 'drush_elmsln_trigger_innovate',
    'description' => dt('Trigger the innovate script to run'),
    'arguments' => array(
      'site' => dt('Site to run this against in the script'),
      'project' => dt('Project machine name for this innovation'),
      'author' => dt('The username of the author of this'),
      'version' => dt('Drupal major project version like 7.x'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_MAX,
  );
  return $items;
}
/**
 * Callback for drush elmsln-add-stack-instance-container
 *
 * This will notice stacks that it currently doesn't have knowledge
 * of in its elmsln/config/stacks/ directory based on a comparison
 * against the elmsln/stacks
 */
function drush_elmsln_add_stack_instance_container() {
  // @todo add support for calling instance containers this way
  // so that we can plug this isn't our spidering bash process
  // which will mirror the way that drup works but for bash
  // scripts
}

/**
 * Call home to send data back to the elmsln data bank for visualization.
 * This can send the following types of things back to the elmsln data bank.
 * `usage`:
 *   anonymous usage data of the ELMSLN deployment to get a sense of how
 *   big the deployment is. This also can be used to show growth / contraction
 *   in platform usage at this instance.
 *   data sent:
 *     # of courses
 *     # of sections
 *     # of students (based on role)
 *     # of staff (based on role)
 *     # of faculty (based on role)
 *     # of TAs (based on role)
 *     active parts of the network
 *     timestamp
 *     uuid of the deployment
 *   when called:
 *     if the elmsln deployment has authorized the sending of data at install
 *     time (this value is saved to the config.cfg) then during upgrades it will
 *     send this anonymous data off to the elmsln data bank. this information is
 *     used to power visuals / data-sets on elmsln.org.
 *   notes:
 *     this information is only relatable back to institutions when they have
 *     expressly stated that they want to be identified; as per our consortium
 *     program. The data itself is always anonymous though the association of
 *     that data to an institution may not be (like how many students at PSU
 *     are taking courses that are powered by ELMSLN).
 * @param  (string) $type The type of data routine to send back
 */
function drush_elmsln_call_home($type = NULL) {
  switch ($type) {
    case 'usage':
    // @todo create address to send back against as global constant
    // then mine these values by connecting to the different systems in the network
    // required to get this data
    // @online - # of courses / # of sections / # of staff / active parts of
    // the network
    // @courses-all # of students / # of faculty / # of TAs
    // uuid is written into the config.cfg at creation time
    //
    // use the drush_invoke_process commands established in DR to bring back
    // this data. Using this, connect to each database then pull for data
    // may need to do some tricky stuff where I return the output to a variable
    // and then parse it to obtain the information needed.
    // These are basically just some EFQs though I might want to make a drush
    // function that just pulls back some data so that we can connect to databases
    // and mine anonymous info like this
    drush_print('future functionality');
    break;
  }
}

/**
 * Trigger the innovation script to fire.
 * @param  string $site    site to target
 * @param  string $project machine name of a project
 * @param  string $author  username
 * @param  string $version 7.x
 */
function drush_elmsln_trigger_innovate($site, $project, $author, $version) {
  exec("bash /var/www/elmsln/scripts/innovate/make-innovation.sh $site $project $author $version");
}
