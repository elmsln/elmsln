Drupal colorbox module:
------------------------
Maintainers:
  Fredrik Jonsson (http://drupal.org/user/5546)
Requires - Drupal 7
License - GPL (see LICENSE)


Overview:
--------
Colorbox is a light-weight, customizable lightbox plugin for jQuery 1.4.3+.
This module allows for integration of Colorbox into Drupal.
The jQuery library is a part of Drupal since version 5+.

Images, iframed or inline content etc. can be displayed in a
overlay above the current page.

* jQuery - http://jquery.com/
* Colorbox - http://www.jacklmoore.com/colorbox/


Features:
---------

The Colorbox module:

* Excellent integration with Image field and Image styles
* Choose between a default style and 5 example styles that are included.
* Style the Colorbox with a custom colorbox.css file in your theme.
* Drush command to download and install the Colorbox plugin in
  sites/all/libraries

The Colorbox plugin:

* Supports photos, grouping, slideshow, ajax, inline, and iframed content.
* Appearance is controlled through CSS so it can be restyled.
* Preloads upcoming images in a photo group.
* Completely unobtrusive, options are set in the JS and require no
  changes to existing HTML.
* Compatible with: jQuery 1.3.2+ in Firefox, Safari, Chrome, Opera,
  Internet Explorer 7+.
* Released under the MIT License.


Installation:
------------
1. Download and unpack the Libraries module directory in your modules folder
   (this will usually be "sites/all/modules/").
   Link: http://drupal.org/project/libraries
2. Download and unpack the Colorbox module directory in your modules folder
   (this will usually be "sites/all/modules/").
3. Download and unpack the Colorbox plugin in "sites/all/libraries".
    Make sure the path to the plugin file becomes:
    "sites/all/libraries/colorbox/jquery.colorbox-min.js"
   Link: https://github.com/jackmoore/colorbox/archive/1.x.zip
   Drush users can use the command "drush colorbox-plugin".
4. Go to "Administer" -> "Modules" and enable the Colorbox module.


Configuration:
-------------
Go to "Configuration" -> "Media" -> "Colorbox" to find
all the configuration options.


Use the Views Colorbox Trigger field:
------------------------------------
TODO


Add a custom Colorbox style to your theme:
----------------------------------------
The easiest way is to start with either the default style or one of the
example styles included in the Colorbox JS library download. Simply copy the entire
style folder to your theme and rename it to something logical like "mycolorbox".
Inside that folder are both a .css and .js file, rename both of those as well to match
your folder name: i.e. "colorbox_mycolorbox.css" and "colorbox_mycolorbox.js"

Add entries in your theme's .info file for the Colorbox CSS/JS files:

stylesheets[all][] = mycolorbox/colorbox_mycolorbox.css
scripts[] = mycolorbox/colorbox_mycolorbox.js

Go to "Configuration" -> "Media" -> "Colorbox" and select "None" under
"Styles and Options". This will leave the styling of Colorbox up to your theme.
Make any CSS adjustments to your "colorbox_mycolorbox.css" file.


Load images from custom links in a Colorbox:
--------------------------------------------

Add the class "colorbox" to the link and point the src to the image
you want to display in the Colorbox.


Load content in a Colorbox:
---------------------------
Check the "Enable Colorbox load" option in Colorbox settings.

This enables custom links that can open content in a Colorbox.
Add the class "colorbox-load" to the link and build the url like
this "[path]?width=500&height=500&iframe=true"
or "[path]?width=500&height=500" if you don't want an iframe.

Other modules may activate this for easy Colorbox integration.


Load inline content in a Colorbox:
----------------------------------
Check the "Enable Colorbox inline"  option in Colorbox settings.

This enables custom links that can open inline content in a Colorbox.
Inline in this context means some part/tag of the current page, e.g. a div.
Replace "id-of-content" with the id of the tag you want to open.

Add the class "colorbox-inline" to the link and build the url like
this "?width=500&height=500&inline=true#id-of-content".

It could e.g. look like this.

<a class="colorbox-inline" href="?width=500&height=500&inline=true#id-of-content">Link to click</a>

<div style="display: none;">
<div id="id-of-content">What ever content you want to display in a Colorbox.</div>
</div>

Other modules may activate this for easy Colorbox integration.


Drush:
------
A Drush command is provides for easy installation of the Colorbox
plugin itself.

% drush colorbox-plugin

The command will download the plugin and unpack it in "sites/all/libraries".
It is possible to add another path as an option to the command, but not
recommended unless you know what you are doing.


Image in Colorbox not displayed in Internet Explorer 8:
-------------------------------------------------------

If your theme has CSS like this (popular in responsive design):

img {
  max-width: 100%;
}

Internet Explorer 8 will have problems with showing images in the Colorbox.
The fix is to add this to the theme CSS:

#cboxLoadedContent img {
  max-width: none;
}

