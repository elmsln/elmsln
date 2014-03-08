ELMSLN
==============
This is the entire ELMS Learning Network as a repository.  It includes installation instructions for getting it stood up on your server as well as multiple git repositories for optimal management downstream.

FAQ
==============
###Q. How can I get more involved?
A. The easiest way is to spin up the [ELMSLN Vagrant](http://github.com/btopro/elmsln-vagrant). Test, ask, jump in on the issue queues on github, drupal.org, twitter, email, PHONE or anywhere else that you can find pieces that will help build upon this work. We always welcome more issue reports.

###Q. Why doesn’t this look like Drupal?
A. Because it’s Drupal and other packages setup in an optimal format for a network of deployed distributions. This as an enterprise Drupal based application that is more "Drupal inside" then Drupal proper. Everything is still done in a completely core compliant way, it's just structured to maximize needed efficencies of a heavily networked ecosystem.

Everything is setup in a manner that has flexibility, sustainability and long term system growth in mind. It’s using a patched version of a drush extension called DSLM to help manage the symlinks between items but it’s heavily symlink. This helps optimize APC as well as make it maintainable for a single person to manage 100s of sites with similar code pushes.

###Q. Should I update Drupal modules?

A. Anything that’s included in the enclosed core directory should not be updated outside of the schedule of updating versions of the code from the github repository (unless you know what you are doing). There are a few projects patched so the best way to get projects upgraded to the latest version is to test it in a vagrant instance, report on it in an issue queue, and then let the ELMSLN community vet the module / theme upgrade.  Once this has happened then it will be rolled into the final package.

This is to ensure that all sites function properly after upgrades.  This package will be updated on versions once they are tested, any modules that you install in your config directory is on you to manage.  The general rule in Drupal is don’t hack core and the same is true with ELMSLN, don’t hack ELMSLN core; apply all your changes you want inside the config directory.

###Q. Where can I add new modules / themes?
A. All changes should be made inside the config directory in a location that aligns with its counterpart in the core directory.  For example, to add a new module for use in all sites, you’ll want to place it in elmsln/config/shared/drupal-7.x/modules.  This is the same area for themes and libraries.  Note: libraries support may be buggy because of how those are symlink over.

There’s also a settings/shared_settings.php file that has settings you want applied to all sites by default.  This is where your environmental staging overrides can go, or you can switch the cache bins used by default.  The version that ships with this has APC and file cache support automatically setup and tuned though you can disable these if you don’t have those.

Also make sure you never place an upgraded module in a different location from its default (such as updating views module by placing it in your config directory).  This will effectively WSOD / brick your site until you run drush rr against the sites that bricked. If you've run the elmsln-install.sh script included in this package, you'll have drush rr.

###Q. Where should I point addresses?
A. The domains directory is structured in the optimal way for managing sites.  The domains directory is ignored below the initial directories inside of it, meaning that your sites that get written here automatically won’t be pushed through git or updated.  If you remove directories or change the way sites are managed in anyway inside this location, you’ll need to add that area to your .gitignore (or stop using the github version).

You can use this as a starting point and self manage from there but sticking as closely as possible to the structure of ELMSLN will help ensure upgrades down the road take correctly.

###Q. When will there be a stable release?
A. Very soon, there has been substancial progress made towards a point release thanks to investment in the [ELMSLN Vagrant](http://github.com/btopro/elmsln-vagrant) installer.
