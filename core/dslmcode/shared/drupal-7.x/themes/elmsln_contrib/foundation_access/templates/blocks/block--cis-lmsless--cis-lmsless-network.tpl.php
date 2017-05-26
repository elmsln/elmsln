<section role="dialog">
  <h2 class="element-invisible"><?php print t('Course network menu'); ?></h2>
  <ul id="<?php print $block_html_id ?>-nav-modal" class="elmsln-modal elmsln-modal-hidden side-nav disable-scroll" aria-label="<?php print t('Course network'); ?>" aria-hidden="true" tabindex="-1">
    <?php print $content; ?>
    <li><a href="#close-dialog" class="close-reveal-side-nav white-text" aria-label="<?php print t('Close network menu'); ?>" data-voicecommand="close (menu)" data-jwerty-key="Esc"><paper-button>&#215;</paper-button></a></li>
  </ul>
</section>