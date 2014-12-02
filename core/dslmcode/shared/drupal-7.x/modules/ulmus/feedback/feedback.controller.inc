<?php

/**
 * @file
 * Entity controller class.
 */

/**
 * Controller class for feedback entries.
 *
 * This extends the DrupalDefaultEntityController class, adding required
 * special handling for feedback objects.
 */
class FeedbackController extends DrupalDefaultEntityController {

  protected function buildQuery($ids, $conditions = array(), $revision_id = FALSE) {
    $query = parent::buildQuery($ids, $conditions, $revision_id);
    // Specify an additional field from the user table.
    $query->innerJoin('users', 'u', 'base.uid = u.uid');
    $query->fields('u', array('name'));
    return $query;
  }
}