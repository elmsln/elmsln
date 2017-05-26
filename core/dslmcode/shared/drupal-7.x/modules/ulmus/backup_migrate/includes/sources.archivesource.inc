<?php
backup_migrate_include('sources.filesource');

/**
 * @file
 * A destination type for saving locally to the server.
 */

/**
 * A destination type for saving locally to the server.
 *
 * @ingroup backup_migrate_destinations
 */

class backup_migrate_files_destination_archivesource extends backup_migrate_destination_filesource {
  var $supported_ops = array('source');

  function type_name() {
    return t("Site Archive Source");
  }

  /**
   * Declare the current files directory as a backup source..
   */
  function sources() {
    $out  = array();
    $out['archive'] = backup_migrate_create_destination('archive', array('machine_name' => 'archive', 'location' => '.', 'name' => t('Entire Site (code, files & DB)'), 'show_in_list' => FALSE));
    return $out;
  }

  /**
   * Return a list of backup filetypes.
   */
  function file_types() {
    return array(
      "sitearchive" => array(
        "extension" => "sitearchive.tar",
        "filemime" => "application/x-tar",
        "backup" => TRUE,
        "restore" => FALSE,
      ),
    );
  }

  /**
   * Get the form for the settings for this destination.
   */
  function backup_settings_default() {
    $out = parent::backup_settings_default();
    $excludes = explode("\n", $out['exclude_filepaths']);
    foreach ($excludes as $i => $exclude) {
      $excludes[$i] = 'public://' . $exclude;
    }
    $excludes[] = 'private://backup_migrate';
    $excludes[] = conf_path() . '/settings.php';
    $excludes[] = file_directory_temp();

    return array(
      'exclude_filepaths' => implode("\n", $excludes),
    );
  }

  /**
   * Backup from this source.
   */
  function _backup_to_file_php($file, $settings) {
    if ($this->check_libs()) {
      $base_dir = $this->get_realpath();

      $excluded_paths = empty($settings->filters['exclude_filepaths']) ? '' : $settings->filters['exclude_filepaths'];
      $exclude = $this->get_excluded_paths($settings);
      $files = $this->get_files_to_backup($this->get_realpath(), $settings, $exclude);
      if ($files) {
        $manifest = $this->generate_manifest();
        $db = $this->get_db();

        $file->push_type('sitearchive');
        $gz = new Archive_Tar($file->filepath(), false);

        $gz->addModify(array($manifest), $file->name .'/', dirname($manifest));
        $gz->addModify($files, $file->name .'/docroot', $base_dir);
        $gz->addModify($db, $file->name . '/', dirname($db));

        unlink($manifest);
        rmdir(dirname($manifest));
        unlink($db);
        rmdir(dirname($db));

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
      foreach ($this->get_excluded_paths($excluded_paths) as $path) {
        $exclude[] = '--exclude=' . escapeshellarg($path);
      }
      $exclude = implode(' ', $exclude);

      // Create a symlink in a temp directory so we can rename the file in the archive.
      $temp = backup_migrate_temp_directory();

      $manifest = $this->generate_manifest();
      $db = $this->get_db();
      rename($db, $temp . '/database.sql');
      rename($manifest, $temp . '/MANIFEST.ini');

      $file->push_type('sitearchive');
      $link = $temp . '/docroot';
      $input = realpath($this->get_location());
      backup_migrate_exec("ln -s %input %link; tar --dereference -C %temp -rf %output $exclude .", array('%output' => $file->filepath(), '%input' => $input, '%temp' => $temp, '%link' => $link));

      return $file;
    }
    return FALSE;
  }

  /**
   * Generate a manifest file.
   */
  function generate_manifest() {
    $info = array(
      'Global' => array(
        'datestamp' => time(),
        'formatversion' => '2011-07-02',
        'generator' => 'Backup and Migrate (http://drupal.org/project/backup_migrate)',
        'generatorversion' => BACKUP_MIGRATE_VERSION, 
      ),
      'Site 0' => array(
        'version' => VERSION,
        'name' => variable_get('site_name', ''),
        'docroot' => 'docroot',
        'sitedir' => 'docroot/' . conf_path(),
        'database-file-default' => 'database.sql',
        'database-file-driver' => 'mysql',
      ),
    );
    if ($private = variable_get('file_private_path', FALSE)) {
      $info['Site 0']['files-private'] = 'docroot/' . $private;
    }
    $info['Site 0']['files-public'] = 'docroot/' . variable_get('file_public_path', FALSE);
    $ini = $this->_array_to_ini($info);

    $tmpdir = backup_migrate_temp_directory();
    $filepath = $tmpdir . '/MANIFEST.ini';
    file_put_contents($filepath, $ini);
    return $filepath;
  }

  /**
   * Get a database dump to add to the archive.
   */
  function get_db() {
    backup_migrate_include('destinations', 'files', 'filters', 'profiles');

    $file = new backup_file();
    // Clone the default settings so we can make changes without them leaking out of this function.
    $settings = clone _backup_migrate_profile_saved_default_profile();
    $settings->source_id = 'db';
    $settings->filters['compression'] = 'none';

    // Execute the backup on the db with the default settings.
    $file = backup_migrate_filters_backup($file, $settings);

    // Generate a tmp file with the correct final title (because ArchiveTar doesn't seem to allow renaming).
    $tmpdir = backup_migrate_temp_directory();
    $filepath = $tmpdir . '/database.sql';
    rename($file->filepath(), $filepath);

    return $filepath;
  }

  /**
   * Restore to this source.
   */
  function _restore_from_file_php($file, &$settings) {
    $success = false;
    if ($this->check_libs()) {
      $from = $file->pop_type();
      $temp = backup_migrate_temp_directory();

      $tar = new Archive_Tar($from->filepath());
      $tar->extractModify($temp, $file->name);

      // Parse the manifest
      $manifest = $this->read_manifest($temp);

      // Currently only the first site in the archive is supported.
      $site = $manifest['Site 0'];

      $docroot  = $temp . '/' . $site['docroot'];
      $sqlfile  = $temp . '/' . $site['database-file-default'];
      $filepath = NULL;
      if (isset($site['files-private'])) {
        $filepath = $temp . '/' . $site['files-private'];
      }
      else if (isset($site['files-public'])) {
        $filepath = $temp . '/' . $site['files-public'];
      }

      // Move the files from the temp directory.
      if ($filepath && file_exists($filepath)) {
        _backup_migrate_move_files($filepath, file_directory_path());
      }
      else {
        _backup_migrate_message('Files were not restored because the archive did not seem to contain a files directory or was in a format that Backup and Migrate couldn\'t read', array(), 'warning');
      }

      // Restore the sql db.
      if ($sqlfile && file_exists($sqlfile)) {
        $db_settings = clone($settings);
        $db_settings->source_id = 'db';
        $file = new backup_file(array('filepath' => $sqlfile));
        $success = backup_migrate_filters_restore($file, $db_settings);
      }
      else {
        _backup_migrate_message('The database was not restored because the archive did not seem to contain a database backup or was in a format that Backup and Migrate couldn\'t read', array(), 'warning');
      }

      if ($docroot) {
        _backup_migrate_message('Backup and Migrate cannot restore the php code of the site for security reasons. You will have to copy the code to the server by hand if you wish to restore the full site.', array(), 'warning');
      }

      return $success && $file;
    }
    return FALSE;
  }

  /**
   * Restore to this source.
   */
  function _restore_from_file_cli($file, &$settings) {
    // @TODO: implement the cli version of the restore.
    return FALSE;
  }

  /**
   * Generate a manifest file.
   */
  function read_manifest($directory) {
    // Assume some defaults if values ore the manifest is missing.
    $defaults = array(
      'docroot' => 'docroot',
      'database-file-default' => 'database.sql',
      'database-file-driver' => 'mysql',
    );

    $out = $this->_ini_to_array($directory . '/MANIFEST.ini');

    // Set the defaults.
    $out['Site 0'] = isset($out['Site 0']) ? $out['Site 0'] : array();
    $out['Site 0'] += $defaults;

    return $out;
  }

  /**
   * Convert an associated array to an ini format string. Only allows 2 levels of depth to allow parse_ini_file to parse.
   */
  function _array_to_ini($sections) {
    $content = ""; 
    foreach ($sections as $section => $data) {
      $content .= '['. $section .']' . "\n";
      foreach ($data as $key => $val) {
        $content .= $key . " = \"". $val ."\"\n";
      }
      $content .= "\n";
    }
    return $content;
  }

  /**
   * Convert an associated array to an ini format string. Only allows 2 levels of depth to allow parse_ini_file to parse.
   */
  function _ini_to_array($path) {
    return parse_ini_file($path, TRUE);
  }
}

