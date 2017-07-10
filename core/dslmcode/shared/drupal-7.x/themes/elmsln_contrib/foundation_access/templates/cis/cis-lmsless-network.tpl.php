<?php
  /**
   * CIS LMS-less Network block template.
   */
?>
  <li class="center-align valign-wrapper elmsln-modal-title-wrapper black">
  <h2 class="flow-text valign elmsln-modal-title white-text"><?php print t('More tools'); ?></h2></li>
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
    <li>
    <?php if (isset($service['icon_library']) && $service['icon_library'] == 'material'): ?>
      <a tabindex="-1" data-prefetch-hover="true" href="<?php print token_replace($service['url']); ?>" class="<?php print $activetool . $service['icon']; ?>-icon" data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($stitle, 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($stitle); ?>" hover-class="<?php print $lmsless_classes[$service['distro']]['color'];?> <?php print $lmsless_classes[$service['distro']]['dark'];?> white-text">
        <paper-button class="paper-button-link">
          <div class="elmsln-hover-icon material-icon elmsln-network-icon left elmsln-icon <?php print $iconcolor;?>"><i class="material-icons"><?php print $service['icon']; ?></i></div>
          <span class="elmsln-network-label"><?php print $stitle; ?></span>
        </paper-button>
      </a>
    <?php else: ?>
      <lrnsys-button href="<?php print token_replace($service['url']); ?>" class="account-logout" hover-class="<?php print $lmsless_classes[$service['distro']]['color'];?> <?php print $lmsless_classes[$service['distro']]['dark'];?> white-text" data-prefetch-hover="true" data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($stitle, 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($stitle); ?>">
        <lrn-icon icon="<?php print $service['icon'];?>"></lrn-icon>
        <span class="elmsln-network-label"><?php print $stitle; ?></span>
      </lrnsys-button>
    <?php endif; ?>
    </li>
    <?php endforeach ?>
  <?php endforeach ?>
