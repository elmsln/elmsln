<?php

/**
 * Add template suggestions as a context reaction.
 */
class context_reaction_template_suggestions extends context_reaction {

  /**
   * Display the text area field for adding new template suggestions.
   */
  function options_form($context) {
    $default_value = $this->fetch_from_context($context);

    return array(
      '#title' => t('Template suggestions'),
      '#type' => 'textarea',
      '#description' => t('Enter template suggestions such as "page__front", one per line, in order of preference (using underscores instead of hyphens). For more information, please visit <a href="@template-suggestions">Drupal 7 Template (Theme Hook) Suggestions</a>.', array('@template-suggestions' => 'http://drupal.org/node/1089656')),
      '#default_value' => is_string($default_value) ? $default_value : '',
    );
  }

  /**
   * Add any new template suggestions to the current list.
   */
  function execute(&$vars = NULL) {

    // Get the list of contexts associated with this reaction.
    $contexts = $this->get_contexts();

    // Iterate through each, and process those with something set.
    foreach ($contexts as $context) {
      if (isset($context->reactions) && (!empty($context->reactions[$this->plugin]))) {

        // Get the suggestion data entered by the user.
        $suggestions = $this->fetch_from_context($context, 'values');

        // Convert it to an list and reverse it (as higher priority items
        // should be on the bottom).
        $suggestions = array_reverse(explode("\n", $suggestions));

        // Append the suggested list to the existing list.
        $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'], $suggestions);
      }
    }
  }
}

