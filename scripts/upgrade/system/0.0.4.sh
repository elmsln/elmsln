#!/bin/bash
# ensure root / ulmus / ulmusdrush users have their drush pluggins updated
/var/www/elmsln/scripts/utilities/refresh-drush-config.sh
su -c 'HOME=/home/ulmus/ PATH=/home/ulmus/.composer/vendor/bin:/home/ulmus/.config/composer/vendor/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/gam$
su -c 'HOME=/home/ulmusdrush/ PATH=/home/ulmusdrush/.composer/vendor/bin:/home/ulmusdrush/.config/composer/vendor/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games$
