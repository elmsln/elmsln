<?php
  // support our method of awesome
  if (arg(0) == 'node' && is_numeric(arg(1)) && arg(2) == '' && $page['content']['system_main']['nodes'][arg(1)]['#bundle'] == 'page') {
    print _webcomponents_app_load_app(variable_get('mooc-app-element', 'mooc-content'));
  }
  else {
?>
<main id="etb-tool-nav" data-offcanvas>
  <div class="inner-wrap">
    <?php if (!empty($messages)): ?>
    <?php endif; ?>
    <section class="main-section etb-book">
      <h2 class="element-invisible"><?php print t('Navigation');?></h2>
      <div class="r-header row">
        <div class="r-header__left">
          <?php print render($page['header']); ?>
        </div>
        <div class="r-header__right">
          <ul class="elmsln--page--operations">
            <!-- Edit Icon -->
            <?php if (isset($edit_path)): ?>
            <?php if (arg(2) == 'hax'): ?>
            <li class="page-op-button">
              <lrnsys-button href="" id="savetip" class="green lighten-2" onclick="(function(){
    var event = document.createEvent('HTMLEvents');
    event.initEvent('hax-save', true, true);
    event.eventName = 'hax-save';
    document.body.dispatchEvent(event);
    return false;
})();return false;" class="r-header__icon elmsln-save-button" inner-class="no-padding" hover-class="<?php print $cis_lmsless['lmsless_classes'][$distro]['text'] . ' text-' . $cis_lmsless['lmsless_classes'][$distro]['dark'];?> white-text" icon="icons:save" alt="<?php print t('Save'); ?>">
              </lrnsys-button>
            </li>
            <li class="page-op-button">
              <lrnsys-button id="outline-tip" href="<?php print base_path() . arg(0) . '/' . arg(1); ?>" class="r-header__icon elmsln-edit-button red lighten-2" inner-class="no-padding" icon="icons:visibility" alt="<?php print t('Back to content'); ?>">
              </lrnsys-button>
            </li>
            <li class="page-op-button">
              <lrnsys-button href="<?php print base_path() . arg(0) . '/' . arg(1); ?>/edit" id="edit-tip" class="r-header__icon elmsln-edit-button red lighten-2" data-jwerty-key="e" inner-class="no-padding" data-voicecommand="edit" icon="editor:mode-edit" alt="<?php print t('Legacy edit form'); ?>">
              </lrnsys-button>
            </li>
            <?php elseif (arg(2) == 'outline'): ?>
            <li class="page-op-button">
              <lrnsys-button id="outline-tip" href="<?php print base_path() . arg(0) . '/' . arg(1); ?>" class="r-header__icon elmsln-edit-button red lighten-2" inner-class="no-padding" icon="icons:visibility" alt="<?php print t('Back to content'); ?>">
              </lrnsys-button>
            </li>
            <?php else: ?>
            <li class="page-op-button">
               <lrnsys-button id="outline-tip" href="<?php print base_path() . arg(0) . '/' . arg(1); ?>" class="r-header__icon elmsln-edit-button red lighten-2" inner-class="no-padding" icon="icons:visibility" alt="<?php print t('Back to content'); ?>">
              </lrnsys-button>
            </li>
              <?php if (user_access('use hax')) : ?>
              <li class="page-op-button">
              <lrnsys-button id="hax-edit-tip" href="<?php print base_path() . arg(0) . '/' . arg(1); ?>/hax"  class="r-header__icon elmsln-edit-button red lighten-2" inner-class="no-padding" icon="maps:layers" alt="<?php print t('HAX editor'); ?>"><span class="element-invisible"><?php print t('HAX editor'); ?></span>
                </lrnsys-button>
              <?php endif; ?>
            </li>
              <?php endif; ?>
            <?php endif; ?>
            <?php if (!empty($cis_shortcodes)) : ?>
              <li class="page-op-button">
              <lrnsys-drawer id="embedcontent" align="right" alt="<?php print t('Embed this content')?>" icon="share" header="<?php print t('Embed this content'); ?>" data-jwerty-key="s" data-voicecommand="open embed (menu)">
                <?php print $cis_shortcodes; ?>
              </lrnsys-drawer>
              </li>
            <?php endif; ?>
            <!-- end Edit Icon -->
            <li class="page-op-button">
            <?php if ((!empty($tabs['#primary']) || !empty($tabs['#secondary']) || !empty($tabs_extras))): ?>
              <lrnsys-button id="more-options-tip" inner-class="no-padding" class="r-header__icon elmsln-more-button elmsln-dropdown-button" data-activates="elmsln-more-menu" aria-controls="elmsln-more-menu" aria-expanded="false" data-jwerty-key="m" data-voicecommand="open more (menu)" icon="more-vert" alt="<?php print t('Less common operations'); ?>">
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
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted-block-area">
          <?php print render($page['highlighted']); ?>
        </div>
      <?php endif; ?>
      <?php if ($contentwrappers): ?>
      <div class="elmsln-content-wrap row">
        <?php if (current_path() == 'mooc/book-toc') : ?>
        <div class="s9 col" role="main">
        <?php elseif (arg(2) == 'outline'): ?>
        <div class="push-s1 s10 col" role="main">
        <?php elseif (arg(2) == 'edit'): ?>
        <div class="push-s2 s7 col" role="main">
        <?php else : ?>
        <div class="push-s3 s8 col" role="main">
        <?php endif; ?>
      <?php else : ?>
      <div class="elmsln-content-wrap">
        <div role="main">
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
          <div>
          <?php if ($title && arg(0) != 'node' && $title != t('Home')): ?>
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
<?php } ?>
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