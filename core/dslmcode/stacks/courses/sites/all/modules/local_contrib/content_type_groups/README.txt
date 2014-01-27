CONTENTS OF THIS FILE
---------------------

* Introduction
* Installation
* Example
* Views Integration
* API
* Design Decisions

INTRODUCTION
------------

Current maintainer: Karen Ziv <me@karenziv.com>

Content type groups was designed to handle the use case when you need to
populate select boxes or other interface elements with certain content
types but not others.

This module allows you to create an unlimited number of groups of
content types. Once a group is created, it can be referenced using API
functions or in Views.

INSTALLATION
------------

There are no special requirements for this module; installation uses the
standard Drupal process. If you're reading this, you've likely already
correctly installed this module.

1. Download the module from drupal.org.
2. Untar the archive into your modules directory.
3. Go to Admin > Modules and enable the Content type groups module.
4. Manage content type groups at Admin > Structure > Content types > Content type groups

EXAMPLE
--------

Let's say you're organizing your media collection. You have the following content types:
'book', 'movie', 'audio', 'article' (for your blog about your collection), 'page' (for
some static content).

Create a content type group called 'Media' and add the 'book', 'movie', and 'audio'
types. You have just created a logical grouping between the content types to show that
they are somehow related. This makes it easier for future developers to understand
the relationship between various content types.

Now let's say you start collecting old magazines. Create a new content type called
'magazine' and add it to the Media content type group. Any place where that content
type group is referenced will automatically reflect the change; there is no need to
track down all Views or lists.

VIEWS INTEGRATION
-----------------

Now that you have your content type group, you can filter Views by the Media content
type group instead of selecting each content type individually. Once enabled, this
module exposes a filter for use in filtering nodes to those only of a type belonging
to a given content type group. Let's walk through this with the Media content type
group (see Example).

You have a view that shows all nodes and you want to filter it to only show nodes that
are of the 'book', 'movie', or 'audio' type. The traditional way is to add a filter
on Content: Type and select those types, but this means that every time you add a
content type that is a media type, you have to remember to go back to your View and
add that to the filter criteria.

Instead, we're going to tell the View to only show nodes that are in the Media
content type group. Click the Add button on the Filter Criteria section in your view.
Select content type groups from the Filter dropdown. You will see one option:
Content type groups: Content type group. Select this option, then click the Add and
configure filter criteria button. From the Options list, select Media, then
click the Apply button to save the filter.

You should see your list of nodes in the preview restricted to only those with a
content type within the Media content type group. Now if you add a new content
type to the Media group, the View will automatically update to show you the
additional nodes.

API
------------

Once enabled, this module exposes a class that can be used in your own
custom module development.

To get information about a content type group:
$group = new ContentTypeGroup($machine_name);

A common use case for this will be to fill the options of a form element
such as a select list or checkboxes:

$group = new ContentTypeGroup($machine_name); // Get the content type group of the given machine name
$form['my_element'] = array(
  '#type'    => 'checkboxes',
  '#options' => $group->typeList(), // Returns an array keyed as $content_type => $type
);

DESIGN DECISIONS
----------------

Class vs Namespaced Functions

A content type group is an object and is thus best represented by a class. All logic for
managing a content type group is thus encapsulated into a cohesive structure. The class
was named after the module to prevent namespacing collisions.

