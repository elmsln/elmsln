Field Redirection
*****************

A field formatter for EntityReference, File, Link, Node Reference, Term
Reference, URL and User Reference fields that will perform a HTTP redirect to
the given entity, file, URL, term, node, URL or user.  The formatter's settings
allow selection from one of the seven different possible HTTP status codes that
are allowed by the specifications.

Example Usage
*************
The best way of using this module is to create a custom display setting for the
"Full content", pick one of the redirect status codes below, e.g. 301, and hide
all other fields to reduce processing & load time.

To configure the recommended settings:
* Go to the "Manage Display" tab on the settings page for the entity of choice
  (user, content type, etc) settings page, e.g. to work with the content type
  "redirect_user", go to the URL:
  http://example.com/admin/structure/types/manage/redirect_user/display
  (where "example.com" is your site's hostname).
* Expand the "Custom display settings" fieldset and ensure the "Full content"
  checkbox is checked.
* Click the "Save" button.
* Go to the "Full Content" tab.
* Ensure that all of the fields are hidden except for the field you wish to
  use.
* Click the selector in the Format column of the field in question and change
  it to "Redirect".
* By default the formatter will do a HTTP 301 redirect indicating the path in
  question is permanently moved.  To change this, click the "cog" icon beside
  the field and select one of the other options then click Update.
* Click the "Save" button.
* Ensure that other display modes do not use the redirect.

Status codes
************
For completeness sake this module provides all of the allowed HTTP status codes
that are valid for redirection:
* 300 - "multiple choices".
* 301 - "moved permanently" - The best option for most use cases, indicates
  that the current path will not be made available again and links should be
  updated to the new path.
* 302 - "found" - Usually used to indicate a temporary redirect, but also that
  there may be technical problems causing the redirection.
* 303 - "see other".
* 304 - "not modified".
* 305 - "use proxy".
* 307 - "temporary redirect" - Best to use if the path is purposefully only
  being redirected temporarily and this current path will be made available
  for display again at a later time.  If the current path will not be made
  available again it would be better to use status code 301 instead.

The most commonly used are 301 and 307.

Further reading: http://en.wikipedia.org/wiki/URL_redirection

WARNING
*******
This field formatter should *only* be used when displaying the "full content"
of a given entity (user, content type, etc), otherwise unexpected results will
happen.  Example problems that can arise include:
* Using this formatter for a view mode used on the search index could cause
  the search index to never complete, or even cron to never complete.
* Using this formatter in an RSS feed would cause all readers of the RSS feed
  to be instantly redirected to the path provided by this field, rather than
  seeing the feed itself.
* Using this formatter in a teaser would cause any page that displayed this
  entity in its content list, e.g. possibly the site's homepage, to redirect.

Limitations
***********
There are a few known limitations to this module:
* Only one field for a given entity (user, content type, etc) should be
  assigned this formatter.
* The field that is given this formatter should have a maximum number of values
  set to 1.
* It does not make sense to create a Panel node_view display for entities using
  this on a field formatter.

TODO
****
There are a few tasks that would be good to add:
* Provide JavaScript redirection, like the old CCK_Redirection module.
* Provide frameset redirection, like the old CCK_Redirection module.
* Backport to Drupal 6 (seriously).

Attribution
***********
Based on the CCK_Redirection [1] module by Robin Monks [2] for Drupal 5 and 6.
The idea of just providing formatters rather than a fully separate field type
was from user e2thex [3] who suggested the idea during discussion of the
Drupal 7 port of CCK_Redirection [4].

Why a separate module?
**********************
This was written as a separate module rather than an expansion of the D7 port
of CCK_Redirection purely to keep it small & simple, without adding any extra
fields or deal with migration of D6 data.

Author
******
The module was written and is maintained by DamienMcKenna [5]. Development is
currently sponsored by Mediacurrent [6].


1: http://drupal.org/project/cck_redirection
2: http://drupal.org/user/12246
3: http://drupal.org/user/189123
4: http://drupal.org/node/1098250
5: http://drupal.org/user/108450
6: http://www.mediacurrent.com/
