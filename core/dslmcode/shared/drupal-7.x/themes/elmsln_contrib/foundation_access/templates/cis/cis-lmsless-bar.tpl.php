<?php
/**
 * CIS LMS-less template file
 */
?>
<!-- Ecosystem Top Nav ---------------------------------------- -->
<div id="etb-course-nav" class="row full collapse">
  <div class="columns small-12 medium-6">
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

        <div id="apps-nav-modal" class="reveal-modal etb-nav-modal disable-scroll" data-reveal>



            <h1><?php print $site_name; ?></h1>
              <hr></hr>
              <?php if (isset($service_option_link)) : ?>
                <div class="minimal-edit-buttons in-modal">
                <!-- <a href="#" class="off-canvas-toolbar-item toolbar-menu-icon" data-dropdown="eco-services-add-menu-1" aria-controls="add-button" aria-expanded="false">
                  <div class="icon-plus-black off-canvas-toolbar-item-icon"></div>
                </a> -->
                <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="eco-services-edit-menu-1" aria-controls="offcanvas-admin-menu" aria-expanded="false">
                  <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
                </a>
              </div>
              <!-- Menu Item Dropdowns -->
              <div id="eco-services-edit-menu-1" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
                <ul class="button-group">
                  <li><?php print l(t('Add another service'), $service_option_link); ?></li>
                  <li><?php print l(t('Edit services'), $service_option_link); ?></li>
                </ul>
              </div>
              <?php endif; ?>
              <!-- End Menu Item Dropdowns -->
              <h2>Services</h2>
              <?php foreach ($services as $service) : ?>
              <a href="<?php print $service['url']; ?>" class=" etb-modal-icon <?php print $service['machine_name']; ?>-icon row">
                <div class="icon-<?php print $service['machine_name']; ?>-black etb-modal-icons"></div>
                <span class=""><?php print $service['title']; ?></span>
              </a>
              <?php endforeach ?>
              <!--
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
              <a href="#" class=" etb-modal-icon write-icon row">
                <div class="icon-write-black etb-modal-icons"></div>
                <span>Blog</span>
              </a>
              <hr></hr>
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
         <div id="user-nav-modal" class="reveal-modal etb-nav-modal disable-scroll" data-reveal>
          <!-- Center Search Section -->

            <h1><?php print t('Account'); ?></h1>
              <hr class="pad-1"></hr>
                <?php print l(t('log out'), 'user/logout', array('attributes' => array('class' => array('account-logout', 'text-center', 'row')))); ?>
              <hr></hr>
              <div class="minimal-edit-buttons in-modal">
                <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="eco-account-edit-menu-1" aria-controls="offcanvas-admin-menu" aria-expanded="false">
                  <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
                </a>
              </div>
              <!-- Menu Item Dropdowns -->
              <div id="eco-account-edit-menu-1" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
                <ul class="button-group">
                  <li><?php print l(t('Edit profile'), 'user/' . $GLOBALS['user']->uid); ?></li>
                  <li><a href="#" data-reveal-id="block-masquerade-masquerade-nav-modal"><?php print t('Impersonate a user'); ?></a></li>
                </ul>
              </div>
              <!-- End Menu Item Dropdowns -->
              <h2>Profile</h2>
              <a href="#" class="modal-img-link row">
                <div class="left">
                    <!-- TODO PUT IMAGE HERE -->
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

         <div id="info-nav-modal" class="reveal-modal etb-nav-modal disable-scroll" data-reveal>
            <h1><?php print t('Syllabus'); ?></h1>
              <hr></hr>
              <!-- End Menu Item Dropdowns -->
              <h2><?php print t('Instructor'); ?></h2>
              <a href="#" class="modal-img-link row">
                <div class="left">
                  <!-- TODO ADD ICON HERE -->
                </div>
                <span class=""><?php print t('Instructor Name'); ?></span>
              </a>
              <hr></hr>
              <div class="minimal-edit-buttons in-modal">
                <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="eco-syllabus-edit-menu-2" aria-controls="offcanvas-admin-menu" aria-expanded="false">
                  <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
                </a>
              </div>
              <!-- Menu Item Dropdowns -->
              <div id="eco-syllabus-edit-menu-2" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
                <ul class="button-group">
                  <li><a href="#" data-reveal-id="block-cis-service-connection-section-context-changer-nav-modal">View another section</a></li>
                  <li><?php print l(t('Download Syllabus'),'syllabus/download'); ?></li>
                </ul>
              </div>
              <!-- End Menu Item Dropdowns -->
              <h2><?php print t('Section'); ?> (<span class="section-id"><?php print $section; ?></span>)</h2>
              <?php if (!empty($main_menu)) : print drupal_render($main_menu); endif; ?>
            <a class="close-reveal-modal">&#215;</a>
         </div>


         <div id="help-nav-modal" class="reveal-modal etb-nav-modal disable-scroll" data-reveal>
            <h1><?php print t('Help'); ?></h1>
              <hr></hr>
              <div class="minimal-edit-buttons in-modal">
                <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="eco-help-edit-menu-1" aria-controls="offcanvas-admin-menu" aria-expanded="false">
                  <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
                </a>
              </div>
              <!-- Menu Item Dropdowns -->
              <div id="eco-help-edit-menu-1" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
                <ul class="button-group">
                  <li><a href="#"><?php print t('Edit contact'); ?></a></li>
                </ul>
              </div>
              <!-- End Menu Item Dropdowns -->
              <h2 class"etb-nav-section-label"><?php print t('Contact'); ?></h2>
              <?php print $contact_block; ?>
              <?php if (isset($tech_support['body'])) : ?>
                <h2 class"etb-nav-section-label"><?php print $tech_support['title']; ?></h2>
                <?php print $tech_support['body']; ?>
              <?php endif; ?>
              <a href="#" class="etb-modal-icon teacher-icon row">
                <div class="icon-teacher-black etb-modal-icons"></div>
                <span><?php print t('E-Mail your instructor'); ?></span>
              </a>
              <hr></hr>
              <h2 class"etb-nav-section-label"><?php print t('Technical Issues'); ?></h2>
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
   <!--  <div class="hide-for-small-only medium-3 columns">
      <?php print render($search); ?>
    </div> -->
    <div class="etb-title small-12 medium-6 columns">
      <nav class="top-bar etb-nav" data-options="is_hover: false" data-topbar role="navigation">
       <section class="top-bar-section title-link">
          <ul class="right">
            <li>
              <?php print l('<span class="course-title">' . $slogan . '</span><span class="course-abrv">' . $site_name . '</span></a>', '<front>', array('html' => TRUE)); ?>
            </li>
          </ul>
        </section>
      </nav>
    </div>
  </div>
