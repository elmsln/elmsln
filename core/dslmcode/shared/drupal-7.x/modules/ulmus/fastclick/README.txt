FastClick is a simple, easy-to-use library for eliminating the 300ms
delay between a physical tap and the firing of a click event on mobile
browsers. The aim is to make your application feel less laggy and more
responsive while avoiding any interference with your current logic.

For instructions on how to use this module, see
https://drupal.org/project/fastclick

Note for developers and users of previous versions (< 1.2): This
module now adds by default the FastClick library on every page. This
was handled previously in the deprecated module 'FastClick Everywhere'
but the functionality was merged.
If you want to add it manually or add the behaviour in specific places,
set the fastclick_enable_everywhere variable to FALSE:

variable_set('fastclick_enable_everywhere', FALSE);


Credits
-------
FastClick is developed by FT Labs, part of the Financial Times. See
https://github.com/ftlabs/fastclick

This Drupal module is maintained by Pere Orga <pere@orga.cat>.
