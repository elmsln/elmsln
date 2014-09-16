<?php

/**
 * @file
 * Provide handler to replace reference with title.
 */
class references_handler_argument extends views_handler_argument_numeric {

  /**
   *  Use entity title for % placeholders in argument titles.
   */
  function title_query() {
    // Use the same table and field than those used for summary lists
    // ('name table', 'name field').
    $table_data = views_fetch_data($this->name_table);
    $table_info = $table_data['table']['join'][$this->table];
    $table = $table_info['table'];
    $key_field = $table_info['field'];
    $title_field = $this->name_field;

    $results = db_select($table, 'base_table')
      ->fields('base_table', array($key_field, $title_field))
      ->condition("base_table.$key_field", $this->value)
      ->execute()
      // Grab results as 'key => title' array.
      ->fetchAllKeyed();

    // Sanitize titles and put them back in the correct order in an unkeyed
    // array.
    $titles = array();
    foreach ($this->value as $key) {
      if (isset($results[$key])) {
        $titles[] = check_plain($results[$key]);
      }
    }

    return $titles;
  }
}
