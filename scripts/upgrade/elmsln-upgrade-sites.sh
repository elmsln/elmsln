#!/bin/bash
#where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

source ../../config/scripts/drush-create-site/config.cfg

#provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=${txtbld}$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  green
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
  return 1
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
  return 1
}
# Define seconds timestamp
timestamp(){
  date +"%s"
}

#test for empty vars. if empty required var -- exit
if [ -z $elmsln ]; then
  elmslnwarn "please update your config.cfg file"
  exit 1
fi

# stacks we currently are supporting for these type of upgrades
# @todo look into pushing this info off onto the cfg file as well
# this way we can read from this source after they've already set the
# whole network in motion as to what they want to support. It will also
# give us flexibility to add a command to pull new tools into this network
# and in the future allow for clustered elmsln instances where parts of
# the network are upgraded and managed locally per system install without
# the possibility of having other stacks written into this one.
standalone=('online' 'media' 'courses' 'studio' 'interact' 'blog')
for stack in "${standalone[@]}"
do
  elmslnecho "working against $stack"
  # run the safe upgrade of projects by taking the site offline then back on
  drush @${stack}-all cook dr_safe_upgrade --y
  # run global upgrades
  drush @${stack}-all drup d7_elmsln_global ${elmsln}/scripts/upgrade/drush_recipes/d7/global --y
  # run stack specific upgrades
  drush @${stack}-all drup d7_elmsln_${stack}-all ${elmsln}/scripts/upgrade/drush_recipes/d7/${stack}-all --y
done
# this only makes sense for online
elmslnecho "online: seed entity / front facing caches"
drush @online-all hss --y
