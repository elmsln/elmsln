<?php

/**
 * Class for field_collection_item entities.
 */
class FieldCollectionItemEntity extends Entity {

  /**
   * Field collection field info.
   *
   * @var array
   */
  protected $fieldInfo;

  /**
   * The host entity object.
   *
   * @var object
   */
  protected $hostEntity;

  /**
   * The host entity ID.
   *
   * @var integer
   */
  protected $hostEntityId;

  /**
   * The host entity revision ID if this is not the default revision.
   *
   * @var integer
   */
  protected $hostEntityRevisionId;

  /**
   * The host entity type.
   *
   * @var string
   */
  protected $hostEntityType;

  /**
   * The language under which the field collection item is stored.
   *
   * @var string
   */
  protected $langcode = LANGUAGE_NONE;

  /**
   * Entity ID.
   *
   * @var integer
   */
  public $item_id;

  /**
   * Field collection revision ID.
   *
   * @var integer
   */
  public $revision_id;

  /**
   * The name of the field-collection field this item is associated with.
   *
   * @var string
   */
  public $field_name;

  /**
   * Whether this revision is the default revision.
   *
   * @var bool
   */
  public $default_revision = TRUE;

  /**
   * Whether the field collection item is archived, i.e. not in use.
   *
   * @see FieldCollectionItemEntity::isInUse()
   * @var bool
   */
  public $archived = FALSE;

  /**
   * Constructs the entity object.
   */
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'field_collection_item');
    // Workaround issues http://drupal.org/node/1084268 and
    // http://drupal.org/node/1264440:
    // Check if the required property is set before checking for the field's
    // type. If the property is not set, we are hitting a PDO or a core's bug.
    // FIXME: Remove when #1264440 is fixed and the required PHP version is
    //  properly identified and documented in the module documentation.
    if (isset($this->field_name)) {
      // Ok, we have the field name property, we can proceed and check the field's type
      $field_info = $this->fieldInfo();
      if (!$field_info || $field_info['type'] != 'field_collection') {
        throw new Exception("Invalid field name given: {$this->field_name} is not a Field Collection field.");
      }
    }
  }

  /**
   * Provides info about the field on the host entity, which embeds this
   * field collection item.
   */
  public function fieldInfo() {
    return field_info_field($this->field_name);
  }

  /**
   * Provides info of the field instance containing the reference to this
   * field collection item.
   */
  public function instanceInfo() {
    if ($this->fetchHostDetails()) {
      return field_info_instance($this->hostEntityType(), $this->field_name, $this->hostEntityBundle());
    }
  }

  /**
   * Returns the field instance label translated to interface language.
   */
  public function translatedInstanceLabel($langcode = NULL) {
    if ($info = $this->instanceInfo()) {
      if (module_exists('i18n_field')) {
        return i18n_string("field:{$this->field_name}:{$info['bundle']}:label", $info['label'], array('langcode' => $langcode));
      }
      return $info['label'];
    }
  }

  /**
   * Specifies the default label, which is picked up by label() by default.
   */
  public function defaultLabel() {
    if ($this->fetchHostDetails()) {
      $field = $this->fieldInfo();
      $label = $this->translatedInstanceLabel();
      $host  = $this->hostEntity();

      if ($new_label = module_invoke_all('field_collection_item_label', $this, $host, $field, $label)) {
        return array_pop($new_label);
      }
      elseif ($field['cardinality'] == 1) {
        return $label;
      }
      elseif ($this->item_id) {
        return t('!instance_label @count', array('!instance_label' => $label, '@count' => $this->delta() + 1));
      }
      else {
        return t('New !instance_label', array('!instance_label' => $label));
      }
    }
    return t('Unconnected field collection item');
  }

  /**
   * Returns the path used to view the entity.
   */
  public function path() {
    if ($this->item_id) {
      return field_collection_field_get_path($this->fieldInfo()) . '/' . $this->item_id;
    }
  }

  /**
   * Returns the URI as returned by entity_uri().
   */
  public function defaultUri() {
    return array(
      'path' => $this->path(),
    );
  }

  /**
   * Sets the host entity. Only possible during creation of a item.
   *
   * @param $create_link
   *   (optional) Whether a field-item linking the host entity to the field
   *   collection item should be created.
   */
  public function setHostEntity($entity_type, $entity, $langcode = LANGUAGE_NONE, $create_link = TRUE) {
    if (!empty($this->is_new)) {
      $this->hostEntityType = $entity_type;
      $this->hostEntity = $entity;
      $this->langcode = $langcode;

      list($this->hostEntityId, $this->hostEntityRevisionId) = entity_extract_ids($this->hostEntityType, $this->hostEntity);
      // If the host entity is not saved yet, set the id to FALSE. So
      // fetchHostDetails() does not try to load the host entity details.
      if (!isset($this->hostEntityId)) {
        $this->hostEntityId = FALSE;
      }
      // We are create a new field collection for a non-default entity, thus
      // set archived to TRUE.
      if (!entity_revision_is_default($entity_type, $entity)) {
        $this->hostEntityId = FALSE;
        $this->archived = TRUE;
      }
      if ($create_link) {
        $entity->{$this->field_name}[$this->langcode][] = array('entity' => $this);
      }
    }
    else {
      throw new Exception('The host entity may be set only during creation of a field collection item.');
    }
  }

  /**
   * Updates the wrapped host entity object.
   *
   * @param object $entity
   *   Host entity.
   * @param string $host_entity_type
   *   The entity type of the entity the field collection is attached to.
   */
  public function updateHostEntity($entity, $host_entity_type = NULL) {
    $this->fetchHostDetails();
    // If it isn't possible to retrieve hostEntityType due to the fact that it's
    // not saved in the DB yet then fill in info about the hostEntity manually.
    // This happens when creating a new revision of a field collection entity
    // and it needs to relate to the new revision of the host entity.
    if (!$this->hostEntityType) {
      $this->hostEntityType = $host_entity_type;
      $this->hostEntity = $entity;
      list($this->hostEntityId, $this->hostEntityRevisionId) = entity_extract_ids($this->hostEntityType, $this->hostEntity);
    }
    list($recieved_id) = entity_extract_ids($this->hostEntityType, $entity);

    if ($this->isInUse()) {
      $current_id = $this->hostEntityId;
    }
    else {
      $current_host = entity_revision_load($this->hostEntityType, $this->hostEntityRevisionId);
      list($current_id) = entity_extract_ids($this->hostEntityType, $current_host);
    }

    if ($current_id == $recieved_id) {
      $this->hostEntity = $entity;
      $delta = $this->delta();
      if (isset($entity->{$this->field_name}[$this->langcode()][$delta]['entity'])) {
        $entity->{$this->field_name}[$this->langcode()][$delta]['entity'] = $this;
      }
    }
    else {
      throw new Exception('The host entity cannot be changed.');
    }
  }

  /**
   * Returns the host entity, which embeds this field collection item.
   */
  public function hostEntity() {
    if ($this->fetchHostDetails()) {
      if (!isset($this->hostEntity) && $this->isInUse()) {
        $this->hostEntity = entity_load_single($this->hostEntityType, $this->hostEntityId);
      }
      elseif (!isset($this->hostEntity) && $this->hostEntityRevisionId) {
        $this->hostEntity = entity_revision_load($this->hostEntityType, $this->hostEntityRevisionId);
      }
      return $this->hostEntity;
    }
  }

  /**
   * Returns the entity type of the host entity, which embeds this
   * field collection item.
   */
  public function hostEntityType() {
    if ($this->fetchHostDetails()) {
      return $this->hostEntityType;
    }
  }

  /**
   * Returns the id of the host entity, which embeds this field collection item.
   */
  public function hostEntityId() {
    if ($this->fetchHostDetails()) {
      if (!$this->hostEntityId && $this->hostEntityRevisionId) {
        $this->hostEntityId = entity_id($this->hostEntityType, $this->hostEntity());
      }
      return $this->hostEntityId;
    }
  }

  /**
   * Returns the bundle of the host entity, which embeds this field collection
   * item.
   */
  public function hostEntityBundle() {
    if ($entity = $this->hostEntity()) {
      list($id, $rev_id, $bundle) = entity_extract_ids($this->hostEntityType, $entity);
      return $bundle;
    }
  }

  protected function fetchHostDetails() {
    if (!isset($this->hostEntityId)) {
      if ($this->item_id) {
        // For saved field collections, query the field data to determine the
        // right host entity.
        $query = new EntityFieldQuery();
        $query->fieldCondition($this->fieldInfo(), 'revision_id', $this->revision_id);
        if (!$this->isInUse()) {
          $query->age(FIELD_LOAD_REVISION);
        }
        $result = $query->execute();
        list($this->hostEntityType, $data) = each($result);

        if ($this->isInUse()) {
          $this->hostEntityId = $data ? key($data) : FALSE;
          $this->hostEntityRevisionId = FALSE;
        }
        // If we are querying for revisions, we get the revision ID.
        else {
          $this->hostEntityId = FALSE;
          $this->hostEntityRevisionId = $data ? key($data) : FALSE;
        }
      }
      else {
        // No host entity available yet.
        $this->hostEntityId = FALSE;
      }
    }
    return !empty($this->hostEntityId) || !empty($this->hostEntity) || !empty($this->hostEntityRevisionId);
  }

  /**
   * Determines the $delta of the reference pointing to this field collection
   * item.
   */
  public function delta() {
    if (($entity = $this->hostEntity()) && isset($entity->{$this->field_name})) {
      foreach ($entity->{$this->field_name} as $langcode => &$data) {
        if (!empty($data)) {
          foreach ($data as $delta => $item) {
            if (isset($item['value']) && $item['value'] == $this->item_id) {
              $this->langcode = $langcode;
              return $delta;
            }
            elseif (isset($item['entity']) && $item['entity'] === $this) {
              $this->langcode = $langcode;
              return $delta;
            }
          }
        }
      }
      // If we don't find the delta in the current values (cause the item
      // is being deleted, for example), we search the delta in the originalcontent.
      if (!empty($entity->original)) {
        foreach ($entity->original->{$this->field_name} as $langcode => &$data) {
          if (!empty($data)) {
            foreach ($data as $delta => $item) {
              if (isset($item['value']) && $item['value'] == $this->item_id) {
                $this->langcode = $langcode;
                return $delta;
              }
              elseif (isset($item['entity']) && $item['entity'] === $this) {
                $this->langcode = $langcode;
                return $delta;
              }
            }
          }
        }
      }
    }
  }

  /**
   * Determines the language code under which the item is stored.
   */
  public function langcode() {
    if ($this->delta() === NULL || empty($this->langcode)) {
      $this->langcode = field_collection_entity_language('field_collection_item', $this);
    }

    if (empty($this->langcode) || ($this->langcode != LANGUAGE_NONE && (!module_exists('entity_translation') || !entity_translation_enabled('field_collection_item')))) {
      $this->langcode = LANGUAGE_NONE;
    }

    return $this->langcode;
  }

  /**
   * Determines whether this field collection item revision is in use.
   *
   * Field collection items may be contained in from non-default host entity
   * revisions. If the field collection item does not appear in the default
   * host entity revision, the item is actually not used by default and so
   * marked as 'archived'.
   * If the field collection item appears in the default revision of the host
   * entity, the default revision of the field collection item is in use there
   * and the collection is not marked as archived.
   */
  public function isInUse() {
    return $this->default_revision && !$this->archived;
  }

  /**
   * Save the field collection item.
   *
   * By default, always save the host entity, so modules are able to react
   * upon changes to the content of the host and any 'last updated' dates of
   * entities get updated.
   *
   * For creating an item a host entity has to be specified via setHostEntity()
   * before this function is invoked. For the link between the entities to be
   * fully established, the host entity object has to be updated to include a
   * reference on this field collection item during saving. So do not skip
   * saving the host for creating items.
   *
   * @param $skip_host_save
   *   (internal) If TRUE is passed, the host entity is not saved automatically
   *   and therefore no link is created between the host and the item or
   *   revision updates might be skipped. Use with care.
   */
  public function save($skip_host_save = FALSE) {
    // Make sure we have a host entity during creation.
    if (!empty($this->is_new) && !(isset($this->hostEntityId) || isset($this->hostEntity) || isset($this->hostEntityRevisionId))) {
      throw new Exception("Unable to create a field collection item without a given host entity.");
    }

    // Copy the values of translatable fields for a new field collection item.
    if (field_collection_item_is_translatable() && !empty($this->is_new) && $this->langcode() == LANGUAGE_NONE) {
      $this->copyTranslations();
    }

    // Only save directly if we are told to skip saving the host entity. Else,
    // we always save via the host as saving the host might trigger saving
    // field collection items anyway (e.g. if a new revision is created).
    if ($skip_host_save) {
      return entity_get_controller($this->entityType)->save($this);
    }
    else {
      $host_entity = $this->hostEntity();
      if (!$host_entity) {
        throw new Exception("Unable to save a field collection item without a valid reference to a host entity.");
      }
      // If this is creating a new revision, also do so for the host entity.
      if (!empty($this->revision) || !empty($this->is_new_revision)) {
        $host_entity->revision = TRUE;
        if (!empty($this->default_revision)) {
          entity_revision_set_default($this->hostEntityType, $host_entity);
        }
      }
      // Set the host entity reference, so the item will be saved with the host.
      // @see field_collection_field_presave()
      $delta = $this->delta();
      if (isset($delta)) {
        $host_entity->{$this->field_name}[$this->langcode()][$delta] = array('entity' => $this);
      }
      else {
        $host_entity->{$this->field_name}[$this->langcode()][] = array('entity' => $this);
      }

      return entity_save($this->hostEntityType, $host_entity);
    }
  }

  /**
   * Deletes the field collection item and the reference in the host entity.
   */
  public function delete() {
    parent::delete();
    $this->deleteHostEntityReference();
  }

  /**
   * Copies text to all languages the collection item has a translation for.
   *
   * @param $source_language
   *   Language code to copy the text from.
   */
  public function copyTranslations($source_language = NULL) {
    // Get a handler for Entity Translation if there is one.
    $host_et_handler = NULL;
    if (module_exists('entity_translation')) {
      $host_et_handler = entity_translation_get_handler($this->hostEntityType(), $this->hostEntity());
    }
    if (is_null($host_et_handler)) {
      return;
    }

    $host_languages = array_keys($host_et_handler->getTranslations()->data);
    if (empty($host_languages)) {
      $host_languages = array(entity_language($this->hostEntityType(), $this->hostEntity()));
    }
    $source_language = isset($source_language) ? $source_language : $host_et_handler->getLanguage();
    $target_languages = array_diff($host_languages, array($source_language));
    $fields_instances = array_keys(field_info_instances('field_collection_item', $this->field_name));
    $fields = field_info_fields();

    foreach ($fields_instances as $translatable_field) {
      if ($fields[$translatable_field]['translatable'] == 1) {
        foreach ($target_languages as $langcode) {
          if (isset($this->{$translatable_field}[$source_language])) {
            //Source (translatable_field) is set, therefore continue processing.
            if(!isset($this->{$translatable_field}[$langcode])) {
              //Destination (translatable_field) is not set, therefore safe to copy the translation.
              $this->{$translatable_field}[$langcode] = $this->{$translatable_field}[$source_language];
            }
          }
        }
        if ($source_language == LANGUAGE_NONE && count($this->{$translatable_field}) > 1) {
          $this->{$translatable_field}[$source_language] = NULL;
        }
      }
    }
  }

  /**
   * Deletes the host entity's reference of the field collection item.
   */
  protected function deleteHostEntityReference() {
    $delta = $this->delta();
    if ($this->item_id && isset($delta)) {
      unset($this->hostEntity->{$this->field_name}[$this->langcode()][$delta]);
      // Do not save when the host entity is being deleted. See
      // field_collection_field_delete().
      if (empty($this->hostEntity->field_collection_deleting)) {
        entity_save($this->hostEntityType(), $this->hostEntity());
      }
    }
  }

  /**
   * Intelligently delete a field collection item revision.
   *
   * If a host entity is revisioned with its field collection items, deleting
   * a field collection item on the default revision of the host should not
   * delete the collection item from archived revisions too. Instead, we delete
   * the current default revision and archive the field collection.
   */
  public function deleteRevision($skip_host_update = FALSE) {
    if (!$this->revision_id) {
      return;
    }

    if (!$skip_host_update) {
      // Just remove the item from the host, which cares about deleting the
      // item (depending on whether the update creates a new revision).
      $this->deleteHostEntityReference();
    }

    if (!$this->isDefaultRevision()) {
      entity_revision_delete('field_collection_item', $this->revision_id);
    }
    // If deleting the default revision, take care!
    else {
      $row = db_select('field_collection_item_revision', 'r')
        ->fields('r')
        ->condition('item_id', $this->item_id)
        ->condition('revision_id', $this->revision_id, '<>')
        ->execute()
        ->fetchAssoc();

      if ($row) {
        // Make the other revision the default revision and archive the item.
        db_update('field_collection_item')
          ->fields(array('archived' => 1, 'revision_id' => $row['revision_id']))
          ->condition('item_id', $this->item_id)
          ->execute();
        entity_get_controller('field_collection_item')->resetCache(array($this->item_id));
        entity_revision_delete('field_collection_item', $this->revision_id);
      }
      if (!$row && !isset($this->hostEntity()->{$this->field_name}[$this->langcode()][$this->delta()])) {
        // Delete if there is no existing revision or translation to be saved.
        $this->delete();
      }
    }
  }

  /**
   * Export the field collection item.
   *
   * Since field collection entities are not directly exportable (i.e., do not
   * have 'exportable' set to TRUE in hook_entity_info()) and since Features
   * calls this method when exporting the field collection as a field attached
   * to another entity, we return the export in the format expected by
   * Features, rather than in the normal Entity::export() format.
   */
  public function export($prefix = '') {
    // Based on code in EntityDefaultFeaturesController::export_render().
    $export = "entity_import('" . $this->entityType() . "', '";
    $export .= addcslashes(parent::export(), '\\\'');
    $export .= "')";
    return $export;
  }

  /**
   * Generate an array for rendering the field collection item.
   */
  public function view($view_mode = 'full', $langcode = NULL, $page = NULL) {
    // Allow modules to change the view mode.
    $view_mode = key(entity_view_mode_prepare($this->entityType, array($this->item_id => $this), $view_mode, $langcode));
    return parent::view($view_mode, $langcode, $page);
  }

  /**
   * Magic method to only serialize what's necessary.
   */
  public function __sleep() {
    $vars = get_object_vars($this);
    unset($vars['entityInfo'], $vars['idKey'], $vars['nameKey'], $vars['statusKey']);
    unset($vars['fieldInfo']);
    // Also do not serialize the host entity, but only if it has already an id.
    if ($this->hostEntity && ($this->hostEntityId || $this->hostEntityRevisionId)) {
      unset($vars['hostEntity']);
    }

    // Also key the returned array with the variable names so the method may
    // be easily overridden and customized.
    return drupal_map_assoc(array_keys($vars));
  }

  /**
   * Magic method to invoke setUp() on unserialization.
   *
   * @todo: Remove this once it appears in a released entity API module version.
   */
  public function __wakeup() {
    $this->setUp();
  }
}
