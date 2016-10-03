<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 * - $theme_path: absolute path to the theme
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */
?>
<!DOCTYPE html>
<!-- Sorry no IE7 support! -->

<!--[if IE 8]><html class="no-js lt-ie9" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if gt IE 8]><!-->
<html class="no-js" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <!--<![endif]-->
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <!--[if lt IE 9]>
    <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->
  <!--cross platform favicons and tweaks-->
  <link rel="shortcut icon" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln.ico">
  <link rel="icon" sizes="16x16 32x32 64x64" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln.ico">
  <link rel="icon" type="image/png" sizes="310x310" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-310.png">
  <link rel="icon" type="image/png" sizes="196x196" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-192.png">
  <link rel="icon" type="image/png" sizes="160x160" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-160.png">
  <link rel="icon" type="image/png" sizes="96x96" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-96.png">
  <link rel="icon" type="image/png" sizes="64x64" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-64.png">
  <link rel="icon" type="image/png" sizes="32x32" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-32.png">
  <link rel="icon" type="image/png" sizes="16x16" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-16.png">
  <!-- iOS Safari -->
  <meta name="apple-mobile-web-app-capable" content="yes">
  <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
  <link rel="apple-touch-icon" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-57.png">
  <link rel="apple-touch-icon" sizes="114x114" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-114.png">
  <link rel="apple-touch-icon" sizes="72x72" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-72.png">
  <link rel="apple-touch-icon" sizes="144x144" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-144.png">
  <link rel="apple-touch-icon" sizes="60x60" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-60.png">
  <link rel="apple-touch-icon" sizes="120x120" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-120.png">
  <link rel="apple-touch-icon" sizes="76x76" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-76.png">
  <link rel="apple-touch-icon" sizes="152x152" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-152.png">
  <link rel="apple-touch-icon" sizes="180x180" href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-180.png">
  <link rel="apple-touch-startup-image"  href="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-320x480.png">
  <!-- Windows Phone -->
  <meta name="msapplication-navbutton-color" content="#eeeeee">
  <meta name="msapplication-TileColor" content="#eeeeee">
  <meta name="msapplication-TileImage" content="<?php print $theme_path . '/icons/elmsicons';?>/elmsln-144.png">
  <meta name="msapplication-config" content="<?php print $theme_path . '/icons/elmsicons';?>/browserconfig.xml">
  <!-- Chrome, Firefox OS and Opera -->
  <meta name="theme-color" content="#eeeeee">
  <!--/end cross platform favicons and tweaks-->
</head>
<body class="<?php print $classes; ?> <?php print $lmsless_classes['color'];?>-selection" <?php print $attributes;?>>
  <div class="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php if (!empty($logo_img)) : ?>
    <div class="header-image-container">
      <?php print $logo_img; ?>
    </div>
  <?php endif; ?>
    <div class="elmsln-system-badge">
      <div class="icon-<?php print $system_icon;?>-black elmsln-badge"></div>
      <div class="elmsln-badge-inner">
        <div class="elmsln-badge-top white-border"></div>
        <div class="elmsln-badge-middle white"></div>
        <div class="elmsln-badge-bottom white-border"></div>
      </div>
      <div class="elmsln-badge-outer">
        <div class="elmsln-badge-top <?php print $lmsless_classes['color'];?>-border"></div>
        <div class="elmsln-badge-middle <?php print $lmsless_classes['color'];?>"></div>
        <div class="elmsln-badge-bottom <?php print $lmsless_classes['color'];?>-border"></div>
      </div>
      <div class="elmsln-badge-middle-name white <?php print $lmsless_classes['color'];?>-border">
        <a href="<?php print base_path();?>" class="<?php print $lmsless_classes['text'];?> <?php print $lmsless_classes['color'];?>-outline">
          <span class="element-invisible"><?php print t('Home');?></span>
          <?php print $system_title;?>
        </a>
      </div>
    </div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
  </body>
</html>
