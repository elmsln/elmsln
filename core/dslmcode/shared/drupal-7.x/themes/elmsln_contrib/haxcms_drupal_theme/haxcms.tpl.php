<?php
/**
 * @file
 * Default theme implementation for HAXcms
 *
 * Available variables:
 * - $siteAttributes: array of options
 * - $node: site object we are rendering out to call
 * - $language: Language code. e.g. "en" for english.
 * - $language_rtl: TRUE or FALSE depending on right to left language scripts.
 * - $base_url: URL to home page.
 * - $contents: rendered node
 *   haxcms.tpl.php.
 *
 * @see template_preprocess_entity_iframe()
 *
 * @ingroup themeable
 */
?>
<div id="loading">
  <div class="messaging">
    <img src="<?php print $logo;?>" alt="" loading="lazy" height="300px" width="300px" />
    <div class="progress-line"></div>
    <h1>Loading <?php print $node->title; ?>..</h1>
  </div>
</div>
<haxcms-site-builder id="site"<?php print drupal_attributes($siteAttributes);?>>
  <?php print $contents; ?>
</haxcms-site-builder>
<div id="haxcmsoutdatedfallback">
  <div id="haxcmsoutdatedfallbacksuperold"> 
    <div style="float:left;padding:16px 0;font-size:32px;text-align: center;width:100%;">Please use a modern browser to
      view our website correctly. <a href="http://outdatedbrowser.com/">Update my browser now</a></div>
  </div>
</div>
