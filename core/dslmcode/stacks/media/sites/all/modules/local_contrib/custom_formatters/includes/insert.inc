<?php
/**
 * @file
 * Insert module integration.
 */

/**
 * Implements hook_insert_styles().
 */
function custom_formatters_insert_styles() {
  $insert_styles = array();
  $supported = array('image', 'file');
  $settings = variable_get('custom_formatters_settings', array('label_prefix' => TRUE, 'label_prefix_value' => t('Custom')));

  foreach (custom_formatters_crud_load_all() as $formatter) {
    if (array_intersect($supported, drupal_explode_tags($formatter->field_types))) {
      $label = $settings['label_prefix'] ? "{$settings['label_prefix_value']}: {$formatter->label}" : $formatter->label;
      $insert_styles["custom_formatters_{$formatter->name}"] = array(
        'label' => $label,
      );
    }
  }

  return $insert_styles;
}

/**
 * Implements hook_insert_content().
 */
function custom_formatters_insert_content($item, $style, $widget) {
  $menu_item = menu_get_item();
  $form_build_id = end($menu_item['page_arguments']);

  if (is_string($form_build_id)) {
    $form = form_get_cache($form_build_id, $form_state = array());

    $obj_type = $form['#entity_type'];
    $object = $form["#{$obj_type}"];
    $field = field_info_field($menu_item['page_arguments'][0]);
    $instance = field_info_instance($obj_type, $field['field_name'], $form['#bundle']);
    $langcode = field_language($obj_type, $object, $field['field_name']);
    $items = array((array) file_load($item['fid']));
    $display = $instance['display']['default'];
    $formatter = custom_formatters_crud_load(drupal_substr($style['name'], 18));

    $display['cf_options'] = array(
      '#contextual_links' => FALSE,
    );

    return render(custom_formatters_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display, $formatter));
  }
  return FALSE;
}
