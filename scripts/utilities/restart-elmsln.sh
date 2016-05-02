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

# if we have service command run everything that way
if [[ $(which service) ]]; then
    service httpd restart
    service mysqld restart
    service php-fpm restart
    service php5-fpm restart
  else
    sudo /etc/init.d/httpd restart
    sudo /etc/init.d/mysqld restart
    sudo /etc/init.d/mysql restart
    sudo /etc/init.d/php-fpm restart
fi
