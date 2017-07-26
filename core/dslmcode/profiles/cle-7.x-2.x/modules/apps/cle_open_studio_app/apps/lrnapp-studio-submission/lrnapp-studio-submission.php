<?php

/**
 * Require the submission service.
 */
define('__ROOT__', dirname(dirname(__FILE__))); 
require_once(__ROOT__.'/services/CleOpenStudioAppSubmissionService.php'); 

function _cle_open_studio_app_submission_findone($machine_name, $app_route, $params, $args) {
  $return = array('status' => 200);
  $method = $_SERVER['REQUEST_METHOD'];

  // Find out if there is a nid specified
  if ($method == 'GET' || $method == 'PUT') {
    if (isset($args[2])) {
      $nid = $args[2];
      if ($nid) {
        // if it's a GET method then we can return the node.
        switch ($method) {
          case 'GET':
            $service = new CleOpenStudioAppSubmissionService();
            $return['data'] = $service->getSubmission($args[2]);
            drupal_set_message('asdf');
            break;
          case 'PUT':
            $service = new CleOpenStudioAppSubmissionService();
            $post_data = file_get_contents("php://input");
            $post_data = json_decode($post_data);
            // try to update the node
            try {
              $update = $service->updateSubmission($post_data, $args[2]);
              $return['data'] = $update;
            }
            // if it fails we'll add errors and return 500
            catch (Exception $e) {
              $return['status'] = 500;
              $return['errors'][] = $e->getMessage();
            }
            break;
          default:
            # code...
            break;
        }
      }
      else {
        $return['status'] = 404;
      }
    }
  }

  return $return;
}

function _cle_open_studio_app_submission_index($machine_name, $app_route, $params, $args) {
  $return = [];
  $status = 200;
  $service = new CleOpenStudioAppSubmissionService();

  $return = $service->getSubmissions();

  return array(
    'status' => 200,
    'data' => $return
  );
}

// function cle_open_studio_app_cle_open_studio_app_encode_submission_alter(&$submissions) {
//   if (_assignment_is_open()) {
//     $action = new stdClass();
//     $action->title = 'Make a Submission';
//     $action->url = '/lrnapp-submission/create';
//     $submissions->actions[] = $action;
//   }
// }