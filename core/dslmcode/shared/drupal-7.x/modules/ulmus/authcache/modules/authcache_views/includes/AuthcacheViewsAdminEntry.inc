<?php
/**
 * @file
 * Defines the block admin entry class.
 */

/**
 * Block admin entry class.
 */
class AuthcacheViewsAdminEntry {

  /**
   * Construct a new block admin entry.
   */
  public function __construct($view_name, $display_id, $config, $defaults) {
    // Copy over defaults.
    foreach ($defaults as $key => $value) {
      $this->{$key} = $value;
    }

    // Specify group.
    $this->group = t('Views');

    $view = views_get_view($view_name);
    $this->name = check_plain($view->get_human_name());
    $this->description = t('Display %display_name on view %view_name', array(
      '%view_name' => $view->human_name,
      '%display_name' => $view->display[$display_id]->display_title,
    ));
    $this->clients = $config['clients'];

    if (module_exists('views_ui')) {
      $this->adminPath = 'admin/structure/views/view/' . $view_name . '/edit/' . $display_id;
    }
  }
}
