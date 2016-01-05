#!/bin/bash
# this script adds a new tool to ELMSLN. It creates the right directories
# in the domains folder, correctly symlinks to things inside of config
# and generates a stubbed out config area. Other setup scripts still need
# to fire in order to ensure that all domains / tools are in place and
# we also need to make sure that the source is updated to support the
# domains that we do but this gets a lot of the way there in conjunction
# with the drush plugin to automatically generate a new stack correctly
# off of a distro / dslm setup.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# load config
source ../../config/scripts/drush-create-site/config.cfg

#provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=${txtbld}$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
}

# check that we are the root user
if [[ $EUID -ne 0 ]]; then
  elmslnwarn "Please run as root"
  exit 1
fi

# test for an argument as to what user to write as
if [ -z $elmsln ]; then
  elmslnwarn "You must have a functioning config directory."
  exit 1
fi
tooltype=$1
domain=$2
dist=$3
# if this is an authority of instance, can check but its annoying
if [ -z "$tooltype" ]; then
  elmslnwarn "You must supply the type of tool this is, authority or instance?"
  read tooltype
  if [ -z "$tooltype" ]; then
    exit 1
  fi
fi
# need to know what domain
if [ -z "$domain" ]; then
  elmslnwarn "You must supply the domain to produce"
  read domain
  if [ -z "$domain" ]; then
    exit 1
  fi
fi
tool=$domain
# need to know what distro to build
if [ -z "$dist" ]; then
  elmslnwarn "What distribtuion should this build? (instances ignore this)"
  read dist
  if [ -z "$dist" ]; then
    exit 1
  fi
fi
# check that this domain exists as a stack, otherwise error out
if [ ! -d "$elmsln/core/dslmcode/stacks/$domain" ]; then
  elmslnwarn "This domain must already exist if we are to correctly discover it."
  exit 1
fi
# check that the config doesn't already exist in the example directory
if [ ! -d "$configsdir/stacks/$domain" ]; then
  # get structure in place for stack config
  mkdir -p "$configsdir/stacks/$domain/sites/default/files"
  cp "$elmsln/core/dslmcode/cores/drupal-7/sites/default/default.settings.php" "$configsdir/stacks/$domain/sites/default/default.settings.php"
  mkdir "$configsdir/stacks/$domain/sites/$domain"
  # get favicon in place
  cp "$elmsln/scripts/server/assets/favicon.ico" "$configsdir/stacks/$domain/favicon.ico"
  cp "$elmsln/core/dslmcode/cores/drupal-7/.htaccess" "$configsdir/stacks/$domain/.htaccess"
  # copy sites.php example then write into it at bottom
  cp "$elmsln/core/dslmcode/cores/drupal-7/sites/example.sites.php" "$configsdir/stacks/$domain/sites/sites.php"
  echo "\$sites = array(" >> "$configsdir/stacks/$domain/sites/sites.php"
  echo "" >> "$configsdir/stacks/$domain/sites/sites.php"
  echo ");" >> "$configsdir/stacks/$domain/sites/sites.php"
fi

# check that it doesn't already exist
if [ ! -d "$elmsln/domains/$domain" ]; then
  cd "$elmsln/domains"
  # authorities are just a symlink to the folder in question, much easier!
  if [ $tooltype == 'authority' ];
    then
    ln -s "../core/dslmcode/stacks/$domain" "$domain"
  fi
  # instances have a bit more symlinks
  if [ $tooltype == 'instance' ];
    then
    ln -s "../../config/stacks/$domain/favicon.ico" "favicon.ico"
    ln -s "../core/dslmcode/stacks/$domain/.htaccess" ".htaccess"
    cp "$elmsln/core/dslmcode/cores/drupal-7/entity-iframe-consumer.html" "$domain/entity-iframe-consumer.html"
    cp "$elmsln/core/dslmcode/cores/drupal-7/apple-touch-icon-precomposed.png" "$domain/apple-touch-icon-precomposed.png"
    cp "courses/.gitignore" "$domain/.gitignore"
    cp "courses/README.txt" "$domain/README.txt"
  fi
fi
char=(0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V X W Y Z)
max=${#char[*]}
# now build the tool in question and user account
dbpw=''
for j in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${dbpw}${char[$rand]}"
done

# if authority we need to build the distro
if [ $tooltype == 'authority' ];
  then
  cd "$elmsln/domains/$domain"

  sitedir=${webdir}/${tool}/sites
  drush site-install ${dist} -y --db-url=mysql://${tool}_${host}:$dbpw@127.0.0.1/${tool}_${host} --db-su=$dbsu --db-su-pw=$dbsupw  --account-mail="$admin" --site-mail="$site_email" --site-name="$tool"
  #move out of $tool site directory to host
  sudo mkdir -p $sitedir/$tool/$host
  sudo mkdir -p $sitedir/$tool/$host/files
  #modify ownership of these directories
  sudo chown -R $wwwuser:$webgroup $sitedir/$tool/$host/files
  sudo chmod -R 755 $sitedir/$tool/$host/files

  # setup private file directory
  sudo mkdir -p $drupal_priv/$tool
  sudo mkdir -p $drupal_priv/$tool/$tool
  sudo chown -R $wwwuser:$webgroup $drupal_priv
  sudo chmod -R 755 $drupal_priv

  # copy the default settings file to this location
  # we leave the original for the time being because this is the first instace
  # of the system. most likely we'll always need a default to fall back on anyway
  sudo cp "$sitedir/default/settings.php" "$sitedir/$tool/$host/settings.php"
  sudo chown $USER:$webgroup $sitedir/default/settings.php
  sudo chown $USER:$webgroup $sitedir/$tool/$host/settings.php
  sudo chmod -R 755 $sitedir/$tool/$host/settings.php

  # establish these values real quick so its more readable below
  site_domain="$tool.${address}"
  site_service_domain="${serviceprefix}$tool.${serviceaddress}"
  # add site to the sites array
  echo "\$sites = array(" >> $sitedir/sites.php
  echo "  '$site_domain' => '$tool/$host'," >> $sitedir/sites.php
  echo "  '$site_service_domain' => '$tool/services/$host'," >> $sitedir/sites.php
  echo ");" >> $sitedir/sites.php
  # set base_url
  echo "\$base_url= '$protocol://$site_domain';" >> $sitedir/$tool/$host/settings.php
  cissettings=${university}_${host}_settings
  # enable the cis_settings registry, set private path then execute clean up routines
  drush -y @${domain} en $cissettings
  drush -y @${domain} vset file_private_path ${drupal_priv}/$tool/$tool
  # distro specific additional install routine
  drush -y @${domain} cook elmsln_$dist

  # add in our cache bins now that we know it built successfully
  echo "" >> $sitedir/$tool/$host/settings.php
  echo "" >> $sitedir/$tool/$host/settings.php
  echo "\$conf['cache_prefix'] = '${tool}_${host}';" >> $sitedir/$tool/$host/settings.php
  echo "" >> $sitedir/$tool/$host/settings.php
  echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/$tool/$host/settings.php

  # adding servies conf file
  if [ ! -d $sitedir/$tool/services/$host ];
    then
      sudo mkdir -p $sitedir/$tool/services/$host
      sudo mkdir -p $sitedir/$tool/services/$host/files
      sudo chown -R $wwwuser:$webgroup $sitedir/$tool/services/$host/files
      sudo chmod -R 755 $sitedir/$tool/services/$host/files
      if [ -f $sitedir/$tool/$host/settings.php ]; then
        sudo cp $sitedir/$tool/$host/settings.php $sitedir/$tool/services/$host/settings.php
      fi
      if [ -f $sitedir/$tool/services/$host/settings.php ]; then
        sudo chown $USER:$webgroup $sitedir/$tool/services/$host/settings.php
        echo "" >> $sitedir/$tool/services/$host/settings.php
        echo "" >> $sitedir/$tool/services/$host/settings.php
        echo "\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $sitedir/$tool/services/$host/settings.php
      fi
  fi
  # make sure everything in that folder is as it should be ownerwise
  sudo chown -R $wwwuser:$webgroup $sitedir/$tool/$host/files
  # forcibly apply 1st ELMSLN global update since it isn't fixed tools
  # this makes it so that we don't REQUIRE multi-sites to run tools (stupid)
  # while still fixing the issue with httprl when used in multisites
  drush -y @${domain} cook d7_elmsln_global_1413916953 --dr-locations=/var/www/elmsln/scripts/upgrade/drush_recipes/d7/global
  # ELMSLN clean up for authority distributions (single point)
  drush -y @${domain} cook elmsln_authority_setup
fi
# if its a service instance we need to build a default site for drush
if [ $tooltype == 'instance' ];
  then
  cd "$elmsln/core/dslmcode/stacks/$domain"
  drush site-install -y --db-url=mysql://${domain}_${host}_dbo:$dbpw@127.0.0.1/default_${domain} --db-su=$dbsu --db-su-pw=$dbsupw --account-mail="$admin" --site-mail="$site_email"
fi

# todo, still need to re-up the _elmsln_scripted key that's been generated
# need to grep into the following file, look to drush-create-site for example
# "$configsdir/shared/drupal-7.x/modules/_elmsln_scripted/${university}/${university}_${host}_settings/${university}_${host}_settings.module
# todo, need to issue a registry resync against CIS
# this will activate the new service once we've populated the info above
elmslnecho "The tool named $domain has now been added to the ELMSLN structure, but the URLs associated to it are not active."
elmslnecho "You should add this to $elmsln/scripts/server/domains/${domain}.conf for how to hook it up to apache."
elmslnecho "<VirtualHost *:80>"
elmslnecho "    DocumentRoot $elmsln/domains/$domain"
elmslnecho "    ServerName $domain.${address}"
elmslnecho "    ServerAlias ${serviceprefix}${domain}.${serviceaddress}"
elmslnecho "</VirtualHost>"
elmslnecho "<Directory $elmsln/domains/$domain>"
elmslnecho "    AllowOverride All"
elmslnecho "    Order allow,deny"
elmslnecho "    allow from all"
elmslnecho "    Include $elmsln/domains/$domain/.htaccess"
elmslnecho "</Directory>"
elmslnecho ""
elmslnecho "After that is in place, restart apache and then you should be able to access ${protocol}://${domain}.${address}/README.txt"
