ELMSLN comes with a function to organically find and upgrade your sites whenever new code is released. You as the developer still choose to run the update and you absolutely should do testing before executing one of these upgrades as they are extensive. The command to run though is
`bash /var/www/elmsln/scripts/upgrade/elmsln-upgrade-system.sh`

This will prompt you for a branch and to verify you want to run the update. It will then update its own code, and then start to apply needed drupal updates to all sites it finds to work against the version of the code just pulled down.

If you don't want it to upgrade its own code and instead apply updates to systems already on the server, you can issue:
`bash /var/www/elmsln/scripts/upgrade/elmsln-upgrade-sites.sh`

Though before doing so you should always refresh your drush config with the following (if not running the mega upgrade system command):
`bash /var/www/elmsln/scripts/upgrade/refresh-drush-config.sh`