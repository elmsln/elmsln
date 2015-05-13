$Id:

Description
===========
This module allows you to insert tokens into a textarea. It supports both plain text and wysiwyg textareas. The format used for the insert is compatible with Token filter.

This module contains three modules:

- Token insert UI: Allows you to select which tokens are available for the insert, by default all tokens are shown. This module doesn't have to be enabled to use the others.
- Token insert (text): Add a fieldset under each textarea, works for both plain text fields and wysiwyg fields.
- Token insert (wysiwyg): Adds an extra button to wysiwyg editors and opens a popup to select the token to insert.

Instructions
============
1. Install the module
2. Configure available tokens at admin/config/content/token_insert
3. Enable Token Insert for each field that requires it
   a. Go to admin/structure/types/manage/
   b. Select "Manage Fields" for content type you would like to add Token Insert to
   c. Select "Edit" for the field you would like to add Token Insert to
   d. Find the "Token Insert" fieldset and check "Use Token Insert for this field"
   e. Configure permissions for "use token insert" at admin/people/permissions

Dependencies
============
-Token
Recommended
===========
- Token filter

Thanks to
=========
- Attiks
- Jelle

