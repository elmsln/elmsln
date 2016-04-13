<?php

/**
 * Search API Processor that filters out terms from moderated vocabularies.
 */
class ContentTaxonomyAutocompleteModeratedTermsSearchAPIProcessor extends SearchApiAbstractProcessor {

  /**
   * Confiuration callback.
   *
   * Only allow users to select taxonomy fields.
   */
  public function configurationForm() {
    $form = parent::configurationForm();
    $form['fields']['#options'] = $this->filterTaxonomyFieldsOptions($form['fields']['#options']);
    return $form;
  }

  /**
   * Postprocess items while indexing and filter out the moderated terms.
   */
  public function preprocessIndexItems(array &$items) {
    $fields = $this->getTaxonomyFields($this->options['fields']);
    foreach ($items as &$item) {
      foreach ($fields as $search_api_property_name => $field) {
        if (isset($item[$search_api_property_name])) {
          $this->processTaxonomyField($item[$search_api_property_name]['value'], $item[$search_api_property_name]['type'], $field);
        }
      }
    }
  }

  /**
   * Processes a single field on a single item and does the actual filtering.
   *
   * As such a field can be nested, recursions are used until we reach the top
   * level.
   */
  protected function processTaxonomyField(&$value, &$type, $field) {
    if (!isset($value) || $value === '') {
      return;
    }
    if (substr($type, 0, 10) == 'list<list<') {
      $inner_type = $t1 = substr($type, 5, -1);
      foreach ($value as &$v) {
        $t1 = $inner_type;
        $this->processTaxonomyField($v, $t1, $field);
      }
      return;
    }
    if (is_array($value)) {
      foreach ($value as $key => $v) {
        if ($this->fieldValueIsModerated($v, $field)) {
          unset($value[$key]);
        }
      }
    }
    elseif ($this->fieldValueIsModerated($value, $field)) {
      $value = NULL;
    }
  }

  /**
   * Returns TRUE if the given term id is from moderated vocabulary.
   *
   * @param $value
   *  The term id.
   * @param $field
   *  The according field API field.
   */
  private function fieldValueIsModerated($value, $field) {
    $allowed_voc = $field['settings']['allowed_values'][0]['vocabulary'];
    $term = taxonomy_term_load($value);
    if ($term && $term->vocabulary_machine_name == $allowed_voc) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Helper function that filters the configuration field options for taxonomy
   * fields.
   */
  private function filterTaxonomyFieldsOptions($options) {
    $taxonomy_fields = array();
    foreach ($options as $search_api_property_name => $label) {
      if ($this->getTaxonomyField($search_api_property_name)) {
        $taxonomy_fields[$search_api_property_name] = $label;
      }
    }
    return $taxonomy_fields;
  }

  /**
   * Helper function that returns the taxonomy fields for the given search API
   * property names.
   */
  private function getTaxonomyFields($search_api_properties) {
    $taxonomy_fields = array();
    foreach ($search_api_properties as $search_api_property_name => $label) {
      if ($field = $this->getTaxonomyField($search_api_property_name)) {
        $taxonomy_fields[$search_api_property_name] = $field;
      }
    }
    return $taxonomy_fields;
  }

  /**
   * Helper function that extracts the taxonomy field from a search API property
   * name.
   */
  private function getTaxonomyField($search_api_property_name) {
    $parts = explode(':', $search_api_property_name);
    foreach ($parts as $part) {
      if (substr($part, 0, 6) == 'field_') {
        $field = field_info_field($part);
        if ($field && isset($field['type']) && $field['type'] == "taxonomy_term_reference") {
          return $field;
        }
      }
    }
    return FALSE;
  }
}
