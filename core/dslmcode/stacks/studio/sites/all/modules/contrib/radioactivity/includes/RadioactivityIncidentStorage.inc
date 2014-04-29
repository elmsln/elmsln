<?php

/**
 * @file Base class for incident storages
 */

abstract class RadioactivityIncidentStorage {

  public function __construct() {
  }

  /**
   * Add incident to the storage system
   * @entity_energy Energies by entity id
   */
  public function addIncident(RadioactivityIncident $incident) {
    // does nothing
  }

  /**
   * Process incidents in the storage
   * When this is run depends solely on cron timing & decay pattern granularity
   */
  public function processIncidents() {
    // nothing to do
  }

  /**
   * Get decay profile attached to this instance
   */
  public function getDecayProfile() {
    return radioactivity_decay_profile_load($this->settings['profile']);
  }

  /**
   * Does this require boostrapping?
   */
  public function requiresBootstrap() {
    return TRUE;
  }
}
