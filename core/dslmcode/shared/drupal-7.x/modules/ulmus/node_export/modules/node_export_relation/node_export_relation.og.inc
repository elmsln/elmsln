<?php

/**
 * @file
 * The Node export relation OG include.
 *
 * Helps maintain organic groups relationships between nodes during node export operations.
 */

/**
 *  Callback for OG settings form.
 */
function node_export_relation_settings_form_og(&$form, &$form_state) {
  $form['og'] = array(
    '#type' => 'fieldset',
    '#title' => t('Organic groups'),
  );
  $form['og']['node_export_og_auto_inc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically OG related related nodes in exports'),
    '#default' => variable_get('node_export_og_auto_inc', TRUE),
  );
  $form['og']['node_export_og_skip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip related OG nodes that cannot be exported'),
    '#default' => variable_get('node_export_og_skip', TRUE),
    '#description' => t('If this is disabled, node exports will fail if a related OG node cannot be exported, for example if the user performing the export does not have access.'),
  );
}

/**
 * Go through group nids and put group UUIDs in their place.
 */
function node_export_relation_og_set_group_uuids(&$nodes) {
  foreach ($nodes as &$node) {
    if (!empty($node->og_groups)) {
      foreach ($node->og_groups as $key => $group_nid) {
        $group_uuid = uuid_get_uuid('node', 'nid', $group_nid);
        // Create uuid if it doesn't exists
        if (empty($group_uuid)) {
          $group_uuid = uuid_set_uuid('node', 'nid', $group_nid);
        }

        $node->og_groups[$group_uuid] = $group_uuid;
        unset($node->og_groups[$key]);
        // Modify og_groups_both as well (gid => title).
        $group_title = $node->og_groups_both[$group_nid];
        $node->og_groups_both[$group_uuid] = $group_title;
        unset($node->og_groups_both[$group_nid]);
      }
    }

    // Support for og_subgroups.
    if (!empty($node->og_parent)) {
      $group_uuid = uuid_get_uuid('node', 'nid', $node->og_parent->nid);
      // Create uuid if it doesn't exists
      if (empty($group_uuid)) {
        $group_uuid = uuid_set_uuid('node', 'nid', $node->og_parent->nid);
      }
      $node->og_parent = $group_uuid;
    }
  }
}

/**
 * Go through group UUIDs and put group nids in their place.
 */
function node_export_relation_og_set_group_nids(&$nodes) {
  foreach ($nodes as &$node) {
    if (!empty($node->og_groups)) {
      foreach ($node->og_groups as $key => $group_uuid) {
        // If this is really a UUID, find the matching nid.
        if (uuid_is_valid($group_uuid)) {
          $group_nids = entity_get_id_by_uuid(array($group_uuid));
          $group_nid = $group_nids[$group_uuid];
          $node->og_groups[$group_nid] = $group_nid;
          unset($node->og_groups[$key]);

          // Modify og_groups_both as well (gid => title).
          $group_title = $node->og_groups_both[$group_uuid];
          $node->og_groups_both[$group_nid] = $group_title;
          unset($node->og_groups_both[$group_uuid]);
        }
      }
    }

    // Support for og_subgroups.
    if (!empty($node->og_parent) && is_string($node->og_parent)) {
      // Create uuid if it doesn't exists
      if (uuid_is_valid($node->og_parent)) {
        $group_nids = entity_get_id_by_uuid(array($group_uuid));
        $node->og_parent = $group_nids[$group_uuid];
      }
    }
  }
}
