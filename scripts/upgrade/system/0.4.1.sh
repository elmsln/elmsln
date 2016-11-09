#!/bin/bash
# Restart PHP so that opcache clears out the symlink for the old shared settings.php
service php-fpm restart
service php5-fpm restart
# restart apache
/etc/init.d/httpd restart
service apache2 restart
service httpd restart
