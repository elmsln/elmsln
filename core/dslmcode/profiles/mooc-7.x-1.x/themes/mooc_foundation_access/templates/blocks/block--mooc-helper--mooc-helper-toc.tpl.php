<section id="<?php print $block_html_id ?>-nav-modal" class="modal elmsln-modal elmsln-modal-hidden disable-scroll" tabindex="-1" aria-label="<?php print t('Course outline'); ?>" aria-hidden="true" role="dialog">
  <div class="center-align valign-wrapper elmsln-modal-title-wrapper black">
  <h2 class="flow-text valign elmsln-modal-title white-text"><?php print t('Course outline'); ?></h2>
  <a tabindex="-1" href="#" class="close-reveal-modal white-text" aria-label="<?php print t('Close'); ?>" data-voicecommand="close (menu)" data-jwerty-key="Esc"><paper-button>&#215;</paper-button></a>
  </div>
  <div class="mooc-outline-modal-content elmsln-scroll-bar">
    <?php print $content; ?>
  </div>
</section>
