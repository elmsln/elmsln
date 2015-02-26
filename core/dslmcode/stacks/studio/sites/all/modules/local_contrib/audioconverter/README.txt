AUDIOCONVERTER.MODULE
---------------------

This module converts audio files from supported CCK fields (AudioField, AudioRecorderField) to the mp3 format using FFMPEG. It also implements file conversion via SOX Utility, but that is currently not fully supported.


Requirements
------------

No additional modules need to be installed.


Install instructions
--------------------

1. Extract Audio Converter to your sites/all/modules directory. 

2. Download, extract and enable AudioField and/or AudioRecorderField modules.

3. Install FFMPEG (see below for detailed instructions)

4. Go to /admin/config/media/audio-convert and choose which audio fields are to be converted, when the conversion should happen and what to do with the converted files. Individual field configurations might be done by going to Content Type -> Manage Fields -> Choose a field -> Configure

5. Upon the next cron job, new non-mp3 files from those fields will be converted to mp3.   

Note: Files are converted to mp3 on cron job unless the "Audio convert on Node Submit" option is enabled.


FFMPEG installation
-------------------

Linux instructions:

1. Most of the official Linux FFMPEG packages do not offer support for MP3. Specific instructions on how to install FFMPEG with MP3 support can be found here: http://ubuntuforums.org/showthread.php?t=1117283 and here: http://drupal.org/node/237072

2. After installation, go to /admin/config/media/audio-convert and enter the full path to the new FFMPEG program. Example: /usr/bin/ffmpeg


Windows instructions:

1. Download latest FFMPEG build from http://ffmpeg.arrozcru.org/autobuilds/

2. Extract it to any folder. 

3. Go to /admin/config/media/audio-convert and enter the full path to the new ffmpeg.exe program. Example: C:\wamp\apps\ffmpeg.exe


Troubleshooting:

Configuring and installing FFMPEG in a web server environment might be pretty difficult. In order to help you troubleshoot the transcoding process, the audioconverter.module puts debugging informations on the Drupal logs. Have a look at them if you are experiencing problems with transcoding.  You might also try to rerun your command on a command shell in order understand what is going wrong.


AudioConverter API
-----------------
It is possible to extend AudioConverter support to other audio-centric CCK modules. You can do so by implementing hook_audioconverter_allowed_fields(), which returns the name of CCK widget.


---
The AudioConverter module has been originally developed by Leo Burd and Tamer Zoubi under the sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).



