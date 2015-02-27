<?php global $base_url; $path = drupal_get_path('module', 'lazyloader_filter'); ?>
<div class="lz-cont">
  <img src="<?php print $base_url;?>/<?php print $path;?>/pixel.gif" data-src=<?php print $attr['src'];?> <?php print $attr_str;?>/>
  <noscript><img src=<?php print $attr['src'];?> <?php print $attr_str;?>></noscript>
</div>
