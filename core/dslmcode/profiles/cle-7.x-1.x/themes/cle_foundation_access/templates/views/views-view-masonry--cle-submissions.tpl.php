<?php
/**
 * @file
 * Default view template to display items in a jQuery Masonry grid.
 */
 // load the flag
 $flag = flag_get_flag('cle_exemplary');
?>

<?php foreach ($rows as $id => $row):
  // check for exemplary work
  $cle_classes = 'cle-masonry-item';
  // test that item is flagged
  if ($flag->is_flagged($view->result[$id]->nid)) {
	  $cle_classes .= ' cle_exemplary';
  }
?>
  <div class="<?php print $cle_classes; ?> masonry-item<?php if ($classes_array[$id]) print ' ' . $classes_array[$id]; ?>">
    <?php print $row;?>
  </div>
<?php endforeach; ?>
