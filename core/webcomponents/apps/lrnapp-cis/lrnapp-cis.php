<?php

define('__ROOT__', dirname(dirname(dirname(__FILE__))));
require_once(__ROOT__.'/services/ELMSLNCourseService.php');
require_once(__ROOT__.'/services/ELMSLNServiceService.php');
/**
 * Callback for apps/lrnapp-cis/data.
 */
function _lrnapp_cis_app_data($machine_name, $app_route, $params, $args) {
  $options = array();
  $courseService = new ELMSLNCourseService();
  $serviceService = new ELMSLNServiceService();
  // get the courses this user has access to and display
  $courses = $courseService->getCourses($options);
  // get a list of services that exist
  $services = $serviceService->getItems($options);
  return array(
    'status' => 200,
    'data' => array(
      'courses' => $courses,
      'services' => $services,
    ),
  );
}

/**
 * Callback for apps/lrnapp-cis/course.
 */
function _lrnapp_cis_course_data($machine_name, $app_route, $params, $args) {
  $options = array();
  $courseService = new ELMSLNCourseService();
  $course = null;
  // get the courses this user has access to and display
  if (is_numeric($params['id'])) {
    // bool tells service to load network topology
    $course = $courseService->getCourse($params['id'], TRUE);
  }
  return array(
    'status' => 200,
    'data' => array('course' => $course),
  );
}


/**
 * Callback for apps/lrnapp-cis/make-service.
 */
function _lrnapp_cis_make_service($machine_name, $app_route, $params, $args) {
  $options = array();
  $serviceService = new ELMSLNServiceService();
  $course = null;
  $course = $params['course'];
  $service = $params['service'];
  $data = $serviceService->createServiceInstance($course, $service);
  return array(
    'status' => 200,
    'message' => t(' request to create has been sent.'),
    'data' => $data,
  );
}
