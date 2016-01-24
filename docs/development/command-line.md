##Command Line
There are two commandline interfaces for ELMSLN, one specific to Drupal and one specific to elmsln.

###Drush
Drush is a commandline version of Drupal used to automate almost everything in the Drupal universe. Drush + Bash + Crontab is effectively how a lot of the automation in elmsln is able to build sites, add users, enable modules, and know where everything is.

The system automatically setsup drush with several drush plugins including registry rebuild, drush recipes, uuid rebuild, drush entity cache loader, and drush entity field query among others. These settings can be refreshed from `leafy`, the elmsln command line agent.

###Leafy
Leafy is a commandline version of elmsln to do all kind of background / system admin style tasks but in a consistent and simplified way. To access leafy simply type `leafy` anywhere on a deployment of elmsln and it will load up some simple statistics about your instance.

![Leafy from the commandline](https://cloud.githubusercontent.com/assets/329735/12537867/88c59480-c298-11e5-8979-3f4bde75c45f.png)

From here you can perform tasks like upgrading elmsln, applying server level patches needed to keep on version, refresh you user's plugins, fix potential permissions issues and more. These options have descriptions of what they are going to do and each of them triggers a bash script in `/var/www/elmsln/scripts/` usually in install, utilities or upgrade directories.
