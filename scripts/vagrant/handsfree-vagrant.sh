#!/bin/bash
# hands free installer for vagrant environment based on cloud deployment 1liners
yes | yum -y install git

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
cd /var/www/elmsln
git checkout $branch
cd $HOME
bash /var/www/elmsln/scripts/install/handsfree/centos7/centos-install.sh elmsln ln elmsln.local http admin@elmsln.local yes
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
echo 'mysql=$(sudo /sbin/service mysqld status)' >> /etc/profile.d/chkon.sh
echo 'httpd=$(sudo /sbin/service httpd status)' >> /etc/profile.d/chkon.sh
# test for mysql
echo 'if [[ $mysql == *"mysqld is stopped"* ]]' >> /etc/profile.d/chkon.sh
echo 'then' >> /etc/profile.d/chkon.sh
echo '  sudo /sbin/service mysqld restart' >> /etc/profile.d/chkon.sh
echo 'fi' >> /etc/profile.d/chkon.sh
# test for apache
echo 'if [[ $httpd == *"httpd is stopped"* ]]' >> /etc/profile.d/chkon.sh
echo 'then' >> /etc/profile.d/chkon.sh
echo '  sudo /sbin/service httpd restart' >> /etc/profile.d/chkon.sh
echo 'fi' >> /etc/profile.d/chkon.sh

# vagrant specific stuff
# seckit causes isses, especially locally
drush @online dis seckit --y
# specific stuff for aiding in development
drush @online en vagrant_cis_dev cis_example_cis --y
# restart apache to frag some caches because of the different settings that changed inside
sudo /etc/init.d/httpd restart
