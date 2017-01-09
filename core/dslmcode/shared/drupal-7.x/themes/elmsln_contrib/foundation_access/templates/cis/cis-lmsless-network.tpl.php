<?php
  /**
   * CIS LMS-less Network block template.
   */
?>
  <li class="center-align valign-wrapper elmsln-modal-title-wrapper <?php print $lmsless_classes[$distro]['color'] . ' ' . $lmsless_classes[$distro]['light'] . ' ' . $lmsless_classes[$distro]['color'];?>-border">
  <h2 class="flow-text valign elmsln-modal-title"><?php print $site_name; ?></h2></li>
  <!-- End Menu Item Dropdowns -->
  <?php foreach ($services as $title => $items) : ?>
    <li>
      <a class="subheader"><?php print t('@title', array('@title' => token_replace($title))); ?></a>
      <div class="divider <?php print $lmsless_classes[$distro]['color'] . ' ' . $lmsless_classes[$distro]['light'];?>"></div>
    </li>
    <?php
      foreach ($items as $service) :
        if (!isset($service['icon'])) {
          $service['icon'] = $service['machine_name'];
        }
        // apply default system color if we get misses
        if (!isset($service['distro'])) {
          $service['distro'] = '_default_';
        }
        $activetool = '';
        $iconcolor = $lmsless_classes[$service['distro']]['color'] . '-text text-darken-4';
        if ($service['machine_name'] == $active['machine_name']) {
          $activetool = $lmsless_classes[$service['distro']]['color'] . ' active-system white-text ';
          $iconcolor = $lmsless_classes[$service['distro']]['color'] . ' white-text ';
        }
        $stitle = token_replace($service['title']);
    ?>
      <li><a data-prefetch-hover="true" href="<?php print token_replace($service['url']); ?>" class="waves-effect waves-<?php print $lmsless_classes[$service['distro']]['color'];?> waves-light <?php print $activetool . $service['icon']; ?>-icon"  data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($stitle, 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($stitle); ?>" data-elmsln-hover="<?php print $lmsless_classes[$service['distro']]['color'];?> <?php print $lmsless_classes[$service['distro']]['dark'];?> white-text" data-elmsln-icon-hover="hover-white-text">
      <?php if (isset($service['icon_library']) && $service['icon_library'] == 'material'): ?>
        <div class="material-icon elmsln-network-icon left elmsln-icon <?php print $iconcolor;?>"><i class="material-icons"><?php print $service['icon']; ?></i></div>
      <?php else: ?>
        <div class="elmsln-network-icon left elmsln-icon icon-<?php print $service['icon'] . ' ' . $iconcolor;?>"></div>
      <?php endif; ?>
        <span class="elmsln-network-label"><?php print $stitle; ?></span>
      </a></li>
    <?php endforeach ?>
  <?php endforeach ?>
