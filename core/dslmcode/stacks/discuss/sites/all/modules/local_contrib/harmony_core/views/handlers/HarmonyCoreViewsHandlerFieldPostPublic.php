<?php

/**
 * @file
 * Contains HarmonyCoreViewsHandlerFieldPostPublic.
 */

class HarmonyCoreViewsHandlerFieldPostPublic extends HarmonyCoreViewsHandlerFieldPublic {
  /**
   * Add in the hidden property to the query.
   *
   * Overrides HarmonyCoreViewsHandlerFieldPublic::construct().
   */
  public function construct() {
    parent::construct();

    $this->additional_fields = array('hidden');
  }
}
