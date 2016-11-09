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
yes | yum -y install git uuid curl nano vim && git clone https://github.com/elmsln/php56-fpm-centos7-mysql56.git && cd php56-fpm-centos7-mysql56 && chmod 700 install/prod.sh && ./install/prod.sh
yes | yum groupinstall 'Development Tools'
# remove brad's test file
yes | rm /etc/httpd/conf.sites.d/test.conf
echo 'ProxyTimeout 1800' >> /etc/httpd/conf/httpd.conf
# set httpd_can_sendmail so drupal mails go out
setsebool -P httpd_can_sendmail on
# stop mysql, initial commands tee this up to ensure that it is running
service mysql restart
service httpd restart
# make an admin group
groupadd admin
groupadd elmsln
# run the handsfree installer that's the same for all deployments
# kick off hands free deployment
bash /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh 3 $1 $2 $3 $3 $3 data- $4 $5 $5 elmsln $6

service mysql restart

cd $HOME
source .bashrc
end="$(timestamp)"
elmslnecho "This took $(expr $end - $start) seconds to complete the whole thing!"
