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
<html class="no-js" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <!--<![endif]-->
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <!-- tell IE versions to render as high as possible -->
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <!--cross platform favicons and tweaks-->
  <link rel="shortcut icon" href="<?php print $favicon_path;?>">
  <link rel="icon" sizes="16x16 32x32 64x64" href="<?php print $theme_path . '/legacy/icons/elmsicons';?>/elmsln.ico">
<?php foreach ($iconsizes as $iconsize) : ?>
  <link rel="icon" type="image/png" sizes="<?php print $iconsize; ?>x<?php print $iconsize; ?>" href="<?php print $theme_path . '/legacy/icons/elmsicons';?>/elmsln-<?php print $iconsize; ?>.png">
<?php endforeach; ?>
  <!-- iOS Safari -->
  <meta name="apple-mobile-web-app-capable" content="yes">
  <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
  <link rel="apple-touch-icon" href="<?php print $theme_path . '/legacy/icons/elmsicons';?>/elmsln-57.png">
<?php foreach ($appleiconsizes as $appleiconsize) : ?>
  <link rel="apple-touch-icon" sizes="<?php print $appleiconsize; ?>x<?php print $appleiconsize; ?>" href="<?php print $theme_path . '/legacy/icons/elmsicons';?>/elmsln-<?php print $appleiconsize; ?>.png">
<?php endforeach; ?>
  <link rel="apple-touch-icon-precomposed" href="<?php print $theme_path . '/legacy/icons/elmsicons';?>/elmsln-152.png">
  <link rel="apple-touch-startup-image"  href="<?php print $theme_path . '/legacy/icons/elmsicons';?>/elmsln-320x480.png">
  <!-- Windows Phone -->
  <meta name="msapplication-TileImage" content="<?php print $theme_path . '/legacy/icons/elmsicons';?>/elmsln-144.png">
  <meta name="msapplication-config" content="<?php print $theme_path . '/legacy/icons/elmsicons';?>/browserconfig.xml">
  <meta name="msapplication-tap-highlight" content="no">
  <!-- Chrome, Firefox OS and Opera -->
  <meta name="msapplication-navbutton-color" content="#eeeeee">
  <meta name="msapplication-TileColor" content="#eeeeee">
  <meta name="theme-color" content="#eeeeee">
  <!--/end cross platform favicons and tweaks-->
  <?php print preg_replace('~>\s+<~', '><', $styles); ?>
  <?php print preg_replace('~>\s+<~', '><', $scripts); ?>
</head>
<body class="<?php print $classes; ?> <?php print $lmsless_classes['color'];?>-selection" <?php print $attributes;?>>
<h1 class="element-invisible"><?php print $head_title;?></h1>
<?php ob_flush(); flush(); ?>
  <span class="cis-lmsless-color"></span>
  <div class="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php if (!empty($banner_image)) : ?>
  <div class="header-image-container">
    <?php print $banner_image; ?>
  </div>
  <?php endif; ?>
    <div class="elmsln-system-badge">
      <div class="elmsln-icon icon-<?php print $system_icon . ' ' . $lmsless_classes['text'];?> elmsln-badge"></div>
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
  <?php print preg_replace('~>\s+<~', '><', $page_top . $page . $page_bottom); ?>
  </body>
</html>
