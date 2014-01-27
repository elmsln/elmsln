<?php

/**
 * @file
 * Common functions for Autocomplete Filters module.
 */

/**
 * Menu callback. Retrieves a pipe delimited string of autocomplete suggestions.
 */
function views_autocomplete_filter($filter_name, $view_name, $display_name, $string = '') {
  if (trim($string) == '') {
    // Ignore empty strings.
    return drupal_json_output(array());
  }

  // Get the view and set current display. The view and display were checked by
  // _views_autocomplete_filters_access_callback().
  $view = views_get_view($view_name);
  $view->set_display($display_name);

  // Set display and display handler vars for quick access.
  $display = $view->display[$display_name];
  $display_handler = $display->handler;

  // Get exposed filter options for our field.
  // Also, check if filter is exposed and autocomplete is enabled for this filter
  // (and if filter exists/exposed at all).
  $filters = $display_handler->get_option('filters');
  if (empty($filters[$filter_name]['exposed']) || empty($filters[$filter_name]['expose']['autocomplete_filter'])) {
    return drupal_not_found();
  }
  $expose_options = $filters[$filter_name]['expose'];

  // Determine field which will be used for output.
  if (empty($expose_options['autocomplete_field'])) {
    if ($view->get_item($display_name, 'field', $filters[$filter_name]['id'])) {
      $field_name = $filters[$filter_name]['id'];
      // force raw data for no autocomplete field defined.
      $expose_options['autocomplete_raw_suggestion'] = 1;
      $expose_options['autocomplete_raw_dropdown'] = 1;
    }
    else {
      // Field is not set, report about it to watchdog and return empty array.
      watchdog('views_autocomplete_filters', 'Field for autocomplete filter %label is not set in view %view, display %display', array(
        '%label' => $expose_options['label'],
        '%view' => $view->name,
        '%display' => $display->id,
      ), WATCHDOG_ERROR);
      return drupal_json_output(array());
    }
  }
  else {
    $field_name = $expose_options['autocomplete_field'];
  }

  // Get field options and check field exists in this display.
  $field_options = $view->get_item($display_name, 'field', $field_name);
  if (empty($field_options)) {
    // Field not exists, report about it to watchdog and return empty array.
    watchdog('views_autocomplete_filters', 'Field for autocomplete filter %label not exists in view %view, display %display', array(
      '%label' => $expose_options['label'],
      '%view' => $view->name,
      '%display' => $display->id,
    ), WATCHDOG_ERROR);
    return drupal_json_output(array());
  }

  // Collect exposed filter values and set them to the view.
  if (!empty($expose_options['autocomplete_dependent'])) {
    $exposed_input = $_GET;
  }
  else {
    $exposed_input = array();
  }
  $exposed_input[$expose_options['identifier']] = $string;
  $view->set_exposed_input($exposed_input);

  // Disable cache for view, because caching autocomplete is a waste of time and memory.
  $display_handler->set_option('cache', array('type' => 'none'));

  // Force limit for results.
  if (empty($expose_options['autocomplete_items'])) {
    $pager = array(
      'type' => 'full',
      'options' => array(),
    );
  }
  else {
    $pager = array(
      'type' => 'some',
      'options' => array(
        'items_per_page' => $expose_options['autocomplete_items'],
        'offset' => 0,
      ),
    );
  }
  $display_handler->set_option('pager', $pager);

  // Execute view query.
  $view->pre_execute();
  $view->execute($view->current_display);
  $view->post_execute();

  // Render field on each row and fill matches array.
  $use_raw_suggestion = !empty($expose_options['autocomplete_raw_suggestion']);
  $use_raw_dropdown = !empty($expose_options['autocomplete_raw_dropdown']);
  
  $matches = array();
  $view->row_index = 0;
  foreach ($view->result as $index => $row) {
    $view->row_index = $index;
    $rendered_field = $raw_field = '';

    // Render field only if suggestion or dropdown item not in RAW format.
    if (!$use_raw_suggestion || !$use_raw_dropdown) {
      $rendered_field = $view->style_plugin->get_field($index, $field_name);
    }
    // Get the raw field value only if suggestion or dropdown item is in RAW format.
    if ($use_raw_suggestion || $use_raw_dropdown) {
      $raw_field = $view->style_plugin->get_field_value($index, $field_name);
      if (!is_array($raw_field)) {
        $raw_field = array(array('value' => $raw_field));
      }
    }
    
    if (empty($raw_field)) {
      $raw_field = array(array('value' => $rendered_field));
    }

    foreach ($raw_field as $delta => $item) {
      if (isset($item['value']) && strstr(drupal_strtolower($item['value']), drupal_strtolower($string))) {
        $dropdown = $use_raw_dropdown ? check_plain($item['value']) : $rendered_field;
        if ($dropdown != '') {
          $suggestion = $use_raw_suggestion ? check_plain($item['value']) : $rendered_field;
          $suggestion = decode_entities($suggestion);

          // Add a class wrapper for a few required CSS overrides.
          $matches[$suggestion] = '<div class="reference-autocomplete">' . $dropdown . '</div>';
        }
      }
    }
  }
  unset($view->row_index);

  if (empty($matches)) {
    $matches[''] = '<div class="reference-autocomplete">' . t('The %string return no results. Please try something else.', array('%string' => $string)) . '</div>';
  }

  return drupal_json_output($matches);
}
