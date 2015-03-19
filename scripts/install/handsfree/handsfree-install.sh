#!/bin/bash
# hands free driving is the safest kind of driving
# when this is all said and done, no one knows the root mysql password
# no one knows the elmslndbo password except elmsln
# and the entire box is built to exactly what it needs to be from the
# ground up

# this script assumes ELMSLN code base is on the server but that's
# about it. See one of the server installs in the hands free directory
cd $HOME
# @todo pipe in values
bash /var/www/elmsln/scripts/install/root/elmsln-preinstall.sh
# copy and paste this
cd $HOME
rm -rf $HOME/.drush
# replace YOU with your username and root with whatever group you want
# to own the system. If not sure leave the second value as root though
# admin is common as well.
chown -R root:root /var/www/elmsln
# setup user as admin
bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh
# install system and off we go
bash /var/www/elmsln/scripts/install/elmsln-install.sh
