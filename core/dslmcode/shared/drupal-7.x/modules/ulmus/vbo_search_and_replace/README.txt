Views Bulk Operations (VBO) Search And Replace
==============================================

This module exposes a new Views Bulk Operations action "Search and replace on Entity values" that allows you to perform a search and replace on the values (fields/properties) of selected entities in a view. It's modeled after the built-in action "Modify Entity Values".

Installation
------------

- Install the module.
- Go to the Views Bulk Operations settings page on a view.
- Select "Search and Replace on Entity values" from the "Selected bulk operations" section.
- Configure settings:
   - "Display Checkboxes Inline": Enable this to add some css to the page to display the checkboxes inline as columns.
   - "Display Values": Specify which fields/properties are able to be search and replaced on.

Usage:
------

- Select some rows on a VBO view and run the "Search and replace on Entity values" Action
- An settings page will be loaded. Here you can select which fields/properties you want to perform the Search and Replace on. The list will automtically filter which fields are shown based on the view. So if you have a view that is only showing nodes of the type "blog", only blog fields will be shown.
- Enter a string to search for
- Enter a replacement string
- Set advanced settings for the search and replace:
   - "Search Prefix": The string that search string must be immediately preceeded by in order for a match to be made (only the search string will be replaced, however).
   - "Search Suffix": The string that the search string must be immediately followed by in order for a match to be made (only the search string will be replaced, however).
   - "Case Sensitive": Whether or not the search should be case sensitive
   - "Exact Match": Check this if the entire field must match the search parameters including the prefix and suffix. example: With this option selected, for the search string "The quick brown fox" to obtain a match, the entire contents of the field must be "The quick brown fox". A field with the value "The quick brown fox jumps over the lazy dog" will not be considered a match

Notes:
------

Note that you can only perform Search and Replace on text based fields/properties. This is probably how it will always be, although I could be swayed by a compelling argument. See FAQs (below) for more information.

FAQs:
-----

Q: Hey, why can't I search and replace on text-based list fields?
A: This would be dangerous because you could alter input that was picked from your allowed values, thus invalidating it. To search and replace on a list field, you would first filter the view using an exposed filter (search), then use "Modify Entity Values" to replace the old value(s) with a new one from the list.

Q: But I changed my allowed values list and now I need to update a bunch of nodes!
A: Use a SQL query. Or, put your old value back in the allowed values list, filter your view to that value, then use Modify Node Fields (as described above) to change the value to your new value. When all is well, remove the old value from the list.

Q: Okay, well what about this other field of type X?
A: The idea with VBO Search and Replace was to be able to search for a word (or paragraph) in a larger block of text and replace it. For other field types this doesn't really make sense and can bring up validation issues (see previous FAQ). However, that might just be me being narrow minded and I'm open to discuss it in the issue queue.

Development sponsored by: Fuse Interactive (http://fuseinteractive.ca)
