
Node access node reference README

CONTENTS OF THIS FILE
----------------------

  * Introduction
  * Requirements
  * Installation
  * Usage
  

INTRODUCTION
------------
Gives content access permissions to users if they have access to content that is
referenced with node reference.  Checks view, update, and delete grant 
operations, and can pass those on to the referencing content, or trigger a
different grant configuration according to settings.

Project page: http://drupal.org/project/nodeaccess_nodereference.


REQUIREMENTS
------------
This module requires a field module that can reference content.  Currently there 
are two modules supported:
http://drupal.org/project/entityreference
http://drupal.org/project/references


INSTALLATION
------------
Install and enable the Node access node reference module.
For detailed instructions on installing contributed modules see:
http://drupal.org/documentation/install/modules-themes/modules-7


USAGE
-----
Create a field to reference content in a content type using the Field UI.  The 
field's configuration page will contain the settings for Node access node 
reference. For detailed instructions on using the Field UI see: 
http://drupal.org/documentation/modules/field-ui