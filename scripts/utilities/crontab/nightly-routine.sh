#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# load config
source ../../../config/scripts/drush-create-site/config.cfg

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
# Define seconds timestamp
timestamp(){
  date +"%s"
}
# @todo make a efq call to pull a student account uid, then build requests off it
# run crons
drush @elmsln cron --y
# ping node resource on all systems just to seed some base-line caches
drush @elmsln hsr node --xmlrpcuid=1 --y
# seed field collections as these have the sections in them
drush @online hss field_collection_item --xmlrpcuid=1 --y
# @todo ping welcome_page on everything which will seed CIS calls
# @todo need to spoof section during the request though or its just master







