-- SUMMARY --

The File module of Drupal 7 enables you to select only one file at a time
which can be very time consuming in case of many files. This module uses the
'multiple' attribute of html5 to overcome this problem and presents a widget 
called 'Multiple' that can be used with fields of type File.

Using this Multiple widget in case of File fields it is possible to select
more files at a time, which can be a big time saver. 

-- REQUIREMENTS --

The core File module.

-- INSTRUCTIONS --

1. Enable the module.
2. Add a 'file' field to a content type and select the widget 'Multiple'.
3. Done

-- IMAGE FIELD --

For an image field see Muliupload Imagefield Widget at 
http://drupal.org/sandbox/czigor/1115368, which depends on this module.

-- BROWSERS --

Known browsers to work with: Firefox 3.6, Chromium 10, Opera 11.01.
As no version of IE supports the 'multiple' html5 attribute, I'm pretty sure 
that it does not work with IE.

-- CONTACT -- 

Current maintainer: 
Czövek András (czigor) - http://drupal.org/user/826222
