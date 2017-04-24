
The RealName module allows the admin to choose fields from the user profile
that will be used to add a "realname" element (method) to a user object.
Hook_user is used to automatically add this to any user object that is loaded.

Installation
------------
Standard module installation applies. See
https://drupal.org/documentation/install/modules-themes/modules-7
for further information.

Menus
-----
The only menu item is for the settings page.

Settings
--------
The settings page is at Configuration >> People >> Real name
(admin/config/people/realname).

This is where you choose which user tokens will be used
to create the user's RealName.

Permissions
-----------
The settings page is controlled by the "Administer Real Name" permission.
