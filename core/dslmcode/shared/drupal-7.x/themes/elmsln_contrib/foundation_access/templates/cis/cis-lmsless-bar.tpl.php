<?php
/**
 * CIS LMS-less template file
 */
?>
<!-- Ecosystem Top Nav -->
<div id="etb-course-nav" class="row full collapse white">
  <div class="s5 m3 l5 col">
    <nav class="top-bar etb-nav middle-align-wrap etb-nav--center--parent" data-options="is_hover: false" data-topbar>
     <section class="top-bar-section title-link">
        <h2 class="element-invisible"><?php print t('System navigation bar');?></h2>
        <!-- Left Nav Section -->
        <div class="left-nav-section">
        <?php
          // account for roles that don't have access to this
          if (!empty($elmsln_main_menu)) {?>
          <lrnsys-drawer alt="<?php print t('Settings menu');?>" header="<?php print t('Settings');?>" align="left" class="course-title elmsln-course-title middle-align-wrap" heading-class="black white-text" title="" aria-expanded="false" data-jwerty-key="t" data-voicecommand="open settings (menu)">
            <span slot="button">
              <lrndesign-avatar class="elmsln-course-avatar" label="<?php print $course_context; ?>" jdenticon color="grey darken-4"></lrndesign-avatar>
              <div class="course-title-group">
                <span class="course-title hide-on-small-only"><?php print $slogan; ?></span>
                <span class="course-abrv"><?php print $site_name; ?> <span class="accessible-grey-text section-label hide-on-small-only"><?php if (isset($section_title)) : print $section_title; endif; ?></span></span>
              </div>
            </span>
            <div class="elmsln-modal-content">
              <ul>
                <li><?php print $elmsln_main_menu; ?></li>
              </ul>
            </div>
          </lrnsys-drawer>
          <?php } else { ?>
          <div class="middle-align-wrap">
	          <lrndesign-avatar label="<?php print $course_context; ?>" class="elmsln-course-avatar" jdenticon color="grey darken-4"></lrndesign-avatar>
	          <div class="course-title-group">
	            <span class="hide-on-small-only course-title"><?php print $slogan; ?></span>
	            <span class="course-abrv"><?php print $site_name; ?> <span class="accessible-grey-text section-label hide-on-small-only">  <?php if (isset($section_title)) : print $section_title; endif; ?></span></span>
	          </div>
          </div>
          <?php } ?>
      	</div>
      </section>
    </nav>
  </div>
  <div class="top-bar-right-actions s7 m9 l7 col">
    <nav class="top-bar etb-nav flex-vertical-right center-align-wrap" data-options="is_hover: false" data-topbar>
     <section>
      <ul class="menu clearfix">
        <?php if ($bar_elements['help']) : ?>
        <li>
          <lrnsys-button data-jwerty-key="h" data-voicecommand="help" href="<?php print $help_link;?>" class="elmsln-help-button middle-align-wrap black-text" hover-class="<?php print $lmsless_classes[$network['active']['distro']]['color'] . ' ' . $lmsless_classes[$network['active']['distro']]['dark'];?> white-text">
            <lrn-icon icon="help"></lrn-icon>
            <span class="hide-on-small-only"><?php print t('Help'); ?></span>
          </lrnsys-button>
        </li>
        <?php endif; ?>
        <?php if (isset($bar_elements['resources']) && $bar_elements['resources']) : ?>
        <li>
          <lrnsys-button data-jwerty-key="r" data-voicecommand="resources" href="<?php print $resources_link;?>" class="elmsln-resource-button middle-align-wrap black-text" icon="maps:local-library" hover-class="<?php print $lmsless_classes[$network['active']['distro']]['color'] . ' ' . $lmsless_classes[$network['active']['distro']]['dark'];?> white-text">
            <span class="hide-on-small-only"><?php print t('Resources'); ?></span>
          </lrnsys-button>
        </li>
        <?php endif; ?>
        <?php if ($bar_elements['syllabus']) : ?>
          <li>
          <lrnsys-button data-jwerty-key="y" data-voicecommand="syllabus" href="<?php print $syllabus_link;?>" class="elmsln-syllabus-button middle-align-wrap black-text" icon="info-outline" hover-class="<?php print $lmsless_classes[$network['active']['distro']]['color'] . ' ' . $lmsless_classes[$network['active']['distro']]['dark'];?> white-text">
            <span class="hide-on-small-only"><?php print t('Syllabus'); ?></span>
          </lrnsys-button>
        </li>
        <?php endif; ?>
        <?php if ($bar_elements['user']) : ?>
        <li class="elmsln-user-profile-menu-item">
          <lrnsys-drawer body-append class="middle-align-wrap elmsln-user-button black-text" align="right" hover-class="<?php print $lmsless_classes[$network['active']['distro']]['color'] . ' ' . $lmsless_classes[$network['active']['distro']]['dark'];?> white-text" heading-class=" black-text">
            <span slot="button">
              <lrndesign-avatar style="display:inline-block; vertical-align: middle;" label="<?php print $username;?>" src="<?php print $userpicture;?>"></lrndesign-avatar>
              <span class="hide-on-small-only" style="display:inline-block; vertical-align: middle;"><?php print $username; ?></span>
            </span>
            <h2 class="element-invisible" slot="header"><?php print t('User menu'); ?></h2>
            <span slot="content" class="elmsln-modal-content">
              <?php print $user_block;?>
            </span>
          </lrnsys-drawer>
        </li>
        <?php endif; ?>
      </ul>
    </section>
    </nav>
  </div>
</div>
<div id="etb-network-nav" class="row full collapse white">
  <ul class="elmsln-service-list col s9">
  <?php if (isset($network['services']['Network'])) : ?>
    <?php
      foreach ($network['services']['Network'] as $service) :
      if (!isset($service['icon'])) {
        $service['icon'] = $service['machine_name'];
      }
      // apply default system color if we get misses
      if (!isset($service['distro'])) {
        $service['distro'] = '_default_';
      }
      $activetool = ' ';
      $label = '';
      $iconcolor = '';
      $stitle = token_replace($service['title']);
      $hover = $lmsless_classes[$service['distro']]['color'] . ' ' . $lmsless_classes[$service['distro']]['dark'];
      if ($service['machine_name'] == $network['active']['machine_name']) {
        $activetool = ' black active-system white-text ';
        $iconcolor = ' white-text ';
        $label = '<span class="elmsln-network-label hide-on-small-only truncate">' . $stitle . '</span>';
      }
      else {
        $label = '<span class="element-invisible">' . $stitle . '</span>';
        $hover .= ' white-text';
      }
      ?>
      <li>
      <lrnsys-button id="lmsless-<?php print $service['machine_name'];?>" data-prefetch-hover="true" href="<?php print token_replace($service['url']); ?>" class="black-text <?php print $activetool . $service['icon']; ?>-icon"  data-jwerty-key="ctrl+<?php print drupal_strtolower(substr($stitle, 0, 1)); ?>" data-voicecommand="<?php print t('go to ') . drupal_strtolower($stitle); ?>" hover-class="<?php print $hover;?>">
        <?php if (isset($service['icon_library']) && $service['icon_library'] == 'material'): ?>
        <i class="material-icons"><?php print $service['icon']; ?></i>
        <?php else: ?>
          <lrn-icon icon="<?php print $service['icon'];?>" class="elmsln-hover-icon"></lrn-icon>
        <?php endif; ?>
        <?php print $label; ?>
      </lrnsys-button>
      <paper-tooltip for="lmsless-<?php print $service['machine_name'];?>" animation-delay="0"><?php print $stitle; ?></paper-tooltip>
      </li>
    <?php endforeach ?>
  <?php endif; ?>
  </ul>
  <?php if ($bar_elements['network']) : ?>
    <ul class="elmsln-more-items col s3">
      <li class="elmsln-network-menu-item right">
        <lrnsys-drawer class="middle-align-wrap elmsln-network-button blue-text" icon-class="blue-text" align="right" header="<?php print t('Applications'); ?>" data-jwerty-key="o+a" data-voicecommand="open applications" hover-class="<?php print $lmsless_classes[$network['active']['distro']]['color'] . ' ' . $lmsless_classes[$network['active']['distro']]['dark'];?> white-text" heading-class="black white-text">
          <span slot="button"><iron-icon icon="apps"></iron-icon><span class=" hide-on-small-only"><?php print t('More apps'); ?></span></span>
          <div slot="content" class="elmsln-modal-content elmsln-network-modal">
            <?php print $network_block;?>
          </div>
        </lrnsys-drawer>
      </li>
    </ul>
  <?php endif; ?>
</div>