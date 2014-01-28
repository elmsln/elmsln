Copyright (C) 2011  The Pennsylvania State University

Bryan Ollendyke
bto108@psu.edu

12 Borland
University Park,  PA 16802

***** USAGE *****
Install then add a context.  Select Variable Match, then write a name|value pair that you are trying to match.  Here's the description for how to use it from the module:

Map values as database variable|value. This will also accept variable|index:value in the case of arrays that are stored in the drupal variable table. %theme can be used to replace it with the current theme in use, accounting for og_theme

The use-case for building this was Spaces can override global settings based on Strongarm.  This module allows your contexts to dynamically react to minor global value overrides.  An example implementation is:

theme_%theme_settings|toggle_primary_links:0

This says "look at the active theme settings variable, then see if primary links are told not to render".  In this instance, the context will match and can display blocks or whatever it wants to.  In ELMS, this variable match allows you to toggle whether links display in the theme's primary links region or if a block should be rendered on the page (hence the if primary links are set to 0 do this).
