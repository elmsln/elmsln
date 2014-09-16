<?php
/**
 * @file
 * Extend base style plugin.
 */

class views_plugin_style_masonry_views_grid extends views_plugin_style {

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();

    // Get default options
    $default_options = masonry_default_options();

    // Add default options
    foreach ($default_options as $option => $value) {
      $options[$option] = array(
        'default' => $value,
      );
      if (is_int($value)) {
        $options[$option]['bool'] = TRUE;
      }
    }

    return $options;
  }

  /**
   * Setup configuration form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Add Masonry options
    if (($library = libraries_detect('masonry')) && !empty($library['installed'])) {
      $form['masonry'] = array(
        '#type' => 'fieldset',
        '#title' => t('Masonry options'),
      );
      masonry_options_form($form, $this->options);
      foreach (masonry_default_options() as $option => $value) {
        $form[$option]['#fieldset'] = 'masonry';
      }
      $form['masonry_animated_duration']['#dependency'] = array(
        'edit-style-options-masonry-animated' => array(1),
      );
    }
    else {
      // jQuery Masonry plugin not installed
      $form['masonry'] = array(
        '#type' => 'fieldset',
        '#title' => t('Masonry options'),
      );
      $form['masonry_disabled'] = array(
        '#markup' => t('These settings have been disabled as the jQuery Masonry plugin is not properly installed.'),
        '#fieldset' => 'masonry',
      );
    }
  }
}

