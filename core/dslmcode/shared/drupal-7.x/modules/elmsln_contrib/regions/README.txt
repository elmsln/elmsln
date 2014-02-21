ELMS: Regions
Development Sponsored by The Pennsylvania State University
The ELMS project name is Copyright (C) 2008-2014  The Pennsylvania State University

Bryan Ollendyke
bto108@psu.edu

12 Borland
University Park,  PA 16802

***** USAGE *****
This is intended to make it easier to define new regions and implement js / css files.  It provides no css / js by itself but helps in the reserving of name spaces of the regions so that they don't conflict with other css loaded on the page.

For example usage see elms_nav_right or review the API in regions.api.php which is very simple as this module does most of the heavily lifting in region creation.  Basic order of operations:
- Make a module based on the API
- Activate the module
- Go to block form or contexts and add blocks / boxes to the region

Because the API is so lightweight it will be easy to include reusable regions in features.  Here are some examples where you could use this with a feature:
-Add an image gallery and image node type where the images will be associated to image galleries via a CCK reference field.
-Make a view for displaying the gallery in a block
-Use context to tell the block from the view to display on the node type you want
-Style with CSS / JS then package it up as a Feature

Another good usage could be a standard contact form / block that's accessible from one of the edges of the screen and is consistent across various sites.  Feedback forms could also be tucked away in this manner and globally shared.

***** Notes *****
This module was inspired by Appbar and draws upon successes in that module in terms of region definition.
