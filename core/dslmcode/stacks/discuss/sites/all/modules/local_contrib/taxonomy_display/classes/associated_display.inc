<?php

/**
 * Abstract class for exposing terms' associated content to manipulation.
 */
abstract class TaxonomyDisplayAssociatedDisplayHandler extends TaxonomyDisplayHandlerForm {
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
   *   The build the user will see for the associated content viewing the term.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   * @see taxonomy_term_page()
   */
  abstract public function displayAssociated($term, $options = NULL);
}
