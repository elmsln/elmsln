README for the Image styleds admin Drupal module
------------------------------------------------

Project page: https://drupal.org/project/imagecache_actions

Current and past maintainers for Image styles admin:
- fietserwin (https://drupal.org/user/750928)


Release notes for 7.x-1.x-dev
-----------------------------
- Clear the (menu) cache after installing or updating.


Introduction
------------
The Image style admin module extends the administrative interface for image
styles by providing additional features.

Currently a duplicate, import and export image style feature are implemented.
More features may be added in the future. These features typically allow you to
more easily handle image styles. It allows us to more easily set up
a test/showcase sute of styles. Finally, it allows everybody to test D8 image
module features in real life.

This module is not a replacement for the features module
(https://drupal.org/project/features). If you are serious about configuration
management and want to distribute styles to other systems, use features.

Use this module for 1 time export/imports between different sites, "copy &
paste" reuse within a site, and when reporting issues to the imagecache_actions
issue queue.


TODO
----
Solving errors in the core image handling?
- [#1554074]: scale does not work with imagemagick when dimensions are unknown?
