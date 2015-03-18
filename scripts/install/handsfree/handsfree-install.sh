#!/bin/bash
# hands free driving is the safest kind of driving
# when this is all said and done, no one knows the root mysql password
# no one knows the elmslndbo password except elmsln
# and the entire box is built to exactly what it needs to be from the
# ground up

# provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
}

# @todo, assume this system has 0 configuration ahead of time
# we are going to setup the server in 1 script and then do the
# rest of getting elmsln in place here
#
# probably can clone nittany-vagrant and then use those scripts
# to establish the baseline for the server components. From there
# we can generate a random root password, then use that to request
# a new elmsdbo user/password
# that should be about all we need to set things up minus obviously
# needing some kind of arguments piped in for the few things
# that are actually specific at that point.
#cd ~
# @todo pipe in values
#bash /var/www/elmsln/scripts/install/root/elmsln-preinstall.sh
# copy and paste this
#cd ~
#rm -rf ~/.drush
# replace YOU with your username and root with whatever group you want
# to own the system. If not sure leave the second value as root though
# admin is common as well.
#sudo chown -R root:root /var/www/elmsln

#bash /var/www/elmsln/scripts/install/elmsln-install.sh
