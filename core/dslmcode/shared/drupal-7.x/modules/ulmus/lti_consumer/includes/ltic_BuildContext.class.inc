<?php

/*
 * @file class/object
 * Generates details for a Context from a context entity
 */

class BuildContext {

  protected $contextEntity;

  public function __construct($id) {
    $this->contextEntity = ltic_context_load($id);
  }

  public function getDetails() {
    return[
      'context_id' => $this->contextEntity->ltic_context_id_ref,
      'context_title' => $this->contextEntity->ltic_context_title,
      'context_label' => $this->contextEntity->ltic_context_label,
      'lis_course_section_sourcedid' =>$this->contextEntity->ltic_lis_course_section_sourcedid
    ];
  }

 public function getResources() {
    $resources = [];
    if (isset($this->contextEntity->field_ltic_resource_ref) && isset($this->contextEntity->field_ltic_resource_ref[LANGUAGE_NONE])) {
      foreach ($this->contextEntity->field_ltic_resource_ref[LANGUAGE_NONE] as $target) {
        $resources[] = $target['target_id'];
      }
    }
    return $resources;
  }

}
