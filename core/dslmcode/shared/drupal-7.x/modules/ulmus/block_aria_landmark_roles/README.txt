ABOUT THIS MOUDLE
-----------------

Inspired by Block Class, this module adds additional elements to the block
configuration forms that allow users to assign blocks ARIA landmark roles.

WHAT ARE ARIA LANDMARK ROLES?
-----------------------------

The WAI ARIA specification defines a set of specialised “landmark” roles. These 
roles provide a method to programmatically identify commonly found sections of 
web page content in a consistent way. they can be used now in whatever flavour 
of (X)HTML you prefer. This allows assistive technologies to provide users with 
features which they can use to identify and navigate to sections of page content.

For further information, go to http://www.w3.org/WAI/PF/aria or 
http://www.nomensa.com/blog/2010/wai-aria-document-landmark-roles.

INSTALLATION
------------

See http://drupal.org/documentation/install/modules-themes/modules-7.

USAGE
-----

Ensure that the attributes variable is being printed within your block.tpl.php
file - the block module's default template does this by default. For example:

<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

AUTHOR
------

Oliver Davies
http://drupal.org/user/381388
