<?php
  /**
   * CIS LMSLess Contextual Links template file
   */
?>
<div class="<?php print $classes; ?>" <?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <h2 <?php print $title_attributes; ?>><?php print $title;?></h2>
  <div class="content"<?php print $content_attributes; ?>>
    <?php print $content ?>
  </div>
  <?php print $more ?>
  <?php print render($title_suffix); ?>
</div>
