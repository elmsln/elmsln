
-- SUMMARY --

The Coffee module helps you to navigate through the Drupal admin faster,
inspired by Alfred and Spotlight (OS X). By default the management menu is
included in the results. Go to the config page to select an other of multiple
menus. 

For a full description of the module, visit the project page:
  http://drupal.org/project/coffee

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/1356930


-- REQUIREMENTS --

Menu module (core).


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70501 for further information.


-- CONFIGURATION --

* Configure user permissions in admin/people/permissions

  - access coffee

    Users in Roles with the "access coffee" permission can make use of the
    Coffee module.

* Configure which menus are included in the coffee results here:
  - admin/config/user-interface/coffee


-- USAGE --

Toggle Coffee using the keyboard shortcut alt + D
(alt + shift + D in Opera, alt + ctrl + D in Windows Internet Explorer).

Type the first few characters of the task that you want to perform. Coffee
will try to find the right result in as less characters as possible.
For example, if you want to go the the Appearance admin page, type ap and
just hit enter.

If your search query returns multiple results, you can use the arrow up/down
keys to choose the one you were looking for.

This will work for all Drupal admin pages.

If the Devel module is installed it will also look for items that Devel 
generates. For example; type 'clear' to get devel/cache/clear as result. 

-- UPGRADE PATH -- 

If you had Coffee 1.x installed, make sure to run update.php as it will install
a cache table for the prefetching the Coffee results. 

If you have implemented the hook hook_coffee_command() make sure to rewrite it 
to the newly hook_coffee_commands(), see coffee.api.php for an example. 

-- COFFEE COMMANDS --

Coffee provides default commands that you can use.

:add
Rapidly add a node of a specific content type.

-- COFFEE HOOKS --

You can define your own commands in your module with hook_coffee_commands(),
see coffee.api.php for further documentation.


-- CONTRIBUTORS --

Maintainer
- Michael Mol 'michaelmol' <http://drupal.org/user/919186>

Co-maintainer
- Alli Price 'heylookalive' <http://drupal.org/user/431193>

JavaScript/CSS/Less
- Maarten Verbaarschot 'maartenverbaarschot' <http://drupal.org/user/1305466>
