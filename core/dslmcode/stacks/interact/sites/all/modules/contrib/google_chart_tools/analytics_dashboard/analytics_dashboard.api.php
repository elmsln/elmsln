<?php
/**
 * @file
 * Analytics Dashboard API definitions.
 */

/**
 * Implements hook_analytics_dashboard().
 */
function hook_analytics_dashboard() {
  $voc = taxonomy_vocabulary_machine_name_load('categories');
  $tree = taxonomy_get_tree($voc->vid);
  $header = array();
  foreach ($tree as $term) {
    $header[] = $term->name;
    $query = db_select('taxonomy_index', 'ti');
    $query->condition('ti.tid', $term->tid, '=')
          ->fields('ti', array('nid'));
    $terms[] = $query->countQuery()->execute()->fetchField();

  }
  $columns = array('Ideas in category');
  $rows = array($terms);

  $settings = array();
  $settings['chart']['chartCategory'] = array(
    'header' => $header,
    'rows' => $rows,
    'columns' => $columns,
    'weight' => -10,
    'chartType' => 'PieChart',
    'options' => array(
      'curveType' => "function",
      'is3D' => TRUE,
      'forceIFrame' => FALSE,
      'title' => 'Ideas per category',
      'width' => 500,
      'height' => 300
    )
  );
  
  return draw_chart($settings);
}