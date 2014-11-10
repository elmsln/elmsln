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
# set all settings.php's to be root and READ ONLY
chown root:root "$configsdir/stacks/*/sites/*/*/*/settings.php"
chmod 444 "$configsdir/stacks/*/sites/*/*/*/settings.php"
chown root:root "$configsdir/stacks/*/sites/*/*/settings.php"
chmod 444 "$configsdir/stacks/*/sites/*/*/settings.php"
# set all sites.php to be root and writable only by root
chown -R root:root "$configsdir/stacks/*/sites/sites.php"
chmod 644 "$configsdir/stacks/*/sites/sites.php"
# ensure script settings are secure and READ ONLY, NEVER globally
chown root:$webgroup "$configsdir/scripts/drush-create-site/config.cfg"
chmod 440 "$configsdir/scripts/drush-create-site/config.cfg"

# set web server perms correctly for private files
chown -R $wwwuser:$webgroup "$drupal_priv"
chmod 774 "$drupal_priv"
# set web server perms correctly for jobs
chown -R $wwwuser:$webgroup "$configsdir/jobs"
chmod 774 "$configsdir/jobs"
# ensure piwik is happy
chown -R $wwwuser:$wwwuser "$configsdir/_nondrupal/piwik"
chmod 744 "$configsdir/_nondrupal/piwik"
# set files directories to be owned by apache
chown -R $wwwuser:$webgroup "$configsdir/stacks/*/sites/*/*/*/files"
chmod 774 "$configsdir/stacks/*/sites/*/*/*/files"
chown -R $wwwuser:$webgroup "$configsdir/stacks/*/sites/*/*/files"
chmod 774 "$configsdir/stacks/*/sites/*/*/files"
