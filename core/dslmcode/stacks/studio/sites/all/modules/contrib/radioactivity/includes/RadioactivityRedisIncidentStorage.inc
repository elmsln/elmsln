<?php

/**
 * @file Memcached incident storage class
 */

class RadioactivityRedisIncidentStorage extends RadioactivityIncidentStorage {

  static $redisEmitters;

  /**
   * Constructor
   */
  public function __construct() {}

  /**
   * Connect to the memcache server
   */
  private function connect() {
    static $included;
    if (!$included) {
      include('/var/www/drupal.dev/web/sites/all/libraries/predis/autoload.php');
    }

    $client = new Predis\Client($single_server);

    $client->set('library', 'predis');
    $retval = $client->get('library');

    var_dump($retval);

  }

  /**
   * Add incident to cache
   */
  public function addIncident($incident) {
    return;
    $mc = $this->connect();
    if (!$mc) {
      return;
    }
    $i = $mc->get("radioactivity_top");
    if (!$i) {
      $i = 0;
    }
    $mc->set("radioactivity_top", $i + 1);
    $mc->set("radioactivity_incident_" . $i, $incident);
  }

  /**
   * Process incidents in the deferred queue
   */
  public function processIncidents() {
    return;
    $mc = $this->connect();
    if (!$mc) {
      return;
    }
    $i = $mc->get("radioactivity_bottom");
    if (!$i) {
      $i = 0;
    }
    // get and reset top
    $to = $mc->get("radioactivity_top");
    $mc->set("radioactivity_top", 0);
    if (!$to) {
      $to = 0;
    }
    while ($i < $to) {
      $incident = $mc->get("radioactivity_incident_" . $i);
      if ($incident->floodCheck()) {
        $incident->updateEnergy();
      }
      $i++;
    }
    $mc->set("radioactivity_bottom", 0);
  }

  /**
   * Default emitting for the default processEmitter function
   */
  public function addEmitter($entity_id, $energy) {
    drupal_set_message($entity_id);
    if (self::$redisEmitters == NULL) {
      self::$redisEmitters = array();
    }
    if ($entity_id !== NULL) {
      if (!isset(self::$redisEmitters[$this->entityType][$this->bundle][$this->fieldName][$entity_id])) {
        self::$redisEmitters[$this->entityType][$this->bundle][$this->fieldName][$entity_id] = 0;
      }
      self::$redisEmitters[$this->entityType][$this->bundle][$this->fieldName][$entity_id] += $energy;
    }
    else {
      return self::$redisEmitters;
    }
  }

  /**
   * Does this require boostrapping?
   */
  public function requiresBootstrap() {
    return FALSE;
  }
}
