<?php

/**
 * A handler for achievement images.
 *
 */
class achievements_views_handler_field_achievements_group extends views_handler_field {
  function query() {
    $this->ensure_my_table();
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
    $this->field_alias = $this->query->add_field($this->table_alias, 'achievement_id', NULL, $params);

    $this->add_additional_fields();
  }

  function render($values) {
      $field_name = $this->table_alias . '_achievement_id';
      $achievement_id = $values->$field_name;
       
      if (!($group = achievements_views_get_group($achievement_id))) {
        return '';
      }

      return $group['title'];
  }
}
