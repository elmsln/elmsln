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
# test for an argument as to what user to write as
if [ -z $1 ]; then
  elmslnwarn "You must supply a domain to produce"
  exit 1
fi
# test for an argument as to what user to write as
if [ -z $2 ]; then
  elmslnwarn "You must supply the type of tool this is, authority or instance?"
  exit 1
fi
domain=$1
tooltype=$2
# check that this domain exists as a stack, otherwise error out
if [ ! -d "$elmsln/core/dslmcode/stacks/$domain" ]; then
  elmslnwarn "This domain must already exist if we are to correctly discover it."
  exit 1
fi
# check that the config doesn't already exist
if [ ! -d "$configsdir/config/stacks/$domain" ]; then
  # get structure in place for stack config
  mkdir -p "$configsdir/config/stacks/$domain/sites/default/files"
  cp "$elmsln/core/dslmcode/cores/drupal-7/sites/default/default.settings.php" "$configsdir/config/stacks/$domain/sites/default/default.settings.php"
  mkdir "$configsdir/config/stacks/$domain/sites/$domain"
  # get favicon in place
  cp "$elmsln/docs/assets/favicon.png" "$configsdir/config/stacks/$domain/favicon.ico"
  cp "$elmsln/core/dslmcode/cores/drupal-7/.htaccess" "$configsdir/config/stacks/$domain/.htaccess"
  # copy sites.php example then write into it at bottom
  cp "$elmsln/core/dslmcode/cores/drupal-7/sites/example.sites.php" "$configsdir/config/stacks/$domain/sites/sites.php"
  echo "\$sites = array(" >> "$configsdir/config/stacks/$domain/sites/sites.php"
  echo "" >> "$configsdir/config/stacks/$domain/sites/sites.php"
  echo ");" >> "$configsdir/config/stacks/$domain/sites/sites.php"
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

# todo, still need to re-up the _elmsln_scripted key that's been generated
# need to grep into the following file, look to drush-create-site for example
# "$configsdir/shared/drupal-7.x/modules/_elmsln_scripted/${university}/${university}_${host}_settings/${university}_${host}_settings.module
# todo, need to issue a registry resync against CIS
# this will activate the new service once we've populated the info above
elmslnecho "The tool named $domain has now been added to the ELMSLN structure, but the URLs associated to it are not active."
elmslnecho "You should review $elmsln/docs/domains.txt for how to hook it up to apache."
elmslnecho "You'll want to add something like the following to /etc/httpd/conf.d/elmsln.conf"
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
