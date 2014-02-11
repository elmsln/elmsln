
Drupal equalheights.module README.txt
==============================================================================

This module implements a jQuery plugin that can equalize the height of the
user specified elements with the same class.
By default, the height of the tallest element is used, but minimum and
maximum height can also be set.
To find out more about the plugin, go to
http://www.cssnewbie.com/equalheights-jquery-plugin/

Installation
------------
Starting with 7.x-2.x, equalheights module requires Libraries API 2.x. and imagesloaded plugin. If you have drush installed
on your machine, it's going to download required libraries. Otherwise, procede with the manual installation.

Installing required libraries manually.
-------------------------------------
Before installing equalheights module, download imagesloaded plugin from https://github.com/desandro/imagesloaded/releases/tag/v2.1.2.
You need two files: jquery.imagesloaded.js and jquery.imagesloaded.min.js. They should be copied to sites/all/libraries/imagesloaded.
You can also use git to clone the repository from the github.

Copy the module to the directory where you store contributed modules and enable
it on the admin modules page. Go to admin/config/development/equalheights and
add the classes for the elements that should have the same height (optionally,
add minimum and maximum height as well as overflow).

Author of the jQuery plugin
--------------------
Rob Glazebrook
http://www.cssnewbie.com/equalheights-jquery-plugin/

Author of the module
--------------------
Drupal librarian
transgarret@gmail.com