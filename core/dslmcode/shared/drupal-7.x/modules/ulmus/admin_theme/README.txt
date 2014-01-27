/* $Id: README.txt,v 1.1.2.2.2.1 2008/12/13 09:22:36 davyvandenbremt Exp $ */

Description
-----------

Drupal allows you to define a different theme for administration pages (Administer -> Site configuration -> Administration theme). By default this only applies to pages with a path starting with 'admin' and content editing pages.

The Administration theme module adds a few more option to the default configuration page like :
- Use administration theme for batch processing
- Use administration theme for code reviews
- ...

Some of these pages will only appear if they apply to your installation, i.e. you have the module installed which generates these pages.

You also have the option to define a custom set of Drupal paths or aliases to apply the administration theme for.


Requirements
------------

This module requires Drupal 7. A Drupal 5 and 6 version are available.


Installation
------------

1) Copy/upload the admin_theme module folder to the sites/all/modules
directory of your Drupal installation. 

2) Enable the Administration theme module in Drupal (administer -> modules).


Configuration
-------------

You can enable/disable the administration theme on the administration theme
configuration page.

Administration theme can be configured at : 
  Administer -> Site configuration -> Administration theme
  
Developers
----------
You can add define extra pages where the administration theme should be applied to by implementing the hook_admin_theme_info and hook_admin_theme_check hooks in your modules.
The first one gets all "options" and the second one checks if each of those options should should be applied to a path. Check out admin_theme_admin_theme_info and admin-theme_admin_theme_check for an example implementation.


Author
------

Davy Van Den Bremt <info@davyvandenbremt.be>
http://www.davyvandenbremt.be