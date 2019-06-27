<!DOCTYPE html>
<html class="no-js" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <title><?php print $head_title; ?></title>
    <meta name="Description" content='<?php print t('Login form for @name in ELMS: Learning Network', array('@name' => $site_name));?>'>
    <!-- tell IE versions to render as high as possible -->
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

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
  </head>
  <body style="background:radial-gradient(circle at center,#43697c 0%,#1f313a 100%);">
  <?php ob_flush(); flush(); ?>
  <img class="elmsln-bg-svg" src="<?php print $theme_path .'/img/logo_ELMSLN-ICON.svg'?>" alt="" />
  <h1 class="course-title"><?php print t('Access %name', array('%name' => $site_name));?></h1>
  <section id="login-page">
    <div class="course-image">
      <?php if (!empty($banner_image)) : ?>
      <?php print $banner_image; ?>
      <?php endif; ?>
    </div>
    <?php print _foundation_access_drop_whitespace($page); ?>
  </body>
  <style>
    html, body {
      height: 100%;
      font-family: "Lato","Helvetica","Tahoma","Geneva","Arial",sans-serif;
      font-size: 1rem;
      line-height: 1.7;
      margin: 0;
      padding: 0;
    }
    .course-image {
      max-width: 36rem;
    }
    .logo__img {
      max-width: 36rem;
    }
    .course-title {
      text-align: center;
      max-width: 34rem;
      margin: 0 auto;
      top: 10%;
      position: relative;
      color: #EEEEEE;
      background-color: rgba(37,58,71,.8);
      border: 1px solid #253a47;
      border-radius: 10px;
      padding: .5em;
      box-shadow: 0 4px 5px 0 rgba(0, 0, 0, 0.14), 0 1px 10px 0 rgba(0, 0, 0, 0.12), 0 2px 4px -1px rgba(0, 0, 0, 0.4);
      z-index: 2;
    }
    #user-login > div {
      color: #ffffff;
      padding: 1rem 3rem 7rem 3rem;
      max-width: 36rem;
    }
    #user-login input {
      width: 100%;
      background: #2a4251;
      color: #d1dee7;
      border: 1px solid #1e2e39;
      margin-bottom: 2rem;
      font-size: 1.4rem;
      line-height: 1.5;
      text-align: center;
      font-weight: 300;
      -webkit-font-smoothing: auto;
    }
    #user-login .description {
      display: none;
    }
    #login-page {
      background: #253a47;
      position: relative;
      top: 38%;
      max-width: 36rem;
      margin: 0 auto;
      -webkit-transform: translateY(-50%);
      -moz-transform: translateY(-50%);
      -o-transform: translateY(-50%);
      -ms-transform: translateY(-50%);
      transform: translateY(-50%);
      box-shadow: 0 4px 5px 0 rgba(0, 0, 0, 0.14), 0 1px 10px 0 rgba(0, 0, 0, 0.12), 0 2px 4px -1px rgba(0, 0, 0, 0.4);
      border: 1px solid black;
      border-radius: 40px;
      overflow: hidden;
    }
    #edit-actions {
      background: #3bab97;
      color: #ffffff;
      text-align: center;
      position: absolute;
      bottom: 0;
      left: 0;
      right: 0;
      max-width: 36rem;
      padding: 1.5rem 3rem;
    }
    #edit-actions button {
      margin: 0;
      color: #ffffff;
      border-radius: 4px;
      background: #216256;
      padding: 0;
      border: none;
      height: 40px;
      font-family: 'Roboto', 'Noto', sans-serif;
    }
    #edit-actions paper-button {
      color: #ffffff;
      border-radius: 4px;
      background: #216256;
      font-size: 20px;
      text-transform: uppercase;
      padding: 0.5rem 1.5rem;
      box-sizing: border-box;
      font-family: 'Roboto', 'Noto', sans-serif;
      box-shadow: 0 4px 5px 0 rgba(0, 0, 0, 0.14), 0 1px 10px 0 rgba(0, 0, 0, 0.12), 0 2px 4px -1px rgba(0, 0, 0, 0.4);
      height: auto;
      border: 0;
      margin: 0;
      -webkit-font-smoothing: auto;
    }
    .elmsln-bg-svg {
      position: fixed;
      opacity: .2;
      z-index: 0;
      height: 225%;
      width: 225%;
      margin: 0;
      top: -62.5%;
      left: -62.5%;
    }
    #toastdrawer {
      padding: 0;
      margin: 0;
      max-width: 400px;
    }
    .paper-toast-label {
      background: #3bab97;
      padding: 1em 2em;
      color: white;
      font-weight: 600;
    }
    .toast-content-container {
      padding: 1em 2em;
    }
    #toastdrawer a {
      color: #3bab97;
    }
    #toastdrawer paper-button {
      margin: 0;
      color: #ffffff;
      border-radius: 4px;
      background: #216256;
      font-weight: 900;
      font-size: 1rem;
      line-height: 1.7;
      padding: 0.5rem 1.5rem;
      box-shadow: 0 4px 5px 0 rgba(0, 0, 0, 0.14), 0 1px 10px 0 rgba(0, 0, 0, 0.12), 0 2px 4px -1px rgba(0, 0, 0, 0.4);
      right: 4px;
      position: absolute;
      top: 4px;
      text-transform: uppercase;
    }
  </style>
  <?php print _foundation_access_drop_whitespace($head); ?>
  <!--/end cross platform favicons and tweaks-->
</html>
