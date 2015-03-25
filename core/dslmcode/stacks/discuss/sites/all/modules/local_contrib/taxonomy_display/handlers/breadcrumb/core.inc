<?php

/**
 * Add a display handler to generate the same breadcrumb from Drupal core.
 */
class TaxonomyDisplayBreadcrumbDisplayHandlerCore extends TaxonomyDisplayBreadcrumbDisplayHandler {
  /**
   * Do not display anything to the user, we return an empty string.
   *
   * @see TaxonomyDisplayBreadcrumbDisplayHandler::buildBreacrumb()
   */
  public function buildBreadcrumb($term) {
    // Build breadcrumb like core does.
    // @see taxonomy_term_page()
    $current = (object) array(
      'tid' => $term->tid,
    );
    $breadcrumb = array();
    while ($parents = taxonomy_get_parents($current->tid)) {
      // Allow modules like i18n_taxonomy to alter the parents.
      drupal_alter('taxonomy_display_breadcrumb_parents', $parents);
      $current = array_shift($parents);
      $breadcrumb[] = l($current->name, 'taxonomy/term/' . $current->tid);
    }
    $breadcrumb[] = l(t('Home'), NULL);
    $breadcrumb = array_reverse($breadcrumb);
    drupal_set_breadcrumb($breadcrumb);
  }

  /**
   * Set a description when the user selects this option.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formFieldset(&$form, &$values, $options = NULL) {
    $form['#description'] = t('The Drupal core breadcrumb will be used for the taxonomy terms.');
  }

  /**
   * Do not want anything stored, return void.
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   */
  public function formSubmit($form, &$values) {}
}
