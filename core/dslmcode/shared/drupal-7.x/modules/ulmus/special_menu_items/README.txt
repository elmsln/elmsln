Special Menu Items Module
------------------------
Written by Tamir Al Zoubi and Karim Djelid - Servit Open Source Solutions - www.servit.ch


Description
-----------
Special Menu Items is module that enables placeholder and separator menu items.Placeholder is a menu item which is
actually not a link. Something like this is useful with drop down menus where we want to have a parent link which
is actually not linking to a page but which is just acting as a parent grouping some children below it.
A separator menu item is something like "-------" which is also not linking anywhere but merely a mean to structure menus.

This module depends on the Menu module. It is recommended that the SimpleMenu module or another drop down menu module
is used, or you will not be able to acess children of nolink menu items.

Features
--------
  - User can create a new menu item and place either "<nolink>" or "<separator>" in the Path field, without quotes.
  - When the menu is rendered the "nolink" item will be rendered similar to a normal menu link item, but there will
    be no link, just the title. Since version 1.3 you can change HTML tag used for menu item.
  - When the menu is rendered the "separator" item will be rendered as an item which has no link,
    and the default title will be "-------". Since version 1.3 it is possible to change both the HTML tag and title.
  - Breadcrumb of "<nolink>" will be rendered same as "<nolink>" menu item.
  - CSS class "nolink" is added to "<nolink>" menu item.
  - CSS class "seperator" is added to "<seperator>" menu item.
  - Compatible with the Sitemap module.

Installation
------------
1. Copy the special_menu_items folder to your sites/all/modules directory.
2. At Administer -> Site building -> Modules (admin/modules) enable the module.
3. Configure the module settings at Administer -> Site configuration -> Special Menu Items (admin/config/system/special_menu_items).

Upgrading
---------
Just overwrite (or replace) the older special_menu_items folder with the newer version.

Contact
-------
This module is developed by Servit Open Source Solutions - http://servit.ch
and maintained by Khaled Zaidan - zaidan@servit.ch
