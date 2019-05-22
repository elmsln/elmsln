<!DOCTYPE html>
<html class="no-js" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <title><?php print $head_title; ?></title>
    <?php print _foundation_access_drop_whitespace($head); ?>
    <?php print _foundation_access_drop_whitespace($styles); ?>
    <?php print _foundation_access_drop_whitespace($scripts); ?>
    <!-- tell IE versions to render as high as possible -->
    <meta http-equiv="X-UA-Compatible" content="IE=EDGE" />
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!--cross platform favicons and tweaks-->
    <link rel="shortcut icon" href="<?php print $favicon_path;?>">
    <?php if ($theme_path . '/icons/elmsicons/elmsln.ico' == $favicon_path) : ?>
    <link rel="icon" sizes="16x16 32x32 64x64" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln.ico">
    <?php foreach ($iconsizes as $iconsize) : ?>
    <link rel="icon" type="image/png" sizes="<?php print $iconsize; ?>x<?php print $iconsize; ?>" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-<?php print $iconsize; ?>.png">
    <?php endforeach; ?>
    <!-- iOS Safari -->
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
    <link rel="apple-touch-icon" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-57.png">
    <?php foreach ($appleiconsizes as $appleiconsize) : ?>
    <link rel="apple-touch-icon" sizes="<?php print $appleiconsize; ?>x<?php print $appleiconsize; ?>" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-<?php print $appleiconsize; ?>.png">
    <?php endforeach; ?>
    <link rel="apple-touch-icon-precomposed" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-152.png">
    <link rel="apple-touch-startup-image"  href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-320x480.png">
    <!-- Windows Phone -->
    <meta name="msapplication-TileImage" content="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-144.png">
    <meta name="msapplication-config" content="<?php print $theme_path . '/icons/elmsicons';?>/browserconfig.xml">
    <?php endif; ?>
    <meta name="msapplication-tap-highlight" content="no">
    <!-- Chrome, Firefox OS and Opera -->
    <meta name="msapplication-navbutton-color" content="#eeeeee">
    <meta name="msapplication-TileColor" content="#eeeeee">
    <meta name="theme-color" content="#eeeeee">
    <!--/end cross platform favicons and tweaks-->
  </head>
  <body class="<?php print $classes; ?> <?php print $lmsless_classes['color'];?>-selection" <?php print $attributes;?> prefix="oer: http://oerschema.org/">
  <h1 class="element-invisible"><?php print $head_title;?></h1>
  <?php ob_flush(); flush(); ?>
  <div class="skip-link">
    <a href="#main-content" class="element-invisible element-focusable black-text"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php if (!empty($banner_image)) : ?>
    <div class="header-image-container"><?php print $banner_image; ?></div>
  <?php endif; ?>
  <?php print _foundation_access_drop_whitespace($page_top . $page . $page_bottom); ?>
  </body>
</html>
