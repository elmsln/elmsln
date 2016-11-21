#!/bin/bash

# generate a uuid
getuuid(){
  uuidgen -rt
}
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../../config/scripts/drush-create-site/config.cfg
# abstract config.cfg password data
config="/var/www/elmsln/config/scripts/drush-create-site/config.cfg"
# backup this file
cp /var/www/elmsln/config/scripts/drush-create-site/config.cfg /var/www/elmsln/config/scripts/drush-create-site/config_bak.cfg
chmod 400 /var/www/elmsln/config/scripts/drush-create-site/config_bak.cfg
chown $owner:$webgroup /var/www/elmsln/config/scripts/drush-create-site/config_bak.cfg
configpwd="/var/www/elmsln/config/scripts/drush-create-site/configpwd.cfg"
# make password file like new installs do
touch $configpwd
# rip these values over there
echo "dbsu='${dbsu}'" > $configpwd
echo "dbsupw='${dbsupw}'" >> $configpwd
# remove them from the existing config file
sed -i "s/#database superuser credentials//g" $config
sed -i "s/dbsu='${dbsu}'//g" $config
sed -i "s/dbsupw='${dbsupw}'//g" $config
if [[ $webgroup != 'root' ]]; then
  sudo usermod -a -G $webgroup ulmus
  sudo usermod -a -G $webgroup ulmusdrush
fi
# make tmp directory as this is made now at run time based on latest repo check out but not previously existing ones
mkdir -p ${elmsln}/config/tmp
# create a salt file that we can use later on to hash values against
# echo a uuid to a salt file we can use later on
echo "$(getuuid)" > /var/www/elmsln/config/SALT.txt
# nullify this file for security though this shouldn't be an issue
echo "Install successful!\nRun drush @online uli if you need to recover your login info." > /var/www/elmsln/config/tmp/INSTALL-LOG.txt
# update banners so they render pervasively
drush @courses-all elmsln-migrate-banner --y
# make permissions match correctly for our new files we've made
bash ../../utilities/harden-security.sh

# regenerate the salt value
drush @online elmsln-salt --y
# rebuild the passwords now that the keychain has been updated / exists in the first place
drush @elmsln elmsln-service-pwd --y
