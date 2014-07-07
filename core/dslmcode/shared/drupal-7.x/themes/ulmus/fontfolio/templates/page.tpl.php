<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 */
?>
<div id="main_container"> 
  <header id="header"><div class="section clearfix">
    <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="logo">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a>
    <?php endif; ?>

    <?php if ($site_name || $site_slogan): ?>
      <div id="name-and-slogan">
        <?php if ($site_name): ?>
          <?php if ($title): ?>
            <div id="site-name"><strong>
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
            </strong></div>
          <?php else: /* Use h1 when the content title is empty */ ?>
            <h1 id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
            </h1>
          <?php endif; ?>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
          <div id="site-slogan"><?php print $site_slogan; ?></div>
        <?php endif; ?>
      </div> <!-- /#name-and-slogan -->
    <?php endif; ?>

    <?php if ($secondary_menu): ?>
      <nav id="header_menu"><div class="section">
        
        <?php print theme('links__system_secondary_menu', array(
                'links' => $secondary_menu,
                'attributes' => array(
                  'id' => 'secondary-menu',
                  'class' => array('menu'),
                ),
              'heading' => array(
                'text' => t('More info'),
                'level' => 'h2',
                'class' => array('element-invisible'),
              ))); ?>
      </div></nav> <!-- /.section, /#header_menu -->
    <?php endif; ?>

    </div></header> <!-- /.section, /#header -->
  <div id="header_top">
    <div class="header_top_border"></div>
    <a class="home-icon toggle" href="<?php print $front_page; ?>"><img src="<?php print $base_path . $directory ?>/styles/images/glyphicons_020_home.png"></a>
  <?php if ($social_links): ?>
    <div class="social">
      <?php print $social_links; ?>
      <div class="clear"></div>
    </div><!--//social-->
    <?php endif; ?>
    <?php if ($page['search']): ?>
      <a class="toggle-search toggle" href="#header_top"><img src="<?php print $base_path . $directory ?>/styles/images/glyphicons_027_search.png"></a>
      <div class="search">
        <?php print render($page['search']); ?>
      </div>
    <?php endif; ?>
    <?php if ($lang_links): ?> 
      <nav id="langs">
        <?php print theme('links', array(
              'links' => $lang_links,
              'attributes' => array(
                'class' => array('menu'),
              ),
            'heading' => array(
              'text' => t('Langs'),
              'level' => 'h2',
              'class' => array('element-invisible'),
        ))); ?>
      </nav><!--//langs-->
    <?php endif; ?>
    <?php if ($main_menu): ?>
      <a class="toggle-nav toggle" href="#header_top"><img src="<?php print $base_path . $directory ?>/styles/images/icon_nav_toggle-black.gif"></a> 
      <nav class="menu_cont">
        <div class="social">
          <?php print $social_links; ?>
        </div><!--//social-->
        <?php print theme('links__system_main_menu', array(
          'links' => $main_menu,
          'attributes' => array(
            'id' => 'menu',
            'class' => array('links', 'inline', 'clearfix', 'menu'),
          ),
          'heading' => array(
            'text' => t('Menu'),
            'level' => 'h2',
            'class' => array('element-invisible'),
          )));
        ?>
        <?php if ($secondary_menu): ?>       
          <?php print theme('links__system_secondary_menu', array(
                  'links' => $secondary_menu,
                  'attributes' => array(
                    'id' => 'sub-menu',
                    'class' => array('menu'),
                  ),
                'heading' => array(
                  'text' => t('More info'),
                  'level' => 'h3',
                  'class' => array('element-invisible'),
                ))); ?>
        <?php endif; ?>
      </nav><!--//menu_cont-->
    <?php endif; ?>    <div class="clear"></div>
  </div> <!-- /#header_top --> 
    <?php print $messages; ?>

      <div id="content" class="column">
        <div class="section">
        <a id="main-content"></a>
        <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php if (!$is_front && (arg(0) != 'taxonomy')) :?>
          <div id="single_left">
        <?php endif;?>
        <?php print render($title_prefix); ?>
        <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
        <?php if (!$is_front && (arg(0) != 'taxonomy')) :?>
          </div><!-- /single_left -->
          <?php if ($page['sidebar']): ?>
            <aside id="sidebar" class="column sidebar"><section class="section">
            <?php print render($page['sidebar']); ?>
            </section></aside> <!-- /.section, /#sidebar-first -->
          <?php endif; ?>
        <?php endif;?>
      </div>
    </div> <!-- /.section, /#content -->
    <footer id="footer">
      <section class="section">
        <?php print render($page['footer']); ?>
      </section>
    </footer> <!-- /.section, /#footer -->

  </div> <!-- /#main_container -->
