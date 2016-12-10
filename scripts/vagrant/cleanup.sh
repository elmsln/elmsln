#!/bin/bash
cd $HOME
# setup vagrant user as an admin of the system
bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh
# refresh file so its good when next call uses it
source $HOME/.bashrc
# add vagrant to the elmsln group
sudo usermod -a -G elmsln vagrant
# set all permissions correctly and for vagrant user
sudo bash /var/www/elmsln/scripts/utilities/harden-security.sh vagrant

# disable varnish which the Cent 6.x image enables by default
# this way when we're doing local development we don't get cached anything
# port swap to not use varnish in local dev
#sudo sed -i 's/Listen 8080/Listen 80/g' /etc/httpd/conf/httpd.conf
#sudo sed -i 's/8080/80/g' /etc/httpd/conf.sites.d/*.conf
#sudo service varnish stop
#sudo /etc/init.d/httpd restart
#sudo /etc/init.d/mysqld restart
# disable varnish from starting automatically on reboot
#sudo chkconfig varnish off

#service php7.0-fpm restart
#service apache2 restart
#service mysqld restart

# Install front end stack in case users wish to develop with sass.
#curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.32.0/install.sh | bash
#source .bashrc
#nvm install 6.7
#cd /var/www/elmsln/core/dslmcode/shared/drupal-7.x/themes/elmsln_contrib/foundation_access/app
#npm update --save-dev
#npm install gulp --save-dev
#npm install -g bower
#npm install
#bower install
