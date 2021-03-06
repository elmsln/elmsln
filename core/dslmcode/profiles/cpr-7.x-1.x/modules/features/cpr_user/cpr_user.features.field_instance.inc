<?php
/**
 * @file
 * cpr_user.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cpr_user_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_accessibility_preference'.
  $field_instances['user-user-field_accessibility_preference'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_accessibility_preference',
    'label' => 'Accessibility Preference',
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
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'user-user-field_bio'.
  $field_instances['user-user-field_bio'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_bio',
    'label' => 'Bio',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 0,
          'student_format' => 'student_format',
          'textbook_editor' => 0,
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_format' => array(
              'weight' => 0,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 1,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'user-user-field_display_name'.
  $field_instances['user-user-field_display_name'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'How you\'d like your name to be presented to you and your classmates throughout your courses.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_display_name',
    'label' => 'Display name',
    'required' => 1,
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
          'student_format' => 'student_format',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_format' => array(
              'weight' => 0,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'user-user-field_first_name'.
  $field_instances['user-user-field_first_name'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_first_name',
    'label' => 'First name',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'student_format' => 'student_format',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_format' => array(
              'weight' => 0,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'user-user-field_last_name'.
  $field_instances['user-user-field_last_name'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_last_name',
    'label' => 'Last name',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'plain_text' => 'plain_text',
          'student_format' => 'student_format',
          'textbook_editor' => 'textbook_editor',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'plain_text' => array(
              'weight' => 10,
            ),
            'student_format' => array(
              'weight' => 0,
            ),
            'textbook_editor' => array(
              'weight' => -10,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'user-user-field_user_banner'.
  $field_instances['user-user-field_user_banner'] = array(
    'bundle' => 'user',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'people_banner_style',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_banner',
    'label' => 'Banner',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
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
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'jpg jpeg',
      'filefield_paths' => array(
        'active_updating' => 0,
        'file_name' => array(
          'options' => array(
            'pathauto' => 1,
            'slashes' => 1,
            'transliterate' => 1,
          ),
          'value' => '[current-user:name].jpg',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => 1,
            'slashes' => 1,
            'transliterate' => 1,
          ),
          'value' => 'users/banners',
        ),
        'redirect' => FALSE,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'focus' => 0,
      'focus_lock_ratio' => 0,
      'focus_min_size' => '',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'user-user-field_user_photo'.
  $field_instances['user-user-field_user_photo'] = array(
    'bundle' => 'user',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'people_user_profile',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_photo',
    'label' => 'Photo',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
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
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'jpg jpeg',
      'filefield_paths' => array(
        'active_updating' => 0,
        'file_name' => array(
          'options' => array(
            'pathauto' => 1,
            'slashes' => 1,
            'transliterate' => 1,
          ),
          'value' => '[current-user:name].jpg',
        ),
        'file_path' => array(
          'options' => array(
            'pathauto' => 1,
            'slashes' => 1,
            'transliterate' => 1,
          ),
          'value' => 'users/photos',
        ),
        'redirect' => FALSE,
        'retroactive_update' => 0,
      ),
      'filefield_paths_enabled' => 1,
      'focus' => 0,
      'focus_lock_ratio' => 0,
      'focus_min_size' => '',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'people_user_profile',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 15,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Accessibility Preference');
  t('Banner');
  t('Bio');
  t('Display name');
  t('First name');
  t('How you\'d like your name to be presented to you and your classmates throughout your courses.');
  t('Last name');
  t('Photo');

  return $field_instances;
}
