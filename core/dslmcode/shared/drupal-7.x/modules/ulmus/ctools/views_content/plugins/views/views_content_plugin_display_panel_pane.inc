<?php

/**
 * The plugin that handles a panel_pane.
 */
class views_content_plugin_display_panel_pane extends views_plugin_display {
  /**
   * If this variable is true, this display counts as a panel pane. We use
   * this variable so that other modules can create alternate pane displays.
   */
  var $panel_pane_display = TRUE;
  var $has_pane_conf = NULL;

  function option_definition() {
    $options = parent::option_definition();

    $options['pane_title'] = array('default' => '', 'translatable' => TRUE);
    $options['pane_description'] = array('default' => '', 'translatable' => TRUE);
    $options['pane_category'] = array(
      'contains' => array(
        'name' => array('default' => 'View panes', 'translatable' => TRUE),
        'weight' => array('default' => 0),
      ),
    );

    $options['allow'] = array(
      'contains' => array(
        'use_pager'       => array('default' => FALSE),
        'items_per_page'  => array('default' => FALSE),
        'offset'          => array('default' => FALSE),
        'link_to_view'    => array('default' => FALSE),
        'more_link'       => array('default' => FALSE),
        'path_override'   => array('default' => FALSE),
        'title_override'  => array('default' => FALSE),
        'exposed_form'    => array('default' => FALSE),
        'fields_override' => array('default' => FALSE),
       ),
    );

    $options['argument_input'] = array('default' => array());
    $options['link_to_view'] = array('default' => 0);
    $options['inherit_panels_path'] = array('default' => 0);

    return $options;
  }

  function has_pane_conf() {
    return isset($this->has_pane_conf);
  }

  function set_pane_conf($conf = array(), $set_cache = TRUE) {
    $this->set_option('pane_conf', $conf);
    $this->view->dom_id = !empty($this->view->dom_id) ? $this->view->dom_id : md5($this->view->name . REQUEST_TIME . rand());
    if ($set_cache) {
      cache_set('view_panel_pane_' . $this->view->dom_id, $conf);
    }
    $this->has_pane_conf = TRUE;
  }

  /**
   * Provide the summary for page options in the views UI.
   *
   * This output is returned as an array.
   */
  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);

    $categories['panel_pane'] = array(
      'title' => t('Pane settings'),
      'column' => 'second',
      'build' => array(
        '#weight' => -10,
      ),
    );

    $pane_title = $this->get_option('pane_title');
    if (empty($pane_title)) {
      $pane_title = t('Use view name');
    }

    if (drupal_strlen($pane_title) > 16) {
      $pane_title = drupal_substr($pane_title, 0, 16) . '...';
    }

    $options['pane_title'] = array(
      'category' => 'panel_pane',
      'title' => t('Admin title'),
      'value' => $pane_title,
    );

    $pane_description = $this->get_option('pane_description');
    if (empty($pane_description)) {
      $pane_description = t('Use view description');
    }

    if (drupal_strlen($pane_description) > 16) {
      $pane_description = drupal_substr($pane_description, 0, 16) . '...';
    }

    $options['pane_description'] = array(
      'category' => 'panel_pane',
      'title' => t('Admin desc'),
      'value' => $pane_description,
    );

    $category = $this->get_option('pane_category');
    $pane_category = $category['name'];
    if (empty($pane_category)) {
      $pane_category = t('View panes');
    }

    if (drupal_strlen($pane_category) > 16) {
      $pane_category = drupal_substr($pane_category, 0, 16) . '...';
    }

    $options['pane_category'] = array(
      'category' => 'panel_pane',
      'title' => t('Category'),
      'value' => $pane_category,
    );

    $options['link_to_view'] = array(
      'category' => 'panel_pane',
      'title' => t('Link to view'),
      'value' => $this->get_option('link_to_view') ? t('Yes') : t('No'),
    );

    $options['inherit_panels_path'] = array(
      'category' => 'panel_pane',
      'title' => t('Use Panel path'),
      'value' => $this->get_option('inherit_panels_path') ? t('Yes') : t('No'),
    );

    $options['argument_input'] = array(
      'category' => 'panel_pane',
      'title' => t('Argument input'),
      'value' => t('Edit'),
    );

    $allow = $this->get_option('allow');
    $filtered_allow = array_filter($allow);

    $options['allow'] = array(
      'category' => 'panel_pane',
      'title' => t('Allow settings'),
      'value' => empty($filtered_allow) ? t('None') : ($allow === $filtered_allow ? t('All') : t('Some')),
    );
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'allow':
        $form['#title'] .= t('Allow settings');
        $form['description'] = array(
          '#value' => '<div class="form-item description">' . t('Checked settings will be available in the panel pane config dialog for modification by the panels user. Unchecked settings will not be available and will only use the settings in this display.') . '</div>',
        );

        $options = array(
          'use_pager' => t('Use pager'),
          'items_per_page' => t('Items per page'),
          'offset' => t('Pager offset'),
          'link_to_view' => t('Link to view'),
          'more_link' => t('More link'),
          'path_override' => t('Path override'),
          'title_override' => t('Title override'),
          'exposed_form' => t('Use exposed widgets form as pane configuration'),
          'fields_override' => t('Fields override'),
        );

        $allow = array_filter($this->get_option('allow'));
        $form['allow'] = array(
          '#type' => 'checkboxes',
          '#default_value' => $allow,
          '#options' => $options,
        );
        break;
      case 'pane_title':
        $form['#title'] .= t('Administrative title');

        $form['pane_title'] = array(
          '#type' => 'textfield',
          '#default_value' => $this->get_option('pane_title'),
          '#description' => t('This is the title that will appear for this view pane in the add content dialog. If left blank, the view name will be used.'),
        );
        break;

      case 'pane_description':
        $form['#title'] .= t('Administrative description');

        $form['pane_description'] = array(
          '#type' => 'textfield',
          '#default_value' => $this->get_option('pane_description'),
          '#description' => t('This is text that will be displayed when the user mouses over the pane in the add content dialog. If blank the view description will be used.'),
        );
        break;

      case 'pane_category':
        $form['#title'] .= t('Administrative description');

        $cat = $this->get_option('pane_category');
        $form['pane_category']['#tree'] = TRUE;
        $form['pane_category']['name'] = array(
          '#type' => 'textfield',
          '#default_value' => $cat['name'],
          '#description' => t('This is category the pane will appear in on the add content dialog.'),
        );
        $form['pane_category']['weight'] = array(
          '#title' => t('Weight'),
          '#type' => 'textfield',
          '#default_value' => $cat['weight'],
          '#description' => t('This is the default weight of the category. Note that if the weight of a category is defined in multiple places, only the first one Panels sees will get that definition, so if the weight does not appear to be working, check other places that the weight might be set.'),
        );
        break;

      case 'link_to_view':
        $form['#title'] .= t('Link pane title to view');

        $form['link_to_view'] = array(
          '#type' => 'select',
          '#options' => array(1 => t('Yes'), 0 => t('No')),
          '#default_value' => $this->get_option('link_to_view'),
        );
        break;

      case 'inherit_panels_path':
        $form['#title'] .= t('Inherit path from panel display');

        $form['inherit_panels_path'] = array(
          '#type' => 'select',
          '#options' => array(1 => t('Yes'), 0 => t('No')),
          '#default_value' => $this->get_option('inherit_panels_path'),
          '#description' => t('If yes, all links generated by Views, such as more links, summary links, and exposed input links will go to the panels display path, not the view, if the display has a path.'),
        );
        break;

      case 'argument_input':
        $form['#title'] .= t('Choose the data source for view arguments');
        $argument_input = $this->get_argument_input();
        ctools_include('context');
        ctools_include('dependent');
        $form['argument_input']['#tree'] = TRUE;

        $converters = ctools_context_get_all_converters();
        ksort($converters);

        foreach ($argument_input as $id => $argument) {
          $form['argument_input'][$id] = array(
            '#tree' => TRUE,
          );

          $safe = str_replace(array('][', '_', ' '), '-', $id);
          $type_id = 'edit-argument-input-' . $safe;

          $form['argument_input'][$id]['type'] = array(
            '#type' => 'select',
            '#options' => array(
              'none' => t('No argument'),
              'wildcard' => t('Argument wildcard'),
              'context' => t('From context'),
              'panel' => t('From panel argument'),
              'fixed' => t('Fixed'),
              'user' => t('Input on pane config'),
            ),
            '#id' => $type_id,
            '#title' => t('@arg source', array('@arg' => $argument['name'])),
            '#default_value' => $argument['type'],
          );
          $form['argument_input'][$id]['context'] = array(
            '#type' => 'select',
            '#title' => t('Required context'),
            '#description' => t('If "From context" is selected, which type of context to use.'),
            '#default_value' => $argument['context'],
            '#options' => $converters,
            '#dependency' => array($type_id => array('context')),
          );

          $form['argument_input'][$id]['context_optional'] = array(
            '#type' => 'checkbox',
            '#title' => t('Context is optional'),
            '#description' => t('This context need not be present for the pane to function. If you plan to use this, ensure that the argument handler can handle empty values gracefully.'),
            '#default_value' => $argument['context_optional'],
            '#dependency' => array($type_id => array('context')),
          );

          $form['argument_input'][$id]['panel'] = array(
            '#type' => 'select',
            '#title' => t('Panel argument'),
            '#description' => t('If "From panel argument" is selected, which panel argument to use.'),
            '#default_value' => $argument['panel'],
            '#options' => array(0 => t('First'), 1 => t('Second'), 2 => t('Third'), 3 => t('Fourth'), 4 => t('Fifth'), 5 => t('Sixth')),
            '#dependency' => array($type_id => array('panel')),
          );

          $form['argument_input'][$id]['fixed'] = array(
            '#type' => 'textfield',
            '#title' => t('Fixed argument'),
            '#description' => t('If "Fixed" is selected, what to use as an argument.'),
            '#default_value' => $argument['fixed'],
            '#dependency' => array($type_id => array('fixed')),
          );

          $form['argument_input'][$id]['label'] = array(
            '#type' => 'textfield',
            '#title' => t('Label'),
            '#description' => t('If this argument is presented to the panels user, what label to apply to it.'),
            '#default_value' => empty($argument['label']) ? $argument['name'] : $argument['label'],
            '#dependency' => array($type_id => array('user')),
          );
        }
        break;
    }
  }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
  function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);
    switch ($form_state['section']) {
      case 'allow':
      case 'argument_input':
      case 'link_to_view':
      case 'inherit_panels_path':
      case 'pane_title':
      case 'pane_description':
      case 'pane_category':
        $this->set_option($form_state['section'], $form_state['values'][$form_state['section']]);
        break;
    }
  }

  /**
   * Adjust the array of argument input to match the current list of
   * arguments available for this display. This ensures that changing
   * the arguments doesn't cause the argument input field to just
   * break.
   */
  function get_argument_input() {
    $arguments = $this->get_option('argument_input');
    $handlers = $this->get_handlers('argument');

    // We use a separate output so as to seamlessly discard info for
    // arguments that no longer exist.
    $output = array();

    foreach ($handlers as $id => $handler) {
      if (empty($arguments[$id])) {
        $output[$id] = array(
          'type' => 'none',
          'context' => 'any',
          'context_optional' => FALSE,
          'panel' => 0,
          'fixed' => '',
          'name' => $handler->ui_name(),
        );
      }
      else {
        $output[$id] = $arguments[$id];
        $output[$id]['name'] = $handler->ui_name();
      }
    }

    return $output;
  }

  function use_more() {
    $allow = $this->get_option('allow');
    if (!$allow['more_link'] || !$this->has_pane_conf()) {
      return parent::use_more();
    }
    $conf = $this->get_option('pane_conf');
    return (bool) $conf['more_link'];
  }

  function get_path() {
    if (empty($this->view->override_path)) {
      return parent::get_path();
    }
    return $this->view->override_path;
  }

  function get_url() {
    if ($this->get_option('inherit_panels_path')) {
      return $this->get_path();
    }
    return parent::get_url();
  }

  function uses_exposed_form_in_block() {
    // We'll always allow the exposed form in a block, regardless of path.
    return TRUE;
  }

  /**
   * Determine if this display should display the exposed
   * filters widgets, so the view will know whether or not
   * to render them.
   *
   * Regardless of what this function
   * returns, exposed filters will not be used nor
   * displayed unless uses_exposed() returns TRUE.
   */
  function displays_exposed() {
    $conf = $this->get_option('allow');
    // If this is set, the exposed form is part of pane configuration, not
    // rendered normally.
    return empty($conf['exposed_form']);
  }

  /**
   * Set the pane configuration options
   * Done here in handler for reuse between views_content_views_panes_content_type_render
   * and views_content_views_pre_view
   */
  function pane_process_conf() {
    ctools_include('context');
    $conf = $this->get_option('pane_conf');
    if (!$conf) {
      // See if dom id has been cached and get conf from there.
      if (!empty($this->view->dom_id) && ($cache = cache_get('view_panel_pane_' . $this->view->dom_id))) {
        $conf = $cache->data;
      }
      if (!$conf) {
        return;
      }
      $this->set_pane_conf($conf);
    }
    $contexts = $conf['pane_contexts'];
    $panel_args = $conf['panel_args'];
    $args = array();
    $arguments = $this->get_option('arguments');

    $context_keys = isset($conf['context']) ? $conf['context'] : array();
    foreach ($this->get_argument_input() as $id => $argument) {
      switch ($argument['type']) {
        case 'context':
          $key = array_shift($context_keys);
          if (isset($contexts[$key])) {
            if (strpos($argument['context'], '.')) {
              list($context, $converter) = explode('.', $argument['context'], 2);
              $args[] = ctools_context_convert_context($contexts[$key], $converter, array('sanitize' => FALSE));
            }
            else {
              $args[] = $contexts[$key]->argument;
            }
          }
          else {
            $args[] = isset($arguments[$id]['exception']['value']) ? $arguments[$id]['exception']['value'] : 'all';
          }
          break;

        case 'fixed':
          $args[] = $argument['fixed'];
          break;

        case 'panel':
          $args[] = isset($panel_args[$argument['panel']]) ? $panel_args[$argument['panel']] : NULL;
          break;

        case 'user':
          $args[] = (isset($conf['arguments'][$id])  && $conf['arguments'][$id] !== '') ? ctools_context_keyword_substitute($conf['arguments'][$id], array(), $contexts) : NULL;
          break;

       case 'wildcard':
          // Put in the wildcard.
         $args[] = isset($arguments[$id]['wildcard']) ? $arguments[$id]['wildcard'] : '*';
         break;

       case 'none':
       default:
         // Put in NULL.
         // views.module knows what to do with NULL (or missing) arguments
         $args[] = NULL;
         break;
      }
    }

    // remove any trailing NULL arguments as these are non-args:
    while (count($args) && end($args) === NULL) {
      array_pop($args);
    }

    $this->view->set_arguments($args);
    $allow = $this->get_option('allow');

    if (!empty($conf['path'])) {
      $conf['path'] = ctools_context_keyword_substitute($conf['path'], array(), $contexts);
    }
    if ($allow['path_override'] && !empty($conf['path'])) {
      $this->view->override_path = $conf['path'];
    }
    else if ($path = $this->get_option('inherit_panels_path')) {
      $this->view->override_path = $_GET['q'];
    }

    // more link
    if ($allow['more_link']) {
      if (empty($conf['more_link'])) {
        $this->set_option('use_more', FALSE);
      }
      else {
        $this->set_option('use_more', TRUE);
        // make sure the view runs the count query so we know whether or not the
        // more link applies.
        $this->view->get_total_rows = TRUE;
      }
    }

    if ($allow['items_per_page'] && isset($conf['items_per_page'])) {
      $this->view->set_items_per_page($conf['items_per_page']);
    }

    if ($allow['offset']) {
      $this->view->set_offset($conf['offset']);
    }

    if ($allow['use_pager']) {
      // Only set use_pager if they differ, this way we can avoid overwriting the
      // pager type that Views uses.
      $pager = $this->get_option('pager');
      if ($conf['use_pager'] && ($pager['type'] == 'none' || $pager['type'] == 'some')) {
        $pager['type'] = 'full';
      }
      elseif (!$conf['use_pager'] && $pager['type'] != 'none' && $pager['type'] != 'some') {
        $pager['type'] = $this->view->get_items_per_page() || !empty($pager['options']['items_per_page']) ? 'some' : 'none';
      }

      if ($conf['use_pager']) {
        if (!isset($pager['options']['id']) || (isset($conf['pager_id']) && $pager['options']['id'] != $conf['pager_id'])) {
          $pager['options']['id'] = (int) $conf['pager_id'];
        }
      }

      $this->set_option('pager', $pager);
    }

    if ($allow['fields_override']) {
      if ($conf['fields_override']) {
        $fields = $this->view->get_items('field');
        foreach ($fields as $field => $field_display) {
          $fields[$field]['exclude'] = empty($conf['fields_override'][$field]);
        }
        $this->set_option('fields', $fields);

      }
    }

    if ($allow['exposed_form'] && !empty($conf['exposed'])) {
      foreach ($conf['exposed'] as $filter_name => $filter_value) {
        if (!is_array($filter_value)) {
          $conf['exposed'][$filter_name] = ctools_context_keyword_substitute($filter_value, array(), $contexts);
        }
      }
      $this->view->set_exposed_input($conf['exposed']);
    }
  }

}

