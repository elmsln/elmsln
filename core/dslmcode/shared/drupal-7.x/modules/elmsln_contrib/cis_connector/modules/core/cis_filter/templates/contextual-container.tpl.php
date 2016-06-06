<?php
  /**
   * Contextual container for wrapping contextual links into page elements.
   */
?>
<div class="<?php print $classes; ?>" <?php print $attributes; ?>>
  <div <?php print $content_attributes; ?>>
    <?php print $content ?>
  </div>
  <div class="custom-contextual-links">
    <?php print render($title_suffix); ?>
  </div>
</div>
