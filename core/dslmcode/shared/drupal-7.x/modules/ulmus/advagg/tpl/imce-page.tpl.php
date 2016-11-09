<?php

/**
 * @file
 * Override imce-page.tpl.php, fixing css/js aggregation issues.
 */

if (isset($_GET['app'])) {
  drupal_add_js(drupal_get_path('module', 'imce') . '/js/imce_set_app.js');
}
$title = t('File Browser');
$full_css = advagg_get_css();
$rendered_css = drupal_render($full_css);
$scripts_header_array = advagg_get_js('header');
$rendered_scripts_header = drupal_render($scripts_header_array);
$scripts_footer_array = advagg_get_js('footer');
$rendered_scripts_footer = drupal_render($scripts_footer_array);
$html_head = drupal_get_html_head();
$status_messages = theme('status_messages');

print <<<HTML
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="{$GLOBALS['language']->language}" xml:lang="{$GLOBALS['language']->language}" class="imce">

<head>
  <title>{$title}</title>
  <meta name="robots" content="noindex,nofollow" />
  {$html_head}
  {$rendered_css}
  {$rendered_scripts_header}
  <style media="all" type="text/css">/*Quick-override*/</style>
</head>

<body class="imce">
<div id="imce-messages">{$status_messages}</div>
{$content}
{$rendered_scripts_footer}
</body>
</html>
HTML;
