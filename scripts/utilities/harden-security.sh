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

# test for an argument as to what user to write as
if [ -z $1 ]; then
    owner='root'
  else
    owner=$1
fi

# make the default config backup location owned by $owner
if [ ! -d /var/www/elmsln-config-backups ]; then
  mkdir /var/www/elmsln-config-backups -v
fi
chown -R $owner:$webgroup /var/www/elmsln-config-backups -v
# make everything in here read only by $owner but accessible by admin team
chmod -R 2750 /var/www/elmsln-config-backups -v
# make the folder group as webgroup so it can write here
chown $owner:$webgroup /var/www/elmsln-config-backups -v
chmod 2750 /var/www/elmsln-config-backups -v

# chown / chmod the entire thing correctly then we undo what we just did
# in all of the steps below. This ensure the entire package is devoid of holes
chown -R $owner:$webgroup $elmsln
chmod -R 775 $elmsln
# set all settings.php's to be root and READ ONLY
# these live at 2 3 and 4 levels deep in folder nesting at times
for i in $(find $configsdir/stacks/*/sites/*/*/*/*/settings.php -type f); do
  chown $owner:$webgroup $i -v
  chmod 444 $i -v
done
for i in $(find $configsdir/stacks/*/sites/*/*/*/settings.php -type f); do
  chown $owner:$webgroup $i -v
  chmod 444 $i -v
done
for i in $(find $configsdir/stacks/*/sites/*/*/settings.php -type f); do
  chown $owner:$webgroup $i -v
  chmod 444 $i -v
done
# set all sites.php to be root and writable only by root
for i in $(find $configsdir/stacks/*/sites/sites.php -type f); do
  chown $owner:$webgroup $i -v
  chmod 644 $i -v
done

# set files directories to be owned by apache/group
for i in $(find $configsdir/stacks/*/sites/*/*/*/*/files -maxdepth 0 -type d); do
  chown -R $wwwuser:$webgroup $i
  chown $wwwuser:$webgroup $i -v
  chmod 2774 $i -v
done
for i in $(find $configsdir/stacks/*/sites/*/*/*/files -maxdepth 0 -type d); do
  chown -R $wwwuser:$webgroup $i
  chown $wwwuser:$webgroup $i -v
  chmod 2774 $i -v
done
for i in $(find $configsdir/stacks/*/sites/*/*/files -maxdepth 0 -type d); do
  chown -R $wwwuser:$webgroup $i
  chown $wwwuser:$webgroup $i -v
  chmod 2774 $i -v
done

# much easier things to target :)
# ensure script settings are secure and READ ONLY, NEVER globally
chown $owner:$webgroup "$configsdir/scripts/drush-create-site/config.cfg" -v
chmod 0444 "$configsdir/scripts/drush-create-site/config.cfg" -v
# set web server perms correctly for private files
chown -R $wwwuser:$webgroup "$drupal_priv"
chown $wwwuser:$webgroup "$drupal_priv" -v
chmod 2774 "$drupal_priv" -v
# set web server perms correctly for jobs
chown -R $wwwuser:$webgroup "$configsdir/jobs"
chown $wwwuser:$webgroup "$configsdir/jobs" -v
chmod 2774 "$configsdir/jobs" -v
# set upgrade log permissions
if [ ! -d "$configsdir/logs" ]; then
  mkdir "$configsdir/logs" -v
fi
chown -R $owner:$webgroup "$configsdir/logs"
chmod 2770 "$configsdir/logs" -v
# ensure piwik is happy too
chown -R $wwwuser:$wwwuser "$configsdir/_nondrupal/piwik"
chmod -R 0755 "$configsdir/_nondrupal/piwik" -v
