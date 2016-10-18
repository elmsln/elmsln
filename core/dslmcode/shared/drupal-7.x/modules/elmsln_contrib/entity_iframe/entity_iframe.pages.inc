<?php
/**
 * @file
 * Pages of output for iframe exporting
 */

/**
 * Callback for entity_iframe/%/%/% menu path item.
 */
function entity_iframe_output($type, $etid, $view_mode) {
  if (empty($view_mode)) {
    $view_mode = 'iframe';
  }
  // load information about the entity type
  $type_info = entity_get_info($type);
  // make sure this is a valid item and they have access
  if (user_access('access iframe version')
    && is_numeric($etid)
    && $type_info
  ) {
    // load the entity
    $entity = entity_load_single($type, $etid);
    // verify we have a valid entity, type and that they have access to it
    if (is_object($entity) && entity_access('view', $type, $entity)) {
      // build the output display based on iframe format
      $build = entity_view($type, array($entity), $view_mode);
      // unset theme and contextual links if set
      if (isset($build[$type][$etid]['#theme'])) {
        unset($build[$type][$etid]['#theme']);
      }
      if (isset($build[$type][$etid]['#contextual_links'])) {
        unset($build[$type][$etid]['#contextual_links']);
      }
      // render build array to output
      $contents = drupal_render($build);
      // check for label callback as title
      if (isset($type_info['label callback'])) {
        $title = call_user_func($type_info['label callback'], $entity);
      }
      // check for entity defined label as key
      else if (isset($type_info['entity keys']['label'])) {
        $title = $entity->{$type_info['entity keys']['label']};
      }
      else {
        // couldn't calculate, use type name
        $title = t('Entity of type @type', array('@type' => $type));
      }
      // theme the output which triggers the entity-iframe.tpl.php file output
      return theme('entity_iframe', array('title' => $title, 'contents' => $contents));
    }
    else {
      drupal_not_found();
    }
  }
  else {
    drupal_access_denied();
  }
}
