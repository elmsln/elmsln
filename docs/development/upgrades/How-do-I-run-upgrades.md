ELMSLN comes with a function to organically find and upgrade your sites whenever new code is released. You as the developer still choose to run the update and you absolutely should do testing before executing one of these upgrades as they are extensive. The command to run though is available via leafy, our command line agent.
`leafy`

Look through the options available and select `upgrade the ELMSLN code base and system`. This will prompt you for a branch and to verify you want to run the update. It will then update its own code, and then start to apply needed drupal updates to all sites it finds to work against the version of the code just pulled down.

If you don't want it to upgrade its own code and instead apply updates to systems already on the server, you can issue the command below it in the list which will just upgrade the sites and not run through the code update.

Though before doing so you should always refresh your drush config with the following (if not running the mega upgrade system command):
`bash /var/www/elmsln/scripts/upgrade/refresh-drush-config.sh`

## Apply server upgrades
Server level upgrades run through advanced bash scripts that bring you on par with the rest of what we’re running. These updates are different from the system upgrade in that it’s upgrading the drupal sites. To run these bash based updates to ensure you’re getting the latest infrastructure updates select `apply server level upgrades (can not be undone)`.