<?php

/**
 * @file
 *
 * Contains functions which utilize the database and other internal helpers.
 */

/**
 * Get the notification preferences for a specific user.
 *
 * @param integer $uid
 * @return mixed
 *  StdClass if found, else NULL
 */
function comment_notify_get_user_notification_setting($uid) {
  $users = &drupal_static(__FUNCTION__);
  if (!isset($users[$uid])) {
    if (is_null($uid)) {
      throw new Exception('Cannot get user preference, uid missing');
    }
    // Handle anonymous users with defaults.
    if ($uid == 0) {
      $users[0] = new stdClass();
      $users[0]->comment_notify = comment_notify_variable_registry_get('default_registered_mailalert');
      $users[0]->node_notify = comment_notify_variable_registry_get('node_notify_default_mailalert');
    }
    else {
      $setting = db_select('comment_notify_user_settings', 'cnus')
        ->fields('cnus')
        ->condition('uid', $uid)
        ->execute()
        ->fetchObject();

      if (!$setting) {
        return NULL;
      }
      else {
        $users[$uid] = $setting;
      }
    }
  }
  return $users[$uid];
}

function comment_notify_get_default_notification_setting() {
  return (object) array(
    'comment_notify' => comment_notify_variable_registry_get('default_registered_mailalert'),
    'node_notify' => comment_notify_variable_registry_get('node_notify_default_mailalert')
  );
}

/**
 * Remove comment notification preferences for a user.
 *
 * @param integer $uid
 * @return boolean
 */
function comment_notify_delete_user_notification_setting($uid) {
  return (bool)db_delete('comment_notify_user_settings')
    ->condition('uid', $uid)
    ->execute();
}

/**
 * Get a user's default preference for comment notification.
 *
 * @param integer $uid
 * @return integer
 */
function comment_notify_get_user_comment_notify_preference($uid) {
  $setting = comment_notify_get_user_notification_setting($uid);
  if (!$setting) {
    $setting = comment_notify_get_default_notification_setting();
  }
  return $setting->comment_notify;
}

/**
 * Get a user's default preference for node update notification.
 *
 * This is notification on nodes where the user is the author.
 *
 * @param integer $uid
 * @return integer
 */
function comment_notify_get_user_node_notify_preference($uid) {
  $setting = comment_notify_get_user_notification_setting($uid);
  if (!$setting) {
    $setting = comment_notify_get_default_notification_setting();
  }
  return $setting->node_notify;
}

/**
 * Sets the notification preferences for a specific user.
 *
 * @param integer $uid
 * @param integer $node_notification
 * @param integer $comment_notification
 * @return boolean
 */
function comment_notify_set_user_notification_setting($uid, $node_notification = NULL, $comment_notification = NULL) {
  if (!$uid) {
    throw new Exception('Cannot set user preference, uid missing');
  }
  $fields = array('uid' => $uid);

  if (!is_null($node_notification)) {
    $fields['node_notify'] = $node_notification;
  }
  if (!is_null($comment_notification)) {
    $fields['comment_notify'] = $comment_notification;
  }
  if (comment_notify_get_user_notification_setting($uid)) {
    $query = db_update('comment_notify_user_settings');
    $query->condition('uid', $uid);
  }
  else {
    $query = db_insert('comment_notify_user_settings');
  }
  return (bool)$query
    ->fields($fields)
    ->execute();
}

/**
 * Add a notification against a comment.
 *
 * @param integer $cid
 * @param integer $notify
 * @param string $notify_hash
 * @return boolean
 */
function comment_notify_add_notification($cid, $notify, $notify_hash) {
  return (bool)db_insert('comment_notify')
    ->fields(array(
      'cid' => $cid,
      'notify' => $notify === NULL ? 0 : $notify,
      'notify_hash' => $notify_hash,
    ))
    ->execute();
}

/**
 * Remove all the notifications linked with a comment
 *
 * @param integer $cid
 * @return boolean
 */
function comment_notify_remove_all_notifications($cid) {
  return (bool)db_delete('comment_notify')
    ->condition('cid', $cid)
    ->execute();
}

/**
 * Updated a notification with a different notification type
 *
 * @param integer $cid
 * @param integer $notify
 * @return boolean
 */
function comment_notify_update_notification($cid, $notify) {
  return (bool)db_update('comment_notify')
    ->fields(array(
      'notify' => $notify === NULL ? 0 : $notify,
    ))
    ->condition('cid', $cid)
    ->execute();
}

/**
 * Get the type of notification for a comment notification record.
 *
 * @param integer $cid
 * @return integer
 */
function comment_notify_get_notification_type($cid) {
  return db_select('comment_notify', 'cn')
    ->fields('cn', array('notify'))
    ->condition('cid', $cid)
    ->execute()
    ->fetchField();
}

/**
 * Get a list of mails which need to be contacted for a node.
 *
 * @param integer $nid
 * @return QueryStatement
 */
function comment_notify_get_watchers($nid) {
  $cids = db_query("SELECT c.cid FROM {comment} c INNER JOIN {comment_notify} cn ON c.cid = cn.cid LEFT JOIN {users} u ON c.uid = u.uid WHERE c.nid = :nid AND c.status = :status AND cn.notify <> :notify AND (u.uid = 0 OR u.status = 1)", array(
    ':nid' => $nid,
    ':status' => COMMENT_PUBLISHED,
    ':notify' => COMMENT_NOTIFY_DISABLED,
  ))->fetchCol();
  return comment_load_multiple($cids);
}

/**
 * Record that the owner of a comment notification request has already been notified.
 *
 * @param integer $cid
 * @return boolean
 */
function comment_notify_mark_comment_as_notified($comment) {
  // First, mark the passed comment (an object, so passed by reference).
  $comment->notified = 1;

  // Next, store this fact in the DB as well.
  return (bool)db_update('comment_notify')
    ->fields(array(
      'notified' => 1,
    ))
    ->condition('cid', $comment->cid)
    ->execute();
}

/**
 * Unsubscribe all comment notification requests associated with an email.
 *
 * If the email belongs to a user, it will unsubscribe all of their Comment Notify records.
 * If it does not, then it will unsubscribe all anonymous users.
 *
 * @param string $mail
 * @return boolean
 */
function comment_notify_unsubscribe_by_email($mail) {
  $update_query = db_update('comment_notify');
  $update_query->fields(array('notify' => 0));

  $comment_query = db_select('comment', 'c');
  $comment_query->fields('c', array('cid'));

  $uid = db_select('users', 'u')
    ->fields('u', array('uid'))
    ->condition('mail', $mail)
    ->execute()
    ->fetchField();
  if ($uid) {
    $comment_query->condition('uid', $uid);
  }
  else {
    $comment_query->condition('mail', $mail);
  }
  $update_query->condition('cid', $comment_query, 'IN');

  return (bool)$update_query->execute();
}

/**
 * Unsubscribe comment notification requests associated with a hash.
 *
 * This is used in the unsubscribe link.
 *
 * @param string $hash
 * @return boolean
 */
function comment_notify_unsubscribe_by_hash($hash) {
  $notification = db_select('comment_notify')
      ->fields('comment_notify')
      ->condition('notify_hash', $hash)
      ->execute()->fetchAll();

  // If this notification is at the node level, delete all notifications for this node.
  if (COMMENT_NOTIFY_NODE == $notification[0]->notify) {
    // Get all this user's comments for this node.
    $result = db_query("SELECT c.cid
      FROM {comment} c, (
        SELECT oc.nid, oc.uid
        FROM {comment} AS oc, {comment_notify} AS ocn
        WHERE oc.cid = ocn.cid
        AND ocn.notify_hash = :hash
      ) AS o
      WHERE o.nid = c.nid
      AND o.uid = c.uid", array(':hash' => $hash));

    $cids = $result->fetchCol();

    // Update all comment notifications to be disabled.
    return (bool)db_update('comment_notify')
      ->fields(array(
        'notify' => 0,
      ))
      ->condition('cid', $cids, 'IN')
      ->execute();
  }
  else {
   // Update this notification to be disabled.
   return (bool)db_update('comment_notify')
     ->fields(array(
       'notify' => 0,
     ))
    ->condition('notify_hash', $hash)
    ->execute();
  }
}

/**
 * Helper function to centralize variable management and defaults.
 *
 * All variables fall under the "comment_notify" psuedo namespace.  This ensures
 * consistancy, and eliminates some verbosity in the calling code.  In addition
 * by storing all of the variables in one place, we avoid repeating duplicate
 * defaults which are harder to maintain.
 *
 * @param string $name
 * @return mixed
 */
function comment_notify_variable_registry_get($name) {
  $variables = array();
  $variables['author_subject'] = t('[site:name] :: new comment for your post.');
  $variables['available_alerts'] = array(COMMENT_NOTIFY_NODE, COMMENT_NOTIFY_COMMENT);
  $variables['default_anon_mailalert'] = COMMENT_NOTIFY_NODE;
  $variables['node_notify_default_mailtext'] = AUTHOR_MAILTEXT;
  $variables['default_registered_mailalert'] = COMMENT_NOTIFY_DISABLED;
  $variables['node_notify_default_mailalert'] = 0;
  $variables['watcher_subject'] = '[site:name] :: new comment on [comment:node:title]';
  $variables['comment_notify_default_mailtext'] = DEFAULT_MAILTEXT;
  $variables['node_types'] = array('article' => 'article');

  // Errors
  $variables['error_anonymous_email_missing'] = 'If you want to subscribe to comments you must supply a valid e-mail address.';
  return variable_get("comment_notify_" . $name, $variables[$name]);
}

/**
 * Helper function to centralize setting variables.
 *
 * @param string $name
 * @param mixed $value
 * @return boolean
 */
function comment_notify_variable_registry_set($name, $value) {
  return variable_set("comment_notify_" . $name, $value);
}
