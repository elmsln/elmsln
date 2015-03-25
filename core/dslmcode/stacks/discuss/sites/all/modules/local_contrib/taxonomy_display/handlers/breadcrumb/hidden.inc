<?php

/**
 * Add a display handler that will omit the breadcrumb on term pages.
 */
class TaxonomyDisplayBreadcrumbDisplayHandlerHidden extends TaxonomyDisplayBreadcrumbDisplayHandler {
  /**
   * Do not display anything to the user, we return an empty string.
   *
   * @see TaxonomyDisplayBreadcrumbDisplayHandler::buildBreacrumb()
   */
  public function buildBreadcrumb($term) {
    drupal_set_breadcrumb('');
  }

  /**
   * Set a description when the user selects this option.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formFieldset(&$form, &$values, $options = NULL) {
    $form['#description'] = t('The breadcrumb for the term will not be displayed to the user when viewed.');
  }

  /**
   * Do not want anything stored, return void.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   */
  public function formSubmit($form, &$values) {}
}
