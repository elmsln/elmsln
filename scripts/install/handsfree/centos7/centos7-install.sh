#!/bin/bash
# a script to install server dependencies

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
# Define seconds timestamp
timestamp(){
  date +"%s"
}
start="$(timestamp)"
RPM="$(which rpm)"
# get the epel and remi repo listings so we can get additional packages like mcrypt
yes | yum -y install git uuid curl && git clone https://github.com/bradallenfisher/php56-fpm-centos7-mysql56.git && cd php56-fpm-centos7-mysql56 && chmod 700 install/prod.sh && ./install/prod.sh

yes | yum groupinstall 'Development Tools'
# using pecl to install uploadprogress
pecl channel-update pecl.php.net

# set httpd_can_sendmail so drupal mails go out
setsebool -P httpd_can_sendmail on
# start mysql to ensure that it is running
service mysqld restart

# optimize apc
echo "" >> /etc/php.d/apcu.ini
echo "apc.rfc1867=1" >> /etc/php.d/apcu.ini
echo "apc.rfc1867_prefix=upload_" >> /etc/php.d/apcu.ini
echo "apc.rfc1867_name=APC_UPLOAD_PROGRESS" >> /etc/php.d/apcu.ini
echo "apc.rfc1867_freq=0" >> /etc/php.d/apcu.ini
echo "apc.rfc1867_ttl=3600" >> /etc/php.d/apcu.ini
# optimize opcodecache for php 5.5
echo "opcache.enable=1" >> /etc/php.d/opcache.ini
echo "opcache.memory_consumption=256" >> /etc/php.d/opcache.ini
echo "opcache.max_accelerated_files=100000" >> /etc/php.d/opcache.ini
echo "opcache.max_wasted_percentage=10" >> /etc/php.d/opcache.ini
echo "opcache.revalidate_freq=2" >> /etc/php.d/opcache.ini
echo "opcache.validate_timestamps=1" >> /etc/php.d/opcache.ini
echo "opcache.fast_shutdown=1" >> /etc/php.d/opcache.ini
echo "opcache.interned_strings_buffer=8" >> /etc/php.d/opcache.ini
echo "opcache.enable_cli=1" >> /etc/php.d/opcache.ini
# remove default apc file that might exist
yes | rm /etc/php.d/apc.ini

service httpd restart
# make an admin group
groupadd admin
groupadd elmsln
# run the handsfree installer that's the same for all deployments
# kick off hands free deployment
bash /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh 3 $1 $2 $3 $3 $3 data- $4 $5 $5 elmsln $6

service mysqld restart

cd $HOME
source .bashrc
end="$(timestamp)"
elmslnecho "This took $(expr $end - $start) seconds to complete the whole thing!"
