<?php

/**
 * Prints the cache status of the currently displayed page.
 *
 * see @boost_block_view()
 */
function boost_block_view_status() {
  global $user;

  $block = array();
  $block['subject'] = '';

  // Don't show the block to anonymous users
  if (! $user->uid) {
    return $block;
  }

  // Do not use the global $_boost to not confuse hook_exit()
  $_boost = boost_transform_url();

  // Unset these variables otherwise boost_is_cacheable() will quickly bail out.
  unset($_boost['is_cacheable']);
  unset($_boost['is_cacheable_reason']);

  $_boost = boost_is_cacheable($_boost, 'status');

  if (! $_boost['is_cacheable']) {
    $reason = ($_boost['is_cacheable_reason'] ? $_boost['is_cacheable_reason'] : 'reason unknown');
    $block['content']['is_not_cacheable'] = array(
      '#markup' => '<p>' . t('This page will not be cached: %reason', array('%reason' => $reason)) . '</p>',
    );

    return $block;
  }

  // We need the extention for the filename
  $_boost['header_info'] = boost_get_header_info();
  $_boost['matched_header_info'] = boost_match_header_attributes($_boost['header_info']);

  $filename = (isset($_boost['filename']) ? $_boost['filename'] . '.' . $_boost['matched_header_info']['extension'] : 'n/a');

  if (file_exists($filename)) {
    // be precise on the time (seconds and timezone)
    $generated = date('c', filemtime($filename));
  }
  else {
    $generated = 'not cached yet (either no one has visited the page recently, or something is preventing the cache from being generated).';
  }

  $block['content'] = array(
    'filename' => array(
      '#markup' => '<p>' . t('File: %filename', array('%filename' => $filename)) . '</p>',
    ),
    'generated' => array(
      '#markup' => '<p>' . t('Generated: %generated', array('%generated' => $generated)) . '</p>',
    ),
  );

  if (file_exists($filename) && user_access('boost flush pages')) {
    $block['content']['flush'] = array(
      '#markup' => drupal_render(drupal_get_form('boost_block_flush_form')),
    );
  }

  return $block;
}

function boost_block_flush_form() {
  $form = array();

  $form['boost_cache']['clear'] = array(
    '#type' => 'submit',
    '#value' => t('Flush Page'),
  );

  return $form;
}

function boost_block_flush_form_submit() {
  $_boost = boost_transform_url();

  // We need the extention for the filename
  $_boost['header_info'] = boost_get_header_info();
  $_boost['matched_header_info'] = boost_match_header_attributes($_boost['header_info']);

  $filename = $_boost['filename'] . '.' . $_boost['matched_header_info']['extension'];

  if (is_file($filename)) {
    if (unlink($filename)) {
      drupal_set_message(t('%filename was deleted from the Boost cache', array('%filename' => $filename)));
    }
    else {
      drupal_set_message(t('%filename could not be deleted, check file permissions on disk to see if the web server can write/delete the file.', array('%filename' => $filename)));
    }
  }
  else {
    drupal_set_message(t('%filename was not found in the Boost cache and could not be deleted.', array('%filename' => $filename)));
  }
}

