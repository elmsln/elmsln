<section id="<?php print $block_html_id ?>-nav-modal" class="modal elmsln-modal elmsln-modal-hidden disable-scroll" tabindex="-1" aria-label="<?php print t('Table of contents'); ?>" aria-hidden="true" role="dialog">
  <div class="center-align valign-wrapper elmsln-modal-title-wrapper cis-lmsless-background cis-lmsless-border">
  <?php print l('<i class="material-icons black-text left">home</i><span class="hide-on-med-and-down">' . t('Home') . '</span>', '<front>', array('html' => TRUE, 'attributes' => array('data-voicecommand' => t('home'), 'class' => array('waves-effect waves-light btn-large white black-text mooc-home-button'))));?>
  <div class="flow-text valign elmsln-modal-title"><?php print t('Table of contents'); ?></div>
  <a href="#" class="close-reveal-modal" aria-label="<?php print t('Close'); ?>" data-voicecommand="close (menu)" data-jwerty-key="Esc">&#215;</a>
  </div>
  <div class="mooc-outline-modal-content elmsln-scroll-bar">
    <?php print $content; ?>
  </div>
</section>
