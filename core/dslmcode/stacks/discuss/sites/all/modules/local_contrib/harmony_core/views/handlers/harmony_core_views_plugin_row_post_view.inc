<?php

/**
 * @file
 * Contains the harmony_post view row style plugin.
 */

/**
 * Plugin which performs a harmony_post_view on the resulting object.
 *
 * Most of the code on this object is in the theme function.
 *
 * @ingroup views_row_plugins
 */
class harmony_core_views_plugin_row_harmony_post_view extends views_plugin_row {
  // Basic properties that let the row style follow relationships.
  var $base_table = 'harmony_post';
  var $base_field = 'post_id';

  // Stores the harmony_posts loaded with pre_render.
  var $harmony_posts = array();

  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    // Handle existing views with the deprecated 'teaser' option.
    if (isset($this->options['inline_reply'])) {
      $this->options['build_mode'] = $this->options['inline_reply'] ? 'inline_reply' : 'full';
    }
    // Handle existing views which has used build_mode instead of view_mode.
    if (isset($this->options['build_mode'])) {
      $this->options['view_mode'] = $this->options['build_mode'];
    }

    module_load_include('inc', 'harmony_core', 'includes/harmony_core.pages');
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['view_mode'] = array('default' => 'full');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = $this->options_form_summary_options();
    $form['view_mode'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('View mode'),
      '#default_value' => $this->options['view_mode'],
    );
  }

  /**
   * Return the main options, which are shown in the summary title.
   */
  function options_form_summary_options() {
    $entity_info = entity_get_info('harmony_post');
    $options = array();
    if (!empty($entity_info['view modes'])) {
      foreach ($entity_info['view modes'] as $mode => $settings) {
        $options[$mode] = $settings['label'];
      }
    }
    if (empty($options)) {
      $options = array(
        'full' => t('Full content'),
        'inline_reply' => t('Inline reply'),
      );
    }

    return $options;
  }

  function summary_title() {
    $options = $this->options_form_summary_options();
    return check_plain($options[$this->options['view_mode']]);
  }

  function pre_render($values) {
    $post_ids = array();
    foreach ($values as $row) {
      $post_ids[] = $row->{$this->field_alias};
    }
    $this->harmony_posts = harmony_post_load_multiple($post_ids);
  }

  function render($row) {
    if (isset($this->harmony_posts[$row->{$this->field_alias}])) {
      $harmony_post = $this->harmony_posts[$row->{$this->field_alias}];
      $harmony_post->view = $this->view;
      $build = harmony_core_post_view($harmony_post, $this->options['view_mode']);

      return drupal_render($build);
    }
  }
}
