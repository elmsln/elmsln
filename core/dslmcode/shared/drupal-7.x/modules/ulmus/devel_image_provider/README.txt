DEVEL IMAGE PROVIDER
--------------------

Allow choose image provider in content generation.


Installation
------------

- Is required this patch for Devel:
  
  http://drupal.org/files/issues/1238344-allow_external_images-4.patch
  
  More information here: http://drupal.org/node/1134986#comment-4512820

- Install module as usual.

Use
---

- Inside Admin > Configuration > Development, you can set Devel Generate Image
  Providers settings.
  
  Developers can add new providers through specific module.
  
  These modules are provided out of the box:
  
  lorempixum.com
  flickholdr.com
  placekitten.com
    
- Generate content with devel generate as usual.


Thanks
------
To ipwa, marvil07, akobashikawa and Drupal Perú community for the idea and
support.
