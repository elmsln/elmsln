= Masquerade =

The Masquerade module allows users to temporarily switch to another user
account. It keeps a record of the original user account, so users can easily
switch back to the previous account.

== Installation and Configuration ==

To install the Masquerade module, extract the module to your modules folder,
such as sites/all/modules. After enabling the module, it can be configured
under Administer > Configuration > People > Masquerade. To enable users to
masquerade, assign the appropriate "masquerade module" permissions to the roles
available on your site. For example:

 * To allow members of the 'customer support' role to masquerade as any
   non-admin user, add the 'masquerade as user' permission to the role. In the
   Masquerade configuration, set 'administrator' as an administrator role
   to prevent customer support users from masquerading as those users.

 * To allow members of the 'tech support' role to masquerade as 'administrator', add the 'masquerade as admin' permission to the role. Then,
   in the Masquerade configuration, set 'administrator' as an
   administrator role.

== Quick Switch Menu ==

By default, when a user is selected for the 'Menu Quick Switch user', the Masquerade module adds two menu items to the 'Navigation' menu:

 * Masquerade as 'the user selected': When clicked, the user can quick switch to the user selected.

 * Switch back: This menu item appears while masquerading so that you can switch back to your original user.

== Help and Support ==

This module was developed by a number of contributors. For more information
about this module, see:

Project Page: http://drupal.org/project/masquerade
Issue Queue: http://drupal.org/project/issues/masquerade
