<?php

/**
 * @file
 * Contains the CER plugin for Node Reference fields.
 */
 
class CerNodeReferenceField extends CerField {

  /**
   * Implements CerField::getTargetType().
   */
  public function getTargetType() {
    return 'node';
  }

  /**
   * @override CerField::getTargetBundles().
   */
  public function getTargetBundles() {
    $bundles = array();

    $view = $this->settings['view']['view_name'];
    if ($view) {
      $view = views_get_view($view);
      $view->set_display($this->settings['view']['view_display']);

      $handler = $view->display_handler->get_handler('filter', 'type');
      if ($handler) {
        $bundles = $handler->value;
      }
    }
    else {
      $bundles = array_filter($this->settings['referenceable_types']);
    }

    return ($bundles ? $bundles : parent::getTargetBundles());
  }

}
 