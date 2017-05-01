File (Field) Paths
==================

[![Build Status](https://travis-ci.org/Decipher/filefield_paths.svg)](https://travis-ci.org/Decipher/filefield_paths)

The File (Field) Paths module extends the default functionality of Drupal's core
File module, Image module and many other File upload modules, by adding the
ability to use entity based tokens in destination paths and file names.

In simple terms, File (Field) Paths allows you to automatically sort and rename
your uploaded files using token based replacement patterns to maintain a nice
clean filesystem.



Features
--------

* Configurable file paths now use entity tokens in addition to user tokens.
* Configurable file names.
* Support for file based fields, including but not limited to:
    * Drupal core File module.
    * Drupal core Image module.
    * Video module.
* File path and filename cleanup options:
    * Remove slashes from tokens.
    * Filter out words and punctuation by taking advantage of the Pathauto
      module.
    * Convert unicode characters into US-ASCII with the Transliteration module.
* Automatically updates unprocessed file paths in any Text fields on the entity.
* Retroactive updates - rename and/or move previously uploaded files.
* Active updating - actively rename and/or move previously uploaded files.
* Create redirect - automatically create a redirect when moving uploaded files,
  using the Redirect module.



Recommended Modules
-------------------

* [Pathauto](https://www.drupal.org/project/pathauto)
* [Redirect](https://www.drupal.org/project/redirect)
* [Token](https://www.drupal.org/project/token)
* [Transliteration](https://www.drupal.org/project/transliteration)



Usage/Configuration
-------------------

Once installed, File (Field) Paths needs to be configured for each file field
you wish to use. Settings can be found on the settings form of any supported
file based field.

  *Example:*
  
    Administration > Structure > Content types > Article > Manage fields > Image
    http://example.com/admin/structure/types/manage/article/fields/field_image



Frequently Asked Questions
--------------------------

Q. Aren't tokens already supported in the File module?

A. A limited selection of tokens are supported in the File module.

   Entity based tokens allow you to use the Entity ID, Title, creation date and
   much more in your directory/filenames where you would otherwise be unable.


Q. Why aren't my files in the correct folder?

A. When you are creating or updating an entity the full values for the tokens
   may not yet be known by Drupal, so the File (Field) Paths module will upload
   your files to a temporary location and then once you save the entity and
   Drupal is provided with the tokens values the file will be moved to the
   appropriate location.


Q. Why is there a warning on the 'Retroactive updates' feature?

A. Retroactive updates will go through every single entity of the particular
   bundle and move and/or rename the files.

   While there have been no reports of errors caused by the feature, it is quite
   possible that the moving/renaming of these files could break links. It is
   strongly advised that you only use this functionality on your developmental
   servers so that you can make sure not to introduce any linking issues.



History and Maintainers
-----------------------

File (Field) Paths was written and is maintained by Stuart Clark (deciphered).

* http://stuar.tc/lark
* http://twitter.com/Decipher
