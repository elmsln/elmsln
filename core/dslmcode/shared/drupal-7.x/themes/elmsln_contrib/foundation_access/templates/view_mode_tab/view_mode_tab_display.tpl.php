<?php foreach ($view_modes as $view_mode => $data): ?>
  <hr />
  <a name="<?php print $data['header_id']; ?>"></a><h2><?php print $view_mode; ?></h2>
  <hr />
  <div class="clipboard__wrapper">
	  <?php if (isset($data['view_mode']['#prefix'])): ?>
	  <div class="clipboard clipboard--button-only">
	  	<?php 
	  		print $data['view_mode']['#prefix'];
	  		unset($data['view_mode']['#prefix']);
	  	 ?>
	  </div>
		<?php endif; ?>

	  <?php print drupal_render($data['view_mode']); ?>
  </div>
<?php endforeach; ?>