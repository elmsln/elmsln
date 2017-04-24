<?php

/**
 * @file
 * Custom Formatters module integration.
 */

/**
 * Implements hook_custom_formatters_engine().
 */
function custom_formatters_custom_formatters_engine_info() {
  $engines = array();

  // PHP engine.
  $engines['php'] = array(
    'label'     => t('PHP'),
    'callbacks' => array(
      'settings form'        => 'custom_formatters_engine_php_settings_form',
      'settings form submit' => 'custom_formatters_engine_php_settings_form_submit',
      'render'               => 'custom_formatters_engine_php_render',
      'export'               => 'custom_formatters_engine_php_export',
    ),
    'file'      => drupal_get_path('module', 'custom_formatters') . '/engines/php.inc',
  );

  // Token engine.
  $engines['token'] = array(
    'label'     => t('HTML + Tokens'),
    'callbacks' => array(
      'settings form' => 'custom_formatters_engine_token_settings_form',
      'render'        => 'custom_formatters_engine_token_render',
      'export'        => 'custom_formatters_engine_token_export',
    ),
    'file'      => drupal_get_path('module', 'custom_formatters') . '/engines/token.inc',
  );

  // Formatter presets engine.
  $engines['formatter_preset'] = array(
    'label'     => t('Formatter preset'),
    'callbacks' => array(
      'settings form'        => 'custom_formatters_engine_formatter_preset_settings_form',
      'settings form submit' => 'custom_formatters_engine_formatter_preset_settings_form_submit',
      'render'               => 'custom_formatters_engine_formatter_preset_render',
      'export'               => 'custom_formatters_engine_formatter_preset_export',
    ),
    'file'      => drupal_get_path('module', 'custom_formatters') . '/engines/formatter_preset.inc',
  );


  return $engines;
}

/**
 * Implements hook_custom_formatters_defaults().
 */
function custom_formatters_custom_formatters_defaults() {
  $formatters = array();

  $formatter                       = new stdClass();
  $formatter->disabled             = TRUE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version          = 2;
  $formatter->name                 = 'example_php_image';
  $formatter->label                = 'Example: Image (PHP)';
  $formatter->description          = 'A PHP example formatter; Display a Thumbnail image linked to a Large image.';
  $formatter->mode                 = 'php';
  $formatter->field_types          = 'image';
  $formatter->code                 = '// Formatter settings.
$settings = $variables[\'#display\'][\'settings\'];

$element = array();
foreach ($variables[\'#items\'] as $delta => $item) {
  $element[$delta] = array(
    \'#type\' => \'link\',
    \'#href\' => file_create_url(image_style_path($settings[\'destination_image_style\'], $item[\'uri\'])),
    \'#title\' => theme(\'image_style\', array(
      \'style_name\' => isset($settings[\'source_image_style\']) ? $settings[\'source_image_style\'] : \'thumbnail\',
      \'path\' => $item[\'uri\'],
    )),
    \'#options\' => array(
      \'html\' => TRUE,
    ),
  );
}
return $element;';
  $formatter->fapi                 = '$form = array();
$form[\'source_image_style\'] = array(
  \'#title\' => t(\'Source image styles\'),
  \'#multiple_toggle\' => \'1\',
  \'#required\' => \'0\',
  \'#type\' => \'custom_formatters_image_styles\',
  \'#weight\' => \'0\',
);
$form[\'destination_image_style\'] = array(
  \'#title\' => t(\'Destination image styles\'),
  \'#multiple_toggle\' => \'1\',
  \'#required\' => \'0\',
  \'#type\' => \'custom_formatters_image_styles\',
  \'#weight\' => \'1\',
);
';
  $formatters['example_php_image'] = $formatter;

  $formatter                         = new stdClass();
  $formatter->disabled               = TRUE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version            = 2;
  $formatter->name                   = 'example_token_image';
  $formatter->label                  = 'Example: Image (HTML + Token)';
  $formatter->description            = 'A HTML + Tokens example formatter; Display a Thumbnail image linked to a Large image.

Requires the Image URL Formatter and Field tokens modules:
- https://www.drupal.org/project/image_url_formatter
- https://www.drupal.org/project/field_tokens';
  $formatter->mode                   = 'token';
  $formatter->field_types            = 'image';
  $formatter->code                   = '<a href="[formatted_field-image:image_url:image_style-large]"><img src="[formatted_field-image:image_url:image_style-thumbnail]" alt="[field_property:alt]" title="[field_property:title]" /></a>';
  $formatters['example_token_image'] = $formatter;

  $formatter                                              = new stdClass();
  $formatter->disabled                                    = TRUE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version                                 = 2;
  $formatter->name                                        = 'example_formatter_preset_image_thumbnail';
  $formatter->label                                       = 'Example: Image thumbnail (Formatter preset)';
  $formatter->description                                 = 'A Formatter preset example formatter; Render a Thumbnail image.';
  $formatter->mode                                        = 'formatter_preset';
  $formatter->field_types                                 = 'image';
  $formatter->code                                        = 'a:2:{s:9:"formatter";s:5:"image";s:8:"settings";a:2:{s:11:"image_style";s:9:"thumbnail";s:10:"image_link";s:0:"";}}';
  $formatter->fapi                                        = '';
  $formatters['example_formatter_preset_image_thumbnail'] = $formatter;

  return $formatters;
}

/**
 * Implements hook_custom_formatters_theme_alter().
 *
 * @param $theme
 */
function custom_formatters_custom_formatters_theme_alter(&$theme) {
  $engines = module_invoke_all('custom_formatters_engine_info');
  foreach (element_children($engines) as $engine) {
    if (isset($engines[$engine]['file']) && file_exists($engines[$engine]['file'])) {
      require_once $engines[$engine]['file'];
    }
    if (function_exists($function = "custom_formatters_engine_{$engine}_theme_alter")) {
      $function($theme);
    }
  }
}
