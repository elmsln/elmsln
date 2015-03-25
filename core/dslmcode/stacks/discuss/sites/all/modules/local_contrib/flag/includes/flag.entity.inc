<?php

/**
 * @file
 * Provides supporting code for the entity/fields system.
 *
 * Note: We're making the <em>flaggings</em> fieldable, not the <em>flags</em>.
 * (In the same way that Drupal makes <em>nodes</em> fieldable, not <em>node
 * types</em>).
 */

/**
 * Controller class for flaggings.
 */
class FlaggingController extends DrupalDefaultEntityController {

  protected function buildQuery($ids, $conditions = array(), $revision_id = FALSE) {
    $query = parent::buildQuery($ids, $conditions, $revision_id);
    // Add the flag name, which determines the bundle.
    $query->innerJoin('flag', 'flag', 'base.fid = flag.fid');
    $query->addField('flag', 'name', 'flag_name');
    return $query;
  }
}
