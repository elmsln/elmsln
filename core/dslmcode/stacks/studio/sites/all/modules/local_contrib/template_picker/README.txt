Template Picker
by Bryan Braun
bryanbraun.com

Overview:
---------

  Template picker gives content creators a list of templates to choose from as they create nodes. The templates in this list are auto-discovered in your site's default theme through a simple naming convention (node--content-type--tp*.tpl.php).

  The ability to pick templates is used to assign page templates in Wordpress, and this module is a port of similar functionality to Drupal.

  Preparation: Download, install, and enable the module.

Nodes:
------

  1. Enable template picking for any or all of your content types through setting module permissions.
  2. Populate the options list by dropping template files into your theme and naming them appropriately (node--content-type--tp*.tpl.php). Here are some examples:

      -  node--article--tp-1.tpl.php
      -  node--article--tp-narrow.tpl.php
      -  node--article--tp-may2013.tpl.php

  3. When editing a node, pick the template you want from the options list in the vertical tabs. This is the template that will be used to display the node.

Entities:
---------

  With the 1.0 release, you can also pick templates for entities, like users, comments, or taxonomy terms. You can use them in the same way you use node templates. The naming convention for entity templates is entity--bundle--tp*.tpl.php

  Here are some examples of entity-based template suggestions:

      -  taxonomy-term--tags--tp-1.tpl.php
      -  user--user--tp-1.tpl.php
      -  comment--comment-node-article--tp-1.tpl.php
      -  node--article--tp-1.tpl.php
      -  video--advertisement--tp-1.tpl.php (a custom entity and bundle)

     (note: entity or bundle machine names containing underscores should be converted to hyphens when used in template file names, as shown above)

  You can pick templates for custom entities (which have their own display template), as long as those entities are built off of the Entity API module (https://drupal.org/project/entity).

  Template picker will probably not work with entities built with the ECK module (https://drupal.org/project/eck), until the issues I've reported with ECK form submission (https://drupal.org/node/2163295) have been addressed.

  Of the entities that come with Drupal 7 core, the 'file' and 'taxonomy_vocabulary' entities are not supported by template picker, since they have no default template implementations to override.

Clean Names:
------------

  Clean names affect how your templates display in the options list like this:

    Display w/out clean name: node--article--tp-narrow.tpl.php
    Display with clean name: Narrow Template

  You can add a "clean name" to each template by specifying the name in the comments of the template. For example, you can assign the clean name of "Narrow Template" like this:

  /**
   * @file
   * Template Name: Narrow Template
   *
   * Available variables:
   * ...
