<?php

define('__ROOT__', dirname(dirname(dirname(__FILE__))));
require_once(__ROOT__.'/services/ELMSLNCourseService.php');
/**
 * Callback for apps/lrnapp-cis/data.
 */
function _lrnapp_cis_app_data($machine_name, $app_route, $params, $args) {
  $options = array();
  $courseService = new ELMSLNCourseService();
  // get the courses this user has access to and display
  $courses = $courseService->getCourses($options);
  return array(
    'status' => 200,
    'data' => array('courses' => $courses),
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
