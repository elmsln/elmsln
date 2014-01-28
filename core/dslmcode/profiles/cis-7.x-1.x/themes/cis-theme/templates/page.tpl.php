<!-- Header and Nav -->
<div class="row">
<nav class="top-bar">
  <div class="back-primary">
    <ul class="title-area">
      <li class="name"><img class="logo show-for-medium-up" src="<?php print $logo; ?>" alt="<?php print $site_slogan; ?> image" title="<?php print $site_slogan; ?> image" /><span class="show-for-medium-up pipe-space">|</span><h1><?php print $linked_site_name; ?></h1></li>
      <li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li>
    </ul>
    <section class="right top-bar-section user-menu">
      <?php if ($top_bar_main_menu) :?>
        <?php print $top_bar_main_menu; ?>
      <?php endif; ?>
      <?php if (!empty($page['header'])): ?>
        <?php print render($page['header']);?>
      <?php endif; ?>
    </section>
  <?php if ($top_bar_secondary_menu) :?>
  <section class="top-bar-section main-menu">
    <div class="unit-color-border">
        <?php print $top_bar_secondary_menu; ?>
    </div>
  </section>
  <?php endif; ?>
  <?php if (isset($third_menu_links)) :?>
  <section class="top-bar-section secondary-menu">
    <div class="unit-color-border">
        <?php print $third_menu_links; ?>
    </div>
  </section>
  <?php endif; ?>
  </div>
</nav>
</div>
<div class="row show-for-medium-up unit-color">
  <?php if ($breadcrumb): print $breadcrumb; endif; ?>
</div>
<div class="row">
  <div class="small-11 small-centered columns">
    <div class="row">
    <?php if (!empty($tabs)): ?>
          <?php print render($tabs); ?>
          <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
        <?php endif; ?>
      <?php if ($messages): print $messages; endif; ?>
      <?php if (!empty($page['help'])): print render($page['help']); endif; ?>
      <a id="main-content"></a>
      
        <?php if ($title && !$is_front && (!isset($node) || (isset($node) && !in_array($node->type, array('course', 'person'))))): ?>
          <?php print render($title_prefix); ?>
          <h1 id="page-title" class="title"><?php print check_markup($title, 'textbook_editor'); ?></h1>
          <?php print render($title_suffix); ?>
        <?php endif; ?>
    </div>
    <div class="row">
      <div id="main" class="<?php print $main_grid; ?> columns">
        <?php if (!empty($page['highlighted'])): ?>
          <div class="highlight panel callout">
            <?php print render($page['highlighted']); ?>
          </div>
        <?php endif; ?>
    
        <?php if ($action_links): ?>
          <ul class="action-links">
            <?php print render($action_links); ?>
          </ul>
        <?php endif; ?>
        <?php print render($page['content']); ?>
      </div>
      <?php if (!empty($page['sidebar_first'])): ?>
        <div id="sidebar-first" class="<?php print $sidebar_first_grid; ?> columns sidebar ">
          <?php print render($page['sidebar_first']); ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($page['sidebar_second'])): ?>
        <div id="sidebar-second" class="<?php print $sidebar_sec_grid;?> columns sidebar">
          <?php print render($page['sidebar_second']); ?>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>
<div class="row">
<?php if (!empty($page['footer_first']) || !empty($page['footer_middle']) || !empty($page['footer_last'])): ?>
<footer class="row">
    <?php if (!empty($page['footer_first'])): ?>
      <div id="footer-first" class="large-4 columns">
        <?php print render($page['footer_first']); ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($page['footer_middle'])): ?>
      <div id="footer-middle" class="large-4 columns">
        <?php print render($page['footer_middle']); ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($page['footer_last'])): ?>
      <div id="footer-last" class="large-4 columns">
        <?php print render($page['footer_last']); ?>
      </div>
    <?php endif; ?>
</footer>
<?php endif; ?>
<div class="bottom-bar panel">
  <div class="show-for-medium-up row">
    <div class="large-10 columns">
      <img class="logo" src="<?php print $logo; ?>" alt="<?php print $site_slogan; ?> image" title="<?php print $site_slogan; ?> image" />
      <span class="pipe-space">|</span><h3 class="footer-name"><?php print $linked_site_name; ?></h3>
    </div>
    <div class="large-2 columns">
    <button>Contact us</button>
    </div>
  </div>
  <div class="row">
  <hr class="footer-divider">
  </div>
  <div class="row">
    <div class="large-8 small-12 columns">
    </div>
    <div class="large-4 small-12 columns powered_by">
    </div>
  </div>
  <div class="row">
    <div class="large-12 small-12 columns">
      <?php if(!empty($page['bottom_menu'])) :?>
        <?php print render($page['bottom_menu']); ?>
      <?php endif; ?>
    </div>
  </div>
</div>
</div>