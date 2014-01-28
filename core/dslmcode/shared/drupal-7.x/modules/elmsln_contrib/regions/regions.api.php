<?php
/**
 * @file
 * Hooks provided by Regions.
 */

/**
 * Hook allowing modules to define regions.
 *
 * @return
 *   An array of regions, keyed by region, containing:
 *   - title: the region title
 *   - css: optional path to stylesheet for theming the new region, relative to
 *     implementing module directory.
 *   - js: optional path to javascript file, relative to implementing module
 *     directory.
 *   - render_callback: optional function to use in rendering blocks of this
 *     region (will be passed 'block' and $block parameters).
 */
function hook_define_regions() {
  return array(
    'myregion1' => array(
      'title' => 'My region 1',
      'css' => drupal_get_path('module', 'mymodule') . '/css/style.css',
      'js' => drupal_get_path('module', 'mymodule') . '/js/script.js',
      'render_callback' => 'mymodule_callback',
    ),
    'myregion2' => array(
      'title' => 'My region 2',
    ),
  );
}

/**
 * Hook allowing other modules to alter the region array.
 *
 * This happens before the each element is concatenated into a string.
 *
 * @param array $region
 *   A keyed array of region HTML elements and strings, containing:
 *   - start: the region DIV with the $region_name as ID and 'regions' CLASS.
 *   - blocks: a string containing the themed blocks for this region, as
 *     returned by theme_block().
 *   - end: a closing DIV.
 * @param string $region_name
 *   machine name of the region being passed.
 *
 * @see regions_footer()
 * @see hook_regions_blocks_alter()
 */
function hook_regions_region_alter(&$region, $region_name) {
  // Example to add an inner DIV to the region markup.
  $new_markup = array(
    'start' => $region['start'],
    'inner' => '<div id="' . $region_name . '-inner">',
    'blocks' => $region['blocks'],
    'inner_end' => '</div>',
    'end' => $region['end'],
  );
  $region = $new_markup;
}

/**
 * Hook allowing other modules to alter any newly defined regions blocks.
 *
 * This happens before the each block object is rendered by theme_block().
 *
 * @param array $blocks
 *   A keyed array of block objects provided by core block and context modules.
 * @param string $region_name
 *   machine name of the region.
 *
 * @see _regions_blocks()
 * @see theme_block()
 */
function hook_regions_blocks_alter(&$blocks = array(), $region_name = NULL) {
  // Example to support HTML titles, with a safe but unorthodox workaround.
  foreach ($blocks as $key => $block) {
    $block->subject = filter_xss_admin(html_entity_decode($block->subject));
    $blocks[$key] = $block;
  }
}