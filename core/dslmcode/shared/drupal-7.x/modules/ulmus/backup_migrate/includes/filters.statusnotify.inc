<?php


/**
 * @file
 * A filter for compressing bckups with zip, gz bzip etc.
 */

/**
 * A filter to send a notification email on success or failure of backup.
 *
 * @ingroup backup_migrate_filters
 */
class backup_migrate_filter_statusnotify extends backup_migrate_filter {
  
  /**
   * Get the default backup settings for this filter.
   */
  function backup_settings_default() {
    return array(
      'notify_success_enable' => FALSE,
      'notify_failure_enable' => FALSE,
      'notify_success_email' => variable_get('site_mail', ''),
      'notify_failure_email' => variable_get('site_mail', ''),
    );
  }

  /**
   * Get the form for the settings for this filter.
   */
  function backup_settings_form($settings) {
    $form = array();
    $form['advanced']['notify_success_enable'] = array(
      "#type" => 'checkbox',
      "#title" => t("Send an email if backup succeeds"),
      "#default_value" => @$settings['notify_success_enable'],
    );
    $form['advanced']['notify_success_email'] = array(
      "#type" => "textfield",
      "#title" => t("Email Address for Success Notices"),
      "#default_value" => @$settings['notify_success_email'],
    );
    $form['advanced']['notify_failure_enable'] = array(
      "#type" => 'checkbox',
      "#title" => t("Send an email if backup fails"),
      "#default_value" => @$settings['notify_failure_enable'],
    );
    $form['advanced']['notify_failure_email'] = array(
      "#type" => "textfield",
      "#title" => t("Email Address for Failure Notices"),
      "#default_value" => @$settings['notify_failure_email'],
    );
    return $form;
  }

  /**
   * Send the success email.
   */
  function backup_succeed($settings) {
    if (@$settings->filters['notify_success_enable'] && $to = @$settings->filters['notify_success_email']) {

      $params = array(
        'messages' => $this->get_messages(),
      );

      // Using the default language since this is not specific to a user.
      $language = language_default();

      drupal_mail('backup_migrate', 'backup_succeed', $settings->filters['notify_success_email'], $language, $params);
    }
  }

  /**
   * Send the failure email.
   */
  function backup_fail($settings) {
    if (@$settings->filters['notify_failure_enable'] && $to = @$settings->filters['notify_failure_email']) {

      $params = array(
        'messages' => $this->get_messages(),
      );

      // Using the default language since this is not specific to a user.
      $language = language_default();

      drupal_mail('backup_migrate', 'backup_fail', $settings->filters['notify_failure_email'], $language, $params);
    }
  }

  /**
   * Render the messages and errors for the email.
   */
  function get_messages() {
    $out = "";
    $messages = _backup_migrate_messages();
    foreach ($messages as $message) {
      $out .= strip_tags(t($message['message'], $message['replace'])) . "\n";
    }
    return $out;
  }
}

