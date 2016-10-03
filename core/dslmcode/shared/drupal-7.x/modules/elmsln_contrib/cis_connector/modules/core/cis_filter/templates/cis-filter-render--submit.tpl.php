<?php
  // render a ridiculous ctools modal submit link
  // Variables
  //  $content - rendered ctoolsmodal that's ready to go, just wrap it
  //  $class - class names to apply to this modal
  //  $tool - the tool that this was requested from, useful for icon formation
?>
<div class="col s12 m12 l12">
  <div class="card horizontal">
    <div class="card-image icon-<?php print $tool; ?>-black">
    </div>
    <div class="card-stacked">
      <div class="card-content">
        <div class="<?php print $class; ?>">
          <?php print $icon; ?>
        </div>
      <?php print $content; ?>
      </div>
      <div class="card-action">
        <?php print $links; ?>
      </div>
    </div>
  </div>
</div>
