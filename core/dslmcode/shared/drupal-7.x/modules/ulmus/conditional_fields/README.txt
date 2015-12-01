
Conditional Fields:
--------------------
A Drupal module


Author:
--------------------
Gregorio Magini (peterpoe) <gmagini@gmail.com> - http://www.twitter.com/peterpoe


Short Description:
--------------------
Define dependencies between fields based on their states and values. Conditional Fields for Drupal 7 is basically an user interface for the States API, plus the ability to hide fields on certain conditions when viewing content.


Description:
--------------------
The Conditional Fields module allows you to manage sets of dependencies between fields. When a field is "dependent", it will only be available for editing and displayed if the state of the "dependee" field matches the right condition.
When editing a node (or any other entity type that supports fields, like users and categories), the dependent fields are dynamically modified with the States API.
You can, for example, define a custom “Article teaser" field that is shown only if a "Has teaser" checkbox is checked.


Dependencies:
--------------------
- Drupal core: version 7.14 or higher.


Installation:
--------------------
- Install as usual, see http://drupal.org/documentation/install/modules-themes/modules-7 for further information.


Usage:
--------------------
Users with the "administer dependencies" permission can administer dependencies at admin/structure/dependencies.

For more information, read the Conditional Fields documentation:
http://drupal.org/node/1704126


Upgrading from Drupal 6 to Drupal 7
--------------------
Read carefully these instructions since taking the wrong steps could lead to loss of dependencies data!

- Before upgrading, ensure that you have the latest stable version of Conditional Fields for Drupal 6 installed and working.
- Follow the instructions on the D6 to D7 upgrade process here: http://drupal.org/node/570162.
- Most importantly, you have to migrate your old CCK fields to the new format BEFORE updating Conditional Fields, so do not omit step 14: "Upgrade fields"! Failing to do so will give an error when trying to run the subsequent update on step 15: "Update contrib modules and themes" and could lead to loss of dependencies data.
- After step 14, leave the Content Migrate module activated. You can safely disable it after step 15.
- Note that Content Migrate in certain cases changes the allowed values of fields: you will have to manually edit the dependencies to match the new allowed values if this happens.


Limitations:
--------------------
- Conditional Fields, for now, supports only core fields and widgets as dependee fields. Fields from other modules might work, but probably won't. Dependent fields, though, can be of any type.


Any help is welcome!
--------------------
Check the issue queue of this module for more information:
http://drupal.org/project/issues/conditional_fields
