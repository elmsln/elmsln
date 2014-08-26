
CSS Embedded Images for Drupal 7
==================================

The CSS Embedded Images module for Drupal 7 will replace image URLs in
aggregated CSS files with data URI schemes when CSS optimization is enabled.
This can greatly reduce the number of HTTP requests required to load your
pages in browsers that support embedded images in CSS:

 * Firefox 2+
 * Safari
 * Google Chrome
 * Opera 7.2+
 * Internet Explorer 8+


Installation
------------

 1) Copy the CSS Embedded Images module to sites/all/modules.
 
 2) Enable it in admin/modules.
 
 3) Enable CSS Optimization in admin/config/development/performance.
 
 4) See that your pages now include aggregated CSS files ending with
    ".emimage.css", and those contain embedded images.
