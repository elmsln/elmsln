Introduction
============
Token Insert Entity offers a WYSIWYG button to embed rendered entities in fields
using a WYSIWYG (tipically the body of a node).

Installation
============

Start by enabling the module and its dependencies.

If you have not set up WYSIWYG, follow the installation instructions at
Home » Administration » Configuration » Content authoring > WYSIWYG Profiles
(admin/config/content/wysiwyg). Then edit a WYSIWYG profile that uses
an editor and under Buttons and Plugins check Rendered Entity. Click the
save button.

Go to Home » Administration » Configuration >> Text formats
(admin/config/content/formats) and edit the configuration of the text
format that matches with the WYSIWYG profile you edited before.
Activate the "Replace tokens" filter and save your changes.

In order for the Insert Content form to work as expected, the
following core patch needs to be applied:
http://drupal.org/files/ac_select_event-365241-54.patch

Clear caches and add or edit a piece of content that contains the
configured WYSIWYG. You should see the Insert a token icon. Open it
and type part of the title of a piece of content, it should
autopopulate and show you the available view modes. Clicking
on Insert token should insert a token in the body. When the
node is rendered these tokens will be replaced by fully
rendered pieces of content.
