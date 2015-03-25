<?php

/**
 * @file
 * Contains the boolean flagged field handler.
 */

/**
 * Views field handler for the flagged field.
 *
 * @ingroup views
 */
class flag_handler_field_flagged extends views_handler_field_boolean {

  function init(&$view, &$options) {
    parent::init($view, $options);

    // Add our boolean labels.
    $this->formats['flag'] = array(t('Flagged'), t('Not flagged'));
    // TODO: We could probably lift the '(Un)Flagged message' strings from the
    // flag object, but a) we need to lift that from the relationship we're on
    // and b) they will not necessarily make sense in a static context.
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();
    // Add the formula.
    $this->field_alias = $this->query->add_field(NULL, "($this->table_alias.uid IS NOT NULL)", 'flagging_flagged');

    $this->add_additional_fields();
  }

}
