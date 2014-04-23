ELMS: Outline Designer API - Usability improvements for outlining

REQUIREMENTS
*This module requires nothing, by itself it is an API

OPTIONAL (need to use to make sense)
* Book integration (this gives you the original outline designer 1.x branch)
* Outline Child Pages will give a contextual outline designer under the outline tab
on a node
* There is keyboard based jwerty integration by downloading the project from
http://keithcirkel.co.uk/jwerty/ and moving the contents to
sites/all/libraries/jwerty .  This package also has book_copy and hidden_nodes support

INSTALLATION
*Place the outline_designer directory in the correct modules folder as you would any other Drupal module
*Activate the module
*Activate the sub-modules (outline_designer_book is highly recommended)
*Go to admin/config/content/outline_designer and configure global settings
If you activate outline_designer_book:
*Go to admin/content/book/settings to enable / disable content types from outlining and set default type
*Go to admin/content/book/outline_designer to enable / disable content types from outlining and set default type
*Go to admin/content/book and click "edit order and titles" to access the outline designer interface.

OPTIONAL INSTALLATION
*There is an organic groups integration helper module.  Activating it will add a "edit Books" tab to the group home page for group admins.  Group admins can now edit books owned by their group without needing the administer book privilege

KEYBOARD SHORTCUTS
Check out the JWERTY.txt file for directions on how to use jwerty

PERMISSIONS
The outline designer is fully compatible with the permissions designated by your Drupal site. To access outline designer:

By itself -- Requires 'use outline designer'
w/ outline_designer_book -- requires admin book outlines
w/ outline_designer_og -- requires admin book outlines OR that you are a group admin
w/ just outline_child_pages -- requires admin book outline OR that you are a group admin OR that you have the following three permissions combined:
** 'outline own pages' permission
** 'add content to books' permission
** have access to update / edit the node you are currently viewing
(If you meet the three criteria you will be allowed to use the outline designer though it will still check for permissions on each action as it always does)

w/ outline_child_pages and book_manager -- requires 'add content to personal books' permission

COMPATIBILITY
No known issues
*Firefox 2+
*Safari 4+
*Chrome
*Opera 10
*IE 7/8
