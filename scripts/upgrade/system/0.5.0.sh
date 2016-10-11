#!/bin/bash
# replicate 0.4.1 because that's not an actual version number
# Restart PHP so that opcache clears out the symlink for the old shared settings.php
service php-fpm restart
service php5-fpm restart
# restart apache
/etc/init.d/httpd restart
service apache2 restart
service httpd restart

# we fixed something downstream in elmsln-admin-user for newer versions of composer based on
# its install location
sudo -u ulmus bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh /home/ulmus
sudo -u ulmusdrush bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh /home/ulmusdrush