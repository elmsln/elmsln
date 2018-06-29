<?php

/**
 * The entity controller for oauth2_server_token entities.
 */
class OAuth2ServerTokenEntityController extends EntityAPIController {

  /**
   * Overrides EntityAPIController::save().
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    // Ensure that the token 'created' timestamp is saved, for new tokens.
    $entity->is_new = !empty($entity->is_new) || empty($entity->{$this->idKey});
    if ($entity->is_new && empty($entity->created)) {
        $entity->created = REQUEST_TIME;
    }

    return parent::save($entity, $transaction);
  }
}
