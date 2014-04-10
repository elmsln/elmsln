

Example Layout Plugins
----------------------

If you are NOT developing a page layout plugin you can safely delete this
entire directory from your sub-theme.


Page Layouts
------------

If you are developing a page layout plugin see the developer notes in:

  at_core/layouts/core/_README.txt

There are many code comments in the three_col_grail.inc file.

You can enable the "naked" example layout plugin by uncommenting the
info file entry in your subthemes info file. Look for:

  ; plugins[page_layout][layouts] = layouts/page
  
Remove the semicolon to uncomment and clear the cache.



Panels Layouts
--------------

If you are developing a Panels layout plugin see the developer notes in:

  at_core/layouts/panels/_README.txt

There are many code comments in the five_5x20.inc file.

You can enable the example Panels plugin by uncommenting the
info file entry in your subthemes info file. Look for:

  ; plugins[panels][layouts] = layouts/panels

Remove the semicolon to uncomment and clear the cache.
