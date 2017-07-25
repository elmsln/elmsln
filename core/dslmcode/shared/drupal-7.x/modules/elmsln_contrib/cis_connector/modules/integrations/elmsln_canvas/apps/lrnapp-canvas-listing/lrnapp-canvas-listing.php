<?php

/**
 * Callback for apps/open-studio/data.
 * @param  string $machine_name machine name of this app
 * @return array               data to be json encoded for the front end
 */
function _elmsln_canvas_course_list($machine_name, $app_route, $params, $args) {
  // @todo return a cross section of courses that are mapped in the system
  // and those that aren't yet
  // Click to expand w/ the sections available in each (no roster querying)
  if ($params['return'] == 'courses') {
    $canvas = canvas_api('courses');
    $canvas->params['include'] = array(
      'total_students',
      'course_image',
      'term',
    );
    $response = $canvas->getCourse(NULL);
    $courses = array();
    foreach ($response as $data) {
      $course = array(
        'name' => $data['name'],
        'student_count' => $data['total_students'],
        'image' => $data['image_download_url'],
        'sis_course_id' => $data['sis_course_id'],
        'workflow_state' => $data['workflow_state'],
        'term' => $data['term']['name'],
        'start' => $data['start_at'],
        'end' => $data['end_at'],
      );
      $courses[$data['sis_course_id']] = $course;
    }
    $nodes = _cis_connector_assemble_entity_list('node', 'course', 'field_machine_name', 'title');
    $elmslnCourses = array(
      array('machineName' => '', 'name' => t('-- none --'))
    );
    foreach ($nodes as $machine_name => $name) {
      $elmslnCourses[] = array(
        'machineName' => $machine_name,
        'name' => $name,
      );
    }
    $return = array(
      'elmslnCourses' => $elmslnCourses,
      'canvasCourses' => $courses,
    );
  }
  else if ($params['return'] == 'users') {
    $canvas = canvas_api('courses');
    $canvas->params = array(
      'enrollment_state' => array('active'),
      'include' => array(
        'avatar_url',
        'enrollments',
      ),
    );
    $users = $canvas->usersByCourse('sis_course_id:' . $params['sis_course_id']);
    foreach ($users as $user) {
      if (isset($user['enrollments'][0]['type'])) {
        $username = _elmsln_canvas_scrub_sis_user($user['sis_user_id']);
        $role = _elmsln_canvas_convert_role($user['enrollments'][0]['type']);
        $roster[$role]['role'] = $role;
        $roster[$role]['users'][$username] = array(
          'name' => $user['sortable_name'],
          'picture' => $user['avatar_url'],
          'email' => $user['sis_user_id'],
          'id' => $user['id'],
        );
        // remove the generic avatar so we can use the letter in a circle
        if (strpos($roster[$role]['users'][$username]['picture'], 'avatar-50.png')) {
          $roster[$role]['users'][$username]['picture'] = '';
        }
      }
    }
    $return = $roster;
    /*$canvas = canvas_api('sections');
    $canvas->params['include'] = array(
      'students',
      'avatar_url',
      'enrollments',
      'total_students',
    );
    $return = $canvas->sectionsByCourseID('sis_course_id:'. $params['sis_course_id']);*/

    //}
    //$return = $courses;
      /*$canvas = canvas_api('enrollment');
      foreach ($sections as $section) {
        $rosters[$course['sis_course_id']][] = $canvas->getEnrollment('sis_section_id:' . $section['sis_section_id']);
      }
      foreach ($rosters[$course['sis_course_id']] as $key1 => $enrollments) {
        // drop things that don't have enrollments
        if (empty($enrollments)) {
          unset($rosters[$course['sis_course_id']][$key1]);
        }
        else {
          // look through enrollments for people that are active
          foreach ($enrollments as $key2 => $enrollment) {
            // only keep people who are active
            if ($enrollment['enrollment_state'] != 'active') {
              unset($rosters[$course['sis_course_id']][$key1][$key2]);
            }
          }
        }
      }
    }*/
  }
  return array(
    'status' => 200,
    'data' => $return
  );
}