<div id="<?php print $block_html_id ?>-nav-modal" class="reveal-modal etb-nav-modal disable-scroll" data-reveal tabindex="-1">
<?php print l('<div class="mooc-helper-toc-icon icon-courses-black etb-modal-icons"></div><span>Home</span>', '<front>', array('html' => TRUE, 'attributes' => array('class' => array('mooc-home-button'))));?><h3><?php print t('Table of Contents'); ?></h3>
<?php print $content; ?>
<a class="close-reveal-modal" aria-label="Close">&#215;</a>
</div>
