<?php

/**
 * @file
 * Contains the HarmonySearchAlterThreadHidden class.
 */

/**
 * Exclude unpublished threads from indexes.
 */
class HarmonySearchAlterThreadHidden extends SearchApiAbstractAlterCallback {

  /**
   * Check whether this data-alter callback is applicable for a certain index.
   *
   * Returns TRUE only for indexes on threads.
   *
   * @param SearchApiIndex $index
   *   The index to check for.
   *
   * @return boolean
   *   TRUE if the callback can run on the given index; FALSE otherwise.
   */
  public function supportsIndex(SearchApiIndex $index) {
    return $index->getEntityType() === 'harmony_thread';
  }

  /**
   * Alter items before indexing.
   *
   * Items which are removed from the array won't be indexed, but will be marked
   * as clean for future indexing.
   *
   * @param array $items
   *   An array of items to be altered, keyed by item IDs.
   */
  public function alterItems(array &$items) {
    foreach ($items as $thread_id => &$item) {
      if (!empty($item->hidden) && $item->hidden == HARMONY_HIDDEN) {
        unset($items[$thread_id]);
      }
    }
  }
}
