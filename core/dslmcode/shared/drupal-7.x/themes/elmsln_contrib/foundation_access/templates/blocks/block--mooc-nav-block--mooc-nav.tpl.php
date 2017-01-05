<section id="<?php print $block_html_id; ?>-nav" class="mooc-nav-<?php print $block->mooc_nav['style']; ?> <?php print $classes; ?>" aria-label="<?php print $block->subject; ?>" role="navigation">
	<?php if (!empty($block->subject)) :?>
    <div class="block-mooc-nav-block-mooc-title black white-text"><?php print $block->subject; ?></div>
	<?php endif;?>
	<?php print $content; ?>
</section>
