<?php

/**
 * @file
 * Definition of views_handler_field_user_roles.
 */

/**
 * Field handler to provide a list of roles.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_user_roles extends views_handler_field_prerender_list {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['uid'] = array('table' => 'users', 'field' => 'uid');
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['uid'];
  }

  /**
   * {@inheritdoc}
   */
  public function pre_render(&$values) {
    $uids = array();
    $this->items = array();

    foreach ($values as $result) {
      $uids[] = $this->get_value($result, NULL, TRUE);
    }

    if ($uids) {
      $result = db_query("SELECT u.uid, u.rid, r.name FROM {role} r INNER JOIN {users_roles} u ON u.rid = r.rid WHERE u.uid IN (:uids) ORDER BY r.name",
        array(':uids' => $uids));
      foreach ($result as $role) {
        $this->items[$role->uid][$role->rid]['role'] = check_plain($role->name);
        $this->items[$role->uid][$role->rid]['rid'] = $role->rid;
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function render_item($count, $item) {
    return $item['role'];
  }

  /**
   * {@inheritdoc}
   */
  public function document_self_tokens(&$tokens) {
    $tokens['[' . $this->options['id'] . '-role' . ']'] = t('The name of the role.');
    $tokens['[' . $this->options['id'] . '-rid' . ']'] = t('The role ID of the role.');
  }

  /**
   * {@inheritdoc}
   */
  public function add_self_tokens(&$tokens, $item) {
    if (!empty($item['role'])) {
      $tokens['[' . $this->options['id'] . '-role' . ']'] = $item['role'];
      $tokens['[' . $this->options['id'] . '-rid' . ']'] = $item['rid'];
    }
  }

}
