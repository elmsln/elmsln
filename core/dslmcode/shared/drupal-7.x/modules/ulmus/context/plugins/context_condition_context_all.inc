<?php

/**
 * Expose active contexts as a context condition.
 */
class context_condition_context_all extends context_condition_path {
  function execute() {
    if ($this->condition_used()) {
      $active_contexts = array_keys(context_active_contexts());
      foreach ($this->get_contexts() as $context) {

        // Only test contexts that haven't been activated yet,
        // and have values set.
        if (!in_array($context->name, $active_contexts, TRUE) && $values = $this->fetch_from_context($context, 'values')) {

          // The condition is met if all contexts are active.
          if (count(array_intersect($values, $active_contexts)) == count($values)) {
            $this->condition_met($context);
          }
        }
      }

      // If the list of active contexts has changed, we need to recurse.
      if ($active_contexts != array_keys(context_active_contexts())) {
        $this->execute();
      }
    }
  }
}
