<?php
/**
 * @file
 * elmsmedia_video.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function elmsmedia_video_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-video-field_caption'.
  $field_instances['node-video-field_caption'] = array(
    'bundle' => 'video',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 6,
      ),
      'iframe' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'mediavideo' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'mediavideo__poster' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'mediavideo__thumbnail' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'mediavideo__thumbnail__right' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_caption',
    'label' => 'Caption',
    'required' => 0,
    'settings' => array(
      'authcache' => array(
        'clients' => array(
          'authcache_ajax' => array(
            'status' => 1,
            'weight' => 0,
          ),
        ),
        'fallback' => 'cancel',
        'lifespan' => 3600,
        'perpage' => 0,
        'peruser' => 1,
        'status' => 0,
      ),
      'description_field' => 0,
      'file_directory' => 'captions',
      'file_extensions' => 'txt srt xml vtt',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'bar',
      ),
      'type' => 'file_generic',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-video-field_cis_course_ref'.
  $field_instances['node-video-field_cis_course_ref'] = array(
    'bundle' => 'video',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => 1,
        ),
        'type' => 'entityreference_label',
        'weight' => 8,
      ),
      'iframe' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
      ),
      'mediavideo' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'mediavideo__poster' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'mediavideo__thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'mediavideo__thumbnail__right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_cis_course_ref',
    'label' => 'Course',
    'required' => 0,
    'settings' => array(
      'authcache' => array(
        'clients' => array(
          'authcache_ajax' => array(
            'status' => 1,
            'weight' => 0,
          ),
        ),
        'fallback' => 'cancel',
        'lifespan' => 3600,
        'perpage' => 0,
        'peruser' => 1,
        'status' => 0,
      ),
      'behaviors' => array(
        'prepopulate' => array(
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'node-video-field_citation'.
  $field_instances['node-video-field_citation'] = array(
    'bundle' => 'video',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'iframe' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_citation',
    'label' => 'Citation',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'simple_text' => 'simple_text',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'simple_text' => array(
              'weight' => 0,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-video-field_elmsln_competency'.
  $field_instances['node-video-field_elmsln_competency'] = array(
    'bundle' => 'video',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Does this item reflect achievement in pursuit of a course competency? Set this for critical events / learning objectives to send additional xAPI metadata for tracking student progression toward learning this competency.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'iframe' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_elmsln_competency',
    'label' => 'Competency',
    'required' => 0,
    'settings' => array(
      'authcache' => array(
        'clients' => array(
          'authcache_ajax' => array(
            'status' => 1,
            'weight' => 0,
          ),
        ),
        'fallback' => 'cancel',
        'lifespan' => 3600,
        'perpage' => 0,
        'peruser' => 1,
        'status' => 0,
      ),
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-video-field_poster'.
  $field_instances['node-video-field_poster'] = array(
    'bundle' => 'video',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'medium',
        ),
        'type' => 'image',
        'weight' => 5,
      ),
      'iframe' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'mediavideo' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'mediavideo__poster' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'mediavideo__thumbnail' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'mediavideo__thumbnail__right' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_poster',
    'label' => 'Poster',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'focus' => 0,
      'focus_lock_ratio' => 0,
      'focus_min_size' => '',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-video-field_tagging'.
  $field_instances['node-video-field_tagging'] = array(
    'bundle' => 'video',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Tagging media can make it easier to find after the fact. This is used for searching and filtering.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 10,
      ),
      'iframe' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'mediavideo' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'mediavideo__poster' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'mediavideo__thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'mediavideo__thumbnail__right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_tagging',
    'label' => 'Tags',
    'required' => 0,
    'settings' => array(
      'authcache' => array(
        'clients' => array(
          'authcache_ajax' => array(
            'status' => 1,
            'weight' => 0,
          ),
        ),
        'fallback' => 'cancel',
        'lifespan' => 3600,
        'perpage' => 0,
        'peruser' => 1,
        'status' => 0,
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'autocomplete_deluxe',
      'settings' => array(
        'autocomplete_deluxe_path' => 'autocomplete_deluxe/taxonomy',
        'delimiter' => '',
        'limit' => 10,
        'min_length' => 0,
        'not_found_message' => 'The term \'@term\' will be added.',
        'size' => 60,
      ),
      'type' => 'autocomplete_deluxe_taxonomy',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-video-field_transcript'.
  $field_instances['node-video-field_transcript'] = array(
    'bundle' => 'video',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 7,
      ),
      'iframe' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'mediavideo' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'mediavideo__poster' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'mediavideo__thumbnail' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'mediavideo__thumbnail__right' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_transcript',
    'label' => 'Transcript',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'transcript',
      'file_extensions' => 'txt',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-video-field_video'.
  $field_instances['node-video-field_video'] = array(
    'bundle' => 'video',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_url_plain',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_url_plain',
        'weight' => 4,
      ),
      'iframe' => array(
        'label' => 'hidden',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_url_plain',
        'weight' => 0,
      ),
      'mediavideo' => array(
        'label' => 'hidden',
        'module' => 'elmsmedia_helper',
        'settings' => array(
          'controls' => 1,
          'download_link' => FALSE,
          'download_text' => 'Download',
          'height' => '400px',
        ),
        'type' => 'ableplayer_video',
        'weight' => 0,
      ),
      'mediavideo__poster' => array(
        'label' => 'hidden',
        'module' => 'elmsmedia_helper',
        'settings' => array(
          'controls' => 1,
          'download_link' => FALSE,
          'download_text' => 'Download',
          'height' => '400px',
        ),
        'type' => 'ableplayer_video',
        'weight' => 0,
      ),
      'mediavideo__thumbnail' => array(
        'label' => 'hidden',
        'module' => 'elmsmedia_helper',
        'settings' => array(
          'controls' => 1,
          'download_link' => FALSE,
          'download_text' => 'Download',
          'height' => '400px',
        ),
        'type' => 'ableplayer_video',
        'weight' => 0,
      ),
      'mediavideo__thumbnail__right' => array(
        'label' => 'hidden',
        'module' => 'elmsmedia_helper',
        'settings' => array(
          'controls' => TRUE,
          'download_link' => FALSE,
          'download_text' => 'Download',
          'height' => 385,
        ),
        'type' => 'ableplayer_video',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_video',
    'label' => 'Video',
    'required' => 1,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'video',
      'file_extensions' => 'mp4',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'bar',
      ),
      'type' => 'file_generic',
      'weight' => 5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Caption');
  t('Citation');
  t('Competency');
  t('Course');
  t('Does this item reflect achievement in pursuit of a course competency? Set this for critical events / learning objectives to send additional xAPI metadata for tracking student progression toward learning this competency.');
  t('Poster');
  t('Tagging media can make it easier to find after the fact. This is used for searching and filtering.');
  t('Tags');
  t('Transcript');
  t('Video');

  return $field_instances;
}
