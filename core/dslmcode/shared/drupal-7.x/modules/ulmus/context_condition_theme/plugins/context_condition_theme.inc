<?php
// $Id: 

/**
 * Expose themes as a context condition.
 */
class context_condition_theme extends context_condition {
  /**
   * Override of condition_values().
   */
  function condition_values() {
    $values = array();
    
    foreach (list_themes() as $theme) {
      if ($theme->status) {
        $values[$theme->name] = $theme->info['name'];
      }
    }    
    return $values;
  }


  /**
   * Override of execute().
   */
  function execute() {
    global $theme_info;
    if ($this->condition_used()) {
      foreach ($this->get_contexts($theme_info->name) as $context) {
        $themes = $this->fetch_from_context($context, 'values'); 
        foreach($themes as $theme) {
          if ($theme_info->name == $theme) {
            $this->condition_met($context);
          }
        }
      }    
    }
  }
}
