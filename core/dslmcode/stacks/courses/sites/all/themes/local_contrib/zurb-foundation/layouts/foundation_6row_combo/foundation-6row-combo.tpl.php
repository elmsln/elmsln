<?php
/**
 * @file
 * Template for a 6 row combo panel layout.
 *
 * This template provides a six row panel display layout see panel regions for more.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the bottom top row.
 *   - $content['top_first']: Content in the top first column.
 *   - $content['top_second']: Content in the top second column.
 *   - $content['top_third']: Content in the top third column.
 *   - $content['top_fourth']: Content in the top fourth column.
 *   - $content['middle_small']: Content in the middle small column.
 *   - $content['middle_large']: Content in the middle large column.
 *   - $content['middle_first']: Content in the middle first column.
 *   - $content['middle_second']: Content in the middle second column.
 *   - $content['bottom_first']: Content in the middle first column.
 *   - $content['bottom_second']: Content in the middle second column.
 *   - $content['bottom_third']: Content in the middle third column.
 *   - $content['bottom_fourth']: Content in the middle fourth column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>
<?php !empty($css_id) ? print '<div id="' . $css_id . '">' : ''; ?>
  <div class="row">
    <div class="large-12 columns"><?php print $content['top']; ?></div>
  </div>

  <div class="row">
    <div class="large-3 columns">
      <?php print $content['top_first']; ?>
    </div>
    <div class="large-3 columns">
      <?php print $content['top_second']; ?>
    </div>
    <div class="large-3 columns">
      <?php print $content['top_third']; ?>
    </div>
    <div class="large-3 columns">
      <?php print $content['top_fourth']; ?>
    </div>
  </div>

  <div class="row">
    <div class="large-3 columns">
      <?php print $content['middle_small']; ?>
    </div>
    <div class="large-9 columns">
      <?php print $content['middle_large']; ?>
    </div>
  </div>

  <div class="row">
    <div class="large-6 columns">
      <?php print $content['middle_first']; ?>
    </div>
    <div class="large-6 columns">
      <?php print $content['middle_second']; ?>
    </div>
  </div>

  <div class="row">
    <div class="large-3 columns">
      <?php print $content['bottom_first']; ?>
    </div>
    <div class="large-3 columns">
      <?php print $content['bottom_second']; ?>
    </div>
    <div class="large-3 columns">
      <?php print $content['bottom_third']; ?>
    </div>
    <div class="large-3 columns">
      <?php print $content['bottom_fourth']; ?>
    </div>
  </div>

  <div class="row">
    <div class="large-12 columns"><?php print $content['bottom']; ?></div>
  </div>
<?php !empty($css_id) ? print '</div>' : ''; ?>
