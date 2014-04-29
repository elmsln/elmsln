<?php

/**
 * @file Deferred incident storage class
 */

class RadioactivityDeferredIncidentStorage extends RadioactivityIncidentStorage {

  /**
   * Constructor
   */
  public function __construct() {}

  /**
   * add incident to the deferred storage
   * @entity_energy energy by entity id
   */
  public function addIncident(RadioactivityIncident $incident) {

    db_insert('radioactivity_deferred_incidents')->fields(array('data' => serialize($incident)))->execute();
  }

  /**
   * Process incidents in the deferred queue
   */
  public function processIncidents() {

    // grab rows from table and push them to fields

    $query = db_select("radioactivity_deferred_incidents", "rds")->fields("rds", array("data"));

    $result = $query->execute();

    while ($row = $result->fetch()) {
      $incident = unserialize($row->data);
      if ($incident->floodCheck()) {
        $incident->updateEnergy();
      }
    }

    // Flush the processed entries from the db
    db_delete("radioactivity_deferred_incidents")->execute();
  }
}
