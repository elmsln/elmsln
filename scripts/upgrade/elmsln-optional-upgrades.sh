#!/bin/bash
# work through and apply optional upgrades. There's no script that runs these
# so they need to executed manually or by jenkins. An example of this would be
# standardizing on the theme conventions we're pushing in the core package but
# not wanting to forcibly apply these to everything.

#where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

source ../../config/scripts/drush-create-site/config.cfg

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
stacklist=('online' 'media' 'courses' 'studio' 'interact' 'blog' 'discuss' 'comply' 'inbox')
for stack in "${stacklist[@]}"
do
  elmslnecho "Applying optional upgrades against $stack"
  # run stack specific upgrades if they exist
  drush @${stack}-all drup d7_elmsln_optional_${stack}-all ${elmsln}/scripts/upgrade/drush_recipes/d7/optional/${stack}-all --y
done
