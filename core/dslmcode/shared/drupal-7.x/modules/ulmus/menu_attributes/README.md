# Menu Attributes


## Introduction

This simple module allows you to specify some additional attributes for menu
items such as id, name, class, style, and rel.

You should use this module when:

* You want to "nofollow" certain menu items to sculpt the flow of PageRank
  through your site.
* You want to give a menu item an ID so you can easily select
  it using jQuery.
* You want to add additional classes or styles to a menu item.

The module currently allows you to set the following attributes for each menu
item or menu link:

* id
* name
* target
* rel
* class
* style
* accesskey

For further information please visit the following:

* For a full description of the module, visit the project page:
  [https://drupal.org/project/menu_attributes](https://drupal.org/project/menu_attributes)
* To submit bug reports and feature suggestions, or to track changes:
  [https://drupal.org/project/issues/menu_attributes](https://drupal.org/project/issues/menu_attributes)

## Installation

1. To install the module copy the 'menu_attributes' folder to your
   *sites/all/modules* directory.
2. Go to admin/modules. Filter for ‘Menu Attributes’ and enable the module. Read
   more about installing modules at [http://drupal.org/node/70151](http://drupal.org/node/70151)

## Configuration

1. Go to *admin/people/permissions*. Filter for the ‘Menu Attributes’ section.
   Set appropriate permissions.
2. Go to *admin/structure/menu/settings*. Review instructions on this screen.
3. Go to *admin/build/menu*
4. Select the menu links you want to edit (In this example we will edit the menu
   'Navigation’).
5. Under operations for that menu, click ‘list links’.
6. Click on any 'edit' link under the 'Operations' column.
7. Scroll down the page to find the 'Menu link attributes' and 'Menu item
   attributes' sections. Expand either section by clicking on it.

    a. **Menu link attributes** are added to the `<a>` link element. Follow
       instructions on screen.

    b. **Menu item attributes** are added to the `<li>` list element for that
       link. Follow instructions on screen.

10. Click the 'Save' button.

Another way of setting menu attributes is to edit any page, scroll to 'Menu
settings' and click the checkbox for ‘Provide a menu link’. This will reveal the
options for this menu item, including ’Menu link attributes' and 'Menu item
attributes'. Follow instructions on screen.


## Troubleshooting

1. Go to the module issue queue at
   [http://drupal.org/project/issues/menu_attributes?status=All&categories=All](http://drupal.org/project/issues/menu_attributes?status=All&categories=All)
2. Check if your particular issue exists.  If not, click on the CREATE A NEW
   ISSUE link.
3. Fill the form.
4. To get a status report on your request go to
   [http://drupal.org/project/issues/user](http://drupal.org/project/issues/user)


## Updating

Read more at [http://drupal.org/node/250790](http://drupal.org/node/250790)
