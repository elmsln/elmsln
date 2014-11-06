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

class backup_migrate_destination_filesource extends backup_migrate_source {
  var $supported_ops = array('restore', 'configure', 'delete', 'source');

  function type_name() {
    return t("Files Directory");
  }

  /**
   * Declare the current files directory as a backup source..
   */
  function sources() {
    $out  = array();
    $out['files'] = backup_migrate_create_destination('filesource', array('machine_name' => 'files', 'location' => 'public://', 'name' => t('Public Files Directory'), 'show_in_list' => FALSE));
    if (variable_get('file_private_path', FALSE)) {
      $out['files_private'] = backup_migrate_create_destination('filesource', array('machine_name' => 'files', 'location' => 'private://', 'name' => t('Private Files Directory'), 'show_in_list' => FALSE));
    }
    return $out;
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
    return $form;
  }

  /**
   * Return a list of backup filetypes.
   */
  function file_types() {
    return array(
      "tar" => array(
        "extension" => "tar",
        "filemime" => "application/x-tar",
        "backup" => TRUE,
        "restore" => TRUE,
      ),
    );
  }

  /**
   * Get the form for the settings for this destination.
   *
   * Return the default directories whose data can be ignored. These directories contain
   *  info which can be easily reproducted. Also exclude the backup and migrate folder 
   *  to prevent exponential bloat.
   */
  function backup_settings_default() {
     return array(
      'exclude_filepaths' => "backup_migrate\nstyles\ncss\njs\nctools\nless",
    );
  }

  /**
   * Get the form for the backup settings for this destination.
   */
  function backup_settings_form($settings) {
    $form['exclude_filepaths'] = array(
      "#type" => "textarea",
      "#multiple" => TRUE,
      "#title" => t("Exclude the following files or directories"),
      "#default_value" => $settings['exclude_filepaths'],
      "#description" => t("A list of files or directories to be excluded from backups. Add one path per line relative to the directory being backed up."),
    );
    return $form;
  }

  /**
   * Backup from this source.
   */
  function backup_to_file($file, $settings) {
    if ($out = $this->_backup_to_file_cli($file, $settings)) {
      return $out;
    }
    else {
      return $this->_backup_to_file_php($file, $settings);
    }
  }

  /**
   * Backup from this source.
   */
  function _backup_to_file_php($file, $settings) {
    if ($this->check_libs()) {
      $excluded_paths = empty($settings->filters['exclude_filepaths']) ? '' : $settings->filters['exclude_filepaths'];
      $files = $this->get_files_to_backup($this->get_realpath(), $settings, $this->get_excluded_paths($excluded_paths), DRUPAL_ROOT . '/');
      if ($files) {
        $file->push_type('tar');
        $gz = new Archive_Tar($file->filepath(), false);
        $gz->addModify($files, '', $this->get_realpath());
        return $file;
      }
      backup_migrate_backup_fail('No files available.', array(), $settings);
      return FALSE;
    }
    return FALSE;
  }

  /**
   * Backup from this source.
   */
  function _backup_to_file_cli($file, $settings) {
    if (!empty($settings->filters['use_cli']) && function_exists('backup_migrate_exec') && function_exists('escapeshellarg')) {
      $excluded_paths = empty($settings->filters['exclude_filepaths']) ? '' : $settings->filters['exclude_filepaths'];
      $exclude = array();
      foreach ($this->get_excluded_paths($excluded_paths) as $path) {
        $exclude[] = '--exclude=' . escapeshellarg($path);
      }
      $exclude = implode(' ', $exclude);

      // Create a symlink in a temp directory so we can rename the file in the archive.
      $temp = backup_migrate_temp_directory();

      $file->push_type('tar'); 
      backup_migrate_exec("tar --dereference -C %input -rf %output $exclude .", array('%output' => $file->filepath(), '%input' => $this->get_realpath(), '%temp' => $temp));

      return $file;
    }
    return FALSE;
  }

  /**
   * Restore to this source.
   */
  function restore_from_file($file, &$settings) {
    if ($out = $this->_restore_from_file_cli($file, $settings)) {
      return $out;
    }
    else {
      return $this->_restore_from_file_php($file, $settings);
    }
  }

  /**
   * Restore to this source.
   */
  function _restore_from_file_php($file, &$settings) {
    if ($this->check_libs()) {
      $from = $file->pop_type();
      $temp = backup_migrate_temp_directory();

      $tar = new Archive_Tar($from->filepath());
      $tar->extractModify($temp, $file->name);

      // Older B&M Files format included a base 'files' directory.
      if (file_exists($temp .'/files')) {
        $temp = $temp . '/files';
      }
      if (file_exists($temp .'/'. $file->name .'/files')) {
        $temp = $temp . '/files';
      }

      // Move the files from the temp directory.
      _backup_migrate_move_files($temp, $this->get_realpath());

      return $file;
    }
    return FALSE;
  }

  /**
   * Restore to this source.
   */
  function _restore_from_file_cli($file, &$settings) {
    if (!empty($settings->filters['use_cli']) && function_exists('backup_migrate_exec')) {
      $temp = backup_migrate_temp_directory();
      backup_migrate_exec("tar -C %temp -xf %input", array('%input' => $file->filepath(), '%temp' => $temp));

      // Older B&M Files format included a base 'files' directory.
      if (file_exists($temp .'/files')) {
        $temp = $temp . '/files';
      }
      if (file_exists($temp .'/'. $file->name .'/files')) {
        $temp = $temp . '/files';
      }

      // Move the files from the temp directory.
      backup_migrate_exec("mv -rf %temp/* %output", array('%output' => $this->get_realpath(), '%temp' => $temp));
      return $file;
    }
    return FALSE;
  }

  /**
   * Get a list of files to backup from the given set if dirs. Exclude any that match the array $exclude.
   */
  function get_files_to_backup($dir, $settings, $exclude = array(), $base_dir = '') {
    $out = $errors = array();
    if (!file_exists($dir)) {
      backup_migrate_backup_fail('Directory %dir does not exist.', array('%dir' => $dir), $settings);
      return FALSE;
    }
    if ($handle = @opendir($dir)) {
      while (($file = readdir($handle)) !== FALSE) {
        if ($file != '.' && $file != '..' && !in_array($file, $exclude)) {
          $real = realpath($dir . '/' . $file);
          $path = str_replace($base_dir, '', $real);
          // If the path is not excluded.
          if (!in_array($path, $exclude)) {
            if (is_dir($real)) {
              $subdir = $this->get_files_to_backup($real, $settings, $exclude, $base_dir);
              // If there was an error reading the subdirectory then abort the backup.
              if ($subdir === FALSE) {
                closedir($handle);
                return FALSE;
              }
              // If the directory is empty, add an empty directory.
              if (count($subdir) == 0) {
                $out[] = $path;
              }
              $out = array_merge($out, $subdir);
            }
            else {
              if (is_readable($real)) {
                $out[] = $path;
              }
              else {
                $errors[] = $dir . '/' . $file;
              }
            }
          }
        }
      }
      closedir($handle);
    }
    else {
      backup_migrate_backup_fail('Could not open directory %dir', array('%dir' => $dir), $settings);
      return FALSE;
    }

    // Alert the user to any errors there might have been.
    if ($errors) {
      if (count($errors < 5)) {
        $filesmsg = t('The following files: !files', array('!files' => theme('item_list', array('items' => $errors))));
      }
      else {
        $filesmsg = t('!count files', array('!count' => count($errors)));
      }

      if (empty($settings->filters['ignore_errors'])) {
        backup_migrate_backup_fail('The backup could not be completed because !files could not be read. If you want to skip unreadable files use the \'Ignore Errors\' setting under \'Advanced Options\' in \'Advanced Backup\' or in your schedule settings profile.', array('!files' => $filesmsg), 'error');
        $out = FALSE;
      }
      else {
        backup_migrate_backup_fail('!files could not be read and were skipped', array('!files' => $filesmsg), 'error');
      }
    }

    return $out;
  }

  /**
   * Break the excpluded paths string into a usable list of paths.
   */
  function get_excluded_paths($paths) {
    $out = explode("\n", $paths);
    foreach ($out as $key => $val) {
      $out[$key] = trim($val, "/ \t\r\n");
    }
    return $out;
  }

  /**
   * Check that the required libraries are installed.
   */
  function check_libs() {
    $result = true;
    // Drupal 7 has Archive_Tar built in so there should be no need to include anything here.
    return $result;
  }

 /**
   * Get the file location.
   */
  function get_realpath() {
    return drupal_realpath($this->get_location());
  }
}

