<?php

/**
 * @file Memcached incident storage class
 */

class RadioactivityRedisIncidentStorage extends RadioactivityIncidentStorage {

  /**
   * Constructor
   */
  public function __construct() {}

  /**
   * Connect to the memcache server
   */
  private function connect() {
    $redis = new Redis();
    $port = VAR_RADIOACTIVITY_REDIS_PORT;
    if (!empty($port)) {
      $redis->connect(VAR_RADIOACTIVITY_REDIS_HOST, VAR_RADIOACTIVITY_REDIS_PORT);
    } else {
      $redis->connect(VAR_RADIOACTIVITY_REDIS_HOST);
    }
    return $redis;
  }

  /**
   * Add incident to cache
   */
  public function addIncident(RadioactivityIncident $incident) {
    if (!$rc = $this->connect()) {
      return;
    }
    $i = $rc->get("radioactivity_top");
    if (!$i) {
      $i = 0;
    }
    $rc->set("radioactivity_top", $i + 1);
    $rc->set("radioactivity_incident_" . $i, serialize($incident));
  }

  /**
   * Process incidents in the deferred queue
   */
  public function processIncidents() {
    $rc = $this->connect();
    if (!$rc) {
      return;
    }
    $i = 0;
    // get and reset top
    $to = $rc->get("radioactivity_top");
    $rc->set("radioactivity_top", 0);
    if (!$to) {
      $to = 0;
    }
    while ($i < $to) {
      $incident = unserialize($rc->get("radioactivity_incident_" . $i));
      if ($incident->floodCheck()) {
        $incident->updateEnergy();
      }
      $i++;
    }
  }

  /**
   * Does this require boostrapping?
   */
  public function requiresBootstrap() {
    return FALSE;
  }
}
