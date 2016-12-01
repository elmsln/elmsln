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
        <div class="page-scroll progress <?php print $cis_lmsless['lmsless_classes'][$distro]['color'] . ' ' . $cis_lmsless['lmsless_classes'][$distro]['light']; ?>">
          <span class="meter <?php print $cis_lmsless['lmsless_classes'][$distro]['color'] . ' ' .$cis_lmsless['lmsless_classes'][$distro]['dark'];?>" style="width: 0%"></span>
        </div>
        <?php if (!empty($messages)): ?>
        <div class="region-messeges">
          <?php print $messages; ?>
        </div>
        <?php endif; ?>
        <section class="main-section etb-book">
          <div class="r-header row">
            <div class="r-header__left">
              <div class="col s12">
                <?php print render($page['header']); ?>
              </div>
            </div>
            <div class="r-header__right">
              <h2 class="element-invisible"><?php print t('Primary tabs');?></h2>
              <ul class="r-header__edit-icons">
                <!-- Edit Icon -->
                <?php if (isset($edit_path)): ?>
                <li class="r-header__edit-icons__list-item">
                  <?php if (arg(2) == 'edit'): ?>
                  <a href="#save-content" onclick="document.getElementById('edit-submit').click();" title="<?php print t('Save')?>" class="r-header__icon elmsln-edit-button">
                    <i class="material-icons green-text text-darken-4">save</i>
                    <span class="element-invisible"><?php print t('Save content'); ?></span>
                  </a>
                <?php else: ?>
                  <a href="<?php print $edit_path; ?>" title="<?php print t('Edit content')?>" class="r-header__icon  elmsln-edit-button" data-jwerty-key="e" data-voicecommand="edit">
                    <i class="material-icons black-text <?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>">mode_edit</i>
                    <span class="element-invisible"><?php print t('Edit content'); ?></span>
                  </a>
                <?php endif; ?>
                </li>
                <?php endif; ?>
                <?php if (!empty($cis_shortcodes)) : ?>
                  <li class="r-header__edit-icons__list-item"><a id="elmsln-shortcodes-button" href="#elmsln-shortcodes" title="<?php print t('Share')?>" class="r-header__icon elmsln-share-button elmsln-right-side-nav-trigger" data-activates="block-cis-shortcodes-cis-shortcodes-block-nav-modal" aria-controls="block-cis-shortcodes-cis-shortcodes-block-nav-modal" aria-expanded="false" data-jwerty-key="s" data-voicecommand="open share (menu)">
                    <i class="material-icons black-text <?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>">share</i>
                    <span class="element-invisible"><?php print t('Short code menu'); ?></span>
                  </a></li>
                <?php endif; ?>
                <?php if (!empty($a11y)) : ?>
                  <li class="r-header__edit-icons__list-item"><a id="elmsln-preferences-button"  href="#elmsln-preferences" title="<?php print t('Preferences')?>" class="r-header__icon elmsln-accessibility-button elmsln-right-side-nav-trigger" data-activates="page-accessibility-menu" aria-controls="page-accessibility-menu" aria-expanded="false" data-jwerty-key="a" data-voicecommand="open preferences (menu)">
                    <i class="material-icons black-text <?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>">accessibility</i>
                    <span class="element-invisible"><?php print t('Preferences menu'); ?></span>
                  </a></li>
                <?php endif; ?>
                <!-- end Edit Icon -->
                <li class="r-header__edit-icons__list-item">
                <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras)): ?>
                    <a href="#elmsln-more" title="<?php print t('More')?>" class="r-header__icon elmsln-more-button elmsln-dropdown-button" data-activates="elmsln-more-menu" aria-controls="elmsln-more-menu" aria-expanded="false" data-jwerty-key="m" data-voicecommand="open more (menu)">
                      <i class="material-icons black-text <?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>">more_vert</i>
                      <span class="element-invisible"><?php print t('More options'); ?></span>
                    </a>
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
                  <a href="#no-options" title="<?php print t('No additional options')?>" class="r-header__icon fa-action-disabled  elmsln-more-button">
                      <i class="zmdi zmdi-more-vert"></i>
                      <span class="element-invisible"><?php print t('No additional options'); ?></span>
                    </a>
                <?php endif; ?>
                </li>
              </ul>
            </div>
          </div>
          <?php if ($contentwrappers): ?>
          <div class="row">
            <div class="s12 m12 push-l1 l10 col" role="main">
          <?php else : ?>
          <div>
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
              <?php if ($title && arg(0) != 'node'): ?>
                <?php print render($title_prefix); ?>
                  <h2 id="page-title" class="title"><?php print $title; ?></h2>
                <?php print render($title_suffix); ?>
              <?php endif; ?>
              <?php print render($page['content']); ?>
            </div>
          </div>
        </section>
      <a class="exit-off-canvas"></a>
      </div>
    </main>
    <footer class="page-footer <?php print $cis_lmsless['lmsless_classes'][$distro]['color'] . ' ' . $cis_lmsless['lmsless_classes'][$distro]['light'];?>">
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
    <!-- Accessibility side nav -->
    <?php if (!empty($a11y)) : ?>
    <section id="page-accessibility-menu" class="elmsln-modal elmsln-modal-hidden side-nav disable-scroll" aria-label="<?php print t('Preferences'); ?>" aria-hidden="true" role="dialog" tabindex="-1">
        <div class="center-align valign-wrapper elmsln-modal-title-wrapper <?php print $cis_lmsless['lmsless_classes'][$distro]['color'] . ' ' . $cis_lmsless['lmsless_classes'][$distro]['light'];?> <?php print $cis_lmsless['lmsless_classes'][$distro]['color'];?>-border">
        <h2 class="flow-text valign elmsln-modal-title"><?php print t('Preferences'); ?></h2>
          <a href="#close-dialog" aria-label="<?php print t('Close'); ?>" class="close-reveal-side-nav" data-voicecommand="close (menu)" data-jwerty-key="Esc" >&#215;</a>
        </div>
        <div class="elmsln-modal-content">
          <?php print $a11y; ?>
        </div>
    </section>
    <?php endif; ?>
    <!-- /Accessibility side nav -->