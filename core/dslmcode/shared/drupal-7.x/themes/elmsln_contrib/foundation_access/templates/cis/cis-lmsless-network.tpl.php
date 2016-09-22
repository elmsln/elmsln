<?php
  /**
   * CIS LMS-less Network block template.
   */
?>
  <li><h1><?php print $site_name; ?></h1></li>
  <!-- End Menu Item Dropdowns -->
  <?php foreach ($services as $title => $items) : ?>
    <li><div class="divider"></div></li>
    <li><a class="subheader"><?php print t('@title', array('@title' => $title)); ?></a></li>
    <?php foreach ($items as $service) : ?>
      <li><a href="<?php print $service['url']; ?>" class="waves-effect etb-modal-icon <?php print $service['machine_name']; ?>-icon"  data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($service['title'], 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($service['title']); ?>">
      <?php if (isset($service['icon_library']) && $service['icon_library'] == 'material'): ?>
        <div class="etb-modal-icons etb-modal-material-icons"><i class="zmdi zmdi-<?php print $service['machine_name']; ?>"></i></div>
      <?php else: ?>
        <div class="icon-<?php print $service['machine_name']; ?>-black etb-modal-icons"></div>
      <?php endif; ?>
        <span class=""><?php print $service['title']; ?></span>
      </a></li>
    <?php endforeach ?>
  <?php endforeach ?>
