<?php

class menu_token_entity_context implements menu_token_handler {
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
    $entity_info = entity_get_info($entity_type);

    // As the $entity object is not available in $options, we can't use uri_callback method.
    // Thus directly look for path in the entity info.
    if (isset($entity_info['path'])) {
      $path = $entity_info['path'];
    }
    // Or look for a default path.
    elseif (isset($entity_info['default path'])) {
      $path = $entity_info['default path'];
    }
    // No path available so far, so exit with NULL.
    else {
      return NULL;
    }

    $path_components = explode('/', $path);
    foreach ($path_components as $position => $component) {
      // If this is a menu argument, then use the current position to find
      // the entity id.
      if (strpos($component, '%') === 0) {
        break;
      }

      // If the current URL deviates from the expected path, assume the
      // entity is not present.
      if ($component !== arg($position)) {
        return FALSE;
      }
    }

    return entity_load_single($entity_type, arg($position));
  }
}
