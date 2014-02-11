<?php

/**
 * @file
 * Definition of MediaBrowserPlugin.
 */

/**
 * Defines a Media browser plugin base class.
 *
 * MediaBrowserPlugin implementations need to implement at least the
 * view() method.
 */
abstract class MediaBrowserPlugin implements MediaBrowserPluginInterface {
  /**
   * The plugin metadata array from hook_media_browser_plugin_info().
   *
   * @var array
   */
  protected $info;

  /**
   * The parameters for the current media browser from
   * media_get_browser_params().
   *
   * @var array
   */
  protected $params;

  /**
   * Implements MediaBrowserPluginInterface::__construct().
   */
  public function __construct($info, $params) {
    $this->info = $info;
    $this->params = $params;
  }

  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    // Backwards compatible support for 'access callback' definitions.
    if (isset($this->info['access callback'])) {
      $access_callback = $this->info['access callback'];
      $access_arguments = isset($this->info['access arguments']) ? $this->info['access arguments'] : array();
      return function_exists($access_callback) && call_user_func_array($access_callback, $access_arguments);
    }

    return TRUE;
  }

  /**
   * Provide a render array to display the plugin in a media browser.
   *
   * This render array will be a jQuery tab in the media browser.
   *
   * Some elements are special:
   *  - #settings: Drupal.settings.media.browser.$key (where key is the array
   *    key).
   *  - #callback: If provided, will make the tab an "ajax" tab.
   *  - #title: If provided, will be used as the tab's title. Otherwise the
   *    'title' value from the plugin's hook_media_browser_plugin_info() will
   *    be used.
   *  - #weight: If provided, will be used to order the tabs between each other.
   *    A lower weight will be displayed first while a higher weight will be
   *    displayed later. If not provided, and there is a 'weight' value in the
   *    plugin's hook_media_browser_plugin_info() then it will be used,
   *    otherwise a default of 0 will be used.
   *  - form: If the plugin is to display a native Drupal form, then the output
   *    of drupal_get_form should be returned into the 'form' render key. If a
   *    form's callback isn't normally loaded, module_load_include() should be
   *    used to ensure that the form can be displayed.
   *
   * Example usage:
   * @code
   *   module_load_include('inc', 'mymodule', 'mymodule.pages');
   *   $build['#attached']['js'][] = drupal_get_path('module', 'mymodule') . '/js/mymodule.media.browser.js';
   *   $build['form'] = drupal_get_form('mymodule_media_form');
   *   return $build;
   * @endcode
   *
   * @return array
   *   Renderable array.
   */
  abstract public function view();
}
