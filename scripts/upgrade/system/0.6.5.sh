#!/bin/bash
# refresh drush config to squash notices being thrown
bash /var/www/elmsln/scripts/utilities/refresh-drush-config.sh
su -c 'HOME=/home/ulmusdrush/ PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/home/ulmusdrush/.composer/vendor/bin:/home/ulmusdrush/.config/composer/vendor/bin bash /var/www/elmsln/scripts/utilities/refresh-drush-config.sh' ulmusdrush
su -c 'HOME=/home/ulmus/ PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/home/ulmus/.composer/vendor/bin:/home/ulmus/.config/composer/vendor/bin bash /var/www/elmsln/scripts/utilities/refresh-drush-config.sh' ulmus
