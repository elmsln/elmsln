Introduction
============
node_revision_delete adds the ability to mass delete aging node revisions.

INSTALL/CONFIG
--------------
1. Move this folder into your modules directory like you would any other module.
2. Enable it from Modules >> Node Revision Delete.
3. Global module settings such as when to run it and how many revisions to
   delete per cron run can be found at admin/config/content/node_revision_delete.
4. Open a content type's edit form (for example,
  admin/structure/types/manage/article) and mark the option
  "Limit the amount of revisions for this content type" under
  Publishing options.

DRUSH INTEGRATION
=================

node_revision_delete supports Drush integration. Open the command line and type
the following to get started:

drush nrd --help
