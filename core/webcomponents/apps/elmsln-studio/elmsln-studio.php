<?php

/**
 * Require the submission service.
 */
define('__ROOT__', dirname(dirname(dirname(__FILE__))));
define('__DEMODATA__', dirname(__FILE__) . '/data/');
require_once(__ROOT__.'/services/LRNAppOpenStudioSubmissionService.php');
require_once(__ROOT__.'/services/LRNAppOpenStudioProjectService.php');
require_once(__ROOT__.'/services/LRNAppOpenStudioAssignmentService.php');
require_once(__ROOT__.'/services/LRNAppOpenStudioFileService.php');
require_once(__ROOT__.'/services/LRNAppOpenStudioCommentService.php');

// context to easily demo things
define('STUDIO_CONTEXT', "demo");
//define('STUDIO_CONTEXT', "production");
// basic context alter so we can rapidly switch to demo or prod data
function _cle_open_studio_2021_context_alter($fname, $response, $context = STUDIO_CONTEXT) {
  // demo context so rewrite the response info to match whatever we get from a local file
  if ($context == "demo") {
    // form file name based on the function name since they are all uniform
    $tmp = file_get_contents(__DEMODATA__ . str_replace('_cle_open_studio_2021_','',str_replace('_source','', $fname)) . '.json');
    $response = (array)json_decode($tmp);
    // debug
    $response['fpath'] = __DEMODATA__ . str_replace('_cle_open_studio_2021_','',str_replace('_source','', $fname)) . '.json';
  }
  return $response;
}

/**
 * Callback for apps/elmsln-studio/assignments-source
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_2021_assignments_source($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->filter['state'] = array('submission_ready', '=');
  $options->truncate = array(
    'images' => 'images',
    'comments' => 'comments',
    'relatedSubmissions' => 'relatedSubmissions',
  );
  // get submissions based on criteria
  $service = new LRNAppOpenStudioSubmissionService();
  $data['submissions'] = $service->getSubmissions($options);
  // snag projects
  $service = new LRNAppOpenStudioProjectService();
  $data['projects'] = $service->getProjects();
  $response = array(
    'status' => $status,
    'data' => $data
  );
  $response = _cle_open_studio_2021_context_alter(__FUNCTION__, $response);
  return $response;
}

/**
 * Callback for apps/elmsln-studio/discussion-source
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_2021_discussion_source($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->filter['state'] = array('submission_ready', '=');
  $options->truncate = array(
    'images' => 'images',
    'comments' => 'comments',
    'relatedSubmissions' => 'relatedSubmissions',
  );
  // get submissions based on criteria
  $service = new LRNAppOpenStudioSubmissionService();
  $data['submissions'] = $service->getSubmissions($options);
  // snag projects
  $service = new LRNAppOpenStudioProjectService();
  $data['projects'] = $service->getProjects();
  $response = array(
    'status' => $status,
    'data' => $data
  );
  $response = _cle_open_studio_2021_context_alter(__FUNCTION__, $response);
  return $response;
}

/**
 * Callback for apps/elmsln-studio/lessons-source
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_2021_lessons_source($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->filter['state'] = array('submission_ready', '=');
  $options->truncate = array(
    'images' => 'images',
    'comments' => 'comments',
    'relatedSubmissions' => 'relatedSubmissions',
  );
  // get submissions based on criteria
  $service = new LRNAppOpenStudioSubmissionService();
  $data['submissions'] = $service->getSubmissions($options);
  // snag projects
  $service = new LRNAppOpenStudioProjectService();
  $data['projects'] = $service->getProjects();
  $response = array(
    'status' => $status,
    'data' => $data
  );
  $response = _cle_open_studio_2021_context_alter(__FUNCTION__, $response);
  return $response;
}

/**
 * Callback for apps/elmsln-studio/portfolios-source
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_2021_portfolios_source($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->filter['state'] = array('submission_ready', '=');
  $options->truncate = array(
    'images' => 'images',
    'comments' => 'comments',
    'relatedSubmissions' => 'relatedSubmissions',
  );
  // get submissions based on criteria
  $service = new LRNAppOpenStudioSubmissionService();
  $data['submissions'] = $service->getSubmissions($options);
  // snag projects
  $service = new LRNAppOpenStudioProjectService();
  $data['projects'] = $service->getProjects();
  $response = array(
    'status' => $status,
    'data' => $data
  );
  $response = _cle_open_studio_2021_context_alter(__FUNCTION__, $response);
  return $response;
}

/**
 * Callback for apps/elmsln-studio/profile-source
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_2021_profile_source($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->filter['state'] = array('submission_ready', '=');
  $options->truncate = array(
    'images' => 'images',
    'comments' => 'comments',
    'relatedSubmissions' => 'relatedSubmissions',
  );
  // get submissions based on criteria
  $service = new LRNAppOpenStudioSubmissionService();
  $data['submissions'] = $service->getSubmissions($options);
  // snag projects
  $service = new LRNAppOpenStudioProjectService();
  $data['projects'] = $service->getProjects();
  $response = array(
    'status' => $status,
    'data' => $data
  );
  $response = _cle_open_studio_2021_context_alter(__FUNCTION__, $response);
  return $response;
}

/**
 * Callback for apps/elmsln-studio/submissions-source
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_2021_submissions_source($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->filter['state'] = array('submission_ready', '=');
  $options->truncate = array(
    'images' => 'images',
    'comments' => 'comments',
    'relatedSubmissions' => 'relatedSubmissions',
  );
  // get submissions based on criteria
  $service = new LRNAppOpenStudioSubmissionService();
  $data['submissions'] = $service->getSubmissions($options);
  // snag projects
  $service = new LRNAppOpenStudioProjectService();
  $data['projects'] = $service->getProjects();
  $response = array(
    'status' => $status,
    'data' => $data
  );
  $response = _cle_open_studio_2021_context_alter(__FUNCTION__, $response);
  return $response;
}

/**
 * Callback for apps/elmsln-studio/users-source
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _cle_open_studio_2021_users_source($machine_name, $app_route, $params, $args) {
  $status = 200;
  $data = array();
  // pull together all the submissions they should be seeing
  $options = new stdClass();
  // only show things marked ready for feedback
  $options->filter['state'] = array('submission_ready', '=');
  $options->truncate = array(
    'images' => 'images',
    'comments' => 'comments',
    'relatedSubmissions' => 'relatedSubmissions',
  );
  // get submissions based on criteria
  $service = new LRNAppOpenStudioSubmissionService();
  $data['submissions'] = $service->getSubmissions($options);
  // snag projects
  $service = new LRNAppOpenStudioProjectService();
  $data['projects'] = $service->getProjects();
  $response = array(
    'status' => $status,
    'data' => $data
  );
  $response = _cle_open_studio_2021_context_alter(__FUNCTION__, $response);
  return $response;
}