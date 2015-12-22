#!/bin/bash
# ensure drush-command-job folder is there
sudo mkdir /var/www/elmsln/config/jobs/drush-command-job
# make sure it's hooked into usr bin
ln -s /var/www/elmsln/scripts/drush-command-job /usr/local/bin/drush-command-job
