<?php
 if (isset($elements['#outline_style']) && $elements['#outline_style'] != 'in-context') { ?>
<ul id="fulloutline" class="menu book-oultine slide-panels"><?php print $content; ?></ul>
<?php } else { print $content; } ?>
