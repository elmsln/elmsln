<?php

/**
 * @file
 * Pathauto integration for files.
 *
 * @ingroup pathauto
 */

/**
 * Implements hook_path_alias_types().
 */
function file_entity_path_alias_types() {
  $objects['file/'] = t('Files');

  return $objects;
}

/**
 * Implements hook_pathauto().
 */
function file_entity_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'file';
      $settings['token_type'] = 'file';
      $settings['groupheader'] = t('File paths');
      $settings['patterndescr'] = t('Default path pattern (applies to all file types with blank patterns below)');
      $settings['patterndefault'] = 'files/[file:name]';
      $settings['batch_update_callback'] = 'file_entity_pathauto_bulk_update_batch_process';
      $settings['batch_file'] = drupal_get_path('module', 'file_entity') . '/file_entity.pathauto.inc';

      foreach (file_type_get_enabled_types() as $file_type => $type) {
        $settings['patternitems'][$file_type] = t('Pattern for all @file_type paths.', array('@file_type' => $type->label));
      }
      return (object) $settings;

    default:
      break;
  }
}

/**
 * Batch processing callback; Generate aliases for files.
 */
function file_entity_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('file_managed', 'fm');
  $query->leftJoin('url_alias', 'ua', "CONCAT('file/', fm.fid) = ua.source");
  $query->addField('fm', 'fid');
  $query->isNull('ua.source');
  $query->condition('fm.fid', $context['sandbox']['current'], '>');
  $query->orderBy('fm.fid');
  $query->addTag('pathauto_bulk_update');
  $query->addMetaData('entity', 'file');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    // If there are no files to update, the stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $fids = $query->execute()->fetchCol();

  pathauto_file_update_alias_multiple($fids, 'bulkupdate');
  $context['sandbox']['count'] += count($fids);
  $context['sandbox']['current'] = max($fids);
  $context['message'] = t('Updated alias for file @fid.', array('@fid' => end($fids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}
