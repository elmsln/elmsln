Your Custom CSS for FontFolio theme.
--------------------------------------

"fontfolio/styles/my-custom" contains empty CSS files that intended to contain
your custom CSS overrides and modifications to FontFolio theme.

When downloaded from Drupal.org this folder initialy contains empty CSS files
with names that ends with ".txt" extention.

After removing the ".txt" extension files will be recognized by fontfolio and 
will automatically included inside your html pages <head>.
"my-custom-ff.css" will be called immediately after "fontfolio.css" and 
"my-custom-ff-md-queries.css" that should contain your custom media query rules will
be called immediately after "fontfolio-md-queries.css" that holds fontfolio's media 
query styles.

After removing the ".txt" extension your custom styles resides in files that will not 
get overwritten by upgrading fontfolio to newer version, because of different file
names/extensions.
