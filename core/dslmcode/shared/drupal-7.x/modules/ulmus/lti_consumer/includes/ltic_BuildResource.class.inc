<?php

/*
 * @file class/object
 * Generates details for a Resource from a resource entity
 */

class BuildResource {

  /**
   * @var array
   */
  protected $resourceEntitys;

  /**
   * @param array $id
   */
  public function __construct(array $id) {
    $this->resourceEntitys = ltic_resource_load_multiple($id);
  }

  /**
   * @return array
   */
  public function getDetails() {
    $rtn = [];
    foreach ($this->resourceEntitys as $key => $entity) {
      $rtn[$key]['resource_link_id'] = $key;
      $rtn[$key]['resource_link_title'] = $entity->ltic_resource_link_title;
      $rtn[$key]['resource_link_description'] = $entity->ltic_resource_link_description;
    }
    return $rtn;
  }

}
