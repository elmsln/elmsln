Version - 1.0-DRAFT-1
Drupal Galaxy
==============
A distribution for managing the deployment of distributions — a system made up of systems, a galaxy.

FAQ
==============
###Q. Why doesn’t this look like Drupal?
Because it’s Drupal and other packages setup in an optimal format for a network of deployed distributions. This as an enterprise Drupal based application that is more "Drupal inside" then Drupal proper. Everything is still done in a completely core compliant way, it's just structured to maximize needed efficiencies of a heavily networked ecosystem.

Everything is setup in a manner that has flexibility, sustainability and long term system growth in mind. It’s using a patched version of a drush extension called DSLM to help manage the symlinks between items but it’s heavily symlink. This helps optimize APC as well as make it maintainable for a single person to manage 100s of sites with similar code pushes.

###Q. Where can I add new modules / themes?
All changes should be made inside the config directory in a location that aligns with its counterpart in the core directory.  For example, to add a new module for use in all sites, you’ll want to place it in galaxy/config/shared/drupal-7.x/modules.  This is the same area for themes and libraries.  Note: libraries support may be buggy because of how those are symlink over.

There’s also a settings/shared_settings.php file that has settings you want applied to all sites by default.  This is where your environmental staging overrides can go, or you can switch the cache bins used by default.  The version that ships with this has APC and file cache support automatically setup and tuned though you can disable these if you don’t have those.

Also make sure you never place an upgraded module in a different location from its default (such as updating views module by placing it in your config directory).  This will effectively WSOD / brick your site until you run drush rr against the sites that bricked.

###Q. Where should I point addresses?
The domains directory is structured in the optimal way for managing sites.  The domains directory is ignored below the initial directories inside of it, meaning that your sites that get written here automatically won’t be pushed through git or updated.  If you remove directories or change the way sites are managed in anyway inside this location, you’ll need to add that area to your .gitignore (or stop using the github version).

You can use this as a starting point and self manage from there but sticking as closely as possible to the structure of Galaxy will help ensure upgrades down the road take correctly.
