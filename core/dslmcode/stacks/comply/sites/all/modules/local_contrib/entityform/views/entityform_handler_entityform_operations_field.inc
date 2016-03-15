<?php

/**
 * @file
 * This field handler aggregates operations that can be done on a entityform
 * under a single field providing a more flexible way to present them in a view
 */
class entityform_handler_entityform_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['entityform_id'] = 'entityform_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('entityform', 'admin/structure/entityforms/entityform', array($this->get_value($values, 'entityform_id')));

    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
