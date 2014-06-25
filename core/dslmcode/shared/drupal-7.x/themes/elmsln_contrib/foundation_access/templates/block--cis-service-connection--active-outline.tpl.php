<div class="sticky-nav book-outline main-a"><?php print $content; ?></div>
<div class="book-outline sticky-book-outline">
  <a href="#" data-dropdown="book-sticky-nav" class="button dropdown">
    <?php print t('Lessons') ?>
  </a>
  <?php print str_replace('<ul class="nav nav-list">', '<ul id="book-sticky-nav" data-downdown-content class="f-dropdown nav nav-list">', $content); ?>
</div>

