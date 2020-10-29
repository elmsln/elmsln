#!/bin/bash

# detect whether ELMSLN is already installed
if [[ -f "/var/www/elmsln/config/SYSTEM_VERSION.txt" ]]; then
  echo "ELMSLN is already installed on this server, exiting installation"
  exit 0
fi

# symlink to get around ddev's mount path
sudo ln -s /var/www/html /var/www/elmsln

# copy across the latest Ubuntu18 installer and make some changes to apply 
# ddev-friendly commands.
echo "Setting up install files"
sed -e "s/apt-get upgrade -y/#apt-get upgrade -y/g" \
    -e "s/service php7.2-fpm restart/service php7.2-fpm reload/g" \
    -e "s/service mariadb restart/service mariadb reload/g" \
    -e "s/service apache2 restart/service apache2 reload/g" \
    -e "s/\/var\/www\/elmsln\/scripts\/install\/handsfree\/handsfree-install.sh/\/var\/www\/elmsln\/scripts\/install\/handsfree\/ddev\/handsfree-install-ddev.sh/g" \
    /var/www/elmsln/scripts/install/handsfree/ubuntu18/ubuntu18-install.sh > /var/www/elmsln/scripts/install/handsfree/ddev/ubuntu18-install-ddev.sh
    
sed -e "s/mysql -u root --password=\$pass/mysql -u root --password='root' --host=db --port=3306/g" \
    -e "s/mysql -e \"UPDATE mysql.user SET Password = PASSWORD('\$pass') WHERE User = 'root'\"//g" \
    -e "s/mysql -e \"DROP USER ''@'localhost'\"//g" \
    -e "s/mysql -e \"DROP USER ''@'\$(hostname)'\"//g" \
    -e "s/mysql -e \"DROP DATABASE test\"//g" \
    -e "s/mysql -e \"FLUSH PRIVILEGES\"//g" \
    -e "s/\/etc\/init.d\/httpd restart/\/etc\/init.d\/httpd reload/g" \
    -e "s/\/etc\/init.d\/mysqld restart/\/etc\/init.d\/mysqld reload/g" \
    -e "s/\/etc\/init.d\/php-fpm restart/\/etc\/init.d\/php-fpm reload/g" \
    -e "s/service httpd restart/service httpd reload/g" \
    -e "s/service apache2 restart/service apache2 reload/g" \
    -e "s/service mysqld restart/service mysqld reload/g" \
    -e "s/service php5-fpm restart/service php5-fpm reload/g" \
    -e "s/service php7.0-fpm restart/service php7.0-fpm reload/g" \
    -e "s/service php7.2-fpm restart/service php7.2-fpm reload/g" \
    -e "s/\/var\/www\/elmsln\/scripts\/install\/root\/elmsln-preinstall.sh/\/var\/www\/elmsln\/scripts\/install\/handsfree\/ddev\/elmsln-preinstall-ddev.sh/g" \
    -e "s/\/var\/www\/elmsln\/scripts\/install\/elmsln-install.sh/\/var\/www\/elmsln\/scripts\/install\/handsfree\/ddev\/elmsln-install-ddev.sh/g" \
    -e "s/'elmslndbo'@'localhost'/'elmslndbo'@'%'/g" \
    /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh > /var/www/elmsln/scripts/install/handsfree/ddev/handsfree-install-ddev.sh

sed -e "s/mysql -u/mysql --host=db --port=3306 -u/g" \
    -e "s/\/etc\/init.d\/httpd restart/\/etc\/init.d\/httpd reload/g" \
    -e "s/\/etc\/init.d\/mysqld restart/\/etc\/init.d\/mysqld reload/g" \
    -e "s/\/etc\/init.d\/php-fpm restart/\/etc\/init.d\/php-fpm reload/g" \
    -e "s/service httpd restart/service httpd reload/g" \
    -e "s/service apache2 restart/service apache2 reload/g" \
    -e "s/service mysqld restart/service mysqld reload/g" \
    -e "s/service php5-fpm restart/service php5-fpm reload/g" \
    -e "s/service php7.0-fpm restart/service php7.0-fpm reload/g" \
    -e "s/service php7.2-fpm restart/service php7.2-fpm reload/g" \
    -e "s/service php-fpm restart/service php-fpm reload/g" \
    -e "s/git clone https:\/\/github.com\/elmsln\/elmsln-config-example.git config/git clone https:\/\/github.com\/elmsln\/elmsln-config-example.git \/var\/www\/elmsln\/config/g" \
    /var/www/elmsln/scripts/install/root/elmsln-preinstall.sh > /var/www/elmsln/scripts/install/handsfree/ddev/elmsln-preinstall-ddev.sh

sed -e "s/source ..\/..\/config\/scripts\/drush-create-site\/config.cfg/source \/var\/www\/elmsln\/config\/scripts\/drush-create-site\/config.cfg/g" \
    -e "s/source ..\/..\/config\/scripts\/drush-create-site\/configpwd.cfg/source \/var\/www\/elmsln\/config\/scripts\/drush-create-site\/configpwd.cfg/g" \
    -e "s/@127.0.0.1/@db/g" \
    /var/www/elmsln/scripts/install/elmsln-install.sh > /var/www/elmsln/scripts/install/handsfree/ddev/elmsln-install-ddev.sh
    
# Now we've made the scripts ddev-friendly, fire the script
bash /var/www/elmsln/scripts/install/handsfree/ddev/ubuntu18-install-ddev.sh $1 $2 $3 $4 $5 $6