<?php

/**
 * @file
 * Version agnostic parts of feeds_tamper.module.
 */


/**
 * @defgroup feeds_tamper_api Feeds Tamper API
 * @{
 * API functions for dealing with plugins and plugin instances.
 */

/**
 * Create a new plugin instance with default values filled in.
 *
 * @return stdClass
 *   A new plugin instance object.
 */
function feeds_tamper_new_instance() {
  ctools_include('export');
  return ctools_export_crud_new('feeds_tamper');
}

/**
 * Load all plugin instances.
 *
 * @param bool $disabled
 *   (optional) If TRUE, load disabled plugin instances. Defaults to FALSE.
 *
 * @return array
 *   An associative array of plugin instances keyed to their id.
 */
function feeds_tamper_load_all_instances($disabled = FALSE) {
  $instances = array();
  ctools_include('export');
  $configs = ctools_export_crud_load_all('feeds_tamper');
  foreach ($configs as $instance_id => $config) {
    if (!empty($config->id) && ($disabled || empty($config->disabled))) {
      $instances[$instance_id] = $config;
    }
  }
  return $instances;
}

/**
 * Load a plugin instance by id.
 *
 * @param string $id
 *   The id of the plugin instance.
 *
 * @return stdClass
 *   A plugin instance object.
 */
function feeds_tamper_load_instance($id) {
  ctools_include('export');
  return ctools_export_crud_load('feeds_tamper', $id);
}

/**
 * Save a plugin instance.
 *
 * @param stdClass $instance
 *   A plugin instance object.
 *
 * @return mixed
 *   If the plugin save failed, returns FALSE. If it succeeded, returns
 *   SAVED_NEW or SAVED_UPDATED, depending on the operation performed.
 */
function feeds_tamper_save_instance($instance) {
  ctools_include('export');
  // It's a new instance, give it the heaviest weight.
  if (!isset($instance->weight)) {
    $conditions = array('importer' => $instance->importer, 'source' => $instance->source);
    $all = ctools_export_load_object('feeds_tamper', 'conditions', $conditions);
    $weight = 0;
    foreach ($all as $i) {
      if ($i->weight >= $weight) {
        $weight = $i->weight + 1;
      }
    }
    $instance->weight = $weight;
  }
  $disabled = variable_get('default_feeds_tamper', array());
  $disabled[$instance->id] = !empty($instance->disabled) ? TRUE : FALSE;
  variable_set('default_feeds_tamper', $disabled);
  return ctools_export_crud_save('feeds_tamper', $instance);
}

/**
 * Delete a single plugin instance.
 *
 * @param string|stdClass $instance
 *   A plugin instance object or the id of a plugin instance.
 */
function feeds_tamper_delete_instance($instance) {
  // Allow for string id or plugin object.
  if (is_scalar($instance)) {
    $instance = feeds_tamper_load_instance($instance);
  }
  ctools_include('export');
  ctools_export_crud_delete('feeds_tamper', $instance);
}

/**
 * Load plugin instances by importer id.
 *
 * @param string|FeedsImporter $importer
 *   The importer id, or object to reference.
 * @param bool $disabled
 *   (optional) If TRUE load disabled plugin instances. Defaults to FALSE.
 *
 * @return array
 *   An associative array of plugin instances, keyed by source.
 */
function feeds_tamper_load_by_importer($importer, $disabled = FALSE) {
  if (is_scalar($importer)) {
    $importer = feeds_importer($importer);
  }
  $mappings = $importer->processor->config['mappings'];
  $sources = array();
  foreach ($mappings as $mapping) {
    $sources[] = $mapping['source'];
  }
  ctools_include('export');
  $t = ctools_export_load_object('feeds_tamper', 'conditions', array('importer' => $importer->id));
  // Sort into array, keyed by source.
  $instances = array();
  foreach ($t as $i) {
    // Filter disabled and only pull plugins that actually have a corresponding
    // source since we don't delete them with a mapping.
    if (($disabled || empty($i->disabled)) && in_array($i->source, $sources)) {
      $instances[$i->source][] = $i;
    }
  }
  foreach ($instances as &$instance_list) {
    usort($instance_list, '_feeds_tamper_cmp');
  }
  return $instances;
}

/**
 * Comparison callback that sorts by weight, then alphabetically by id.
 */
function _feeds_tamper_cmp($a, $b) {
  // If weights are equal compare id's.
  if ($a->weight == $b->weight) {
    $tmp = array($a->id, $b->id);
    sort($tmp);
    if ($tmp[0] == $a->id) {
      return -1;
    }
    return 1;
  }
  return ($a->weight < $b->weight) ? -1 : 1;
}

/**
 * Get all available plugins.
 *
 * @return array
 *   An associative array where the keys are the plugin keys and the values are
 *   the plugin info arrays as defined in a plugin include file.
 */
function feeds_tamper_get_plugins() {
  ctools_include('plugins');
  return ctools_get_plugins('feeds_tamper', 'plugins');
}

/**
 * Get a single plugin.
 *
 * @param string $id
 *  The id of a plugin.
 *
 * @return stdClass
 *   A plugin object.
 */
function feeds_tamper_get_plugin($id) {
  ctools_include('plugins');
  return ctools_get_plugins('feeds_tamper', 'plugins', $id);
}

/**
 * Return a machine name safe version of a string.
 *
 * @param string $string
 *   String to get machine nameized.
 *
 * @return string
 *   A lowercase string with all values not in [a-zA-Z0-9] replaced with an
 *   underscore and shortened to 128 characters.
 */
function feeds_tamper_make_machine($string) {
  return drupal_substr(preg_replace('/[^a-z0-9-]/', '_', drupal_strtolower($string)), 0, 127);
}

/**
 * @} End of "feeds_tamper_api".
 */

/**
 * Menu access callback.
 *
 * @param string|FeedsImporter $importer
 *   The importer or importer id being tampered with.
 * @param string|stdClass $instance
 *   (optional) If set, the importer attached to $instance will be tried first.
 *   Defaults to NULL.
 *
 * @return bool
 *   TRUE if the user has acces, FALSE if not.
 */
function feeds_tamper_access($importer, $instance = NULL) {
  if (isset($instance)) {
    if (is_object($instance)) {
      $importer = $instance->importer;
    }
    else {
      $importer = feeds_tamper_load_instance($instance)->importer;
    }
  }
  elseif (is_object($importer)) {
    $importer = $importer->id;
  }

  // Verify actual input if above failed.
  if ($importer) {
    // Check for permissions, otherwise return FALSE.
    if (user_access('administer feeds_tamper') || user_access('tamper ' . $importer)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Implements hook_form_feeds_ui_mapping_form_alter().
 *
 * This is an interesting bit of work. Each source name has to be unique,
 * but we have no idea how many to create with
 * feeds_tamper_feeds_parser_sources_alter() because we don't know how many
 * targets there are going to be.
 *
 * The solution is to keep track in the form how many have been added.
 */
function feeds_tamper_form_feeds_ui_mapping_form_alter(&$form, &$form_state) {
  // Don't alter the form for parsers that use manual input.
  if ($form['source']['#type'] == 'textfield') {
    return;
  }
  $newest_source = NULL;
  $newest_target = NULL;
  foreach ($form['#mappings'] as $mapping) {
    if (strpos($mapping['source'], 'Blank source ') === 0) {
      $newest_source = $mapping['source'];
    }
    elseif (strpos($mapping['target'], 'Temporary target ') === 0) {
      $newest_target = $mapping['target'];
    }
  }
  if (!empty($newest_source)) {
    list(, , $count) = explode(' ', $newest_source);
    unset($form['source']['#options']['Blank source 1']);
    $form['source']['#options']['Blank source ' . ++$count] = 'Blank source';
  }
  else {
    $form['source']['#options']['Blank source 1'] = 'Blank source';
  }
  if (!empty($newest_target)) {
    list(, , $count) = explode(' ', $newest_target);
    unset($form['target']['#options']['Temporary target 1']);
    $form['target']['#options']['Temporary target ' . ++$count] = 'Temporary target';
  }
  else {
    $form['target']['#options']['Temporary target 1'] = 'Temporary target';
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function feeds_tamper_ctools_plugin_api($owner, $api) {
  if ($owner == 'feeds_tamper' && $api == 'plugins') {
    return array('version' => 2);
  }
}

/**
 * Implements hook_ctools_plugin_directory().
 */
function feeds_tamper_ctools_plugin_directory($module, $plugin) {
  if ($module == 'feeds_tamper') {
    return 'plugins';
  }
}
