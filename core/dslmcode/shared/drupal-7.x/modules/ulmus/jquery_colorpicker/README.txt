The Drupal 7 branch of Jquery Colorpicker offers a form element than can be
included in any form in this way:

<?php
$form['element'] = array(
  '#type' => 'jquery_colorpicker',
  '#title' => t('Color'),
  '#default_value' => 'FFFFFF',
);
?>

This module includes Field API integration. A colorpicker field can be added to
any content type with the JQuery Colorpicker widget

==================
Installation guide
=================
 1.- Install http://drupal.org/project/libraries
 2.- Install the module as you would any other Drupal module
 3.- Go to www.eyecon.ro/colorpicker/ and download colorpicker.zip.
 4.- Extract the the zip file content to the colorpicker folder in your
     libraries folder.
 5.- If you have extracted the contents right, the following filepath should
     exist: [path to libraries folder]/colorpicker/js/colorpicker.js
 6.- Enjoy your colors!!
