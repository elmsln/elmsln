<?php
/**
 * @file
 * Defines context provider collecting views argumnets from path.
 */

/**
 * Collect views arguments from current menu router item path.
 *
 * Use this context provider when rendering page displays with context filters.
 */
class AuthcacheViewsDisplayPageContextProvider implements AuthcacheP13nContextProviderInterface {
  /**
   * {@inheritdoc}
   */
  public function get($params) {
    $router_item = menu_get_item();
    $args = $router_item['page_arguments'];

    // Remove $name and $display_id from the arguments.
    array_shift($args);
    array_shift($args);

    return $args;
  }
}
