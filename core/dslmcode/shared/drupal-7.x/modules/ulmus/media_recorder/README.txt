INTRODUCTION
------------
The media recorder module provides a HTML5 audio recorder with flash fallback,
for use with the media module.

REQUIREMENTS
------------
 * Media module - https://drupal.org/project/media
 * Libraries module - https://drupal.org/project/libraries
 * Modernizr module - https://drupal.org/project/modernizr
 * Transliteration module - https://drupal.org/project/transliteration
 * RecorderJS library - https://github.com/mattdiamond/Recorderjs
 * SWFObject library - http://code.google.com/p/swfobject
 * WAMI recorder library - http://code.google.com/p/wami-recorder

INTEGRATION
-----------
 * MediaElement - https://drupal.org/project/mediaelement
   Replaces playback HTML5 audio element with mediaelement player.
 * Media: Youtube - https://drupal.org/project/media
   Adds an option to record using the Youtube Upload Widget.

INSTALLATION
------------
1. Install the RecorderJS library in sites/all/libraries. The recorder.js file
   should be located at sites/all/libraries/Recorderjs/recorder.js.

2. Install the SWFObject & Wami recorder libraries in sites/all/libraries. The
   swfobject.js file should be at sites/all/libraries/swfobject/swfobject.js,
   and recorder.js should be at sites/all/libraries/wami/recorder.js.

3. Install dependencies and media recorder module as per:
   https://drupal.org/documentation/install/modules-themes/modules-7

4. Visit the media recorder configuration page to set default audio, file path,
   etc, at admin/config/media/mediarecorder. If you want your default audio in
   the correct file path, set the path and save, then record the default audio.

CREDITS
-------
Current maintainers are:
 * Norman Kerr (kenianbei) - https://drupal.org/user/778980

This project has been sponsored by:
 * Yamada Language Center - https://babel.uoregon.edu
