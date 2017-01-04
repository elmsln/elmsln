<?php
/**
 * @file
 * Helper functions that utilize Canvas' Enrollment APIs
 *
 * See @link https://canvas.instructure.com/doc/api/enrollment.html @endlink
 *
 */

/**
 * {@inheritdoc}
 */
class CanvasEnrollment extends Canvas {

  function __construct() {
    parent::__construct();
  }

  /**
   * Enroll a user
   *
   * See @link https://canvas.instructure.com/doc/api/enrollments.html#method.enrollments_api.create @endlink
   *
   * Example:
   *
   *  $canvas_api = canvas_api('enrollment');
   *  $canvas_api->params = array(
   *    'enrollment' => array(
   *       'user_id' => 3,
   *       'type' => 'StudentEnrollment',
   *       'enrollment_state' => 'active',
   *    ),
   *  );
   *  $sisCourseID = 'sis_course_id:ART063|123|S2-16';
   *  $enrollment = $canvas_api->createEnrollment($sisCourseID,'course');
   *
   * @param string $id
   *  The Canvas course or section ID
   * @param string $type
   *  Either 'course' or 'section'. Defaults to 'section'.
   * @return array
   */
  public function createEnrollment($id, $type = 'section') {
    $this->path = "{$type}s/$id/enrollments";
    return $this->post();
  }

  /**
   * List Enrollments
   *
   * See @link https://canvas.instructure.com/doc/api/enrollments.html#method.enrollments_api.index @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('enrollment');
   *    $courseID = 4543;
   *    $canvas_api->params = array(
   *        'type' => ['TeacherEnrollment'],
   *    );
   *    $enrollment = $canvas_api->getEnrollment($courseID,'course');
   *
   * @param $courseID
   * @return array
   */
  public function getEnrollment($id, $type = 'section') {
    $this->path = "{$type}s/$id/enrollments";
    return $this->get();
  }

  /**
   * Delete (or conclude) an enrollment
   *
   * See @link https://canvas.instructure.com/doc/api/enrollments.html#method.enrollments_api.destroy @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('enrollment');
   *    $courseID = 4543;
   *		$enrollmentID = 149850;
   *    $canvas_api->params['task'] = 'delete'; // Defaults to 'conclude'
   *    $course = $canvas_api->deleteEnrollment($courseID,$enrollmentID);
   *
   * @param $courseID
   * @param $enrollmentID
   * @return array
   *  The deleted enrollment
   */
  public function deleteEnrollment($courseID,$enrollmentID) {
    if (empty($this->params['task'])) {
      $this->params['task'] = 'conclude';
    }
    $this->path = "courses/$courseID/enrollments/$enrollmentID";
    return $this->delete();
  }


}