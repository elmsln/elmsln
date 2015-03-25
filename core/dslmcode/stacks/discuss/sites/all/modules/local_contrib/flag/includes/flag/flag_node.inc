<?php

/**
 * @file
 * Contains the flag_node class.
 */

/**
 * Implements a node flag.
 */
class flag_node extends flag_entity {
  function options() {
    $options = parent::options();
    // Use own display settings in the meanwhile.
    $options += array(
      'i18n' => 0,
    );
    return $options;
  }

  /**
   * Options form extras for node flags.
   */
  function options_form(&$form) {
    parent::options_form($form);

    $form['access']['access_author'] = array(
      '#type' => 'radios',
      '#title' => t('Flag access by content authorship'),
      '#options' => array(
        '' => t('No additional restrictions'),
        'own' => t('Users may only flag content they own'),
        'others' => t('Users may only flag content of others'),
      ),
      '#default_value' => $this->access_author,
      '#description' => t("Restrict access to this flag based on the user's ownership of the content. Users must also have access to the flag through the role settings."),
    );

    // Support for i18n flagging requires Translation helpers module.
    $form['i18n'] = array(
      '#type' => 'radios',
      '#title' => t('Internationalization'),
      '#options' => array(
        '1' => t('Flag translations of content as a group'),
        '0' => t('Flag each translation of content separately'),
      ),
      '#default_value' => $this->i18n,
      '#description' => t('Flagging translations as a group effectively allows users to flag the original piece of content regardless of the translation they are viewing. Changing this setting will <strong>not</strong> update content that has been flagged already.'),
      '#access' => module_exists('translation_helpers'),
      '#weight' => 5,
    );

    // Override the UI texts for nodes.
    $form['display']['show_on_form'] = array(
      '#title' => t('Display checkbox on node edit form'),
      '#description' => t('If you elect to have a checkbox on the node edit form, you may specify its initial state in the settings form <a href="@content-types-url">for each content type</a>.', array('@content-types-url' => url('admin/structure/types'))),
    ) + $form['display']['show_on_form'];

    // Add the 'teaser' view mode as a default value for the entity link display
    // option if this is a new flag.
    if (empty($this->fid)) {
      $form['display']['show_in_links']['#default_value']['teaser'] = 'teaser';
    }
  }

  function type_access_multiple($entity_ids, $account) {
    $access = array();

    // If all subtypes are allowed, we have nothing to say here.
    if (empty($this->types)) {
      return $access;
    }

    // Ensure that only flaggable node types are granted access. This avoids a
    // node_load() on every type, usually done by applies_to_entity_id().
    $result = db_select('node', 'n')->fields('n', array('nid'))
      ->condition('nid', array_keys($entity_ids), 'IN')
      ->condition('type', $this->types, 'NOT IN')
      ->execute();
    foreach ($result as $row) {
      $access[$row->nid] = FALSE;
    }

    return $access;
  }

  /**
   * Adjust the Content ID to find the translation parent if i18n-enabled.
   *
   * @param $entity_id
   *   The nid for the content.
   *
   * @return
   *   The tnid if available, the nid otherwise.
   */
  function get_translation_id($entity_id) {
    if ($this->i18n) {
      $node = $this->fetch_entity($entity_id);
      if (!empty($node->tnid)) {
        $entity_id = $node->tnid;
      }
    }
    return $entity_id;
  }

  function flag($action, $entity_id, $account = NULL, $skip_permission_check = FALSE, $flagging = NULL) {
    $entity_id = $this->get_translation_id($entity_id);
    return parent::flag($action, $entity_id, $account, $skip_permission_check, $flagging);
  }

  // Instead of overriding is_flagged() we override get_flagging_record(),
  // which is the underlying method.
  function get_flagging_record($entity_id, $uid = NULL, $sid = NULL) {
    $entity_id = $this->get_translation_id($entity_id);
    return parent::get_flagging_record($entity_id, $uid, $sid);
  }

  /**
   * This is overridden for no other purpose than to document that $entity_id
   * can be one of the following fake IDs in certain contexts:
   *  - 'new': On a new node form.
   *  - 'fake': On the node type admin form.
   */
  function replace_tokens($label, $contexts, $options, $entity_id) {
    return parent::replace_tokens($label, $contexts, $options, $entity_id);
  }
}
