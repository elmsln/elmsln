#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# load config
source ../../../config/scripts/drush-create-site/config.cfg


# provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=${txtbld}$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
}
# Define seconds timestamp
timestamp(){
  date +"%s"
}

# touch the lock to start off the job
touch /tmp/elmsln-upgrade-lock
elmslnecho "Switching profile from 1.x to 2.x"
cd ${elmsln}/core/dslmcode/stacks/online/profiles
rm cis
ln -s ../../../profiles/cis-7.x-2.x cis

elmslnecho "Applying Upgrades"
cd ${elmsln}
drush @online cook cis1x_2x --dr-locations=${elmsln}/scripts/upgrade/drush_recipes/d7/optional/cis/ --y
# revert core features to ensure they match what things are now
drush @online fr cis_displays cis_default_permissions cis_types cis_users cis_ux --force --y
# update db
drush @online updb
# remove upgrade lock file
rm /tmp/elmsln-upgrade-lock
