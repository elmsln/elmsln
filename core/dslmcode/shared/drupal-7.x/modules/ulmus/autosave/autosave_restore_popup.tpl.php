<?php
/**
 * @file
 * Popup markup for restore form message.
 */
?>

<span id="status">
  <?php print t('This form was autosaved on @date', array('@date' => $autosave['savedDate'])); ?>
</span>
<span id="operations">
  <?php print $ignore_link . $restore_link; ?>
</span>
