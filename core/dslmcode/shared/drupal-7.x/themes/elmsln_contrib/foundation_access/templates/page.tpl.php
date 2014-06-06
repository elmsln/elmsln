<!--.page -->
<div role="document" class="page">


    <!--.l-off-canvas menu -->
   <!--  <div class="off-canvas-wrap" data-offcanvas>
    <div class="inner-wrap">
      <nav class="tab-bar">
        <?php if (!empty($page['offcanvas_left'])): ?>
          <section class="left-small">
            <a class="left-off-canvas-toggle menu-icon" href="#"><span></span></a>
          </section>
        <?php endif; ?>
        <section class="middle tab-bar-section">
          <h1 class="title">Menu TBD</h1>
        </section>
        <?php if (!empty($page['offcanvas_right'])): ?>
          <section class="right-small">
            <a class="right-off-canvas-toggle menu-icon" href="#"><span></span></a>
          </section>
        <?php endif; ?>
      </nav>

      <?php if (!empty($page['offcanvas_left'])): ?>
        <aside class="left-off-canvas-menu">
          <?php print render($page['offcanvas_left']); ?>
        </aside>
      <?php endif; ?>

      <?php if (!empty($page['offcanvas_right'])): ?>
        <aside class="right-off-canvas-menu">
          <ul class="off-canvas-list">
            <li><label>Users</label></li>
            <li><a href="#">Example</a></li>
            <li><a href="#">...</a></li>
          </ul>
          <?php print render($page['offcanvas_right']); ?>
        </aside>
      <?php endif; ?> -->
      <!--/.l-off-canvas region -->
      
      <div>
        <div class="large-12 breakpoint-indicator"></div>
        <?php print render($page['admin_first']); ?>
      </div>
      <div>
        <?php print render($page['preheader']); ?>
      </div>


      <!--.l-header region -->
      <header role="banner" class="l-header">
      
       

        <!-- Title, slogan and menu -->
        <?php if ($alt_header): ?>
        <section class="row <?php print $alt_header_classes; ?>">

          <?php if ($linked_logo): print $linked_logo; endif; ?>

          <?php if ($site_name): ?>
            <?php if ($title): ?>
              <div id="site-name" class="element-invisible">
                <strong>
                  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                </strong>
              </div>
            <?php else: /* Use h1 when the content title is empty */ ?>
              <h1 id="site-name">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </h1>
            <?php endif; ?>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <h2 title="<?php print $site_slogan; ?>" class="site-slogan"><?php print $site_slogan; ?></h2>
          <?php endif; ?>

          <?php if ($alt_main_menu): ?>
            <nav id="main-menu" class="navigation" role="navigation">
              <?php print ($alt_main_menu); ?>
            </nav> <!-- /#main-menu -->
          <?php endif; ?>

          <?php if ($alt_secondary_menu): ?>
            <nav id="secondary-menu" class="navigation" role="navigation">
              <?php print $alt_secondary_menu; ?>
            </nav> <!-- /#secondary-menu -->
          <?php endif; ?>

        </section>
        <?php endif; ?>
        <!-- End title, slogan and menu -->

        <?php if (!empty($page['header'])): ?>
          <!--.l-header-region -->
          <section class="l-header-region row">
            <div class="large-12 columns">
              <?php print render($page['header']); ?>
            </div>
          </section>
          <!--/.l-header-region -->
        <?php endif; ?>

      </header>
      <!--/.l-header -->

      <?php if (!empty($page['featured'])): ?>
        <!--/.featured -->
        <section class="l-featured row">
          <div class="large-12 columns">
            <?php print render($page['featured']); ?>
          </div>
        </section>
        <!--/.l-featured -->
      <?php endif; ?>

      <?php if ($messages && !$zurb_foundation_messages_modal): ?>
        <!--/.l-messages -->
        <section class="l-messages row">
          <div class="large-12 columns">
            <?php if ($messages): print $messages; endif; ?>
          </div>
        </section>
        <!--/.l-messages -->
      <?php endif; ?>

      <?php if (!empty($page['help'])): ?>
        <!--/.l-help -->
        <section class="l-help row">
          <div class="large-12 columns">
            <?php print render($page['help']); ?>
          </div>
        </section>
        <!--/.l-help -->
      <?php endif; ?>

      <main role="main" class="row l-main">
        <!-- content nav  -->
        <div class="large-12 columns content-manage-btns">
          
            <?php if (!empty($tabs)): ?>
              <div class="local-task-tabs-1">
                <?php print render($tabs); ?>
              </div>
              <div class="local-task-tabs-2">
                <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
              </div>
            <?php endif; ?>

            <?php if ($action_links): ?>
              <div class="action-links-bar">
              <ul class="action-links">
                <?php print render($action_links); ?>
              </ul>
              <div class="large-12 action-links-ui"><span class="point-a"></span><span class="point-b"></span></div>
            </div>
            <?php endif; ?>    
          
        </div>

        <div class="large-12 columns top-bar-container">



        <?php if ($top_bar): ?>
          <!--.top-bar -->
          <?php if ($top_bar_classes): ?>
          <div class="<?php print $top_bar_classes; ?>">
          <?php endif; ?>
            <nav class="top-bar content-top-nav" data-options="is_hover: false" data-topbar <?php print $top_bar_options; ?>>
              <ul class="title-area">
                <li class="name">
                  <h1><a href="#"></a></h1>
                </li>  
                <!-- Remove the class "menu-icon" to get rid of menu icon. -->
                <li class="toggle-topbar menu-icon"><a href="#"><span><?php print $top_bar_menu_text; ?></span></a></li>
              </ul>
              <section class="top-bar-section">


                <?php if ($top_bar_main_menu) :?>
                <!--.l-header-top_bar_main_menu -->
                      
                    <?php print $top_bar_main_menu; ?>
                     
                <!--/.l-header-top_bar_main_menu -->     
                <?php endif; ?>
                
                
               
              </section>
            </nav>
          <?php if ($top_bar_classes): ?>
          </div>
          <?php endif; ?>
          <!--/.top-bar -->
        <?php endif; ?>
        <!--/ content nav  -->

          <?php if (!empty($page['cis_user_profile'])): ?>
          <!--.l-header-cis_user_profile -->
            <div class="left">
              <?php print render($page['cis_user_profile']); ?>
            </div>
          <!--/.l-header-cis_user_profile -->
          <?php endif; ?>


          <?php if (!empty($page['cis_lmsless'])): ?>
            <!--.l-header-cis_lmsless -->
              <div class="cis-lmsless right">             
                <?php print render($page['cis_lmsless']); ?>
              </div>        
            <!--/.l-header-cis_lmsless -->
            <?php endif; ?>
        </div>


        <div class="<?php print $main_grid; ?> main columns">

          <?php if (!empty($page['highlighted'])): ?>
            <div class="highlight panel callout">
              <?php print render($page['highlighted']); ?>
            </div>
          <?php endif; ?>

          <a id="main-content"></a>

          <?php if ($breadcrumb): print $breadcrumb; endif; ?>

          <?php if ($title && !$is_front): ?>
            <?php print render($title_prefix); ?>
            <h1 id="page-title" class="title"><?php print $title; ?></h1>
            <?php print render($title_suffix); ?>
          <?php endif; ?>

          <?php print render($page['content']); ?>
        </div>
        <!--/.main region -->

        <?php if (!empty($page['sidebar_first'])): ?>
          <aside role="complementary" class="<?php print $sidebar_first_grid; ?> sidebar-first columns sidebar">
            <?php print render($page['sidebar_first']); ?>
          </aside>
        <?php endif; ?>

        <?php if (!empty($page['sidebar_second'])): ?>
          <aside role="complementary" class="<?php print $sidebar_sec_grid; ?> sidebar-second columns sidebar">
            <?php print render($page['sidebar_second']); ?>
          </aside>
        <?php endif; ?>
      </main>
      <!--/.main-->

      <?php if (!empty($page['triptych_first']) || !empty($page['triptych_middle']) || !empty($page['triptych_last'])): ?>
        <!--.triptych-->
        <section class="l-triptych row">
          <div class="triptych-first large-4 columns">
            <?php print render($page['triptych_first']); ?>
          </div>
          <div class="triptych-middle large-4 columns">
            <?php print render($page['triptych_middle']); ?>
          </div>
          <div class="triptych-last large-4 columns">
            <?php print render($page['triptych_last']); ?>
          </div>
        </section>
        <!--/.triptych -->
      <?php endif; ?>

      <?php if (!empty($page['footer_firstcolumn']) || !empty($page['footer_secondcolumn']) || !empty($page['footer_thirdcolumn']) || !empty($page['footer_fourthcolumn'])): ?>
        <!--.footer-columns -->
        <section class="row l-footer-columns">
          <?php if (!empty($page['footer_firstcolumn'])): ?>
            <div class="footer-first large-3 columns">
              <?php print render($page['footer_firstcolumn']); ?>
            </div>
          <?php endif; ?>
          <?php if (!empty($page['footer_secondcolumn'])): ?>
            <div class="footer-second large-3 columns">
              <?php print render($page['footer_secondcolumn']); ?>
            </div>
          <?php endif; ?>
          <?php if (!empty($page['footer_thirdcolumn'])): ?>
            <div class="footer-third large-3 columns">
              <?php print render($page['footer_thirdcolumn']); ?>
            </div>
          <?php endif; ?>
          <?php if (!empty($page['footer_fourthcolumn'])): ?>
            <div class="footer-fourth large-3 columns">
              <?php print render($page['footer_fourthcolumn']); ?>
            </div>
          <?php endif; ?>
        </section>
        <!--/.footer-columns-->
      <?php endif; ?>

      <!--.l-footer-->
      <footer class="l-footer panel row" role="contentinfo">
        <?php if (!empty($page['footer'])): ?>
          <div class="footer copyright large-12 columns">
            <?php print render($page['footer']); ?>
          </div>
        <?php endif; ?>

      </footer>
      <!--/.footer-->
      <?php if ($messages && $zurb_foundation_messages_modal): print $messages; endif; ?>
    <!--.l-off-canvas menu -->
        <!-- <a class="exit-off-canvas"></a>
      </div>
    </div> -->
    <!--/.l-off-canvas menu -->
</div>
<!--/.page -->
