<?php
/**
 * @file
 * Default theme implementation to display a region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>
<main id="etb-tool-nav">
  <div class="inner-wrap">
    <section class="main-section etb-book">
    <a id="main-content"></a>
    <?php if ($title && arg(2) != 'edit'): ?>
      <?php print render($title_prefix); ?>
        <h1 id="page-title" class="title"><?php print $title; ?></h1>
      <?php print render($title_suffix); ?>
    <?php endif; ?>
    <?php print render($page['content']); ?>
    </section>
  </div>
</main>