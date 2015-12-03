
CONTENTS OF THIS FILE
---------------------

 * Author
 * Description
 * Installation
 * Usage
 * Todo

AUTHOR
------
stred (http://drupal.org/user/956840)

DESCRIPTION
-----------
This module provides a field to upload video directly to YouTube and a formatter
 to display the videos. It uses the Google api php client library to interface the 
 YouTube API
 and implements the "browser upload method" so the file never hits the Drupal
 file system. It saves storage and bandwidth and your users don't need a 
 YouTube Account. 
 
REQUIREMENTS
------------
Google api php client library
  https://github.com/google/google-api-php-client
A defined Google Application
  https://console.developers.google.com/project
Google CORS Upload file
  https://raw.githubusercontent.com/youtube/api-samples/master/javascript/cors_upload.js


INSTALLATION
------------
Automatic

using drush en -y youtube_uploader will download/enable the module and the libraries.
the libraries will be created on sites/all/libraries

use drush ytu-libraries to only (re)install them. 
Pass the directory as parameter to use a different libraries folder 
drush ytu-libraries sites/mysite/libraries

Manual

1. Enable the module as usual in Administer -> Site building -> Modules.

2. Install 
- the Google API php client library
  download it here https://github.com/google/google-api-php-client
  Extract it so the path <br />sites/all/libraries/google-api-php-client/src/Google/autoload.php
  or sites/[domain]/libraries/google-api-php-client/src/Google/autoload.php is available.
  
- the Google CORS Upload file
  download it here https://raw.githubusercontent.com/youtube/api-samples/master/javascript/cors_upload.js
  Extract it so the path <br />sites/all/libraries/google-api-cors-upload/cors_upload.js
  or sites/[domain]/libraries/google-api-cors-upload/cors_upload.js is available.
  
CONFIGURATION
-------------
Configure the Google App that will hold the video on the module 
configuration page (admin/config/media/youtube_uploader).

1. To get credentials,
 go to https://console.developers.google.com/project. Next in "APIs & auth" -> "Credentials" -> "OAuth".
 Click "Create new Client ID" and then under "Application Type" select "Web Application".
For the redirect uri use http://yourdomain/youtube_uploader/oauth2callback

2. You will next have to authorise your application (by clicking on a link on the module settings page).
This should be done only one time. The required token will be automatically refreshed for any additional request.


USAGE
-----
You can *optionally* set YouTube options for the whole site on the module 
configuration page (admin/config/media/YouTube_uploader)
or per field on each field settings.
Options are
- automatic delete the video on YouTube when the video is removed on Drupal
- set the visibility of the video on YouTube (public or unlisted)
- a YouTube category
- a default description
- default tag(s)

You can configure the formatter to display 
  the video at a predefined or custom size
  the default thumbnail following an image preset with or without the title
  
Images for the thumbnails are stored in a YouTube_upload file directory.

When the video first is uploaded, the default thumbnail doesn't exist 
on YouTube 
(YouTube needs time to parse the video and generate the thumb) 
so you can click the link "refresh data from YouTube" 
(this link will refresh the title as well) or wait and the module will 
automatically fetch the thumbnail next time it will be displayed 
on the frontend or the backend.

Users with proper permission "Edit video on YouTube" will see a link to the
 corresponding YouTube edit video page. the permission "Upload a video" allows user
 to upload a file to YouTube. 

 The module has been tested to work with the views module
 
CREDITS
-------
To YouTube module for the formatter http://drupal.org/project/youtube
To video_upload module for ideas on the code and options 
http://drupal.org/project/video_upload
 
 TODO
 ----

 Re-use video previously uploaded 
 (probably with the help of the FileField Sources module)
 
