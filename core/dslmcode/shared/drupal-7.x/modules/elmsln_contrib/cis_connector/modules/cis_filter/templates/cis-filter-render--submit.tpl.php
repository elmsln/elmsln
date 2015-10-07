<?php
  // render a ridiculous ctools modal submit link
  // Variables
  //  $content - rendered ctoolsmodal that's ready to go, just wrap it
  //  $class - class names to apply to this modal
  //  $tool - the tool that this was requested from, useful for icon formation
?>
<div class="small-4 medium-6 <?php print $class; ?> icon-<?php print $tool; ?>-black">
  <?php print $content; ?>
</div>