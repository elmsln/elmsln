<?php
/**
 * @file
 * Helper functions that utilize Canvas' Sections APIs
 *
 * See @link https://canvas.instructure.com/doc/api/sections.html @endlink
 *
*/


/**
 * {@inheritdoc}
 */
class CanvasSections extends Canvas{
  
  function __construct(){
    parent::__construct();
  }

  /**
   * Create a Canvas section
   *
   * See @link https://canvas.instructure.com/doc/api/sections.html#method.sections.create @endlink
   *
   * Example:
   *
   *    $canvas_api = canvas_api('sections');
   *    $sisCourseID = 'sis_course_id:ART063|FIT|S2-16';
   *    $canvas_api->params = array(
   *       'course_section' => array(
   *          'name' => 'My Newest Section Name',
   *          'sis_section_id' => 'ART063-05-S2-16',
   *        ),
   *    );
   *    $result = $canvas_api->createSection($sisCourseID);
   *
   * @param $courseID
   * @return array
   */
  public function createSection($courseID){
    $this->path = "courses/$courseID/sections";
    return $this->post();
  }

  /**
   * Get a Canvas section
   *
   * See @link https://canvas.instructure.com/doc/api/sections.html#method.sections.show @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('sections');
   *    $sisSectionID = 'sis_section_id:ART063-04-S2-16';
   *    $section = $canvas_api->getSection($sisSectionID);
   *
   * @param $sectionID
   * @return array
   */
  public function getSection($sectionID){
    $this->path = "sections/$sectionID";
    return $this->get();
  }

  /**
   * Edit a Canvas section
   *
   * See @link https://canvas.instructure.com/doc/api/sections.html#method.sections.update @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('sections');
   *    $sectionID = 4260;
   *    $canvas_api->params = array(
   *      'course_section' => array(
   *        'name' => 'My New Section Name',
   *      ),
   *    );
   *    $section = $canvas_api->editSection($sectionID);
   *
   * @param $sectionID
   * @return array
   *    The Section array
   */
  public function editSection($sectionID){
    $this->path = "sections/$sectionID";
    return $this->put();
  }

  /**
   * Delete a Canvas section
   *
   * See @link https://canvas.instructure.com/doc/api/sections.html#method.sections.destroy @endlink
   *
   * Example:
   *    $canvas_api = canvas_api('sections');
   *    $sisSectionID = 'sis_section_id:ART063-05-S2-16';
   *    $section = $canvas_api->deleteSection($sisSectionID);
   *
   * @param $sectionID
   * @return array
   */
  public function deleteSection($sectionID){
    $this->path = "sections/$sectionID";
    return $this->delete();
  }

  /**
   * List sections for a course.
   *
   * See @link https://canvas.instructure.com/doc/api/sections.html#method.sections.index @endlink
   * 
   * Example:
   *    $canvas_api = canvas_api('sections');
   *    $sisCourseID = 'sis_course_id:ART063|FIT|S2-16';
   *    $sections = $canvas_api->sectionsByCourseID($sisCourseID);
   *
   * @param string $courseID
   * @return array
   *   An array of Section arrays
   */
  public function sectionsByCourseID($courseID){
    $this->path = "courses/$courseID/sections";
    return $this->get();
  }



}
