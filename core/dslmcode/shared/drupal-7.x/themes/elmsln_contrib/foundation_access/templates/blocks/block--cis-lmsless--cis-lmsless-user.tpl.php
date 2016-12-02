<section role="dialog">
<h2 class="element-invisible"><?php print t('User menu'); ?></h2>
  <ul id="<?php print $block_html_id ?>-nav-modal" class="elmsln-modal elmsln-modal-hidden side-nav disable-scroll" aria-label="<?php print t('User profile menu'); ?>" aria-hidden="true" tabindex="-1">
    <?php print $content; ?>
    <li><a href="#close-dialog" class="close-reveal-side-nav" aria-label="<?php print t('Close user menu'); ?>" data-voicecommand="close (menu)" data-jwerty-key="Esc">&#215;</a></li>
  </ul>
</section>
