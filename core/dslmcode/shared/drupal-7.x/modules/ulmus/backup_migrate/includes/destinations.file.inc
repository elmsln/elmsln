<?php


/**
 * @file
 * A destination type for saving locally to the server.
 */

/**
 * A destination type for saving locally to the server.
 *
 * @ingroup backup_migrate_destinations
 */

class backup_migrate_destination_files extends backup_migrate_destination {
  var $supported_ops = array('scheduled backup', 'manual backup', 'local backup', 'restore', 'list files', 'configure', 'delete');

  function type_name() {
    return t("Server Directory");
  }

  /**
   * Get the file location.
   */
  function get_realpath() {
    return drupal_realpath($this->get_location());
  }

  /**
   * File save destination callback.
   */
  function _save_file($file, $settings) {
    if ($this->confirm_destination() && $dir = $this->get_location()) {
      $filepath = rtrim($dir, "/") ."/". $file->filename();
      // Copy the file if there are multiple destinations.
      if (count($settings->get_destinations()) > 1) {
        file_unmanaged_copy($file->filepath(), $filepath);
      }
      // Otherwise we can move it and save a delete.
      else {
        file_unmanaged_move($file->filepath(), $filepath);
      }

      // chmod, chown and chgrp the file if needed.
      if ($chmod = $this->settings('chmod')) {
        if (!@drupal_chmod($filepath, octdec($chmod))) {
          _backup_migrate_message('Unable to set the file mode for: @file', array('@file' => $filepath), 'error');
        }
      }
      if ($chgrp = $this->settings('chgrp')) {
        if (!@chgrp($filepath, $chgrp)) {
          _backup_migrate_message('Unable to set the file group for: @file', array('@file' => $filepath), 'error');
        }
      }
      return $file;
    }
  }

  /**
   * Determine if we can read the given file.
   */
  function can_read_file($file_id) {
    return $this->op('restore') && is_readable($this->get_filepath($file_id));
  }

  /**
   * File load destination callback.
   */
  function load_file($file_id) {
    $filepath = $this->get_filepath($file_id);
    if (file_exists($filepath)) {
      backup_migrate_include('files');
      return new backup_file(array('filepath' => $filepath));
    }
  }

  /**
   * Get the file object for the given file.
   */
  function get_file($file_id) {
    $files = $this->list_files();
    if (isset($files[$file_id])) {
      isset($files[$file_id]);
    }
    return NULL;
  }

  /**
   * File list destination callback.
   */
  function _list_files() {
    $files = array();
    if ($dir = $this->get_realpath()) {
      if ($handle = @opendir($dir)) {
        backup_migrate_include('files');
        while (FALSE !== ($file = readdir($handle))) {
          if (substr($file, 0, 1) !== '.') {
            $filepath = $dir ."/". $file;
            $files[$file] = new backup_file(array('filepath' => $filepath));          
          }
        }
      }
    }
    return $files;
  }

  /**
   * File delete destination callback.
   */
  function _delete_file($file_id) {
    $filepath = $this->get_filepath($file_id);
    file_unmanaged_delete($filepath);
  }

  /**
   * Get the filepath from the given file id.
   */
  function get_filepath($file_id) {
    if ($dir = $this->get_realpath()) {
      $filepath = rtrim($dir, '/') .'/'. $file_id;
      return $filepath;
    }
    return FALSE;
  }

  /**
   * Get the form for the settings for the files destination.
   */
  function edit_form() {
    $form = parent::edit_form();
    $form['location'] = array(
      "#type" => "textfield",
      "#title" => t("Directory path"),
      "#default_value" => $this->get_location(),
      "#required" => TRUE,
      "#description" => t('Enter the path to the directory to save the backups to. Use a relative path to pick a path relative to your Drupal root directory. The web server must be able to write to this path.'),
    );
    $form['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced Settings'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    if (function_exists('chmod')) {
      $form['settings']['chmod'] = array(
        '#type' => 'textfield',
        '#title' => t('Change file mode (chmod)'),
        '#size' => 5,
        '#default_value' => $this->settings('chmod'),
        '#description' => t('If you enter a value here, backup files will be chmoded with the mode you specify. Specify the mode in octal form (e.g. 644 or 0644) or leave blank to disable this feature.'),
      );
    }
    if (function_exists('chgrp')) {
      $form['settings']['chgrp'] = array(
        '#type' => 'textfield',
        '#title' => t('Change file group (chgrp)'),
        '#size' => 5,
        '#default_value' => $this->settings('chgrp'),
        '#description' => t('If you enter a value here, backup files will be chgrped to the group you specify. Leave blank to disable this feature.'),
      );
    }
    return $form;
  }

  /**
   * Validate the form for the settings for the files destination.
   */
  function edit_form_validate($form, &$form_state) {
    $values = $form_state['values'];
    if (isset($values['settings']['chmod']) && !empty($values['settings']['chmod']) && !preg_match('/0?[0-7]{3}/', $values['settings']['chmod'])) {
      form_set_error('chmod', t('You must enter a valid chmod octal value (e.g. 644 or 0644) in the change mode field, or leave it blank.'));
    }
    parent::edit_form_validate($form, $form_state);
  }

  /**
   * Submit the form for the settings for the files destination.
   */
  function edit_form_submit($form, &$form_state) {
    // Add a 0 to the start of a 3 digit file mode to make it proper PHP encoded octal.
    if (strlen($form_state['values']['settings']['chmod']) == 3) {
      $form_state['values']['settings']['chmod'] = '0' . $form_state['values']['settings']['chmod'];
    }
    parent::edit_form_submit($form, $form_state);
  }

  /**
   * Check that a destination is valid.
   */
  function confirm_destination() {
    if ($dir = $this->get_location()) {
      return $this->check_dir($dir);
    }
    return FALSE;
  }

  /**
   * Prepare the destination directory for the backups.
   */
  function check_dir($directory) {
    if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
      // Unable to create destination directory.
      _backup_migrate_message("Unable to create or write to the save directory '%directory'. Please check the file permissions of that directory and try again.", array('%directory' => $directory), "error");
      return FALSE;
    }

    // If the destination directory is within the webroot, then secure it as best we can.
    if ($this->dir_in_webroot($directory)) {
      $directory = $this->check_web_dir($directory);
    }

    return $directory;
  }

  /**
   * Check that a web accessible directory has been properly secured, othewise attempt to secure it.
   */
  function check_web_dir($directory) {
    // Check if the file has already been tested.
    if (is_file($directory .'/tested.txt')) {
      return $directory;
    }
    else {
      file_create_htaccess($directory, TRUE);
  
      // Check the user agent to make sure we're not responding to a request from drupal itself.
      // That should prevent infinite loops which could be caused by poormanscron in some circumstances.
      if (strpos($_SERVER['HTTP_USER_AGENT'], 'Drupal') !== FALSE) {
        return FALSE;
      }
  
      // Check to see if the destination is publicly accessible
      $test_contents = "this file should not be publicly accessible";
      // Create the the text.txt file if it's not already there.
      if (!is_file($directory .'/test.txt') || file_get_contents($directory .'/test.txt') != $test_contents) {
        if ($fp = fopen($directory .'/test.txt', 'w')) {
          @fputs($fp, $test_contents);
          fclose($fp);
        }
        else {
          $message = t("Security notice: Backup and Migrate was unable to write a test text file to the destination directory %directory, and is therefore unable to check the security of the backup destination. Backups to the server will be disabled until the destination becomes writable and secure.", array('%directory' => $directory));
          drupal_set_message($message, "error");
          return FALSE;
        }
      }
  
      // Attempt to read the test file via http. This may fail for other reasons,
      // so it's not a bullet-proof check.
      if ($this->test_file_readable_remotely($directory .'/test.txt', $test_contents)) {
        $message = t("Security notice: Backup and Migrate will not save backup files to the server because the destination directory is publicly accessible. If you want to save files to the server, please secure the '%directory' directory", array('%directory' => $directory));
        drupal_set_message($message, "error");
        return FALSE;
      }
      // Directory tested OK, so we mark it as tested.
      if ($fp = fopen($directory .'/tested.txt', 'w')) {
        $contents = t('The presence of this file indicates that this directory has been tested as safe to use as a destination for Backup and Migrate. If you change the permissions of this directory or change your web server settings, please delete this file so that the directory can be checked again.');
        @fputs($fp, $contents);
        fclose($fp);
      }
      return $directory;
    }
  }

  /**
   * Check if the given directory is within the webroot and is therefore web accessible.
   */
  function dir_in_webroot($directory) {
    $real_dir = drupal_realpath($directory);
    $real_root = drupal_realpath(DRUPAL_ROOT);
    if ($real_dir == $real_root || strpos($real_dir, $real_root . '/') === 0) {
      return TRUE;
    }
    return FALSE;
  }

/**
   * Check if a file can be read remotely via http.
   */
  function test_file_readable_remotely($directory, $contents) {
    $real_dir = drupal_realpath($directory);
    $real_root = drupal_realpath(DRUPAL_ROOT);
    if ($real_dir && $real_root) {
      // Get the root relative path.
      $path = substr($real_dir, strlen($real_root));

      $url = $GLOBALS['base_url'] . str_replace('\\', '/', $path);
      $result = drupal_http_request($url);
      if (!empty($result->data) && strpos($result->data, $contents) !== FALSE) {
        return TRUE;
      }
    }
    return FALSE;
  }
}

/**
 * The manual files directory.
 */
class backup_migrate_destination_files_manual extends backup_migrate_destination_files {
  var $supported_ops = array('manual backup', 'restore', 'list files', 'configure', 'delete');
  function __construct($params = array()) {
    $dir = 'private://backup_migrate/manual';
    parent::__construct($params + array('location' => $dir, 'name' => t('Manual Backups Directory')));
  }
}

/**
 * The scheduled files directory.
 */
class backup_migrate_destination_files_scheduled extends backup_migrate_destination_files {
  var $supported_ops = array('scheduled backup', 'restore', 'list files', 'configure', 'delete');
  function __construct($params = array()) {
    $dir = 'private://backup_migrate/scheduled';
    parent::__construct($params + array('location' => $dir, 'name' => t('Scheduled Backups Directory')));
  }
}

