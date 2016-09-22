<div id="<?php print $block_html_id ?>-nav-modal" class="elmsln-scroll-bar modal elmsln-modal etb-nav-modal disable-scroll" tabindex="-1">
<?php print l('<i class="material-icons black-text">home</i><span>Home</span>', '<front>', array('html' => TRUE, 'attributes' => array('data-voicecommand' => t('home'), 'class' => array('mooc-home-button'))));?><h3><?php print t('Table of Contents'); ?></h3>
<?php print $content; ?>
<a href="#" class="close-reveal-modal" aria-label="Close" data-voicecommand="close (menu)" data-jwerty-key="Esc">&#215;</a>
</div>
