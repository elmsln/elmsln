<?php
/**
 * @file
 * Defines fragment for fields.
 */

/**
 * Fragment handler for fields.
 *
 * @see field.module
 */
class AuthcacheFieldFragment implements AuthcacheP13nFragmentInterface, AuthcacheP13nFragmentLoaderInterface, AuthcacheP13nFragmentAccessInterface, AuthcacheP13nFragmentValidatorInterface {
  protected $entityType;
  protected $fieldName;

  /**
   * Construct new field fragment.
   *
   * @param string $entity_type
   *   The entity type, e.g., "node" or "taxonomy_term".
   *
   * @param string $field_name
   *   The field name, e.g., "body" or "field_tags".
   */
  public function __construct($entity_type, $field_name) {
    $this->entityType = $entity_type;
    $this->fieldName = $field_name;
  }

  /**
   * Split up the field specifier string.
   */
  public function validate($field_specifiers) {
    $result = array();

    foreach ($field_specifiers as $key) {
      list($entity_id, $view_mode, $language) = explode(':', $key);
      $result[$key] = array($entity_id, $view_mode, $language);
    }

    return $result;
  }

  /**
   * Load entities specified in the field specifier.
   */
  public function load($field_specifiers, $context) {
    $result = array();
    $entity_ids = array();

    foreach ($field_specifiers as $key => $specifier) {
      list($entity_id) = $specifier;
      $entity_ids[$entity_id] = $key;
    }

    $entities = entity_load($this->entityType, array_keys($entity_ids));

    foreach ($entities as $entity_id => $entity) {
      $key = $entity_ids[$entity_id];
      $specifier = $field_specifiers[$key];
      $result[$key] = array_merge(array($entity), $specifier);
    }

    return $result;
  }

  /**
   * {@inheritdoc}
   */
  public function check($account, $field_specifier, $args, $context) {
    list($entity) = $args;
    return entity_access('view', $this->entityType, $entity, $account) && field_access('view', field_info_field($this->fieldName), $this->entityType, $entity, $account);
  }

  /**
   * Render fields.
   */
  public function render($field_specifier, $args, $context) {
    list($entity, $entity_id, $view_mode, $language) = $args;
    unset($entity_id);

    $build = field_view_field($this->entityType, $entity, $this->fieldName, $view_mode, $language);

    // Remove extra markup, this has been rendered before.
    unset($build['#prefix']);
    unset($build['#suffix']);
    unset($build['#theme_wrappers']);

    return render($build);
  }
}
