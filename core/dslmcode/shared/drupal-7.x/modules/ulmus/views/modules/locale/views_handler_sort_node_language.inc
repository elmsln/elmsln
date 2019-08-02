<?php

/**
 * @file
 * Contains .
 */

/**
 * Sort handler that allows sorting on a specific language.
 *
 * @ingroup views_sort_handlers
 */
class views_handler_sort_node_language extends views_handler_sort {

  /**
   * {@inheritdoc}
   */
  public function can_expose() {
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    if (isset($this->options['language'])) {
      $langcode = $this->get_system_langcode($this->options['language']);
      // Validate the langcode.
      if (preg_match('/^[a-z0-9\-]+$/i', $langcode)) {
        $this->ensure_my_table();
        // See https://stackoverflow.com/questions/14104055/ordering-by-specific-field-value-first
        $formula = "{$this->table_alias}_language = '{$langcode}'";
        $this->query->add_orderby($this->table_alias, NULL, $this->options['order'], $formula);
      }
    }
  }

  /**
   * Converts a views language code into a Drupal language code.
   */
  public function get_system_langcode($langcode) {
    global $language_content;
    $default_language = language_default('language');
    $system_langcode = str_replace(array(
      '***CURRENT_LANGUAGE***',
      '***DEFAULT_LANGUAGE***',
      ),
      array(
        $language_content->language,
        $default_language,
      ),
      $langcode);
    return $system_langcode;
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['language'] = array('default' => '***CURRENT_LANGUAGE***');
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function admin_summary() {
    $summary = parent::admin_summary();
    if ($this->options['language']) {
      $language_options = $this->get_language_options();
      $summary = t('@order, @language', array(
        '@order' => $summary,
        '@language' => $language_options[$this->options['language']],
      ));
    }
    return $summary;
  }

  /**
   * Returns languages to sort by.
   *
   * @return array
   *   All the languages.
   */
  public function get_language_options() {
    $languages = array(
      '***CURRENT_LANGUAGE***' => t("Current user's language"),
      '***DEFAULT_LANGUAGE***' => t("Default site language"),
      LANGUAGE_NONE => t('No language'),
    );
    $languages = array_merge($languages, views_language_list());
    return $languages;
  }

  /**
   * {@inheritdoc}
   */
  public function show_sort_form(&$form, &$form_state) {
    parent::show_sort_form($form, $form_state);

    $form['language'] = array(
      '#type' => 'radios',
      '#title' => t("Specific language"),
      '#description' => t("Choose which specific language to sort by. Not to be confused with the 'Language' sort handler, which sorts by language."),
      '#options' => $this->get_language_options(),
      '#default_value' => $this->options['language'],
    );
  }

}
