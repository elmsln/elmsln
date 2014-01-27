<?php

/**
 * @file
 * Provides infrequently used functions and hooks for menu_block_export.
 */

/**
 * Page callback to export menu blocks in bulk.
 */
function menu_block_export_export() {
  $blocks = variable_get('menu_block_ids', array());

  if (!empty($blocks)) {
    $form_state = array(
      'no_redirect' => TRUE,
    );

    $output = drupal_build_form('menu_block_export_form', $form_state);
    if (!empty($form_state['output'])) {
      $output = $form_state['output'];
    }
    return $output;
  }
  else {
    return t('There are no menu blocks to be exported at this time.');
  }
}

/**
 * Menu callback; export form.
 *
 * @return
 *   The export form used by Menu block.
 */
function menu_block_export_form($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Module name'),
    '#default_value' => 'custom',
    '#description' => t('Enter the module name to export code to.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
  );

  $form['#action'] = url('admin/config/user-interface/menu-block/export/results');
  return $form;
}

/**
 * Submit callback for menu_block_export_form().
 */
function menu_block_export_form_submit(&$form, &$form_state) {
  $output = '';
  $module = check_plain($form_state['values']['name']);

  foreach (variable_get('menu_block_ids', array()) AS $delta) {
    $config = menu_block_get_config($delta);
    // Use the constant instead of the constant's value.
    if ($config['menu_name'] == MENU_TREE__CURRENT_PAGE_MENU) {
      $config['menu_name'] = 'MENU_TREE__CURRENT_PAGE_MENU';
    }
    else {
      // If it's not the constant, wrap value in quotes.
      $config['menu_name'] = "'" . $config['menu_name'] . "'";
    }
    $output .= <<<END_OF_CONFIG

    '$module-$delta' => array(
      'menu_name'   => {$config['menu_name']},
      'parent_mlid' => {$config['parent_mlid']},
      'title_link'  => {$config['title_link']},
      'admin_title' => '{$config['admin_title']}',
      'level'       => {$config['level']},
      'follow'      => {$config['follow']},
      'depth'       => {$config['depth']},
      'expanded'    => {$config['expanded']},
      'sort'        => {$config['sort']},
    ),
END_OF_CONFIG;
  }

  $output = <<<END_OF_CONFIG
/**
 * Implements hook_menu_block_blocks().
 */
function {$module}_menu_block_blocks() {
  // The array key is the block delta used by menu block.
  return array($output
  );
}

END_OF_CONFIG;

  $element = array(
    '#type' => 'textarea',
    '#title' => t('Use this in your !module.module file:', array('!module' => $module)),
    '#value' => $output,
    '#rows' => 20,
    // Since this isn't a real form, manually add additional required properties.
    '#id' => 'menu-block-export-textarea',
    '#name' => 'export',
    '#required' => FALSE,
    '#attributes' => array('style' => 'font-family: monospace;'),
    '#title_display' => 'before',
    '#parents' => array('dummy'),
  );
  $form_state['output'] = drupal_render($element);
}
