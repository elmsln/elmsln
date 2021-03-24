<?php

/**
 * @file
 * Batch API callbacks for the linkchecker module.
 */

/**
 * Batch: Scan nodes for links.
 */
function _linkchecker_batch_import_nodes($node_types = array()) {
  // Get all active {node}.nid's.
  $result = db_query('SELECT n.nid FROM {node} n WHERE n.status = :status AND n.type IN (:types) ORDER BY n.nid', array(':status' => 1, ':types' => $node_types));

  $operations = array();
  foreach ($result as $row) {
    $operations[] = array('_linkchecker_batch_node_import_op', array($row->nid));
  }
  $batch = array(
    'file' => drupal_get_path('module', 'linkchecker') . '/linkchecker.batch.inc',
    'finished' => '_linkchecker_batch_node_import_finished',
    'operations' => $operations,
    'title' => t('Scanning for links'),
  );

  return $batch;
}

/**
 * Batch operation: Scan one by one node for links.
 */
function _linkchecker_batch_node_import_op($nid, &$context) {
  // Load the node and scan for links.
  $node = node_load($nid, NULL, TRUE);
  _linkchecker_add_node_links($node);

  // Store results for post-processing in the finished callback.
  $context['results'][] = $node->nid;
  $context['message'] = t('Content: @title', array('@title' => $node->title));
}

/**
 * Output node batch result messages.
 *
 * @param bool $success
 *   If scan completed successfully or not.
 * @param int $results
 *   Number of nodes scanned.
 * @param array $operations
 *   Array of functions called.
 */
function _linkchecker_batch_node_import_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One node has been scanned.', '@count nodes have been scanned.');
  }
  else {
    $message = t('Scanning for links in content has failed with an error.');
  }
  drupal_set_message($message);
}

/**
 * Batch: Scan comments for links.
 */
function _linkchecker_batch_import_comments($node_types = array()) {
  // Get all active {comment}.cid's.
  $result = db_query('SELECT c.cid FROM {comment} c INNER JOIN {node} n ON c.nid = n.nid WHERE c.status = :cstatus AND n.status = :nstatus AND n.type IN (:types) ORDER BY c.cid', array(':cstatus' => COMMENT_PUBLISHED, ':nstatus' => 1, ':types' => $node_types));

  $operations = array();
  foreach ($result as $row) {
    $operations[] = array('_linkchecker_batch_comments_import_op', array($row->cid));
  }
  $batch = array(
    'file' => drupal_get_path('module', 'linkchecker') . '/linkchecker.batch.inc',
    'finished' => '_linkchecker_batch_comments_import_finished',
    'operations' => $operations,
    'title' => t('Scanning for links'),
  );

  return $batch;
}

/**
 * Batch operation: Scan one by one comment for links.
 */
function _linkchecker_batch_comments_import_op($cid, &$context) {
  // Load the comment and scan for links.
  $comment = comment_load($cid);
  _linkchecker_add_comment_links($comment);

  // Store results for post-processing in the finished callback.
  $context['results'][] = $comment->cid;
  $context['message'] = t('Comment: @title', array('@title' => $comment->subject));
}

/**
 * Output comment batch result messages.
 *
 * @param bool $success
 *   If scan completed successfully or not.
 * @param int $results
 *   Number of comments scanned.
 * @param array $operations
 *   Array of functions called.
 */
function _linkchecker_batch_comments_import_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One comment has been scanned.', '@count comments have been scanned.');
  }
  else {
    $message = t('Scanning for links in comments have failed with an error.');
  }
  drupal_set_message($message);
}

/**
 * Batch: Scan blocks for links.
 */
function _linkchecker_batch_import_block_custom() {
  // Get all {block_custom}.bid's as block module suxxx and has no usable hooks.
  $result = db_query('SELECT bid FROM {block_custom} ORDER BY bid');

  $operations = array();
  foreach ($result as $row) {
    $operations[] = array('_linkchecker_batch_import_block_custom_op', array($row->bid));
  }
  $batch = array(
    'file' => drupal_get_path('module', 'linkchecker') . '/linkchecker.batch.inc',
    'finished' => '_linkchecker_batch_block_custom_import_finished',
    'operations' => $operations,
    'title' => t('Scanning for links'),
  );

  return $batch;
}

/**
 * Batch operation: Scan one by one block for links.
 */
function _linkchecker_batch_import_block_custom_op($bid, &$context) {
  // Load the custom block and scan for links.
  $block_custom = linkchecker_block_custom_block_get($bid);
  _linkchecker_add_block_custom_links($block_custom, $block_custom->delta);

  // Store some result for post-processing in the finished callback.
  $context['results'][] = $block_custom->delta;
  $context['message'] = t('Block: @title', array('@title' => $block_custom->info));
}

/**
 * Output block batch result messages.
 *
 * @param bool $success
 *   If scan completed successfully or not.
 * @param int $results
 *   Number of blocks scanned.
 * @param array $operations
 *   Array of functions called.
 */
function _linkchecker_batch_block_custom_import_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One block has been scanned.', '@count blocks have been scanned.');
  }
  else {
    $message = t('Scanning for links in blocks have failed with an error.');
  }
  drupal_set_message($message);
}

/**
 * Recurring scans of a single node via batch API.
 *
 * @param int $nid
 *   The unique node id to scan for links.
 * @param int $missing_links_count
 *   The number of links not yet added to linkchecker_links table. By this
 *   number the re-scan rounds are calulated.
 *
 * @return array
 *   The batch task definition.
 */
function _linkchecker_batch_import_single_node($nid, $missing_links_count) {
  $operations = array();
  for ($i = 0; $i <= $missing_links_count; $i = $i + LINKCHECKER_SCAN_MAX_LINKS_PER_RUN) {
    $operations[] = array('_linkchecker_batch_single_node_import_op', array($nid));
  }
  $batch = array(
    'file' => drupal_get_path('module', 'linkchecker') . '/linkchecker.batch.inc',
    'finished' => '_linkchecker_batch_single_node_import_finished',
    'operations' => $operations,
    'title' => t('Scanning for links'),
    'progress_message' => t('Remaining @remaining of @total scans.'),
  );

  return $batch;
}

/**
 * Run single node link extraction.
 *
 * @param int $nid
 *   Node ID.
 * @param array $context
 *   Batch context array.
 */
function _linkchecker_batch_single_node_import_op($nid, &$context) {
  // Load the node and scan for links.
  $node = node_load($nid, NULL, TRUE);
  _linkchecker_add_node_links($node, TRUE);

  // Store results for post-processing in the finished callback.
  $context['results'][] = $node->nid;
  $context['message'] = t('Content: @title', array('@title' => $node->title));
}

/**
 * Output single node batch result messages.
 *
 * @param bool $success
 *   If scan completed successfully or not.
 * @param int $results
 *   How often the node has been scanned.
 * @param array $operations
 *   Array of functions called.
 */
function _linkchecker_batch_single_node_import_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'Node @nid has been re-scanned once to collect all links.', 'Node @nid has been re-scanned @count times to collect all links.', array('@nid' => $results[0]));
  }
  else {
    $message = t('Recurring scanning for links in node @nid has failed with an error.', array('@nid' => $results[0]));
  }
  drupal_set_message($message);
}

/**
 * Recurring scans of a single comment via batch API.
 *
 * @param int $cid
 *   The unique comment id to scan for links.
 * @param int $missing_links_count
 *   The number of links not yet added to linkchecker_links table. By this
 *   number the re-scan rounds are calulated.
 *
 * @return array
 *   The batch task definition.
 */
function _linkchecker_batch_import_single_comment($cid, $missing_links_count) {
  $operations = array();
  for ($i = 0; $i <= $missing_links_count; $i = $i + LINKCHECKER_SCAN_MAX_LINKS_PER_RUN) {
    $operations[] = array('_linkchecker_batch_single_comment_import_op', array($cid));
  }
  $batch = array(
    'file' => drupal_get_path('module', 'linkchecker') . '/linkchecker.batch.inc',
    'finished' => '_linkchecker_batch_single_comment_import_finished',
    'operations' => $operations,
    'title' => t('Scanning for links'),
    'progress_message' => t('Remaining @remaining of @total scans.'),
  );

  return $batch;
}

/**
 * Run single comment link extraction.
 *
 * @param int $cid
 *   Comment ID.
 * @param array $context
 *   Batch context array.
 */
function _linkchecker_batch_single_comment_import_op($cid, &$context) {
  $comment = comment_load($cid);
  _linkchecker_add_comment_links($comment, TRUE);

  // Store results for post-processing in the finished callback.
  $context['results'][] = $comment->cid;
  $context['message'] = t('Comment: @title', array('@title' => $comment->subject));
}

/**
 * Output single comment batch result messages.
 *
 * @param bool $success
 *   If scan completed successfully or not.
 * @param int $results
 *   How often the comment has been scanned.
 * @param array $operations
 *   Array of functions called.
 */
function _linkchecker_batch_single_comment_import_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'Comment @cid has been re-scanned once to collect all links.', 'Comment @cid has been re-scanned @count times to collect all links.', array('@cid' => $results[0]));
  }
  else {
    $message = t('Recurring scanning for links in comment @cid has failed with an error.', array('@cid' => $results[0]));
  }
  drupal_set_message($message);
}

/**
 * Recurring scans of a single block via batch API.
 *
 * @param int $bid
 *   The unique block id to scan for links.
 * @param int $missing_links_count
 *   The number of links not yet added to linkchecker_links table. By this
 *   number the re-scan rounds are calulated.
 *
 * @return array
 *   The batch task definition.
 */
function _linkchecker_batch_import_single_block_custom($bid, $missing_links_count) {
  $operations = array();
  for ($i = 0; $i <= $missing_links_count; $i = $i + LINKCHECKER_SCAN_MAX_LINKS_PER_RUN) {
    $operations[] = array('_linkchecker_batch_single_block_custom_import_op', array($bid));
  }
  $batch = array(
    'file' => drupal_get_path('module', 'linkchecker') . '/linkchecker.batch.inc',
    'finished' => '_linkchecker_batch_single_block_custom_import_finished',
    'operations' => $operations,
    'title' => t('Scanning for links'),
    'progress_message' => t('Remaining @remaining of @total scans.'),
  );

  return $batch;
}

/**
 * Run single block link extraction.
 *
 * @param int $bid
 *   Node ID.
 * @param array $context
 *   Batch context array.
 */
function _linkchecker_batch_single_block_custom_import_op($bid, &$context) {
  // Load the custom block and scan for links.
  $block_custom = linkchecker_block_custom_block_get($bid);
  _linkchecker_add_block_custom_links($block_custom, $block_custom->delta, TRUE);

  // Store some result for post-processing in the finished callback.
  $context['results'][] = $block_custom->delta;
  $context['message'] = t('Block: @title', array('@title' => $block_custom->info));
}

/**
 * Output single block batch result messages.
 *
 * @param bool $success
 *   If scan completed successfully or not.
 * @param int $results
 *   How often the block has been scanned.
 * @param array $operations
 *   Array of functions called.
 */
function _linkchecker_batch_single_block_custom_import_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'Block @bid has been re-scanned once to collect all links.', 'Block @bid has been re-scanned @count times to collect all links.', array('@bid' => $results[0]));
  }
  else {
    $message = t('Recurring scanning for links in block @bid has failed with an error.', array('@bid' => $results[0]));
  }
  drupal_set_message($message);
}
