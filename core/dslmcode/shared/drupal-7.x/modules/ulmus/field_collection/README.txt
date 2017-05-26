Field collection
-----------------
Provides a field collection field, to which any number of fields can be attached.

Each field collection item is internally represented as an entity, which is
referenced via the field collection field in the host entity. While
conceptually field collections are treated as part of the host entity, each
field collection item may also be viewed and edited separately.


 Usage
 ------

  * Add a field collection field to any entity, e.g. to a node. For that use the
   the usual "Manage fields" interface provided by the "field ui" module of
   Drupal, e.g. "Admin -> Structure-> Content types -> Article -> Manage fields".

  * Then go to "Admin -> Structure-> Field collection" to define some fields for
   the created field collection.

  * By the default, the field collection is not shown during editing of the host
    entity. However, some links for adding, editing or deleting field collection
    items is shown when the host entity is viewed.

  * Widgets for embedding the form for creating field collections in the
    host-entity can be provided by any module. In future the field collection
    module might provide such widgets itself too.


 Using field collection with entity translation
 -----------------------------------------------

  * Field collection items must be selected as a translatable entity type at
    Admin -> Config -> Regional -> Entity Translation.

  * The common use case is to leave the field collection field untranslatable
    and set the necessary fields inside it to translatable.  There is currently
    a known issue where a host can not be translated unless it has at least
    one other field that is translatable, even if some fields inside one of
    its field collections are translatable.

  * The alternate use case is to make the field collection field in the host
    translatable.  If this is done it does not matter whether the inner fields
    are set to translatable or not, they will all be translatable as every
    language for the host will have a completely separate copy of the field
    collection item(s).
