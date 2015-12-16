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
        <!-- progress bar -->
        <div class="page-scroll progress">
          <span class="meter" style="width: 0%"></span>
        </div>
        <section class="main-section etb-book">
          <div class="r-header row">
            <div class="r-header__left">
              <?php print render($page['header']); ?>
            </div>
            <div class="r-header__right">
              <ul class="r-header__edit-icons">
                <!-- Edit Icon -->
                <?php if (isset($edit_path)): ?>
                <li class="r-header__edit-icons__list-item">
                  <a href="<?php print $edit_path; ?>" title="<?php print t('Edit content')?>" class="r-header__icon">
                    <div class="icon icon-edit-black"></div>
                  </a>
                </li>
                <?php endif; ?>
                <!-- end Edit Icon -->
                <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras)): ?>
                <li class="r-header__edit-icons__list-item">
                  <a href="#" class="r-header__icon" data-dropdown="r-header__icon--advanced" aria-controls="r-header__icon--advanced" aria-expanded="false">
                    <div class="icon icon-gear-outline"></div>
                    <span class="icon--dropdown"></span>
                  </a>
                  <ul id="r-header__icon--advanced" data-dropdown-content class="f-dropdown f-dropdown--classic content" aria-hidden="true" tabindex="-1">
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
                  </ul>
                </li>
              <?php endif; ?>
              <?php if (!empty($cis_shortcodes)) : ?>
                <li class="r-header__edit-icons__list-item"><a href="#" class="r-header__icon r-header__icon-secondary" data-reveal-id="block-cis-shortcodes-cis-shortcodes-block-nav-modal" aria-controls="cis-shortcodes-drop" aria-expanded="false">
                  <div class="icon-collab-black off-canvas-toolbar-item-icon"></div>
                </a></li>
              <?php endif; ?>
              <?php if (isset($speedreader) || isset($mespeak)) : ?>
                <li class="r-header__edit-icons__list-item"><a href="#" class="r-header__icon r-header__icon-secondary" data-reveal-id="page-accessibility-menu" aria-controls="accessibility-drop" aria-expanded="false">
                  <div class="icon-access-black off-canvas-toolbar-item-icon"></div>
                </a></li>
              <?php endif; ?>
              </ul>
            </div>
          </div>
          <div class="row">
            <div class="content-element-region small-12 medium-12 large-12 columns">
              <div class="row">
                <div class="small-12 medium-12 large-push-1 large-10 columns" role="content">
                  <?php if (!empty($page['highlighted'])): ?>
                    <div class="highlight panel callout">
                      <?php print render($page['highlighted']); ?>
                    </div>
                  <?php endif; ?>

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

                  <?php if (!empty($page['help'])): ?>
                    <div class="region-help row">
                      <?php print render($page['help']); ?>
                    </div>
                  <?php endif; ?>
                  <?php if (!empty($page['local_header'])): ?>
                  <div class="r-local-header row">
                    <?php print render($page['local_header']); ?>
                  </div>
                  <?php endif; ?>
                  <?php if (!empty($page['local_subheader'])): ?>
                  <div class="r-local-subheader row">
                    <?php print render($page['local_subheader']); ?>
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
<?php print render($page['cis_lmsless_modal']); ?>
<!-- Accessibility Modal -->
<?php if (isset($speedreader) || isset($mespeak)) : ?>
<div id="page-accessibility-menu" class="reveal-modal" data-reveal aria-labelledby="<?php print t('Accessibility'); ?>" aria-hidden="true" role="dialog">
  <h2 id="Accessibility"><?php print t('Accessibility') ?></h2>
   <?php if (isset($speedreader)) : ?>
  <a href="#" data-reveal-id="block-speedreader-speedreader-block-nav-modal" aria-controls="accessibility-drop" aria-expanded="false"><?php print t('Speed reader'); ?></a>
  <?php endif; ?>
  <?php if (isset($mespeak)) : ?>
  <a href="#" data-reveal-id="block-mespeak-mespeak-block-nav-modal" aria-controls="accessibility-drop" aria-expanded="false"><?php print t('Speak page'); ?></a>
  <?php endif; ?>
  <a class="close-reveal-modal">&#215;</a>
</div>
<?php endif; ?>
<!-- /Accessibility Modal -->
