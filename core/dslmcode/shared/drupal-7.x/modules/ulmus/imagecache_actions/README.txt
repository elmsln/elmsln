README for the Imagecache Actions Drupal module
-----------------------------------------------

Project page: https://drupal.org/project/imagecache_actions

Current and past maintainers for Imagecache Actions:
- dman (https://drupal.org/user/33240)
- sidneyshan (https://drupal.org/user/652426)
- fietserwin (https://drupal.org/user/750928)


Release notes for 7.x-1.x-dev
-----------------------------
- Clear all caches after updating.


Release notes for 7.x-1.4
-------------------------
- This release supports image labels as introduced by Drupal 7.23.
- See CHANGELOG.txt for a full overview of changes.


Release notes for 7.x-1.1
-------------------------
- If you use the module:// notation anywhere in an image effect, you must now
  install the System Stream Wrapper module
  (https://drupal.org/project/system_stream_wrapper).
- Clear the cache after updating.


Release notes for 7.x-1.0
-------------------------
- Clear the (registry) cache after installing or updating to 7.x-1.0.
- If you use custom actions, run update.php.
- If you use custom actions, be sure to enable the 'PHP filter' module and give
  image style editors that may create custom actions the 'use PHP for settings'
  permission. The module must also be enabled on image creation.
- If you use custom actions, please read the README.txt from that sub-module to
  find out about how information and resources are available to you. You will
  probably have to change your code snippets.
- If you use effects that use files (mask, overlays, underlays, text fonts),
  check the way they are specified. From 7.x-1.0 on, you have to specify the
  location using one of the schemes private://, public://, module:// or
  temporary://. If no scheme is specified, the file is searched for as is, thus
  relative to the current directory or as an absolute path.
- Effects that use the transparency layer (e.g. mask, rounded corners) do not
  automatically convert to PNG anymore. Use the "Change file format" for that.
- There's no upgrade from D6. You will have to recreate your styles manually.

Warning:
  Ongoing development in the area of e.g. making the effects more consistent,
  adding and/or removing parameters or redefining their meaning, might cause
  backward incompatibilities between future versions and the current version.
  Thus, we cannot and do not guarantee backwards compatibility or automatic
  upgrade paths for future versions.


Introduction
------------
The Imagecache Actions module provides a suite of additional image effects that
can be added to image styles. Image styles let you create derivations of images
by applying (a series of) effect(s) to it. Think of resizing, desaturating,
masking, etc.

Furthermore, imagecache_actions extends the administrative interface for image
styles by providing additional features. It does so in the "Image styles admin"
sub module.

The additional effects that Imagecache Actions provides include:
- Watermark: place a image with transparency anywhere over a source picture.
- Overlay: add photo-corners etc to the image
- Text overlay: add e.g. a copyright notice to your image.
- Color-shifting: colorize images.
- Brighten/Darken.
- Alpha blending: use a gray scale image to define the transparency layer of an
  image.
- Canvas manipulation: resize the canvas and add a background color or image.
- File Format switcher: if you need transparency in JPGs, make them PNG. If your
  PNG thumbnails are 30K each, save them as JPGs.
- Rounded corners.
- TODO: complete list, check short descriptions

These effects are grouped in sub-modules. Just enable the ones you want to use.
TODO: list sub-modules and their sets of effects.

Imagecache Actions supports both the GD toolkit from Drupal core and the
Imagemagick toolkit. However, please note that Imagemagick support is not yet
complete. Please file an issue if you encounter problems in using Imagemagick.


What is imagecache_action not?
------------------------------
Imagecache Actions does not provide a new UI or new menu items. It hooks into
the already existing image styles system (from Drupal core). See
https://drupal.org/documentation/modules/image for more information about
working with images.


A note about the name of this module
------------------------------------
Image styles are part of Drupal 7 core and are the successor of the Drupal 6
imagecache module. In Drupal 6 image styles were called (imagecache) presets and
the separate effects that made up a style were called (imagecache) actions. In
porting to D7, that name has not been changed (yet).


Which toolkit to use?
---------------------
Personally, I (fietserwin) prefer the imagemagick toolkit:
- It is better in anti-aliasing. Try to rotate an image using both toolkits and
  you will see what I mean.
- It does not execute in the PHP memory space, so is not restricted by the
  memory_limit PHP setting.
- The GD toolkit will, at least on my Windows configuration, keep the font file
  open after a text operation, so you cannot delete, move or rename it anymore.

On the other hand: the GD toolkit is always available (in the correct version),
whereas imagemagick is not always present on shared hosting or may be present in
an antique version that might give problems.

Please note that effects may give different results depending on the
toolkit used.

Please also note that a 3rd image toolkit exists:
  Imagick (https://www.drupal.org/project/imagick)
This toolkit uses the Imagick extension and thus does not call the ImageMagick
binaries directly. However our module does not implement the toolkit specific
parts for the effects we provide for the Imagick toolkit, but the Imagick
toolkit comes with its own set of effects that partly covers our effects. So,
depending on the effects you require it may be a replacement for both our module
and the Imagemagick module or the core GD toolkit.

Hard Dependencies
-----------------
- Image module from Drupal core

At least 1 of the available image toolkits:
- GD toolkit from Drupal core.
- Imagemagick toolkit: https://drupal.org/project/imagemagick.


Soft Dependencies
-----------------
- System stream wrapper (https://drupal.org/project/system_stream_wrapper)
- Remote stream wrapper (https://drupal.org/project/remote_stream_wrapper)
These modules provide additional stream wrappers. Especially the system stream
wrapper is very handy as it provides, among others, a module:// and theme://
wrapper.


Installing
----------
As usual.


Usage
-----
After enabling the module:
- Assure that the Image module from core is enabled.
- Configure your toolkit and its settings at admin/config/media/image-toolkit.
- Define image styles at admin/config/media/image-styles and add 1 or more
  effects as defined by this module
- Use the image styles via e.g. the formatters of image fields.


Upgrading from D6
-----------------
There's no upgrade path defined for sites upgrading from D6 to D7. This means
that you will have to manually redefine your D6 imagecache presets as D7 image
styles. Note that actually an upgrade path would have to be defined by the
imagecache module, not this imagecache actions module. However, as there is no
D7 version of imagecache that provides an upgrade, users may post an upgrade
function to the issue queue and we will incorporate it.


Backwards compatibility
-----------------------
Future releases will not be guaranteed to be backwards compatible. Implementing
Imagemagick support e.g. might give unforeseen problems that can only be solved
by changing the details of what an effect does. We will document these kind of
incompatibilities in the changelog and the release notes.


File form fields
----------------
A number of effects have a file form field where the editor can define a file
name to use. This can be e.g. for overlays, masks or fonts. The file name should
be defined using either:
- 1 of the (enabled) scheme's:
  * public://
  * private:// Preferred for site specific masks, overlays, etc, that do not
    need to be shared publicly.
  * temporary:// Unlikely to be useful, but supported anyway as all schemes are
    supported.
  * module:// Introduced by the system stream wrapper module and preferred for
    module provided resources.
  * theme:// idem.
  * profile:// idem.
  * library:// idem.
- A relative (to the current directory, probably Drupal root) or absolute path.


Support
-------
Via the issue queue of this project at Drupal.org.


Known problems
--------------
These are better documented in the issue queue, but might be listed here (as
well).

- Underlay does not work in imagemagick if the dimensions of both images are not
  equal. As a workaround first add a canvas effect with a fully transparent
  background.
- Underlay/overlay: keywords in the x and y offset fields do not work.
- Underlay does still display a message about Imagemagick not being supported.
- Brightness values outside the -250 .. 250 range are accepted.
- Check color fields that allow a transparency component or allow to be empty to
  specify fully transparent.

Known problems: Imagemagick
---------------------------
- Define canvas using offsets may bot work on older versions. We have an error
  report for version 6.5.4.7 (2009-07) (https://drupal.org/node/888644).
