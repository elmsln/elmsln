

Basic Info
----------

The base theme provides many resources to all subthemes including templates,
layout CSS, base CSS helper, template overrides, function overrides and theme
settings. You should not edit this theme - its only job is to provide resources
to subthemes.



Templates and Theme Functions
-----------------------------

All templates are in:

  ~/at_core/templates/

If you need to modify a template OR theme function for your subtheme copy and
paste the template or function into your subtheme and clear your sites cache.

Its worth reviewing many of the templates - especially block and region tpl files
because these are quite different to Drupal cores templates and use preprocess
and process functions to build most of the markup.

All theme function overrides are in:

  ~/at_core/inc/theme.inc



Preprocess and Process Functions
--------------------------------

AT Core makes heavy use of these functions, they can be found respectively in:

  ~/at_core/inc/preprocess.inc
  ~/at_core/inc/process.inc



Alters
------

Drupal 7 allows themes to run many alters, AT Core takes advantage of this, see:

  ~/at_core/inc/alters.inc



Layout System
-------------

Adaptivetheme uses a pluggable layout. There are two types of layout plugins:

  - AT Core Page Layout plugins
  - Panels plugins

Both are responsive and can be configured via the theme settings on your themes
appearace configuration page.

You can define new layout plugins in your subtheme - please the info file in
adaptivetheme_subtheme and detailed docs on how to build plugins in the
following files:

page layouts: at_core/layouts/core/the three_col_grail/the three_col_grail.inc

panels: at_core/layouts/panels/five_5x20/five_5x20.inc



Gpanels
-------

Gpanels are multi-column layout snippets for displaying blocks in vertical columns
that you can drop into your subtheme. For example you may want a 4 column footer,
or a 3 column panel above your main content. Gpanels makes this as easy as copy
and paste.

See the README in the gpanels directory for instructions.

NOTE: Gpanels use the exact same markup and CSS as the Panels module plugins, so
they will respond to the same theme settings you set for Panels. See below.



Panels module
-------------

Like all Gpanels the Panels module layouts are all responsive - simply enable
this theme, go to Panels and start building your pages.

All the Panels layouts will load automatically inside Panels - they are called
AT Responsive Panels. Only AT Responsive Panels are responsive, the normal
Panels layout or other panels layouts may not be and will not respond.

To set alternative layouts for each mobile device group goto the theme settings
for your theme and configure them under the "Gpanels and Panels" tab.

NOTE: if you do not have Panels installed you will not see anything to configure,
unless your theme has some Gpanels - AT Core detects if Panels module is enabled
and what Gpanels are being used by your sub-theme and only shows you the options
for what you are actually using in your theme/site.




Theme Settings
--------------

The base theme provides the core layout settings that provide support for
mobile devices and standard desktop and laptop layouts.

Additionally you will find many settings for Polyfills, Mobile metatags, CSS and
helpful debugging features.

You do not need to add these to your subtheme - it will inherit them
automatically from the base theme.



Extensions
----------

Adaptivetheme ships with many hidden options and features - these are tucked
away in a group of settings called "Extensions". To enable these extensions see:

  - Layout & General Settings > Extensions

There are additional features and options for Fonts, Heading and title styles,
Image alignment and captions, breadcrumbs, login block setting, Apple touch
icons, many options for overrideing markup and even a way to enable a
page.tpl.php template that uses 100% width wrappers for designs that need this.

Additionally there is an extension that allows end users to paste in CSS - you
don't need to create an entire sub-theme to make small changes.




CSS Classes
-----------

Adaptivetheme removes many standard CSS classes from the Drupals output - we do
this to clean up the markup because most times these classes are never used. You
can add these back (and additional useful classes) using the theme settings for
CSS classes. You must enable "Extensions" first to do this.

Any problems please post an issue in the Adaptivethemes issue queue on Drupal.org:
http://drupal.org/project/issues/adaptivetheme

aintainer:
* Jeff Burnz http://drupal.org/user/61393




