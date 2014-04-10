<?php

/**
 * @file
 * Page Layout CSS Builder.
 */

global $theme_key, $theme_name;
$theme_name = $theme_key;
$path_to_at_core = drupal_get_path('theme', 'adaptivetheme');
require_once($path_to_at_core . '/inc/plugins.inc');

/**
 * Build Page Layouts
 *
 * Unlike the Panels layouts which hold CSS in their data array the Page layout
 * plugins each include a unique CSS builder function. This is required because
 * page layouts are all bespoke and can accept arbitrary user input for the
 * sidebar widths and must support three value units - pixles, em's and
 * percentages.  In other words building a one-size-fits-all builder function
 * would be overly complex and its far more flexible for themers to be able to
 * define thier own.
 *
 * As values come in from the submit function they are dispatched to the right
 * builder function.
 *
 * @param $method, tells the function which layout builder function to call.
 * @param $sidebar_first, an arbitrary numeric value.
 * @param $sidebar_second, an arbitrary numeric value.
 * @param $sidebar_unit, one of px, em or %.
 * @param $theme_name, the active theme.
 *
 * @see three_col_grail_layout() for an example of a builder function with docs.
 */
function at_build_page_layout($method, $sidebar_first, $sidebar_second, $sidebar_unit, $theme_name = NULL) {
  // Use the passed in theme_name, else grab it from global $theme_key
  if ($theme_name == NULL) {
    global $theme_key;
    $theme_name = $theme_key;
  }

  $output = '';

  // We need to invoke at_load_plugins() to get the function names, this is
  // rather expensive but we're in a submit function so IMO this is OK.
  at_load_plugins($theme_name, $plugin_type = 'page_layout');

  $builder_functions = responsive_page_layouts_data_structure($theme_name);

  foreach ($builder_functions as $function_prefix => $redundant_values) {
    if ($method === $function_prefix) {
      $function = $function_prefix . '_layout';
      $output = $function($sidebar_first, $sidebar_second, $sidebar_unit);
    }
  }

  return $output;
}

/**
 * Panels CSS Builder, programatically builds and optimizes CSS.
 *
 * Adaptivetheme panels layout plugins do not have CSS files, instead the CSS is
 * held in the data structure inside the actual plugin inc file. This data is
 * extracted, compared and output for all panel layouts per device type. The CSS
 * is highly optimized with no repetition of style declarations. The output is
 * embedded within media queries (or not, depending on theme settings) and
 * printed to file.
 *
 * @param $panel_styles
 * @param $device_panels_data
 *
 * @see adaptivetheme_five_5x20_panels_layouts() for an example of the CSS in
 * the data array with good docs and guidelines.
 */
function at_build_panels_layout_css($panel_styles, $device_panels_data) {
  $output = '';
  $declarations = $these_groups = $these_selectors_styles = array();

  foreach ($panel_styles as $panel_subtypes_data) {
    foreach ($panel_subtypes_data as $panel_subtype => $panel_subtype_styles_data) {
      if (in_array($panel_subtype, $device_panels_data)) {
        foreach ($panel_subtype_styles_data as $data_type_array) {
          foreach ($data_type_array as $declaration_type => $declaration_block) {
             foreach ($declaration_block as $selector => $declaration) {
              $selectors[$declaration_type][] = $selector;
              $declarations[$declaration_type] = array($declaration_type => $declaration);
            }
          }
        }
      }
    }
  }
  foreach ($declarations as $type => $groups) {
    foreach ($groups as $group) {
      $these_groups[$group] = $selectors[$type];
    }
  }
  foreach ($these_groups as $css_styles => $selector_array) {
    $merged_css = $css_styles;
    $these_selectors_styles[] = implode(',', $selector_array) . ' {' . $merged_css . '}';
  }

  $output = implode('', $these_selectors_styles);
  return $output;
}

/**
 * Build font family CSS.
 *
 * @param $element
 * @param $selector
 * @param $font_values
 */
function at_build_font_families($element, $selector, $font_values) {
  $output = '';

  // Format values as valid CSS
  $font_styles = array();
  if (!empty($font_values)) {
    if (isset($font_values['font_size']) && $font_values['font_size'] === '<none>') {
      $font_values['font_size'] = '';
    }
    $font_styles[] = $font_values['font_style']  ? 'font-style:' . $font_values['font_style'] . ';' : '';
    $font_styles[] = $font_values['font_weight'] ? 'font-weight:' . $font_values['font_weight'] . ';' : '';
    $font_styles[] = $font_values['font_size']   ? 'font-size:' . $font_values['font_size'] . ';' : '';
    $font_styles[] = $font_values['font_family'] ? 'font-family:' . $font_values['font_family'] : '';
  }
  $font_styles = implode('', $font_styles);

  $css = array();
  switch ($element) {
    case $element:
      if ($font_styles) {
        $css[] = $selector . '{' . $font_styles . '}';
      }
    break;
  }

  $output = implode("\n", $css);
  return $output;
}
