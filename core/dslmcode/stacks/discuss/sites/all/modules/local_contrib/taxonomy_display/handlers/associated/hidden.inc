<?php

/**
 * Add a display handler that will hide the term when viewed.
 */
class TaxonomyDisplayAssociatedDisplayHandlerHidden extends TaxonomyDisplayAssociatedDisplayHandler {
  /**
   * Do not display anything to the user, we return an empty string.
   *
   * @see TaxonomyDisplayAssociatedDisplayHandler::displayAssociated()
   */
  public function displayAssociated($term, $options = NULL) {
    return array();
  }

  /**
   * Set a description when the user selects this option.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formFieldset(&$form, &$values, $options = NULL) {
    $form['#description'] = t('The associated content for the term will not be displayed to the user when viewed. Leaving only the title and term display.');
  }

  /**
   * Do not want anything stored, return void.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   */
  public function formSubmit($form, &$values) {}
}
