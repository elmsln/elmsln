<fieldset <?php if (!empty($attributes)) print drupal_attributes($attributes) ?>>
  <?php if (!empty($title)): ?>
    <legend><span class='<?php print $hook ?>-title fieldset-legend'><?php print $title ?></span></legend>
  <?php endif; ?>
  <?php if (!empty($content)): ?>
    <div class='<?php print $hook ?>-content fieldset-wrapper clearfix'><?php print $content ?></div>
  <?php endif; ?>
</fieldset>
