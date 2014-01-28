<?php

/**
* Field handler to present an entity iframe embed code
*
* Closely modeled after views/modules/node/views_handler_field_node_link_edit.inc
*/
class views_handler_field_entity_iframe_embed extends entity_views_handler_field_text {  
  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($values) {
    // capture the entity type in use
    $type = $this->entity_type;
    if (user_access('view iframe embed code') && _entity_iframe_view_iframe($type, $values->{$this->base_field})) {
      global $base_url;
      // load type info so we know what property to target
      $properties = array(
        'width' => variable_get('entity_iframe_width', ENTITY_IFRAME_WIDTH),
        'height' => variable_get('entity_iframe_height', ENTITY_IFRAME_HEIGHT),
        'src' => "$base_url/entity_iframe/$type/" . $values->{$this->base_field},
        'frameborder' => '0',
        'class' => 'entity_iframe entity_iframe_' . $type,
        'id' => 'entity_iframe_' . $type . '_' . $values->{$this->base_field},
      );
      $form = array(
        '#attributes' => array('class' => array('entity_iframe_embed')),
        '#value' => _entity_iframe_build_iframe($properties, 'view'),
        '#type' => 'textarea',
        '#rows' => 3,
        '#cols' => 1,
        '#pre_render' => array('_entity_iframe_embed_add_js'),
      );
      $text = drupal_render($form);
      return $text;
    }
  }
}
