<?php foreach ($view_modes as $view_mode => $data): ?>
  <hr />
  <a name="<?php print $data['header_id']; ?>"></a><h2><?php print $view_mode; ?></h2>
  <hr />
  <?php print drupal_render($data['view_mode']); ?>
<?php endforeach; ?>