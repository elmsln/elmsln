<?php
/**
 * @file
 * mooc_content_theming.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function mooc_content_theming_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-page-field_mooc_color'
  $field_instances['node-page-field_mooc_color'] = array(
    'bundle' => 'page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'An accent color to associate with this content.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_mooc_color',
    'label' => 'Color',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'jquery_colorpicker',
      'settings' => array(),
      'type' => 'jquery_colorpicker',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-page-field_mooc_image'
  $field_instances['node-page-field_mooc_image'] = array(
    'bundle' => 'page',
    'deleted' => 0,
    'description' => 'An image to use to replace the one in the theme.',
    'display' => array(
      'default' => array(
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
    'field_name' => 'field_mooc_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'mooc_images',
      'file_extensions' => 'png gif jpg jpeg',
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
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-page-field_mooc_thumbnail'
  $field_instances['node-page-field_mooc_thumbnail'] = array(
    'bundle' => 'page',
    'deleted' => 0,
    'description' => 'A smaller representation of the content visually',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
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
    'field_name' => 'field_mooc_thumbnail',
    'label' => 'Thumbnail',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'mooc_thumbnails',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '50KB',
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
      'weight' => 11,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('A smaller representation of the content visually');
  t('An accent color to associate with this content.');
  t('An image to use to replace the one in the theme.');
  t('Color');
  t('Image');
  t('Thumbnail');

  return $field_instances;
}
