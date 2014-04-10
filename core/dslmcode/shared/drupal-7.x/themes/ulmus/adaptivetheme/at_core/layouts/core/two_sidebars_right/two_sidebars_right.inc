<?php

/**
 * @file
 * Implimentation of a Page Layout Plugin for Adaptivetheme.
 *
 * @see three_col_grail.inc for detailed documentation.
 */
function two_sidebars_right() {
  $page_layout['two_sidebars_right'] = array(
    'title'    => t('Two Sidebars Right'),
    'category' => t('AT Core layout'),
    'method'   => 'two_sidebars_right',
    'type'     => 'page_layout',
    'device_groups' => array(
      'bigscreen',
      'tablet_landscape',
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the two_sidebars_right layout.
 * Positions both sidebars to the right of the main content column.
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.
 */
function two_sidebars_right_layout($sidebar_first, $sidebar_second, $sidebar_unit) {

  $left = 'left';
  $right = 'right';

  $content_margin = $sidebar_second + $sidebar_first . $sidebar_unit;
  $sidebar_first  = $sidebar_first . $sidebar_unit;
  $sidebar_second = $sidebar_second . $sidebar_unit;
  $push_left      = $sidebar_first;
  $push_right     = $sidebar_second;
  $left_margin    = $content_margin;
  $right_margin   = $sidebar_second;

  $styles = <<<EOF
#content-column,.content-column,div.sidebar {float: left; clear: none}
.two-sidebars .content-inner {margin-$right: $content_margin; margin-$left: 0}
.sidebar-first .content-inner {margin-$right: $push_left; margin-$left: 0}
.sidebar-second .content-inner {margin-$right: $push_right; margin-$left: 0}
.region-sidebar-first {width: $sidebar_first; margin-$left: -$left_margin}
.region-sidebar-second {width: $sidebar_second; margin-$left: -$right_margin}
.sidebar-first .region-sidebar-first {width: $sidebar_first; margin-$left: -$sidebar_first}
EOF;

  return $styles;
}
