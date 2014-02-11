<?php
/**
 * @file
 * Token engine for Custom Formatters modules.
 */

/**
 *
 */
function custom_formatters_engine_php_theme_alter(&$theme) {
  $theme['custom_formatters_php_export'] = array(
    'variables' => array(
      'item' => NULL,
      'module' => NULL,
    ),
    'template' => 'php.export',
    'path' => drupal_get_path('module', 'custom_formatters') . '/engines',
  );
}

/**
 * Settings form callback for Custom Formatters PHP engine.
 */
function custom_formatters_engine_php_settings_form(&$form) {
  $form['code']['#description'] = t('Enter the PHP code that will be evaluated. You should NOT include %php tags. The $variables object is available.', array('%php' => '<?php ?>'));
  $form['code']['#attributes']['class'][] = 'syntax-php';

  $form['settings'] = array(
    '#type' => 'container',
  );

  // Additional debugging modes.
  $form['preview']['options']['dpm'] = array(
    '#type' => 'container',
  );
  $form['preview']['options']['dpm']['vars'] = array(
    '#type' => 'checkbox',
    '#title' => t('Output <strong>$variables</strong> array (requires <a href="http://drupal.org/project/devel">Devel</a> module).'),
    '#default_value' => module_exists('devel'),
    '#disabled' => !module_exists('devel'),
  );
  $form['preview']['options']['dpm']['html'] = array(
    '#type' => 'checkbox',
    '#title' => t('Output raw HTML (requires <a href="http://drupal.org/project/devel">Devel</a> module).'),
    '#default_value' => module_exists('devel'),
    '#disabled' => !module_exists('devel'),
  );
}

/**
 * Render callback for Custom Formatters PHP engine.
 */
function custom_formatters_engine_php_render($formatter, $obj_type, $object, $field, $instance, $langcode, $items, $display) {
  global $theme_path, $theme_info, $conf;

  // Store current theme path.
  $old_theme_path = $theme_path;

  // Restore theme_path to the theme, as long as php_eval() executes,
  // so code evaluated will not see the caller module as the current theme.
  // If theme info is not initialized get the path from theme_default.
  if (!isset($theme_info)) {
    $theme_path = drupal_get_path('theme', $conf['theme_default']);
  }
  else {
    $theme_path = dirname($theme_info->filename);
  }

  // Build variables array for formatter.
  $variables = array(
    '#obj_type' => $obj_type,
    '#object' => $object,
    '#field' => $field,
    '#instance' => $instance,
    '#langcode' => $langcode,
    '#items' => $items,
    '#display' => $display,
  );

  ob_start();
  $output = eval($formatter->code);
  $output = !empty($output) ? $output : ob_get_contents();
  ob_end_clean();

  // Preview debugging; Show the available variables data.
  if (module_exists('devel') && isset($formatter->preview) && $formatter->preview['options']['dpm']['vars']) {
    dpm($variables);
  }

  // Recover original theme path.
  $theme_path = $old_theme_path;

  return $output;
}

/**
 * Export callback for Custom Formatters PHP engine.
 */
function custom_formatters_engine_php_export($item, $module) {
  $formatter = clone $item;

  if (isset($formatter->fapi)) {
    ob_start();
    eval($formatter->fapi);
    ob_get_clean();

    if (isset($form)) {
      $formatter->form = $form;
    }
  }

  // Modify #default_value for hook_field_formatter_settings_form() export.
  include drupal_get_path('module', 'form_builder') . '/examples/form_builder_examples.module';
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['#default_value'])) {
      unset($form[$key]['#default_value']);
    }
    $form[$key]['#default_value'] = "[default-value::{$key}]";
  }
  $formatter->fapi = form_builder_examples_export_recurse($form);
  preg_match_all('/\'\[default-value::(.*)?\]\'/', $formatter->fapi, $matches, PREG_SET_ORDER);
  foreach ($matches as $match) {
    $formatter->fapi = str_replace($match[0], "\$settings['{$match[1]}']", $formatter->fapi);
  }

  return theme('custom_formatters_php_export', array('item' => $formatter, 'module' => $module));
}

/**
 * Help callback for Custom Formatters PHP engine.
 */
function custom_formatters_engine_php_help() {
  return t('A PHP Formatter is essentially a standard Drupal API Field Formatter, the primary difference is that all availble parameters have been bundled into a <strong>$variables</strong> array for ease of use.') . "<br />\n"
       . t('The Formatter should be PHP code that returns either a value or <a href="http://drupal.org/node/930760">Render Array</a> and it should NOT include <em><?php ?></em> tags.') . "\n";
}
