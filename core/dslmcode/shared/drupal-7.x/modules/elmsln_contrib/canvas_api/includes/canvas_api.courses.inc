<?php
/**
 * @file
 * Helper functions that utilize Canvas' Courses APIs
 *
 * See @link https://canvas.instructure.com/doc/api/courses.html @endlink
 *
 */

/**
 * {@inheritdoc}
 */
class CanvasCourses extends Canvas {

  function __construct(){
    parent::__construct();
  }

  /**
   * Create a Canvas course
   *
   * See @link https://canvas.instructure.com/doc/api/courses.html#method.courses.create @endlink
   *
   * Example:
   *
   *  $canvas_api = canvas_api('courses');
   *  $canvas_api->params = array(
   *    'course' => array(
   *       'name' => 'New Test Course',
   *       'course_code' => 'NTC123',
   *       'term_id' => 144,
   *       'sis_course_id' => 'ART063|BOB|S2-16',
   *    ),
   *  );
   *  $course = $canvas_api->createCourse(1);
   *
   * @param $rootAccountID
   *  The Canvas account this course should be created under
   * @return array
   */
  public function createCourse($rootAccountID){
    $this->path = "accounts/$rootAccountID/courses";
    return $this->post();
  }

  /**
   * Get a Canvas course
   *
   * See @link https://canvas.instructure.com/doc/api/courses.html#method.courses.show @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('courses');
   *    $courseID = 4542;
   *    $course = $canvas_api->getCourse($courseID);
   *
   * @param $courseID
   * @return array
   */
  public function getCourse($courseID){
    $this->path = "courses/$courseID";
    return $this->get();
  }

  /**
   * Edit a Canvas course
   *
   * See @link https://canvas.instructure.com/doc/api/courses.html#method.courses.update @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('courses');
   *    $courseID = 4542;
   *    $canvas_api->params = array(
   *      'course' = array(
   *        'name' => 'My Updated Course Name',
   *      ),
   *    );
   *    $course = $canvas_api->editCourse($courseID);
   *
   * @param $courseID
   * @return array
   *    The Course array
   */
  public function editCourse($courseID){
    $this->path = "courses/$courseID";
    return $this->put();
  }

  /**
   * Delete (or conclude) a Canvas course
   *
   * See @link https://canvas.instructure.com/doc/api/courses.html#method.courses.destroy @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('courses');
   *    $sisCourseID = 'sis_course_id:ART063|BOB|S2-16';
   *    $canvas_api->params['event'] = 'delete'; // Optional; defaults to "conclude"
   *    $course = $canvas_api->deleteCourse($sisCourseID);
   *
   * @param $courseID
   * @return array
   *  The event parameter. Useful, no?
   */
  public function deleteCourse($courseID){
    if(empty($this->params['event'])){
      $this->params['event'] = 'conclude';
    }
    $this->path = "courses/$courseID";
    return $this->delete();
  }


  /**
   * Get a user's courses
   *
   * See @link https://canvas.instructure.com/doc/api/courses.html#method.courses.user_index @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('courses');
   *    $userID = 630;
   *    $canvas_api->params['include'] = ['term','sections'];
   *    $courses = $canvas_api->coursesByUser($userID);
   *
   * @param string $userID
   * @return array
   */
  public function coursesByUser($userID){
    $this->path = "users/$userID/courses";
    return $this->get();
  }

  /**
   * List users in a Canvas course
   *
   * See @link https://canvas.instructure.com/doc/api/courses.html#method.courses.users @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('courses');
   *    $courseID = 3472;
   *    $canvas_api->params = array(
   *        'enrollment_type' => ['student'],
   *        'include' => ['email','enrollments'],
   *    );
   *    $users = $canvas_api->usersByCourse($courseID);
   *
   * @param string $courseID
   * @return array
   *  Users enrolled in this course
   */
  public function usersByCourse($courseID){
    $this->path = "courses/$courseID/users";
    return $this->get();
  }
}
