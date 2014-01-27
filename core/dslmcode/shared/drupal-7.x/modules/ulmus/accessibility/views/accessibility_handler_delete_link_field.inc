<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class accessibility_handler_delete_link_field extends accessibility_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['test_id'] = 'test_id';
  }


  function render($values) {
    $type = $values->{$this->aliases['test_id']};
    
    //Creating a dummy accessibility to check access against
    $dummy_accessibility = (object) array('type' => $type);
    if (!accessibility_test_access('edit', $dummy_accessibility)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $accessibility_id = $values->{$this->aliases['test_id']};
    
    return l($text, 'accessibility-test/' . $accessibility_id . '/delete');
  }
}
