<div class="container">

  <?php if ($page['header']): print render($page['header']); endif; ?>
  <?php if ($page['highlight']): print render($page['highlight']); endif; ?>

  <div class="sidebar">
    <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
      </a>
    <?php endif; ?>

    <?php if ($site_name): ?>
      <h1 id="site-name"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a></h1>
    <?php endif; ?>

    <?php if ($site_slogan): ?>
      <p><?php print $site_slogan; ?></p>
      <hr />
    <?php endif; ?>

    <?php print theme('links', array('links' => $main_menu, 'attributes' => array('id' => 'primary', 'class' => array('links', 'clearfix', 'main-menu')))); ?>

    <?php if ($page['sidebar_first']): print render($page['sidebar_first']); endif; ?>
  </div>

  <div class="content">
    <?php print render($title_prefix); ?>
    <?php /* if ($title): ?><h1 class="page-title"><?php print $title; ?></h1><?php endif; */ ?>
    <?php print render($title_suffix); ?>

    <?php print $messages; ?>
    <?php print render($page['help']); ?>

    <?php if ($tabs): print render($tabs); endif; ?>

    <?php if ($action_links): ?><ul><?php print render($action_links); ?></ul><?php endif; ?>

    <?php print render($page['content']) ?>
  </div>

</div>

<?php if ($page['footer']): ?>
  <div class="footer">
    <div class="footer-inner">
      <?php print render($page['footer']); ?>
    </div>
  </div>
<?php endif; ?>
