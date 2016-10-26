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

# make sure we're up to date with 5.6 repos
apt-get update -y
export DEBIAN_FRONTEND=noninteractive
# using apt-get to install the main packages
apt-get -y install uuid curl policycoreutils php5-mysql mysql-server patch git nano gcc make apache2 libapache2-mod-fastcgi apache2-mpm-event libapache2-mod-php5 php5 php5-fpm php5-common php-xml-parser php5-cgi php5-curl php5-gd php5-cli php5-fpm php-apc php-pear php5-dev php5-mcrypt mcrypt php5-gd
# enable apache headers
a2enmod ssl rewrite headers
pecl channel-update pecl.php.net
# install uploadprogress
pecl install uploadprogress

# Add fastcgi config to server php from the new external server.
cat <<EOF > /etc/apache2/conf-available/php5-fpm.conf
<IfModule mod_fastcgi.c>
    AddHandler php5-fcgi .php
    Action php5-fcgi /php5-fcgi
    Alias /php5-fcgi /usr/lib/cgi-bin/php5-fcgi
    FastCgiExternalServer /usr/lib/cgi-bin/php5-fcgi -socket /var/run/php5-fpm.sock -pass-header Authorization

    <Directory /usr/lib/cgi-bin>
        Require all granted
    </Directory>

</IfModule>
EOF

# Put fastcgi in place, disable mod_php, use event for systems that don't need cosign and restart apache. 
a2enmod actions fastcgi alias
a2dismod mpm_prefork php5
a2enconf php5-fpm
a2enmod mpm_event
service apache2 restart

# adding uploadprogresss to php conf files
touch /etc/php5/mods-available/uploadprogress.ini
echo extension=uploadprogress.so > /etc/php5/mods-available/uploadprogress.ini
# make sure mcrypt is enabled out of the box
cd /etc/php5/fpm/conf.d
ln -s ../../mods-available/mcrypt.ini 20-mcrypt.ini
cd /etc/php5/apache2/conf.d
ln -s ../../mods-available/uploadprogress.ini 20-uploadprogress.ini
ln -s ../../mods-available/mcrypt.ini 20-mcrypt.ini
# restart fpm so we have access to these things
service php5-fpm restart
# set httpd_can_sendmail so drupal mails go out
setsebool -P httpd_can_sendmail on
# start mysql to ensure that it is running
service mysql restart
service apache2 restart
# make an admin group
groupadd admin
groupadd elmsln
# get base mysql tables established
mysql_install_db
# run the handsfree installer that's the same for all deployments
# kick off hands free deployment
cd $HOME
bash /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh 2 $1 $2 $3 $3 $3 data- $4 $5 $5 elmsln $6
cd $HOME
source .bashrc
end="$(timestamp)"
elmslnecho "This took $(expr $end - $start) seconds to complete the whole thing!"
