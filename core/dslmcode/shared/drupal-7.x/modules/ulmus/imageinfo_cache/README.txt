
----------------------------------
IMAGEINFO CACHE MODULE
----------------------------------


CONTENTS OF THIS FILE
---------------------

 * Features & benefits
 * Configuration
 * Hooks


FEATURES & BENEFITS
-------------------

Imageinfo cache features:
 * Generation of selected image styles right after an image is uploaded.
 * Will also run the generation code upon node save.
 * If the HTTPRL module is installed, generation logic will work in the
   background. http://drupal.org/project/httprl/
 * Drush integration. Can do bulk image style generation.


CONFIGURATION
-------------

Settings page is located at: admin/config/media/imageinfo_cache


HOOKS
-----

 * hook_imageinfo_cache_detect_image_widget_alter - Allow other widget types to
   be pre-generated in imageinfo_cache.
