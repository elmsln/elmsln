<?php

/**
 * @file
 * Valid example template file.
 *
 * Alternative control structure style is allowed.
 */
?>
<div>
<?php if (TRUE): ?>
  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" id="logo">
    <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
  </a>
<?php else: ?>
  <i>some text</i>
<?php endif; ?>
</div>
<br />
<?php print $foo; ?>
