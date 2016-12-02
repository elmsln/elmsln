<?php
  // render a ridiculous ctools modal submit link
  // Variables
  //  $content - rendered ctoolsmodal that's ready to go, just wrap it
  //  $class - class names to apply to this modal
  //  $tool - the tool that this was requested from, useful for icon formation
?>
<!-- Modal Trigger -->
<a href="#side-nav-<?php print $trigger;?>" class="elmsln-right-side-nav-widget-trigger <?php print $lmsless_classes[$tool]['text'];?> elmsln-filter-tpl-side-nav waves-effect btn waves-<?php print $lmsless_classes[$tool]['color'];?> waves-light <?php print $lmsless_classes[$tool]['color'];?> <?php print $lmsless_classes[$tool]['light'];?> <?php print $lmsless_classes[$tool]['outline'];?>" aria-controls="side-nav-<?php print $trigger;?>" aria-expanded="false" data-activates="side-nav-<?php print $trigger;?>"><?php print $icon; ?> <?php print $label; ?></a>
<!-- Modal Structure -->
<section role="dialog" class="elmsln-modal-append-container">
  <h2 class="element-invisible"><?php print $title; ?></h2>
  <ul id="side-nav-<?php print $trigger;?>" class="elmsln-modal elmsln-modal-hidden side-nav disable-scroll" aria-hidden="true" tabindex="-1" aria-label="<?php print $title; ?>">
    <li class="center-align valign-wrapper elmsln-modal-title-wrapper <?php print $lmsless_classes[$tool]['color'] . ' ' . $lmsless_classes[$tool]['light'] . ' ' . $lmsless_classes[$tool]['color'];?>-border"><h2 class="flow-text valign elmsln-modal-title"><?php print $title; ?></h2></li>
    <li class="elmsln-modal-content">
      <iframe id="<?php print $id; ?>" class="<?php print $class; ?>" src="<?php print $link; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" frameborder="0" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true" data-xapi-hypothesis="<?php print $hypothesis; ?>" data-course-competency="<?php print $competency; ?>"></iframe>
    </li>
    <li><a href="#" class="close-reveal-side-nav" aria-label="<?php print t('Close'); ?>" data-voicecommand="close (menu)" data-jwerty-key="Esc">&#215;</a></li>
  </ul>
</section>