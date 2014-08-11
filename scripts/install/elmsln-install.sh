#!/bin/bash
# This install script will build job files correctly that drush-create-site
# will pick up and build the initial sites for the system.
# Only user this to initially setup the system as it will add in jobs
# that would fail after the fact.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../config/scripts/drush-create-site/config.cfg

#test for empty vars. if empty required var -- exit
if [ -z $fileloc ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $site_email ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $admin ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $webdir ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $hostfile ]; then
  echo "please update your config.cfg file"
  exit 1
fi

#test mysql login
#mysql -u$dbsu -p$dbsupw -e exit
#if [[ $? > 0 ]];then
  #echo "mysql connection failed"
  #exit 1
#fi

# make sure drush is happy before we begin drush calls
drush cc drush

source install-steps/commons.cfg

sudo sh $elmsln/scripts/install/install-steps/steps.sh step1

# build the default sites
for build in "${buildlist[@]}"
  do
  # install default site for associated stacks in the build list
  cd $stacks/$build
  drush site-install -y --db-url=mysql://elmslndfltdbo:$dbpw@localhost/default_$build --db-su=$dbsu --db-su-pw=$dbsupw --account-mail="$admin" --site-mail="$site_email"
done

# install the CIS site
# generate a random 30 digit password
pass=''
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${pass}${char[$rand]}"
done
cd $stacks/online
sitedir=$stacks/online/sites

drush site-install cis -y --db-url=mysql://online_$host:$dbpw@localhost/online_$host --db-su=$dbsu --db-su-pw=$dbsupw  --account-mail="$admin" --site-mail="$site_email" --site-name="Online"
#move out of online site directory to host
sudo mkdir -p $sitedir/online/$host
sudo mkdir -p $sitedir/online/$host/files
#modify ownership of these directories
sudo chown -R $wwwuser:$webgroup $sitedir/online/$host/files
sudo chmod -R 755 $sitedir/online/$host/files

# setup private file directory
sudo mkdir -p $drupal_priv/online
sudo mkdir -p $drupal_priv/online/online
sudo chown -R $wwwuser:$webgroup $drupal_priv
sudo chmod -R 755 $drupal_priv

# copy the default settings file to this location
# we leave the original for the time being because this is the first instace
# of the system. most likely we'll always need a default to fall back on anyway
sudo cp $sitedir/default/settings.php $sitedir/online/$host/settings.php

sudo sh $elmsln/scripts/install/install-steps/steps.sh step2

# clean up tasks
drush -y --uri=$protocol://$online_domain vset site_slogan 'Welcome to ELMSLN'
drush -y --uri=$protocol://$online_domain en $cissettings
drush -y --uri=$protocol://$online_domain en cis_restws
drush -y --uri=$protocol://$online_domain vset cron_safe_threshold 0
drush -y --uri=$protocol://$online_domain vset user_register 1
drush -y --uri=$protocol://$online_domain vset user_email_verification 0
drush -y --uri=$protocol://$online_domain vset preprocess_css 1
drush -y --uri=$protocol://$online_domain vset preprocess_js 1
drush -y --uri=$protocol://$online_domain vset cis_college_name $host
drush -y --uri=$protocol://$online_domain vset file_private_path ${drupal_priv}/online/online
drush -y --uri=$protocol://$online_domain vset cis_build_lms cis_account_required,cis_lms_required
drush -y --uri=$protocol://$online_domain vset cis_build_code cis_account_required,cis_lms_required
drush -y --uri=$protocol://$online_domain vset cis_build_authenticated cis_account_required
drush -y --uri=$protocol://$online_domain vdel update_notify_emails

# specialized job to automatically produce service nodes to match registry we made
drush -y --uri=$protocol://$online_domain cis-sync-reg
# may seem odd but basically we want to import a default set of nodes then disable
# everything required to do this because it can throw a lot of errors but does work
drush -y --uri=$protocol://$online_domain en cis_sample_content

# uninstall all these now because they should be in correctly as sample nodes
drush -y --uri=$protocol://$online_domain dis cis_sample_content node_export node_export_features node_export_dependency
drush -y --uri=$protocol://$online_domain pm-uninstall cis_sample_content
drush -y --uri=$protocol://$online_domain pm-uninstall node_export_features node_export_dependency
drush -y --uri=$protocol://$online_domain pm-uninstall node_export

# run cron for the good of the order
drush -y --uri=$protocol://$online_domain cron

# print out a reset password link for the online site so you can gain access
drush -y --uri=$protocol://$online_domain upwd admin --password=admin

# run step 3
sudo sh $elmsln/scripts/install/install-steps/steps.sh step3

# a message so you know where my head is at. you get candy if you reference this
echo 'Welcome to the Singularity of edtech.. Go forth, build the future.'
