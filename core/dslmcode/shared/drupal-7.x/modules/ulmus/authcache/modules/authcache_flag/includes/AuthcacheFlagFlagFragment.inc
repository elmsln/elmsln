<?php
/**
 * @file
 * Defines a personalization fragment for retrieving flags.
 * on a node.
 */

/**
 * Personalization fragment for retrieving flags.
 *
 * @see flag.module
 */
class AuthcacheFlagFlagFragment implements AuthcacheP13nFragmentInterface, AuthcacheP13nFragmentLoaderInterface, AuthcacheP13nFragmentAccessInterface {
  protected $flagName;

  /**
   * Construct new flag fragment.
   */
  public function __construct($flag_name) {
    $this->flagName = $flag_name;
  }

  /**
   * {@inheritdoc}
   */
  public function load($entity_ids, $context) {
    $flag = flag_get_flag($this->flagName);

    if (!$flag) {
      throw new AuthcacheP13nRequestNotFound();
    }

    return array_fill_keys($entity_ids, $flag);
  }

  /**
   * {@inheritdoc}
   */
  public function check($account, $entity_id, $flag, $context) {
    if (!$flag->access($entity_id) && (!$flag->is_flagged($entity_id) || !$flag->access($entity_id, 'flag'))) {
      // User has no permission to use this flag.
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function render($entity_id, $flag, $context) {
    return $flag->theme($flag->is_flagged($entity_id) ? 'unflag' : 'flag', $entity_id);
  }
}
