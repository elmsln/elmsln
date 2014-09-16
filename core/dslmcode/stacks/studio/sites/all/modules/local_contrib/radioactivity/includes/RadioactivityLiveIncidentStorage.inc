<?php

/**
 * @file Live Incident storage class
 */

class RadioactivityLiveIncidentStorage extends RadioactivityIncidentStorage {

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
    $incident->updateEnergy();
  }
}
