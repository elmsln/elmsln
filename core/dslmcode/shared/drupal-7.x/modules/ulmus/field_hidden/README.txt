(Drupal Field Hidden module)

CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Hidden in forms
 * Optionally displayed in content
 * Visible default value
 * Validation and escaping
 * Requirements
 * Installation and uninstallation
 * Permissions
 * Configuration
 * Documentation
 * Suggestions and bug reporting

INTRODUCTION
------------

Maintainer: Jacob Friis Mathiasen <jacob.friis@simple-complex.net>

Field Hidden defines five hidden field types
 * text, long text
 * integer, decimal, floating-point
 
HIDDEN IN FORMS
---------------

Hidden fields are always rendered as <input type="hidden" /> elements in forms.

OPTIONALLY DISPLAYED IN CONTENT
-------------------------------

The value of a Field Hidden field defaults to be hidden in content - as in not
rendered at all.
It may however be displayed in content, if another format than <Hidden> is
selected in the content type's 'Manage Display' section.
The numeric types have exactly the same formatting options as ordinary numeric
fields (the Number field module, e.g. prefix, suffix, thousand marker, decimal
marker).

VISIBLE DEFAULT VALUE
---------------------

Setting the default value of a field - in instance settings - is kind of hard
when it's hidden.
For ease of access, this module includes a small feature which turns the
default value field into a visible text field. May be turned off via the
administrative settings.

VALIDATION AND ESCAPING
-----------------------

The values of all the field types are being validated and escaped according
to coding standards, or stricter.
None of the text types allow for HTML/PHP input (nor output).
The only difference between text and long text is the database data type used
- varchar versus text.

REQUIREMENTS
------------

 * Drupal 7.x
 
INSTALLATION AND UNINSTALLATION
-------------------------------

Ordinary installation and unstallation.

Introduces persistent variables; these are automatically deleted when
uninstalling.

The module cannot be uninstalled if an entity/content type still has a
hidden field (of a Field Hidden type).
 * delete the entity's hidden field(s)
 * run cron
 * do uninstall

PERMISSIONS
-----------

'Administer hidden fields' - see
http://your-drupal-site.tld/admin/people/permissions#module-field_hidden

CONFIGURATION
-------------

Check the modules administrative page (requires that a role of your user
has the 'Administer hidden fields' privilege):
http://your-drupal-site.tld/admin/config/fields/field_hidden

DOCUMENTATION
-------------

PHP documentation, phpdoc Doxygen dialect:
http://www.simple-complex.net/docs/drupal/modules/field_hidden/php/field__hidden_8module.html

SUGGESTIONS AND BUG REPORTING
-----------------------------

It's your civil duty as a subject of the state of Drupal to report bugs ;-)

Please create an issue at http://drupal.org/project/field_hidden,
or mail to <jacob.friis@simple-complex.net>.