<?php

/**
 * @file
 * Implimentation of a Page Layout Plugin for Adaptivetheme.
 *
 * @see three_col_grail.inc for detailed documentation.
 */
function one_col_vert() {
  $page_layout['one_col_vert'] = array(
    'title'    => t('One Column Vertical Sidebars'),
    'category' => t('AT Core layout'),
    'method'   => 'one_col_vert',
    'type'     => 'page_layout',
    'device_groups' => array(
      'tablet_portrait',
      'smalltouch_landscape',
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the one_col_vert layout.
 * Displays sidebars vertically side by side beneath the main content column.
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.
 */
function one_col_vert_layout($sidebar_first, $sidebar_second, $sidebar_unit) {

  $one_sidebar    = $sidebar_first + $sidebar_second . $sidebar_unit;
  $sidebar_first  = $sidebar_first . $sidebar_unit;
  $sidebar_second = $sidebar_second . $sidebar_unit;

  $styles = <<<EOF
.two-sidebars .content-inner,.one-sidebar .content-inner,.region-sidebar-first,.region-sidebar-second {margin-left: 0; margin-right: 0}
.region-sidebar-first {width: $sidebar_first}
.region-sidebar-second {width: $sidebar_second}
.one-sidebar .sidebar {width: $one_sidebar}
.region-sidebar-first,.region-sidebar-second {overflow: hidden; margin-top: 20px; float: left; clear: none}
.region-sidebar-first.block,.region-sidebar-second .block {width: 100%}
EOF;

  return $styles;
}
