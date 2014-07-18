<?php

/**
 * @file
 * System display plugin.
 */

/**
 * Plugin to handle replacement of existing system paths.
 *
 * The System display is mostly identical to Views' native Page display. The
 * only differences are:
 * - No menu link options.
 * - No tab/local task options.
 * These options make no sense, because the System display is supposed to
 * replace the main page output of an existing system path only. This plugin
 * code should therefore always be kept in sync with the Page display plugin
 * code (excluding the support code for the removed functionality).
 *
 * @see views_plugin_display_page
 *
 * To achieve a correct replacement of an existing system path,
 * execute_hook_menu() performs some advanced processing on menu router
 * definitions to account for possible child router items that would normally
 * inherit properties of the original system path.
 *
 * @see views_plugin_display_system::execute_hook_menu()
 *
 * @ingroup views_display_plugins
 */
class views_plugin_display_system extends views_plugin_display {

  /**
   * The system display requires a path.
   */
  function has_path() {
    return TRUE;
  }

  /**
   * The system display uses breadcrumbs.
   */
  function uses_breadcrumb() {
    return TRUE;
  }

  /**
   * Overrides views_plugin_display::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['path'] = array(
      'default' => '',
    );

    // Override the access plugin to always enforce views_plugin_access_menu.
    // The UI widget for configuring access is additionally hidden.
    // @see options_summary()
    $options['defaults']['default']['access'] = FALSE;
    $options['access'] = array(
      'default' => array(
        'type' => 'menu',
      ),
    );

    return $options;
  }

  /**
   * Overrides views_plugin_display::options_summary().
   */
  function options_summary(&$categories, &$options) {
    parent::options_summary($categories, $options);

    $categories['system'] = array(
      'title' => t('System path settings'),
    );

    // Disable the access plugin configuration in the UI.
    // @see option_definition()
    $categories['access']['build']['#access'] = FALSE;

    $path = strip_tags('/' . $this->get_option('path'));
    if (empty($path)) {
      $path = t('None');
    }

    $options['path'] = array(
      'category' => 'system',
      'title' => t('Path'),
      'value' => views_ui_truncate($path, 24),
    );
  }

  /**
   * Overrides views_plugin_display::options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'path':
        $form['#title'] .= t('An existing menu path this view replaces');
        $form['path'] = array(
          '#type' => 'textfield',
          '#description' => t('This view replaces this path on your site. You may use "%" in your URL to represent values that will be used for contextual filters. For example: "node/%/feed".'),
          '#default_value' => $this->get_option('path'),
          '#field_prefix' => '<span dir="ltr">' . url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
          '#field_suffix' => '</span>&lrm;',
          '#attributes' => array('dir' => 'ltr'),
        );
        break;
    }
  }

  /**
   * Overrides views_plugin_display::options_validate().
   */
  function options_validate(&$form, &$form_state) {
    parent::options_validate($form, $form_state);

    switch ($form_state['section']) {
      case 'path':
        if (strpos($form_state['values']['path'], '$arg') !== FALSE) {
          form_error($form['path'], t('"$arg" is no longer supported. Use % instead.'));
        }

        if (strpos($form_state['values']['path'], '%') === 0) {
          form_error($form['path'], t('"%" may not be used for the first segment of a path.'));
        }
        // Automatically remove '/' from path.
        $form_state['values']['path'] = trim($form_state['values']['path'], '/');
        break;
    }
  }

  /**
   * Overrides views_plugin_display::options_submit().
   */
  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);

    switch ($form_state['section']) {
      case 'path':
        $this->set_option('path', $form_state['values']['path']);
        break;
    }
  }

  /**
   * Add this display's path information to Drupal's menu system.
   *
   * @param array $callbacks
   *   All existing menu router items defined by modules. Taken by reference, in
   *   order to adjust any possibly existing child router items of the replaced
   *   system path. (This method only returns new router items normally.)
   */
  function execute_hook_menu(&$callbacks) {
    $items = array();

    // Replace % with the link to our standard views argument loader
    // views_arg_load().
    $bits = explode('/', $this->get_option('path'));
    $page_arguments = array($this->view->name, $this->display->id);
    $this->view->init_handlers();
    $view_arguments = $this->view->argument;

    // Replace % with %views_arg for menu autoloading and add to the
    // page arguments so the argument actually comes through.
    foreach ($bits as $pos => $bit) {
      if ($bit == '%') {
        $argument = array_shift($view_arguments);
        if (!empty($argument->options['specify_validation']) && $argument->options['validate']['type'] != 'none') {
          $bits[$pos] = '%views_arg';
        }
        $page_arguments[] = $pos;
      }
    }

    $path = implode('/', $bits);
    if (!$path) {
      return $items;
    }

    // Only existing system paths can be replaced.
    if (!isset($callbacks[$path])) {
      // However, if the specified path contains dynamic argument placeholders,
      // then we need to search more carefully.
      $views_path = $this->get_option('path');
      if (strpos($views_path, '%') !== FALSE) {
        $views_path = preg_quote($views_path, '@');
        $views_path = strtr($views_path, array('%' => '%[^/]*'));
        $result = preg_grep('@^' . $views_path . '$@', array_keys($callbacks));
        if ($result) {
          $parent_path = reset($result);
          $parent = &$callbacks[$parent_path];
        }
        else {
          return $items;
        }
      }
      // No dynamic placeholders found, so nothing can be replaced.
      else {
        return $items;
      }
    }
    else {
      $parent = &$callbacks[$path];
    }

    // Work out whether we need to get the access callback and arguments from
    // the parent item.
    $default_map = array(
      'access callback' => 'user_access',
      'access arguments' => array(),
    );

    foreach ($default_map as $menu_key => &$default) {
      // Override the default if we can. Otherwise this will use the defaults
      // above.
      if (!empty($callbacks[$path][$menu_key])) {
        $default = $callbacks[$path][$menu_key];
      }
      elseif (!empty($parent[$menu_key])) {
        $default = $parent[$menu_key];
      }
    }

    $items[$path] = array(
      // default views page entry
      'page callback' => 'views_page',
      'page arguments' => $page_arguments,
      // Take over the access definition from the original router item.
      // @see option_definition()
      // @see views_plugin_access_menu
      'access callback' => $default_map['access callback'],
      'access arguments' => $default_map['access arguments'],
      // Identify URL embedded arguments and correlate them to a handler
      'load arguments' => array($this->view->name, $this->display->id, '%index'),
    );

    // List of router item default property values, which are inherited to
    // children. These default values are only applied if the original parent
    // item does not define them (see below).
    // @see _menu_router_build()
    $defaults = array(
      'access callback' => 'user_access',
      'menu_name' => NULL,
      'file' => NULL,
      'file path' => NULL,
      'delivery callback' => NULL,
      'theme callback' => NULL,
      'theme arguments' => array(),
    );

    // Grep all router items below the target path.
    $num_parent_parts = count(explode('/', $path));
    $children = preg_grep('@^' . preg_quote($path, '@') . '/@', array_keys($callbacks));

    // Ensure correct inheritance of properties on the original parent path
    // (being replaced) to child items.
    foreach ($children as $child_path) {
      // Only apply property inheritance to direct children of the parent path.
      $num_child_parts = count(explode('/', $child_path));
      if ($num_parent_parts == $num_child_parts - 1) {
        // Check if the child router item is a views page. If so, there are
        // default properties we do not want this item to inherit.
        if (isset($callbacks[$child_path]['page callback']) && ($callbacks[$child_path]['page callback'] === 'views_page')) {
          continue;
        }
        $child = &$callbacks[$child_path];
        // Get this first, as we want to know if this existed before parent and
        // default values are merged.
        $file = isset($child['file']);
        // Copy all properties from the original parent that will be replaced
        // with new values.
        // This typically resets 'access arguments', etc.
        $child += array_intersect_key($parent, $items[$path]);
        // Copy all properties from the original parent, for which the router
        // system would inherit parent values or fill in default values.
        // This typically adds back 'file' and other properties defined on the
        // parent but not on $items[$path]. (The two operations could be
        // combined with $items[$path] + $defaults, but are separated for
        // documentation purposes and clarity.)
        $child += array_intersect_key($parent, $defaults);
        // Unset the child 'file' property if its implementing module doesn't
        // match it's parent and it didn't have a 'file' preoperty specified
        // before. Otherwise, for example, example_module could inherit a 'file'
        // property of 'node.admin.inc', so the actual include path would be
        // something like .../modules/example_module/node.admin.inc.
        if (!$file && isset($child['module'], $parent['module']) && ($child['module'] != $parent['module'])) {
          unset($child['file']);
        }
        // Last catch-22, insert new default properties and their default values
        // for the child, which may not be defined on the original parent.
        // This typically inserts 'access callback', which can be omitted in
        // router item definitions and only gets a default of user_access() in
        // the final _menu_router_build(). Without this, the new access callback
        // views_access() in $items[$path] would be inherited to all children.
        $child += $defaults;
      }
    }

    // If the original parent path already existed, copy over its remaining
    // properties.
    $items[$path] += $parent;

    return $items;
  }

  /**
   * Overrides views_plugin_display::execute().
   *
   * Build and render the page view.
   *
   * Since we replace an existing page, we need to invoke views_set_page_view().
   * Also set the page title, because original page callbacks might do this.
   */
  function execute() {
    // Let the world know that this is the page view we're using.
    views_set_page_view($this->view);

    // Prior to this being called, the $view should already be set to this
    // display, and arguments should be set on the view.
    $this->view->build();
    if (!empty($this->view->build_info['fail'])) {
      return drupal_not_found();
    }

    if (!empty($this->view->build_info['denied'])) {
      return drupal_access_denied();
    }

    drupal_add_css(drupal_get_path('module', 'admin_views') . '/admin_views.css');

    return $this->view->render();
  }

  /**
   * Overrides views_plugin_display::get_argument_text().
   */
  function get_argument_text() {
    return array(
      'filter value not present' => t('When the filter value is <em>NOT</em> in the URL'),
      'filter value present' => t('When the filter value <em>IS</em> in the URL or a default is provided'),
      'description' => t('The contextual filter values is provided by the URL.'),
    );
  }

}
