<?php
/**
 * @file
 * Fork of Default theme implementation to display a single Drupal page.
 *
 */
?>
  <div id="content" class="column"><div class="section">
    <a id="main-content"></a>
    <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
    <?php print render($page['content']); ?>
  </div></div> <!-- /.section, /#content -->