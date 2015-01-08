<?php
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * each column roughly equal in width. It is 5 rows high; the top
 * middle and bottom rows contain 1 column, while the second
 * and fourth rows contain 2 columns.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['above_left']: Content in the left column in row 2.
 *   - $content['above_right']: Content in the right column in row 2.
 *   - $content['middle']: Content in the middle row.
 *   - $content['below_left']: Content in the left column in row 4.
 *   - $content['below_right']: Content in the right column in row 4.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>
<?php !empty($css_id) ? print '<div id="' . $css_id . '">' : ''; ?>
  <div class="row">
    <div class="large-12 columns"><?php print $content['top']; ?></div>
  </div>

  <div class="row">
    <div class="large-6 columns">
      <?php print $content['above_left']; ?>
    </div>
    <div class="large-6 columns">
      <?php print $content['above_right']; ?>
    </div>
  </div>

  <div class="row">
    <div class="large-12 columns"><?php print $content['middle']; ?></div>
  </div>

  <div class="row">
    <div class="large-6 columns">
      <?php print $content['below_left']; ?>
    </div>

    <div class="large-6 columns">
      <?php print $content['below_right']; ?>
    </div>
  </div>

  <div class="row">
    <div class="large-12 columns"><?php print $content['bottom']; ?></div>
  </div>
<?php !empty($css_id) ? print '</div>' : ''; ?>
