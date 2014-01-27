#!/bin/bash

while [ -f /var/run/drush-create-site ]; do
/usr/local/bin/drush-create-site/drush-create-site & 
sleep 10
done
