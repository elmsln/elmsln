<?php

/**
 * @file
 * Default theme implementation for the Checklist API progress bar.
 *
 * Available variables:
 * - $message: The progress message.
 * - $number_complete: The number of items complete.
 * - $number_of_items: The total number of items.
 * - $percent_complete: The percent of items complete.
 *
 * @see template_preprocess()
 * @see template_preprocess_checklistapi_progress_bar()
 * @see template_process()
 */
?>
<div class="progress">
  <div class="bar"><div class="filled" style="width:<?php print $percent_complete; ?>%;"></div></div>
  <div class="percentage"><?php print $number_complete; ?> of <?php print $number_of_items; ?> (<?php print $percent_complete; ?>%)</div>
  <div class="message"><?php print $message; ?></div>
</div>
