README.txt
==========

INTRODUCTION
------------
The Voice Commander module automatically makes voice commands
for navigating the entire menu system of your Drupal site, using
Chrome Web Speech API. You can choose which menu to work, than
just press Ctrl+Alt and start speak. Also, you can turn on voice
commands on mobile device.


 * For a full description of the module, visit the project page:
   https://www.drupal.org/project/voicecommander


REQUIREMENTS
------------
This module requires the following modules:
 * Libraries API (https://drupal.org/project/libraries)

INSTALLATION
------------
 * Install as you would normally install a contributed Drupal module. See:
   https://www.drupal.org/project/voicecommander for
   further information.
 * Run <drush vc> or manual install annyang plugin to your libraries folder
   (e.g. /sites/default/libraries). Check drupal status reports in any concern.
   URL for download annyang plugin:
   https://github.com/Voicecommander/annyang/archive/master.zip
 * Go to /admin/config/user-interface/voice-commander and configured VC
 * Hold Ctrl+Alt key for starting recognition on desktop. Hold left bottom
   corner on mobile device for run voice commands. Enjoy it!

CONFIGURATION
-------------
 * Configure user permissions in Administration >> Configuration >>
   User interface >> VoiceCommander:

   - Set Administartor command prefix for navigate in admin menu;
   - Select menus which you want to use;
   - Turn on or off recognition on mobile devices;

DEFAULT COMMANDS
----------------
 - Cache clear: 'drupal cache'
 - Management menu: '[Administrator command prefix] [Management menu item]',
     where [Administrator command prefix] is an option that set at
     /admin/config/user-interface/voice-commander and [Management menu item]
     is an any menu link from management menu
     /admin/structure/menu/manage/management

AUTHOR/MAINTAINER
-----------------
Current maintainers:
 * Yuriy Kostin - https://drupal.org/u/yuriy.kostin
 * Yaremiy Roman - https://drupal.org/u/andrdrx
 * Alexand Danilenko - https://drupal.org/u/danilenko_dn

SUPPORTING ORGANIZATION
-----------------------
This project supporting by:
 * Blink Reaction
   https://drupal.org/marketplace/blink-reaction

   Blink Reaction is a leader in Enterprise Drupal Development, delivering
   robust, high-performance websites for dynamic companies. Blink creates
   scalable and flexible web solutions that provide the best in customer
   experience and meet brand, marketing, and business goals.
