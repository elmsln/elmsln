Superfish module

About
-----
This module allows for integration of jQuery Superfish plug-in with Drupal CMS.


Requirement
-----------
- Superfish library.
  Link: http://drupal.org/project/superfish


Installation instructions
-------------------------
1. Download and extract the Superfish library into the libraries directory (usually
   "sites/all/libraries").
   Link: https://github.com/mehrpadin/Superfish-for-Drupal/zipball/master

2. Download and extract the Superfish module into the modules directory (usually
   "sites/all/modules").
   Link: http://drupal.org/project/superfish
   Drush users can use the command "drush superfish-plugin".

3. Go to "Administer" -> "Modules" and enable the module.

Note: Though no longer required, using Libraries API is still recommended.
      Link: http://drupal.org/project/libraries


Upgrade instructions
--------------------
Did you change any part of the module or the library?

- If you did not change the module or the library; download the latest versions of the module and
  the library and upload them (replacing the old files).

- If you did change the module or the library; use a visual comparison tool (such as Winmerge 
  or Kompare, so on) in order to compare your current copy with its original one (you can find it at
  http://drupal.org/node/711944/release) find out what was changed and do the same to the version
  you are upgrading to.
  WARNING: This is for experts only!
  
- Please note that if you are upgrading from version 1.6 running update.php will cause error
  messages to appear. To resolve this go to "Administer" -> "Structure" -> "Blocks", click the
  "Configure" link for each Superfish block and click "Save block" button.
  

Configuring the module
----------------------
- For block-specific settings go to "Administer" -> "Structure" -> "Blocks" and click the
  "Configure" link of the Superfish block.

- For module settings go to "Administer" -> "Configuration" -> "User Interface" -> "Superfish".

- Detailed configuration instructions can be found at http://drupal.org/node/1125896


How to style
------------
If you know CSS, even basics of it, designing won't be a big challenge.

Here are some tips and tricks:

A) Always use a DOM inspector utility (such as Firebug).

B) Set the "Menu delay" option to a very high number such as 99999999. This will give you enough
   time to work with sub-menus.

C) If you are not using the built-in styles, set the "Style" option to "None".

D) Utilise the "Simple" style as reference; add the newly-created CSS file either to your theme CSS
   or as a new CSS file under the styles directory in the Superfish library (probably
   "sites/all/libraries/superfish/style"); putting it in the styles folder will automatically add it
   to the styles list in the block configuration.
   
- More information can be found in the Superfish documentation at http://drupal.org/node/1125896


Support requests
----------------
You can request support here: http://drupal.org/project/issues/superfish


How to help?
------------
Glad you asked that :)

- Help find bugs!
- Suggest new features!
- Test the beta versions!
- Translate the UI into your language!