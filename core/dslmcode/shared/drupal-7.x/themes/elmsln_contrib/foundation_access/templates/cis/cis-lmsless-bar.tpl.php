<?php
/**
 * CIS LMS-less template file
 */
  // support authcache_cookie value that gets dynamically loaded instead
  if (isset($user_name)) {
    $username = $user_name;
  }
?>
<!-- Ecosystem Top Nav -->
<div id="etb-course-nav" class="row full collapse <?php print $lmsless_classes[$distro]['color'] . ' ' . $lmsless_classes[$distro]['light'] . ' ' . $lmsless_classes[$distro]['color'];?>-border z-depth-1">
  <div class="s12 m7 col">
    <nav class="top-bar etb-nav middle-align-wrap etb-nav--center--parent" data-options="is_hover: false" data-topbar>
     <section>
        <h2 class="element-invisible"><?php print t('System navigation bar');?></h2>
        <!-- Left Nav Section -->
        <ul class="left-nav-section">
          <?php if ($bar_elements['network']) : ?>
          <li class="elmsln-network-menu-item">
            <a href="#network-menu-button" class="middle-align-wrap elmsln-network-button elmsln-left-side-nav-trigger  black-text waves-effect waves-<?php print $lmsless_classes[$distro]['color'];?> waves-light" data-activates="block-cis-lmsless-cis-lmsless-network-nav-modal" data-jwerty-key="n" data-voicecommand="open network">
              <div class="cis-lmsless-network elmsln-icon icon-network"></div>
              <span class="hide-on-med-and-down truncate"><?php print t('Network'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['user']) : ?>
          <li class="elmsln-user-profile-menu-item ferpa-protect">
            <a href="#user-menu-button" class="middle-align-wrap elmsln-user-button elmsln-left-side-nav-trigger black-text waves-effect waves-<?php print $lmsless_classes[$distro]['color'];?> waves-light" data-activates="block-cis-lmsless-cis-lmsless-user-nav-modal" data-jwerty-key="u" data-voicecommand="open user">
              <?php if (isset($userpicture)) { print $userpicture; } ?>
              <span class="hide-on-med-and-down truncate"><?php print $username; ?></span>
            </a>
          </li>
          <?php endif; ?>
          <li class="divider-right <?php print $lmsless_classes[$distro]['color'];?>-border"></li>
          <?php if ($bar_elements['help']) : ?>
          <li>
            <a href="<?php print $help_link;?>" class="elmsln-help-button middle-align-wrap black-text waves-effect waves-<?php print $lmsless_classes[$distro]['color'];?> waves-light" data-jwerty-key="h" data-voicecommand="help">
              <i class="material-icons">help</i>
              <span class="hide-on-med-and-down"><?php print t('Help'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if (isset($bar_elements['resources']) && $bar_elements['resources']) : ?>
          <li>
            <a href="<?php print $resources_link;?>" class="elmsln-resource-button middle-align-wrap black-text waves-effect waves-<?php print $lmsless_classes[$distro]['color'];?> waves-light" data-jwerty-key="r" data-voicecommand="resources">
              <i class="material-icons">local_library</i>
              <span class="hide-on-med-and-down"><?php print t('Resources'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['syllabus']) : ?>
            <li>
            <a href="<?php print $syllabus_link;?>" class="elmsln-syllabus-button middle-align-wrap black-text waves-effect waves-<?php print $lmsless_classes[$distro]['color'];?> waves-light" data-jwerty-key="y" data-voicecommand="syllabus">
              <i class="material-icons">info_outline</i>
              <span class="hide-on-med-and-down"><?php print t('Syllabus'); ?></span>
            </a>
          </li>
          <?php endif; ?>
        </ul>
      </section>
    </nav>
  </div>
    <div class="etb-title s12 m5 col">
      <nav class="top-bar etb-nav flex-vertical-right center-align-wrap" data-options="is_hover: false" data-topbar>
       <section class="top-bar-section title-link">
       <h2 class="element-invisible"><?php print t('Course identifier and settings');?></h2>
        <ul class="menu right clearfix">
          <li class="first expanded">
          <?php
            // account for roles that don't have access to this
            if (!empty($elmsln_main_menu)) {?>
            <a id="elmsln-tools-trigger" class="course-title elmsln-course-title elmsln-dropdown-button" href="#elmsln-settings-menu" title="" data-activates="elmsln-tools-menu" aria-controls="elmsln-tools-menu" aria-expanded="false" data-jwerty-key="t" data-voicecommand="open settings (menu)">
              <span class="course-title-group">
                <span class="course-title"><?php print $slogan; ?></span>
                <span class="course-abrv"><?php print $site_name; ?> <?php if (isset($section_title)) : print $section_title; endif; ?></span>
              </span>
              <span class="course-title-icon icon--dropdown"></span>
            </a>
            <ul id="elmsln-tools-menu" class="dropdown-content" aria-hidden="true">
              <li><?php print $elmsln_main_menu; ?></li>
            </ul>
            <?php
            }
            else { ?>
            <a id="elmsln-tools-trigger" class="course-title elmsln-course-title" href="<?php print base_path(); ?>" title="<?php print t('Home'); ?>">
              <span class="course-title-group">
                <span class="course-title"><?php print $slogan; ?></span>
                <span class="course-abrv"><?php print $site_name; ?> <?php if (isset($section_title)) : print $section_title; endif; ?></span>
              </span>
            </a>
            <?php } ?>
          </li>
        </ul>
      </section>
      </nav>
    </div>
  </div>

