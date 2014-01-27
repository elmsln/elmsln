<?php
  global $language;
  $language->dir = $language->direction ? 'rtl' : 'ltr';
  $rdf_namespaces = drupal_get_rdf_namespaces();
  $grddl_profile = 'http://www.w3.org/1999/xhtml/vocab';
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>
<head profile="<?php print $grddl_profile; ?>">
  <title><?php print $title; ?></title>
  <?php print drupal_get_js(); ?>
  <?php print drupal_get_css(); ?>
</head>
<body class="shadowbox_login">
<?php print theme('status_messages'); ?>
<?php print $content; ?>
</body>
</html>
