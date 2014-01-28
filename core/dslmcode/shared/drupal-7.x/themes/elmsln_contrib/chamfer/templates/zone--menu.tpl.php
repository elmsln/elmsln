<?php if ($wrapper): ?><div<?php print $attributes; ?>><?php endif; ?>
  <?php
  if (strpos($logo, 'color/chamfer')) {
    $styles = '';
  }
  else {
    $path = base_path() . path_to_theme();
    $styles = ' style="'."background-image: url('$path/images/crop.png'), url('$path/images/crop.png'), url('$path/images/border.png'), url('$path/images/border.png'), url('$logo');".'"';
  }
  ?>
  <div<?php print $content_attributes . $styles;?>>    
    <?php print $content; ?>
  </div>
<?php if ($wrapper): ?></div><?php endif; ?>