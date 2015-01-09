<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class entityform_handler_delete_link_field extends entityform_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
  }


  function render($values) {
    if ($entity = $this->get_value($values)) {
      $uri = array(
        'path' => 'entityform/' . $entity->entityform_id . '/delete',
        'options' => array('query' => array('destination' => request_path())),
      );
      return $this->render_link($entity, 'delete', $uri, t('delete'));
    }
  }
}
