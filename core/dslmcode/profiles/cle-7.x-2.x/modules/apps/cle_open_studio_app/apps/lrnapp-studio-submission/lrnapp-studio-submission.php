<?php

/**
 * Require the submission service.
 */
define('__ROOT__', dirname(dirname(__FILE__))); 
require_once(__ROOT__.'/services/CleOpenStudioAppSubmissionService.php'); 
require_once(__ROOT__.'/services/CleOpenStudioAppFileService.php'); 

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
  $return = array();
  $status = 200;
  $service = new CleOpenStudioAppSubmissionService();

  $return = $service->getSubmissions();

  return array(
    'status' => 200,
    'data' => $return
  );
}

function _cle_open_studio_app_file_index($machine_name, $app_route, $params, $args) {
  $return = array('status' => 200);
  $method = $_SERVER['REQUEST_METHOD'];
  $file_service = new CleOpenStudioAppFileService();

  if ($method == 'POST') {
    // check for a file upload
    if (isset($_FILES['file-upload']) && isset($_FILES['file-upload']['type']) && isset($_FILES['file-upload']['tmp_name'])) {
      // find out what the file type is. It's often separated by a '/'
      $type = explode('/', $_FILES['file-upload']['type']);
      $type = $type[0];
      $tmp_name = $_FILES['file-upload']['tmp_name'];
      $options = array();
      if (isset($params['file_wrapper'])) {
        $options['file_wrapper'] = $params['file_wrapper'];
      }
      if (isset($_FILES['file-upload']['name'])) {
        $options['name'] = $_FILES['file-upload']['name'];
      }
      $file = $file_service->create($type, $tmp_name, $options);
      $return['data'] = array('file' => $file);
    }
  }
  return $return;
}

function _cle_open_studio_app_video_index($machine_name, $app_route, $params, $args) {
  return array('status' => 403);
}

function _cle_open_studio_app_video_generate_source_url($machine_name, $app_route, $params, $args) {
  $return = array('status' => 200);
  $method = $_SERVER['REQUEST_METHOD'];
  if ($method == 'POST') {
    $post_data = file_get_contents("php://input");
    $submission_service = new CleOpenStudioAppSubmissionService;
    $src_url = $submission_service->videoGenerateSourceUrl($post_data);
    if ($src_url) {
      $return['data'] = $src_url;
      return $return;
    }
  }
  else {
    return array('status' => 400, 'errors' => array(t('No video url was provided')));
  }
  return array('status' => 422, 'errors' => array(t('Unprocessable entity')));
}

function _cle_open_studio_app_submission_comments($machine_name, $app_route, $params, $args) {
  $raw_data = '[
    {
      "metadata": {
        "id": 100,
        "editform": false,
        "disabled": false
      },
      "actions": {
        "edit": true,
        "reply": true,
        "like": false,
        "delete": true
      },
      "attributes": {
        "body": "This a **whole** bunch of my content that you now see!",
        "threadDepth": 1,
        "created": "1991-12-31"
      },
      "relationships": {
        "author": {
          "data": {
            "name": "Bryan",
            "avatar": "http://www.elmsln.org/sites/redesign/files/styles/square-profile-portrait/public/headshot.jpg?itok=_1HEhahr",
            "username": "btopro",
            "userid": 1
          }
        }
      }
    },
    {
      "metadata": {
        "id": 200,
        "editform": false,
        "disabled": false
      },
      "actions": {
        "edit": false,
        "reply": true,
        "like": true,
        "delete": false
      },
      "attributes": {
        "body": "This a **whole** bunch of my content that you now see!",
        "threadDepth": 2,
        "created": "2000-12-31"
      },
      "relationships": {
        "author": {
          "data": {
            "name": "Michael Potter",
            "avatar": "http://www.elmsln.org/sites/redesign/files/styles/square-profile-portrait/public/img_1773-1-sq_720_1.jpg?itok=KR9AsnhA",
            "username": "heymp",
            "userid": 2
          }
        }
      }
    },
    {
      "metadata": {
        "id": 300,
        "editform": false,
        "disabled": false
      },
      "actions": {
        "edit": false,
        "reply": true,
        "like": true,
        "delete": false
      },
      "attributes": {
        "body": "This a **whole** bunch of my content that you now see!",
        "threadDepth": 3,
        "created": "2017-12-31"
      },
      "relationships": {
        "author": {
          "data": {
            "name": "Brittany Terpstra",
            "avatar": "http://www.elmsln.org/sites/redesign/files/styles/square-profile-portrait/public/brt.png?itok=WdC_WcB4",
            "username": "bterp",
            "userid": 41
          }
        }
      }
    }
  ]';
  $normalized_data = json_decode($raw_data);

  return array('status' => 200, 'data' => $normalized_data);
}

// function cle_open_studio_app_cle_open_studio_app_encode_submission_alter(&$submissions) {
//   if (_assignment_is_open()) {
//     $action = new stdClass();
//     $action->title = 'Make a Submission';
//     $action->url = '/lrnapp-submission/create';
//     $submissions->actions[] = $action;
//   }
// }