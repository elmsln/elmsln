<?php

/**
 * @file
 * Migration support for the Comment Notify module.
 */

/**
 * Field handler.
 */
class CommentNotifyMigrationHandler extends MigrateDestinationHandler {
  public function __construct() {
    $this->registerTypes(array('comment'));
  }

  /**
   * Make the destination field visible.
   */
  public function fields() {
    return array(
      'notify' => t('Comment Notify: Whether to send notifications for this comment'),
      'notified' => t('Comment Notify: Whether notifications have been sent for this comment'),
      'notify_hash' => t('Comment Notify: Hash representing this notification'),
    );
  }

  /**
   * Implements MigrateDestinationHandler::prepare().
   *
   * @param $comment
   *  The comment object being prepared for saving.
   * @param $row
   *  Raw source data for the migration - ignored.
   */
  public function prepare($comment, $row) {
    // By default, set notifications off
    if (!isset($comment->notify)) {
      $comment->notify = 0;
    }
    if (!isset($comment->notify_type)) {
      $comment->notify_type = 1;
    }
  }

  /**
   * Implements MigrateDestinationHandler::complete().
   *
   * @param $comment
   *  The comment object taht was just saved.
   * @param $row
   *  Raw source data for the migration - ignored.
   */
  public function complete($comment, $row) {
    if (!isset($comment->notified) || $comment->notified) {
      comment_notify_mark_comment_as_notified($comment);
    }
  }
}

/*
 * Implementats hook_migrate_api().
 */
function comment_notify_migrate_api() {
  $api = array(
    'api' => 2,
  );
  return $api;
}
