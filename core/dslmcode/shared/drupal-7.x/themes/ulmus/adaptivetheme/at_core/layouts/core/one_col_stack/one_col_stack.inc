<?php

/**
 * @file
 * Implimentation of a Page Layout Plugin for Adaptivetheme.
 *
 * @see three_col_grail.inc for detailed documentation.
 */
function one_col_stack() {
  $page_layout['one_col_stack'] = array(
    'title'    => t('One Column Stacked'),
    'category' => t('AT Core layout'),
    'method'   => 'one_col_stack',
    'type'     => 'page_layout',
    'device_groups' => array(
      'tablet_portrait',
      'smalltouch_landscape',
     ),
  );

  return $page_layout;
}

/**
 * CSS Builder for the one_col_stack layout.
 * Note: this is the only layout for smalltouch portrait, and for mobile first.
 * All columns and regions are 100% width, stacked.
 *
 * @param $sidebar_first, an arbitary numeric value.
 * @param $sidebar_second, an arbitary numeric value.
 * @param $sidebar_unit, a value unit, one of px, em or %.
 */
function one_col_stack_layout($sidebar_first, $sidebar_second, $sidebar_unit) {
  $styles = <<<EOF
div#content-column,div.content-inner,.sidebar-first div.content-inner,.sidebar-second div.content-inner,.two-sidebars div.content-inner,div.sidebar,.sidebar-first div.sidebar,.sidebar-second div.sidebar,.two-sidebars div.sidebar,div.region .block {float:none;clear:both;display:block;width:100%;margin-left:0;margin-right:0}
EOF;

  return $styles;
}
