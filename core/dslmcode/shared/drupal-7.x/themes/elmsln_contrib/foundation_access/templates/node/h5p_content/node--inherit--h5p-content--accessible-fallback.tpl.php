<?php print render($content['field_accessible_fallback']); ?>
<?php if (isset($content['field_figurelabel_ref'])): ?>
  <?php print render($content['field_figurelabel_ref'][0]); ?>
<?php endif; ?>
<?php print l(t('Switch to more interactive form of this media.'), 'entity_iframe/node/' . $nid);?>