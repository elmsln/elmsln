ELMSLN — Scripts — drush alias shortcuts

This is a drush auto-alias generator based on the specification for how
ELMSLN groups and stores its various service instances / Drupal sites.
You can run commands against series of sites more easily with commands like:

drush @courses-all cc all --y
To clear the cache against all sites that are on the courses service

It also allows things like:

drush @courses.test100 cron --y
To run cron against a single site in the courses instance.

There is a remoteconnect script with this that allows you to issue
these drush alias calls remotely via ssh. Install both  these scripts on your
local user/.drush directory