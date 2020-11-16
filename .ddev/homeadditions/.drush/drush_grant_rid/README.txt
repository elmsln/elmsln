Drush Grant by RID

This is a drush plugin that will grant a user a role based on the role id being passed in.

When to use this then?
If you have spaces in the names of your roles (or don't know the role name in a script but do know the RID) then this plugin might be for you. This is especially useful for those using https://www.drupal.org/project/role_export to maintain consistent rids across sites / distributions. You then would know the rid in advance and can write scripts to grant off that rather then the drush core method which is by role name. This can cause problems if your role is something like "past student" as character encapsulation will sometimes pass this to drush improperly.

Usage

drush ugrid 6 btopro

This will grant 