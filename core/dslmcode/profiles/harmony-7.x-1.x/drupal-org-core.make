api = 2
core = 7.x

; Drupal Core
projects[drupal][type] = core
projects[drupal][version] = 7.34

; Patch to allow install profile enabling to enable dependencies correctly.
projects[drupal][patch][1093420] = http://drupal.org/files/1093420-22.patch

; Patch to fix issue with PHP 5.5 and image issues.
projects[drupal][patch][2215369] = https://www.drupal.org/files/issues/php_5_5_imagerotate-2215369-35.patch

; Patch to skip extra calls to filesize for images.
projects[drupal][patch][2289493] = https://www.drupal.org/files/issues/drupal-2289493-3-image_get_info-filesize-D7.patch
