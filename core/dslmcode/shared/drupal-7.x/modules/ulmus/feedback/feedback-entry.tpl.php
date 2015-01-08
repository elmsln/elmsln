<?php
// $Id$

/**
 * @file
 * Default theme implementation to present a feedback entry.
 *
 * @see template_preprocess_feedback_entry()
 */
?>
<div class="feedback-entry"<?php print $attributes; ?>>
  <div class="field">
    <div class="field-label"><?php print t('Location'); ?>:&nbsp;</div>
    <?php print $location; ?>
  </div>
  <div class="field">
    <div class="field-label"><?php print t('Date'); ?>:&nbsp;</div>
    <?php print $date; ?>
  </div>
  <div class="field">
    <div class="field-label"><?php print t('User'); ?>:&nbsp;</div>
    <?php print $account; ?>
  </div>
  <div class="field">
    <div class="field-label"><?php print t('Message'); ?>:&nbsp;</div>
    <?php print render($message); ?>
  </div>

  <?php print render($content); ?>
</div>
