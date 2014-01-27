<div class='form form-layout-simple clearfix'>
  <?php print drupal_render_children($form) ?>
  <?php if (!empty($actions)) print drupal_render($actions) ?>
</div>
