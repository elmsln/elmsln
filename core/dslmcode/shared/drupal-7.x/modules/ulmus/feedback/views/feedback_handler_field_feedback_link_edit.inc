<?php

/**
 * Field handler to present a link to edit a feedback entry.
 */
class feedback_handler_field_feedback_link_edit extends feedback_handler_field_feedback_link {
  function render_link($data, $values) {
    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "admin/reports/feedback/$data/edit";
    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    return $text;
  }
}
