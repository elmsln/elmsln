<?php
/**
 * @file
 * On behalf implementation of Feeds mapping API for video_embed_field.module.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see FeedsNodeProcessor::getMappingTargets().
 */
function video_embed_field_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if ($info['type'] == 'video_embed_field') {
      $targets[$name] = array(
        'name' => $instance['label'],
        'callback' => 'video_embed_field_set_target',
        'description' => t('The @label field of the node.', array('@label' => $instance['label'])),
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

  $field = isset($entity->$target) ? $entity->$target : array();
  if (!is_array($value) && !is_object($value)) {
    $field['und'][0]['video_url'] = $value;
  }
  $entity->{$target} = $field;

}
