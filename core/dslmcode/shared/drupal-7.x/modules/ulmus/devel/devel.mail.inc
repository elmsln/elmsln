<?php

/**
 * @file
 * MailSystemInterface for logging mails to the filesystem.
 *
 * To enable, save a variable in settings.php (or otherwise) whose value
 * can be as simple as:
 *
 * $conf['mail_system'] = array(
 *   'default-system' => 'DevelMailLog',
 *);
 *
 * Saves to temporary://devel-mails dir by default. Can be changed using
 * 'devel_debug_mail_directory' variable. Filename pattern controlled by
 * 'devel_debug_mail_file_format' variable.
 *
 */

/**
 * Logs mail messages to the filesystem.
 */
class DevelMailLog extends DefaultMailSystem {

  /**
   * Converts a message array to a string.
   *
   * @param $message
   *   The message array containing the body and headers.
   *
   * @return
   *   The message as it will be printed in the file.
   */
  public function composeMessage($message) {
    $mimeheaders = array();
    $message['headers']['To'] = $message['to'];
    foreach ($message['headers'] as $name => $value) {
      $mimeheaders[] = $name . ': ' . mime_header_encode($value);
    }

    $line_endings = variable_get('mail_line_endings', MAIL_LINE_ENDINGS);
    $output = join($line_endings, $mimeheaders) . $line_endings;
    // 'Subject:' is a mail header and should not be translated.
    $output .= 'Subject: ' . $message['subject'] . $line_endings;
    // Blank line to separate headers from body.
    $output .= $line_endings;
    $output .= preg_replace('@\r?\n@', $line_endings, $message['body']);
    return $output;
  }

  /**
   * Gets a filename for a message using tokens.
   *
   * @param $message
   *   The message that will supply values for token replacement.
   *
   * @return
   *   The full path and filename after token replacement.
   */
  public function getFileName($message) {
    $output_directory = $this->getOutputDirectory();
    $this->makeOutputDirectory($output_directory);

    $output_file_format = variable_get('devel_debug_mail_file_format', '%to-%subject-%datetime.mail.txt');
    $tokens = array(
      '%to' => $message['to'],
      '%subject' => $message['subject'],
      '%datetime' => date('y-m-d_his'),
    );
    return $output_directory . '/' . $this->dirify(str_replace(array_keys($tokens), array_values($tokens), $output_file_format));
  }

  /**
   * Convert a string to a valid directory name.
   *
   * @return
   *   The sanitized string, replacing any characters not whitelisted with "_".
   */
  private function dirify($string) {
    return preg_replace('/[^a-zA-Z0-9_\-\.@]/', '_', $string);
  }

  /**
   * Save a mail message to a file using Drupal variables and default settings.
   *
   * @param $message
   *   A message array, as described in hook_mail_alter().
   * @return
   *   TRUE if the mail was successfully accepted, otherwise FALSE.
   *
   * @see http://php.net/manual/en/function.mail.php
   * @see drupal_mail()
   */
  public function mail(array $message) {
    $output = $this->composeMessage($message);
    $output_file = $this->getFileName($message);

    return file_put_contents($output_file, $output);
  }

  /**
   * Creates the directory to contain the message file if necessary.
   *
   * @throws Exception
   *   Exception thrown when unable to create the destination directory.
   */
  protected function makeOutputDirectory($output_directory) {
    if (!file_prepare_directory($output_directory, FILE_CREATE_DIRECTORY)) {
      throw new Exception("Unable to continue sending mail, $output_directory is not writable");
    }
  }

  /**
   * Retrieves the directory that contains message files.
   *
   * @return
   *   The path to mail messages, possibly using a file URI scheme.
   */
  public function getOutputDirectory() {
    return variable_get('devel_debug_mail_directory', 'temporary://devel-mails');
  }
}
