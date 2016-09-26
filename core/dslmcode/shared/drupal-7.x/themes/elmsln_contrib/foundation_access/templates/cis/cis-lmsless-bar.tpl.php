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
<div id="etb-course-nav" class="row full collapse <?php print $lmsless_classes['topbar'];?>">
  <div class="s12 m6 col">
    <nav class="top-bar etb-nav middle-align-wrap etb-nav--center--parent" data-options="is_hover: false" data-topbar role="navigation">
     <section>
        <!-- Left Nav Section -->
        <ul class="left kill-margin middle-align-wrap">
        <?php if ($bar_elements['network']) : ?>
          <li class="elmsln-network-menu-item">
            <a href="#" class="middle-align-wrap elmsln-network-button elmsln-left-side-nav-trigger  black-text waves-effect waves-orange" data-activates="block-cis-lmsless-cis-lmsless-network-nav-modal" data-jwerty-key="n" data-voicecommand="open network">
              <div class="cis-lmsless-network icon-apps-black svg"></div>
              <span class="hide-on-med-and-down truncate"><?php print t('Network'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['user']) : ?>
          <li class="elmsln-user-profile-menu-item ferpa-protect divider-right">
            <a href="#" class="middle-align-wrap elmsln-user-button elmsln-left-side-nav-trigger black-text waves-effect waves-orange" data-activates="block-cis-lmsless-cis-lmsless-user-nav-modal" data-jwerty-key="u" data-voicecommand="open user">
              <?php if (isset($userpicture)) { print $userpicture; } ?>
              <span class="hide-on-med-and-down truncate"><?php print $username; ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['help']) : ?>
          <li>
            <a href="<?php print $help_link;?>" class="elmsln-help-button middle-align-wrap black-text waves-effect waves-orange" data-jwerty-key="h" data-voicecommand="help">
              <i class="material-icons left">help</i>
              <span class="hide-on-med-and-down"><?php print t('Help'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if (isset($bar_elements['resources']) && $bar_elements['resources']) : ?>
            <li>
            <a href="<?php print $resources_link;?>" class="elmsln-resource-button middle-align-wrap black-text waves-effect waves-orange" data-jwerty-key="r" data-voicecommand="resources">
              <i class="material-icons left">local_library</i>
              <span class="hide-on-med-and-down"><?php print t('Resources'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['syllabus']) : ?>
            <li>
            <a href="<?php print $syllabus_link;?>" class="elmsln-syllabus-button middle-align-wrap black-text waves-effect waves-orange" data-jwerty-key="y" data-voicecommand="syllabus">
              <i class="material-icons left">info_outline</i>
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

