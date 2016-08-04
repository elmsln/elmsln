<?php
  // render an iframe based on passed in values
  // Variables
  //  $id - content id
  //  $class - classes to apply
  //  $link - link to what the frame is pointing to
  //  $width - width of the frame
  //  $height - height of the frame
  //  $hypothesis - possible xAPI hypothesis
?>
<iframe id="<?php print $id; ?>" class="<?php print $class; ?>" src="<?php print $link; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" frameborder="0" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true" data-xapi-hypothesis="<?php print $hypothesis; ?>"></iframe>
