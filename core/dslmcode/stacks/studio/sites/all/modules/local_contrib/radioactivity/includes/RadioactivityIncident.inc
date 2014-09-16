<?php

/**
 * @file Incident class
 */

class RadioactivityIncident {

  public $bundle;
  public $fieldName;
  public $entityType;
  public $energy;
  public $language;
  public $entityId;
  public $time;
  public $source;

  private static $source_cache; function __construct($entity_type, $bundle, $field_name, $language, $entity_id, $energy, $time) {
    $this->entityType = $entity_type;
    $this->bundle     = $bundle;
    $this->fieldName  = $field_name;
    $this->language   = $language;
    $this->entityId   = $entity_id;
    $this->energy     = $energy;
    $this->time       = $time;
    $this->source     = $this->getSource();
  }

  /**
   * Figure out the source of this incident
   * MUST work without Drupal boostrap also
   */
  private function getSource() {
    if (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
      self::$source_cache = $_SERVER['HTTP_X_FORWARDED_FOR'];
    }
    else {
      self::$source_cache = $_SERVER['REMOTE_ADDR'];
    }
    if (isset($_SERVER['HTTP_USER_AGENT'])) {
      self::$source_cache .= $_SERVER['HTTP_USER_AGENT'];
    }
    $hash = $this->entityType . $this->bundle . $this->fieldName . $this->language . $this->entityId;
    $source = md5(self::$source_cache . $hash);
    return $source;
  }

  /**
   * Update energy
   * Drupal only
   */
  public function updateEnergy() {
    _radioactivity_update_energy(
      $this->entityType,
      $this->bundle,
      $this->fieldName,
      $this->language,
      $this->entityId,
      $this->energy,
      $this->time
    );
  }

  /**
   * Flood check
   * Drupal only
   */
  public function floodCheck() {
    static $enabled;
    static $timeout;

    if (!isset($enabled)) {
      $enabled = variable_get('radioactivity_flood_protection', FALSE);
      $timeout = variable_get('radioactivity_flood_timeout', 15) * 60;
    }

    if ($enabled) {

      // check the map for hits
      $hit = db_select('radioactivity_flood_map', 'fm')->fields('fm', array('time'))->condition('fm.source', $this->source)->condition('fm.time', $this->time - $timeout, ">")->execute()->fetchObject();

      if ($hit) {
        return FALSE;
      }

      // insert current
      db_merge('radioactivity_flood_map')->key(array(
          'source' => $this->source,
        ))->fields(array(
          'source' => $this->source,
          'time' => $this->time,
        ))->execute();
      return TRUE;
    }

    return TRUE;
  }
}
