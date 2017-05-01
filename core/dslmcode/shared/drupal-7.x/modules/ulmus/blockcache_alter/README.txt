Block cache alter
------------------------
Requires Drupal 7

Author: Kristof De Jaeger - http://drupal.org/user/107403
Sponsored by One Agency - http://www.one-agency.be

Overview:
--------
Alter cache settings per block. Cache settings per block are now set in code,
but if you don't like the default - usually none - you can now easily change this
per block on the block configuration page in a fieldset called 'Cache settings'.
Install this to speed up block rendering for authenticated users.

Block cache is disabled if any module implements node_grants. This however can
be changed in settings.php by setting the variable
'block_cache_bypass_node_grants' to TRUE.

Caution: Only enable this if no block is configured for caching that shows nodes
         that need to be access filtered!

The module also comes with a core patch you can apply to the block module
which will make block caching smarter. You'll be able to set expire times
per block. For the advanced expiration features of the Drupal 6 version of
this module, use the contributed 'expire' module instead.

- blockcache_alter_core_patch.patch

Notes:
1: You can run this module *without* applying a patch, you simply don't get
that much options for refreshing a block.
2: If you apply a patch, the module must be enabled at all times. Running without
the patches gives you the option to turn off the module after you made your changes.

Installation:
-------------
1. Place this module directory in your modules folder (this will
   usually be "sites/all/modules/contrib/").
2. Go to "Admin -> Modules" and enable the module.

3. Apply the core patch if you like. If you patch, copy the patchfile to
   modules/block and run the following command:
   
   patch -p0 < filename.
   
   To reverse the patch, simple run following command:
   
   patch -R -p0 < filename

Configuration:
--------------
Go to "Admin -> Configuration -> Development > Performance" where you have 2 options

- Core patch: toggle this checkbox if you have applied the core patch.
  Additional options for refreshing the block will appear in the caching
  fieldset on the block configuration page. Note: If you didn't apply a core patch,
  these additional settings simply won't have any effect.
- Debug: Apply this only during testing and development. It will show you
  messages when a block is refreshed.
- Cache blocks for user 1: Use with caution! Allows to cache blocks for user 1,
  which is special cased as a 'super user' in Drupal.

Support:
--------
Please use the issue queue available at http://drupal.org/project/blockcache_alter to
file support and feature requests, bugs etc. Be as descriptive as you can.

Last updated:
------------
