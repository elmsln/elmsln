
= INTRODUCTION =

LABjs is the performance script loader. It loads all your JavaScript in parallel.
Of course, this module is only useful when JavaScript preprocess is
disabled.

Project homepage: http://drupal.org/project/labjs

= INSTALL =

- Enable this module

= COMPATIBILITY =

LABjs, like any other script loader, does not support JavaScript with
document.write() calls at the moment. Don't use those scripts with LABjs, by
adding an "inline" attribute. For example:

// This JS file is required by some inline code that use document.write()
drupal_add_js('/path/to/service.js', array('inline' => TRUE));


This module tries to maintain a maximum compatibility with all JavaScript code.
If you have any problem, please file an issue in the project homepage.
