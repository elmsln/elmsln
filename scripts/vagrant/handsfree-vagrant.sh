#!/bin/bash
# hands free installer for vagrant environment based on cloud deployment 1liners
yes | yum -y install git
git clone https://github.com/elmsln/elmsln.git /var/www/elmsln
bash /var/www/elmsln/scripts/install/handsfree/centos/centos-install.sh elmsln ln elmsln.local http admin@elmsln.local yes
cd $HOME && source .bashrc

git clone git://github.com/elmsln/elmsln-config-vagrant.git /var/www/elmsln-config-vagrant

# vagrant specific stuff downloaded from vagrant config directory
cp -R /var/www/elmsln-config-vagrant/scripts/hooks/* /var/www/elmsln/config/scripts/hooks
cp -R /var/www/elmsln-config-vagrant/shared/drupal-7.x/modules/vagrant /var/www/elmsln/config/shared/drupal-7.x/modules/vagrant
rm /var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php
cp /var/www/elmsln-config-vagrant/shared/drupal-7.x/settings/shared_settings.php /var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php

# setup host file so httprl works for local cache rebuilding
cat /var/www/elmsln/scripts/vagrant/hosts >> /etc/hosts

# vagrant specific stuff
drush @online dis seckit --y
drush @online en vagrant_cis_dev cis_example_cis vagrant_bakery --y
drush @online upwd admin --password=admin
