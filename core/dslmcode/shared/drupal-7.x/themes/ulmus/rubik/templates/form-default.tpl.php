<div class='form form-layout-default clearfix'>
  <div class='column-main'><div class='column-wrapper clearfix'>
    <?php print drupal_render_children($form); ?>
    <?php print rubik_render_clone($actions); ?>
  </div></div>
  <div class='column-side'><div class='column-wrapper clearfix'>
    <?php print drupal_render($actions); ?>
    <?php print drupal_render($sidebar); ?>
  </div></div>
  <?php if (!empty($footer)): ?>
    <div class='column-footer'><div class='column-wrapper clearfix'><?php print drupal_render($footer); ?></div></div>
  <?php endif; ?>
</div>
