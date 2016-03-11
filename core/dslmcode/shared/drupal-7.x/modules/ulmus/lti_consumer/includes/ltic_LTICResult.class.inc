<?php

class LTICResult {

  /**
   * @var string
   */
  protected $contextId;

  /**
   * @var string
   */
  protected $resourceId;

  /**
   * @var int
   */
  protected $userId;

  /**
   * @global stdObject $user
   * @param string $context_id
   * @param string $resource_id
   * @param string $user_id
   */
  public function __construct($context_id, $resource_id, $user_id = FALSE) {
    $this->contextId = $context_id;
    $this->resourceId = $resource_id;
    if ($user_id) {
      $this->userId = $user_id;
    }
    else {
      global $user;
      $this->userId = $user->uid;
    }
  }

  /**
   * Checks to see if the user has a result.
   * @return int
   */
  public function check() {
    return db_query("
       SELECT ltic_result_id
       FROM {ltic_result} 
       WHERE ltic_context_id_ref = :cid 
       AND ltic_resource_id_ref = :rid 
       AND ltic_user_id = :uid
       ", [':cid' => $this->contextId, ':rid' => $this->resourceId, ':uid' => $this->userId])->fetchField();
  }

  /**
   * If they dont have a record for this resource create one.
   */
  public function initalise() {
    if (!$this->check()) {
      $entity = new stdClass();
      $entity->bundle_type = 'first_example_bundle';
      $entity->ltic_context_id_ref = $this->contextId;
      $entity->ltic_resource_id_ref = $this->resourceId;
      $entity->ltic_user_id = $this->userId;
      $entity->ltic_result = 0;
      $entity->ltic_result_id = NULL;
      ltic_result_save($entity);
    }
  }

}
