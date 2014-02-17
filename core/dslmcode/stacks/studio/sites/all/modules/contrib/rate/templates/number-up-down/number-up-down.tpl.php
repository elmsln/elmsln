<?php

/**
 * @file
 * Rate widget theme
 */

?>

<?php print $up_button; ?>

<div class="rate-number-up-down-rating <?php print $score_class ?>"><?php print $score; ?></div>

<?php print $down_button; ?>

<?php

if ($info) {
  print '<div class="rate-info">' . $info . '</div>';
}

if ($display_options['description']) {
  print '<div class="rate-description">' . $display_options['description'] . '</div>';
}
