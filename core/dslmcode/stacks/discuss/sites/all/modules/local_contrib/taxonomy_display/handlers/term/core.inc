<?php

/**
 * Add a display handler that will use the Drupal core method of display.
 */
class TaxonomyDisplayTermDisplayHandlerCore extends TaxonomyDisplayTermDisplayHandler {
  /**
   * Build our output to be rendered to the user.
   *
   * @see TaxonomyDisplayTermDisplayHandler::displayTerm()
   */
  public function displayTerm($term, $options = NULL) {
    $build = array();

    $build = array(
      '#prefix' => '<div class="term-listing-heading">',
      '#suffix' => '</div>',
      'term' => taxonomy_term_view($term, 'full'),
    );

    // We unset $build description key if the Drupal version is less than 7.2
    // and description is empty because the taxonomy_term_view() generation was
    // fixed to not include description, when empty, at that point. Done for
    // compatibility for sites using less than version 7.2.
    if (empty($term->description) && version_compare('7.2', VERSION) == 1) {
      unset($build['description']);
    }

    return $build;
  }

  /**
   * Build our form for the fieldset.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formFieldset(&$form, &$values, $options = NULL) {
    $form['#description'] = t('The core Drupal functionality will be used to display the term.');
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
}
