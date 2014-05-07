CSS Injector
============
Allows administrators to inject CSS into the page output based on configurable
rules. It's useful for adding simple CSS tweaks without modifying a site's
official theme -- for example, a 'nighttime' color scheme could be added during
certain hours. The CSS is added using Drupal's standard drupal_add_css()
function and respects page caching, etc.

This module is definitely not a replacement for full-fledged theming, but it
provides site administrators with a quick and easy way of tweaking things
without diving into full-fledged theme hacking.

The rules provided by CSS Injector typically are loaded last, even after the
theme CSS, although another module could override these.

