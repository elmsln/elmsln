#!/bin/bash
# admin-user setup. This helps setup the drush / bashrc baseline needed for
# a consistent administration experience across hosting clusters.

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
# check that we are NOT root user
if [[ $EUID -eq 0 ]]; then
  elmslnwarn "You are running this as root, make sure you establish it for you as well!"
fi

# check for a user passed in, if not default to home directory of active
homedir=$1
if [ -z "$homedir" ]; then
  homedir=$HOME
  # establish as webadmin group otherwise they can't modify the stack at all
  # only do this when running in interactive mode
  if [[ $webgroup != 'root' ]]; then
    sudo usermod -a -G $webgroup $USER
  fi
fi

# modify the user's home directory to run drush and make life lazy
if [[ ! -d "${homedir}/elmsln" ]] ; then
  ln -s ${elmsln} $homedir/elmsln
fi
touch $homedir/.bashrc
echo "alias g='git'" >> $homedir/.bashrc
echo "alias d='drush'" >> $homedir/.bashrc
echo "alias l='ls -laHF'" >> $homedir/.bashrc
echo "alias leafy='bash /var/www/elmsln/scripts/elmsln.sh'" >> $homedir/.bashrc

# setup drush
sed -i '1i export PATH="$HOME/.composer/vendor/bin:$PATH"' $homedir/.bashrc
source $homedir/.bashrc
php /usr/local/bin/composer global require drush/drush:6.*

# copy in the elmsln server stuff as the baseline for .drush
if [ ! -d $homedir/.drush ]; then
  mkdir $homedir/.drush
fi
yes | cp -rf ${elmsln}/scripts/drush/server/* $homedir/.drush/
# clear caches to force a rebuild of the functions in there
drush cc drush
# list the available aliases
drush sa
elmslnecho "if you see targets listed above other then 'none' then you are good to go (otherwise elmsln still needs to be fully installed via bash /var/www/elmsln/scripts/install/elmsln-install.sh). Log out, then issue the following after you log back in to play with your new super powers:"
elmslnecho "d @online status"
