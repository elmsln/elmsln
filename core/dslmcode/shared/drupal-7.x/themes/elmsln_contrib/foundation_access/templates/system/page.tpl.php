<?php
/**
 * @file
 * Default theme implementation to display a region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
  if (!isset($cis_lmsless['active'])) {
    $cis_lmsless['active']['title'] = '';
  }
?>
    <div id="etb-tool-nav" class="off-canvas-wrap" data-offcanvas>
      <div class="inner-wrap">
        <?php if (isset($cis_lmsless['admin_status_bar']) && !empty($cis_lmsless['admin_status_bar'])) : ?>
         <!-- Admin Status Bar -->
         <div class="row full admin-status-bar divider-bottom">
            <div class="columns small-12">
              <?php foreach($cis_lmsless['admin_status_bar'] as $admin_status_msg_key => $admin_status_msg) : ?>
              <span class="<?php print $admin_status_msg_key;?>">
                <?php print (isset($admin_status_msg['content']) ? $admin_status_msg['content'] : ''); ?>
                <?php if (isset($admin_status_msg['modal'])) : ?>
                  <a href="#" data-reveal-id="<?php print $admin_status_msg['modal']; ?>" class="admin-alert">
                <?php endif; ?>
                <?php print (isset($admin_status_msg['title']) ? '<span>' . $admin_status_msg['title'] . '</span>' : ''); ?>
                <?php if (isset($admin_status_msg['modal'])) : ?>
                  </a>
                <?php endif; ?>
              </span>
              <?php endforeach ?>
            </div>
          </div>
        <?php endif; ?>
        <!-- progress bar -->
          <div class="page-scroll progress">
            <span class="meter" style="width: 0%"></span>
          </div>
          <nav class="tab-bar etb-tool">
            <section class="left">
              <!-- If the off-canvas menu is in use, activate off canvas toggle -->
              <?php if (!empty($page['left_menu'])): ?>
                <a class="left-off-canvas-toggle open menu-icon" href="#"><span><?php print $cis_lmsless['active']['title'] ?></span></a>
              <?php else : ?>
                <span><?php print $cis_lmsless['active']['title'] ?></span>
              <?php endif; ?>
              <!-- Add Button -->
             <?php if (!empty($page['add_content_menu'])): ?>
                <?php print render($page['add_content_menu']); ?>
             <?php endif; ?>
            </section>

          <section class="middle tab-bar-section">
          <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras)): ?>
              <li class="toolbar-menu-icon"><a href="#" class="off-canvas-toolbar-item toolbar-menu-icon" data-dropdown="middle-section-buttons" aria-controls="middle-section-buttons" aria-expanded="false">
                <div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
              </a></li>
              <?php if (!empty($cis_shortcodes)) : ?>
                <li class="toolbar-menu-icon divider-left"><a href="#" class="off-canvas-toolbar-item toolbar-menu-icon" data-reveal-id="page-share-menu" aria-controls="cis-shortcodes-drop" aria-expanded="false">
                  <div class="icon-collab-black off-canvas-toolbar-item-icon"></div>
                </a></li>
              <?php endif; ?>
              <?php if (isset($speedreader) || isset($mespeak)) : ?>
                <li class="toolbar-menu-icon divider-left"><a href="#" class="off-canvas-toolbar-item toolbar-menu-icon" data-reveal-id="page-accessibility-menu" aria-controls="accessibility-drop" aria-expanded="false">
                  <div class="icon-access-black off-canvas-toolbar-item-icon"></div>
                </a></li>
              <?php endif; ?>
          <?php endif; ?>
          </section>
          <?php print render($page['cis_appbar_second']); ?>
          <!-- Share Modal -->
          <?php if (isset($cis_shortcodes)) : ?>
          <div id="page-share-menu" class="reveal-modal" data-reveal aria-labelledby="Share" aria-hidden="true" role="dialog">
            <h2 id="Share"><?php print t('Share') ?></h2>
            <?php print $cis_shortcodes; ?>
            <a class="close-reveal-modal">&#215;</a>
          </div>
          <?php endif; ?>
          <!-- /accessibility dropdown -->
          <!-- Accessibility Modal -->
          <?php if (isset($speedreader) || isset($mespeak)) : ?>
          <div id="page-accessibility-menu" class="reveal-modal" data-reveal aria-labelledby="Accessibility" aria-hidden="true" role="dialog">
            <h2 id="Accessibility"><?php print t('Accessibility') ?></h2>
             <?php if (isset($speedreader)) : ?>
            <a href="#" class="off-canvas-toolbar-item access-icon" data-reveal-id="block-speedreader-speedreader-block-nav-modal" aria-controls="accessibility-drop" aria-expanded="false"><?php print t('Speed reader'); ?></a>
            <?php endif; ?>
            <?php if (isset($mespeak)) : ?>
            <a href="#" class="off-canvas-toolbar-item access-icon" data-reveal-id="block-mespeak-mespeak-block-nav-modal" aria-controls="accessibility-drop" aria-expanded="false"><?php print t('Speak page'); ?></a>
            <?php endif; ?>
            <a class="close-reveal-modal">&#215;</a>
          </div>
          <?php endif; ?>
          <!-- /accessibility dropdown -->
        </nav>

        <!-- Middle Section Dropdown Page Tabs -->
        <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras)): ?>
        <div id="middle-section-buttons" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
          <?php if (!empty($tabs)): ?>
              <?php print render($tabs); ?>
            <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
          <?php endif; ?>
          <?php if ($action_links): ?>
              <?php print render($action_links); ?>
          <?php endif; ?>
          <?php if (isset($tabs_extras)): ksort($tabs_extras); ?>
           <?php foreach ($tabs_extras as $group) : ?>
            <?php foreach ($group as $button) : ?>
              <li><?php print $button; ?></li>
            <?php endforeach; ?>
           <?php endforeach; ?>
          <?php endif; ?>
        </div>
      <?php endif; ?>

        <?php print render($page['cis_appbar_first']); ?>

        <?php print render($page['left_menu']); ?>

        <section class="main-section etb-book">
          <?php if (!empty($messages)): ?>
            <div class="region-messeges row">
              <?php print $messages; ?>
            </div>
          <?php endif; ?>

          <?php if ($breadcrumb) : ?>
            <div class="breadcrumb-wrapper">
            <?php print $breadcrumb; ?>
            </div>
          <?php endif; ?>

          <?php if (!empty($page['header'])): ?>
            <div class="region-header row">
              <?php print render($page['header']); ?>
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
                  <?php if ($title): ?>
                    <?php print render($title_prefix); ?>
                      <h1 id="page-title" class="title"><?php print $title; ?></h1>
                    <?php print render($title_suffix); ?>
                  <?php endif; ?>
                  <?php print render($page['content']); ?>
                </div>
              </div>
            </div>
          </div>
        </section>

      <a class="exit-off-canvas"></a>
      </div>
    </div>
    <footer class="sticky-footer">
      <div class="row">
        <div class="small-12 medium-push-1 medium-10 columns">
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
<!-- generic container for other off canvas modals -->
<?php print render($page['cis_appbar_modal']); ?>
