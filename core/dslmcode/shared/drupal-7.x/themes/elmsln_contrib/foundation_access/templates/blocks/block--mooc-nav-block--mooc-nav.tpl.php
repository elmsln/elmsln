<div id="<?php print $block_html_id; ?>-nav" class="mooc-nav-<?php print $block->mooc_nav['style']; ?> <?php print $classes; ?>">
<?php if (!empty($block->subject)) :?>
  <h3><?php print check_plain($block->subject); ?></h3>
<?php endif;?>
<?php print $content; ?>
</div>
