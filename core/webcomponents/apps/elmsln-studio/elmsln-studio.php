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
  // get all users in current section
  $section_id = _cis_connector_section_context();
  $section = _cis_section_load_section_by_id($section_id);
  $field_conditions = array(
    'og_user_node' => array('target_id', $section, '='),
    '__role' => _cis_connector_role_groups('learner'),
  );
  $users = _cis_connector_assemble_entity_list('user', 'user', 'uid', 'name', $field_conditions);

  // form a single user record
  foreach ($users as &$usr) {
    $response[$usr->name] = new stdClass();
    $response[$usr->name]->id = $usr->name;
    $response[$usr->name]->lastName = _elmsln_core_get_user_name('last', $usr->uid);;
    $response[$usr->name]->firstName = _elmsln_core_get_user_name('first', $usr->uid);;
    $response[$usr->name]->image = _elmsln_core_get_user_picture('avatar', $usr->uid);
    // need full submission object
    $response[$usr->name]->submissions = array();
    // need IDs of the feedback given
    $response[$usr->name]->given = array();
    // @todo figure out difference here
    $response[$usr->name]->replies = array();
    // @todo figure out difference here
    $response[$usr->name]->discussions = array();
    $response[$usr->name]->feedbackPercentile = 25;
  }
  /**
  "kmk5124": {
      "id": "kmk5124",
      "lastName": "Korat",
      "firstName": "Kitty",
      "image": "//placekitten.com/g/400/300",
      "submissions": [
        {
          "id": "assignment-10-kmk5124",
          "assignment": "Deliver: Iterate critique",
          "assignmentDate": "2021-01-09T23:06:35.000Z",
          "project": "Hypertext Narrative Project",
          "lesson": "Lesson 1",
          "portfolio": "project-1-kmk5124",
          "portfolioId": "project-1-kmk5124",
          "assignmentId": "assignment-10",
          "projectId": "project-1",
          "lessonId": "lesson-1",
          "userId": "kmk5124",
          "firstName": "Kitty",
          "lastName": "Korat",
          "avatar": "//placekitten.com/g/400/300",
          "date": "2021-01-14T22:06:37.000Z",
          "image": "https://webcomponents.psu.edu/styleguide/elements/elmsln-studio/demo/images/image3.jpg",
          "thumbnail": "https://webcomponents.psu.edu/styleguide/elements/elmsln-studio/demo/images/image3.jpg",
          "full": "https://webcomponents.psu.edu/styleguide/elements/elmsln-studio/demo/images/image3.jpg",
          "imageAlt": "Random tech image #290",
          "imageLongdesc": "This is a long description for image #290. Cursus viverra eu neque eu id enim ut. Phasellus vestibulum maximus pellentesque quisque.",
          "feedbackInstructions": "",
          "feedbackRubric": {
            "key": [
              { "description": "Exceeded", "points": 2 },
              { "description": "Met", "points": 1 },
            ],
            "values": {
              "pellentesque porttitor": [
                "In consectetur scelerisque?",
                "Semper varius ex nibh.",
                "Nulla etiam mollis."
              ],
              "a orci": [
                "Magna eleifend interdum et?",
                "Nisi ante faucibus ac quisque.",
                "Eget quis quisque?"
              ]
            }
          },
          "feature": "Orci sem mi lectus risus lorem feugiat suspendisse consequat ante tortor diam nisi. Ipsum eleifend ac proin lectus cursus lobortis interdum? Risus iaculis consectetur massa ut magna.",
          "body": "Pellentesque euismod fringilla ultrices. Orci ligula aliquam scelerisque sem venenatis duis phasellus ipsum faucibus. Nunc vivamus ut ex ac odio lacus lorem accumsan iaculis.",
          "feedback": ["feedback-132", "feedback-133"],
          "activity": "submission"
        }
      ],
      "given": [
        "feedback-2",
        "feedback-258"
      ],
      "replies": [
        "feedback-4-reply-1",
        "feedback-14-reply-1"
      ],
      "discussions": [
        "feedback-84",
        "feedback-258",
        "feedback-4-reply-1",
        "feedback-14-reply-1"
      ],
      "feedbackPercentile": 25
    }
   */
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