<?php

/**
 * Simple condition that sets context active if no other non-default and non
 * sitewide context is active.
 */
class context_condition_default extends context_condition {
  function condition_values() {
    return array('context_condition_default' => t('Default context'));
  }

  function editor_form($context = NULL) {
    $form = parent::editor_form($context);
    $form[1]['#title'] = t('Default context');
    $form['#weight'] = -10;
    return $form;
  }

  function execute() {
    if ($this->condition_used()) {
      $active_contexts = context_active_contexts();

      foreach ($active_contexts as $name => $context) {
        foreach (array_keys($context->conditions) as $cond) {
          if (!in_array($cond, array('default', 'sitewide'))) {
            return;
          }
        }
      }
      foreach ($this->get_contexts('context_condition_default') as $context) {
        $this->condition_met($context, 'context_condition_default');
      }
    }
  }
}
