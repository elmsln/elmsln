<?php
/**
 * @file
 * Default theme implementation to display a region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>
    <div id="etb-tool-nav" class="off-canvas-wrap" data-offcanvas>
      <div class="inner-wrap">
                <nav class="tab-bar etb-tool">
          <section class="left">
            <a class="left-off-canvas-toggle menu-icon" ><span><?php print $cis_lmsless['active']['title'] ?></span></a>
          </section>

          <section class="middle tab-bar-section">
            <?php if (!empty($tabs)): ?>
                <?php print render($tabs); ?>
              <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
            <?php endif; ?>
            <?php print render($page['cis_appbar_first']); ?>
          </section>

          <section class="right-small">
            <a href="#" class="off-canvas-toolbar-item access-icon" data-dropdown="accessibility-drop" aria-controls="accessibility-drop" aria-expanded="false">
              <div class="icon-access-white off-canvas-toolbar-item-icon"></div>
              <!-- <span>Accessibilty</span> -->
            </a>
            <?php print render($page['cis_appbar_second']); ?>
          </section>
          <!-- accessibility dropdown -->
          <div id="accessibility-drop" data-dropdown-content class="f-dropdown content large" aria-hidden="true" tabindex="-1">
             <div class="switch small radius">
              <input id="enable-page-reader-switch" type="checkbox">
              <label for="enable-page-reader-switch"></label>
             </div>
             <!-- generic container for other off canvas modals -->
             <?php print render($page['cis_appbar_modal']); ?>
            </div>
            <!-- /accessibility dropdown -->
        </nav>

        <?php print render($page['left_menu']); ?>

        <section class="main-section etb-book">
          <?php if (!empty($page['header'])): ?>
            <div class="region-header row">
              <?php print render($page['header']); ?>
            </div>
          <?php endif; ?>

          <?php if (!empty($messages)): ?>
            <div class="region-messeges row">
              <?php print $messages; ?>
            </div>
          <?php endif; ?>

          <?php if (!empty($page['help'])): ?>
            <div class="region-help row">
              <?php print render($page['help']); ?>
            </div>
          <?php endif; ?>

          <div class="row">
            <div class="content-element-region small-12 medium-12 large-12 columns">
              <div class="row">
                <div class="small-12 medium-12 large-push-1 large-10 columns" role="content">
                  <?php if (!empty($page['highlighted'])): ?>
                    <div class="highlight panel callout">
                      <?php print render($page['highlighted']); ?>
                    </div>
                  <?php endif; ?>

                  <a id="main-content"></a>

                  <?php if ($breadcrumb): print $breadcrumb; endif; ?>

                  <?php if ($title): ?>
                    <?php print render($title_prefix); ?>
                      <h1 id="page-title" class="title"><?php print $title; ?>
                        <br><small>This is my course. It's awesome.</small>
                      </h1>
                      <hr>
                    <?php print render($title_suffix); ?>
                  <?php endif; ?>
                  <?php if ($action_links): ?>
                    <ul class="action-links">
                      <?php print render($action_links); ?>
                    </ul>
                  <?php endif; ?>

                  <?php print render($page['content']); ?>
                </div>
              </div>
            </div>
          </div>

          <footer class="row">
            <div class="large-12 columns">
              <hr/>
              <div class="row">
                <?php if (!empty($page['footer'])): ?>
                <?php print render($page['footer']); ?>
                <?php endif; ?>
              </div>
              <?php if (!empty($page['footer_firstcolumn']) || !empty($page['footer_secondcolumn'])): ?>
              <hr/>
              <div class="row">
                <?php if (!empty($page['footer_firstcolumn'])): ?>
                <div class="large-6 columns">
                  <?php print render($page['footer_firstcolumn']); ?>
                </div>
                <?php endif; ?>
                <?php if (!empty($page['footer_secondcolumn'])): ?>
                <div class="large-6 columns">
                  <?php print render($page['footer_secondcolumn']); ?>
                </div>
                <?php endif; ?>
              </div>
              <?php endif; ?>
            </div>
          </footer>

        </section>

      <a class="exit-off-canvas"></a>
      </div>
    </div>
