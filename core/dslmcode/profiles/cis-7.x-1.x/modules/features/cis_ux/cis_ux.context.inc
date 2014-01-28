<?php
/**
 * @file
 * cis_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function cis_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis-about';
  $context->description = 'Blocks for the about page';
  $context->tag = 'CIS';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'pages/about' => 'pages/about',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-nodequeue_5-block' => array(
          'module' => 'views',
          'delta' => 'nodequeue_5-block',
          'region' => 'content',
          'weight' => '10',
        ),
        'views-nodequeue_8-block' => array(
          'module' => 'views',
          'delta' => 'nodequeue_8-block',
          'region' => 'content',
          'weight' => '11',
        ),
        'views-nodequeue_7-block' => array(
          'module' => 'views',
          'delta' => 'nodequeue_7-block',
          'region' => 'content',
          'weight' => '12',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blocks for the about page');
  t('CIS');
  $export['cis-about'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis-course_blocks';
  $context->description = 'Blocks for course pages';
  $context->tag = 'CIS';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'course' => 'course',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-courses_overview-block_3' => array(
          'module' => 'views',
          'delta' => 'courses_overview-block_3',
          'region' => 'content',
          'weight' => '10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blocks for course pages');
  t('CIS');
  $export['cis-course_blocks'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis-faculty_blocks';
  $context->description = 'Faculty courses authored block';
  $context->tag = 'CIS';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'person' => 'person',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'path' => array(
      'values' => array(
        'faculty/*' => 'faculty/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-courses_overview-block_1' => array(
          'module' => 'views',
          'delta' => 'courses_overview-block_1',
          'region' => 'content',
          'weight' => '9',
        ),
        'views-courses_overview-block_2' => array(
          'module' => 'views',
          'delta' => 'courses_overview-block_2',
          'region' => 'content',
          'weight' => '10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('CIS');
  t('Faculty courses authored block');
  $export['cis-faculty_blocks'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis-front_page';
  $context->description = 'Front page blocks';
  $context->tag = 'CIS';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-nodequeue_3-block' => array(
          'module' => 'views',
          'delta' => 'nodequeue_3-block',
          'region' => 'content',
          'weight' => '-23',
        ),
        'views-nodequeue_2-block' => array(
          'module' => 'views',
          'delta' => 'nodequeue_2-block',
          'region' => 'content',
          'weight' => '-23',
        ),
        'views-nodequeue_1-block' => array(
          'module' => 'views',
          'delta' => 'nodequeue_1-block',
          'region' => 'content',
          'weight' => '-23',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('CIS');
  t('Front page blocks');
  $export['cis-front_page'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis-management';
  $context->description = 'Management and administrative blocks';
  $context->tag = 'CIS';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~admin*' => '~admin*',
        '~node/edit/*' => '~node/edit/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-1' => array(
          'module' => 'menu_block',
          'delta' => '1',
          'region' => 'regions_admin_left',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('CIS');
  t('Management and administrative blocks');
  $export['cis-management'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis-news';
  $context->description = 'News block related to an entity in the system';
  $context->tag = 'News';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'academic_unit' => 'academic_unit',
        'college_services' => 'college_services',
        'course' => 'course',
        'person' => 'person',
        'program' => 'program',
        'service' => 'service',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-person_in_the_news-block' => array(
          'module' => 'views',
          'delta' => 'person_in_the_news-block',
          'region' => 'content',
          'weight' => '10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('News');
  t('News block related to an entity in the system');
  $export['cis-news'] = $context;

  return $export;
}
