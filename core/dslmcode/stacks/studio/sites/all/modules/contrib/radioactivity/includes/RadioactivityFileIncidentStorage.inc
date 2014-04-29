<?php

/**
 * @file File incident storage class
 */

class RadioactivityFileIncidentStorage extends RadioactivityIncidentStorage {

  static $fileEmitters;
  static $cronDone;

  /**
   * Constructor
   */
  public function __construct() {
    parent::__construct();
  }

  /**
   * Add incident directly to the db
   */
  public function addIncident(RadioactivityIncident $incident) {
    $row  = serialize($incident);
    $tmp  = VAR_RADIOACTIVITY_TEMP_DIR;
    $file = $tmp . "/radioactivity-payload.txt";
    $fh   = fopen($file, "a+");
    fwrite($fh, $row . PHP_EOL);
    fclose($fh);
  }

  /**
   * Process incidents in the deferred queue
   */
  public function processIncidents() {

    // file incidents are all in the same storage so we'll do this only once
    // even though there might be many fields
    if (self::$cronDone) {
      return;
    }
    self::$cronDone = TRUE;

    $tmp = VAR_RADIOACTIVITY_TEMP_DIR;

    $file = $tmp . "/radioactivity-payload.txt";

    if (file_exists($file)) {
      // get file contents and clear file
      $fh = fopen($file, "r");
      $data = fread($fh, filesize($file));
      fclose($fh);
      unlink($file);

      $data = explode(PHP_EOL, $data);
      foreach ($data as $row) {
        if (empty($row)) {
          continue;
        }
        $incident = unserialize($row);
        $incident->updateEnergy();
      }
    }
  }

  /**
   * Default emitting for the default processEmitter function
   */
  public function addEmitter($entity_type, $bundle, $field_name, $entity_id, $energy) {
    if (self::$fileEmitters == NULL) {
      self::$fileEmitters = array();
    }

    if ($entity_id !== NULL) {

      if (!isset(self::$fileEmitters[$entity_type][$bundle][$field_name][$entity_id])) {

        self::$fileEmitters[$entity_type][$bundle][$field_name][$entity_id] = 0;

      }

      self::$fileEmitters[$entity_type][$bundle][$field_name][$entity_id] += $energy;
    }
    else {

      return self::$fileEmitters;
    }
  }

  /**
   * Does this require boostrapping?
   */
  public function requiresBootstrap() {
    return FALSE;
  }
}
