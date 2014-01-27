<?php
/**
 * @file
 * Integration with the Feeds module.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see FeedsNodeProcessor::getMappingTargets().
 */
function email_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if (in_array($info['type'], array('email'))) {
      $targets[$name] = array(
        'name' => $instance['label'],
        'callback' => 'email_feeds_set_target',
        'description' => t('The @label field of the node.', array('@label' => $instance['label'])),
      );
    }
  }
}

/**
 * Callback function for mapping email field.
 *
 * This function is invoked via hook_feeds_processor_targets_alter().
 * Here is where the actual mapping happens.
 *
 * @param $target
 *   the name of the field the user has decided to map to.
 * @param $value
 *   the value of the feed item element the user has picked as a source.
 */
function email_feeds_set_target($source, $entity, $target, $value) {
  $value = is_array($value) ? $value : array($value);

  $info = field_info_field($target);

  // Iterate over all values.
  $i = 0;
  $field = isset($entity->$target) ? $entity->$target : array();
  foreach ($value as $v) {
    if (!is_array($v) && !is_object($v)) {
      $field[LANGUAGE_NONE][$i]['email'] = $v;
    }
    if ($info['cardinality'] == 1) {
      break;
    }
    $i++;
  }

  $entity->{$target} = $field;
}
