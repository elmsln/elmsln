<?php

/**
 * @file
 * Image module's drush integration.
 *
 * @todo image-build($field_name, $bundle, $style_name)
 */

/**
 * Implements hook_drush_command().
 */
function imageinfo_cache_drush_command() {
  $items['image-generate'] = array(
    'callback' => 'drush_imageinfo_cache_image_generate',
    'description' => 'Generate all derived images for a given field and style.',
    'core' => array('7+'),
    'drupal_dependencies' => array('image'),
    'arguments' => array(
      'field_name' => 'An image field machine name. If not provided, user may choose from a list of names.',
      'style' => 'An image style machine name. If not provided, user may choose from a list of names.',
    ),
    'examples' => array(
      'drush image-generate' => 'Pick an image field name and image style to generate.',
      'drush image-generate field_image' => 'Pick an image style to generate for the selected image field.',

      'drush image-generate all all' => 'Generate all images styles for all image fields.',
      'drush image-generate all inuse' => 'Generate images styles in use for all image fields.',
      'drush image-generate field_image all' => 'Generate all image styles for the selected image field.',
      'drush image-generate field_image inuse' => 'Generate image styles in use for the selected image field.',
      'drush image-generate field_image thumbnail' => 'Generate the selected image style for the selected image field.',
    ),
  );
  return $items;
}

/**
 * Drush callback.
 *
 * @param string $field_name
 *   Name of the field containing the images.
 * @param string $style_name
 *   Style name to generate.
 */
function drush_imageinfo_cache_image_generate($field_name = NULL, $style_name = NULL) {
  module_load_include('inc', 'imageinfo_cache', 'imageinfo_cache');
  $image_fields = imageinfo_cache_get_image_fields();
  $image_styles = image_styles();

  if (empty($field_name)) {
    // Output help.
    $choices = array_merge(array('all' => 'all'), drupal_map_assoc(array_keys($image_fields)));
    $field_name = drush_choice($choices, dt("Choose a target field to generate."));
  }
  if ($field_name !== 'all' && empty($image_fields[$field_name])) {
    // Bail if field name is bad.
    return drush_set_error(dt("Image field !field not recognized. Valid options:\n!fields", array(
      '!field' => $field_name,
      '!fields' => implode(', ', array_keys($image_fields)),
    )));
  }
  if (empty($style_name)) {
    // Output help.
    $choices = array_merge(array('all' => 'all', 'inuse' => 'inuse'), drupal_map_assoc(array_keys($image_styles)));
    $style_name = drush_choice($choices, dt("Choose an image style to generate."));
  }
  if ($style_name !== 'all' && $style_name !== 'inuse' && empty($image_styles[$style_name])) {
    // Bail if style name is bad.
    return drush_set_error(dt("Image style !style not recognized. Valid options:\n!styles", array(
      '!style' => $style_name,
      '!styles' => implode(', ', array_keys($image_styles)),
    )));
  }

  // Get list of files.
  if ($field_name === 'all') {
    $files = imageinfo_cache_get_all_images_in_all_fields($image_fields);
  }
  else {
    $files[$field_name] = imageinfo_cache_get_all_images_in_field($image_fields, $field_name);
  }

  // Get list of image styles to generate.
  foreach ($files as $field_name => $uris) {
    if (empty($uris)) {
      drush_print(dt("!field_name - has no images attached to it.\n", array(
        '!field_name' => $field_name,
      )));
      continue;
    }

    if ($style_name === 'inuse') {
      foreach ($uris as $uri) {
        $image_styles = $image_fields[$field_name];
        unset($image_styles['#field_info']);
      }
    }
    elseif ($style_name !== 'all') {
      $image_styles = array($style_name => $image_styles[$style_name]);
    }

    drush_print(dt("!field_name - Image styles: !style_names\n", array(
      '!field_name' => $field_name,
      '!style_names' => implode(", ", array_keys($image_styles)),
    )));
    foreach ($uris as $fid => $uri) {
      $return[$field_name][$fid] = imageinfo_cache_create_image_styles($uri, array(), $image_styles);
      if (!empty($return[$field_name][$fid])) {
        drush_log(dt('!uri derivatives generated.', array(
          '!uri' => $uri,
        )), 'success');
      }
      elseif (isset($return[$field_name][$fid])) {
        drush_log(dt('!uri already generated.', array(
          '!uri' => $uri,
        )), 'success');
      }
      else {
        drush_log(dt('Error generating image.', array(
          '!uri' => $uri,
        )), 'error');
      }
    }
  }
}

/**
 * Given a list of image_fields get all image uri's in them.
 *
 * @param array $image_fields
 *   Array of image fields from imageinfo_cache_get_image_fields().
 *
 * @return array
 *   Array of image files attached to the fields.
 */
function imageinfo_cache_get_all_images_in_all_fields(array $image_fields) {
  $files = array();
  foreach ($image_fields as $field_name => $values) {
    $files[$field_name] = imageinfo_cache_get_all_images_in_field($image_fields, $field_name);
  }
  return $files;
}

/**
 * Given a field name get all image uri's in it.
 *
 * @param array $image_fields
 *   Array of image fields from imageinfo_cache_get_image_fields().
 * @param string $field_name
 *   Name of field.
 *
 * @return array
 *   Array of files attached to this field.
 */
function imageinfo_cache_get_all_images_in_field(array $image_fields, $field_name) {
  $fids = array();
  foreach ($image_fields[$field_name]['#field_info'] as $field_values) {
    $query = new ApachesolrAttachmentsEntityFieldQuery();
    $results = $query->entityCondition('entity_type', $field_values['entity_type'], '=')
      ->entityCondition('bundle', $field_values['bundle'])
      ->fieldCondition($field_name, 'fid', NULL, 'IS NOT NULL')
      ->deleted(FALSE)
      ->addExtraField($field_name, 'fid', 'fid')
      ->execute();
    if (!empty($results[$field_values['entity_type']])) {
      foreach ($results[$field_values['entity_type']] as $key => $value) {
        if (!empty($value->extraFields->{$field_name . '_fid'}) && is_numeric($value->extraFields->{$field_name . '_fid'})) {
          $fids[$key] = $value->extraFields->{$field_name . '_fid'};
        }
      }
    }
  }

  $files = array();
  if (!empty($fids)) {
    $files = db_select('file_managed', 'fm')
      ->fields('fm', array('fid', 'uri'))
      ->condition('status', 1, '=')
      ->condition('fid', $fids, 'IN')
      ->execute()
      ->fetchAllKeyed();
  }
  return $files;
}

/**
 * Use instead of EntityFieldQuery when you need field information.
 *
 * @see http://drupal.stackexchange.com/questions/18093/get-only-some-fields-with-entityfieldquery/58202#58202
 *
 * Usage:
 * $q = new ApachesolrAttachmentsEntityFieldQuery;
 * $q->entityCondition('entity_type', 'node');
 *   ->addExtraField('table', 'field', 'value')
 *   ->execute();
 */
if (!class_exists('ApachesolrAttachmentsEntityFieldQuery') && class_exists('EntityFieldQuery')) {
  /**
   * Class copied from Apachesolr module.
   */
  class ApachesolrAttachmentsEntityFieldQuery extends EntityFieldQuery {
    // Extra added fields to the query.
    private $addedFields = array();

    /**
     * Finishes the query.
     *
     * Adds tags, metaData, range and returns the requested list or count.
     *
     * @param SelectQuery $select_query
     *   A SelectQuery which has entity_type, entity_id, revision_id and bundle
     *   fields added.
     * @param string $id_key
     *   Which field's values to use as the returned array keys.
     *
     * @return array
     *   See EntityFieldQuery::execute().
     */
    public function finishQuery(SelectQuery $select_query, $id_key = 'entity_id') {
      foreach ($this->tags as $tag) {
        $select_query->addTag($tag);
      }
      foreach ($this->metaData as $key => $object) {
        $select_query->addMetaData($key, $object);
      }
      $select_query->addMetaData('entity_field_query', $this);
      if ($this->range) {
        $select_query->range($this->range['start'], $this->range['length']);
      }
      if ($this->count) {
        return $select_query->countQuery()->execute()->fetchField();
      }
      $return = array();

      foreach ($this->addedFields as $added_field) {
        $fields = $select_query->getFields();
        if (!empty($added_field['field_name'])) {
          $column = $added_field['field_name'] . '_' . $added_field['column'];
          $column_alias = $added_field['field_name'] . '_' . $added_field['column_alias'];
        }
        else {
          $column = $added_field['column'];
          $column_alias = $added_field['column_alias'];
        }
        $select_query->addField($fields['entity_id']['table'], $column, $column_alias);
      }

      foreach ($select_query->execute() as $partial_entity) {
        $bundle = isset($partial_entity->bundle) ? $partial_entity->bundle : NULL;
        $ids = array(
          $partial_entity->entity_id,
          $partial_entity->revision_id,
          $bundle,
        );
        $entity = entity_create_stub_entity($partial_entity->entity_type, $ids);
        // This is adding the file id using our metaData field.
        $entity->extraFields = $partial_entity;
        $return[$partial_entity->entity_type][$partial_entity->$id_key] = $entity;
        $this->ordered_results[] = $partial_entity;
      }
      return $return;
    }

    /**
     * Add info to the $this->addedFields array.
     */
    public function addExtraField($field_name, $column, $column_alias = NULL) {
      $this->addedFields[] = array(
        'field_name' => $field_name,
        'column' => $column,
        'column_alias' => $column_alias,
      );
      return $this;
    }

  }
}
