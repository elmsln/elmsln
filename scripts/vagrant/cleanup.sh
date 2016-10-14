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
sudo sed -i 's/Listen 8080/Listen 80/g' /etc/httpd/conf/httpd.conf
sudo sed -i 's/8080/80/g' /etc/httpd/conf.d/*.conf
sudo service varnish stop
sudo /etc/init.d/httpd restart
sudo /etc/init.d/mysqld restart
# disable varnish from starting automatically on reboot
sudo chkconfig varnish off
