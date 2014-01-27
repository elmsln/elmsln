Replicate Field Collection Extends Replicate module to manage the cloning of 
field_collection entities and fields.

Basics:
-------
When you clone an entity (node, taxonomy term, ...) containing a 
field collection reference, the field collection items are not duplicated, 
and the cloned entity still references the same field collection than 
the original entity.
This poses great issues as any modification on the field collection will impact 
all the duplicated entities.

Replicate Field Collection correct that behavior and implements a clean 
duplication of field collections.
The replication is recursive, i.e will work on field collections containing 
field collections and so on.


Dependencies:
-------------
-Replicate
-Entity API
-Field Collection

Thanks:
-------
-Vincent Bouchet for his help on the coding and testing of this module
-All the people involved on the discussion: http://drupal.org/node/1233256, 
the first draft of this module was based on the patches submitted here

Module development sponsorized by Capgemini Drupal Factory.
