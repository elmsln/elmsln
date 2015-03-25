<?php
/**
 * @file
 * Contains the HarmonySearchAlterPostThreadAccess class.
 */

/**
 * Adds thread access information to harmony_thread indexes.
 */
class HarmonySearchAlterPostThreadAccess extends SearchApiAbstractAlterCallback {

  /**
   * Overrides SearchApiAbstractAlterCallback::supportsIndex().
   *
   * Returns TRUE only for indexes on harmony_thread.
   */
  public function supportsIndex(SearchApiIndex $index) {
    // Currently only harmony_thread access is supported.
    return $index->getEntityType() === 'harmony_post';
  }

  /**
   * Overrides SearchApiAbstractAlterCallback::propertyInfo().
   *
   * Adds the "harmony_search_thread_access" property.
   */
  public function propertyInfo() {
    return array(
      'harmony_search_post_thread_access' => array(
        'label' => t('Post thread access information'),
        'description' => t('Data needed to apply thread access.'),
        'type' => 'list<token>',
      ),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function alterItems(array &$items) {
    static $account;

    if (!isset($account)) {
      // Load the anonymous user.
      $account = drupal_anonymous_user();
    }

    foreach ($items as $id => $item) {
      $post = $this->getPost($item);
      $post_wrapper = entity_metadata_wrapper('harmony_post', $post);
      $thread_id = $post_wrapper->field_harmony_thread->value() ? $post_wrapper->field_harmony_thread->thread_id->value() : NULL;

      if ($thread_id) {
        $thread = harmony_thread_load($thread_id);

        if ($thread) {
          // Check whether all users have access to the thread.
          if (!harmony_core_thread_access_callback('view', $thread, $account)) {
            // Get thread access grants.
            $result = db_query('SELECT * FROM {harmony_access_records} WHERE (entity_id = 0 OR entity_id = :id) AND grant_view = 1 AND entity_type = :type', array(':id' => $thread->thread_id, ':type' => 'harmony_thread'));

            // Store all grants together with their realms in the item.
            foreach ($result as $grant) {
              $items[$id]->harmony_search_post_thread_access[] = "harmony_access_{$grant->realm}:{$grant->gid}";
            }
          }
          else {
            // Add the generic view grant if we are not using harmony access or the
            // thread is viewable by anonymous users.
            $items[$id]->harmony_search_post_thread_access = array('harmony_access__all');
          }
        }
      }
    }
  }

  /**
   * Retrieves the post related to a search item.
   *
   * In the default implementation for thread, the item is already the thread.
   * Subclasses may override this to easily provide thread access checks for
   * items related to threads.
   */
  protected function getPost($item) {
    return $item;
  }

  /**
   * Overrides SearchApiAbstractAlterCallback::configurationFormSubmit().
   *
   * If the data alteration is being enabled, set "Published" and "Author" to
   * "indexed", because both are needed for the thread access filter.
   */
  public function configurationFormSubmit(array $form, array &$values, array &$form_state) {
    $old_status = !empty($form_state['index']->options['data_alter_callbacks']['harmony_search_post_thread_access']['status']);
    $new_status = !empty($form_state['values']['callbacks']['harmony_search_post_thread_access']['status']);

    if (!$old_status && $new_status) {
      $form_state['index']->options['fields']['status']['type'] = 'boolean';
      $form_state['index']->options['fields']['uid']['type'] = 'integer';
      $form_state['index']->options['fields']['uid']['entity_type'] = 'user';
    }

    return parent::configurationFormSubmit($form, $values, $form_state);
  }
}
