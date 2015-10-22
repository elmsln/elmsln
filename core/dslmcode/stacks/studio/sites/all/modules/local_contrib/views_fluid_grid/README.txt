;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Views Fluid Grid
;; Original author: markus_petrux (http://drupal.org/user/39593)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CONTENTS OF THIS FILE
=====================
* OVERVIEW
* VIEWS INTEGRATION
* REQUIREMENTS
* INSTALLATION
* CUSTOMIZATION
  * TEMPLATES
  * STYLESHEETS
  * ADVANCED


OVERVIEW
========

This module provides the Fluid Grid style plugin for Views. This plugin displays
the view as a fluid grid using an HTML list element.

The plugin settings form provides options to define the width and height of the
elements in the grid. But it also provides advanced layout options implemented
in separate CSS classes that allow you to define item margins, alignment and a
couple of CSS3 properties (box-shadow and border-radius).


VIEWS INTEGRATION
=================

A fluid grid style plugin could be included in Views in the future. For further
information, please see the following issue in the Views queue:

http://drupal.org/node/377574


REQUIREMENTS
============

- Views 3.
  http://drupal.org/project/views


INSTALLATION
============

- Be sure to install all dependent modules.

- Copy all contents of this package to your modules directory preserving
  subdirectory structure.

- Go to Administer -> Site building -> Modules to install module.

- You can now start using the Fluid grid style plugin in your views.


CUSTOMIZATION - TEMPLATES
=========================

Please, see the "Theme: Information" option in Views UI. Information about
the template used by this style plugin is available under the "Style output"
entry.

The template shipped with the module is views-fluid-grid-plugin-style.tpl.php
located under the theme subdirectory of the package.


CUSTOMIZATION - STYLESHEETS
===========================

The following stylesheets are provided:

- views_fluid_grid.base.css

  It contains the base CSS classes to style the fluid grid.

- views_fluid_grid.size.css

  It contains additional CSS classes that are used to define the width and
  height of the items in the grid. These sizes are defined for each option
  in the settings form of the style plugin. If you need to add more sizes to
  the list, please see ADVANCED section below.

- views_fluid_grid.advanced.css

  If contains additional CSS classes to implement the advanced layout options
  available from the settings form of the style plugin. This file is loaded
  only if any of these advanced options are really used.


CUSTOMIZATION - ADVANCED
========================

You may want to use a different set of values for a few style plugin options.
To do so, you need to add the proper entries to your settings.php file.

@code
// Custom options for Views Fluid Grid style plugin.
$conf['views_fluid_grid_plugin_style_widths']  = array(100, 150, 180, 200, 250, 300, 350, 400, 450, 500);
$conf['views_fluid_grid_plugin_style_heights'] = array(100, 150, 200, 250, 300, 350, 400, 450, 500);
$conf['views_fluid_grid_plugin_style_margins'] = array('0', '2px', '4px', '6px', '8px', '10px', '0.2em', '0.5em', '0.8em', '1em', '1.2em', '1.5em', '1.8em', '2em');
@endcode

You can add more items to any of these variables to suit your needs. Then, you
also need to provide the proper CSS classes. See the stylesheets shipped with
this module to find out how these values match CSS classes. See examples for
classes used for width and height in css/views_fluid_grid.size.css.

Note that dots in $conf['views_fluid_grid_plugin_style_margins'] will be
converted to dashes. See examples in css/views_fluid_grid.advanced.css.

Examples:

@code
/* This class is used for width 120. */
ul.views-fluid-grid-items-width-120 li.views-fluid-grid-item { width: 120px; }

/* This class is used for horizontal margin 0.6em. */
ul.views-fluid-grid-items-h-margin-0-6em li.views-fluid-grid-item { margin-left: 0.6em; margin-right: 0.6em; }
@endcode
