/**
 * Unique Field module for Drupal (unique_field)
 * Compatible with Drupal 7.x
 *
 * By Joe Turgeon [http://arithmetric.com]
 */

The Unique Field module provides a way to require that specified fields
or characteristics of a node are unique. This includes the node's title,
author, language, taxonomy terms, and other fields.

Without this module, Drupal and CCK do not prevent multiple nodes from
having the same title or the same value in a given field.

For example, if you have a content type with a Date field and there
should only be one node per date, you could use this module to prevent a
node from being saved with a date already used in another node.

This module adds additional options to the administration page for each
content type (i.e. admin/structure/types/manage/<content type>) for
specifying which fields must be unique. The administrator may specify
whether each field must be unique or whether the fields in combination must
be unique. Also, the administrator can choose whether the fields must be
unique among all other nodes or only among nodes from the given node's
content type.

Alternatively, you can select the 'single node' scope, which allows you
to require that the specified fields are each unique on that node. For
example, if a node has multiple, separate user reference fields, this
setting will require that no user is selected more than once on one node.

For more information, see this module's page at:
http://drupal.org/project/unique_field
