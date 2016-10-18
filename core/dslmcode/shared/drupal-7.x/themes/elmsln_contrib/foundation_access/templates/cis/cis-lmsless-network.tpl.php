<?php
  /**
   * CIS LMS-less Network block template.
   */
?>
  <li class="center-align valign-wrapper elmsln-modal-title-wrapper cis-lmsless-background cis-lmsless-border"><h1 class="flow-text valign elmsln-modal-title"><?php print $site_name; ?></h1></li>
  <!-- End Menu Item Dropdowns -->
  <?php foreach ($services as $title => $items) : ?>
    <li>
      <a class="subheader"><?php print t('@title', array('@title' => $title)); ?></a>
      <div class="divider cis-lmsless-background"></div>
    </li>
    <?php
      foreach ($items as $service) :
        $activetool = '';
        if ($service['machine_name'] == $active['machine_name']) {
          $activetool = 'active ';
        }
    ?>
      <li><a href="<?php print $service['url']; ?>" class="waves-effect cis-lmsless-waves etb-modal-icon <?php print $activetool . $service['machine_name']; ?>-icon"  data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($service['title'], 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($service['title']); ?>">
      <?php if (isset($service['icon_library']) && $service['icon_library'] == 'material'): ?>
        <div class="etb-modal-icons etb-modal-material-icons"><i class="zmdi zmdi-<?php print $service['machine_name']; ?>"></i></div>
      <?php else: ?>
        <div class="icon-<?php print $service['machine_name']; ?>-black etb-modal-icons"></div>
      <?php endif; ?>
        <span class=""><?php print $service['title']; ?></span>
      </a></li>
    <?php endforeach ?>
  <?php endforeach ?>
