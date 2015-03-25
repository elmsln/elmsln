<?php

/**
 * Abstract class for exposing taxonomy term breadcrumbs to generation.
 */
abstract class TaxonomyDisplayBreadcrumbDisplayHandler extends TaxonomyDisplayHandlerForm {
  /**
   * Build and attach breadcrumb to page.
   *
   * @param termObject $term
   *   The taxonomy term to build breadcrumb for.
   *
   * @return void
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   * @see taxonomy_term_page()
   */
  abstract public function buildBreadcrumb($term);
}
