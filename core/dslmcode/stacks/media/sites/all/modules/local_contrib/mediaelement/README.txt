Media Element
--------------------------------------------------------------------------------

Provides HTML5 video and audio elements using Mediaelement.js for HTML4 browsers.

Installation
--------------------------------------------------------------------------------

1. Download MediaElement from http://mediaelementjs.com/
2. Unzip into a libraries directory as supported by the libraries module with
   the name mediaelement (e.g., /sites/all/libraries/mediaelement).
3. Install the libraries and mediaelement modules.

Usage
--------------------------------------------------------------------------------

Set a file field or link field to use video (or audio) as its display formatter.
Or use the media module (http://drupal.org/project/media) if you want to have your
file field display images and video.

API
--------------------------------------------------------------------------------
This module supplies the MediaElement library as a Drupal library and has some
helper functions if you want to use it independently of fields. To add the
library into a page use the command:

drupal_add_library('mediaelement', 'mediaelement');

If you want to use the helper scripts include the script mediaelement.js included
with the module. You can do it using a command like:

drupal_add_js(drupal_get_path('module', 'mediaelement') . '/mediaelement.js');

Then you need to add settings for the script. They are a selector for jQuery and
settings. For example:

$settings = array('mediaelement' => array(
  '.class-name' => array(
    'controls' => TRUE,
    'opts' => array(), // This is the mediaelement scripts options.
  )
));
drupal_add_js($settings, 'setting');

For more details on the MediaElement API see http://mediaelementjs.com

Changelog
--------------------------------------------------------------------------------
7.x-1.0:
- #1026050 Fixed issue with Preprocessing problems.

7.x-1.0 Beta 3:
- Fixed bug where mediaelement js was having options passed in that were not its
  own and were causing the script to break.

7.x-1.0 Beta 2:
- Updated to MediaElement.js changes.
- Updated to Drupal API changes.

7.x-1.0 Beta 1:
- Added download media option.
- Added support to disable the controls.
- Added link.module support.
- Added configurable classes for each formatter settings. This will aid in
  custom themeing for each place a formatter is used.

7.x-1.x Alpha 1:
- Provide a global option for video and audio tags.
- Provide file field formatter for video and audio.
