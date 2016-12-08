#!/bin/bash
# hands free installer for vagrant environment based on cloud deployment 1liners
yes | apt-get install git

if [ -z $1 ]; then
  repo='https://github.com/elmsln/elmsln.git'
else
  repo=$1
fi
if [ -z $2 ]; then
  branch='master'
else
  branch=$2
fi
if [ -z $3 ]; then
  configrepo='https://github.com/elmsln/elmsln-config-vagrant.git'
else
  configrepo=$3
fi
git clone $repo /var/www/elmsln
# move to directory
cd /var/www/elmsln
# drop current remote in case it changes
git remote remove origin
# add in the one the user defined
git remote add origin $repo
# checkout their branch, in case its different
git checkout -b $branch
# hard reset to the branch in question
git fetch --all
git reset --hard origin/$branch
cd $HOME
bash /var/www/elmsln/scripts/install/handsfree/ubuntu16/ubuntu16-install.sh elmsln ln elmsln.local http admin@elmsln.local yes
cd $HOME && source .bashrc

git clone $configrepo /var/www/elmsln-config-vagrant

# vagrant specific stuff downloaded from vagrant config directory
cp -R /var/www/elmsln-config-vagrant/scripts/hooks/* /var/www/elmsln/config/scripts/hooks
cp -R /var/www/elmsln-config-vagrant/shared/drupal-7.x/modules/vagrant /var/www/elmsln/config/shared/drupal-7.x/modules/vagrant
rm /var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php
cp /var/www/elmsln-config-vagrant/shared/drupal-7.x/settings/shared_settings.php /var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php

# add in checks to ensure apache/mysql haven't stopped
# when we SSH into the box. For the purposes of drupal
# and vagrant, these services should NEVER be stopped
# though there appears to be a possible glitch with
# vagrant and core services on the VM starting correctly
# when ever networking is screwed up
echo '#!/bin/bash' >> /etc/profile.d/chkon.sh
echo 'phpfpm=$(sudo /usr/sbin/service php7.0-fpm status)' >> /etc/profile.d/chkon.sh
echo 'mysql=$(sudo /usr/sbin/service mysqld status)' >> /etc/profile.d/chkon.sh
echo 'httpd=$(sudo /usr/sbin/service apache2 status)' >> /etc/profile.d/chkon.sh
# test for mysql
echo 'if [[ $mysql == *"inactive (dead)"* ]]' >> /etc/profile.d/chkon.sh
echo 'then' >> /etc/profile.d/chkon.sh
echo '  sudo /usr/sbin/service mysqld restart' >> /etc/profile.d/chkon.sh
echo 'fi' >> /etc/profile.d/chkon.sh
# test for apache
echo 'if [[ $httpd == *"inactive (dead)"* ]]' >> /etc/profile.d/chkon.sh
echo 'then' >> /etc/profile.d/chkon.sh
echo '  sudo /usr/sbin/service apache2 restart' >> /etc/profile.d/chkon.sh
echo 'fi' >> /etc/profile.d/chkon.sh
# test for phpfpm
echo 'if [[ $phpfpm == *"inactive (dead)"* ]]' >> /etc/profile.d/chkon.sh
echo 'then' >> /etc/profile.d/chkon.sh
echo '  sudo /usr/sbin/service php7.0-fpm restart' >> /etc/profile.d/chkon.sh
echo 'fi' >> /etc/profile.d/chkon.sh

# vagrant specific stuff
# seckit causes isses, especially locally
drush @online dis seckit --y
# specific stuff for aiding in development
drush @online en vagrant_cis_dev cis_example_cis --y
# update password everywhere to be something simple
drush @elmsln upwd admin --password=admin --y
# enable devel everywhere
drush @elmsln en devel --y
# restart apache to frag some caches because of the different settings that changed inside
service apache2 restart

su - vagrant bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh /home/vagrant

sed -i '1i export PATH="/home/vagrant/.config/composer/vendor/bin:$PATH"' /home/vagrant/.bashrc
sed -i '1i export PATH="/home/vagrant/.composer/vendor/bin:$PATH"' /home/vagrant/.bashrc

# add vagrant to the elmsln group
usermod -a -G elmsln vagrant

# set all permissions correctly and for vagrant user
bash /var/www/elmsln/scripts/utilities/harden-security.sh vagrant

# disable varnish this way when we're doing local development we don't get cached anything
# port swap to not use varnish in local dev
#//sed -i 's/Listen 8080/Listen 80/g' /etc/httpd/conf/httpd.conf

#service varnish stop
service apache2 restart
service mysqld restart

# disable varnish from starting automatically on reboot
#chkconfig varnish off
