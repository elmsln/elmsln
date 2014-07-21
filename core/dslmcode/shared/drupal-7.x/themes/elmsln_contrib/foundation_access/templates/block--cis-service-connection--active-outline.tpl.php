<div class="sticky-nav book-outline main-a"><?php print $content; ?></div>
<div class="book-outline sticky-book-outline">
  <a href="#" data-dropdown="book-sticky-nav" class="button dropdown">
    <?php print (($active = _cis_service_connection_active_outline()) ? $active->title : t('Lessons')); ?>
  </a>
  <? print '<ul id="book-sticky-nav" data-downdown-content class="f-dropdown nav nav-list">' . $content . '</ul>'; ?>
</div>
