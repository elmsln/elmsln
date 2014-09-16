<?php

/**
 * @file Memcached incident storage class
 */
class RadioactivityMemcachedIncidentStorage extends RadioactivityIncidentStorage {

  /**
   * Constructor
   */
  public function __construct() {}

  /**
   * Connect to the memcache server
   */
  private function connect() {
    $mc = null;
    if (class_exists('Memcache')) {
      $extension = 'Memcache';
    }
    elseif (class_exists('Memcached')) {
      $extension = 'Memcached';
    }
    if (empty($extension)) return FALSE;
    
    $mc = new $extension();
    $connected = @$mc->addServer(VAR_RADIOACTIVITY_MEMCACHED_HOST, VAR_RADIOACTIVITY_MEMCACHED_PORT);
    if ($connected) {
      return $mc;
    }

    return FALSE;
  }

  /**
   * Add incident to cache
   */
  public function addIncident(RadioactivityIncident $incident) {
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
    $mc = $this->connect();
    if (!$mc) {
      return;
    }
    $i = 0;
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
  }

  /**
   * Does this require boostrapping?
   */
  public function requiresBootstrap() {
    return FALSE;
  }
}
