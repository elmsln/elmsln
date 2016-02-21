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
            <div class="r-header__right" ng-controller="FaHeaderOptionsCtrl as ctrl" ng-cloak ng-app="Fa">
              <ul class="r-header__edit-icons">
                <!-- Edit Icon -->
                <?php if (isset($edit_path)): ?>
                <li class="r-header__edit-icons__list-item">
                  <?php if (arg(2) == 'edit'): ?>
                  <a href="#" onclick="document.getElementById('edit-submit').click();" title="<?php print t('Save')?>" class="r-header__icon elmsln-edit-button">
                    <i class="zmdi zmdi-save"></i>
                  </a>
                <?php else: ?>
                  <a href="<?php print $edit_path; ?>" title="<?php print t('Edit content')?>" class="r-header__icon  elmsln-edit-button" data-jwerty-key="e" data-voicecommand="edit">
                    <i class="zmdi zmdi-edit"></i>
                  </a>
                <?php endif; ?>
                </li>
                <?php endif; ?>
                <?php if (!empty($cis_shortcodes)) : ?>
                  <li class="r-header__edit-icons__list-item"><a href="#" title="<?php print t('Share')?>" class="r-header__icon elmsln-share-button" data-reveal-id="block-cis-shortcodes-cis-shortcodes-block-nav-modal" aria-controls="cis-shortcodes-drop" aria-expanded="false" data-jwerty-key="s" data-voicecommand="open share (menu)">
                    <i class="zmdi zmdi-arrow-split"></i>
                  </a></li>
                <?php endif; ?>
                <?php if (!empty($a11y)) : ?>
                  <li class="r-header__edit-icons__list-item"><a href="#" title="<?php print t('Accessibility options')?>" class="r-header__icon elmsln-accessibility-button" data-reveal-id="page-accessibility-menu" aria-controls="accessibility-drop" aria-expanded="false" data-jwerty-key="a" data-voicecommand="open accessibility (menu)">
                    <i class="zmdi zmdi-tune"></i>
                  </a></li>
                <?php endif; ?>
                <!-- end Edit Icon -->
                <li class="r-header__edit-icons__list-item">
                <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras)): ?>
                    <a href="#" title="<?php print t('More')?>" class="r-header__icon elmsln-more-button" data-dropdown="r-header__icon--advanced" aria-controls="r-header__icon--advanced" aria-expanded="false" data-jwerty-key="m" data-voicecommand="open more (menu)">
                      <i class="zmdi zmdi-more-vert"></i>
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
                <?php else: ?>
                  <a href="#" title="<?php print t('No additional options')?>" class="r-header__icon fa-action-disabled  elmsln-more-button">
                      <i class="zmdi zmdi-more-vert"></i>
                    </a>
                <?php endif; ?>

<!--
                  <md-button class="md-icon-button r-header__icon" href="<?php print $edit_path; ?>" title="<?php print t('Edit content')?>">
                    <i class="zmdi zmdi-edit"></i>
                  </md-button>
                </li>
                <?php endif; ?>

                <li class="r-header__edit-icons__list-item">
                  <md-menu md-position-mode="target-right target">
                    <md-button aria-label="Course outline options menu" class="md-icon-button r-header__icon" ng-click="ctrl.openMenu($mdOpenMenu, $event)">
                     <i class="zmdi zmdi-collection-text"></i>
                    </md-button>
                   <md-menu-content width="4">
                     <md-menu-item>
                       <md-button href="#">Add child page</md-button>
                     </md-menu-item>
                     <md-menu-item>
                       <md-button href="#">Edit child outline</md-button>
                     </md-menu-item>
                     <md-menu-item>
                       <md-button href="#">Edit course outline</md-button>
                     </md-menu-item>
                     <md-menu-item>
                       <md-button href="#">Duplicate outline</md-button>
                     </md-menu-item>
                    </md-menu-content>
                   </md-menu>
                </li> -->
              </ul>
            </div>
          </div>
          <div class="row content-element-region-wrapper">
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
<?php if (!empty($a11y)) : ?>
<div id="page-accessibility-menu" class="reveal-modal" data-reveal aria-labelledby="<?php print t('Accessibility'); ?>" aria-hidden="true" role="dialog">
  <h2 id="Accessibility"><?php print t('Accessibility') ?></h2>
  <?php print $a11y; ?>
  <a class="close-reveal-modal" data-voicecommand="close (menu)" data-jwerty-key="Esc">&#215;</a>
</div>
<?php endif; ?>
<!-- /Accessibility Modal -->


