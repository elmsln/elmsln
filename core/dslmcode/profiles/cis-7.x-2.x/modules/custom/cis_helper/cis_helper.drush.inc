<?php
/**
 * @file
 * Drush integration for CIS distribution.
 */
/**
 * Implements hook_drush_command().
 */
function cis_helper_drush_command() {
  $items['create-service-instances'] = array(
    'description' => dt('Create service instances for an existing course via drush'),
    'arguments' => array(
      'machine_name' => dt("Course machine name, built automatically if it doesn't exist currently"),
      'string' => dt('Access bind to the section key pair in time'),
    ),
    'options' => array(
      'uname' => dt("Username requesting the space, defaults to user 1's name otherwise"),
      'build_service' => dt('Build a specific service when you specify a valid machine name.'),
      'outline_import' => dt('Point to sites/{site}/files/cis_outline_import/{machine_name}.xml for outline to use instead of default.'),
    ),
    'aliases' => array('cis-si'),
    'examples' => array(
      'drush create-course-instance art010 2012faup001' =>
        'Add service instances to art010, use user 1 and use default outline for mooc',
      'drush cis-ci gd100 2012spaa002 --outline_import' =>
        'Add service instances to gd100, use user 1 and import from import bucket gd100.xml',
      'drush cis-ci gd100 2012spaa001 --uname=admin' =>
        'Add service instances to gd100, user is admin',
    ),
  );
  $items['cis-release-kraken'] = array(
    'description' => dt('Look up all possible courses and produce matching service instances'),
    'aliases' => array('cis-kraken'),
    'options' => array(
      'actually_run' => dt("default behavior doesn't actually commit the action, need this to really run it."),
      'build_service' => dt('Build a specific service when you specify a valid machine name.'),
      'outline_import' => dt('Point to sites/{site}/files/cis_outline_import/{machine_name}.xml for outline to use instead of default.'),
    ),
    'examples' => array(
      'drush cis-release-kraken' =>
        'Add service instances to all known courses in system',
      'drush cis-kraken --outline_import --build_service=course' =>
        'Add service instances to all known courses in system, attempt outline importing, only building the "course" instance.',
    ),
  );
  $items['cis-sync-registry'] = array(
    'description' => dt('Sync the service nodes in CIS with the reported services in the registry keychain'),
    'aliases' => array('cis-sync-reg'),
    'options' => array(),
    'examples' => array(
      'drush cis-sync-reg' =>
        'Add service nodes to match their registry counterparts. If there is a match on machine_name then update associated fields in CIS to match registry.',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function cis_helper_drush_help($section) {
  switch ($section) {
    case 'drush:create-service-instance':
      return dt('Pass this commands to produce a new drupal site in the CIS instance.');
    case 'drush:cis-release-kraken':
      return dt('Produce a "kraken" that will hit and force the production of every course into all instances, good for initial population and testing.');
    case 'drush:cis-sync-registry':
      return dt('Create and update Service nodes in CIS to match what is available in the cis registry of connections.');
  }
}

/**
 * Drush command callback for cis-sync-registry.
 */
function drush_cis_helper_cis_sync_registry() {
  // load up the services and the registry to compare them
  $services = _cis_connector_assemble_entity_list('node', 'service', 'field_distribution', 'nid');
  $registry = _cis_connector_build_registry();
  foreach ($registry as $distribution => $reg) {
    // if it is set in CIS, load the node then update it
    if (isset($services[$distribution])) {
      // load this service node and update it if fields are set
      $service = node_load($services[$distribution]);
      $service->field_location['und'][0]['url'] = $reg['protocol'] . '://' . $reg['address'];
      $service->field_data_location['und'][0]['url'] = $reg['protocol'] . '://' . $reg['service_address'];
      node_save($service);
    }
    else {
      // make sure we aren't told to ignore this service
      if (!isset($reg['ignore']) || !$reg['ignore']) {
        // produce a new service instance
        $title = $reg['default_title'];
        $machine_name = explode('.', $reg['address']);
        // snag base address as machine_name
        $machine_name = $machine_name[0];
        // form addresses, CIS uses these for creating paths to cron and links
        $address = $reg['protocol'] . '://' . $reg['address'];
        $data_address = $reg['protocol'] . '://' . $reg['service_address'];
        $service = _cis_helper_generate_service_node($title, $machine_name, $distribution, $address, $data_address);
        drush_print(dt('New service node created based on registry named @title', array('@title' => $title)));
      }
    }
  }
}

/**
 * Drush command callback for cis-release-kraken.
 */
function drush_cis_helper_cis_release_kraken() {
  $courses = _cis_connector_assemble_entity_list('node', 'course', 'field_machine_name', 'title');
  // load all services
  $services = _cis_connector_assemble_entity_list('node', 'service', 'field_machine_name', 'title');
  $build_service = drush_get_option('build_service');
  // remove anything with (dev) in title
  foreach ($services as $name => $title) {
    if (strpos($title, '(dev)')) {
      unset($services[$name]);
    }
    // see if we should unset everything except the service to build
    if (!empty($build_service) && in_array($build_service, array_keys($services)) && $name != $build_service) {
      unset($services[$name]);
    }
  }
  $vars = array(
    '@count' => count($courses),
    '@services' => count($services),
    '@total' => count($courses) * count($services),
  );
  drush_print(dt('@count courses will each build @services for @total operations', $vars));
  if (!drush_confirm(dt('Do you really want to continue!?!?'))) {
    drush_log('Aborting.. that was close!', 'ok');
  }
  else {
    drush_print(dt('Good luck!'));
    foreach ($courses as $name => $title) {
      // make a fake section ID
      $string = '201415SPUP___SING_' . rand(100, 500) . '_' . rand(1, 100);
      $parts = array(
        'year' => '2014',
        'semester' => 'SP',
        'campus' => NULL,
        'number' => '1',
      );
      if (drush_get_option('actually_run')) {
        drush_cis_helper_create_service_instances($name, $string, $parts);
      }
      else {
        drush_print(dt('Would have run drush_cis_helper_create_service_instances course "@name" with string "@string"', array('@name' => $name, '@string' => $string)));
      }
    }
  }
}

/**
 * Drush command callback for create-service-instances.
 */
function drush_cis_helper_create_service_instances($machine_name, $string, $parts = array()) {
  module_load_include('inc', 'cis_helper', 'cis_helper.pages');
  // load all services
  $build_service = drush_get_option('build_service');
  if (!empty($build_service)) {
    $list = _cis_connector_assemble_entity_list('node', 'service', 'field_machine_name', 'nid');
    if (in_array($build_service, array_keys($list))) {
      $nid = $list[$build_service];
    }
  }
  $services = _cis_connector_assemble_entity_list('node', 'service', 'nid', 'title');
  // remove anything with (dev) in title
  foreach ($services as $key => $service_name) {
    if (strpos($service_name, '(dev)')) {
      unset($services[$key]);
    }
    // see if we got an option to only produce one item
    if (isset($nid) && $key != $nid) {
      unset($services[$key]);
    }
  }
  $uname = drush_get_option('uname');
  // if no username, assume admin
  if (!$uname || !user_validate_name($uname)) {
    $tmp = user_load(1);
    $uname = $tmp->name;
  }
  // allow other projects to define custom alterations
  // return should be array w/ year, semester, campus and number (section)
  drupal_alter('cis_string_process', $string, $parts);
  $year = $parts['year'];
  $semester = $parts['semester'];
  $campus = $parts['campus'];
  $number = $parts['number'];
  // check if we want to use outline import location and that it exists, or default
  $path = variable_get('file_public_path', conf_path() . '/files') . '/cis_outline_import/';
  if (drush_get_option('outline_import') && file_exists($path . $machine_name . '.xml')) {
    $outline = $path;
  }
  else {
    $outline = drupal_get_path('module', 'cis_helper') . '/instructional_models/' . CIS_HELPER_DEFAULT_CONTENT_OUTLINE;
  }
  // set up the form array
  $form_state = array();
  $form_state['values'] = array(
    'course' => $machine_name, // course machine name
    'instructional_outline' => $outline, // location of outline to use
    'services' => array_keys($services), // array of entity ids of services to use
    'semester' => $semester, // semester as word
    'year' => $year, // year of offering
    'number' => $number, // section number
    'campus' => $campus, // campus code
    'access_string' => $string, // access string to bind
    'instructor' => $uname, // name of the instructor for this course
  );
  // required for forced submission
  $form_state['values']['op'] = t('Create course');
  // try and "submit" the form
  drupal_form_submit('cis_helper_quick_setup_page', $form_state);
}
