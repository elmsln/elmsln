<?php

/**
 * @file
 * Definition of views_handler_field_ctools_dropdown.
 */

/**
 * Field handler which displays some amount of links as ctools dropdown button.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_ctools_dropdown extends views_handler_field_links {
  function option_definition() {
    $options = parent::option_definition();

    $options['views_admin_css'] = array('default' => TRUE, 'bool' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['fields']['#description'] = t('Fields to be included as ctools dropdown button.');
    $form['destination']['#description'] = t('Include a "destination" parameter in the link to return the user to the original view upon completing a link action.');

    $form['views_admin_css'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include Views admin CSS'),
      '#description' => t("Add additional css to match the style of the Views admin screen."),
      '#default_value' => $this->options['views_admin_css'],
    );
  }

  /**
   * Render the dropdown button.
   */
  function render($values) {
    static $added_admin_css;
    $links = $this->get_links();

    if (!empty($links)) {
      if (!empty($this->options['views_admin_css']) && !$added_admin_css) {
        views_include('admin');
        views_ui_add_admin_css();
        $added_admin_css = TRUE;
      }

      return theme('links__ctools_dropbutton', array('links' => $links, 'attributes' => array('class' => array('links', 'inline'))));
    }
    else {
      return '';
    }
  }
}
