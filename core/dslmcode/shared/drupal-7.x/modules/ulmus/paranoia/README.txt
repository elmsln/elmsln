Description:
===========
Paranoia module is for all the sysadmins out there who think that
allowing random CMS admins to execute PHP of their choice is not
a safe idea.

What it does:
=============
- Disable the PHP module.
- Disable granting of the "use PHP for block visibility" permission.
  Save the permissions form once to remove all previous grants.
  (An error appears in the site status report if a role still has this
  permission.)
- Disable granting to Anonymous or Authenticated any permission that is
  marked "restrict access" in a module's hook_permission.
- Disable granting several permissions from popular contribs that are not
  marked as "restrict access" but are still important.
- Remove the PHP and paranoia modules from the module admin page.
- Provides a hook to let you remove other modules from the module admin page.

NOTE on disabling:
=====
The only way to disable paranoia module is by changing its status in the
database system table.  By design it does not show up in the module
administration page after it is enabled. You can also disable it with drush:

drush dis paranoia

Support
=======
View current issues:
http://drupal.org/project/issues/paranoia
Submit a new issue:
http://drupal.org/node/add/project-issue/paranoia

Development
===========
All development happens in branches like 7.x-1.x and 6.x-1.x

Maintainers
======
Gerhard Killesreiter
Greg Knaddison @greggles
