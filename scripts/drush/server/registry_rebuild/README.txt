Registry Rebuild
----------------

THIS IS NOT A MODULE. PLEASE READ BELOW.

There are times in Drupal 7+ when the registry gets hopelessly hosed and you
need to rebuild the registry (a list of PHP classes and the files they go with).
Sometimes, though, you can't do this regular cache-clear activity because some
class is required when the system is trying to bootstrap. 

When would you need Registry Rebuild?
-------------------------------------

You might get something like:

PHP Fatal error:  Class 'EntityAPIControllerExportable' not found in 
...sites/all/modules/rules/includes/rules.core.inc on line 11

If this happens when you're trying to run update.php, and happens when you're 
trying to clear your cache, well, you have some trouble. That's what Registry
Rebuild is for.

When would you *not* need Registry Rebuild?
-------------------------------------------
If you can access any page, or install a module, or run update.php, you almost
certainly don't need Registry Rebuild.

You can run registry_rebuild with or without drush. See below.

How To Use It (with drush)
--------------------------
1. Make a backup of your database.
2. drush dl registry_rebuild will download the current recommended version and
   place it in your .drush folder. Or you can copy the directory 
   registry_rebuild from this package into your
   ~/.drush folder (or other appropriate folder)
3. Run "drush rr"

How To Use It (without drush)
-----------------------------
This isn't really a module, but it's just packaged as a module to make it so 
it's easy to find and people can download it as a package.

1. Make a backup of your database.
2. Download and install as usual where you put modules (sites/all/modules is 
   most common)
3. You don't need to enable it. If you were able to enable it you wouldn't 
   need it. See above.
4. Either run it from the command line:
   cd sites/all/modules/registry_rebuild
   php registry_rebuild.php
   OR
   point your web browser to 
   http://example.com/sites/all/modules/registry_rebuild/registry_rebuild.php
   Changing "example.com" to your own site's base URL of course.
4. You should see something like this:

DRUPAL_ROOT is /home/rfay/workspace/commerce.
There were 631 files in the registry before and 508 files now.
If you don't see any crazy fatal errors, your registry has been rebuilt. You will probably want to flush your caches now.

5. Hopefully you'll now be able to go about your affairs in peace, updating,
   clearing cache, etc.
   
This package comes with no guarantee explicit or implicit.

There's no reason it should do any harm to your install. But there can be lots
of things wrong with a system, and the registry problem is not the fix for
everything.

