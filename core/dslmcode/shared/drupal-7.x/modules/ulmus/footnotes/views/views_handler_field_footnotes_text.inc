<?php
/**
 * @file
 * Views handler for the body footnotes.
 */

class views_handler_field_footnotes_text extends entity_views_handler_field_text {
  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($values) {
    $start = strpos($values->{$this->base_field}, '<ul class="footnotes">');
    // By default footnotes are at the end, but they could be anywhere really.
    // $end   = strpos($data, '</ul><!-- end footnotes -->')+strlen('</ul><!-- end footnotes -->');
    if ($start !== FALSE) {
      // $data = substr($data, $start, $end);
      $data = substr($values->{$this->base_field}, $start);
    }
    else {
      // There are no footnotes.
      $data = '';
    }
    return $data;
  }
};
