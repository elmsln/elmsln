<?php

/**
 * Harmony Thread selection handler.
 */
class HarmonyThreadSelectionPlugin extends EntityReference_SelectionHandler_Generic {
  /**
   * Implements EntityReferenceHandler::getInstance().
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new HarmonyThreadSelectionPlugin($field, $instance, $entity_type, $entity);
  }

  /**
   * Build an EntityFieldQuery to get referencable entities.
   */
  public function buildEntityFieldQuery($match = NULL, $match_operator = 'CONTAINS') {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $this->field['settings']['target_type']);
    if (!empty($this->field['settings']['handler_settings']['target_bundles'])) {
      $query->entityCondition('bundle', $this->field['settings']['handler_settings']['target_bundles'], 'IN');
    }
    if (isset($match)) {
      $query->propertyCondition('title', $match, $match_operator);
    }

    // Add an access tag to the query.
    $query->addTag('harmony_access');
    $query->addTag('entityreference');
    $query->addMetaData('field', $this->field);
    $query->addMetaData('entityreference_selection_handler', $this);

    // Adding the 'harmony_thread_access' tag is sadly insufficient for threads: core
    // requires us to also know about the concept of 'published' and
    // 'unpublished'. We need to do that as long as there are no access control
    // modules in use on the site. As long as one access control module is there,
    // it is supposed to handle this check.
    if ((!user_access('bypass harmony forum access control') || !user_access('administer harmony forum content')) && !count(module_implements('harmony_thread_grants'))) {
      $query->propertyCondition('status', HARMONY_PUBLISHED);
      $query->propertyCondition('locked', HARMONY_NOT_LOCKED);
    }

    // Add the sort option.
    if (!empty($this->field['settings']['handler_settings']['sort'])) {
      $sort_settings = $this->field['settings']['handler_settings']['sort'];
      if ($sort_settings['type'] == 'property') {
        $query->propertyOrderBy($sort_settings['property'], $sort_settings['direction']);
      }
      elseif ($sort_settings['type'] == 'field') {
        list($field, $column) = explode(':', $sort_settings['field'], 2);
        $query->fieldOrderBy($field, $column, $sort_settings['direction']);
      }
    }

    return $query;
  }
}
