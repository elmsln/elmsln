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
  // Clicking to expand those can do a individual section query to pull up some more stats
  if ($params['return'] == 'courses') {
    $canvas = canvas_api('courses');
    $canvas->params['include'] = array(
      'sections',
      'total_students',
      'course_image',
    );
    $response = $canvas->getCourse(NULL);
    $courses = array();
    foreach ($response as $data) {
      $course = array(
        'name' => $data['name'],
        'course_code' => $data['course_code'],
        'sections' => count($data['sections']),
        'student_count' => $data['total_students'],
        'image' => $data['image_download_url'],
        'sis_course_id' => $data['sis_course_id'],
        'workflow_state' => $data['workflow_state'],
      );
      $courses[$data['sis_course_id']] = $course;
    }
    // @todo query against current SIS mappings to put that in output
    $return = $courses;
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
    $return = $canvas->usersByCourse('sis_course_id:' . $params['sis_course_id']);
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