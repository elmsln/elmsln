##Command Line
There are two commandline interfaces for ELMSLN, one specific to Drupal and one specific to elmsln.

###Drush
Drush is a commandline version of Drupal used to automate almost everything in the Drupal universe. Drush + Bash + Crontab is effectively how a lot of the automation in elmsln is able to build sites, add users, enable modules, and know where everything is.

The system automatically setsup drush with several drush plugins including registry rebuild, drush recipes, uuid rebuild, drush entity cache loader, and drush entity field query among others. These settings can be refreshed from `leafy`, the elmsln command line agent.

To use drush or see the options available to it type `drush help`. `drush sa` will give you a list of available site aliases. elmsln has a series of alias files that automatically update themselves based on new options / sites that can be commands run against them.

### Drush Aliases

There are several alias types you can issue commands against for shortcuts. these are:
- `@elmsln` - Commands issued against this will run against ALL sites found in this copy of elmsln. This can be useful for global calls like registry rebuild, cache clearing, or cache loading (`drush @elmsln ecl node --y`).
- `@network.{name}` - This will target all systems in a specific course network. In the example of `@network.sing100` this might run the command against `@studio.sing100`,`@courses.sing100`,`@blog.sing100` and `@discuss.sing100`. For example, if you wanted to add a user to all parts of a network.
- `@{stack}-all` This lets you run a command against everything found for a certain type of tool. For example, `drush @courses-all en views_ui --y` would enable views UI for all courses that are found.
- `@{stack}.{name}` - This lets you run a command against 1 site. For example, `drush @courses.sing100 en context_ui --y` would enable context UI just for the courses.elmsln.local/sing100 site.

###Leafy
Leafy is a commandline version of elmsln to do all kind of background / system admin style tasks but in a consistent and simplified way. To access leafy simply type `leafy` anywhere on a deployment of elmsln and it will load up some simple statistics about your instance.

![Leafy from the commandline](https://cloud.githubusercontent.com/assets/329735/12537867/88c59480-c298-11e5-8979-3f4bde75c45f.png)

From here you can perform tasks like upgrading elmsln, applying server level patches needed to keep on version, refresh you user's plugins, fix potential permissions issues and more. These options have descriptions of what they are going to do and each of them triggers a bash script in `/var/www/elmsln/scripts/` usually in install, utilities or upgrade directories.
