About
=====
Integrates the FlexSlider library into Drupal.

Current Options
---------------
Allows you to use FlexSlider in a few different ways


- As a library to be used with any other theme or module by calling flexslider_add() (N.B. You may also use drupal_add_library('flexslider', 'flexslider') however this is not recommended)
- Integrates with Views Slideshow with FlexSlider Views submodule (80% feature complete) (flexslider_views_slideshow)
- Integrates with Fields (flexslider_fields)
- Adds a Views display mode (flexslider_views)

Future Plans
------------

- Add support for Views jQFX

About FlexSlider
----------------

Library available at https://github.com/woothemes/FlexSlider

- Simple, semantic markup
- Supported in all major browsers
- Horizontal/vertical slide and fade animations
- Multiple slider support, Callback API, and more
- Hardware accelerated touch swipe support
- Custom navigation options
- Use any html elements in the slides
- Built for beginners and pros, alike
- Free to use under the MIT license


Installation
============

1. Download the FlexSlider library from https://github.com/woothemes/FlexSlider
2. Unzip the file and rename the folder to "flexslider" (pay attention to the case of the letters)
3. Put the folder in a libraries directory
    - Ex: sites/all/libraries
4. The first two files are required and the last is optional (required for javascript debugging)
    - jquery.flexslider-min.js
    - flexslider.css
    - jquery.flexslider.js
4. Ensure you have a valid path similar to this one for all files
    - Ex: sites/all/libraries/flexslider/jquery.flexslider-min.js

That's it!

Usage
======

No matter how you want to use Flex Slider (with fields, views or views slideshow) you need to define "option sets" to tell Flex Slider how you want it to display. 

Go to admin/config/media/flexslider

From there you can edit the default option set and define new ones. These will be listed as options in the various forms where you setup Flex Slider to display.

Debugging
---------

You can toggle the development version of the library in the administrative settings page. This will load the unminified version of the library.

Export API
==========

You can export your Flex Slider option presets using CTools exportables. So either using the Bulk Export module or Features.