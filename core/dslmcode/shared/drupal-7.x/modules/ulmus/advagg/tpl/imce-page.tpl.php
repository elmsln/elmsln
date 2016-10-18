<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $GLOBALS['language']->language; ?>" xml:lang="<?php print $GLOBALS['language']->language; ?>" class="imce">

<head>
  <title><?php print t('File Browser'); ?></title>
  <meta name="robots" content="noindex,nofollow" />
  <?php if (isset($_GET['app'])): drupal_add_js(drupal_get_path('module', 'imce') .'/js/imce_set_app.js'); endif;?>
  <?php print drupal_get_html_head(); ?>
  <?php $full_css = advagg_get_css(); print drupal_render($full_css); ?>
  <?php $scripts_header_array = advagg_get_js('header'); print drupal_render($scripts_header_array);  ?>
  <style media="all" type="text/css">/*Quick-override*/</style>
</head>

<body class="imce">
<div id="imce-messages"><?php print theme('status_messages'); ?></div>
<?php print $content; ?>
<?php $scripts_footer_array = advagg_get_js('footer'); print drupal_render($scripts_footer_array); ?>
</body>

</html>
