DOCUMENTATION
----------------------------------
Please refer also to the community documentation:
  http://drupal.org/node/1948260

BUILD A THEME WITH ZURB FOUNDATION
----------------------------------

The base Foundation theme is designed to be easily extended by its sub-themes.
You shouldn't modify any of the CSS or PHP files in the zurb_foundation/ folder;
but instead you should create a sub-theme of zurb_foundation which is located in
a folder outside of the root zurb_foundation/ folder. The examples below assume
zurb_foundation and your sub-theme will be installed in sites/all/themes/,
but any valid theme directory is acceptable. Read the
sites/default/default.settings.php for more info.

This theme does not support IE7. If you need it downgrade to Foundation 2 see
http://foundation.zurb.com/docs/faq.php or use the script in the starter
template.php THEMENAME_preprocess_html function.

*** IMPORTANT NOTE ***
*
* In Drupal 7, the theme system caches which template files and which theme
* functions should be called. This means that if you add a new theme,
* preprocess or process function to your template.php file or add a new template
* (.tpl.php) file to your sub-theme, you will need to rebuild the "theme
* registry." See http://drupal.org/node/173880#theme-registry
*
* Drupal 7 also stores a cache of the data in .info files. If you modify any
* lines in your sub-theme's .info file, you MUST refresh Drupal 7's cache by
* simply visiting the Appearance page at admin/appearance or at
  admin/config/development/performance.

BUILD A THEME WITH DRUSH
----------------------------------
If you have drush and the zurb foundation theme enabled you can create a
subtheme easily with a drush.

The command to do this is simply:
  drush fst [THEMENAME] [Description !Optional]

MANUALLY BUILD A THEME
----------------------------------
 1. Setup the location for your new sub-theme.

    Copy the STARTER folder out of the zurb_foundation/ folder and rename it to
    be your new sub-theme. IMPORTANT: The name of your sub-theme must start with
    an alphabetic character and can only contain lowercase letters, numbers and
    underscores.

    For example, copy the sites/all/themes/zurb_foundation/STARTER folder and
    rename it as sites/all/themes/foo.

      Why? Each theme should reside in its own folder. To make it easier to
      upgrade Foundation, sub-themes should reside in a folder separate from the
      base theme.

 2. Setup the basic information for your sub-theme.

    In your new sub-theme folder, rename the STARTERKIT.info.txt file to include
    the name of your new sub-theme and remove the ".txt" extension. Then edit
    the .info file by editing the name and description field.

    For example, rename the foo/STARTER.info.txt file to foo/foo.info. Edit the
    foo.info file and change "name = Foundation Sub-theme Starter" to
    "name = Foo" and "description = Read..." to "description = A sub-theme".

      Why? The .info file describes the basic things about your theme: its
      name, description, features, template regions, CSS files, and JavaScript
      files. See the Drupal 7 Theme Guide for more info:
      http://drupal.org/node/171205

    Then, visit your site's Appearance page at admin/appearance to refresh
    Drupal 7's cache of .info file data.

 3. Edit your sub-theme to use the proper function names.

    Edit the template.php and theme-settings.php files in your sub-theme's
    folder; replace ALL occurrences of "STARTER" with the name of your
    sub-theme.

    For example, edit foo/template.php and foo/theme-settings.php and replace
    every occurrence of "STARTER" with "foo".

    It is recommended to use a text editing application with search and
    "replace all" functionality.

 5. Set your website's default theme.

    Log in as an administrator on your Drupal site, go to the Appearance page at
    admin/appearance and click the "Enable and set default" link next to your
    new sub-theme.


Optional steps:

 6. Modify the markup in Foundation core's template files.

    If you decide you want to modify any of the .tpl.php template files in the
    zurb_foundation folder, copy them to your sub-theme's folder before
    making any changes.And then rebuild the theme registry.

    For example, copy zurb_foundation/templates/page.tpl.php to
    THEMENAME/templates/page.tpl.php.

 7. Modify the markup in Drupal's search form.

    Copy the search-block-form.tpl.php template file from the modules/search/
    folder and place it in your sub-theme's template folder. And then rebuild
    the theme registry.

    You can find a full list of Drupal templates that you can override in the
    templates/README.txt file or http://drupal.org/node/190815

      Why? In Drupal 7 theming, if you want to modify a template included by a
      module, you should copy the template file from the module's directory to
      your sub-theme's template directory and then rebuild the theme registry.
      See the Drupal 7 Theme Guide for more info: http://drupal.org/node/173880

 8. Further extend your sub-theme.

    Discover further ways to extend your sub-theme by reading
    Drupal 7's Theme Guide online at: http://drupal.org/theme-guide

CHANGING FOUNDATION DEFAULT SETTINGS
------------------------------------
Subthemes use the parent theme Foundation settings in scss/foundation/_settings.scss.

If you want to override these, copy the _settings file from the parent theme into your subtheme,
and include it in the base/init SCSS file of your subtheme.

DEVELOPING A SUBTHEME WITH GRUNT.JS
-----------------------------------

Overview
Grunt.js is a javascript library that runs on Node.js that allows tedious tasks to be automated behind the scenes so you can be more efficient with developing code. It is a full on replacement for the Compass/Ruby stack, relieving you from managing
multiple versions of Ruby and gemsets while providing the benefit of LiveReload, automated Drush, and hundreds of extensible Node.js modules for Grunt to pad your workflow tools.

System Requirements (Mac)
 - Homebrew (OSX Package Manager - http://brew.sh/)
 - Node.js
 - Grunt

It is encouraged to use package managers like Homebrew (mac) and RVM (Ruby manager) so using sudo is not required to install global
packages.

If you do not use them and you get errors with the commands, you can try 'sudo' before the command to see if that works for you.

Installation (Mac)
==================

Install Homebrew with the docs here: http://brew.sh/

At the command line, enter the following commands:

brew install node
npm install -g grunt grunt-cli

This will install homebrew, nodejs, and grunt at the global level (so npm and grunt are global level commands in terminal).

Installation (Linux)
====================

TBD, need documentation.

Installation (Windows)
======================

TBD, need documentation.


Generating Subthemes
====================

See above - it is highly recommended that you use the drush function to do this.

In terminal, navigate to the subtheme folder and type the following:

npm install

This will tell node.js to install the dependencies listed in package.json. Due to the amount of files and file size that is downloaded, we do not commit these to the repositories. If you have a gitignore file,
make sure ‘node_modules’ is ignored. It only takes seconds to grab the dependencies.

Finally, in terminal, type ‘grunt’ and hit enter. If all went well, Grunt is now running and watching your theme for changes. You can test it by making a simple edit to the theme SASS file and saving. Grunt
should react and generate a new file, based on the information given to it in the Gruntfile. The drush function automatically fills in placeholders with the real subtheme name, so peeking at Gruntfile.js should have your theme name in it and
the right paths to the CSS/SCSS folders within it.

When the SASS task fires, so is LiveReload, so any connected browser should instantly refresh with the changes.

Strange issues on iOS?
======================

You may be seeing issues with the FastClick plugin.

Try disabling FastClick in your subtheme by opening the Gruntfile and commenting out this line:

'<%= global_vars.base_theme_path %>/js/vendor/fastclick.js'

Trigger Grunt to recompile your theme, and reload to see if the issue persists.