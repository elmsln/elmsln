<?php

/**
 * @file
 * Provides the Display Suite views fields style plugin.
 */

/**
 * Plugin which defines the view mode on the resulting entity object.
 */
class views_plugin_ds_fields_view extends views_plugin_row {

  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $this->base_table = $view->base_table;
    // Special case for apachesolr_views.
    if ($this->base_table == 'apachesolr') {
      $this->base_table = 'node';
    }
    $this->base_field = $this->ds_views_3_support();
  }

  // Return base_field based on base_table. It might not be
  // the cleanest solution, it's the fastest though.
  function ds_views_3_support() {
    if (strpos($this->base_table, 'eck_') === 0) {
      // Base tables of entities created by entity construction kit (eck)
      // are prefixed with 'eck_' and the base field is always 'id'.
      return 'id';
    }

    $base_table_fields = array(
      'node' => 'nid',
      'comment' => 'cid',
      'users' => 'uid',
      'apachesolr' => 'nid',
      'taxonomy_term_data' => 'tid',
      'file_managed' => 'fid',
      'micro' => 'mid',
      'drealty_listing' => 'id',
      'commerce_product' => 'product_id',
      'commerce_line_item' => 'line_item_id',
      'civicrm_event' => 'id',
      'field_collection_item' => 'item_id',
    );
    return isset($base_table_fields[$this->base_table]) ? $base_table_fields[$this->base_table] : 'nid';
  }

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $url = url('admin/structure/ds/vd', array('absolute' => TRUE));
    $link_url = l($url, $url, array('alias' => TRUE));
    $form['info'] = array(
      '#markup' => t('The layout selection and positioning of fields happens at !url.', array('!url' => $link_url)),
    );
  }
}

/**
 * Preprocess function for ds_fields_view().
 */
function template_preprocess_ds_row_fields(&$vars) {
  static $row_layout = array();

  // Check if we have layout configured for this bundle.
  $bundle = $vars['view']->name . '-' . $vars['view']->current_display . '-fields';
  if (!isset($row_layout[$bundle])) {

    // Register the layout, even if when it returns false.
    $row_layout[$bundle] = ds_get_layout('ds_views', $bundle, 'default');

    // Add css.
    if ($row_layout[$bundle]) {
      drupal_add_css($row_layout[$bundle]['path'] . '/' . $row_layout[$bundle]['layout'] . '.css');
    }
  }

  // Render the views fields into the template layout.
  // This code is more or less copied from ds_entity_variables().
  if (isset($row_layout[$bundle])) {

    $view = $vars['view'];
    $layout = $row_layout[$bundle];
    if (!$layout) {
      return;
    }

    // Classes array.
    $vars['classes_array'] = array();
    $vars['classes_array'][] = strtr($bundle, '_', '-');

    // Template suggestions.
    $vars['theme_hook_suggestions'][] = $layout['layout'];
    $vars['theme_hook_suggestions'][] = $layout['layout'] . '__ds_views_' . $bundle;

    // Row index.
    $row_index = $view->row_index;

    // Layout wrapper.
    $vars['layout_wrapper'] = isset($layout['settings']['layout_wrapper']) ? $layout['settings']['layout_wrapper'] : 'div';

    // Layout attributes
    if (!empty($layout['settings']['layout_attributes'])) {
      $vars['layout_attributes'] = ' ' . $layout['settings']['layout_attributes'];
    }
    else {
      $vars['layout_attributes'] = '';
    }

    // Create region variables based on the layout settings.
    foreach ($layout['regions'] as $region_name => $region) {

      // Create the region content.
      $region_content = '';
      if (isset($layout['settings']['regions'][$region_name])) {
        foreach ($layout['settings']['regions'][$region_name] as $key => $field) {
          // Do not render the field when empty and configured to be hidden.
          if ($view->field[$field]->options['hide_empty'] && empty($view->style_plugin->rendered_fields[$row_index][$field])) {
            continue;
          }
          $region_content .= '<div class="views-field-' . $field . '">';
          if (!empty($view->field[$field]->options['label'])) {
            $region_content .= '<div class="field-label">';
            $region_content .= check_plain($view->field[$field]->options['label']);
            if ($view->field[$field]->options['element_label_colon']) {
              $region_content .= ':';
            }
            $region_content .= '</div>';
          }
          $region_content .= $view->style_plugin->rendered_fields[$row_index][$field];
          $region_content .= '</div>';
        }
      }
      $vars[$region_name] = $region_content;

      // Region wrapper.
      $vars[$region_name . '_wrapper'] = isset($layout['settings']['wrappers'][$region_name]) ? $layout['settings']['wrappers'][$region_name] : 'div';

      // Add extras classes to the region.
      $vars[$region_name . '_classes'] = !empty($layout['settings']['classes'][$region_name]) ? ' ' . implode(' ', $layout['settings']['classes'][$region_name]) : '';
    }
  }
}
