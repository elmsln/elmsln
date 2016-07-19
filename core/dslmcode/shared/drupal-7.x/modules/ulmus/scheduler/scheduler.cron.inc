<?php

/**
 * @file
 * Scheduler cron functions.
 *
 * This file is included only when running a crontab job or executing the
 * lightweight cron via the admin interface.
 */

/**
 * Publish scheduled nodes.
 *
 * @return bool
 *   TRUE if any node has been published, FALSE otherwise.
 */
function _scheduler_publish() {
  $result = FALSE;

  // If the time now is greater than the time to publish a node, publish it.
  // The INNER join on 'node' and 'users' is just to ensure the nodes are valid.
  $query = db_select('scheduler', 's');
  $query->addField('s', 'nid');
  $query->addJoin('INNER', 'node', 'n', 's.nid = n.nid');
  $query->addJoin('INNER', 'users', 'u', 'u.uid = n.uid');
  $query->condition('s.publish_on', 0, '>');
  $query->condition('s.publish_on', REQUEST_TIME, '<=');
  $query_result = $query->execute();
  $nids = array();
  while ($node = $query_result->fetchObject()) {
    $nids[] = $node->nid;
  }

  $action = 'publish';

  // Allow other modules to add to the list of nodes to be published.
  $nids = array_unique(array_merge($nids, _scheduler_scheduler_nid_list($action)));

  // Allow other modules to alter the list of nodes to be published.
  drupal_alter('scheduler_nid_list', $nids, $action);

  foreach ($nids as $nid) {
    $n = node_load($nid);

    // Check that other modules allow the action on this node.
    if (!_scheduler_allow($n, $action)) {
      continue;
    }

    // Invoke Scheduler API for modules to react before the node is published.
    // @todo For D8 move the 'pre' call to here.
    // See https://www.drupal.org/node/2311273

    // Update timestamps.
    $n->changed = $n->publish_on;
    $old_creation_date = $n->created;
    if (variable_get('scheduler_publish_touch_' . $n->type, 0) == 1) {
      $n->created = $n->publish_on;
    }

    $create_publishing_revision = variable_get('scheduler_publish_revision_' . $n->type, 0) == 1;
    if ($create_publishing_revision) {
      $n->revision = TRUE;
      // Use a core date format to guarantee a time is included.
      $n->log = t('Node published by Scheduler on @now. Previous creation date was @date.', array(
        '@now' => format_date(REQUEST_TIME, 'short'),
        '@date' => format_date($old_creation_date, 'short'),
      ));
    }
    // Unset publish_on so the node will not get rescheduled by subsequent calls
    // to node_save(). Save the value for use when calling Rules.
    $publish_on = $n->publish_on;
    $n->publish_on = NULL;

    // Invoke scheduler API to allow modules to alter the node before it is
    // saved.
    // @todo For D8, remove this from here.
    _scheduler_scheduler_api($n, 'pre_' . $action);

    // Use the actions system to publish the node.
    watchdog('scheduler', '@type: scheduled publishing of %title.', array('@type' => $n->type, '%title' => $n->title), WATCHDOG_NOTICE, l(t('view'), 'node/' . $n->nid, array('alias' => TRUE)));
    $actions = array('node_publish_action', 'node_save_action');
    $context['node'] = $n;
    actions_do($actions, $n, $context, NULL, NULL);

    // Invoke the event to tell Rules that Scheduler has published this node.
    if (module_exists('rules')) {
      rules_invoke_event('scheduler_node_has_been_published_event', $n, $publish_on, $n->unpublish_on);
    }

    // Invoke scheduler API for modules to react after the node is published.
    _scheduler_scheduler_api($n, $action);

    $result = TRUE;
  }

  return $result;
}

/**
 * Unpublish scheduled nodes.
 *
 * @return bool
 *   TRUE is any node has been unpublished, FALSE otherwise.
 */
function _scheduler_unpublish() {
  $result = FALSE;

  // If the time is greater than the time to unpublish a node, unpublish it.
  // The INNER join on 'node' and 'users' is just to ensure the nodes are valid.
  $query = db_select('scheduler', 's');
  $query->addField('s', 'nid');
  $query->addJoin('INNER', 'node', 'n', 's.nid = n.nid');
  $query->addJoin('INNER', 'users', 'u', 'u.uid = n.uid');
  $query->condition('s.unpublish_on', 0, '>');
  $query->condition('s.unpublish_on', REQUEST_TIME, '<=');
  $query_result = $query->execute();
  $nids = array();
  while ($node = $query_result->fetchObject()) {
    $nids[] = $node->nid;
  }

  $action = 'unpublish';

  // Allow other modules to add to the list of nodes to be unpublished.
  $nids = array_unique(array_merge($nids, _scheduler_scheduler_nid_list($action)));

  // Allow other modules to alter the list of nodes to be unpublished.
  drupal_alter('scheduler_nid_list', $nids, $action);

  foreach ($nids as $nid) {
    $n = node_load($nid);

    // Check that other modules allow the action on this node.
    if (!_scheduler_allow($n, $action)) {
      continue;
    }

    // Do not process the node if it has a publish_on time which is in the past,
    // as this implies that scheduled publishing has been blocked by one of the
    // API functions we provide. Hence unpublishing should be halted too.
    if (!empty($n->publish_on) && $n->publish_on <= REQUEST_TIME) {
      continue;
    }

    // Invoke scheduler API for modules to react before the node is unpublished.
    // @todo For D8, move the 'pre' call to here.
    // See https://www.drupal.org/node/2311273

    // Update timestamps.
    $old_change_date = $n->changed;
    $n->changed = $n->unpublish_on;

    $create_unpublishing_revision = variable_get('scheduler_unpublish_revision_' . $n->type, 0) == 1;
    if ($create_unpublishing_revision) {
      $n->revision = TRUE;
      // Use a core date format to guarantee a time is included.
      $n->log = t('Node unpublished by Scheduler on @now. Previous change date was @date.', array(
        '@now' => format_date(REQUEST_TIME, 'short'),
        '@date' => format_date($old_change_date, 'short'),
      ));
    }
    // Unset unpublish_on so the node will not get rescheduled by subsequent
    // calls to node_save(). Save the value for use when calling Rules.
    $unpublish_on = $n->unpublish_on;
    $n->unpublish_on = NULL;

    // Invoke scheduler API to allow modules to alter the node before it is
    // saved.
    // @todo For D8, remove this from here.
    _scheduler_scheduler_api($n, 'pre_' . $action);

    // Use the actions system to unpublish the node.
    watchdog('scheduler', '@type: scheduled unpublishing of %title.', array('@type' => $n->type, '%title' => $n->title), WATCHDOG_NOTICE, l(t('view'), 'node/' . $n->nid, array('alias' => TRUE)));
    $actions = array('node_unpublish_action', 'node_save_action');
    $context['node'] = $n;
    actions_do($actions, $n, $context, NULL, NULL);

    // Invoke event to tell Rules that Scheduler has unpublished this node.
    if (module_exists('rules')) {
      rules_invoke_event('scheduler_node_has_been_unpublished_event', $n, $n->publish_on, $unpublish_on);
    }

    // Invoke scheduler API for modules to react after the node is unpublished.
    _scheduler_scheduler_api($n, 'unpublish');

    $result = TRUE;
  }

  return $result;
}

/**
 * Gather node IDs for all nodes that need to be $action'ed.
 *
 * @param string $action
 *   The action being performed, either "publish" or "unpublish".
 *
 * @return array
 *   An array of node ids.
 */
function _scheduler_scheduler_nid_list($action) {
  $nids = array();

  foreach (module_implements('scheduler_nid_list') as $module) {
    $function = $module . '_scheduler_nid_list';
    $nids = array_merge($nids, $function($action));
  }

  return $nids;
}

/**
 * Run the lightweight cron.
 *
 * The Scheduler part of the processing performed here is the same as in the
 * normal Drupal cron run. The difference is that only scheduler_cron() is
 * executed, no other modules hook_cron() functions are called.
 *
 * This function is called from the external crontab job via url /scheduler/cron
 * or it can be run interactively from the Scheduler configuration page at
 * /admin/config/content/scheduler/cron.
 */
function _scheduler_run_cron() {
  $log = variable_get('scheduler_lightweight_log', 1);
  if ($log) {
    watchdog('scheduler', 'Lightweight cron run activated', array(), WATCHDOG_NOTICE);
  }
  scheduler_cron();
  if (ob_get_level() > 0) {
    $handlers = ob_list_handlers();
    if (isset($handlers[0]) && $handlers[0] == 'default output handler') {
      ob_clean();
    }
  }
  if ($log) {
    watchdog('scheduler', 'Lightweight cron run completed', array(), WATCHDOG_NOTICE, l(t('settings'), 'admin/config/content/scheduler/cron'));
  }

  $menu_item = menu_get_item();
  if ($menu_item['path'] == 'admin/config/content/scheduler/cron') {
    // This cron run has been initiated manually from the configuration form.
    // Give a message and return something so that an output page is created.
    // No output should be returned if running from a crontab job.
    if (module_exists('dblog')) {
      drupal_set_message(t('Lightweight cron run completed - see <a href="@url">log</a> for details.', array('@url' => url('admin/reports/dblog'))));
    }
    else {
      drupal_set_message(t('Lightweight cron run completed.'));
    }
    return ' ';
  }
  // drupal_exit() is the proper controlled way to terminate the request, as
  // this will invoke all implementations of hook_exit().
  drupal_exit();
}
