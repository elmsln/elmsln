<?php

/**
 * @file
 * Definition of views_handler_field_file_link_usage.
 */

/**
 * Field handler to present a link to view the usage of a file.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_file_link_usage extends views_handler_field_file_link {

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['count_entities_once'] = array('default' => TRUE);
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    $form['count_entities_once'] = array(
      '#type' => 'checkbox',
      '#title' => t('Count each unique entity once'),
      '#description' => t('Files can be used multiple times for an entity, especially when an entity is revisionable.'),
      '#default_value' => !empty($this->options['count_entities_once']),
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Renders the link.
   */
  function render_link($file, $values) {
    // Ensure user has access to update this file.
    if (!file_entity_access('update', $file)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "file/$file->fid/usage";
    $this->options['alter']['query'] = drupal_get_destination();

    // Get total count for each file.
    $total_count = 0;
    $file_usage = file_usage_list($file);
    $count_entities_once = !empty($this->options['count_entities_once']);
    foreach ($file_usage as $module => $usage) {
      foreach ($usage as $entity_type => $entity_ids) {
        if ($count_entities_once) {
          // Just count each unique entity once.
          $total_count += count($entity_ids);
        }
        else {
          // Count multiple usages for each entity.
          foreach ($entity_ids as $id => $count) {
            $total_count += $count;
          }
        }
      }
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : format_plural((int) $total_count, '1 place', '@count places');
    return $text;
  }
}
