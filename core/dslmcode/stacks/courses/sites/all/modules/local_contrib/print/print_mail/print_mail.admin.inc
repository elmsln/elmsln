<?php

/**
 * @file
 * Contains the administrative functions of the send by email module.
 *
 * This file is included by the send by email module, and includes the
 * settings form.
 *
 * @ingroup print
 */

// Include MIME library, if available.
@include_once 'Mail/mime.php';

/**
 * Form constructor for the send by email module settings form.
 *
 * @ingroup forms
 */
function print_mail_settings() {
  $link = print_mail_print_link();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Send by email options'),
  );

  $form['settings']['print_mail_hourly_threshold'] = array(
    '#type' => 'select',
    '#title' => t('Hourly threshold'),
    '#default_value' => variable_get('print_mail_hourly_threshold', PRINT_MAIL_HOURLY_THRESHOLD),
    '#options' => drupal_map_assoc(
      array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50)
    ),
    '#description' => t('The maximum number of emails a user can send per hour.'),
  );

  $form['settings']['print_mail_use_reply_to'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Reply-To header'),
    '#default_value' => variable_get('print_mail_use_reply_to', PRINT_MAIL_USE_REPLY_TO),
    '#description' => t("When enabled, any email sent will use the provided user and username in the 'Reply-To' header, with the site's email address used in the 'From' header (configured in !link). Enabling this helps in preventing email being flagged as spam.", array('!link' => l(t('Site information'), 'admin/config/system/site-information'))),
  );

  $form['settings']['print_mail_teaser_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send only the teaser'),
    '#default_value' => variable_get('print_mail_teaser_default', PRINT_MAIL_TEASER_DEFAULT_DEFAULT),
    '#description' => t("If selected, the default choice will be to send only the node's teaser instead of the full content."),
  );

  $form['settings']['print_mail_user_recipients'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable user list recipients'),
    '#default_value' => variable_get('print_mail_user_recipients', PRINT_MAIL_USER_RECIPIENTS_DEFAULT),
    '#description' => t("If selected, a user list will be included as possible email recipients."),
  );

  $form['settings']['print_mail_teaser_choice'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable teaser/full mode choice'),
    '#default_value' => variable_get('print_mail_teaser_choice', PRINT_MAIL_TEASER_CHOICE_DEFAULT),
    '#description' => t('If checked, the user will be able to choose between sending the full content or only the teaser at send time.'),
  );

  $form['settings']['print_mail_send_option_default'] = array(
    '#type' => 'select',
    '#title' => t('Default email sending format'),
    '#default_value' => variable_get('print_mail_send_option_default', PRINT_MAIL_SEND_OPTION_DEFAULT),
    '#options' => array(
      'sendlink' => t('Link'),
      'sendpage' => t('Inline HTML'),
    ),
  );
  if (class_exists('Mail_mime')) {
    $form['settings']['print_mail_send_option_default']['#options']['inline-attachment'] = t('Inline HTML with Attachment');
    $form['settings']['print_mail_send_option_default']['#options']['plain-attachment'] = t('Plain Text with Attachment');
  }

  $form['settings']['print_mail_job_queue'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send emails using queue'),
    '#default_value' => variable_get('print_mail_job_queue', PRINT_MAIL_JOB_QUEUE_DEFAULT),
    '#description' => t("Selecting this option, email delivery will be performed by the system queue during each cron run. Leaving this unselected, the email will be sent immediately, but the site will take slightly longer to reply to the user."),
  );

  $form['settings']['print_mail_display_sys_urllist'] = array(
    '#type' => 'checkbox',
    '#title' => t('Printer-friendly URLs list in system pages'),
    '#default_value' => variable_get('print_mail_display_sys_urllist', PRINT_TYPE_SYS_URLLIST_DEFAULT),
    '#description' => t('Enabling this option will display a list of printer-friendly destination URLs at the bottom of the page.'),
  );

  $form['settings']['link_text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom link text'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['settings']['link_text']['print_mail_link_text_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable custom link text'),
    '#default_value' => variable_get('print_mail_link_text_enabled', PRINT_TYPE_LINK_TEXT_ENABLED_DEFAULT),
  );
  $form['settings']['link_text']['print_mail_link_text'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('print_mail_link_text', $link['text']),
    '#description' => t('Text used in the link to the send by email form.'),
  );

  return system_settings_form($form);
}
