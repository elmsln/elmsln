<?php
/**
 * @file
 * Theme definitions file for the Content type groups module.
 */
function theme_content_type_groups_group_form($vars) {

  $form = $vars['form'];

  $output = '';
  $header = array(
    '',
    t('Name'),
    t('Weight'),
  );
  $tbody = array();
  foreach ($form['content_types'] as $machine_name => $row) {

    if (strpos($machine_name, '#') === 0) {
      continue;
    }
    $tr = array(
      drupal_render($row['checked-' . $machine_name]),
      drupal_render($row['name']),
      drupal_render($row['weight-' . $machine_name]),
    );

    $tbody[] = array('data' => $tr, 'class' => array('draggable'));

  }

  // Add the subgroup widget
  /*
  $tr = array(
    drupal_render($form['subgroup']['checked']),
    drupal_render($form['subgroup']['name']),
    drupal_render($form['subgroup']['weight']),
  );
  $tbody[] = array('data' => $tr, 'class' => array('draggable'));
  */

  $id = 'ctg_items';
  drupal_add_tabledrag($id, 'order', 'sibling', 'weight');

  $form['content_types'] = array(
    '#type'   => 'markup',
    '#markup'  => theme('table', array(
                 'header'     => $header,
                 'rows'       => $tbody,
                 'attributes' => array('id' => $id),
               )),
    '#weight' => 1,
  );

  $output = drupal_render_children($form);
  return $output;
}
