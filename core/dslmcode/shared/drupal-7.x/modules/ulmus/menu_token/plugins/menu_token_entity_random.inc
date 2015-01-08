<?php

class menu_token_entity_random implements menu_token_handler {
  function form_options($options) {
    // Nothing to do here.
  }

  function form_submit($form, &$form_state) {
    // Nothing to do here.
  }

  function form_validate($form, &$form_state) {
    // Nothing to do here.
  }

  function form_alter(&$form, &$form_state) {
    // Nothing to do here.
  }

  function object_load($options) {
    $entity_type = $options['_type'];
    $info = entity_get_info($entity_type);

    $id =
      db_select($info['base table'], 'e')
      ->fields('e', array($info['entity keys']['id']))
      ->orderRandom()
      ->range(0, 1)
      ->execute()
      ->fetchField(0);

    if ($id) {
      return entity_load_single($entity_type, $id);
    }

    return FALSE;
  }
}
