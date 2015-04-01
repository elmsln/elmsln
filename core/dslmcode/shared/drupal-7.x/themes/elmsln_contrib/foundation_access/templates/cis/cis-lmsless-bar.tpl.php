<?php
  /**
   * CIS LMS-less template file
   *
   *
   */
?>
<!-- Ecosystem Top Nav ---------------------------------------- -->
<div id="etb-course-nav" class="row full collapse">
  <div class="columns small-6 medium-5">
    <nav class="top-bar etb-nav etb-nav--center--parent" data-options="is_hover: false" data-topbar role="navigation">
     <section>
        <!-- Left Nav Section -->
        <ul class="left kill-margin">
          <li class="left apps">
            <a href="#" class="etb-nav_item_service_btn etb-icon apps-icon" data-reveal-id="apps-nav-modal">
              <div class="icon-apps-black etb-icons"></div>
              <span class="visible-for-large-up"><?php print t('Course'); ?></span>
            </a>
          </li>
          <li class="left">
            <a href="#" class="etb-nav_item_service_btn etb-icon user-icon" data-reveal-id="user-nav-modal">
              <div class="icon-user-black etb-icons"></div>
              <span class="visible-for-large-up"><?php print $username; ?></span>
            </a>
          </li>
          <li class="left">
            <a href="#" class="etb-nav_item_service_btn etb-icon info-icon" data-reveal-id="info-nav-modal">
              <div class="icon-info-black etb-icons"></div>
              <span class="visible-for-large-up"><?php print t('Syllabus'); ?></span>
            </a>
          </li>
          <li class="left">
            <a href="#" class="etb-nav_item_service_btn etb-icon help-icon" data-reveal-id="help-nav-modal">
              <div class="icon-help-black etb-icons"></div>
              <span class="visible-for-large-up"><?php print t('Help'); ?></span>
            </a>
          </li>
        </ul>
        <!-- Eco Nav Modals ---------------------------------------- -->
        <div id="apps-nav-modal" class="reveal-modal etb-nav-modal" data-reveal>
            <h1><?php print $site_name; ?></h1>
              <hr></hr>
              <h2>Services</h2>
              <?php foreach ($services as $service) : ?>
              <a href="<?php print $service['url']; ?>" class=" etb-modal-icon <?php print $service['machine_name']; ?>-icon row">
                <div class="icon-<?php print $service['machine_name']; ?>-black etb-modal-icons"></div>
                <span class=""><?php print $service['title']; ?></span>
              </a>
              <?php endforeach ?>
              <!--
              <hr></hr>
              <h2>Future</h2>
              <a href="#" class="etb-modal-icon calendar-icon row">
                <div class="icon-calendar-black etb-modal-icons"></div>
                <span class="">Calendar</span>
              </a>
              <a href="#" class="etb-modal-icon assignments-icon row">
                <div class="icon-assignments-black etb-modal-icons"></div>
                <span class="">Assignments</span>
              </a>
              <a href="#" class="etb-modal-icon people-icon row">
                <div class="icon-people-black etb-modal-icons "></div>
                <span class="">People</span>
              </a>
              <hr></hr>
              <h2>Communicate</h2>
              <a href="#" class=" etb-modal-icon inbox-icon row">
                <div class="icon-inbox-black etb-modal-icons"></div>
                <span>Inbox</span>
              </a>
              <a href="#" class=" etb-modal-icon speechballoons-icon row">
                <div class="icon-speechballoons-black etb-modal-icons"></div>
                <span>Discussions</span>
              </a>
              <a href="#" class=" etb-modal-icon write-icon row">
                <div class="icon-write-black etb-modal-icons"></div>
                <span>Blog</span>
              </a>
              <hr></hr>
              <h2>Environments</h2>
              <a href="#" class=" etb-modal-icon easle-icon row">
                <div class="icon-easle-black etb-modal-icons"></div>
                <span>Studio</span>
              </a>
              <a href="#" class=" etb-modal-icon beaker-icon row">
                <div class="icon-beaker-black etb-modal-icons"></div>
                <span>Labs</span>
              </a>
              <a href="#" class=" etb-modal-icon collab-icon row">
                <div class="icon-collab-black etb-modal-icons"></div>
                <span>Peer Collaboration</span>
              </a>
            -->
            <a class="close-reveal-modal">&#215;</a>
         </div>
         <div id="user-nav-modal" class="reveal-modal etb-nav-modal" data-reveal>
          <!-- Center Search Section -->

            <h1>Account</h1>
              <hr class="pad-1"></hr>
                <a class="account-logout text-center row" href="#">log out</a>
              <hr></hr>
              <h2>Profile</h2>
              <a href="#" class="modal-img-link row">
                <div class="left">
                  <img alt="placeholder image" src="https://placehold.it/100x100">
                </div>
                <span><?php print $username; ?></span>
              </a>
              <!--
               <a href="#" class="etb-modal-icon grades-icon row">
                <div class="icon-grades-black etb-modal-icons "></div>
                <span class="">Grades</span>
              </a>
              <a href="#" class="etb-modal-icon bookmark-outline-icon row">
                <div class="icon-bookmark-outline-black etb-modal-icons "></div>
                <span class="">Bookmarks</span>
              </a>
              <hr></hr>
              <h2>Settings</h2>
              <a href="#" class="etb-modal-icon access-icon row">
                <div class="icon-access-black etb-modal-icons"></div>
                <span>Accessibility</span>
              </a> -->
            <a class="close-reveal-modal">&#215;</a>
         </div>


         <div id="info-nav-modal" class="reveal-modal etb-nav-modal" data-reveal>
            <h1><?php print t('Syllabus'); ?></h1>
              <hr></hr>
              <h2><?php print t('Instructor'); ?></h2>
              <a href="#" class="modal-img-link row">
                <div class="left">
                  <img alt="placeholder image" src="https://placehold.it/100x100">
                </div>
                <span class="">Instructor Name</span>
              </a>
              <!--<hr></hr>
               <h2><?php print t('My Section'); ?></h2>
              <a href="#" class="etb-nav_item_service_btn etb-modal-icon techsupport-icon">
                <div class="icon-techsupport-black etb-modal-icons"></div>
                <span><?php print $section; ?></span>
              </a> -->
              <hr></hr>
              <h2><?php print t('Section'); ?> (<span class="section-id"><?php print $section; ?></span>)</h2>
              <?php print drupal_render($main_menu); ?>
            <a class="close-reveal-modal">&#215;</a>
         </div>


         <div id="help-nav-modal" class="reveal-modal etb-nav-modal" data-reveal>
            <h1><?php print t('Help'); ?></h1>
              <hr></hr>
              <h2 class"etb-nav-section-label"><?php print t('Contact'); ?></h2>
              <?php print $contact_block; ?>
              <?php if (isset($tech_support['body'])) : ?>
                <h2 class"etb-nav-section-label"><?php print $tech_support['title']; ?></h2>
                <?php print $tech_support['body']; ?>
              <?php endif; ?>
              <a href="#" class="etb-modal-icon teacher-icon row">
                <div class="icon-teacher-black etb-modal-icons"></div>
                <span>E-Mail your instructor</span>
              </a>
              <hr></hr>
              <h2 class"etb-nav-section-label">Technical Issues</h2>
              <a href="<?php print $help_link; ?>" class="etb-nav_item_service_btn etb-modal-icon support-icon row">
                <div class="icon-support-black etb-modal-icons"></div>
                <span><?php print t('Help page');?></span>
              </a>
              <a href="<?php print $tour; ?>" class="etb-nav_item_service_btn etb-modal-icon tour-icon row">
                <div class="icon-tour-black etb-modal-icons"></div>
                <span><?php print t('Take a tour'); ?></span>
              </a>
            <a class="close-reveal-modal">&#215;</a>
         </div>


        </section>
      </nav>
    </div>
    <div class="hide-for-small-only medium-3 columns">
      <?php print render($search); ?>
    </div>
    <div class="etb-title hide-for-small-only medium-4 columns">
      <nav class="top-bar etb-nav" data-options="is_hover: false" data-topbar role="navigation">
       <section class="top-bar-section">
          <ul class="right">
            <li class="has-dropdown">
              <a href="#"><span class="course-title"><?php print $slogan; ?></span><span class="course-abrv"><?php print $site_name; ?></span></a>
              <ul class="dropdown">
                <li><a href="#">Course program information</a></li>
                <li class="active"><a href="#">Course program information</a></li>
              </ul>
            </li>
          </ul>
        </section>
      </nav>
    </div>
  </div>
