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
            <a href="#" class="etb-nav_item_service_btn etb-icon apps-icon middle-align-wrap" data-reveal-id="apps-nav-modal">
              <div class="icon-apps-black etb-icons svg"></div>
              <span class="visible-for-large-up"><?php print t('Network'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['user']) : ?>
          <li>
            <a href="#" class="etb-nav_item_service_btn etb-icon user-icon middle-align-wrap" data-reveal-id="user-nav-modal">
              <div class="icon-user-black etb-icons svg"></div>
              <span class="visible-for-large-up"><?php print $username; ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['help']) : ?>
          <li>
            <a href="<?php print $help_link;?>" class="etb-nav_item_service_btn etb-icon help-icon middle-align-wrap">
              <div class="icon-help-black etb-icons svg"></div>
              <span class="visible-for-large-up"><?php print t('Help'); ?></span>
            </a>
          </li>
          <?php endif; ?>
          <?php if ($bar_elements['syllabus']) : ?>
          <li class="divider-left">
            <a href="<?php print $syllabus_link;?>" class="etb-nav_item_service_btn etb-icon info-icon middle-align-wrap">
              <div class="icon-info-black etb-icons svg"></div>
              <span class="visible-for-large-up"><?php print t('Syllabus'); ?></span>
            </a>
          </li>
          <?php endif; ?>
        </ul>
        <!-- Eco Nav Modals -->
        <div id="apps-nav-modal" class="reveal-modal etb-nav-modal disable-scroll" data-reveal>
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
                </ul>
              </div>
              <?php endif; ?>
              <!-- End Menu Item Dropdowns -->
              <?php foreach ($services as $title => $items) : ?>
                <hr/>
                <h2><?php print t('@title', array('@title' => $title)); ?></h2>
                <?php foreach ($items as $service) : ?>
                <a href="<?php print $service['url']; ?>" class=" etb-modal-icon <?php print $service['machine_name']; ?>-icon row">
                  <div class="icon-<?php print $service['machine_name']; ?>-black etb-modal-icons"></div>
                  <span class=""><?php print $service['title']; ?></span>
                </a>
                <?php endforeach ?>
              <?php endforeach ?>
            <a class="close-reveal-modal">&#215;</a>
         </div>
         <div id="user-nav-modal" class="reveal-modal etb-nav-modal disable-scroll" data-reveal>
            <h1><?php print t('Account'); ?></h1>
              <hr class="pad-1" />
              <?php if (isset($masquerade)) : ?>
              <h2><?php print t('Impersonate'); ?></h2>
              <div class="cis-admin-area user-nav-masquerade">
                <?php print $masquerade; ?>
              </div>
              <?php endif; ?>
              <hr class="pad-1" />
              <?php if (isset($user_roles)) : ?>
              <h2><?php print t('Roles'); ?></h2>
              <div class="cis-admin-area user-nav-user-roles">
                <?php print $user_roles; ?>
              </div>
              <?php endif; ?>
              <?php if (isset($section_title)) : ?>
              <h2><?php print t('Section'); ?></h2>
              <div class="cis-admin-area user-nav-section">
                <?php print $user_section; ?>
              </div>
              <?php endif; ?>
              <hr class="pad-1" />
              <?php if (!empty($username)) : ?>
              <h2><?php print t('User'); ?></h2>
              <span><?php print $username; ?></span>
              <?php endif; ?>
              <hr class="pad-1" />
                <?php print $userlink; ?>
              <hr />
            <a class="close-reveal-modal">&#215;</a>
         </div>
        </section>
      </nav>
    </div>
    <div class="etb-title small-12 medium-6 columns">
      <nav class="top-bar etb-nav flex-vertical-right center-align-wrap" data-options="is_hover: false" data-topbar role="navigation">
       <section class="top-bar-section title-link">
        <ul class="menu right clearfix">
          <li class="first expanded menu-mlid-365">
            <a id="courseToolsMenuTrigger" class="icon icon--dropdown" href="/" title="" data-dropdown="courseToolsMenu" aria-controls="courseToolsMenu" aria-expanded="false" >
              <span class="course-title"><?php print $slogan; ?></span>
              <span class="course-abrv"><?php print $site_name; ?> <?php print $section_title; ?></span>
            </a>
            <ul id="courseToolsMenu" class="f-dropdown" data-dropdown-content aria-hidden="true" aria-autoclose="true">
              <?php print $elmsln_main_menu; ?>
            </ul>
          </li>
        </ul>
      </section>
      </nav>
    </div>
  </div>

