#!/bin/bash
# Step 3

# include our config settings
source ../../../config/scripts/drush-create-site/config.cfg
source commons.cfg

# add in our cache bins now that we know it built successfully
printf "\n\n\$conf['cache_prefix'] = 'online_$host';" >> $sitedir/online/$host/settings.php
printf "\n\nrequire_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/online/$host/settings.php

# adding servies conf file
if [ ! -d $sitedir/online/services/$host ];
  then
    sudo mkdir -p $sitedir/online/services/$host
    sudo mkdir -p $sitedir/online/services/$host/files
    sudo chown -R $wwwuser:$webgroup $sitedir/online/services/$host/files
    sudo chmod -R 755 $sitedir/online/services/$host/files
    if [ -f $sitedir/online/$host/settings.php ]; then
      sudo cp $sitedir/online/$host/settings.php $sitedir/online/services/$host/settings.php
    fi
    if [ -f $sitedir/online/services/$host/settings.php ]; then
      printf "\n\n\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $sitedir/online/services/$host/settings.php
    fi
fi

# perform some clean up tasks
# piwik directories
sudo chown -R $wwwuser:$webgroup $elmsln/config/_nondrupal/piwik
sudo chmod -R 755 $elmsln/config/_nondrupal/piwik
sudo chown -R $wwwuser:$webgroup $elmsln/core/_nondrupal/piwik
# check for tmp directory in config area
if [ ! -d $elmsln/config/_nondrupal/piwik/tmp ];
then
  sudo mkdir $elmsln/config/_nondrupal/piwik/tmp
  sudo chown -R $wwwuser:$webgroup $elmsln/config/_nondrupal/piwik/tmp
fi
sudo chmod -R 0755 $elmsln/config/_nondrupal/piwik/tmp
# jobs file directory
sudo chown -R $wwwuser:$webgroup $elmsln/config/jobs
sudo chmod -R 755 $elmsln/config/jobs
# make sure everything in that folder is as it should be ownerwise
sudo chown -R $wwwuser:$webgroup $sitedir/online/$host/files
