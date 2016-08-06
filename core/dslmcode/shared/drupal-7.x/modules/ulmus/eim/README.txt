Extend the image module.

Extended functionalities

  - Adds checkboxes for the fields of image editing forms by content type.
    - Alt field required
    - Title field required
  - Sets the Alt field maxlength value to 128 for editing forms of nodes.

EIM was written by Siegfried Neumann aka Quiptime.

Dependencies
------------

The image (core) module.

Install
-------

1) Copy the EIM folder to the modules folder in your installation. Usually
   this is sites/all/modules.
   Or use the UI and install it via admin/modules/install.

2) In your Drupal site, enable the module under Administration -> Modules
   (/admin/modules).

3) Administer additional checkboxes

     Content types

       Configure a image field under Administration -> Structure ->
       Content types -> [type] -> Manage fields
       (admin/structure/types/manage/[type]/fields/[image_field_name]).

     Content type comments

       Configure a image field under Administration -> Structure ->
       Content types -> [type] -> Comment fields
       (admin/structure/types/manage/[type]/comment/fields/[image_field_name]).

     Taxonomy terms

       Configure a image field under Administration -> Structure -> Taxonomy ->
       [term name] -> Manage fields
       (admin/structure/taxonomy/[vocabulary name]/fields/[image_field_name])

     Add the additonal checkboxes

       Check 'Enable Alt field' to see the checkbox 'Alt field required'.
       Check 'Enable Title field' to see the checkbox 'Title field required'.

   Alt field maxlength

     The use of the maxlength value is not configurable. This value is used 
     for all alt fields of image fields - when enabled the EIM module.
