Editable Views
==============

Editable Views lets you create Views where the fields can be edited. Fields show both the current value and a form to edit it. A 'Save' button allows saving of all the entities shown in the View (this is compatible with having exposed filters on the View).

Editable fields can be added on the base entity as well as on entities brought into the View by a relationship. Other, non-editable fields may be added to the View, in which case they function normally.

Currently, the following Views fields can be edited:
- all FieldAPI fields
- node title

If a relationship is 'non-required', then it can bring empty data to the View. If there are editable fields on such a relationship, then it is possible to create new entities by entering data into those fields. However, the relationship must be of a sort that defines how to do this.

Currently the following relationships are supported for creating new entities:
- backward reference relationship on entityreference fields
- forward relationships on entityreference fields

Usage
-----

- Create a View, and set its style to 'Editable table'.
- Add one or more editable fields

Developer documentation
-----------------------

See the documentation page on drupal.org for developer documentation.
