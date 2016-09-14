#!/bin/bash
# Restart PHP so that opcache clears out the symlink for the old shared settings.php
service php-fpm restart
