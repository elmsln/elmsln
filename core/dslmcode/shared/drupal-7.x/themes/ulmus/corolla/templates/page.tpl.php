<?php // Corolla ?>
<div id="page-wrapper">
  <div id="page" class="<?php print $classes; ?>">

    <?php if ($menubar = render($page['menu_bar'])): ?>
      <div id="menu-bar-wrapper">
        <div class="container clearfix">
          <?php print $menubar; ?>
        </div>
      </div>
    <?php endif; ?>

    <div id="header-wrapper">
      <div class="container clearfix">

        <header class="clearfix<?php print $site_logo ? ' with-logo' : ''; ?>" role="banner">

          <?php if ($site_logo || $site_name || $site_slogan): ?>
            <div id="branding" class="branding-elements clearfix">

              <?php if ($site_logo): ?>
                <div id="logo">
                  <?php print $site_logo; ?>
                </div>
              <?php endif; ?>

              <?php if ($site_name || $site_slogan): ?>
                <div<?php print $hgroup_attributes; ?>>

                  <?php if ($site_name): ?>
                    <h1<?php print $site_name_attributes; ?>><?php print $site_name; ?></h1>
                  <?php endif; ?>

                  <?php if ($site_slogan): ?>
                    <h2<?php print $site_slogan_attributes; ?>><?php print $site_slogan; ?></h2>
                  <?php endif; ?>

                </div>
              <?php endif; ?>

            </div>
          <?php endif; ?>

          <?php print render($page['header']); ?>

        </header>

      </div>
    </div>

    <?php if (
      $page['three_33_top'] ||
      $page['three_33_first'] ||
      $page['three_33_second'] ||
      $page['three_33_third'] ||
      $page['three_33_bottom']
      ): ?>
      <div id="top-panels-wrapper">
        <div class="container clearfix">
          <!-- Three column 3x33 Gpanel -->
          <div class="at-panel gpanel panel-display three-3x33 clearfix">
            <?php print render($page['three_33_top']); ?>
            <?php print render($page['three_33_first']); ?>
            <?php print render($page['three_33_second']); ?>
            <?php print render($page['three_33_third']); ?>
            <?php print render($page['three_33_bottom']); ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($page['secondary_content']): ?>
      <div id="secondary-content-wrapper">
        <div class="container clearfix">
          <?php print render($page['secondary_content']); ?>
        </div>
      </div>
     <?php endif; ?>

    <?php if ($messages || $page['help']): ?>
      <div id="messages-help-wrapper">
        <div class="container clearfix">
          <?php print $messages; ?>
          <?php print render($page['help']); ?>
        </div>
      </div>
    <?php endif; ?>

    <div id="content-wrapper">
      <div class="container">

        <div id="columns">
          <div class="columns-inner clearfix">

            <div id="content-column">
              <div class="content-inner">

                <?php print render($page['highlighted']); ?>

                <<?php print $tag; ?> id="main-content" role="main">

                  <?php if ($primary_local_tasks): ?>
                    <div id="tasks" class="clearfix">

                      <?php if ($primary_local_tasks): ?>
                        <ul class="tabs primary">
                          <?php print render($primary_local_tasks); ?>
                        </ul>
                      <?php endif; ?>

                    </div>
                  <?php endif; ?>

                  <div class="content-margin">
                    <div class="content-style">

                      <?php if ($secondary_local_tasks): ?>
                        <ul class="tabs secondary">
                          <?php print render($secondary_local_tasks); ?>
                        </ul>
                      <?php endif; ?>

                      <?php if ($breadcrumb): print $breadcrumb; endif; ?>

                      <?php print render($title_prefix); ?>

                      <?php if ($title): ?>
                        <header class="clearfix">
                          <h1 id="page-title">
                            <?php print $title; ?>
                          </h1>
                        </header>
                      <?php endif; ?>

                      <?php print render($title_suffix); ?>

                      <?php if ($action_links = render($action_links)): ?>
                        <ul class="action-links">
                          <?php print $action_links; ?>
                        </ul>
                      <?php endif; ?>

                      <div id="content">
                        <?php print render($page['content']); ?>
                      </div>

                      <?php print $feed_icons; ?>

                    </div>
                  </div>

                </<?php print $tag; // end main content ?>>

                <?php print render($page['content_aside']); ?>

              </div>
            </div>

            <?php print render($page['sidebar_first']); ?>
            <?php print render($page['sidebar_second']); ?>

          </div>
        </div>

      </div>
    </div>

    <?php if ($page['tertiary_content']): ?>
      <div id="tertiary-content-wrapper">
        <div class="container clearfix">
          <?php print render($page['tertiary_content']); ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if (
      $page['four_first'] ||
      $page['four_second'] ||
      $page['four_third'] ||
      $page['four_fourth']
      ): ?>
      <div id="footer-panels-wrapper">
        <div class="container clearfix">
          <!-- Four column Gpanel -->
          <div class="at-panel gpanel panel-display four-4x25 clearfix">
            <div class="panel-row row-1 clearfix">
              <?php print render($page['four_first']); ?>
              <?php print render($page['four_second']); ?>
            </div>
            <div class="panel-row row-2 clearfix">
              <?php print render($page['four_third']); ?>
              <?php print render($page['four_fourth']); ?>
            </div>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($page['footer'] || $attribution): ?>
      <div id="footer-wrapper">
        <div class="container clearfix">
          <footer class="clearfix" role="contentinfo">
            <?php print render($page['footer']); ?>
            <p class="attribute-creator"><?php print $attribution; ?></p>
          </footer>
        </div>
      </div>
    <?php endif; ?>

  </div>
</div>
