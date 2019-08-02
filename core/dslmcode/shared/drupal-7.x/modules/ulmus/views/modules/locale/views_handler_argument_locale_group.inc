<?php

/**
 * @file
 * Contains .
 */

/**
 * Argument handler to accept a language.
 *
 * @ingroup views_argument_handlers
 */
class views_handler_argument_locale_group extends views_handler_argument {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct('group');
  }

  /**
   * Override the behavior of summary_name(). Get the user friendly version
   * of the group.
   */
  public function summary_name($data) {
    return $this->locale_group($data->{$this->name_alias});
  }

  /**
   * Override the behavior of title(). Get the user friendly version
   * of the language.
   */
  public function title() {
    return $this->locale_group($this->argument);
  }

  /**
   * {@inheritdoc}
   */
  public function locale_group($group) {
    $groups = module_invoke_all('locale', 'groups');
    // Sort the list.
    asort($groups);
    return isset($groups[$group]) ? $groups[$group] : t('Unknown group');
  }

}
