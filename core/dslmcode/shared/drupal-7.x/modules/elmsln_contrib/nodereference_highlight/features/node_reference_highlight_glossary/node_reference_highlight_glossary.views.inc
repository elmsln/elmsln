<?php
/**
 * Implementation of hook_views_query_alter().
 */
function node_reference_highlight_glossary_views_query_alter(&$view, &$query) {
  // need to modify results based on those found in page
  if ($view->name == 'nrhi_term_glossary' && $view->current_display == 'block_1') {
    $nids = array();
    $node = menu_get_object();
    // make sure this node has content, otherwise we're wasting time
    if (isset($node->body) && !empty($node->body)) {
      // load all titles / nids of terms
      $result = db_select('node', 'n')
      ->fields('n', array('title', 'nid'))
      ->condition('type', 'nrhi_term')
      ->condition('status', 1)
      ->execute();
      // search for each title in the body of content
      $body = drupal_strtolower($node->body['und'][0]['value']);
      foreach ($result as $val) {
        // build an array of nids if found
        if (strpos($body, drupal_strtolower($val->title)) !== FALSE) {
          $nids[] = $val->nid;
        }
      }
      // didn't find matches, return nothing
      if (empty($nids)) {
        $nids = array(0);
      }
      // manually generate where clause with list of nids
      $query->where[1]['conditions'][] = array(
        'field' => 'node.nid',
        'value' => $nids,
        'operator' => 'in',
      );
    }
  }
}
