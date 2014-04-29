<?php

/**
 * @file
 * Hooks for Views integration.
 */

/**
 * Implements hook_field_views_data().
 */
function video_embed_field_field_views_data($field) {
  $data = field_views_field_default_views_data($field);

  // Only expose these components as Views field handlers.
  $implemented = array(
    'video_url' => 'views_handler_field',
    'thumbnail_path' => 'views_embed_field_views_handler_field_thumbnail_path',
    'description' => 'views_handler_field',
  );

  // Get the translated field information.
  $properties = video_embed_field_data_property_info();

  // Iterate over video_embed_field defined tables.
  foreach ($data as &$table) {
    // Make sure the parent Views field (video_embed_field) is defined.
    if (isset($table[$field['field_name']]['field'])) {
      // Use the parent field definition as a template for component columns.
      $field_def = $table[$field['field_name']]['field'];

      // Remove 'additional fields' from the field definition. We don't
      // necessarily want all our sibling columns.
      unset($field_def['additional fields']);

      // Define the valid columns.
      $valid_columns = array();
      foreach ($implemented as $implement => $handler) {
        $column_name = $field['field_name'] . '_' . $implement;
        $valid_columns[$column_name] = $handler;
      }

      // Iterate over the video_embed_field components.
      foreach ($table as $column_name => &$column) {
        if (empty($column['field']) && isset($valid_columns[$column_name])) {
          // Assign the default component definition.
          $column['field'] = $field_def;
          $column['field']['real field'] = $column_name;
          $column['field']['handler'] = $valid_columns[$column_name];

          // Assign human-friendly labels for video_embed_field components.
          $field_labels = field_views_field_label($field['field_name']);
          $field_label = array_shift($field_labels);
          $property = str_replace($field_def['field_name'] . '_', '', $column_name);

          if (!empty($properties[$property])) {
            $property_label = $properties[$property]['label'];

            $title = t('@field-label - @property-label', array(
              '@field-label' => $field_label,
              '@property-label' => $property_label,
            ));

            $column['title'] = $title;
            $column['title short'] = $title;
          }
        }
      }
    }
  }

  return $data;
}
