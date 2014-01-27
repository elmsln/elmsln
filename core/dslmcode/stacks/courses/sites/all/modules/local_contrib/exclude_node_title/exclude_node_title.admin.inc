<?php
// $Id$
/**
 * @file
 * Exclude Node Title Administrative Interface
 *
 * @author Gabriel Ungureanu
 * gabriel.ungreanu@ag-prime.com
 */

/**
 * Admin configuration form
 */
function exclude_node_title_admin_settings() {
  $form['exclude_node_title_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove node title from search pages'),
    '#description' => t('Select if you wish to remove title from search pages. You need to have Search module !url.', array('!url' => l(t('enabled'), 'admin/modules/list'))),
    '#default_value' => variable_get('exclude_node_title_search', 0),
    '#disabled' => !module_exists('search')
  );

  $form['exclude_node_title_translation_sync'] = array(
    '#type' => 'checkbox',
    '#title' => t('Syncronize content translations'),
    '#description' => t('If you hide title from one node, it will automatically hide title for all the translated versions of that node. You need to have Content translation module !url.', array('!url' => l(t('enabled'), 'admin/modules/list'))),
    '#default_value' => variable_get('exclude_node_title_translation_sync', TRUE),
    '#disabled' => !module_exists('translation')
  );

  $form['exclude_node_title_content_type'] = array(
    '#type' => 'fieldset',
    '#title' => t('Exclude title by content-types'),
    '#description' => t('Define title excluding settings for each content type.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $node_types = _node_types_build()->names;
  foreach ($node_types as $node_type => $node_type_label) {
    $form['exclude_node_title_content_type']['exclude_node_title_content_type_value_' . $node_type] = array(
      '#type' => 'select',
      '#title' => $node_type_label,
      '#default_value' => variable_get('exclude_node_title_content_type_value_' . $node_type, 'none'),
      '#options' => array('none' => t('None'), 'all' => t('All nodes'), 'user' => t('User defined nodes')),
    );

    $entity_info = entity_get_info('node');
    $view_modes = $entity_info['view modes'];
    $modes = array();
    foreach ($view_modes as $view_mode_name => $view_mode_info) {
      $modes[$view_mode_name] = $view_mode_info['label'];
    }
    $modes += array('nodeform' => t('Node form'));

    $form['exclude_node_title_content_type']['exclude_node_title_content_type_modes_' . $node_type] = array(
      '#type' => 'checkboxes',
      '#title' => t('Exclude from:'),
      '#default_value' => variable_get('exclude_node_title_content_type_modes_' . $node_type, array()),
      '#options' => $modes,
      '#states' => array(
        // Hide the modes when the content type value is <none>.
        'invisible' => array(
         'select[name="exclude_node_title_content_type_value_' . $node_type . '"]' => array('value' => 'none'),
        ),
      ),
    );
  }

  return system_settings_form($form);
}
