<?php

/**
 * @file
 * Definition of views_plugin_display_attachment.
 */

/**
 * The plugin that handles an attachment display.
 *
 * Attachment displays are secondary displays that are 'attached' to a primary
 * display. Effectively they are a simple way to get multiple views within
 * the same view. They can share some information.
 *
 * @ingroup views_display_plugins
 */
class views_plugin_display_attachment extends views_plugin_display {

  /**
   * {@inheritdoc}
   */
  public function option_definition () {
    $options = parent::option_definition();

    $options['show_title'] = array('default' => FALSE, 'bool' => TRUE);
    $options['show_title_empty'] = array('default' => FALSE, 'bool' => TRUE);
    $options['displays'] = array('default' => array());
    $options['attachment_position'] = array('default' => 'before');
    $options['inherit_arguments'] = array('default' => TRUE, 'bool' => TRUE);
    $options['inherit_exposed_filters'] = array('default' => FALSE, 'bool' => TRUE);
    $options['inherit_pager'] = array('default' => FALSE, 'bool' => TRUE);
    $options['render_pager'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function execute() {
    return $this->view->render($this->display->id);
  }

  /**
   * {@inheritdoc}
   */
  public function attachment_positions($position = NULL) {
    $positions = array(
      'before' => t('Before'),
      'after' => t('After'),
      'both' => t('Both'),
    );

    if ($position) {
      return $positions[$position];
    }

    return $positions;
  }

  /**
   * Provide the summary for attachment options in the views UI.
   *
   * This output is returned as an array.
   */
  public function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here.
    parent::options_summary($categories, $options);

    $categories['attachment'] = array(
      'title' => t('Attachment settings'),
      'column' => 'second',
      'build' => array(
        '#weight' => -10,
      ),
    );

    $displays = array_filter($this->get_option('displays'));
    if (count($displays) > 1) {
      $attach_to = t('Multiple displays');
    }
    elseif (count($displays) == 1) {
      $display = array_shift($displays);
      if (!empty($this->view->display[$display])) {
        $attach_to = check_plain($this->view->display[$display]->display_title);
      }
    }

    if (!isset($attach_to)) {
      $attach_to = t('Not defined');
    }

    $options['show_title'] = array(
      'category' => 'title',
      'title' => t('Show title'),
      'value' => $this->get_option('show_title') ? t('Yes') : t('No'),
    );

    $options['show_title_empty'] = array(
      'category' => 'title',
      'title' => t('Show title even if view has no results'),
      'value' => $this->get_option('show_title_empty') ? t('Yes') : t('No'),
    );

    $options['displays'] = array(
      'category' => 'attachment',
      'title' => t('Attach to'),
      'value' => $attach_to,
    );

    $options['attachment_position'] = array(
      'category' => 'attachment',
      'title' => t('Attachment position'),
      'value' => $this->attachment_positions($this->get_option('attachment_position')),
    );

    $options['inherit_arguments'] = array(
      'category' => 'attachment',
      'title' => t('Inherit contextual filters'),
      'value' => $this->get_option('inherit_arguments') ? t('Yes') : t('No'),
    );

    $options['inherit_exposed_filters'] = array(
      'category' => 'attachment',
      'title' => t('Inherit exposed filters'),
      'value' => $this->get_option('inherit_exposed_filters') ? t('Yes') : t('No'),
    );

    $options['inherit_pager'] = array(
      'category' => 'pager',
      'title' => t('Inherit pager'),
      'value' => $this->get_option('inherit_pager') ? t('Yes') : t('No'),
    );

    $options['render_pager'] = array(
      'category' => 'pager',
      'title' => t('Render pager'),
      'value' => $this->get_option('render_pager') ? t('Yes') : t('No'),
    );

  }

  /**
   * Provide the default form for setting options.
   */
  public function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here.
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'show_title':
        $form['#title'] .= t('Title');
        $form['show_title'] = array(
          '#type' => 'checkbox',
          '#title' => t('Show title'),
          '#description' => t('Do you want to show the title of the attachment?'),
          '#default_value' => $this->get_option('show_title'),
        );
        break;
      case 'show_title_empty':
        $form['#title'] .= t('Title');
        $form['show_title_empty'] = array(
          '#type' => 'checkbox',
          '#title' => t('Show title for empty view'),
          '#description' => t('Do you want to show the title of the attachment even if the view has no results?'),
          '#default_value' => $this->get_option('show_title_empty'),
        );
        break;
      case 'inherit_arguments':
        $form['#title'] .= t('Inherit contextual filters');
        $form['inherit_arguments'] = array(
          '#type' => 'checkbox',
          '#title' => t('Inherit'),
          '#description' => t('Should this display inherit its contextual filter values from the parent display to which it is attached?'),
          '#default_value' => $this->get_option('inherit_arguments'),
        );
        break;

      case 'inherit_exposed_filters':
        $form['#title'] .= t('Inherit exposed filters');
        $form['inherit_exposed_filters'] = array(
          '#type' => 'checkbox',
          '#title' => t('Inherit'),
          '#description' => t('Should this display inherit its exposed filter values from the parent display to which it is attached?'),
          '#default_value' => $this->get_option('inherit_exposed_filters'),
        );
        break;

      case 'inherit_pager':
        $form['#title'] .= t('Inherit pager');
        $form['inherit_pager'] = array(
          '#type' => 'checkbox',
          '#title' => t('Inherit'),
          '#description' => t('Should this display inherit its paging values from the parent display to which it is attached?'),
          '#default_value' => $this->get_option('inherit_pager'),
        );
        break;

      case 'render_pager':
        $form['#title'] .= t('Render pager');
        $form['render_pager'] = array(
          '#type' => 'checkbox',
          '#title' => t('Render'),
          '#description' => t('Should this display render the pager values? This is only meaningful if inheriting a pager.'),
          '#default_value' => $this->get_option('render_pager'),
        );
        break;

      case 'attachment_position':
        $form['#title'] .= t('Position');
        $form['attachment_position'] = array(
          '#type' => 'radios',
          '#description' => t('Attach before or after the parent display?'),
          '#options' => $this->attachment_positions(),
          '#default_value' => $this->get_option('attachment_position'),
        );
        break;

      case 'displays':
        $form['#title'] .= t('Attach to');
        $displays = array();
        foreach ($this->view->display as $display_id => $display) {
          if (!empty($display->handler) && $display->handler->accept_attachments()) {
            $displays[$display_id] = $display->display_title;
          }
        }
        $form['displays'] = array(
          '#type' => 'checkboxes',
          '#description' => t('Select which display or displays this should attach to.'),
          '#options' => $displays,
          '#default_value' => $this->get_option('displays'),
        );
        break;
    }
  }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
  public function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here.
    parent::options_submit($form, $form_state);
    switch ($form_state['section']) {
      case 'show_title':
      case 'show_title_empty':
      case 'inherit_arguments':
      case 'inherit_pager':
      case 'render_pager':
      case 'inherit_exposed_filters':
      case 'attachment_position':
      case 'displays':
        $this->set_option($form_state['section'], $form_state['values'][$form_state['section']]);
        break;
    }
  }

  /**
   * Attach to another view.
   */
  public function attach_to($display_id) {
    $displays = $this->get_option('displays');

    if (empty($displays[$display_id])) {
      return;
    }

    if (!$this->access()) {
      return;
    }

    // Get a fresh view because our current one has a lot of stuff on it
    // because it's already been executed.
    $view = $this->view->clone_view();
    $view->original_args = $view->args;

    $args = $this->get_option('inherit_arguments') ? $this->view->args : array();
    $view->set_arguments($args);
    $exposed_input = $this->get_option('inherit_exposed_filters') && isset($this->view->exposed_input) ? $this->view->exposed_input : array();
    $view->set_exposed_input($exposed_input);
    $view->set_display($this->display->id);
    if ($this->get_option('inherit_pager')) {
      $view->display_handler->use_pager = $this->view->display[$display_id]->handler->use_pager();
      $view->display_handler->set_option('pager', $this->view->display[$display_id]->handler->get_option('pager'));
    }

    $attachment_output = $view->execute_display($this->display->id, $args);

    $attachment = '';
    if ($view->display_handler->get_option('show_title') && $view->display_handler->get_option('title')) {
      if ($view->display_handler->get_option('show_title_empty') || !empty($view->result)) {
        $attachment .= theme('html_tag', array(
          'element' => array(
            '#tag' => 'h2',
            '#value' => $view->display_handler->get_option('title'),
          ),
        ));
      }
    }
    $attachment .= $attachment_output;

    switch ($this->get_option('attachment_position')) {
      case 'before':
        $this->view->attachment_before .= $attachment;
        break;

      case 'after':
        $this->view->attachment_after .= $attachment;
        break;

      case 'both':
        $this->view->attachment_before .= $attachment;
        $this->view->attachment_after .= $attachment;
        break;
    }

    $view->destroy();
  }

  /**
   * Attachment displays only use exposed widgets if they are set to inherit
   * the exposed filter settings of their parent display.
   */
  public function uses_exposed() {
    if (!empty($this->options['inherit_exposed_filters']) && parent::uses_exposed()) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * If an attachment is set to inherit the exposed filter settings from its
   * parent display, then don't render and display a second set of exposed
   * filter widgets.
   */
  public function displays_exposed() {
    return $this->options['inherit_exposed_filters'] ? FALSE : TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function use_pager() {
    return !empty($this->use_pager);
  }

  /**
   * {@inheritdoc}
   */
  public function render_pager() {
    return !empty($this->use_pager) && $this->get_option('render_pager');
  }

}
