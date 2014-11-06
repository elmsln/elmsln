#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# load config
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

# check that we are the root user
if [[ $EUID -ne 0 ]]; then
  elmslnwarn "Please run as root"
  exit 1
fi

# make the default config backup location owned by root
mkdir /var/www/elmsln-config-backups
chown -R root:root /var/www/elmsln-config-backups
# harden logs
mkdir $configsdir/logs
chown -R root:root $configsdir/logs
# set sites.php and settings.phps to be owned by root
chown -R root:root "$configsdir/stacks/*/sites/*/*/*/settings.php"
chown -R root:root "$configsdir/stacks/*/sites/*/*/settings.php"
chown -R root:root "$configsdir/stacks/*/sites/sites.php"

# set web server perms correctly for private files
chown -R $wwwuser:$webgroup "$drupal_priv"
# set files directories to be owned by apache
chown -R $wwwuser:$webgroup "$configsdir/stacks/*/sites/*/*/*/files"
chown -R $wwwuser:$webgroup "$configsdir/stacks/*/sites/*/*/files"
