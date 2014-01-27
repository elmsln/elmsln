<?php

/**
 * @file
 * Displays and processes the mail send form.
 *
 * This file is included by the print_mail module and includes the
 * mail form display, validation and submit hooks.
 *
 * @ingroup print
 */

require_once(DRUPAL_ROOT . '/' . drupal_get_path('module', 'print') . '/print.pages.inc');

// Include MIME library
@include_once('Mail/mime.php');

/**
 * Menu callback for the send by email form.
 *
 * @ingroup forms
 */
function print_mail_form($form, &$form_state) {
  global $user;

  // Remove the printmail/ prefix
  $path_arr = explode('/', $_GET['q']);
  unset($path_arr[0]);
  $path = filter_xss(implode('/', $path_arr));
  if (empty($path)) {
    // If no path was provided, let's try to generate a page for the referer
    global $base_url;

    $ref = $_SERVER['HTTP_REFERER'];
    $path = preg_replace("!^$base_url/!", '', $ref);
    if (($path === $ref) || empty($path)) {
      $path = variable_get('site_frontpage', 'node');
    }
    drupal_goto(PRINTMAIL_PATH . '/' . $path);
  }
  elseif (ctype_digit($path_arr[1])) {
    if (drupal_lookup_path('source', $path)) {
      // This is a numeric alias
      $path = drupal_get_normal_path($path);
    }
    else {
      // normal nid
      $path = 'node/' . $path;
    }
  }
  else {
    $path = drupal_get_normal_path($path);
  }

  // Handle the query
  $query = $_GET;
  unset($query['q']);

  $print_mail_hourly_threshold = variable_get('print_mail_hourly_threshold', PRINT_MAIL_HOURLY_THRESHOLD);

  if ((!user_access('send unlimited emails')) && (!flood_is_allowed('print_mail', $print_mail_hourly_threshold))) {
    $form['flood'] = array(
      '#type' => 'markup',
      '#markup' => '<p>' . format_plural($print_mail_hourly_threshold, 'You cannot send more than 1 message per hour. Please try again later.', 'You cannot send more than @count messages per hour. Please try again later.') . '</p>',
    );
    return $form;
  }

  $print_mail_teaser_default = variable_get('print_mail_teaser_default', PRINT_MAIL_TEASER_DEFAULT_DEFAULT);
  $print_mail_teaser_choice = variable_get('print_mail_teaser_choice', PRINT_MAIL_TEASER_CHOICE_DEFAULT);
  $form = array();

  $cid = isset($_GET['comment']) ? (int)$_GET['comment'] : NULL;
  $title = _print_get_title($path);

  if (count($form_state['input']) == 0) {
    $nodepath = drupal_get_normal_path($path);
    db_merge('print_mail_page_counter')
      ->key(array('path' => $nodepath))
      ->fields(array(
          'totalcount' => 1,
          'timestamp' => REQUEST_TIME,
      ))
      ->expression('totalcount', 'totalcount + 1')
      ->execute();
  }

  $form['path'] = array('#type' => 'value', '#value' => $path);
  $form['query'] = array('#type' => 'value', '#value' => $query);
  $form['cid'] =  array('#type' => 'value', '#value' => $cid);
  $form['title'] = array('#type' => 'value', '#value' => $title);

  $form['fld_from_addr'] = array(
    '#type' => 'textfield',
    '#title' => t('Your email'),
    '#size' => 62,
    '#required' => TRUE,
  );
  $form['fld_from_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Your name'),
    '#size' => 62,
  );
  $form['txt_to_addrs'] = array(
    '#type' => 'textarea',
    '#title' => t('Send to'),
    '#rows' => 3,
    '#resizable' => FALSE,
    '#description' => t('Enter multiple addresses separated by commas and/or different lines.'),
    '#required' => TRUE,
  );
  $form['fld_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#size' => 62,
    '#required' => TRUE,
  );
  if (!empty($title)) {
    // To prevent useless translation strings, try to translate only node titles
    if (drupal_substr($path, 0, 5) == 'node/') {
      $title = t($title);
    }

    $form['fld_title'] = array(
      '#type' => 'item',
      '#title' => t('Page to be sent'),
      '#markup' => l($title, $path, array('attributes' => array('title' => t('View page')), 'query' => $query)),
    );
  }
  $form['txt_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Your message'),
    '#rows' => 6,
    '#required' => TRUE,
  );

  if ($print_mail_teaser_choice) {
    $form['chk_teaser'] = array(
      '#type' => 'checkbox',
      '#title' => t('Send only the teaser'),
      '#default_value' => $print_mail_teaser_default,
    );
  }
  else {
    $form['chk_teaser'] = array('#type' => 'value', '#value' => $print_mail_teaser_default);
  }

  $form['btn_submit'] = array(
    '#name' => 'submit',
    '#type' => 'submit',
    '#value' => t('Send email'),
  );
  $form['btn_clear'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="reset" name="clear" id="edit-btn-clear" value="' . t('Clear form') . '" class="form-submit" />',
  );
  $form['btn_cancel'] = array(
    '#name' => 'cancel',
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );

  if ($user->uid != 0) {
    $user_name = check_plain(strip_tags(theme('username', array('account' => $user))));
    $form['fld_from_addr']['#default_value'] = $user->mail;
    $form['fld_from_addr']['#disabled'] = TRUE;
    $form['fld_from_addr']['#value'] = $user->mail;
    $form['fld_from_name']['#default_value'] = $user_name;
  }
  else {
    $user_name = t('Someone');
  }
  $site_name = variable_get('site_name', t('an interesting site'));
  $print_mail_text_subject = filter_xss(variable_get('print_mail_text_subject', t('!user has sent you a message from !site')));
  $form['fld_subject']['#default_value'] = t($print_mail_text_subject, array('!user' => $user_name, '!site' => $site_name, '!title' => $title));
  $print_mail_text_content = filter_xss(variable_get('print_mail_text_content', ''));
  $form['txt_message']['#default_value'] = t($print_mail_text_content);

  return $form;
}

/**
 * Theme function for the send by-email form submission.
 *
 * Adds a class to the form labels. This class is used to place the label on
 * the left of the input fields.
 *
 * @ingroup forms
 */
function theme_print_mail_form($variables) {
  $form = $variables['form'];

  drupal_add_css(drupal_get_path('module', 'print') . '/css/printlinks.css');
  $content = '';
  foreach (element_children($form) as $key) {
    $tmp = drupal_render($form[$key]);
    switch ($key) {
      case 'fld_from_addr':
      case 'fld_from_name':
      case 'txt_to_addrs':
      case 'fld_subject':
      case 'fld_title':
        $tmp = str_replace('<label', '<label class ="printmail-label"', $tmp);
        break;
    }
    $content .= $tmp;
  }
  return $content;
}

/**
 * Validate the send by-email form submission.
 *
 * @ingroup forms
 */
function print_mail_form_validate($form, &$form_state) {
  if (array_key_exists('cancel', $form_state['input'])) {
    form_set_error(NULL, '', TRUE);
    drupal_get_messages('error');

    drupal_goto(preg_replace('!^book/export/html/!', 'node/', $form_state['values']['path']), array('query' => $form_state['values']['query']));
    return;
  }
  $from_addr = trim($form_state['values']['fld_from_addr']);
  $test = user_validate_mail($from_addr);
  if ($test) {
    form_set_error('fld_from_addr', $test);
  }

  // All new-lines are replaced by commas
  $to_addrs = preg_replace('![\r|\n|,]+!', ',', trim($form_state['values']['txt_to_addrs']));
  // Create an array from the string
  $to_array = explode(',', $to_addrs);
  // Verify each element of the array
  foreach ($to_array as $key => $address) {
    $address = trim($address);
    if (preg_match('/(.*?) <(.*)>/s', $address, $matches)) {
      // Address is of the type User Name <user@domain.tld>
      $test = user_validate_mail($matches[2]);
      $to_array[$key] = trim($matches[1]) . ' <' . $matches[2] . '>';
    }
    else {
      // Address must be user@domain.tld
      $test = user_validate_mail($address);
    }
    if ($test) {
      form_set_error('txt_to_addrs', $test);
    }
  }

  $print_mail_hourly_threshold = variable_get('print_mail_hourly_threshold', PRINT_MAIL_HOURLY_THRESHOLD);

  if ((!user_access('send unlimited emails')) && (!flood_is_allowed('print_mail', $print_mail_hourly_threshold - count($to_array) + 1))) {
    form_set_error('txt_to_addrs',  t('You cannot send more than %number messages per hour. Please reduce the number of recipients.', array('%number' => $print_mail_hourly_threshold)));
  }

  // In all fields, prevent insertion of custom headers
  foreach ($form_state['values'] as $key => $string) {
    if ( (drupal_substr($key, 0, 4) == 'fld_') && ((strpos($string, "\n") !== FALSE) || (strpos($string, "\r") !== FALSE)) ) {
      form_set_error($key, 'Found invalid character');
    }
  }

  $form_state['values']['fld_from_addr'] = $from_addr;
  $form_state['values']['fld_from_name'] = trim($form_state['values']['fld_from_name']);
  // Re-create the string from the re-organized array
  $form_state['values']['txt_to_addrs'] = implode(', ', $to_array);
}

/**
 * Process the send by-email form submission.
 *
 * @ingroup forms
 */
function print_mail_form_submit($form, &$form_state) {
  if (!array_key_exists('cancel', $form_state['values'])) {
    $cid = isset($form_state['values']['cid']) ? $form_state['values']['cid'] : NULL;
    $print_mail_text_message = filter_xss_admin(variable_get('print_mail_text_message', t('Message from sender')));
    $sender_message = $print_mail_text_message . ':<br /><br /><em>' . nl2br(check_plain($form_state['values']['txt_message'])) . '</em>';

    $print = print_controller($form_state['values']['path'], $form_state['values']['query'], $cid, PRINT_MAIL_FORMAT, $form_state['values']['chk_teaser'], $sender_message);

    if ($print !== FALSE) {
      $print_mail_send_option_default = variable_get('print_mail_send_option_default', PRINT_MAIL_SEND_OPTION_DEFAULT);

      $params = array();
      $params['subject'] = $form_state['values']['fld_subject'];
      $params['message'] = $sender_message;
      $params['link'] = $print['url'];
      $params['title'] = $form_state['values']['title'];

      // If a name is provided, make From: in the format Common Name <address>
      if (!empty($form_state['values']['fld_from_name'])) {
        $from = '"' . mime_header_encode($form_state['values']['fld_from_name']) . '" <' . $form_state['values']['fld_from_addr'] . '>';
      }
      else {
        $from = $form_state['values']['fld_from_addr'];
      }

      // If using reply-to, move the From: info to the params array, so that it is passed to hook_mail later
      if (variable_get('print_mail_use_reply_to', PRINT_MAIL_USE_REPLY_TO)) {
        $params['from'] = $from;
        $from = NULL;
      }

      // Spaces in img URLs must be replaced with %20
      $pattern = '!<(img\s[^>]*?)>!is';
      $print['content'] = preg_replace_callback($pattern, '_print_replace_spaces', $print['content']);

      $node = $print['node'];
      $params['body'] = theme('print', array('print' => $print, 'type' => PRINT_MAIL_FORMAT, 'node' => $node));

      // Img elements must be set to absolute
      $pattern = '!<(img\s[^>]*?)>!is';
      $params['body'] = preg_replace_callback($pattern, '_print_rewrite_urls', $params['body']);

      // Convert the a href elements, to make sure no relative links remain
      $pattern = '!<(a\s[^>]*?)>!is';
      $params['body'] = preg_replace_callback($pattern, '_print_rewrite_urls', $params['body']);

      $ok = FALSE;
      $use_job_queue = variable_get('print_mail_job_queue', PRINT_MAIL_JOB_QUEUE_DEFAULT);
      if ($use_job_queue) {
        $queue = DrupalQueue::get('print_mail_send');
      }

      $addresses = explode(', ', $form_state['values']['txt_to_addrs']);
      foreach ($addresses as $to) {
        if ($use_job_queue) {
          // Use job queue to send mails during cron runs
          $queue->createItem(array('module' => 'print_mail', 'key' => $print_mail_send_option_default, 'to' => $to, 'language' => language_default(), 'params' => $params, 'from' => $from));
        }
        else {
          // Send mail immediately using Drupal's mail handler
          $ret = drupal_mail('print_mail', $print_mail_send_option_default, $to, language_default(), $params, $from);
        }
        if ($use_job_queue || $ret['result']) {
          flood_register_event('print_mail');
          $ok = TRUE;
        }
      }
      if ($ok) {
        $query = empty($form_state['values']['query']) ? '' : '?' . rawurldecode(drupal_http_build_query($form_state['values']['query']));
        watchdog('print_mail', '%name [%from] sent %page to [%to]', array('%name' => $form_state['values']['fld_from_name'], '%from' => $form_state['values']['fld_from_addr'], '%page' => $form_state['values']['path'] . $query, '%to' => $form_state['values']['txt_to_addrs']));
        $site_name = variable_get('site_name', t('us'));
        $print_mail_text_confirmation = variable_get('print_mail_text_confirmation', t('Thank you for spreading the word about !site.'));
        drupal_set_message(check_plain(t($print_mail_text_confirmation, array('!site' => $site_name))));

        $nodepath = drupal_get_normal_path($form_state['values']['path']);
        db_update('print_mail_page_counter')
          ->fields(array(
              'sentcount' => 1,
              'sent_timestamp' => REQUEST_TIME,
          ))
          ->condition('path', $nodepath, '=')
          ->expression('sentcount', 'sentcount + :inc', array(':inc' => count($addresses)))
          ->execute();
      }
    }
  }

  $form_state['redirect'] = array(preg_replace('!^book/export/html/!', 'node/', $form_state['values']['path']), array('query' => $form_state['values']['query']));
}
