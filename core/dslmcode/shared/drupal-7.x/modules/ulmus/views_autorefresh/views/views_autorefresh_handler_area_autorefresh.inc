<?php

/**
 * Base class for area handlers.
 *
 * @ingroup views_area_handlers
 */
class views_autorefresh_handler_area_autorefresh extends views_handler_area {

  /**
   * Overrides views_handler_area::init().
   *
   * Reset override done in views_handler_area::init(). This area must be
   * rendered even if view has no results.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['interval'] = array('default' => '');
    $options['nodejs'] = array('default' => FALSE, 'bool' => TRUE);
    $options['incremental'] = array('default' => FALSE, 'bool' => TRUE);
    $options['display'] = array('default' => '');

    $options['incremental_advanced'] = array(
      'contains' => array(
        'sourceSelector' => array('default' => '.view-content'),
        'targetSelector' => array('default' => '.view-content'),
        'emptySelector' => array('default' => '.view-empty'),
        'afterSelector' => array('default' => '.view-header'),
        'targetStructure' => array('default' => '<div class="view-content"></div>'),
        'firstClass' => array('default' => 'views-row-first'),
        'lastClass' => array('default' => 'views-row-last'),
        'oddClass' => array('default' => 'views-row-odd'),
        'evenClass' => array('default' => 'views-row-even'),
        'rowClassPrefix' => array('default' => 'views-row-'),
      )
    );

    $options['ping'] = array('default' => FALSE, 'bool' => TRUE);
    $options['ping_base_path'] = array('default' => '');
    $options['ping_arguments'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    if (module_exists('nodejs')) {
      $form['nodejs'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use Node.js to refresh the view instead of interval pings'),
        '#default_value' => $this->options['nodejs'],
      );
    }
    else {
      $form['nodejs'] = array(
        '#type' => 'value',
        '#value' => FALSE,
      );
    }
    $form['interval'] = array(
      '#type' => 'textfield',
      '#title' => t('Interval to check for new items'),
      '#default_value' => $this->options['interval'],
      '#field_suffix' => 'milliseconds',
      '#required' => TRUE,
      '#dependency' => array(
        'edit-options-nodejs' => array(0),
      ),
    );
    $form['incremental'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use a secondary view display to incrementally insert new items only'),
      '#default_value' => $this->options['incremental'],
    );
    $options = array();
    foreach ($this->view->display as $display) {
      if ($display->display_plugin == 'page') {
        // TODO: check secondary display arguments.
        $options[$display->id] = $display->display_title;
      }
    }
    $form['display'] = array(
      '#type' => 'select',
      '#title' => t('Secondary display'),
      '#default_value' => $this->options['display'],
      '#description' => t('Only displays of type page are eligible. Additionally the display must have a timestamp argument of the <em>(with operator)</em> variant. For example <em>Node: Post date (with operator)</em>.'),
      '#options' => $options,
      '#dependency' => array(
        'edit-options-incremental' => array(1),
      ),
    );
    $form['incremental_advanced'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#dependency' => array(
        'edit-options-incremental' => array(1),
      ),
      '#description' => t('Advanced settings for incremental display. Unless your view is using an overridden template, the defaults below should be fine.'),
    );
    $form['incremental_advanced']['sourceSelector'] = array(
      '#type' => 'textfield',
      '#title' => t('Source selector'),
      '#default_value' => $this->options['incremental_advanced']['sourceSelector'],
      '#description' => t('A jQuery selector expression representing the main view container of your secondary display.'),
    );
    $form['incremental_advanced']['targetSelector'] = array(
      '#type' => 'textfield',
      '#title' => t('Target selector'),
      '#default_value' => $this->options['incremental_advanced']['targetSelector'],
      '#description' => t('A jQuery selector expression representing the main view container of your primary display.'),
    );
    $form['incremental_advanced']['emptySelector'] = array(
      '#type' => 'textfield',
      '#title' => t('Empty selector'),
      '#default_value' => $this->options['incremental_advanced']['emptySelector'],
      '#description' => t('A jQuery selector expression representing the main view container in case of empty results.'),
    );
    $form['incremental_advanced']['afterSelector'] = array(
      '#type' => 'textfield',
      '#title' => t('Header selector'),
      '#default_value' => $this->options['incremental_advanced']['afterSelector'],
      '#description' => t('A jQuery selector expression representing the view header, in case the header is displayed with empty results.'),
    );
    $form['incremental_advanced']['targetStructure'] = array(
      '#type' => 'textfield',
      '#title' => t('Target structure'),
      '#default_value' => $this->options['incremental_advanced']['targetStructure'],
      '#description' => t('An HTML fragment describing the view skeleton in case of empty results.'),
    );
    $form['incremental_advanced']['firstClass'] = array(
      '#type' => 'textfield',
      '#title' => t('First row class'),
      '#default_value' => $this->options['incremental_advanced']['firstClass'],
      '#description' => t('A class to be added to the first result row.'),
    );
    $form['incremental_advanced']['lastClass'] = array(
      '#type' => 'textfield',
      '#title' => t('Last row class'),
      '#default_value' => $this->options['incremental_advanced']['lastClass'],
      '#description' => t('A class to be added to the last result row.'),
    );
    $form['incremental_advanced']['oddClass'] = array(
      '#type' => 'textfield',
      '#title' => t('Odd rows class'),
      '#default_value' => $this->options['incremental_advanced']['oddClass'],
      '#description' => t('A class to be added to each odd result row.'),
    );
    $form['incremental_advanced']['evenClass'] = array(
      '#type' => 'textfield',
      '#title' => t('Even rows class'),
      '#default_value' => $this->options['incremental_advanced']['evenClass'],
      '#description' => t('A class to be added to each even result row.'),
    );
    $form['incremental_advanced']['rowClassPrefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Row class prefix'),
      '#default_value' => $this->options['incremental_advanced']['rowClassPrefix'],
      '#description' => t('The prefix of a class to be added to each result row. The row number will be appended to this prefix.'),
    );
    $form['ping'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use a ping url'),
      '#default_value' => $this->options['ping'],
      '#description' => t('Use a custom script for faster check of new items. See <code>ping.php.example</code> in <code>views_autorefresh</code> folder for reference.'),
    );
    $form['ping_base_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path to the ping script'),
      '#default_value' => $this->options['ping_base_path'],
      '#description' => t('This path is relative to the Drupal root.'),
      '#dependency' => array(
        'edit-options-ping' => array(1),
      ),
    );
    $form['ping_arguments'] = array(
      '#type' => 'textarea',
      '#title' => t('Ping arguments'),
      '#default_value' => $this->options['ping_arguments'],
      '#description' => t('A PHP script that generates arguments that will be sent on the ping URL as query parameters. Do not surround with <code>&lt;?php&gt;</code> tag.'),
      '#dependency' => array(
        'edit-options-ping' => array(1),
      ),
    );
  }

  function options_validate(&$form, &$form_state) {
    if (!is_numeric($form_state['values']['options']['interval'])) {
      form_set_error('interval', t('Invalid interval.'));
    }
    if ($form_state['values']['options']['ping']) {
      $ping_base_path = DRUPAL_ROOT . '/' . $form_state['values']['options']['ping_base_path'];
      if (!file_exists($ping_base_path)) {
        form_set_error('ping_base_path', t('Ping script not found at %path.', array('%path' => $ping_base_path)));
      }
      $args = $this->eval_ping_arguments($form_state['values']['options']['ping_arguments']);
      if (!is_array($args)) {
        form_set_error('ping_arguments', t('Error in ping arguments script: %error', array('%error' => $args)));
      }
    }
  }

  function options_submit(&$form, &$form_state) {
    $this->view->display_handler->set_option('use_ajax', TRUE);
  }

  function render($empty = FALSE) {
    $args = array();
    $args['view'] = $this->view;
    $args['nodejs'] = !empty($this->options['nodejs']);
    $args['interval'] = $this->options['interval'];
    if ($this->options['ping']) {
      $args['ping'] = array(
        'ping_base_path' => $this->options['ping_base_path'],
        'ping_args' => $this->eval_ping_arguments($this->options['ping_arguments']),
      );
    }
    if ($this->options['incremental']) {
      $display = $this->view->display[$this->options['display']];

      $args['incremental'] = array(
        'view_base_path' => $display->display_options['path'],
        'view_display_id' => $display->id,
        'view_name' => $this->view->name,
        'sourceSelector' => $this->options['incremental_advanced']['sourceSelector'],
        'targetSelector' => $this->options['incremental_advanced']['targetSelector'],
        'emptySelector' => $this->options['incremental_advanced']['emptySelector'],
        'afterSelector' => $this->options['incremental_advanced']['afterSelector'],
        'targetStructure' => $this->options['incremental_advanced']['targetStructure'],
        'firstClass' => $this->options['incremental_advanced']['firstClass'],
        'lastClass' => $this->options['incremental_advanced']['lastClass'],
        'oddClass' => $this->options['incremental_advanced']['oddClass'],
        'evenClass' => $this->options['incremental_advanced']['evenClass'],
        'rowClassPrefix' => $this->options['incremental_advanced']['rowClassPrefix'],
      );
    }

    return theme('views_autorefresh', $args);
  }

  function eval_ping_arguments($script) {
    $args = array();
    if (empty($script)) return $args;

    // Make view visible to script.
    $view = $this->view;

    // Avoid Drupal's error handler: http://www.php.net/manual/en/function.restore-error-handler.php#93261
    set_error_handler(create_function('$errno,$errstr', 'return false;'));
    $return = eval($script);
    if ($return === FALSE) {
      $error = error_get_last();
      $args = $error['message'];
    }
    else if (is_array($return)) {
      $args = $return;
    }
    else {
      $args = t('expecting an array of arguments, got a !type instead.', array('!type' => gettype($return)));
    }
    restore_error_handler();
    return $args;
  }
}
