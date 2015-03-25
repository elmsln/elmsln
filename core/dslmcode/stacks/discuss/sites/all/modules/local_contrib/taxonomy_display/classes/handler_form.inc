<?php

/**
 * Abstract class to act as the taxonomy display plugins form handing.
 *
 * The $form and $form_state parameters listed within this section are not true
 * $form and $form_state but rather a fieldset and form_state['values'] for the
 * fields in that fielset.
 */
abstract class TaxonomyDisplayHandlerForm {
  /**
   * Prepare the form that users will configure.
   *
   * @param array $form
   *   A fieldset for configuration to display to the user for this handler.
   * @param array $values
   *   The values from the sub-form taken from $form_state, note any alterations
   *   will affect the values in $form_state.
   * @param mixed $options
   *   The data that was stored on behalf of the handler resulting from the
   *   return of the TaxonomyDisplayHandlerForm::formSubmit implementation.
   *
   * @return TaxonomyTermDisplayHandler
   *
   * @see TaxonomyDisplayHandlerForm::formSubmit()
   */
  abstract public function formFieldset(&$form, &$values, $options = NULL);

  /**
   * Perform any processing desired and return the result to be stored.
   *
   * @param array $form
   *   A fieldset containing the sub-form rendered to the user.
   * @param array $values
   *   The values from the sub-form taken from $form_state, note any alterations
   *   will affect the values in $form_state.
   *
   * @return mixed
   *   Any single variable or no variable can be returned. Whatever is returned
   *   will be stored on behalf of the plugin for later use.
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formSubmit($form, &$values) {
    // Override formSubmit in your implementing handler if any data is to be
    // stored on behalf of your handler on submit.
    return;
  }

  /**
   * Perform validation on the custom formFieldset when the user submits.
   *
   * This method does not need to be defined in the implementing class as
   * validation can be skipped in some cases.
   *
   * @param array $form
   *   A fieldset containing the sub-form rendered to the user.
   * @param array $values
   *   The values from the sub-form taken from $form_state, note any alterations
   *   will affect the values in $form_state.
   *
   * @return TaxonomyTermDisplayHandler
   *
   * @see TaxonomyDisplayHandlerForm::formFieldset()
   */
  public function formValidate($form, &$values) {
    // Override formValidate in your implementing handler if any validation work
    // is to be done.
    
    if (FALSE) {
      // This is an example of how you can set an error on one of your form
      // elements with the key 'example_element'.
      form_set_error(implode('][', $form['example_element']['#parents']), t('Error message'));
    }
    return $this;
  }
}
