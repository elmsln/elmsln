ELMSLN Upgrades

Often times, instead of authoring upgrade hooks in distributions, ELMSLN utilizes a drush plugin called drush_recipes and specifically the drup command to further automate upgrades. This allows for the creation of upgrades based on files being named appropriately.

For example:
d7_elmsln_courses-all_1390936501.drecipe
d7_elmsln_courses-all_1630936501.drecipe
d7_elmsln_courses-all_1930936501.drecipe
d7_elmsln_online_1630936501.drecipe

could be the files included in this directory structure (spiders so location doesn’t
matter). the following call can be run (from the elmsln-upgrade.sh script):

drush @online drup d7_elmsln_online /var/www/elmsln/scripts/upgrade/drush_recipes —y

which will find all of the recipes above, but realize that it should only be looking
to execute the d7_elmsln_online_1630936501.drecipe named file. It will then run this recipe against
@online and then store a record in the online website to indicate that it previously ran
the file in question. That way if future files are added, they can more easily be processed.

Another example:
drush @courses-all drup d7_elmsln_courses-all /var/www/elmsln/scripts/upgrade/drush_recipes —y

This similar command, will be able to discover:
d7_elmsln_courses-all_1630936501.drecipe
d7_elmsln_courses-all_1830936501.drecipe
d7_elmsln_courses-all_1930936501.drecipe
