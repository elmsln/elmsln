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
# make sure we're up to date
yes | yum update
# using yum to install the main packages
yes | yum -y install curl uuid patch git nano gcc make mysql55-server httpd24
# amazon packages on 56
yes | yum -y install php56 php56-common php56-opcache php56-fpm php56-pecl-apcu php56-cli php56-pdo php56-mysqlnd php56-gd php56-mbstring php56-mcrypt php56-xml php56-devel php56-pecl-ssh2 --skip-broken

yes | yum groupinstall 'Development Tools'
pecl channel-update pecl.php.net

# set httpd_can_sendmail so drupal mails go out
setsebool -P httpd_can_sendmail on
# start mysql to ensure that it is running
# todo pass some stuff in here... cause it's weird for amazon.
service mysqld restart

#install varnish
yum install varnish -y

sed -i 's/VARNISH_LISTEN_PORT=6081/VARNISH_LISTEN_PORT=80/g' /etc/sysconfig/varnish
sed -i 's/Listen 80/Listen 8080/g' /etc/httpd/conf/httpd.conf
cat /dev/null > /etc/varnish/default.vcl
cat /var/www/elmsln/scripts/server/varnish.txt > /etc/varnish/default.vcl

service varnish start
chkconfig varnish on

# optimize apc
echo "" >> /etc/php.d/40-apcu.ini
echo "apc.rfc1867=1" >> /etc/php.d/40-apcu.ini
echo "apc.rfc1867_prefix=upload_" >> /etc/php.d/40-apcu.ini
echo "apc.rfc1867_name=APC_UPLOAD_PROGRESS" >> /etc/php.d/40-apcu.ini
echo "apc.rfc1867_freq=0" >> /etc/php.d/40-apcu.ini
echo "apc.rfc1867_ttl=3600" >> /etc/php.d/40-apcu.ini
# optimize opcodecache for php 5.5
echo "opcache.enable=1" >> /etc/php.d/10-opcache.ini
echo "opcache.memory_consumption=256" >> /etc/php.d/10-opcache.ini
echo "opcache.max_accelerated_files=100000" >> /etc/php.d/10-opcache.ini
echo "opcache.max_wasted_percentage=10" >> /etc/php.d/10-opcache.ini
echo "opcache.revalidate_freq=2" >> /etc/php.d/10-opcache.ini
echo "opcache.validate_timestamps=1" >> /etc/php.d/10-opcache.ini
echo "opcache.fast_shutdown=1" >> /etc/php.d/10-opcache.ini
echo "opcache.interned_strings_buffer=8" >> /etc/php.d/10-opcache.ini
echo "opcache.enable_cli=1" >> /etc/php.d/10-opcache.ini

# Make sure apache knows what you are tyring to do with host files.
echo IncludeOptional conf.sites.d/*.conf >> /etc/httpd/conf/httpd.conf
echo 'ProxyTimeout 1800' >> /etc/httpd/conf/httpd.conf


# make an admin group
groupadd admin
groupadd elmsln

# run the handsfree installer that's the same for all deployments
# kick off hands free deployment
bash /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh 3 $1 $2 $3 $3 $3 data- $4 $5 $5 elmsln $6

chkconfig mysqld on
service mysqld restart

## very smart of ami to have the php-fpm fallback already in place so you can just kill mod_php
rm /etc/httpd/conf.modules.d/10-php.conf -rf

#This needs to happen again after you remove mod_php
chkconfig httpd on
service httpd restart

#Turn on php-fpm service
chkconfig php-fpm on
service php-fpm start

cd $HOME
source .bashrc
end="$(timestamp)"
elmslnecho "This took $(expr $end - $start) seconds to complete the whole thing!"
