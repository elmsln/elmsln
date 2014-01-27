Jammer
http://drupal.org/project/jammer
================


DESCRIPTION
------------
Hide or remove items from displaying including the node and comment preview
buttons, node and user delete buttons, revision log textarea, node "split 
summary" function, and feed icon.


REQUIREMENTS
------------
Drupal 7.x


INSTALLING
------------
1. Copy the 'jammer' folder to your sites/all/modules directory.
2. Go to Administer > Site building > Modules. Enable the module.


CONFIGURING AND USING
---------------------
1. Go to Administer > User management > Permissions. Under line 'jammer module'
   configure appropriate permissions.
2. Go to Administer > Site configuration > Jammer
   Set appropriate options.


REPORTING ISSUE. REQUESTING SUPPORT. REQUESTING NEW FEATURE
-----------------------------------------------------------
1. Go to the module issue queue at
   http://drupal.org/project/issues/jammer?status=All&categories=All
2. Click on CREATE A NEW ISSUE link.
3. Fill the form.
4. To get a status report on your request go to
   http://drupal.org/project/issues/user


UPGRADING
---------
1. One of the most IMPORTANT things to do BEFORE you upgrade, is to backup your
   site's files and database. More info: http://drupal.org/node/22281
2. Disable actual module. To do so go to Administer > Site building > Modules.
   Disable the module.
3. Just overwrite (or replace) the older module folder with the newer version.
4. Enable the new module. To do so go to Administer > Site building > Modules.
   Enable the module.
5. Run the update script. To do so go to the following address:
   www.example.com/update.php
   Follow instructions on screen. You must be log in as an administrator
   (user #1) to do this step.

Read more about upgrading modules: http://drupal.org/node/250790
