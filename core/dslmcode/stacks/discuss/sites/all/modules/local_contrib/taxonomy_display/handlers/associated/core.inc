<?php

/**
 * Add a display handler that will use the Drupal core method of display.
 */
class TaxonomyDisplayAssociatedDisplayHandlerCore extends TaxonomyDisplayAssociatedDisplayHandler {
  /**
   * Build our output to be rendered to the user.
   *
   * @see TaxonomyDisplayAssociatedDisplayHandler::displayAssociated()
   */
  public function displayAssociated($term, $options = NULL) {
    $build = array();

    $number_nodes = intval(isset($options['associated_per_page']) ? $options['associated_per_page'] : variable_get('default_nodes_main', 10));
    if ($number_nodes === 0) {
      $number_nodes = FALSE;
    }
    if ($nids = taxonomy_select_nodes($term->tid, TRUE, $number_nodes)) {
      $nodes = node_load_multiple($nids);
      $build += node_view_multiple($nodes);
      $build['pager'] = array(
        '#theme' => 'pager',
        '#weight' => 5,
       );
    }
    elseif (isset($options['empty_text']) && !empty($options['empty_text'])) {
      $build['no_content'] = array(
        '#prefix' => '<p>',
        '#markup' => t($options['empty_text']),
        '#suffix' => '</p>',
      );
    }

    return $build;
  }

  /**
   * Build our form for the fieldset.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formFieldset(&$form, &$values, $options = NULL) {
    $form['#description'] = t('The core Drupal functionality will be used to display the term\'s associated content.');

    $form['associated_per_page'] = array(
      '#default_value' => isset($options['associated_per_page']) ? $options['associated_per_page'] : variable_get('default_nodes_main', 10),
      '#description' => t('Enter 0 to display all associated content for the taxonomy term.'),
      '#maxlength' => 7,
      '#required' => TRUE,
      '#size' => 8,
      '#title' => t('Number of associated content entities per page'),
      '#type' => 'textfield',
    );

    $form['empty_text'] = array(
      '#default_value' => isset($options['empty_text']) ? $options['empty_text'] : 'There is currently no content classified with this term.',
      '#description' => t('Text displayed if there is no associated content, set to blank if no empty text should be displayed.'),
      '#title' => t('No associated content text'),
      '#type' => 'textfield',
    );
  }

  /**
   * We store values to access later for rendering and editing.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   */
  public function formSubmit($form, &$values) {
    // We are using the exact keys that our formFieldset() implementation
    // defines and we want all of the values stored, so we have no need to alter
    // them before returning.
    return $values;
  }

  /**
   * Validate the form values.
   *
   * @see TaxonomyDisplayHandlerForm::formValidate()
   */
  public function formValidate($form, &$values) {
    if ($values['associated_per_page'] !== '0' &&
        !preg_match('#^[1-9][0-9]*$#', $values['associated_per_page'])) {
      form_set_error(implode('][', $form['associated_per_page']['#parents']), t('The number of associated content entities per page must be a whole, non-negative number.'));
    }

    return $this;
  }
}
