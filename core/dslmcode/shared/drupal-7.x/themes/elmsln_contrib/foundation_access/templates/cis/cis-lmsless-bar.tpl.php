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
  <div class="columns small-12 medium-6">
    <nav class="top-bar etb-nav middle-align-wrap etb-nav--center--parent" data-options="is_hover: false" data-topbar role="navigation">
     <section>
        <!-- Left Nav Section -->
        <ul class="left kill-margin middle-align-wrap">
        <?php if ($bar_elements['network']) : ?>
          <li class="apps">
            <a href="#" class="etb-nav_item_service_btn etb-icon apps-icon middle-align-wrap" data-reveal-id="block-cis-lmsless-cis-lmsless-network-nav-modal">
              <div class="icon-apps-black etb-icons svg"></div>
              <span class="visible-for-large-up"><?php print t('Network'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['user']) : ?>
          <li>
            <a href="#" class="etb-nav_item_service_btn etb-icon user-icon middle-align-wrap" data-reveal-id="block-cis-lmsless-cis-lmsless-user-nav-modal">
              <?php if (isset($userpicture)) { print $userpicture; } ?>
              <span class="visible-for-large-up"><?php print $username; ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['help']) : ?>
          <li class="divider-left">
            <a href="<?php print $help_link;?>" class="etb-nav_item_service_btn etb-icon help-icon middle-align-wrap">
              <div class="icon-help-black etb-icons svg"></div>
              <span class="visible-for-large-up"><?php print t('Help'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['syllabus']) : ?>
            <?php if ($bar_elements['help']) : ?>
            <li>
            <?php else : ?>
            <li class="divider-left">
            <?php endif; ?>
            <a href="<?php print $syllabus_link;?>" class="etb-nav_item_service_btn etb-icon info-icon middle-align-wrap">
              <div class="icon-info-black etb-icons svg"></div>
              <span class="visible-for-large-up"><?php print t('Syllabus'); ?></span>
            </a>
          </li>
          <?php endif; ?>
        </ul>
        </section>
      </nav>
    </div>
    <div class="etb-title small-12 medium-6 columns">
      <nav class="top-bar etb-nav flex-vertical-right center-align-wrap" data-options="is_hover: false" data-topbar role="navigation">
       <section class="top-bar-section title-link">
        <ul class="menu right clearfix">
          <li class="first expanded menu-mlid-365">
          <?php
            // account for roles that don't have access to this
            if (!empty($elmsln_main_menu)) {?>
            <a id="courseToolsMenuTrigger" class="course-title" href="#" title="" data-dropdown="courseToolsMenu" aria-controls="courseToolsMenu" aria-expanded="false" >
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
            <a id="courseToolsMenuTrigger" class="course-title" href="<?php print base_path(); ?>" title="<?php print t('Home'); ?>">
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

