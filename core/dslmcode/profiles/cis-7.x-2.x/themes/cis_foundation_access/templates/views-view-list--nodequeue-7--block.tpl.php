<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<div class="light-triangle-down triangle-overflow border-step-center"></div>
<div class="row accolades-wrapper">
  <div class="small-centered columns small-11 large-8">
  <h2 class="block-title"><?php print t('Accolades'); ?></h2>
  <?php print $wrapper_prefix; ?>
    <?php if (!empty($title)) : ?>
      <h3><?php print $title; ?></h3>
    <?php endif; ?>
    <?php print $list_type_prefix; ?>
      <?php foreach ($rows as $id => $row): ?>
        <li class="<?php print $classes_array[$id]; ?>"><?php print $row; ?></li>
      <?php endforeach; ?>
    <?php print $list_type_suffix; ?>
  <?php print $wrapper_suffix; ?>
  </div>
</div>
<div class="light-triangle-down triangle-overflow border-step-center"></div>