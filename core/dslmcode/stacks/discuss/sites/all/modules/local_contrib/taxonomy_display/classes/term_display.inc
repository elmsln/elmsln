<?php

/**
 * Abstract class for exposing term display to manipulation.
 */
abstract class TaxonomyDisplayTermDisplayHandler extends TaxonomyDisplayHandlerForm {
  /**
   * Render the output to be displayed when the user views the taxonomy term.
   *
   * @param termObject $term
   *   The taxonomy term to be displayed.
   * @param mixed $options
   *   The data that was stored on behalf of the handler resulting from the
   *   return of the TaxonomyDisplayHandlerForm::formSubmit implementation.
   *
   * @return array
   *   The build the user will see when viewing the term.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   * @see taxonomy_term_page()
   */
  abstract public function displayTerm($term, $options = NULL);
}
