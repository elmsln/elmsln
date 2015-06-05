#!/bin/bash
cd $HOME
# setup vagrant user as an admin of the system
bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh
# refresh file so its good when next call uses it
source $HOME/.bashrc
# add vagrant to the admin group
sudo usermod -a -G admin vagrant
# set all permissions correctly and for vagrant user
sudo bash /var/www/elmsln/scripts/utilities/harden-security.sh vagrant
# restart apache / mysql just to be safe
sudo /etc/init.d/httpd restart
sudo /etc/init.d/mysqld restart

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
