<?php
/**
 * @file
 * Hooks provided by the Better Expoosed Filters module.
 */

/**
 * Alters Better Exposed Filters settings before the exposed form widgets are
 * built.
 *
 * @param $settings
 *   The settings array.
 * @param $context
 *   The view and display to which the settings apply.
 */
function hook_better_exposed_filters_settings_alter(&$settings, $context) {
  // Set the min/max value of a slider.
  $settings['field_price_value']['slider_options']['bef_slider_min'] = 500;
  $settings['field_price_value']['slider_options']['bef_slider_max'] = 5000;
}


/**
 * Modify the array of BEF display options for an exposed filter.
 *
 * @param array $display_options
 *   The set of display options available to this filter.
 * @param object $filter
 *   The exposed filter.
 */
function hook_better_exposed_filters_display_options_alter(&$display_options, $filter) {
  if ($filter instanceof CustomViewsFilterFoo) {
    $display_options['bef_links'] = t('Links');
  }
}
