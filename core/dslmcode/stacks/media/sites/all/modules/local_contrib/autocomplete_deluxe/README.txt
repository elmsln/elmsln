CONTENTS OF THIS FILE
---------------------

* Introduction
* Requirements
* Installation
* Configuration
* FAQ
* Maintainers


INTRODUCTION
------------

The Autocomplete Deluxe module is an enhanced autocomplete element that uses the
JQuery UI autocomplete. It will also implement a widget for taxonomy. This
module does not require any 3rd party jQuery libraries.

 * For a full description of the module visit
   https://www.drupal.org/project/autocomplete_deluxe

 * To submit bug reports and feature suggestions, or to track changes visit
   https://www.drupal.org/project/issues/autocomplete_deluxe


REQUIREMENTS
------------

This module requires no modules outside of Drupal core.


INSTALLATION
------------

Install the Autocomplete Deluxe module as you would normally install a
contributed Drupal module. Visit
https://drupal.org/documentation/install/modules-themes/modules-7 for further
information.


CONFIGURATION
-------------

To set up a field named Tags which uses an Autocomplete Deluxe widget to set
values for that field from the Tags taxonomy, do the following:

 * Navigate to Administration > Modules and enable the Autocomplete Deluxe
   module.
 * Navigate to Administration  > Structure > Content types and select manage
   fields of the content type you wish to edit.
 * Add a new field of "Term reference" named "Tags". Select the Widget Type
   "Autocomplete Deluxe" in the drop down menu. Save.
 * Select the Tags vocabulary.  Save field settings.
 * Customize or keep the default Autocomplete Deluxe settings for the field.
   Save settings.

Now when new content is added the Tags widget allows editors to enter
existing tags as well as create new ones.


FAQ
---

Q: Can I use the Autocomplete Deluxe widget as a Views exposed filter?

A: Why yes, yes you can!  First, add the field as a traditional exposed
   Autocomplete filter in your view.  Then, create a custom module (see
   https://www.drupal.org/docs/7/creating-custom-modules if you have
   never written a module before), where your .module file contains
   something like the following:

   function MY_MODULE_form_alter(&$form, &$form_state, $form_id) {
     if ($form_id == 'views_exposed_form' &&
       $form_state['view']->name == '<my view name>') {
       $form['<my field machine name>_tid'] = array(
         '#type' => 'autocomplete_deluxe',
         '#autocomplete_deluxe_path' => url('autocomplete_deluxe/taxonomy/<my
           field machine name>', array('absolute' => TRUE)),
         '#multiple' => TRUE,
         '#autocomplete_min_length' => 0,
         '#autocomplete_multiple_delimiter' => ',',
         '#not_found_message' => "The term '@term' will be added.",
       );
     }
   }

   So if you have a view with the machine name 'list_articles', and you want
   to provide an exposed Autocomplete Deluxe filter for a field with the
   machine name 'field_term_ref', the code becomes:

   function MY_MODULE_form_alter(&$form, &$form_state, $form_id) {
     if ($form_id == 'views_exposed_form' &&
       $form_state['view']->name == 'list_articles') {
       $form['field_term_ref_tid'] = array(
         '#type' => 'autocomplete_deluxe',
         '#autocomplete_deluxe_path' => url(
           'autocomplete_deluxe/taxonomy/field_term_ref',
           array('absolute' => TRUE)
         ),
         '#multiple' => TRUE,
         '#autocomplete_min_length' => 0,
         '#autocomplete_multiple_delimiter' => ',',
         '#not_found_message' => "The term '@term' will be added.",
       );
     }
   }


MAINTAINERS
-----------

Current maintainers:
 * Edward Chan (edwardchiapet) - https://www.drupal.org/u/edwardchiapet
 * Lee Nakamura (LNakamura) - https://www.drupal.org/u/lnakamura

Active support and ongoing development by Mediacurrent -
http://www.mediacurrent.com/
