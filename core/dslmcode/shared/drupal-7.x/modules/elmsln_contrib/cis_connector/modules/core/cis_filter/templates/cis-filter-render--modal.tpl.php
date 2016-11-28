<?php
  // render a ridiculous ctools modal submit link
  // Variables
  //  $content - rendered ctoolsmodal that's ready to go, just wrap it
  //  $class - class names to apply to this modal
  //  $tool - the tool that this was requested from, useful for icon formation
?>
<!-- Modal Trigger -->
<a class="elmsln-modal-trigger elmsln-filter-tpl-modal waves-effect waves-<?php print $lmsless_classes[$tool]['color'];?> waves-light btn vibrate <?php print $lmsless_classes[$tool]['text'];?> <?php print $lmsless_classes[$tool]['color'];?> <?php print $lmsless_classes[$tool]['light'];?> <?php print $lmsless_classes[$tool]['outline'];?>" aria-controls="modal-<?php print $trigger;?>" aria-expanded="false" href="#modal-<?php print $trigger;?>"><?php print $icon; ?> <?php print $label; ?></a>
<!-- Modal Structure -->
<section id="modal-<?php print $trigger;?>" class="elmsln-modal modal elmsln-modal-append-container" aria-hidden="true" role="dialog" tabindex="-1" aria-label="<?php print $title; ?>">
  <div class="center-align valign-wrapper elmsln-modal-title-wrapper <?php print $lmsless_classes[$tool]['color'] . ' ' . $lmsless_classes[$tool]['light'] . ' ' . $lmsless_classes[$tool]['color'];?>-border">
    <div class="flow-text valign elmsln-modal-title"><?php print $title; ?></div>
    <a href="#" class="close-reveal-modal" aria-label="<?php print t('Close'); ?>" data-voicecommand="close" data-jwerty-key="Esc">&#215;</a>
  </div>
  <div class="elmsln-modal-content">
    <iframe id="<?php print $id; ?>" class="<?php print $class; ?>" src="<?php print $link; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" frameborder="0" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true" data-xapi-hypothesis="<?php print $hypothesis; ?>"></iframe>
  </div>
</section>

