
<a href="#" class="off-canvas-toolbar-item access-icon" data-reveal-id="<?php print $block_html_id ?>-nav-modal">
  <div class="icon-access-white off-canvas-toolbar-item-icon"></div>
  <span><?php print $block->subject; ?></span>
</a>

<div id="<?php print $block_html_id ?>-nav-modal" class="reveal-modal etb-nav-modal" data-reveal>
<?php print $content; ?>
</div>
