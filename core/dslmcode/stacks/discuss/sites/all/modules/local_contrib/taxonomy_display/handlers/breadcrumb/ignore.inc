<?php

/**
 * Add a display handler to not set any breadcrumb.
 */
class TaxonomyDisplayBreadcrumbDisplayHandlerIgnore extends TaxonomyDisplayBreadcrumbDisplayHandlerCore {
  /**
   * Do not display anything to the user, we return an empty string.
   *
   * @see TaxonomyDisplayBreadcrumbDisplayHandler::buildBreacrumb()
   */
  public function buildBreadcrumb($term) {
  }

  /**
   * Set a description when the user selects this option.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formFieldset(&$form, &$values, $options = NULL) {
    $form['#description'] = t('A breadcrumb will not be set, allowing other modules to do so.');
  }

  /**
   * Do not want anything stored, return void.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   */
  public function formSubmit($form, &$values) {

  }
}
