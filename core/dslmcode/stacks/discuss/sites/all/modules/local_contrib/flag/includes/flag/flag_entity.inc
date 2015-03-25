<?php

/**
 * @file
 * Contains the flag_entity class.
 */

/**
 * Base entity flag handler.
 */
class flag_entity extends flag_flag {
  /**
   * Adds additional options that are common for all entity types.
   */
  function options() {
    $options = parent::options();
    $options += array(
      // Output the flag in the entity links.
      // This is empty for now and will get overriden for different
      // entities.
      // @see hook_entity_view().
      'show_in_links' => array(),
      // Output the flag as individual pseudofields.
      'show_as_field' => FALSE,
      // Add a checkbox for the flag in the entity form.
      // @see hook_field_attach_form().
      'show_on_form' => FALSE,
      'access_author' => '',
      'show_contextual_link' => FALSE,
    );
    return $options;
  }

  /**
   * Options form extras for the generic entity flag.
   */
  function options_form(&$form) {
    $bundles = array();
    $entity_info = entity_get_info($this->entity_type);
    foreach ($entity_info['bundles'] as $bundle_key => $bundle) {
      $bundles[$bundle_key] = check_plain($bundle['label']);
    }
    $form['access']['types'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Bundles'),
      '#options' => $bundles,
      '#description' => t('Select the bundles that this flag may be used on. Leave blank to allow on all bundles for the entity type.'),
      '#default_value' => $this->types,
    );

    // Add checkboxes to show flag link on each entity view mode.
    $options = array();
    $defaults = array();
    $entity_view_modes = $entity_info['view modes'];
    foreach ($entity_view_modes as $name => $view_mode) {
      $options[$name] = t('Display on @name view mode', array('@name' => $view_mode['label']));
      $defaults[$name] = !empty($this->show_in_links[$name]) ? $name : 0;
    }
    // Select the first display option by default if this is a new flag.
    if (empty($this->fid)) {
      $first_view_mode_keys = array_keys($entity_view_modes);
      $first_view_mode = reset($first_view_mode_keys);
      $defaults[$first_view_mode] = $first_view_mode;
    }

    $form['display']['show_in_links'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Display in entity links'),
      '#description' => t('Show the flag link with the other links on the entity.'),
      '#options' => $options,
      '#default_value' => $defaults,
    );

    $form['display']['show_as_field'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display link as field'),
      '#description' => t('Show the flag link as a pseudofield, which can be ordered among other entity elements in the "Manage display" settings for the entity type.'),
      '#default_value' => isset($this->show_as_field) ? $this->show_as_field : TRUE,
    );
    if (empty($entity_info['fieldable'])) {
      $form['display']['show_as_field']['#disabled'] = TRUE;
      $form['display']['show_as_field']['#description'] = t("This entity type is not fieldable.");
    }

    $form['display']['show_on_form'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display checkbox on entity edit form'),
      '#default_value' => $this->show_on_form,
      '#weight' => 5,
    );

    // We use FieldAPI to put the flag checkbox on the entity form, so therefore
    // require the entity to be fielable. Since this is a potential DX
    // headscratcher for a developer wondering where this option has gone,
    // we disable it and explain why.
    if (empty($entity_info['fieldable'])) {
      $form['display']['show_on_form']['#disabled'] = TRUE;
      $form['display']['show_on_form']['#description'] = t('This is only possible on entities which are fieldable.');
    }
    $form['display']['show_contextual_link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display in contextual links'),
      '#default_value' => $this->show_contextual_link,
      '#description' => t('Note that not all entity types support contextual links.'),
      '#access' => module_exists('contextual'),
      '#weight' => 10,
    );
  }

  /**
   * Loads the entity object.
   */
  function _load_entity($entity_id) {
    if (is_numeric($entity_id)) {
      $entity = entity_load($this->entity_type, array($entity_id));
      return reset($entity);
    }
    return NULL;
  }

  /**
   * Checks whether the flag applies for the current entity bundle.
   */
  function applies_to_entity($entity) {
    $entity_info = entity_get_info($this->entity_type);
    // The following conditions are applied:
    // - if the types array is empty, the flag applies to all bundles and thus
    //   to this entity.
    // - if the entity has no bundles, the flag applies to the entity.
    // - if the entity's bundle is in the list of types.
    if (empty($this->types) || empty($entity_info['entity keys']['bundle']) || in_array($entity->{$entity_info['entity keys']['bundle']}, $this->types)) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Provides permissions for this flag.
   *
   * @return
   *  An array of permissions for hook_permission().
   */
  function get_permissions() {
    // For entity flags, use the human label of the entity.
    $entity_info = entity_get_info($this->entity_type);
    $entity_label = $entity_info['label'];
    return array(
      "flag $this->name" => array(
        'title' => t('Flag %entity entities as %flag_title', array(
          '%flag_title' => $this->title,
          '%entity' => $entity_label,
        )),
      ),
      "unflag $this->name" => array(
        'title' => t('Unflag %entity entities as %flag_title', array(
          '%flag_title' => $this->title,
          '%entity' => $entity_label,
        )),
      ),
    );
  }

  /**
   * Invoke a Rules event in reaction to a flagging or unflagging.
   *
   * @param $action
   *   Either 'flag' or 'unflag'.
   * @param $flagging
   *  The flagging entity that is either newly created or about to be deleted.
   * @param $entity_id
   *  The entity ID of entity being flagged or unflagged.
   * @param $account
   *  The account performing the action.
   */
  protected function invoke_rules_event($action, $flagging, $entity_id, $account) {
    switch ($action) {
      case 'flag':
        $event_name = 'flag_flagged_' . $this->name;
        break;
      case 'unflag':
        $event_name = 'flag_unflagged_' . $this->name;
        break;
    }

    $variables = array(
      'flag' => $this,
      'flagged_' . $this->entity_type => $entity_id,
      'flagging_user' => $account,
      'flagging' => $flagging,
    );
    rules_invoke_event_by_args($event_name, $variables);
  }

  /**
   * Returns the entity id, if it already exists.
   */
  function get_entity_id($entity) {
    $entity_info = entity_get_info($this->entity_type);
    if ($entity && isset($entity->{$entity_info['entity keys']['id']})) {
      return $entity->{$entity_info['entity keys']['id']};
    }
  }

  /**
   * Determine whether the flag should show a flag link in entity links.
   */
  function shows_in_entity_links($view_mode) {
    // Check for settings for the given view mode.
    if (isset($this->show_in_links[$view_mode])) {
      return (bool) $this->show_in_links[$view_mode];
    }
    return FALSE;
  }

  /**
   * Returns token types for the current entity type.
   */
  function get_labels_token_types() {
    // The token type name might be different to the entity type name. If so,
    // an own flag entity handler can be used for overriding this.
    $entity_info = entity_get_info($this->entity_type);
    if (isset($entity_info['token type'])) {
      return array_merge(array($entity_info['token type']), parent::get_labels_token_types());
    }
    else {
      return array_merge(array($this->entity_type), parent::get_labels_token_types());
    }
  }

  /**
   * Replaces tokens.
   */
  function replace_tokens($label, $contexts, $options, $entity_id) {
    if ($entity_id && ($entity = $this->fetch_entity($entity_id))) {
      $contexts[$this->entity_type] = $entity;
    }
    return parent::replace_tokens($label, $contexts, $options, $entity_id);
  }

  /**
   * Returns a 'flag action' object.
   */
  function get_flag_action($entity_id) {
    $flag_action = parent::get_flag_action($entity_id);
    $entity = $this->fetch_entity($entity_id);
    $flag_action->content_title = entity_label($this->entity_type, $entity);
    $flag_action->content_url = $this->_flag_url($this->entity_type . '/' . $this->get_entity_id($entity));
    return $flag_action;
  }

  /**
   * Returns objects the action may possible need.
   */
  function get_relevant_action_objects($entity_id) {
    return array(
      $this->entity_type => $this->fetch_entity($entity_id),
    );
  }

  /**
   * Returns information for the Views integration.
   */
  function get_views_info() {
    $entity_info = entity_get_info($this->entity_type);

    if (!isset($entity_info['base table'])) {
      return NULL;
    }

    return array(
      'views table' => $entity_info['base table'],
      'join field' => $entity_info['entity keys']['id'],
      'title field' => isset($entity_info['entity keys']['label']) ? $entity_info['entity keys']['label'] : '',
      'title' => t('@entity_label flag', array('@entity_label' => $entity_info['label'])),
      'help' => t('Limit results to only those entity flagged by a certain flag; Or display information about the flag set on a entity.'),
      'counter title' => t('@entity_label flag counter', array('@entity_label' => $entity_info['label'])),
      'counter help' => t('Include this to gain access to the flag counter field.'),
    );
  }
}
