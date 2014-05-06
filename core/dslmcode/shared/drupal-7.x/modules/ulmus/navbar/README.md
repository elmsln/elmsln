# Attention

The Navbar module is incompatible with Drupal 7 core's Toolbar module. Toolbar
module should be disabled before the Navbar module is enabled.


# Special installation instructions

The Navbar module depends on several third party JavaScript libraries, which you must download manually. After following these instructions, go to the Status Report page to confirm that all of Navbar's requirements are met.

## Modernizr

1. Download [preconfigured version of Modernizr](http://modernizr.com/download/#-inputtypes-svg-touch-cssclasses-addtest-teststyles-prefixes-elem_details) and name the file `modernizr.js`.
2. Place the file in the `sites/all/libraries/modernizr` directory.
3. Optionally, also download the minified version, place it in the same directory and name it `modernizr-min.js`. The Navbar module will automatically use the minified version if it's available, because it is more efficient.

## Backbone

1. Download `backbone.js` from [GitHub](https://github.com/jashkenas/backbone).
2. Place the file in the `sites/all/libraries/backbone/` directory.
3. Optionally, also download the minified ("production") version, place it in the same directory and name it `backbone-min.js`. The Navbar module will automatically use the minified version if it's available, because it is more efficient.

## Underscore

1. Download `underscore.js` from [GitHub](https://github.com/jashkenas/underscore).
2. Place the file in the `sites/all/libraries/underscore/` directory.
3. Optionally, also download the minified ("production") version, place it in the same directory and name it `underscore-min.js`. The Navbar module will automatically use the minified version if it's available, because it is more efficient.
