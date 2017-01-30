<?php print render($content); ?>
<?php if (isset($content['field_figurelabel_ref'])): ?>
  <?php print render($content['field_figurelabel_ref'][0]); ?>
<?php endif; ?>