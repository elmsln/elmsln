#!/bin/bash
# admin-user setup. This helps setup the drush / bashrc baseline needed for
# a consistent administration experience across hosting clusters.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

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
# check that we are NOT root user
if [[ $EUID -eq 0 ]]; then
  elmslnwarn "Don't run this as root!"
  exit 0
fi

# modify the user's home directory to run drush and make life lazy
ln -s /var/www/elmsln $HOME/elmsln
touch $HOME/.bashrc
echo "alias g='git'" >> $HOME/.bashrc
echo "alias d='drush'" >> $HOME/.bashrc
echo "alias l='ls -laHD'" >> $HOME/.bashrc

# setup drush
sed -i '1i export PATH="$HOME/.composer/vendor/bin:$PATH"' $HOME/.bashrc
source $HOME/.bashrc
composer global require drush/drush:6.*

mkdir $HOME/.drush/

# copy in the elmsln server stuff as the baseline for .drush
cp -r /var/www/elmsln/scripts/drush/server/* $HOME/.drush/
# clear caches to force a rebuild of the functions in there
drush cc drush
# list the available aliases
drush sa
elmslnecho "if you see targets listed above other then 'none' then you are good to go (otherwise elmsln still needs to be fully installed via bash /var/www/elmsln/scripts/install/elmsln-install.sh). Log out, then issue the following after you log back in to play with your new super powers:"
elmslnecho "d @online status"
