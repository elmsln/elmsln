#!/bin/bash

crontab="/var/spool/cron/crontabs/root"
# shortcuts for ease of use
cd $HOME
touch .bashrc
ln -s /var/www/elmsln $HOME/elmsln
echo "alias g='git'" >> .bashrc
echo "alias d='drush'" >> .bashrc
echo "alias l='ls -laHF'" >> .bashrc
echo "alias drs='/usr/local/bin/drush-create-site/rm-site.sh'" >> .bashrc
echo "alias leafy='bash /var/www/elmsln/scripts/elmsln.sh'" >> .bashrc

# setup drush
sed -i '1i export PATH="$HOME/.composer/vendor/bin:$PATH"' .bashrc
sed -i '1i export PATH="$HOME/.config/composer/vendor/bin:$PATH"' .bashrc
source $HOME/.bashrc

# full path to execute in case root needs to log out before it picks it up
php /usr/local/bin/composer global require consolidation/cgr
cgr drush/drush:8.x-dev --prefer-source

# copy in the elmsln server stuff as the baseline for .drush
if [ ! -d $HOME/.drush ]; then
  mkdir $HOME/.drush
fi
yes | cp -rf /var/www/elmsln/scripts/drush/server/* $HOME/.drush/

# stupid ubuntu drush thing to work with sudo
ln -s /root/.composer/vendor/drush/drush /usr/share/drush
ln -s /root/.config/composer/vendor/drush/drush /usr/share/drush
drush cc drush

# install google API so we can tap into it as needed
cd /var/www/elmsln/core/dslmcode/shared/drupal-7.x/libraries/google-api-php-client/
php /usr/local/bin/composer install

service php7.2-fpm reload

# source one last time before hooking crontab up
source $HOME/.bashrc

echo "* * * * * bash /var/www/elmsln/scripts/install/handsfree/ddev/drush-create-site-ddev.sh" >> $crontab