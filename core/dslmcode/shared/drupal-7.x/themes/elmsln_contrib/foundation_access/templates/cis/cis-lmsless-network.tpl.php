<?php
  /**
   * CIS LMS-less Network block template.
   */
?>
  <ul>
  <!-- End Menu Item Dropdowns -->
  <?php foreach ($network['services'] as $title => $items) : ?>
    <?php if ($title == t('Network')) { continue; } ?>
    <li>
      <div class="subheader"><?php print t('@title', array('@title' => token_replace($title))); ?></div>
      <div class="divider grey"></div>
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
        if (isset($active['machine_name']) && $service['machine_name'] == $active['machine_name']) {
          $activetool = $lmsless_classes[$service['distro']]['color'] . ' active-system white-text ';
          $iconcolor = $lmsless_classes[$service['distro']]['color'] . ' white-text ';
        }
        $stitle = token_replace($service['title']);
    ?>
    <li>
    <?php if (isset($service['icon_library']) && $service['icon_library'] == 'material'): ?>
      <lrnsys-button href="<?php print token_replace($service['url']); ?>" button-class="black-text" hover-class="<?php print $lmsless_classes[$service['distro']]['color'];?> <?php print $lmsless_classes[$service['distro']]['dark'];?> white-text" data-prefetch-hover="true" data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($stitle, 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($stitle); ?>" icon="<?php print $service['icon'];?>">
        <span class="elmsln-network-label"><?php print $stitle; ?></span>
      </lrnsys-button>
    <?php else: ?>
      <lrnsys-button href="<?php print token_replace($service['url']); ?>" button-class="black-text" hover-class="<?php print $lmsless_classes[$service['distro']]['color'];?> <?php print $lmsless_classes[$service['distro']]['dark'];?> white-text" data-prefetch-hover="true" data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($stitle, 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($stitle); ?>">
        <lrn-icon icon="<?php print $service['icon'];?>"></lrn-icon>
        <span class="elmsln-network-label"><?php print $stitle; ?></span>
      </lrnsys-button>
    <?php endif; ?>
    </li>
    <?php endforeach ?>
  <?php endforeach ?>
  </ul>
