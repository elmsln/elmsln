<?php

/**
 * Add a display handler that will hide the term when viewed.
 */
class TaxonomyDisplayTermDisplayHandlerHidden extends TaxonomyDisplayTermDisplayHandler {
  /**
   * Do not display anything to the user, we return an empty array.
   *
   * @see TaxonomyDisplayTermDisplayHandler::displayTerm()
   */
  public function displayTerm($term, $options = NULL) {
    return array();
  }

  /**
   * Set a description when the user selects this option.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formFieldset(&$form, &$values, $options = NULL) {
    $form['#description'] = t('The term will not be displayed to the user when viewed. Leaving only the title and associated content.');
  }

  /**
   * Do not want anything stored, return void.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   */
  public function formSubmit($form, &$values) {}
}
