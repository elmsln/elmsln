<?php
/**
 * @file
 * mooc_cis_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_cis_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc_cis_student_ux-blocks';
  $context->description = 'This helps display the instructional content outline block';
  $context->tag = 'Content';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~mooc-themecompat-*' => '~mooc-themecompat-*',
      ),
    ),
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'cis_service_connection-all_active_outline' => array(
          'module' => 'cis_service_connection',
          'delta' => 'all_active_outline',
          'region' => 'sidebar_first',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('This helps display the instructional content outline block');
  $export['mooc_cis_student_ux-blocks'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc_cis_ux-blocks';
  $context->description = '';
  $context->tag = 'Content';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~mooc-themecompat-*' => '~mooc-themecompat-*',
      ),
    ),
    'user' => array(
      'values' => array(
        'administrator' => 'administrator',
        'instructor' => 'instructor',
        'staff' => 'staff',
        'teaching assistant' => 'teaching assistant',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-course-tools-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-course-tools-menu',
          'region' => 'regions_admin_left',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  $export['mooc_cis_ux-blocks'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc_cis_ux-guidedtour';
  $context->description = 'Guided tour for how to navigate the course, great for coming to the site for the first time.';
  $context->tag = 'Content';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'welcome_page/guided_tour' => 'welcome_page/guided_tour',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'joyride-joyride_start_link' => array(
          'module' => 'joyride',
          'delta' => 'joyride_start_link',
          'region' => 'sidebar_first',
          'weight' => '-20',
        ),
      ),
    ),
    'joyride_add' => array(
      'joyride_auto_start' => 1,
      'joyride_play_once' => 0,
      'joyride_tour_content' => '<li data-button="Start Tour">
  <h2>Get to know your course</h2>
  <p>This tour is intended to help you become familiar with the course interface.</p>
</li>
<li data-id="block-system-main-menu" data-button="Next" data-options="tipLocation:bottom">
  <h2>Logistics</h2>
  <p>You can see the welcome message from your instructor, get a copy of the welcome letter and syllabus.</p>
</li>
<li data-id="block-cis-service-connection-active-outline" data-button="Next" data-options="tipLocation:top">
  <h2>Course Outline</h2>
  <p>This is your content outline and primary means of navigation through the course.</p>
</li>
<li data-id="page-title" data-button="Next" data-options="tipLocation:bottom">
  <h2>Title</h2>
  <p>This is the title of this piece of content you will read about.</p>
</li>
<li data-id="examplecontent" data-button="Next" data-options="tipLocation:top">
  <h2>Reading</h2>
  <p>Most pages will have reading similar to this filler text.</p>
</li>
<li data-id="examplemedia" data-button="Next" data-options="tipLocation:top">
  <h2>Media</h2>
  <p>This is an example of media supplied by the college. If you can see and play this clip you should be able to view media in the course.</p>
</li>
<li data-id="examplerequired" data-button="Next" data-options="tipLocation:top">
  <h2>Directions</h2>
  <p>This is an example page treatment for alerting you to course objectives you need to take action on.</p>
</li>
<li data-id="youtubeexample" data-button="Close" data-options="tipLocation:top">
  <h2>YouTube</h2>
  <p>Some media is played through YouTube.  If you can see this example video you\'ll be able to watch these in the course.</p>
</li>
<li data-button="Close">
  <h2>Feedback</h2>
  <p>We are always looking to improve your course, even while you\'re taking it.  If you have questions, issues or suggestions please use the feedback button.</p>
</li>',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Guided tour for how to navigate the course, great for coming to the site for the first time.');
  $export['mooc_cis_ux-guidedtour'] = $context;

  return $export;
}
