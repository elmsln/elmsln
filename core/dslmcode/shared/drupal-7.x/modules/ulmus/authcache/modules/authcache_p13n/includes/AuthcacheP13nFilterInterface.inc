<?php

/**
 * @file
 * Defines request filter.
 */

/**
 * Interface for filters.
 */
interface AuthcacheP13nFilterInterface {
  /**
   * Perform a filter operation.
   */
  public function filter($event, $input);
}
