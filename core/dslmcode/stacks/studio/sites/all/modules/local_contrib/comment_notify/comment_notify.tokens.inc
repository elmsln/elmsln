<?php

/**
 * @file
 * Builds placeholder replacement tokens for comment_notify.module.
 */

/**
 * Implements hook_token_info().
 */
function comment_notify_token_info() {
  // Comment tokens.
  $info['tokens']['comment']['unsubscribe-url'] = array(
    'name' => t('Unsubscribe URL'),
    'description' => t('The URL to disable notifications for the comment.'),
    'type' => 'url',
  );

  // Comment subscriber token type (extends the comment token type).
  $info['types']['comment-subscribed'] = array(
    'name' => t('Subscribed comment'),
    'description' => t('Tokens related to a comment that is subscribed to new comments.'),
    'type' => 'comment',
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function comment_notify_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);
  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }
  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'comment' && !empty($data['comment'])) {
    $comment = $data['comment'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'unsubscribe-url':
          if ($unsubscribe_url = comment_notify_get_unsubscribe_url($comment)) {
            $replacements[$original] = url($unsubscribe_url, $url_options);
          }
          break;
      }
    }

    // [comment:unsubscribe-url:*] chained token replacements.
    if (($unsubscribe_url_tokens = token_find_with_prefix($tokens, 'unsubscribe-url')) && $unsubscribe_url = comment_notify_get_unsubscribe_url($comment)) {
      $replacements += token_generate('url', $unsubscribe_url_tokens, array('path' => $unsubscribe_url), $options);
    }
  }

  // Comment subscriber tokens (pass through to comment token replacement).
  if ($type == 'comment-subscribed' && !empty($data['comment-subscribed'])) {
    $replacements += token_generate('comment', $tokens, array('comment' => $data['comment-subscribed']), $options);
  }

  return $replacements;
}
