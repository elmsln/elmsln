#!/bin/bash
# Step 2

# include our config settings
source ../../../config/scripts/drush-create-site/config.cfg
source commons.cfg

#add site to the sites array
printf "\$sites = array(\n  '$online_domain' => 'online/$host',\n" >> $sitedir/sites.php
printf "  '$online_service_domain' => 'online/services/$host',\n);\n" >> $sitedir/sites.php
# set base_url
printf "\n\$base_url= '$protocol://$online_domain';" >> $sitedir/online/$host/settings.php
