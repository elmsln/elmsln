
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Implementation
 * Drush


INTRODUCTION
------------

Current Maintainer: Travis Carden <http://drupal.org/user/236758>

Checklist API provides a simple interface for modules to create fillable,
persistent checklists that track progress with completion times and users. See
checklistapi_example.module for an example implementation.


INSTALLATION
------------

Checklist API is installed in the usual way. See
http://drupal.org/documentation/install/modules-themes/modules-7.


IMPLEMENTATION
--------------

Checklists are declared as multidimensional arrays using
hook_checklistapi_checklist_info(). They can be altered using
hook_checklistapi_checklist_info_alter(). Checklist API handles creation of menu
items and permissions. Progress details are saved in one Drupal variable per
checklist. (Note: it is the responsibility of implementing modules to remove
their own variables on hook_uninstall().)

See checklistapi.api.php for more details.


DRUSH
-----

Checklist API provides Drush commands. They require Drush 6 or later. To see the
list of available commands, run `drush --filter=checklistapi`. For more about
Drush, including installation instructions, visit
https://github.com/drush-ops/drush.
