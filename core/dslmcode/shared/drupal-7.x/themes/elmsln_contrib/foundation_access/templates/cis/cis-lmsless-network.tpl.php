<?php
  /**
   * CIS LMS-less Network block template.
   */
?>
  <h1><?php print $site_name; ?></h1>
  <?php if (isset($service_option_link)) : ?>
    <div class="minimal-edit-buttons in-modal">
    <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="eco-services-edit-menu-1" aria-controls="offcanvas-admin-menu" aria-expanded="false">
      <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
    </a>
  </div>
  <!-- Menu Item Dropdowns -->
  <div id="eco-services-edit-menu-1" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
    <ul class="button-group">
      <li><?php print l(t('Add services'), $service_option_link); ?></li>
      <li><?php print l(t('Edit this list'), 'admin/config/user-interface/cis-lmsless-nav'); ?></li>
    </ul>
  </div>
  <?php endif; ?>
  <!-- End Menu Item Dropdowns -->
  <?php foreach ($services as $title => $items) : ?>
    <hr/>
    <h2><?php print t('@title', array('@title' => $title)); ?></h2>
    <?php foreach ($items as $service) : ?>
      <a href="<?php print $service['url']; ?>" class=" etb-modal-icon <?php print $service['machine_name']; ?>-icon row"  data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($service['title'], 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($service['title']); ?>">
      <?php if (isset($service['icon_library']) && $service['icon_library'] == 'material'): ?>
        <div class="etb-modal-icons etb-modal-material-icons"><i class="zmdi zmdi-<?php print $service['machine_name']; ?>"></i></div>
      <?php else: ?>
        <div class="icon-<?php print $service['machine_name']; ?>-black etb-modal-icons"></div>
      <?php endif; ?>
        <span class=""><?php print $service['title']; ?></span>
      </a>
    <?php endforeach ?>
  <?php endforeach ?>