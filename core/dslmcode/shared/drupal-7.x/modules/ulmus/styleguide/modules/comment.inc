<?php

/**
 * Implements hook_styleguide().
 */
function comment_styleguide() {
  global $conf, $user;
  $user_register = $conf['user_register'];
  $account = clone $user;
  $user->uid = 0;
  $conf['comment_form_location_-styleguide-'] = COMMENT_FORM_SEPARATE_PAGE;
  $conf['user_register'] = TRUE;

  $authenticated_post_comments = &drupal_static('theme_comment_post_forbidden', NULL);
  $authenticated_post_comments = TRUE;
  $items['comment_post_forbidden'] = array(
    'title' => t('Comment post forbidden'),
    'content' => theme('comment_post_forbidden', array('node' => (object) array('nid' => 0, 'type' => '-styleguide-'))),
    'group' => t('Comment'),
  );
  $user = $account;
  $conf['user_register'] = $user_register;

  $name = styleguide_word(2);
  $render = array(
    '#theme' => 'comment',
    '#comment' => (object) array(
      'cid' => 0,
      'pid' => 0,
      'nid' => 1,
      'uid' => 0,
      'subject' => 'foo bar',
      'hostname' => '::1',
      'created' => time(),
      'changed' => time(),
      'status' => 1,
      'thread' => '01/',
      'name' => $name,
      'mail' => '',
      'homepage' => 'http://drupal.org/project/styleguide',
      'language' => 'und',
      'node_type' => 'comment_node_styleguide',
      'registered_name' => '',
      'u_uid' => 0,
      'signature' => '',
      'signature_format' => NULL,
      'picture' => 0,
      'new' => 0,
    ),
    '#node' => (object) array('nid' => 1, 'type' => 'styleguide'),
  );
  $render['body'] = array('#markup' => styleguide_paragraph(2));
  $items['comment'] = array(
    'title' => t('Comment'),
    'content' => drupal_render($render),
    'group' => t('Comment'),
  );

  return $items;
}
