<?php print render($page['content']); ?>
<footer class="page-footer black white-text">
  <div class="container">
    <div class="row">
      <div class="s12 push-m1 m-10 col">
        <?php if (!empty($page['footer'])): ?>
        <?php print render($page['footer']); ?>
        <?php endif; ?>
      </div>
      <?php if (!empty($page['footer_firstcolumn']) || !empty($page['footer_secondcolumn'])): ?>
      <hr/>
      <div class="row">
        <?php if (!empty($page['footer_firstcolumn'])): ?>
        <div class="l6 col">
          <?php print render($page['footer_firstcolumn']); ?>
        </div>
        <?php endif; ?>
        <?php if (!empty($page['footer_secondcolumn'])): ?>
        <div class="l6 col">
          <?php print render($page['footer_secondcolumn']); ?>
        </div>
        <?php endif; ?>
      </div>
      <?php endif; ?>
    </div>
  </div>
</footer>
<!-- generic container for other off canvas modals -->
<div class="elmsln-modal-container">
  <?php print render($page['cis_lmsless_modal']); ?>
</div>
<?php print $messages; ?>
