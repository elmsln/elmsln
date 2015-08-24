<?php

/**
 * @file
 * Definition of og_handler_field_og_membership_link_delete.
 */

/**
 * Field handler to present a link to delete membership.
 *
 * @ingroup views_field_handlers
 */
class og_handler_field_og_membership_link_delete extends views_handler_field_entity {

  function construct() {
    parent::construct();
    $this->additional_fields['id'] = 'id';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    $options['destination'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
    $form['destination'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use destination'),
      '#description' => t('Add destination to the link'),
      '#default_value' => $this->options['destination'],
      '#fieldset' => 'more',
    );
    parent::options_form($form, $form_state);
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $value = $this->get_value($values, 'id');
    return $this->render_link($this->sanitize_value($value), $values);
  }

  function render_link($data, $values) {
    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['html'] = TRUE;

    // Ensure user has access to delete this membership.
    $og_membership = $this->get_value($values);
    $group_type = $og_membership->group_type;
    $gid = $og_membership->gid;
    $group = entity_load_single($group_type, $gid);

    if (!og_user_access($group_type, $gid, 'manage members')) {
      // User is a group manager, and may not be removed.
      return;
    }
    if (isset($group->uid) && $group->uid == $og_membership->etid) {
      // User created the group, and may not be removed.
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('remove');
    unset($this->options['alter']['fragment']);

    if (!empty($this->options['destination'])) {
      $this->options['alter']['query'] = drupal_get_destination();
    }

    $this->options['alter']['path'] = "group/" . $group_type . "/" . $gid  . "/admin/people/delete-membership/" . $og_membership->id;

    return $text;
  }
}
