#!/bin/bash
# this script assumes ELMSLN was installed and now your migrating
# here and need to just tune up different packages involved.
# this assumes ubuntu20

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
apt-get update -y

# Needed to make sure that we have mcrypt which apparently is ok again.
apt-get upgrade -y

#Install Mariadb
apt-get install software-properties-common -y
apt-get update -y
apt-get install mariadb-server -y
# Install docker
apt-get -y install docker docker.io docker-compose

# Install apache
apt-get -y install apache2

# using apt-get to install the main packages
apt-get -y install sendmail uuid uuid-runtime curl policycoreutils unzip patch git nano gcc make autoconf libc-dev pkg-config
#install php
apt-get -y install php7.4 php-yaml php7.4-fpm php7.4-gd php7.4-xml php7.4-common php7.4-mysql php7.4-ldap php7.4-cgi php-pear php7.4-mbstring php7.4-zip php7.4-xml php7.4-curl php7.4-cli php7.4-apcu php7.4-dev libmcrypt-dev
apt-get install -y 

a2enmod proxy_fcgi setenvif
a2enconf php7.4-fpm
a2dismod mpm_prefork
a2enmod mpm_event
a2enmod http2
# enable protocol support
echo "Protocols h2 http/1.1" > /etc/apache2/conf-available/http2.conf
a2enconf http2

# enable apache headers
a2enmod ssl rewrite headers
pecl channel-update pecl.php.net

# install uploadprogress
pecl install uploadprogress
yes '' | pecl install mcrypt-1.0.3
echo 'extension=mcrypt.so' > /etc/php/7.4/mods-available/mcrypt.ini
phpenmod mcrypt
# adding uploadprogresss to php conf files
touch /etc/php/7.4/mods-available/uploadprogress.ini
echo extension=uploadprogress.so > /etc/php/7.4/mods-available/uploadprogress.ini

# Sanity Logs
mkdir /var/log/php-fpm/
echo slowlog = /var/log/php-fpm/www-slow.log >> /etc/php/7.4/fpm/pool.d/www.conf
echo request_slowlog_timeout = 2s >> /etc/php/7.4/fpm/pool.d/www.conf
echo php_admin_value[error_log] = /var/log/php-fpm/www-error.log >> /etc/php/7.4/fpm/pool.d/www.conf

# restart fpm so we have access to these things
service php7.4-fpm restart

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

# Not sure why but run this at the end...
apt-get install libyaml-dev -y
yes '' | pecl install -f yaml-2.0.0
echo "extension=yaml.so" > /etc/php/7.4/mods-available/yaml.ini
phpenmod yaml
service php7.4-fpm restart
# these are supposed to be installed but aren't for whatever reason...
apt-get -y install php7.4-mbstring php7.4-zip

# setup infrastructure tools
ln -s /var/www/elmsln/scripts/drush-create-site /usr/local/bin/drush-create-site
ln -s /var/www/elmsln/scripts/drush-command-job /usr/local/bin/drush-command-job
chmod 740 /usr/local/bin/drush-create-site/rm-site.sh

# shortcuts for ease of use
cd $HOME
touch .bashrc
ln -s /var/www/elmsln $HOME/elmsln
echo "alias g='git'" >> .bashrc
echo "alias d='drush'" >> .bashrc
echo "alias l='ls -laHF'" >> .bashrc
echo "alias drs='/usr/local/bin/drush-create-site/rm-site.sh'" >> .bashrc
echo "alias leafy='bash /var/www/elmsln/scripts/elmsln.sh'" >> .bashrc

# setup drush
curl -sS https://getcomposer.org/installer | php
mv composer.phar /usr/local/bin/composer
sed -i '1i export PATH="$HOME/.composer/vendor/bin:$PATH"' .bashrc
sed -i '1i export PATH="$HOME/.config/composer/vendor/bin:$PATH"' .bashrc
source $HOME/.bashrc

# full path to execute in case root needs to log out before it picks it up
php /usr/local/bin/composer global require consolidation/cgr
cgr drush/drush:8.x-dev --prefer-source
# copy in the elmsln server stuff as the baseline for .drush
if [ ! -d $HOME/.drush ]; then
  mkdir $HOME/.drush
fi
yes | cp -rf /var/www/elmsln/scripts/drush/server/* $HOME/.drush/
sudo ln -s /root/.composer/vendor/drush/drush /usr/share/drush
sudo ln -s /root/.config/composer/vendor/drush/drush /usr/share/drush
drush cc drush
# create the accounts we need
bash /var/www/elmsln/scripts/install/root/elmsln-create-accounts.sh

# source one last time before hooking crontab up
source $HOME/.bashrc
cp /var/www/elmsln/scripts/server/ulmus_crontab.txt /etc/cron.d/ulmus
cp /var/www/elmsln/scripts/server/ulmusdrush_crontab.txt /etc/cron.d/ulmusdrush
chmod 600 /etc/cron.d/ulmus
chmod 600 /etc/cron.d/ulmusdrush
chown ulmus:crontab /etc/cron.d/ulmus
chown ulmusdrush:crontab /etc/cron.d/ulmusdrush