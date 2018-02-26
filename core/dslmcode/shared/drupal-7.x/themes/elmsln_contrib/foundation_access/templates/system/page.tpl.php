<main id="etb-tool-nav" data-offcanvas>
  <div class="inner-wrap">
    <?php if (!empty($messages)): ?>
    <?php endif; ?>
    <section class="main-section etb-book">
      <div class="r-header row">
        <div class="r-header__left">
          <?php print render($page['header']); ?>
        </div>
        <div class="r-header__right">
          <h2 class="element-invisible"><?php print t('Primary tabs');?></h2>
          <ul class="elmsln--page--operations">
            <!-- Edit Icon -->
            <?php if (isset($edit_path)): ?>
            <li class="page-op-button">
              <?php if (arg(2) == 'edit'): ?>
              <lrnsys-button id="edit-tip" onclick="document.getElementById('edit-submit').click();" class="r-header__icon elmsln-edit-button accessible-green-text" inner-class="no-padding" hover-class="<?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>" icon="save" alt="<?php print t('Save content'); ?>">
              </lrnsys-button>
            <?php if (!empty($cis_shortcodes)) : ?>
              </li>
              <li class="page-op-button">
              <lrnsys-drawer hover-class="<?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>" align="right" alt="<?php print t('Embed this content')?>" icon="share" header="<?php print t('Embed this content'); ?>" data-jwerty-key="s" data-voicecommand="open embed (menu)">
                <?php print $cis_shortcodes; ?>
              </lrnsys-drawer>
            <?php endif; ?>
            <?php else: ?>
              <lrnsys-button id="edit-tip" href="<?php print $edit_path; ?>" class="r-header__icon elmsln-edit-button" inner-class="no-padding" data-jwerty-key="e" data-voicecommand="edit" hover-class="<?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>" icon="editor:mode-edit" alt="<?php print t('Edit content'); ?>">
              </lrnsys-button>
            <?php endif; ?>
            </li>
            <?php endif; ?>
            <!-- end Edit Icon -->
            <li class="page-op-button">
            <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras)): ?>
              <lrnsys-button id="more-options-tip" class="r-header__icon elmsln-more-button elmsln-dropdown-button" data-activates="elmsln-more-menu" aria-controls="elmsln-more-menu" aria-expanded="false" data-jwerty-key="m" data-voicecommand="open more (menu)" hover-class="<?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?>" icon="more-vert" alt="<?php print t('Less common operations'); ?>">
              </lrnsys-button>
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
              <paper-button disabled class="disabled elmsln-more-menu-button">
                <iron-icon icon="more-vert"></iron-icon>
              </paper-button>
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
          <div class="push-s1 s9 col">
          <?php if ($title && arg(0) != 'node'): ?>
            <?php print render($title_prefix); ?>
            <h2 id="page-title" class="title"><?php print $title; ?></h2>
            <?php print render($title_suffix); ?>
          <?php endif; ?>
          <a id="main-content" class="scrollspy" data-scrollspy="scrollspy"></a>
          <?php print render($page['content']); ?>
          </div>
        </div>
      </div>
    </section>
  <a class="exit-off-canvas"></a>
  </div>
</main>
<footer class="page-footer black white-text">
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
<?php print $messages; ?>