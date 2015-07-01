#!/bin/bash
# hands free installer for vagrant environment based on cloud deployment 1liners
yes | yum -y install git
git clone https://github.com/elmsln/elmsln.git /var/www/elmsln
bash /var/www/elmsln/scripts/install/handsfree/centos/centos-install.sh elmsln ln elmsln.local http admin@elmsln.local yes
cd $HOME && source .bashrc

git clone https://github.com/elmsln/elmsln-config-vagrant.git /var/www/elmsln-config-vagrant

# vagrant specific stuff downloaded from vagrant config directory
cp -R /var/www/elmsln-config-vagrant/scripts/hooks/* /var/www/elmsln/config/scripts/hooks
cp -R /var/www/elmsln-config-vagrant/shared/drupal-7.x/modules/vagrant /var/www/elmsln/config/shared/drupal-7.x/modules/vagrant
rm /var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php
cp /var/www/elmsln-config-vagrant/shared/drupal-7.x/settings/shared_settings.php /var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php

# some minor clean up that we need to do via sudo
# setup host file so httprl works for local cache rebuilding
cat /var/www/elmsln/scripts/vagrant/hosts >> /etc/hosts
# add in checks to ensure apache/mysql haven't stopped
# when we SSH into the box. For the purposes of drupal
# and vagrant, these services should NEVER be stopped
# though there appears to be a possible glitch with
# vagrant and core services on the VM starting correctly
# when ever networking is screwed up
echo '#!/bin/bash' >> /etc/profile.d/chkon.sh
echo 'mysql=$(sudo /etc/init.d/mysqld status)' >> /etc/profile.d/chkon.sh
echo 'httpd=$(sudo /etc/init.d/httpd status)' >> /etc/profile.d/chkon.sh
# test for mysql
echo 'if [[ $mysql == *"mysqld is stopped"* ]]' >> /etc/profile.d/chkon.sh
echo 'then' >> /etc/profile.d/chkon.sh
echo '  sudo /etc/init.d/mysqld start' >> /etc/profile.d/chkon.sh
echo 'fi' >> /etc/profile.d/chkon.sh
# test for apache
echo 'if [[ $httpd == *"httpd is stopped"* ]]' >> /etc/profile.d/chkon.sh
echo 'then' >> /etc/profile.d/chkon.sh
echo '  sudo /etc/init.d/httpd start' >> /etc/profile.d/chkon.sh
echo 'fi' >> /etc/profile.d/chkon.sh


# vagrant specific stuff
drush @online dis seckit --y
drush @online en vagrant_cis_dev cis_example_cis vagrant_bakery --y
drush @online upwd admin --password=admin
