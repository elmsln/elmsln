CONTENTS OF THIS FILE
---------------------
   
 * Summary
 * Requirements
 * Recommended modules
 * Tracking features
 * Module integration
 * Installation
 * Configuration
 * Get involved
 * Maintainers
 * Credits


SUMMARY
-------

The Tin Can API project is a suite of modules that provide various points of 
integration with the Tin Can API/Experience API.  The module(s) can be used 
to track many different types of user interaction such as viewing nodes, 
clicking links and watching YouTube or Vimeo videos via the Media module.  
The Tin Can API module can also act as a framework to track custom statements.

The Tin Can API module has been tested and works with the SCORM Cloud LRS and
the Learning Locker.


REQUIREMENTS
------------

This module requires the following modules:
 * Libraries (https://drupal.org/project/libraries)


RECOMMENDED MODULES
-------------------

 * Token (https://www.drupal.org/project/token):
   When enabled, tokens may be used to specify the statement Actor Name.


TRACKING FEATURES
-----------------

 * Node views (content type and view mode selection)
 * External link clicks
 * Link clicks based on file extensions
 * User creation and updates
 * Video player interaction (play, pause, stop, skip) for YouTube and Vimeo 
   videos via the Media module
 * Quiz interaction (answering questions and quiz completion) via the Quiz 
   module


MODULE INTEGRATION
------------------

 * Media
 * Quiz


INSTALLATION
------------

 * Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.

 * Enable and configure one or more of the tracking sub-modules.


CONFIGURATION
-------------

    1) Navigate to the Tin Can API configuration page 
       (http://www.example.com/admin/config/services/tincanapi) and enter your
       SCORM Cloud LRS or Learning Locker API credentials.

    2) Enable or disable tracking features.


GET INVOLVED
------------

Suggestions, bugs, and patches can be posted in the issue queue.  If you 
would like your module to be included in the Tin Can API package please create 
a feature request.


MAINTAINERS
-----------

 * Devan Chase  (devan.chase)
 * Nikos Verschore (nve)


CREDITS
-------

Development for this project is sponsored by iMinds (http://www.iminds.be).
