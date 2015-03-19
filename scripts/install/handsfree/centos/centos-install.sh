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
# using yum to install the main packages
yes | yum -y install patch git nano gcc make mysql mysql-server httpd php php-gd php-xml php-pdo php-mbstring php-mysql php-pear php-devel php-pecl-ssh2 php-pecl-apc

yes | yum groupinstall 'Development Tools'
# using pecl to install uploadprogress
pecl channel-update pecl.php.net
# uploadprogress to get rid of that warning
pecl install uploadprogress

# adding uploadprogresss to php conf files
touch /etc/php.d/uploadprogress.ini
echo extension=uploadprogress.so > /etc/php.d/uploadprogress.ini

# set httpd_can_sendmail so drupal mails go out
setsebool -P httpd_can_sendmail on
# start mysql to ensure that it is running
/etc/init.d/mysqld restart
# make an admin group
groupadd admin
# run the handsfree installer that's the same for all deployments
# kick off hands free deployment
bash /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh 1 $1 $2 $3 $3 $3 data- $4 $5 $5 admin $6
cd $HOME
source .bashrc
end="$(timestamp)"
elmslnecho "This took $(expr $end - $start) seconds to complete the whole thing!"
