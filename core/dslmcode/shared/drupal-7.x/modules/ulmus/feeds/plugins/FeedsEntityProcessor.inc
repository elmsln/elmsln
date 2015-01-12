<?php
/**
 * @file
 * Class definition of FeedsEntityProcessor.
 */

/**
 * Creates entities from feed items.
 */
class FeedsEntityProcessor extends FeedsProcessor {

  /**
   * Returns the entity type.
   *
   * @return string
   *   The type of entity this processor will create.
   */
  public function entityType() {
    $plugin_info = $this->pluginDefinition();
    return $plugin_info['type'];
  }

  /**
   * Returns the bundle.
   *
   * @return string
   *   The bundle of the entities this processor will create.
   */
  public function bundle() {
    $bundle = $this->entityType();

    $entity_info = $this->entityInfo();
    if(!empty($this->config['bundle']) && isset($entity_info['bundles'][$this->config['bundle']])) {
      $bundle = $this->config['bundle'];
    }

    return $bundle;
  }

  /**
   * Overrides parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    if (isset($info['label plural'])) {
      $plural = $info['label plural'];
    }
    else {
      $plural = $info['label'];
    }

    $info += array('label plural' => $plural);
    return $info;
  }

  /**
   * Creates a new entity in memory and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $info = $this->entityInfo();
    $values = $this->config['values'];

    if (isset($info['entity keys']['bundle']) && isset($this->config['bundle'])) {
      $values[$info['entity keys']['bundle']] = $this->config['bundle'];
    }

    return entity_create($this->entityType(), $values);
  }

  /**
   * Check that the user has permission to save an entity.
   *
   * @todo Is checking the uid safe? A quick glance through core and some
   *   contrib seems to say yes.
   */
  protected function entitySaveAccess($entity) {

    // The check will be skipped for anonymous users.
    if (!empty($this->config['authorize']) && !empty($entity->uid)) {

      $author = user_load($entity->uid);

      // If the uid was mapped directly, rather than by email or username, it
      // could be invalid.
      if (!$author) {
        $message = 'User %uid is not a valid user.';
        throw new FeedsAccessException(t($message, array('%uid' => $entity->uid)));
      }

      if (!empty($entity->is_new)) {
        $op = 'create';
        $access = entity_access($op, $this->entityType(), $author);
      }
      else {
        $op = 'update';
        $access = entity_access($op, $this->entityType(), $author);
      }

      if (!$access) {
        $message = t('The user %name is not authorized to %op entity %entity_type. To import this item, the user "@name" (owner of the item) must be given the permission to @op entity @entity_type.', array(
          '%name' => $author->name,
          '%op' => $op,
          '%entity_type' => $this->entityType(),
          '@name' => $author->name,
          '@op' => $op,
          '@entity_type' => $this->entityType(),
        ));
        throw new FeedsAccessException($message);
      }
    }
  }

  /**
   * Save a entity.
   */
  public function entitysave($entity) {
    entity_save($this->entityType(), $entity);
  }

  /**
   * Delete a series of entities.
   */
  protected function entityDeleteMultiple($ids) {
    entity_delete_multiple($this->entityType(), $ids);
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'mappings' => array(),
      'update_existing' => FEEDS_SKIP_EXISTING,
      'update_non_existent' => FEEDS_SKIP_NON_EXISTENT,
      'input_format' => NULL,
      'skip_hash_check' => FALSE,
      'bundle' => NULL,
      'values' => array(),
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);

    $form['values'] = array(
      '#type' => 'fieldset',
      '#title' => t('Default values'),
      '#tree' => TRUE,
      '#description' => t('Most of the values below can be overriden by mapping a value.'),
    );

    $entity_info = $this->entityInfo();
    $label_plural = $entity_info['label plural'];

    $form['input_format']['#description'] = t('Select the default input format for the %entity to be created.', array('%entity' => $label_plural));

    $wrapper = entity_metadata_wrapper($this->entityType());

    $bundle_key = !empty($entity_info['entity keys']['bundle']) ? $entity_info['entity keys']['bundle']: NULL;

    foreach ($wrapper->getPropertyInfo() as $name => $property) {
      if ($name == $bundle_key) {
        continue;
      }

      if (!empty($property['setter callback']) && empty($property['field'])) {
        $form['values'][$name] = array(
          '#type' => 'textfield',
          '#title' => $property['label'],
          '#description' => isset($property['description']) ? $property['description'] : '',
          '#default_value' => isset($this->config['values'][$name]) ? $this->config['values'][$name] : NULL,
          '#required' => !empty($property['required']),
        );

        if (!empty($property['options list'])) {
          $form['values'][$name]['#type'] = 'select';
          if (isset($property['type']) && entity_property_list_extract_type($property['type'])) {
            $form['values'][$name]['#type'] = 'checkboxes';
            if (!is_array($form['values'][$name]['#default_value'])) {
              $form['values'][$name]['#default_value'] = array($form['values'][$name]['#default_value']);
            }
          }
          $form['values'][$name]['#options'] = $wrapper->$name->optionsList();
        }

        elseif (!empty($property['type']) && $property['type'] == 'boolean') {
          $form['values'][$name]['#type'] = 'checkbox';
        }
        // elseif (!empty($property['type']) && $property['type'] == 'date') {
        //   $form['values'][$name]['#type'] = 'date';
        // }
      }
    }
    return $form;
  }

  /**
   * Override parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
    $form = parent::configFormValidate($values);

    $wrapper = entity_metadata_wrapper($this->entityType());

    foreach ($wrapper->getPropertyInfo() as $name => $property) {
      if (!empty($property['setter callback']) && empty($property['field'])) {

        // Entity api won't accept empty date values.
        if (!empty($property['type']) && $property['type'] == 'date') {
          if (empty($values['values'][$name])) {
            unset($values['values'][$name]);
            continue;
          }
        }

        if (isset($property['type']) && array_key_exists($name, $values['values'])) {
          if (entity_property_list_extract_type($property['type']) && !is_array($values['values'][$name])) {
            $values['values'][$name] = array($values['values'][$name]);
          }
          // check if values empty first as all default values are optional
          if (!empty($values['values'][$name])) {
            $valid = entity_property_verify_data_type($values['values'][$name], $property['type']);
            if (!$valid) {
              form_set_error("values][$name", t('Invalid data value given. Be sure it matches the required data type and format.'));
            }
          }
        }
      }
    }
  }

  /**
   * Returns available mapping targets.
   */
  public function getMappingTargets() {
    // Get a wrapper with the right bundle info.

    $targets = parent::getMappingTargets();
    $info = array('bundle' => $this->bundle());

    $wrapper = entity_metadata_wrapper($this->entityType(), NULL, $info);
    // @todo: maybe restrict to data types feeds can deal with.
    foreach ($wrapper->getPropertyInfo() as $name => $property) {
      if (empty($property['field'])) {
        $targets[$name] = array(
          'name' => $property['label'],
          'description' => isset($property['description']) ? $property['description'] : NULL,
        );
      }
    }

    $entity_info = $this->entityInfo();
    $targets[$entity_info['entity keys']['id']]['optional_unique'] = TRUE;

    // Remove the bundle target.
    if (isset($entity_info['bundle keys']['bundle'])) {
      unset($targets[$entity_info['bundle keys']['bundle']]);
    }

    // Let other modules expose mapping targets.
    self::loadMappers();
    $type = $this->entityType();
    drupal_alter('feeds_processor_targets', $targets, $type, $info['bundle']);

    return $targets;
  }
}
