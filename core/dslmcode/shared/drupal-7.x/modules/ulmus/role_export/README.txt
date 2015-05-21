CONTENTS OF THIS FILE
---------------------

  * Introduction
  * Installation
  * Configuration
  * Frequently Asked Questions
    - Why are you doing this?
    - Hashing machine names? That will never be unique, are you out of your
      mind?
    - But shouldn't we fix all those broken modules that rely on role ids in
      their exports?
  * Known Issues
    - Re-ordering roles

INTRODUCTION
------------
Maintainers:
  * FatGuyLaughing (http://drupal.org/user/377114)
  * klausi (http://drupal.org/user/262198)

The Role Export module allows roles to have machine_names and generates a unique
role id (rid) based off of the machine_name. Roles can be exported with Features
and get the exact same rid if imported on other sites. Because of this unique
rid there is no need to create plugins per contrib module that use the rid in
their export code, such as Views, Ctools, Rules, etc. References to this role id
will not break on other sites.


INSTALLATION
------------
1. Copy role_export directory to sites/all/modules directory.
2. Go to (http://www.example.com/admin/modules) and enable the role_export
   module.
3. Go to (http://www.example.com/admin/people/permissions/roles) to create a new
   role with a unique rid and machine name.


CONFIGURATION
-------------
The role_export module does not have settings to configure.


FREQUENTLY ASKED QUESTIONS
--------------------------
Why are you doing this?
-----------------------
Consider the following scenario:
Site A: I create a new role (rid = 4, name = teacher). I add a new rule: if
a user registers at path /teacher assign the role with rid 4. Now I export
the role and the rule to a feature.

Site B: I create a new role (rid = 4, name = super_admin) and use it for
something completely different. Now I take the Feature from Site A and
enable it. Features will insert the teacher role with rid = 5. The rule is
also imported and enabled (contains hard-coded rid 4). Now if someone
registers at /teacher ==> bam! they are super_admin now ;-)

Hashing machine names? That will never be unique, are you out of your mind?
---------------------------------------------------------------------------
Certainly not. There will not be a large number of roles on a Drupal site
(if you have more than 50 you're doing it wrong). So we can assume that the
probability of an id clash is very, very, very, very low. If you encounter
such a case, please report it in the issue queue.

But shouldn't we fix all those broken modules that rely on role ids in their
exports?
----------------------------------------------------------------------------
Yes, ideally they should rely on a unique machine name for role
identification. But then all those modules would have to be changed to
depend on role_export, which is very unlikely to happen in the Drupal 7
release cycle. Or we would have to provide integration on their behalf,
which is also a lot of work. So we go with this pragmatic approach and will
fix it properly in Drupal 8.

KNOWN ISSUES
------------
Re-ordering roles
-----------------
Reordering the roles will create the missing machine names and change the role
ids which could break existing configurations.
