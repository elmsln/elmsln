#!/bin/sh
# This is a standardized caching routine that can be run to spider
# and see caches in a logical way for all systems in elmsln.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
source ../config/scripts/drush-create-site/config.cfg

#provide messaging colors for output to console
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
# run cron on all authorities
drush @network.${host} cron --y
# TODO ned to modify hss / provide option for limitting responses
# also need option for picking an account by role so we can spider
# as the webservice user against CIS for these paths, and hit all
# but in courses we spider against a limited number of items, per role available
#drush @network.${host} hss node --xmlrpcuid=1 --y

#seed caches on CIS / media

#run crons on all courses and seed caches there