<?php

/**
 * @file
 * Integration with Views.
 */

/**
 * Implements hook_views_data_alter().
 */
function views_autocomplete_filters_views_data_alter(&$data) {
  foreach ($data as $data_type => $data_fields) {
    foreach ($data_fields as $fieldname => $data_field) {
      if (isset($data_field['filter']['handler'])) {
        // Extend the basic textfield filter handler with autocomplete.
        if ($data_field['filter']['handler'] == 'views_handler_filter_string') {
          $data[$data_type][$fieldname]['filter']['handler'] = 'views_autocomplete_filters_handler_filter_string';
        }
        // Extend the multiple fields search filter handler with autocomplete.
        elseif ($data_field['filter']['handler'] == 'views_handler_filter_combine') {
          $data[$data_type][$fieldname]['filter']['handler'] = 'views_autocomplete_filters_handler_filter_combine';
        }
      }
    }
  }
}
