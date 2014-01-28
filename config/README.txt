ELMSLN Config

This is where all of your configuration that makes this deployment specific to your server should live.  This will contain all modules, themes, libraries, and install profiles you want to add to your Drupal sites. You also will manage your sites.php and settings.php / files directory for each site / service that’s created.

This is possible because of symlinks at the correct locations inside the core package that reference files and folders kept in config.  For example, when a new site is added automatically via crush-create-site, it will write to /elmsln/core/dslmcode/stacks/courses/sites/sites.php as well as courses/{group}/{name}/settings.php.  The sites.php and courses subdirectory inside the traditional drupal/sites folder are symlinked back into config.

By doing this, when the system writes these locations, they are kept in config which allows you to upgrade the core ELMSLN system, safely, without any possibility of losing your specific settings / configuration.  As long as you are always placing file changes and adding functionality through this direction, the core package should remain in sync with what’s available on github.