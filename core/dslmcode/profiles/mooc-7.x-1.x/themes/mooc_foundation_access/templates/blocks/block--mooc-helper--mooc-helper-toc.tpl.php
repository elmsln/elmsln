<div id="<?php print $block_html_id ?>-nav-modal" class="elmsln-scroll-bar modal elmsln-modal elmsln-modal-hidden etb-nav-modal disable-scroll" tabindex="-1" aria-labelledby="<?php print t('Table of contents'); ?>" aria-hidden="true" role="dialog">
<?php print l('<i class="material-icons black-text">home</i><span>Home</span>', '<front>', array('html' => TRUE, 'attributes' => array('data-voicecommand' => t('home'), 'class' => array('mooc-home-button'))));?><h3><?php print t('Table of contents'); ?></h3>
<?php print $content; ?>
<a href="#" class="close-reveal-modal" aria-label="<?php print t('Close'); ?>" data-voicecommand="close (menu)" data-jwerty-key="Esc">&#215;</a>
</div>
