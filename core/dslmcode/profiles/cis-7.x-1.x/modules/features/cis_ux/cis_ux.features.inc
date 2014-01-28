<?php
/**
 * @file
 * cis_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "delta" && $api == "delta") {
    return array("version" => "3");
  }
  if ($module == "flexslider" && $api == "flexslider_default_preset") {
    return array("version" => "1");
  }
  if ($module == "path_breadcrumbs" && $api == "path_breadcrumbs") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "video_embed_field" && $api == "default_video_embed_styles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_fe_nodequeue_export_fields().
 */
function cis_ux_fe_nodequeue_export_fields() {
  $nodequeues = array();

  // Exported nodequeues: accolades
  $nodequeues['accolades'] = array(
    'name' => 'accolades',
    'title' => 'Accolades',
    'subqueue_title' => '',
    'size' => 0,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'news',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_faculty
  $nodequeues['cis_faculty'] = array(
    'name' => 'cis_faculty',
    'title' => 'Featured faculty',
    'subqueue_title' => '',
    'size' => 3,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'person',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_featured_courses
  $nodequeues['cis_featured_courses'] = array(
    'name' => 'cis_featured_courses',
    'title' => 'Featured courses',
    'subqueue_title' => '',
    'size' => 4,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'course',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_featured_services
  $nodequeues['cis_featured_services'] = array(
    'name' => 'cis_featured_services',
    'title' => 'Featured services',
    'subqueue_title' => '',
    'size' => 0,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'college_services',
      1 => 'service',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_homepage_featured
  $nodequeues['cis_homepage_featured'] = array(
    'name' => 'cis_homepage_featured',
    'title' => 'CIS homepage featured',
    'subqueue_title' => '',
    'size' => 6,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: cis_programs
  $nodequeues['cis_programs'] = array(
    'name' => 'cis_programs',
    'title' => 'Featured programs',
    'subqueue_title' => '',
    'size' => 3,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'program',
    ),
    'roles' => array(),
    'count' => 0,
  );

  // Exported nodequeues: our_people
  $nodequeues['our_people'] = array(
    'name' => 'our_people',
    'title' => 'Our people',
    'subqueue_title' => '',
    'size' => 0,
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => 1,
    'show_in_tab' => 1,
    'show_in_links' => 0,
    'reference' => 0,
    'reverse' => 0,
    'i18n' => 0,
    'subqueues' => 1,
    'types' => array(
      0 => 'person',
    ),
    'roles' => array(),
    'count' => 0,
  );

  return $nodequeues;
}

/**
 * Implements hook_context_default_contexts_alter().
 */
function cis_ux_context_default_contexts_alter(&$data) {
  if (isset($data['regions_admin'])) {
    $data['regions_admin']->conditions['path']['values']['~node/edit/*'] = '~node/edit/*'; /* WAS: '' */
    unset($data['regions_admin']->conditions['path']['values']['~ajax*']);
    unset($data['regions_admin']->conditions['path']['values']['~node/*/*']);
  }
}

/**
 * Implements hook_filter_default_formats_alter().
 */
function cis_ux_filter_default_formats_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['filters']['lazyloader_filter'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => 0,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['1/2'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['1/3'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['1/4'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['1/5'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['1/6'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['1/8'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['2/3'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['2/5'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['3/4'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['3/5'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['3/8'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['4/5'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['5/6'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['5/8'] = 0; /* WAS: '' */
    $data['textbook_editor']['filters']['typogrify']['settings']['fractions']['7/8'] = 0; /* WAS: '' */
  }
}

/**
 * Implements hook_image_default_styles().
 */
function cis_ux_image_default_styles() {
  $styles = array();

  // Exported image style: course_author_thumb.
  $styles['course_author_thumb'] = array(
    'name' => 'course_author_thumb',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 95,
          'height' => 95,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: course_block_thumb.
  $styles['course_block_thumb'] = array(
    'name' => 'course_block_thumb',
    'effects' => array(
      4 => array(
        'label' => 'Scale and Smart Crop',
        'help' => 'Similar to "Scale And Crop", but preserves the portion of the image with the most entropy.',
        'effect callback' => 'smartcrop_scale_effect',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'smartcrop',
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 275,
          'height' => 115,
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: course_thumb.
  $styles['course_thumb'] = array(
    'name' => 'course_thumb',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 270,
          'height' => 220,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: people_headshot.
  $styles['people_headshot'] = array(
    'name' => 'people_headshot',
    'effects' => array(
      10 => array(
        'label' => 'Focus Scale And Crop',
        'help' => 'Scale and crop based on data provided by <em>ImageField Focus</em>.',
        'effect callback' => 'imagefield_focus_scale_and_crop_effect',
        'form callback' => 'imagefield_focus_scale_and_crop_form',
        'summary theme' => 'imagefield_focus_scale_and_crop_summary',
        'module' => 'imagefield_focus',
        'name' => 'imagefield_focus_scale_and_crop',
        'data' => array(
          'width' => 720,
          'height' => 580,
          'strength' => 'high',
          'fallback' => 'smartcrop',
        ),
        'weight' => -10,
      ),
      11 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 720,
          'height' => 580,
          'upscale' => 1,
        ),
        'weight' => -9,
      ),
    ),
  );

  return $styles;
}
