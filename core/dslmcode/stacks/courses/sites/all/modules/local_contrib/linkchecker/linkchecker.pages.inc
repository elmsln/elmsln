<?php

/**
 * @file
 * User page callbacks for the linkchecker module.
 */

/**
 * Menu callback for general reporting.
 *
 * @return string
 *   Themed report page.
 */
function linkchecker_admin_report_page() {

  $ignore_response_codes = preg_split('/(\r\n?|\n)/', variable_get('linkchecker_ignore_response_codes', "200\n206\n302\n304\n401\n403"));

  // Search for broken links in nodes and comments and blocks of all users.
  // @todo Try to make UNION'ed subselect resultset smaller.
  $subquery4 = db_select('linkchecker_node', 'ln')
    ->distinct()
    ->fields('ln', array('lid'));

  $subquery3 = db_select('linkchecker_comment', 'lc')
    ->distinct()
    ->fields('lc', array('lid'));

  $subquery2 = db_select('linkchecker_block_custom', 'lb')
    ->distinct()
    ->fields('lb', array('lid'));

  // UNION all linkchecker type tables.
  $subquery1 = db_select($subquery2->union($subquery3)->union($subquery4), 'q1')->fields('q1', array('lid'));

  // Build pager query.
  $query = db_select('linkchecker_link', 'll')->extend('PagerDefault')->extend('TableSort');
  $query->innerJoin($subquery1, 'q2', 'q2.lid = ll.lid');
  $query->fields('ll');
  $query->condition('ll.last_checked', 0, '<>');
  $query->condition('ll.status', 1);
  $query->condition('ll.code', $ignore_response_codes, 'NOT IN');

  return _linkchecker_report_page($query);
}

/**
 * Menu callback for author specific reporting.
 *
 * @param object $account
 *   The user account.
 *
 * @return string
 *   Themed report page.
 */
function linkchecker_user_report_page($account) {
  drupal_set_title($account->name);

  $ignore_response_codes = preg_split('/(\r\n?|\n)/', variable_get('linkchecker_ignore_response_codes', "200\n206\n302\n304\n401\n403"));

  // Build query for broken links in nodes of the current user.
  $subquery2 = db_select('node', 'n');
  $subquery2->innerJoin('node_revision', 'r', 'r.vid = n.vid');
  $subquery2->innerJoin('linkchecker_node', 'ln', 'ln.nid = n.nid');
  $subquery2->innerJoin('linkchecker_link', 'll', 'll.lid = ln.lid');
  $subquery2->condition('ll.last_checked', 0, '<>');
  $subquery2->condition('ll.status', 1);
  $subquery2->condition('ll.code', $ignore_response_codes, 'NOT IN');
  $subquery2->condition(db_or()
    ->condition('n.uid', $account->uid)
    ->condition('r.uid', $account->uid)
  );
  $subquery2->distinct();
  $subquery2->fields('ll', array('lid'));

  $comment_types = linkchecker_scan_comment_types();
  if (!empty($comment_types)) {
    // Build query for broken links in nodes and comments of the current user.
    $subquery3 = db_select('comment', 'c');
    $subquery3->innerJoin('linkchecker_comment', 'lc', 'lc.cid = c.cid');
    $subquery3->innerJoin('linkchecker_link', 'll', 'll.lid = lc.lid');
    $subquery3->condition('ll.last_checked', 0, '<>');
    $subquery3->condition('ll.status', 1);
    $subquery3->condition('ll.code', $ignore_response_codes, 'NOT IN');
    $subquery3->condition('c.uid', $account->uid);
    $subquery3->distinct();
    $subquery3->fields('ll', array('lid'));

    // UNION the linkchecker_node and linkchecker_comment tables.
    $subquery1 = db_select($subquery2->union($subquery3), 'q1')->fields('q1', array('lid'));
  }
  else {
    // Build query for broken links in nodes of the current user.
    $subquery1 = db_select($subquery2, 'q1')->fields('q1', array('lid'));
  }

  // Build pager query.
  $query = db_select('linkchecker_link', 'll')->extend('PagerDefault')->extend('TableSort');
  $query->innerJoin($subquery1, 'q2', 'q2.lid = ll.lid');
  $query->fields('ll');
  $query->condition('ll.last_checked', 0, '<>');
  $query->condition('ll.status', 1);
  $query->condition('ll.code', $ignore_response_codes, 'NOT IN');

  return _linkchecker_report_page($query, $account);
}

/**
 * Builds the HTML report page table with pager.
 *
 * @param SelectQueryInterface $query
 *   The pager query for the report page. Can be per user report or global.
 * @param object|null $account
 *   The user account object.
 *
 * @return string
 *   Themed report page.
 */
function _linkchecker_report_page($query, $account = NULL) {

  $links_unchecked = db_query('SELECT COUNT(1) FROM {linkchecker_link} WHERE last_checked = :last_checked AND status = :status', array(':last_checked' => 0, ':status' => 1))->fetchField();
  if ($links_unchecked > 0) {
    $links_all = db_query('SELECT COUNT(1) FROM {linkchecker_link} WHERE status = :status', array(':status' => 1))->fetchField();
    drupal_set_message(format_plural($links_unchecked,
      'There is 1 unchecked link of about @links_all links in the database. Please be patient until all links have been checked via cron.',
      'There are @count unchecked links of about @links_all links in the database. Please be patient until all links have been checked via cron.',
      array('@links_all' => $links_all)), 'warning');
  }

  $header = array(
    array('data' => t('URL'), 'field' => 'url', 'sort' => 'desc'),
    array('data' => t('Response'), 'field' => 'code', 'sort' => 'desc'),
    array('data' => t('Error'), 'field' => 'error'),
    array('data' => t('Operations')),
  );

  $result = $query
    ->limit(50)
    ->orderByHeader($header)
    ->execute();

  // Evaluate permission once for performance reasons.
  $access_edit_link_settings = user_access('edit link settings');
  $access_administer_blocks = user_access('administer blocks');
  $access_administer_redirects = user_access('administer redirects');

  $rows = array();
  foreach ($result as $link) {
    // Get the node, block and comment IDs that refer to this broken link and
    // that the current user has access to.
    $nids = _linkchecker_link_node_ids($link, $account);
    $cids = _linkchecker_link_comment_ids($link, $account);
    $bids = _linkchecker_link_block_ids($link);

    // If the user does not have access to see this link anywhere, do not
    // display it, for reasons explained in _linkchecker_link_access(). We
    // still need to fill the table row, though, so as not to throw off the
    // number of items in the pager.
    if (empty($nids) && empty($cids) && empty($bids)) {
      $rows[] = array(array('data' => t('Permission restrictions deny you access to this broken link.'), 'colspan' => count($header)));
      continue;
    }

    $links = array();

    // Show links to link settings.
    if ($access_edit_link_settings) {
      $links[] = l(t('Edit link settings'), 'linkchecker/' . $link->lid . '/edit', array('query' => drupal_get_destination()));
    }

    // Show link to nodes having this broken link.
    foreach ($nids as $nid) {
      $links[] = l(t('Edit node @node', array('@node' => $nid)), 'node/' . $nid . '/edit', array('query' => drupal_get_destination()));
    }

    // Show link to comments having this broken link.
    $comment_types = linkchecker_scan_comment_types();
    if (module_exists('comment') && !empty($comment_types)) {
      foreach ($cids as $cid) {
        $links[] = l(t('Edit comment @comment', array('@comment' => $cid)), 'comment/' . $cid . '/edit', array('query' => drupal_get_destination()));
      }
    }

    // Show link to blocks having this broken link.
    if ($access_administer_blocks) {
      foreach ($bids as $bid) {
        $links[] = l(t('Edit block @block', array('@block' => $bid)), 'admin/structure/block/manage/block/' . $bid . '/configure', array('query' => drupal_get_destination()));
      }
    }

    // Show link to redirect this broken internal link.
    if (module_exists('redirect') && $access_administer_redirects && _linkchecker_is_internal_url($link)) {
      $links[] = l(t('Create redirection'), 'admin/config/search/redirect/add', array('query' => array('source' => $link->internal, drupal_get_destination())));
    }

    // Create table data for output.
    $rows[] = array(
      'data' => array(
        l(_filter_url_trim($link->url, 40), $link->url),
        $link->code,
        check_plain($link->error),
        theme('item_list', array('items' => $links)),
      ),
    );
  }

  $build['linkchecker_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No broken links have been found.'),
  );
  $build['linkchecker_pager'] = array('#theme' => 'pager');

  return $build;
}

/**
 * Edit link settings form.
 */
function linkchecker_link_edit_form($form, &$form_state, $link) {

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => FALSE,
    '#description' => t('The link <a href="@url">@url</a> was last checked on @last_checked and failed @fail_count times.', array('@url' => $link->url, '@fail_count' => $link->fail_count, '@last_checked' => format_date($link->last_checked)))
  );

  $form['settings']['lid'] = array('#type' => 'value', '#value' => $link->lid);
  $form['settings']['url'] = array('#type' => 'value', '#value' => $link->url);

  $form['settings']['method'] = array(
    '#type' => 'select',
    '#title' => t('Select request method'),
    '#default_value' => $link->method,
    '#options' => array(
      'HEAD' => t('HEAD'),
      'GET' => t('GET'),
    ),
    '#description' => t('Select the request method used for link checks of this link. If you encounter issues like status code 500 errors with the HEAD request method you should try the GET request method before ignoring a link.'),
  );

  $form['settings']['status'] = array(
    '#default_value' => $link->status,
    '#type' => 'checkbox',
    '#title' => t('Check link status'),
    '#description' => t("Uncheck if you wish to ignore this link. Use this setting only as a last resort if there is no other way to solve a failed link check."),
  );

  $form['maintenance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Maintenance'),
    '#collapsible' => FALSE,
  );

  $form['maintenance']['recheck'] = array(
    '#default_value' => 0,
    '#type' => 'checkbox',
    '#title' => t('Re-check link status on next cron run'),
    '#description' => t('Enable this checkbox if you want to re-check the link during the next cron job rather than wait for the next scheduled check on @date.', array('@date' => format_date($link->last_checked + variable_get('linkchecker_check_links_interval', 2419200)))),
  );

  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));
  $form['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset to defaults'));

  return $form;
}

/**
 * Edit link settings form submit handler.
 */
function linkchecker_link_edit_form_submit($form, &$form_state) {
  // Force link re-check asap.
  if ($form_state['values']['recheck']) {
    db_update('linkchecker_link')
      ->condition('lid', $form_state['values']['lid'])
      ->fields(array('last_checked' => 0))
      ->execute();
    drupal_set_message(t('The link %url will be checked again on the next cron run.', array('%url' => $form_state['values']['url'])));
  }

  if ($form_state['values']['method'] != $form['settings']['method']['#default_value']) {
    // Update settings and reset statistics for a quick re-check.
    db_update('linkchecker_link')
      ->condition('lid', $form_state['values']['lid'])
      ->fields(array(
        'method' => $form_state['values']['method'],
        'fail_count' => 0,
        'last_checked' => 0,
        'status' => $form_state['values']['status'],
      ))
      ->execute();
    drupal_set_message(t('The link settings for %url have been saved and the fail counter has been reset.', array('%url' => $form_state['values']['url'])));
  }
  else {
    // Update setting only.
    db_update('linkchecker_link')
      ->condition('lid', $form_state['values']['lid'])
      ->fields(array(
        'method' => $form_state['values']['method'],
        'status' => $form_state['values']['status'],
      ))
      ->execute();
    drupal_set_message(t('The link settings for %url have been saved.', array('%url' => $form_state['values']['url'])));
  }
}

/**
 * Check if the link is an internal URL or not.
 *
 * @param object $link
 *   Link object.
 *
 * @return bool
 *   TRUE if link is internal, otherwise FALSE.
 */
function _linkchecker_is_internal_url(&$link) {
  global $base_url;

  if (strpos($link->url, $base_url) === 0) {
    $link->internal = trim(substr($link->url, strlen($base_url)), " \t\r\n\0\\/");
    return TRUE;
  }
}
