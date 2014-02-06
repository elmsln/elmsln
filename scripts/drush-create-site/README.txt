## drush-create-site ##

This is a bash script that helps automate the creation of
new drupal sites.  It was originally developed for use with
the ELMS Course information system (CIS) distribution in order
to allow for the simple request of new systems to be spun up.

The basic workflow is that a node is created in drupal and CIS
will write a file to a private directory (/var/wwwjobs by default).
The script reads in the lines and executes a series of drush commands
that have been both expected based on line number as well as free-form
if they are white-listed.  The basic workflow is:

-- Run Drush SI command to build a new site
-- create symlinks and sites.php and settings.php records
-- allow for structured, whitelisted drush commands that are variable

The script then ends (in CIS at least) with a drush cc and drush cron
calls.  These aren't required but can help with build accuracy.

## Some context of our environment ##
This has been written for use in the automatic creation of new RESTful
API driven Drupal sites to be created and so it actually builds two
different settings.php files.  One for front end web calls and one for
backend REST calls (for security they are separate).  It also is setup
for writing to multiple multi-site stacks.  This allows for automatic
writing to distro1/newsite vs distro2/newsite based on the creation
of either a newsite.distro1 file or newsite.distro2 file.

You'll most likely need to hack this to bits to fit your org structure
internally but it's worth seeing how we automate Drupal like crazy.

## rm-site.sh ##
This is a script for quickly removing a site created based on the above
structure.  This is a very useful during testing to make sure that all
traces of a built site are removed.  This will delete the database, dbuser,
symlink, sites.php record, and multisite structure for the site.

Currently there is no automation with CIS to use this and it's a backend
developer command only because of its destructive nature.