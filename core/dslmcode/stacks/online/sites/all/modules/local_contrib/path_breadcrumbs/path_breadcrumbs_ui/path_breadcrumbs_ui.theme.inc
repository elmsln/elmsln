<?php

/**
 * @file
 *
 */

/**
 * @param $vars
 */
function theme_path_breadcrumbs_ui_add_form($vars) {
  return _path_breadcrumbs_render_table($vars);
}

/**
 * Theme table with path breadcrumbs values.
 * @param $vars
 */
function theme_path_breadcrumbs_ui_edit_form($vars) {
  return _path_breadcrumbs_render_table($vars);
}

/**
 * @param $vars
 * @return string
 */
function _path_breadcrumbs_render_table($vars) {
  $form = $vars['form'];

  if (isset($form['breadcrumbs_table'])) {
    $rows = array();
    foreach (element_children($form['breadcrumbs_table']) as $value) {
      $row = array();
      $input = $form['breadcrumbs_table'][$value];
      if (isset($input['left_value']) && isset($input['right_value']) && isset($input['delete'])) {
        $input['weight']['#attributes']['class'][] = 'path-weight';
        $row[] = array('data' => $input['left_value']);
        $row[] = array('data' => $input['right_value']);
        $row[] = array('data' => $input['weight']);
        $row[] = array('data' => $input['delete']);
        $rows[] = array(
          'data' => $row,
          'class' => array('draggable'),
        );
      }
    }

    unset($form['breadcrumbs_table']);

    $rows[] = array(
      'data' => array(array('data' => render($form['more']), 'colspan' => 4)),
    );

    $headers = array(t('Link title'), t('Link path'), t('Weight'), t('Delete link'));
    $output = theme('table', array(
      'header' => $headers,
      'rows' => $rows,
      'attributes' => array(
        'class' => array('breadcrumb-tokens'),
        'id' => 'breadcrumbs-table',
      ),
    ));

    // Build some other elements after table.
    $context_placeholders = render($form['contexts']);
    $custom = !empty($form['custom']) ? render($form['custom']) : '';
    $buttons = render($form['actions']);

    drupal_add_tabledrag('breadcrumbs-table', 'order', 'sibling', 'path-weight');

    return drupal_render_children($form) . $output . $context_placeholders . $custom . $buttons;
  }
}

/**
 * Theming function for path_breadcrumbs_ui_breadcrumbs_list form.
 */
function theme_path_breadcrumbs_ui_breadcrumbs_list($vars) {

  $form = $vars['form'];
  $rows = array();
  foreach (element_children($form) as $path_id) {
    if (isset($form[$path_id]['weight'])) {
      $row = array();
      $row[] = filter_xss_admin(render($form[$path_id]['title']));
      $row[] = check_plain(render($form[$path_id]['name']));
      $row[] = check_plain(render($form[$path_id]['path']));
      $row[] = render($form[$path_id]['actions']);
      $row[] = render($form[$path_id]['weight']);

      $class = 'enabled';
      if ($form[$path_id]['disabled']['#value'] == TRUE) {
        $class = 'disabled';
      }

      $rows[] = array(
        'data' => $row,
        'class' => array('draggable', $class),
      );
    }
  }

  if (empty($rows)) {
    $rows = array(array(
      'data' => array(array('data' => t('There are no created path breadcrumbs yet.'), 'colspan' => 5)),
    ));
  }

  $header = array(t('Title'), t('Name'), t('Path'), t('Actions'), t('Weight'));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'path-breadcrumbs-ui-table-list')));
  drupal_add_tabledrag('path-breadcrumbs-ui-table-list', 'order', 'sibling', 'path-breadcrumbs-ui-table-weight');
  return $output . drupal_render_children($form);
}

/**
 * Theme the table for argument settings form.
 */
function theme_path_breadcrumbs_ui_form_step_arguments_selection_table($vars) {

  $header = array(
    array('data' => t('Argument')),
    array('data' => t('Position in path')),
    array('data' => t('Context assigned')),
    array('data' => t('Operations')),
  );

  $form = $vars['form'];
  ctools_include('modal');
  ctools_modal_add_js();

  $rows = array();
  foreach (element_children($form['argument']) as $key) {
    $row   = array();
    $row[] = check_plain($form['argument'][$key]['#keyword']);
    $row[] = check_plain($form['argument'][$key]['#position']);
    $row[] = $form['argument'][$key]['#context'] . ' &nbsp; ' . drupal_render($form['argument'][$key]['change']);
    $row[] = drupal_render($form['argument'][$key]['settings']) . drupal_render($form['argument'][$key]);
    $rows[]  = array('data' => $row);
  }

  if (!$rows) {
    $rows[] = array(array('data' => t('The path %path has no arguments to configure.', array('%path' => $form['#breadcrumbs-path'])), 'colspan' => 4));
  }

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'path-breadcrumbs-ui-argument-table'),
  ));
}
