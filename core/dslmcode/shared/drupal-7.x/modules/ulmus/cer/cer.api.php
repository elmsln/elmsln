<?php

/**
 * In order to create relationships between reference fields, CER needs to know
 * about what reference fields are available, and how to handle them, which is
 * what this hook is for. It should always return an array, even if there are
 * no fields to expose. The ultimate goal of this hook is to define a flattened
 * hierarchy of all the reference-type fields that CER can use.
 *
 * A reference-type field is any type of field that can refer to an entity.
 * This is pretty broadly defined: for example, CER considers field collections
 * to be reference-type fields, since they refer to entities of the
 * field_collection_item type. Even though the field collection may be displayed
 * as an embedded part of its host entity, at heart it's still just a reference
 * to an entity.
 */
function hook_cer_fields() {
  return array(
    // The keys should refer to a single field instance on a single bundle of a single
    // entity type, even for embedded entities like field collections (see below).
    'node:article:field_related_pages' => array(
      // At the very least, each field you return here needs to have a 'class' set,
      // which is the class of the plugin which will handle this field. A CER field
      // plugin must be a sub-class of CerField, and there must be a separate plugin
      // for each *type* of field you want to integrate (CER provides support for
      // most reference-type fields out of the box, though). The class you provide
      // MUST be registered with the autoloader (i.e., you need to mention it in the
      // files[] array in your module's info file).
      'class' => 'CerEntityReferenceField',
    ),
    // A field collection field is a type of reference field, so you can expose these
    // to CER too. If you want to refer to reference fields on field collections, you
    // must define the parent fields too, as in this example.
    'node:page:field_my_field_collection' => array(
      'class' => 'CerFieldCollectionField',
    ),
    'field_collection_item:field_my_field_collection:field_related_articles' => array(
      'class' => 'CerEntityReferenceField',
      // For fields that are embedded in other entities (the prime example being field
      // collections), the possible parents of the field need to be defined. The array
      // of parents should be an array of keys that are present in the aggregated result
      // of hook_cer_fields(). There could be many possible parents for a single field;
      // each parent represents another possible "route" to this field. If you leave 
      // this out, CER will try to automatically detect the parents.
      'parents' => array(
        'node:page:field_my_field_collection',
      ),
      // Embedded fields might *require* a parent. At the time of this writing, this
      // really only applies to field collections. The "require parent" flag means that
      // this field MUST have at least one parent, or CER won't use it. You can probably
      // omit this key, and let CER detect the correct value.
      'require parent' => TRUE,
    ),
  );
}

/**
 * Alter the information gathered by hook_cer_fields().
 */
function hook_cer_fields_alter(array &$fields) {
  // Do clever things here.
}
