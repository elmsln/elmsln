#!/bin/bash
# replicate 0.4.1 because that's not an actual version number
# Restart PHP so that opcache clears out the symlink for the old shared settings.php
service php-fpm restart
service php5-fpm restart
# restart apache
/etc/init.d/httpd restart
service apache2 restart
service httpd restart

# we fixed something downstream in elmsln-admin-user for newer versions of composer based on
# its install location
su ulmus -c "bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh /home/ulmus"
su ulmusdrush -c "bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh /home/ulmusdrush"
#!/bin/bash
# This install script will build job files correctly that drush-create-site
# will pick up and build the initial sites for the system.
# Only user this to initially setup the system as it will add in jobs
# that would fail after the fact.

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

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../../config/scripts/drush-create-site/config.cfg

core='7.x'
authoritydistros=()
authoritylist=()
# all distributions / stacks we have
cd $elmsln/core/dslmcode/stacks
stacklist=( $(find . -maxdepth 1 -type d | sed 's/\///' | sed 's/\.//') )
# figure out the distros that go with each stack based on name
for stack in "${stacklist[@]}"
do
  cd $elmsln/core/dslmcode/stacks
  cd "${stack}/profiles"
  # pull the name of the profile in this stack by ignoring core ones
  profile=$(find . -maxdepth 1 -type l \( ! -iname "cle__2" ! -iname "testing" ! -iname "minimal" ! -iname "README.txt" ! -iname "standard" \) | sed 's/\///' | sed 's/\.//')
  cd $profile
  # dig into the file in question for the type values we need
  IFS=$'\n'
  for next in `cat ${profile}.info`
  do
    IFS=' = ' read -a tmp <<< "$next"
    # find the type
    if [[ ${tmp[0]} == 'elmslntype' ]]; then
      distrotype=${tmp[1]}
      if [[ $distrotype == '"authority"' ]]; then
        authoritydistros+=($profile)
        authoritylist+=($stack)
      fi
    fi
  done
done
COUNTER=0
# install authority distributions like online, media, comply
for tool in "${authoritylist[@]}"
  do
  echo $tool
  dist=${authoritydistros[$COUNTER]}
  cd ${webdir}/${tool}
  sitedir=${webdir}/${tool}/sites
  # adding servies conf file
  if [ -f $sitedir/$tool/services/$host/settings.php ]; then
    echo "" >> $sitedir/$tool/services/$host/settings.php
    echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/$tool/services/$host/settings.php
  fi
  COUNTER=$COUNTER+1
done