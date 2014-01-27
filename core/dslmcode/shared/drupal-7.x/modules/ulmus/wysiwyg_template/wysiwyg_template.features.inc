<?php
/**
 * @file
 * Additional hooks for features support.
 */

/**
 * Implements hook_features_export_options().
 */
function wysiwyg_template_features_export_options() {
  $options = array();
  foreach (wysiwyg_template_load_all() as $template) {
    $options[$template['name']] = $template['title'];
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function wysiwyg_template_features_export($data, &$export, $module_name) {
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['wysiwyg_template'] = 'wysiwyg_template';
  foreach ($data as $component) {
    $export['features']['wysiwyg_template'][$component] = $component;
  }
  return array();
}

/**
 * Implements hook_features_export_render().
 */
function wysiwyg_template_features_export_render($module_name, $data, $export = NULL) {
  $code = array();
  $code[] = '  $templates = array();';
  foreach ($data as $name) {
    $code[] = "  \$templates['{$name}'] = " . features_var_export(wysiwyg_template_load_template($name), '  ') . ";";
  }
  $code[] = "  return \$templates;";
  $code = implode("\n", $code);
  return array('wysiwyg_template_default_templates' => $code);
}

/**
 * Implements hook_features_revert().
 */
function wysiwyg_template_features_revert($module) {
  return wysiwyg_template_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 */
function wysiwyg_template_features_rebuild($module) {
  if ($defaults = features_get_default('wysiwyg_template', $module)) {
    foreach ($defaults as $template) {
      wysiwyg_template_save_template($template);
    }
  }
}
