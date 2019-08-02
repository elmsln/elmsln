<?php
/**
 * @file
 * On behalf implementation of Feeds mapping API for video_embed_field.module.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see FeedsNodeProcessor::getMappingTargets()
 */
function video_embed_field_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if ($info['type'] == 'video_embed_field') {
      $targets[$name . ":video_url"] = array(
        'name' => t('@name: Embed URL', array('@name' => $instance['label'])),
        'callback' => 'video_embed_field_set_target',
        'description' => t('The URL for the @label field of the @entity_type.', array('@entity_type' => $entity_type, '@label' => $instance['label'])),
        'real_target' => $name,
      );
      $targets[$name . ':description'] = array(
        'name' => t('@name: Embed description', array('@name' => $instance['label'])),
        'callback' => 'video_embed_field_set_target',
        'description' => t('The description for the @label field of the @entity_type.', array('@entity_type' => $entity_type, '@label' => $instance['label'])),
        'real_target' => $name,
      );
    }
  }
}

/**
 * Callback for mapping. Here is where the actual mapping happens.
 *
 * When the callback is invoked, $target contains the name of the field the
 * user has decided to map to and $value contains the value of the feed item
 * element the user has picked as a source.
 */
function video_embed_field_set_target($source, $entity, $target, $value) {
  if (empty($value)) {
    return;
  }

  if (!is_array($value)) {
    $value = array($value);
  }

  list($field_name, $sub_field) = explode(':', $target, 2);

  $info = field_info_field($field_name);

  // Iterate over all values.
  $field = isset($entity->$field_name) ? $entity->$field_name : array(LANGUAGE_NONE => array());

  // Allow for multiple mappings to the same target.
  $count = call_user_func_array('array_merge_recursive', $field[LANGUAGE_NONE]);
  $delta = count($count[$sub_field]);

  foreach ($value as $v) {

    if ($info['cardinality'] != FIELD_CARDINALITY_UNLIMITED && $info['cardinality'] <= $delta) {
      break;
    }

    if (is_scalar($v)) {
      $field[LANGUAGE_NONE][$delta][$sub_field] = $v;

      $delta++;
    }
  }

  $entity->{$field_name} = $field;
}
