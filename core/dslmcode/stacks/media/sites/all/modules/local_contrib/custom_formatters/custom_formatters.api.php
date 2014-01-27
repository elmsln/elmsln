<?php
/**
 * @file
 * Hooks provided by the Custom Formatters module.
 */

/**
 * Implements hook_custom_formatters_engine().
 */
function hook_custom_formatters_engine_info() {
  $engines = array();

  $engines['MY_MODULE'] = array(
    'label' => t('MY_MODULE'),
    'callbacks' => array(
      'settings form' => 'MYMODULE_engine_settings_form',
      'render' => 'MYMODULE_engine_render',
    ),
    'file' => drupal_get_path('module', 'MYMODULE') . '/engines/MYMODULE.inc',
  );

  return $engines;
}

/**
 * Implements hook_custom_formatters_defaults().
 */
function hook_custom_formatters_defaults() {
  $formatters = array();

  $formatter = new stdClass;
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'MYMODULE';
  $formatter->label = 'MYMODULE';
  $formatter->description = 'A PHP example formatter; Display a Thumbnail image linked to a Large image.';
  $formatter->mode = 'php';
  $formatter->field_types = 'image';
  $formatter->code = 'foreach (element_children($variables[\'#items\']) as $delta) {
  $item = $variables[\'#items\'][$delta];
  $thumbnail = theme(\'image_style\', array(\'style_name\' => \'thumbnail\', \'path\' => $item[\'uri\']));
  $large = image_style_path(\'large\', $item[\'uri\']);

  print l($thumbnail, file_create_url($large), array(\'html\' => TRUE));
}';
  $formatters['example_php_image'] = $formatter;

  return $formatters;
}
