<?php

/**
 * @file
 * Bad example template file.
 *
 * Curly braces for control structures should not be used.
 */
?>
<div>
<?php if (TRUE) { ?>
  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" id="logo">
    <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
  </a>
<?php } else { ?>
  <i>some text</i>
<?php } ?>
</div>
<br>
