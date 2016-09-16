<?php
/**
 * @file
 * Provides the Views content cache votingapi plugin.
 */

class views_content_cache_key_votingapi extends views_content_cache_key {

  function options_form($value, &$handler = NULL) {
    // Get all of the possible tags that we could monitor:
    $metadata = votingapi_metadata();
    $options = array();
    foreach ($metadata['tags'] as $tag => $data) {
      $options['tag:' . $tag] = t('Tag: @name', array('@name' => $data['name']));
    }
    foreach ($metadata['functions'] as $function => $data) {
      $options['function:' . $function] = t('Function: @name', array('@name' => $data['name']));
    }

    return array(
      '#title' => t('Voting API'),
      '#description' => t('Checks for updates to votes'),
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => $value,
    );
  }

  function content_key($object, $object_type) {
    $keys = array();
    if ($object_type === 'votingapi_results') {
      foreach ($object as $result) {
        $keys[] = 'tag:' . $result['tag'];
        $keys[] = 'function:' . $result['function'];
      }
    }
    return $keys;
  }

  function clause_mode() {
    // We can't be combined with other cache segments:
    return 'OR';
  }
}
