<?php

/**
 * @file
 * Contains HarmonyCoreViewsHandlerFilterPostPublic.
 */

class HarmonyCoreViewsHandlerFilterPostPublic extends HarmonyCoreViewsHandlerFilterPublic {
  /**
   * Add in the hidden property to the query.
   *
   * Overrides HarmonyCoreViewsHandlerFilterPostPublic::construct().
   */
  function construct() {
    parent::construct();

    $this->apply_hidden = TRUE;
  }
}
