#!/bin/bash

# a script to install server dependencies

# provide messaging colors for output to console

txtbld=$(tput bold)  # Bold
bldgrn=$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)

elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}

elmslnwarn(){
  echo "${bldred}$1${txtreset}"
}

# Define seconds timestamp
timestamp(){
  date +"%s"
}
start="$(timestamp)"

# make sure we're up to date with 5.6 repos
apt-get update -y

# Needed to make sure that we have mcrypt which apparently is ok again. 
apt-get upgrade -y
export DEBIAN_FRONTEND=noninteractive

#Install Mariadb
apt-get install software-properties-common -y
apt-key adv --recv-keys --keyserver hkp://keyserver.ubuntu.com:80 0xF1656F24C74CD1D8
add-apt-repository 'deb [arch=amd64,i386,ppc64el] http://ftp.utexas.edu/mariadb/repo/10.1/ubuntu xenial main'

#update again after new repo and install the db server.
apt-get update -y
apt-get install mariadb-server -y

# Install apache
apt-get -y install apache2

# using apt-get to install the main packages
apt-get -y install sendmail uuid uuid-runtime curl policycoreutils unzip patch git nano gcc make mcrypt

#install php
apt-get -y install php php-fpm php-common php-mysql php-ldap php-cgi php-pear php-xml-parser php-curl php-gd php-cli php-fpm php-apcu php-dev php-mcrypt mcrypt
a2enmod proxy_fcgi setenvif
a2enconf php7.0-fpm

# enable apache headers
a2enmod ssl rewrite headers
pecl channel-update pecl.php.net

pecl install yaml-2.0.0 && echo "extension=yaml.so" > /etc/php/7.0/mods-available/yaml.ini
phpenmod yaml

# install uploadprogress
pecl install uploadprogress

# adding uploadprogresss to php conf files
touch /etc/php/7.0/mods-available/uploadprogress.ini
echo extension=uploadprogress.so > /etc/php/7.0/mods-available/uploadprogress.ini


# Sanity Logs
mkdir /var/log/php-fpm/
echo slowlog = /var/log/php-fpm/www-slow.log >> /etc/php/7.0/fpm/pool.d/www.conf
echo request_slowlog_timeout = 2s >> /etc/php/7.0/fpm/pool.d/www.conf
echo php_admin_value[error_log] = /var/log/php-fpm/www-error.log >> /etc/php/7.0/fpm/pool.d/www.conf

# restart fpm so we have access to these things
service php7.0-fpm restart

# set httpd_can_sendmail so drupal mails go out
setsebool -P httpd_can_sendmail on

# start mysql to ensure that it is running
service mariadb restart
service apache2 restart

# make an admin group
groupadd admin
groupadd elmsln

# get base mysql tables established
#mysql_install_db
# run the handsfree installer that's the same for all deployments

# kick off hands free deployment
cd $HOME
bash /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh 2 $1 $2 $3 $3 $3 data- $4 $5 $5 elmsln $6
cd $HOME
source .bashrc
end="$(timestamp)"
elmslnecho "This took $(expr $end - $start) seconds to complete the whole thing!"
