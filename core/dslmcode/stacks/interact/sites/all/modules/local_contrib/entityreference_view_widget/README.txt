This module provides an advanced Entity Reference widget that uses a view for selecting items.
The view can be paginated and have exposed filters.
It degrades, so it can be used even if Javascript is disabled.

Depends on the Entity View style plugin (provided by Entity API) rendering
the entity in the "Entityreference View Widget" view mode, and the
"Entityreference View Widget" exposed form plugin, provided by the module.

Usage:
1) Add the display "Entityreference View Widget" to your view.
2) In the Field UI for the Entity Reference field select "View" as the widget
and on the next page select your View from the dropdown.

The module has a way of hiding selected items from the View.
Simply add a base field contextual argument (Product ID for products, Node ID for nodes, etc)
and in the "More" fieldset enable "Allow multiple values" and "Exclude".
Then edit the Entity Reference field, and in the widget settings enable "Pass selected entity ids to View ".
