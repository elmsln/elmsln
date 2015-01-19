INTRODUCTION
------------
The media recorder module provides a HTML5 audio recorder with flash fallback,
for use with the media module.

REQUIREMENTS
------------
 * Media module - https://drupal.org/project/media
 * Libraries module - https://drupal.org/project/libraries
 * RecorderJS library - https://github.com/mattdiamond/Recorderjs
 * Recorder.js library - https://github.com/jwagener/recorder.js
 * SWFObject library - http://code.google.com/p/swfobject

INSTALLATION
------------
** Use the drush command 'drush mrdl' to automatically download the libraries.

1. Install the RecorderJS library in sites/all/libraries. The recorder.js file
   should be located at sites/all/libraries/Recorderjs/recorder.js.

2. Install the SWFObject & flash recorder.js libraries in sites/all/libraries. The
   swfobject.js file should be at sites/all/libraries/swfobject/swfobject.js,
   and recorder.js should be at sites/all/libraries/recorder.js/recorder.js.

3. Install dependencies and media recorder module as per:
   https://drupal.org/documentation/install/modules-themes/modules-7

4. Visit the media recorder configuration page to set file path,
   etc, at admin/config/media/mediarecorder.

CREDITS
-------
Current maintainers are:
 * Norman Kerr (kenianbei) - https://drupal.org/user/778980

This project has been sponsored by:
 * Yamada Language Center - https://babel.uoregon.edu
