<?php

/**
 * @file
 * Definition of views_handler_area and views_handler_area_broken.
 */

/**
 * @defgroup views_area_handlers Views area handlers
 * @{
 * Handlers to tell Views what can display in header, footer
 * and empty text in a view.
 */

/**
 * Base class for area handlers.
 *
 * @ingroup views_area_handlers
 */
class views_handler_area extends views_handler {

  /**
   * {@inheritdoc}
   */
  public function init(&$view, &$options) {
    parent::init($view, $options);
    // Make sure that no result area handlers are set to be shown when the
    // result is empty.
    if ($this->handler_type == 'empty') {
      $this->options['empty'] = TRUE;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function label() {
    if (!isset($this->options['label'])) {
      return $this->ui_name();
    }
    return $this->options['label'];
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $this->definition['field'] = !empty($this->definition['field']) ? $this->definition['field'] : '';
    $label = !empty($this->definition['label']) ? $this->definition['label'] : $this->definition['field'];
    $options['label'] = array('default' => $label, 'translatable' => TRUE);
    $options['empty'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  /**
   * Provide extra data to the administration form.
   */
  public function admin_summary() {
    return $this->label();
  }

  /**
   * Default options form that provides the label widget that all fields should
   * have.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#default_value' => isset($this->options['label']) ? $this->options['label'] : '',
      '#description' => t('The label for this area that will be displayed only administratively.'),
    );

    if ($form_state['type'] != 'empty') {
      $form['empty'] = array(
        '#type' => 'checkbox',
        '#title' => t('Display even if view has no result'),
        '#default_value' => isset($this->options['empty']) ? $this->options['empty'] : 0,
      );
    }
  }

  /**
   * Don't run a query.
   */
  public function query() {
  }

  /**
   * Render the area.
   */
  public function render($empty = FALSE) {
    return '';
  }

  /**
   * Area handlers shouldn't have groupby.
   */
  public function use_group_by() {
    return FALSE;
  }

}

/**
 * A special handler to take the place of missing or broken handlers.
 *
 * @ingroup views_area_handlers
 */
class views_handler_area_broken extends views_handler_area {

  /**
   * {@inheritdoc}
   */
  public function ui_name($short = FALSE) {
    return t('Broken/missing handler');
  }

  /**
   * {@inheritdoc}
   */
  public function ensure_my_table() {
    // No table to ensure!
  }

  /**
   * {@inheritdoc}
   */
  public function query($group_by = FALSE) {
    // No query to run.
  }

  /**
   * {@inheritdoc}
   */
  public function render($empty = FALSE) {
    return '';
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    $form['markup'] = array(
      '#prefix' => '<div class="form-item description">',
      '#value' => t('The handler for this item is broken or missing and cannot be used. If a module provided the handler and was disabled, re-enabling the module may restore it. Otherwise, you should probably delete this item.'),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function broken() {
    return TRUE;
  }

}

/**
 * @}
 */
