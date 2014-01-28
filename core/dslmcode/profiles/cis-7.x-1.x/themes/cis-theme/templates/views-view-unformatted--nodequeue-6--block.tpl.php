<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
 if (count($rows) > 1) {
	$count = 12 / (count($rows)-1);
 }
?>
<?php foreach ($rows as $id => $row): ?>
<?php if ($id == 0) { ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .' row cis-featured-first-row"';  } ?>>
    <?php 
			print '<div class="columns small-12 large-6 cis-featured-first-image">';
			print $row;
			print '</div>';
		?>
  </div>
  <div class="row">
  <div class="columns small-11 large-11 small-centered large-centered">
  <div class="row cis-featured-old-row">
<?php }else{ ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
    <?php 
			print '<div class="columns small-12 large-' . $count . ' cis-featured-older">';
			print $row;
			print '</div>';
		?>
  </div>
<?php }?>
<?php endforeach; ?>
</div></div></div>