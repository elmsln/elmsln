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
  );
  $users = _cis_connector_assemble_entity_list('user', 'user', 'name', '_entity', $field_conditions);

  // form a single user record
  foreach ($users as &$usr) {
    if ($usr->name != 'SERVICE_CLE_AA') {
      $data[$usr->name] = new stdClass();
      $data[$usr->name]->id = $usr->name;
      $data[$usr->name]->lastName = _elmsln_core_get_user_name('last', $usr->uid);
      $data[$usr->name]->firstName = _elmsln_core_get_user_name('first', $usr->uid);
      $data[$usr->name]->image = _elmsln_core_get_user_picture('avatar', $usr->uid);
      // instructor bool
      $data[$usr->name]->instructor = _cis_connector_role_grouping("teacher");
      // need full submission object
      $data[$usr->name]->submissions = array();
      // pull together all the submissions they should be seeing
      $options = new stdClass();
      // only show things marked ready for feedback
      $options->filter['state'] = array('submission_ready', '=');
      $options->filter['author'] = $usr->uid;
      $options->truncate = array(
        'images' => 'images',
        'comments' => 'comments',
        'relatedSubmissions' => 'relatedSubmissions',
      );
      // get submissions based on criteria
      $service = new LRNAppOpenStudioSubmissionService();
      $submissions = $service->getSubmissions($options, FALSE);
      foreach ($submissions as &$submission) {
        $encodeSub = new stdClass();
        $encodeSub->id = $submission->id;
        $encodeSub->assignment = "Deliver: Iterate critique";
        $encodeSub->assignmentDate = "2021-01-09T23:06:35.000Z";
        $encodeSub->project = "Hypertext Narrative Project";
        $encodeSub->lesson = "Lesson 1";
        $encodeSub->portfolio = "project-1-kmk5124";
        $encodeSub->portfolioId = "project-1-kmk5124";
        $encodeSub->assignmentId = "assignment-10";
        $encodeSub->projectId = "project-1";
        $encodeSub->lessonId = "lesson-1";
        $encodeSub->userId = $usr->name;
        $encodeSub->firstName = _elmsln_core_get_user_name('first', $usr->uid);
        $encodeSub->lastName = _elmsln_core_get_user_name('last', $usr->uid);
        $encodeSub->avatar = _elmsln_core_get_user_picture('avatar', $usr->uid);
        $encodeSub->date = gmdate(DATE_W3C, $submission->changed);
        $encodeSub->image = "";
        $encodeSub->thumbnail = "";
        $encodeSub->full = "";
        $encodeSub->imageAlt = "";
        $encodeSub->imageLongdesc = "";
        $encodeSub->feedbackInstructions = "";
        $encodeSub->feedbackRubric = array(
          "key" => array(),
          "values" => array(),
        );
        $encodeSub->feature = $submission->field_submission_text[LANGUAGE_NONE][0]['safe_value'];
        $encodeSub->body = $submission->field_submission_text[LANGUAGE_NONE][0]['safe_value'];
        // @todo need IDs of the feedback given
        $encodeSub->feedback = array();
        $encodeSub->activity = "submission";
        $data[$usr->name]->submissions[] = $encodeSub;
      }
      // @todo need IDs of the feedback given
      $data[$usr->name]->given = array();
      // @todo figure out difference here
      $data[$usr->name]->replies = array();
      // @todo figure out difference here
      $data[$usr->name]->discussions = array();
      // @todo figure out what this is
      $data[$usr->name]->feedbackPercentile = 25;
    }
  }
  $response = array(
    'status' => $status,
    'data' => $data,
    'submissions' => $service->getSubmissions($options),
  );
  //$response = _cle_open_studio_2021_context_alter(__FUNCTION__, $response);
  return $response;
}