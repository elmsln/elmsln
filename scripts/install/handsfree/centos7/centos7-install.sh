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
# get the epel and remi repo listings so we can get additional packages like mcrypt
yes | yum -y install git && git clone https://github.com/bradallenfisher/php-fpm-apache-2.4-centos7.git && cd php-fpm-apache-2.4-centos7/install && chmod 700 prod.sh && ./prod.sh

yes | yum groupinstall 'Development Tools'
# using pecl to install uploadprogress
pecl channel-update pecl.php.net

# set httpd_can_sendmail so drupal mails go out
setsebool -P httpd_can_sendmail on
# start mysql to ensure that it is running
/etc/init.d/mysqld restart

#install varnish
rpm --nosignature -i https://repo.varnish-cache.org/redhat/varnish-3.0.el6.rpm
yum install varnish -y

sed -i 's/VARNISH_LISTEN_PORT=6081/VARNISH_LISTEN_PORT=80/g' /etc/sysconfig/varnish
sed -i 's/Listen 80/Listen 8080/g' /etc/httpd/conf/httpd.conf
cat /dev/null > /etc/varnish/default.vcl
cat /var/www/elmsln/docs/varnish.txt > /etc/varnish/default.vcl

service varnish start
chkconfig varnish on

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

/etc/init.d/httpd restart
# make an admin group
groupadd admin
# run the handsfree installer that's the same for all deployments
# kick off hands free deployment
bash /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh 1 $1 $2 $3 $3 $3 data- $4 $5 $5 admin $6


# get things in place so that we can run mysql 5.5
yes | yum -y --enablerepo=remi install mysql mysql-server
/etc/init.d/mysqld restart

cd $HOME
source .bashrc
end="$(timestamp)"
elmslnecho "This took $(expr $end - $start) seconds to complete the whole thing!"
