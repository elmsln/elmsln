<div id="<?php print $block_html_id ?>-nav-modal" class="elmsln-scroll-bar elmsln-modal modal" aria-label="<?php print $block->subject; ?>" aria-hidden="true" role="dialog" tabindex="-1">
  <div class="center-align valign-wrapper elmsln-modal-title-wrapper cis-lmsless-background cis-lmsless-border">
    <h1 class="flow-text valign elmsln-modal-title"><?php print $block->subject; ?></h1>
    <a href="#" class="close-reveal-modal" aria-label="<?php print t('Close'); ?>" data-voicecommand="close" data-jwerty-key="Esc">&#215;</a>
  </div>
  <div class="elmsln-modal-content">
    <?php print $content; ?>
  </div>
</div>
