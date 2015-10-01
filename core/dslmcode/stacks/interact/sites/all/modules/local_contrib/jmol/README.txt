CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Dependencies
 * Installation
 * Usage
 * Example pages
 * Info for themers

INTRODUCTION
------------

This module adds a display formatter for the file field type to display
molecular structure files in a Jmol interactive java applet. Using the applet,
it is possible to interactively analyse the uploaded molecular structure in 3D.

The formatter settings include options to set:
 * the size of the applet
 * a number of exposed viewing styles (wireframe, sticks, ribbon, ...)
 * the default viewing style
 * a textbox allowing custom Jmol script input
 * the page alignment of the applet
 * the default measurements units (angstroms or nanometers)

The default usage of this module would be to create a new content type with
a file field and to choose "Jmol applet" as formatter in the manage
display section of the content type fields.
For more information on the Jmol script language, visit
http://jmol.sourceforge.net/demo/jssample1/ for some example scripts and visit
http://chemapps.stolaf.edu/jmol/docs/ for a reference of all scripting commands
in Jmol. Also visit http://jmol.sourceforge.net/jslibrary for all the Jmol
applet functionality.

Have fun!

DEPENDENCIES
------------

The Jmol module requires the following modules to be installed and enabled:

 * Libraries (from https://drupal.org/project/libraries)

The Jmol module also requires the external Jmol library (see next section).
This version of the Jmol module ONLY works with Jmol 13.2.0 or higher.

INSTALLATION
------------

1. It is not recommended to place this module in the core modules folder
   (this is the 'module' folder directly under your Drupal installation folder).
   Instead place it (unzip it) in a module folder where all contributed
   modules should be located e.g. 'sites/all/modules'.
   So you would end up with a folder 'sites/all/modules/jmol' under the main
   Drupal installation folder. This folder now contains the jmol.module file and
   other files belonging to the Jmol module.

2. Download the external Jmol library from 
   http://sourceforge.net/projects/jmol/files/Jmol/
   This is typically a file named Jmol-13.2.3-binary.zip, depending on
   the version.
   The content of this zip file should be extracted in the 
   'sites/all/libraries/jmol' folder. Create it if it doesn't exist.
   If you now look in this folder, you will see a zipfile named jsmol.zip with
   the path 'sites/all/libraries/jmol/jsmol.zip'.
   Unzip this file so that the file JSmol.min.js is located as written here:
   'sites/all/libraries/jmol/jsmol/JSmol.min.js'.

3. On your Drupal site, go to Administration > Modules and
   activate the Jmol module.

USAGE
-----

1. Go to Administration > Structure > Content type and add a new content type.
   Add at least one field of the field type File to the content type.
   You can also add a file field to an existing content type like
   'Article' or 'Basic page'. Don't forget to allow your favorite molecular
   structure file type to be uploaded. This is by default set to files
   with the extension .txt only.

2. Once you added all your fields click on Manage Displays and for the file
   field choose "Jmol applet" as formatter.

3. Now you can click on the cog wheel besides the field to configure the
   formatter. Don't forget to update and save.

Done! Now any uploaded structure file to this field will be displayed using
the Jmol applet.

FEATURES EXPLANATION
--------------------

Most of the features available in the Jmol formatter section are easy to
understand.
However, the Applet type might need some explanation.
There are three applet types to choose from:

* Java and HTML5
* Java only
* HTML5 only

The ability to choose has been introduced in Jmol 13.2.x. A Java only applet
uses Java on the client side, so the user must have the Java browser addon
enabled. For security reasons some users disable Java in the browser, so for
them, the HTML5 applet (uses only JavaScript) will work instead.
When you choose 'Java and HTML5' as applet type, Jmol will default to the 
original Java applet when the user has Java enabled. When Java is not enabled,
Jmol will automatically use the HTML5 applet, so all users are satisfied and
will be able to use your website with the Jmol module.

For now, the HTML5 version is still under development by the Jmol team and
is still slower and a bit buggier than the Java version.

INFO FOR THEMERS
----------------

The Jmol module implements a theme function to display the Jmol applet with
default theming. This function is called theme_jmol_formatter() and the
variables available for theming are explained in the function's comment.
Theme developers can override the default theme function by e.g. creating
a template file jmol_formatter.tpl.php or jmol-formatter.tpl.php in
sites/all/themes/<theme-name>/. For example, in that template file you can
access the size of the applet by calling $variables['settings']['size'].
Clear your cache to make sure Drupal finds the template file.
