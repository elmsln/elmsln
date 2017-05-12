<?php
  // render a ridiculous ctools modal submit link
  // Variables
  //  $content - rendered ctoolsmodal that's ready to go, just wrap it
  //  $class - class names to apply to this modal
  //  $tool - the tool that this was requested from, useful for icon formation
?>
<!-- Modal Trigger -->
<a tabindex="-1" class="elmsln-modal-trigger vibrate" aria-controls="modal-<?php print $trigger;?>" aria-expanded="false" href="#modal-<?php print $trigger;?>">
<paper-button raised class="<?php print $lmsless_classes[$tool]['text'];?> <?php print $lmsless_classes[$tool]['color'];?> <?php print $lmsless_classes[$tool]['light'];?> <?php print $lmsless_classes[$tool]['outline'];?>"><?php print $icon; ?> <?php print $label; ?></paper-button></a>
<!-- Modal Structure -->
<section id="modal-<?php print $trigger;?>" class="elmsln-modal modal elmsln-modal-append-container" aria-hidden="true" role="dialog" tabindex="-1" aria-label="<?php print $title; ?>">
  <div class="center-align valign-wrapper elmsln-modal-title-wrapper <?php print $lmsless_classes[$tool]['color'] . ' ' . $lmsless_classes[$tool]['dark'] . ' ' . $lmsless_classes[$tool]['color'];?>-border">
    <h2 class="flow-text valign elmsln-modal-title white-text"><?php print $title; ?></h2>
    <a tabindex="-1" href="#" class="close-reveal-modal white-text" aria-label="<?php print t('Close'); ?>" data-voicecommand="close" data-jwerty-key="Esc"><paper-button>&#215;</paper-button></a>
  </div>
  <div class="elmsln-modal-content">
    <iframe id="<?php print $id; ?>" class="<?php print $class; ?>" src="<?php print $link; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" frameborder="0" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true" data-xapi-hypothesis="<?php print $hypothesis; ?>" data-course-competency="<?php print $competency; ?>"></iframe>
  </div>
</section>

