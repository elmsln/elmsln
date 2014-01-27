<?php
/**
 * @file
 * Integration with Views.
 */

function views_autocomplete_filters_views_data_alter(&$data) {
  foreach ($data as $data_type => $data_fields) {
    foreach ($data_fields as $fieldname => $data_field) {
      if (isset($data_field['filter']['handler']) && ($data_field['filter']['handler'] == 'views_handler_filter_string')) {
          $data[$data_type][$fieldname]['filter']['handler'] = 'views_autocomplete_filters_handler_filter_string';
      }
    }
  }
}