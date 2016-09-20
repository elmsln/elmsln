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
<div id="etb-course-nav" class="row full collapse">
  <div class="s12 m6 col">
    <nav class="top-bar etb-nav middle-align-wrap etb-nav--center--parent" data-options="is_hover: false" data-topbar role="navigation">
     <section>
        <!-- Left Nav Section -->
        <ul class="left kill-margin middle-align-wrap">
        <?php if ($bar_elements['network']) : ?>
          <li class="apps">
            <a href="#" class="etb-nav_item_service_btn etb-icon apps-icon middle-align-wrap elmsln-network-button elmsln-left-side-nav-trigger" data-activates="block-cis-lmsless-cis-lmsless-network-nav-modal" data-jwerty-key="n" data-voicecommand="open network">
              <div class="icon-apps-black etb-icons svg"></div>
              <span class="hide-on-med-and-down"><?php print t('Network'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['user']) : ?>
          <li class="ferpa-protect">
            <a href="#" class="etb-nav_item_service_btn etb-icon user-icon middle-align-wrap elmsln-user-button elmsln-left-side-nav-trigger" data-activates="block-cis-lmsless-cis-lmsless-user-nav-modal" data-jwerty-key="u" data-voicecommand="open user">
              <?php if (isset($userpicture)) { print $userpicture; } ?>
              <span class="hide-on-med-and-down"><?php print $username; ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['help']) : ?>
          <li class="divider-left">
            <a href="<?php print $help_link;?>" class="etb-nav_item_service_btn etb-icon help-icon elmsln-help-button middle-align-wrap" data-jwerty-key="h" data-voicecommand="help">
              <div class="icon-help-black etb-icons svg"></div>
              <span class="hide-on-med-and-down"><?php print t('Help'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if (isset($bar_elements['resources']) && $bar_elements['resources']) : ?>
            <?php if ($bar_elements['help']) : ?>
            <li>
            <?php else : ?>
            <li class="divider-left">
            <?php endif; ?>
            <a href="<?php print $resources_link;?>" class="etb-nav_item_service_btn etb-icon elmsln-resource-button resources-icon middle-align-wrap" data-jwerty-key="r" data-voicecommand="resources">
              <div class="icon-teacher-black etb-icons svg"></div>
              <span class="hide-on-med-and-down"><?php print t('Resources'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['syllabus']) : ?>
            <?php if ($bar_elements['help'] || $bar_elements['resources']) : ?>
            <li>
            <?php else : ?>
            <li class="divider-left">
            <?php endif; ?>
            <a href="<?php print $syllabus_link;?>" class="etb-nav_item_service_btn etb-icon info-icon elmsln-syllabus-button middle-align-wrap" data-jwerty-key="y" data-voicecommand="syllabus">
              <div class="icon-info-black etb-icons svg"></div>
              <span class="hide-on-med-and-down"><?php print t('Syllabus'); ?></span>
            </a>
          </li>
          <?php endif; ?>
        </ul>
        </section>
      </nav>
    </div>
    <div class="etb-title s12 m6 col">
      <nav class="top-bar etb-nav flex-vertical-right center-align-wrap" data-options="is_hover: false" data-topbar role="navigation">
       <section class="top-bar-section title-link">
        <ul class="menu right clearfix">
          <li class="first expanded menu-mlid-365">
          <?php
            // account for roles that don't have access to this
            if (!empty($elmsln_main_menu)) {?>
            <a id="courseToolsMenuTrigger" class="course-title elmsln-course-title" href="#" title="" data-dropdown="courseToolsMenu" aria-controls="courseToolsMenu" aria-expanded="false" data-jwerty-key="t" data-voicecommand="open settings (menu)">
              <span class="course-title-group">
                <span class="course-title"><?php print $slogan; ?></span>
                <span class="course-abrv"><?php print $site_name; ?> <?php if (isset($section_title)) : print $section_title; endif; ?></span>
              </span>
              <span class="course-title-icon icon--dropdown"></span>
            </a>
            <ul id="courseToolsMenu" class="f-dropdown f-dropdown--classic content" data-dropdown-content aria-hidden="true" aria-autoclose="true">
              <?php print $elmsln_main_menu; ?>
            </ul>
            <?php
            }
            else { ?>
            <a id="courseToolsMenuTrigger" class="course-title elmsln-course-title" href="<?php print base_path(); ?>" title="<?php print t('Home'); ?>">
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

