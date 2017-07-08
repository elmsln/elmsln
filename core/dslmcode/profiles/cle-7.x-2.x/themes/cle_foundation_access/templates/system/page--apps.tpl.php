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
    <main id="etb-tool-nav" data-offcanvas>
      <div class="inner-wrap">
        <!-- progress bar -->
        <div class="page-scroll progress white">
          <span class="meter <?php print $cis_lmsless['lmsless_classes'][$distro]['color'] . ' ' .$cis_lmsless['lmsless_classes'][$distro]['dark'];?>" style="width: 0%"></span>
        </div>
        <?php if (!empty($messages)): ?>
        <?php endif; ?>
        <section class="main-section etb-book">
          <div class="r-header row">
            <div class="r-header__left">
              <?php print render($page['header']); ?>
            </div>
            <div class="r-header__right">
              <h2 class="element-invisible"><?php print t('Primary tabs');?></h2>
              <ul class="r-header__edit-icons">
                <!-- Edit Icon -->
                <?php if (isset($edit_path)): ?>
                <li class="r-header__edit-icons__list-item">
                  <?php if (arg(2) == 'edit'): ?>
                  <a tabindex="-1" id="edit-tip" onclick="document.getElementById('edit-submit').click();" class="r-header__icon elmsln-edit-button">
                  <paper-button>
                    <i class="material-icons green-text text-darken-4">save</i>
                    <span class="element-invisible"><?php print t('Save content'); ?></span>
                  </paper-button>
                  </a>
                  <paper-tooltip for="edit-tip"><?php print t('Save')?></paper-tooltip>
                <?php else: ?>
                  <a tabindex="-1" id="edit-tip" href="<?php print $edit_path; ?>" class="r-header__icon elmsln-edit-button" data-jwerty-key="e" data-voicecommand="edit">
                  <paper-button>
                    <i class="material-icons black-text" data-elmsln-hover="<?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>">mode_edit</i>
                    <span class="element-invisible"><?php print t('Edit content'); ?></span>
                  </paper-button>
                  </a>
                  <paper-tooltip for="edit-tip"><?php print t('Edit content')?></paper-tooltip>
                <?php endif; ?>
                </li>
                <?php endif; ?>
                <?php if (!empty($cis_shortcodes)) : ?>
                  <li class="r-header__edit-icons__list-item">
                    <a tabindex="-1" id="elmsln-shortcodes-button" title="<?php print t('Embed this item')?>" class="r-header__icon elmsln-share-button elmsln-right-side-nav-trigger" data-activates="block-cis-shortcodes-cis-shortcodes-block-nav-modal" aria-controls="block-cis-shortcodes-cis-shortcodes-block-nav-modal" aria-expanded="false" data-jwerty-key="s" data-voicecommand="open share (menu)">
                    <paper-button>
                      <i class="material-icons black-text" data-elmsln-hover="<?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>">share</i>
                      <span class="element-invisible"><?php print t('Menu to embed this elsewhere'); ?></span>
                    </paper-button>
                    </a>
                    <paper-tooltip for="elmsln-shortcodes-button"><?php print t('Embed content elsewhere')?></paper-tooltip>
                  </li>
                <?php endif; ?>
                <?php if (!empty($a11y)) : ?>
                  <li class="r-header__edit-icons__list-item">
                  <lrnsys-drawer align="right" alt="<?php print t('Your preferences')?>" icon="accessibility" header="<?php print t('Preferences'); ?>" data-jwerty-key="a" data-voicecommand="open preferences (menu)">
                    <?php print $a11y; ?>
                  </lrnsys-drawer>
                  </li>
                <?php endif; ?>
                <!-- end Edit Icon -->
                <li class="r-header__edit-icons__list-item">
                <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras)): ?>
                  <a tabindex="-1" id="more-options-tip" class="r-header__icon elmsln-more-button elmsln-dropdown-button" data-activates="elmsln-more-menu" aria-controls="elmsln-more-menu" aria-expanded="false" data-jwerty-key="m" data-voicecommand="open more (menu)">
                  <paper-button>
                    <i class="material-icons black-text" data-elmsln-hover="<?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>">more_vert</i>
                    <span class="element-invisible"><?php print t('Less common options'); ?></span>
                  </paper-button>
                  </a>
                  <paper-tooltip for="more-options-tip"><?php print t('Less common options')?></paper-tooltip>
                  <ul id="elmsln-more-menu" class="dropdown-content" aria-hidden="true" tabindex="-1">
                  <?php if (!empty($tabs)): ?>
                      <?php print render($tabs); ?>
                    <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
                  <?php endif; ?>
                  <?php if (!empty($action_links)): ?>
                      <?php print render($action_links); ?>
                  <?php endif; ?>
                  <?php if (isset($tabs_extras)): ksort($tabs_extras); ?>
                   <?php foreach ($tabs_extras as $group) : ?>
                    <?php foreach ($group as $button) : ?>
                      <li class="elmsln-more-menu-option"><?php print $button; ?></li>
                    <?php endforeach; ?>
                   <?php endforeach; ?>
                  <?php endif; ?>
                  </ul>
                <?php else: ?>
                  <a tabindex="-1" href="#no-options" title="<?php print t('No additional options')?>" class="r-header__icon fa-action-disabled  elmsln-more-button">
                  <div class="icon-wrapper">
                    <i class="zmdi zmdi-more-vert"></i>
                    <span class="element-invisible"><?php print t('No additional options'); ?></span>
                  </div>
                  </a>
                <?php endif; ?>
                </li>
              </ul>
            </div>
          </div>
          <?php if ($contentwrappers): ?>
          <div class="elmsln-content-wrap row">
            <div class="s12 push-m2 m10 push-l1 l11 col" role="main">
          <?php else : ?>
          <div class="elmsln-content-wrap">
            <div role="main">
          <?php endif; ?>
              <?php if (!empty($page['highlighted'])): ?>
                <div class="highlighted-block-area">
                  <?php print render($page['highlighted']); ?>
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
              <?php if (!empty($page['local_header']) || !empty($page['local_subheader'])): ?>
                <div class="r-local-header-wrapper row">
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
                </div>
              <?php endif; ?>
              <div class="push-s1 s10 col">
              <a id="main-content" class="scrollspy" data-scrollspy="scrollspy"></a>
              <div class="region-messeges">
                <?php print $messages; ?>
              </div>
              <?php print render($page['content']); ?>
              </div>
            </div>
          </div>
        </section>
      <a class="exit-off-canvas"></a>
      </div>
    </main>
    <footer class="page-footer <?php print $cis_lmsless['lmsless_classes'][$distro]['color'] . ' ' . $cis_lmsless['lmsless_classes'][$distro]['dark'] . ' ' . $cis_lmsless['lmsless_classes'][$distro]['color'];?>-border white-text">
      <div class="container">
        <div class="row">
          <div class="s12 push-m1 m-10 col">
            <?php if (!empty($page['footer'])): ?>
            <?php print render($page['footer']); ?>
            <?php endif; ?>
          </div>
          <?php if (!empty($page['footer_firstcolumn']) || !empty($page['footer_secondcolumn'])): ?>
          <hr/>
          <div class="row">
            <?php if (!empty($page['footer_firstcolumn'])): ?>
            <div class="l6 col">
              <?php print render($page['footer_firstcolumn']); ?>
            </div>
            <?php endif; ?>
            <?php if (!empty($page['footer_secondcolumn'])): ?>
            <div class="l6 col">
              <?php print render($page['footer_secondcolumn']); ?>
            </div>
            <?php endif; ?>
          </div>
          <?php endif; ?>
        </div>
      </div>
    </footer>
    <!-- generic container for other off canvas modals -->
    <div class="elmsln-modal-container">
      <?php print render($page['cis_lmsless_modal']); ?>
    </div>