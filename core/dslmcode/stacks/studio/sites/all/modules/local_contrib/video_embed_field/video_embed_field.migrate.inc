<?php
/**
 * @file
 * Migrate support for Video Embed Field module.
 */

/**
 * Implements hook_migrate_api().
 */
function video_embed_field_migrate_api() {
  $api = array(
    'api' => 2,
    'field handlers' => array('MigrateVideoEmbedFieldFieldHandler'),
  );
  return $api;
}

/**
 * Custom extended MigrateFieldHandler class for Video Embed Field module.
 */
class MigrateVideoEmbedFieldFieldHandler extends MigrateFieldHandler {

  public function __construct() {
    $this->registerTypes(array('video_embed_field'));
  }

  /**
   * {@inheritdoc}
   */
  public function fields($type, $parent_field, $migration = NULL) {
    $fields = array(
      'video_url' => t('Video: The video URL.'),
    );
    return $fields;
  }

  /**
   * {@inheritdoc}
   */
  public function prepare($entity, array $field_info, array $instance, array $values) {
    $arguments = array();
    if (isset($values['arguments'])) {
      $arguments = array_filter($values['arguments']);
      unset($values['arguments']);
    }
    $language = $this->getFieldLanguage($entity, $field_info, $arguments);

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      $return[$language][$delta] = array('video_url' => $value);
      $delta++;
    }

    return isset($return) ? $return : NULL;
  }
}
