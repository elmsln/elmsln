<?php

/**
 * @file
 * Contains the CER plugin for Entity Reference fields.
 */
 
class CerEntityReferenceField extends CerField {

  /**
   * Implements CerField::getTargetType().
   */
  public function getTargetType() {
    return $this->settings['target_type'];
  }
  
  /**
   * @override CerField::getTargetBundles().
   */
  public function getTargetBundles() {
    $bundles = array();

    // If the reference field is using a view, load the view and see if it's filtering by the entity
    // type's bundle filter. If it is, the filter values are the target bundles. Otherwise,
    // assume that all bundles can be referenced.
    //
    // @todo Support contextual filters?
    //
    // NOTE: Selection handlers (i.e., $field['settings']['handler']) are plugins owned by
    // Entity Reference. There is no method defined to get an array of referenceable
    // bundles, but hopefully, if CER gains enough traction in the community, such a
    // method can be added to the EntityReference_SelectionHandler interface. This
    // function could then be deprecated, which would be a more flexible, future-proof
    // method of finding a field's target bundles.
    //
    if ($this->settings['handler'] == 'views') {
      $view = views_get_view($this->settings['handler_settings']['view']['view_name']);
      $view->set_display($this->settings['handler_settings']['view']['display_name']);

      $info = entity_get_info($this->getTargetType());
      if (isset($info['entity keys']['bundle'])) {
        $handler = $view->display_handler->get_handler('filter', $info['entity keys']['bundle']);
        if ($handler) {
          $bundles = $handler->value;
        }
      }
    }
    else {
      $bundles = $this->settings['handler_settings']['target_bundles'];
    }

    return ($bundles ? $bundles : parent::getTargetBundles());
  }

}
