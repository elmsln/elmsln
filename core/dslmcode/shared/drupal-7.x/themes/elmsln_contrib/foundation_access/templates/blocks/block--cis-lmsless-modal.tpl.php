<section id="<?php print $block_html_id ?>-nav-modal" class="elmsln-scroll-bar elmsln-modal modal" aria-label="<?php print $block->subject; ?>" aria-hidden="true" role="dialog" tabindex="-1">
  <div class="center-align valign-wrapper elmsln-modal-title-wrapper black">
    <h2 class="valign elmsln-modal-title white-text"><?php print check_plain($block->subject); ?></h2>
    <a tabindex="-1" href="#close-dialog" class="close-reveal-modal white-text" aria-label="<?php print t('Close @item', array('@item' => check_plain($block->subject))); ?>" data-voicecommand="close" data-jwerty-key="Esc"><paper-button>&#215;</paper-button></a>
  </div>
  <div class="elmsln-modal-content">
    <?php print $content; ?>
  </div>
</section>
