<?php
/**
 * @file
 * harmony_core.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function harmony_core_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_taxonomy_term__harmony_category';
  $strongarm->value = array(
    'view_modes' => array(
      'full' => array(
        'custom_settings' => TRUE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'metatags' => array(
          'weight' => '6',
        ),
        'path' => array(
          'weight' => '5',
        ),
        'name' => array(
          'weight' => '0',
        ),
        'description' => array(
          'weight' => '1',
        ),
      ),
      'display' => array(
        'description' => array(
          'default' => array(
            'weight' => '0',
            'visible' => TRUE,
          ),
          'full' => array(
            'weight' => '0',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_taxonomy_term__harmony_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_user__user';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(
        'summary' => array(
          'harmony_user_post_profile' => array(
            'weight' => '2',
            'visible' => FALSE,
          ),
        ),
        'name' => array(
          'harmony_user_post_profile' => array(
            'weight' => '11',
            'visible' => TRUE,
          ),
        ),
        'user_picture' => array(
          'harmony_user_post_profile' => array(
            'weight' => '10',
            'visible' => TRUE,
          ),
        ),
        'username' => array(
          'harmony_user_post_profile' => array(
            'weight' => '11',
            'visible' => TRUE,
          ),
        ),
        'harmony_core_user_name' => array(
          'harmony_user_post_profile' => array(
            'weight' => '11',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_user__user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_harmony_core_pattern';
  $strongarm->value = 'thread/[harmony_thread:thread-id]/[harmony_thread:title]';
  $export['pathauto_harmony_core_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_harmony_category_pattern';
  $strongarm->value = 'category/[term:parents:join-path]/[term:name]';
  $export['pathauto_taxonomy_term_harmony_category_pattern'] = $strongarm;

  return $export;
}
