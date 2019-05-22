<?php

/**
 * @file context_condition_query_string.inc
 *
 * Similar to context_condition_path but for entire query string.
 */

/**
 * Expose query strings as a context condition.
 */
class context_condition_query_string extends context_condition_path {

  /**
   * Execute.
   */
  function execute() {
    if ($this->condition_used()) {
      $current_query_string = $_SERVER["QUERY_STRING"];
      foreach ($this->get_contexts() as $context) {
        $query_strings = $this->fetch_from_context($context, 'values');
        if ($this->match($current_query_string, $query_strings, TRUE)) {
          $this->condition_met($context);
        }
      }
    }
  }
}
