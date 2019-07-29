<?php

/**
 * @file
 * Definition of views_handler_field_profile_list.
 */

/**
 * Field handler display a profile list item.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_profile_list extends views_handler_field_prerender_list {

  /**
   * Break up our field into a proper list.
   */
  public function pre_render(&$values) {
    $this->items = array();
    foreach ($values as $value) {
      $field = $this->get_value($value);
      $this->items[$field] = array();
      foreach (preg_split("/[,\n\r]/", $field) as $item) {
        if ($item != '' && $item !== NULL) {
          $this->items[$field][] = array('item' => $item);
        }
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function render_item($count, $item) {
    return $item['item'];
  }

  /**
   * {@inheritdoc}
   */
  public function document_self_tokens(&$tokens) {
    $tokens['[' . $this->options['id'] . '-item' . ']'] = t('The text of the profile item.');
  }

  /**
   * {@inheritdoc}
   */
  public function add_self_tokens(&$tokens, $item) {
    $tokens['[' . $this->options['id'] . '-item' . ']'] = $item['item'];
  }

}
