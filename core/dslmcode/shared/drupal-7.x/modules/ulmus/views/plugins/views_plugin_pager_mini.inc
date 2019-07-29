<?php

/**
 * @file
 * Definition of views_plugin_pager_mini.
 */

/**
 * The plugin to handle mini pager.
 *
 * @ingroup views_pager_plugins
 */
class views_plugin_pager_mini extends views_plugin_pager_full {

  /**
   * {@inheritdoc}
   */
  public function summary_title() {
    if (!empty($this->options['offset'])) {
      return format_plural($this->options['items_per_page'], 'Mini pager, @count item, skip @skip', 'Mini pager, @count items, skip @skip', array('@count' => $this->options['items_per_page'], '@skip' => $this->options['offset']));
    }
    return format_plural($this->options['items_per_page'], 'Mini pager, @count item', 'Mini pager, @count items', array('@count' => $this->options['items_per_page']));
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    // Overrides the full pager options form by deleting unused settings.
    unset($options['quantity']);
    unset($options['tags']['first']);
    unset($options['tags']['last']);
    $options['tags']['previous']['default'] = '‹‹';
    $options['tags']['next']['default'] = '››';

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Overrides the full pager options form by deleting unused settings.
    unset($form['quantity']);
    unset($form['tags']['first']);
    unset($form['tags']['last']);
  }

  /**
   * {@inheritdoc}
   */
  public function render($input) {
    // Overrides the full pager renderer by changing the theme function and
    // leaving out variables that are not used in the mini pager.
    $pager_theme = views_theme_functions('views_mini_pager', $this->view, $this->display);

    // The 1, 3 index are correct.
    // @see theme_pager().
    $tags = array(
      1 => $this->options['tags']['previous'],
      3 => $this->options['tags']['next'],
    );
    return theme($pager_theme, array(
      'tags' => $tags,
      'element' => $this->get_pager_id(),
      'parameters' => $input,
    ));
  }

}
