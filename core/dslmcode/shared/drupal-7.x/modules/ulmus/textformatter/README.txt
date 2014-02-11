ABOUT

This module provides an additional formatter to render values in all
core fields as HTML or comma-separated lists.

For multi-value fields, each field value becomes a list item. For long text
fields, each line becomes a list item.

Textformatter also provides hooks (see textformatter.api.php) so that other
modules can register and implement listings for their field data. The
textformatter_contrib module provides some implementations. This is bundled
with this module. Currently entityreference, node reference, and link fields
are supported.

REQUIREMENTS

- Drupal 7.x
- Drupal core's Field module

CONFIGURATION

There is no special configuration for this module.  You may configure it just as
you would any other field formatter on the "Manage display" tab.

AUTHOR AND CREDIT

This module was developed for Drupal 6 by:
Larry Garfield & Emily Brand
http://www.palantir.net/

The Drupal 7 version initiated and maintained by:
Damian Lee

This module was initially developed by Palantir.net.
