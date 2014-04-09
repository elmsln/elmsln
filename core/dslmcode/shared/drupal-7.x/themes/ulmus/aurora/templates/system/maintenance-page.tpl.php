<?php

/**
 * @file
 * Implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in page.tpl.php.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 * @see bartik_process_maintenance_page()
 */
?>
<!DOCTYPE html>
<!--[if lt IE 7 ]> <html class="ie6 no-js" <?php print $html_attributes; ?>> <![endif]-->
<!--[if IE 7 ]>    <html class="ie7 no-js" <?php print $html_attributes; ?>> <![endif]-->
<!--[if IE 8 ]>    <html class="ie8 no-js" <?php print $html_attributes; ?>> <![endif]-->
<!--[if IE 9 ]>    <html class="ie9 no-js" <?php print $html_attributes; ?>> <![endif]-->
<!--[if (gt IE 9)|!(IE)]><!--> <html class="no-js" <?php print $html_attributes; ?>> <!--<![endif]-->
  <head>
    <?php print $head; ?>
    <title><?php print $head_title; ?></title>
    <?php print $styles; ?>
    <?php print $scripts; ?>
  </head>
  <body class="<?php print $classes; ?>" <?php print $body_attributes;?>>
    <div id="skip-link">
      <a href="#main-content" class="element-invisible element-focusable" role="link"><?php print t('Skip to main content'); ?></a>
    </div>
    <?php print $page_top; ?>
    <div id="page" role="document">
      <header id="header" role="banner" class="clearfix">

        <?php if ($logo): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
          </a>
        <?php endif; ?>

        <?php if ($site_name || $site_slogan): ?>
          <div id="name-and-slogan">
            <?php if ($site_name): ?>
              <h1 id="site-name">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
              </h1>
            <?php endif; ?>

            <?php if ($site_slogan): ?>
              <h3 id="site-slogan"><?php print $site_slogan; ?></h3>
            <?php endif; ?>
          </div><!-- #name-and-slogan -->
        <?php endif; ?>
      </header>


      <?php if ($messages): ?>
        <div id="messages" role="alertdialog"><?php print $messages; ?></div>
      <?php endif; ?>

      <div id="main" role="main" class="clearfix">

        <div id="content" role="article" class="column">
          <a id="main-content"></a>
          <?php print render($title_prefix); ?>
          <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
          <?php print render($title_suffix); ?>
          <?php print $content; ?>
        </div>
      </div><!-- #main -->

    </div><!-- #page -->
    <?php print $page_bottom; ?>
  </body>
</html>
