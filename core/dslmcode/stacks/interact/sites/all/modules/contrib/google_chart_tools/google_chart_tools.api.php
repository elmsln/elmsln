<?php
/**
 * @file
 * Google Chart Tools API definitions.
 */

/**
 * Implements hook_draw_chart_alter().
 */
function hook_draw_chart_alter(&$settings) {
  foreach ($settings as $chart) {
    if (isset($chart['chart']['chartCategory']) && !empty($chart['chart']['chartCategory'])) {
      // Geting the count result by vocabulary machine name.
      $voc = taxonomy_vocabulary_machine_name_load('categories');
      $tree = taxonomy_get_tree($voc->vid);
      $header = array();
      foreach ($tree as $term) {
        // Feeds the header with terms names.
        $header[] = $term->name;
        $query = db_select('taxonomy_index', 'ti');
        $query->condition('ti.tid', $term->tid, '=')
              ->fields('ti', array('nid'));
        // Feeding the terms with the node count.
        $terms[] = $query->countQuery()->execute()->fetchField();
      }
      $columns = array('Content per category');
      $rows = array($terms);
      // Replacing the data of the chart.
      $chart['chart']['chartCategory']['header'] = $header;
      $chart['chart']['chartCategory']['rows'] = $rows;
      $chart['chart']['chartCategory']['columns'] = $columns;
      // Adding a colors attribute to the pie.
      $chart['chart']['chartCategory']['options']['colors'] = array('red', '#004411');
    }
  }
}

/**
 * Implements hook_gct_types_alter().
 */
function hook_gct_types_alter(&$types) {
  $types['OrgChart'] = t('Organizational Chart');
}