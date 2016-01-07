#!/bin/bash
# ensure root / ulmus / ulmusdrush users have their drush pluggins updated
/var/www/elmsln/scripts/utilities/refresh-drush-config.sh
su -c 'HOME=/home/ulmus/ PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/home/ulmus/.composer/vendor/bin /var/www/elmsln/scripts/utilities/refresh-drush-config.sh' ulmus
su -c 'HOME=/home/ulmusdrush/ PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/home/ulmusdrush/.composer/vendor/bin /var/www/elmsln/scripts/utilities/refresh-drush-config.sh' ulmusdrush
