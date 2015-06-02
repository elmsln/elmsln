<?php

/**
 * @file
 * Shows the overview screen with all links to entities.
 */

/**
 * Menu callback: Show the layout list.
 */
function ds_layout_list() {
  $build = array();

  // All entities.
  $rows = array();
  $entities = entity_get_info();

  // Change label of node content type to 'Content' and move to the top
  if (isset($entities['node'])) {
    $node_entity = $entities['node'];
    $node_entity['label'] = 'Content';
    unset($entities['node']);
    $entities = array_merge(array('node' => $node_entity), $entities);
  }

  if (isset($entities['comment'])) {
    $comment_entity = $entities['comment'];
    unset($entities['comment']);
    $entities['comment'] = $comment_entity;
  }

  foreach ($entities as $entity_type => $entity) {
    if ((isset($entity['fieldable']) && $entity['fieldable']) || isset($entity['ds_display'])) {

      $rows = array();
      foreach ($entity['bundles'] as $bundle_type => $bundle) {
        $row = array();

        $path = isset($bundle['admin']['real path']) ? $bundle['admin']['real path'] : (isset($bundle['admin']['path']) ? $bundle['admin']['path'] : '');
        if (empty($path)) {
          continue;
        }

        $row[] = check_plain($bundle['label']);
        $links = array(l(t('Manage display'), $path . '/display'));
        // Add Mangage Form link if this entity type is supported by ds_forms.
        if (module_exists('ds_forms') && _ds_forms_is_entity_type_supported($entity_type)) {
          $links[] = l(t('Manage form'), $path . '/fields');
        }
        $row[] = implode(' - ', $links);
        $rows[] = $row;
      }

      if (!empty($rows)) {
        $variables = array(
          'header' => array(array('data' => $entity['label']), array('data' => t('operations'), 'class' => 'ds-display-list-options')),
          'rows' => $rows,
        );
        $build['list_' . $entity_type] = array(
          '#markup' => theme('table', $variables)
        );

        $entity_rows = array();
        $rows = array();
      }
    }
  }
  drupal_add_css(drupal_get_path('module', 'ds') . '/css/ds.admin.css');

  return $build;
}

/**
 * Emergency page.
 */
function ds_emergency() {

  $form['ds_fields_error'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fields error'),
  );

  $form['ds_fields_error']['ds_disable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable attaching fields via Display Suite'),
    '#description' => t('In case you get an error after configuring a layout printing a message like "Fatal error: Unsupported operand types", you can temporarily disable adding fields from DS by toggling this checkbox. You probably are trying to render an node inside a node, for instance through a view, which is simply not possible. See <a href="http://drupal.org/node/1264386">http://drupal.org/node/1264386</a>.'),
    '#default_value' => variable_get('ds_disable', FALSE),
    '#weight' => 0,
  );

  $form['ds_fields_error']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Disable/enable field attach'),
    '#submit' => array('ds_emergency_fields_attach'),
    '#weight' => 1,
  );

  if (module_exists('ds_extras')) {
    $region_blocks = variable_get('ds_extras_region_blocks', array());
    if (!empty($region_blocks)) {

      $region_blocks_options = array();
      foreach ($region_blocks as $key => $info) {
        $region_blocks_options[$key] = $info['title'];
      }

      $form['region_to_block'] = array(
        '#type' => 'fieldset',
        '#title' => t('Block regions'),
      );

      $form['region_to_block']['remove_block_region'] = array(
        '#type' => 'checkboxes',
        '#options' => $region_blocks_options,
        '#description' => t('In case you renamed a content type, you will not see the configured block regions anymore, however the block on the block settings page is still available. On this screen you can remove orphaned block regions.'),
      );

      $form['region_to_block']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Remove block regions'),
        '#submit' => array('ds_emergency_region_to_block_submit'),
        '#weight' => 1,
      );
    }
  }

  return $form;
}

/**
 * Submit callback of fields error form.
 */
function ds_emergency_fields_attach($form, &$form_state) {
  variable_set('ds_disable', $form_state['values']['ds_disable']);
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Submit callback of region to block form.
 */
function ds_emergency_region_to_block_submit($form, &$form_state) {
  if (isset($form_state['values']['remove_block_region'])) {
    $variable_set = FALSE;
    $region_blocks = variable_get('ds_extras_region_blocks', array());
    $remove = $form_state['values']['remove_block_region'];
    foreach ($remove as $key => $value) {
      if ($value != 0 && $key == $value) {
        $variable_set = TRUE;
        if (module_exists('block')) {
          db_delete('block')
            ->condition('delta', $key)
            ->condition('module', 'ds_extras')
            ->execute();
        }
        unset($region_blocks[$key]);
      }
    }

    if ($variable_set) {
      drupal_set_message(t('Block regions were removed.'));
      variable_set('ds_extras_region_blocks', $region_blocks);
    }
  }
  else {
    drupal_set_message(t('No block regions were removed.'));
  }
}
