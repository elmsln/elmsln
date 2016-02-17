#!/bin/bash
# composer self-update to get all older deployments up to this point
php /usr/local/bin/composer self-update
php /usr/local/bin/composer global require drush/drush:6.*
