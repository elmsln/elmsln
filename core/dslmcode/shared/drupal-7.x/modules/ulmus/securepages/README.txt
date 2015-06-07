
Configuration
------------------------------------------------------------------------------

Generally on test/development servers you do not have access to SSL, so 
generally you would like to disable secure pages on these systems.

To do this add the following to your settings.php

$conf['securepages_enable'] = 0;

Removal of SecurePages
------------------------------------------------------------------------------

In the case where your SSL mode has been disabled and you can no longer access
the administration section of your site to disable securepages you can do one
of the 2 following things.

  1. Use the above method to disable securepages.
  2. delete the secure pages module from your site.

If you can use the first option but if you can't edit your settings.php then
deleting it will not break your site, but will leave some variables that are
set by secure pages.