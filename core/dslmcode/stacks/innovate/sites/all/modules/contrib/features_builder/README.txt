CONTENTS OF THIS FILE
---------------------

* Introduction
* Requirements
* Recommended modules
* Installation
* Configuration
* Usage
* Packaging
* Troubleshooting
* Maintainers

INTRODUCTION
------------

Features Builder is a module that analyzes the build of your Drupal site and
automatically builds Feature modules to capture the site's configuration.

The main functionality is built around the idea of a "builder" which is
responsible for identifying what configuration it's responsible for. Various
administrative screens allow you to see what's available on your site, how the
builders will package your configuration, and one-click operation to generate
and install the Features modules.

 * For a full description of the module, visit the project page:
   https://www.drupal.org/project/features_builder

* To submit bug reports and feature suggestions, or to track changes:
   https://www.drupal.org/project/issues/features_builder

REQUIREMENTS
------------
This module requires the following modules:

* Features (https://drupal.org/project/features)

RECOMMENDED MODULES
-------------------
* Strongarm (https://www.drupal.org/project/strongarm)
  When enabled, simple variable-type components are exposed and may be included
  in Features modules.

INSTALLATION
------------

* Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.

* Features Builder does not include any builders (packaging logic) by default.
   To utilize the standard configuration packaging methodology, install the
   "Features Builder Default" module which is packaged with Features Builder
   project.

CONFIGURATION
-------------

 * Basic configuration of the names and locations of the generated Feature
    modules may be set at admin/structure/features/build/config.

 * There is currently no configuration of the builder functionality available
    through the UI.

USAGE
-----

To create Feature modules using Features builder, go to the Build screen at
admin/structure/features/build. Then just press the button. Alternatively, you
may create the Features modules using the `drush fb` command.

As the configuration of the site changes, re-run the the build process to
capture new configuration and changes to existing configuration. Use Features
revert functionality to deploy changes.

PACKAGING
---------

The logic used for packaging features is a function of the builder classes. A
default set of builders is included with the "Features Builder Default" module.
If you would like to change the methodology used to package the Feature modules,
here are your options.

* Simplest: Implement hook_features_builder_components_BUILDER_alter() to make
   adjustments to the components contained in a Feature module built by an
   existing builder. This is

* Medium complexity: Implement hook_features_builders_info_alter() to swap in
   your own builder classes in place of the default builders.

* Enterprise-grade: Implement hook_features_builders_info() to expose your new
   builders to Features Builder and use them to implement your own packaging
   methodology from scratch.

TROUBLESHOOTING
---------------

This project is still somewhat experimental. Please feel free to poke around the
code. Issues, questions, comments, etc are welcome in the issue queue
https://www.drupal.org/project/issues/features_builder.

MAINTAINERS
-----------

 * Will Long (kerasai) - https://drupal.org/user/1175666
