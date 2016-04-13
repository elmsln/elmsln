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
elmsln="${DIR}/../../"
configsdir="${DIR}/../../../instances/_development/config-example"
address="YOURUNIT"
serviceaddress="SERVICEYOURUNIT"
serviceprefix="DATA."
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

# test for an argument as to what user to write as
if [ -z $1 ]; then
  elmslnwarn "You must supply a domain to produce"
  read domain
else
  domain=$1
fi
# test for an argument as to what user to write as
if [ -z $2 ]; then
  elmslnwarn "You must supply a distro to create like inbox"
  read distro
else
  distro=$2
fi
# test for an argument as to what user to write as
if [ -z $3 ]; then
  elmslnwarn "You must supply the version such as 7.x-1.x."
  read version
else
  version=$3
fi
# test for an argument as to what user to write as
if [ -z $4 ]; then
  elmslnwarn "You must supply the type of tool this is, authority or service?"
  read tooltype
else
  tooltype=$4
fi

# check that the config doesn't already exist in the example directory
if [ ! -d "$configsdir/stacks/$domain" ]; then
  # get structure in place for stack config
  mkdir -p "$configsdir/stacks/$domain/sites/default/files"
  cp "$elmsln/core/dslmcode/cores/drupal-7/sites/default/default.settings.php" "$configsdir/stacks/$domain/sites/default/default.settings.php"
  mkdir "$configsdir/stacks/$domain/sites/$domain"
  # write empty file so this can get picked up by version control
  touch "$configsdir/stacks/$domain/sites/$domain/README.txt"
  # get favicon in place
  cp "$elmsln/scripts/server/assets/favicon.ico" "$configsdir/stacks/$domain/favicon.ico"
  cp "$elmsln/core/dslmcode/cores/drupal-7/.htaccess" "$configsdir/stacks/$domain/.htaccess"
  # copy sites.php example then write into it at bottom
  cp "$elmsln/core/dslmcode/cores/drupal-7/sites/example.sites.php" "$configsdir/stacks/$domain/sites/sites.php"
  echo "\$sites = array(" >> "$configsdir/stacks/$domain/sites/sites.php"
  echo "" >> "$configsdir/stacks/$domain/sites/sites.php"
  echo ");" >> "$configsdir/stacks/$domain/sites/sites.php"
fi

# check for the distro, if we don't have it then create it
if [ ! -d "$elmsln/core/dslmcode/profiles/${distro}-${version}" ]; then
  cd "$elmsln/core/dslmcode/profiles"
  cp -R ulmus-7.x-1.x "${distro}-${version}"
  cd "${distro}-${version}"
  renames=('.travis.yml' 'drupal-org.make' 'local.make.example' 'drecipes/elmsln_ulmus.drecipe' 'ulmus.info' 'ulmus.install' 'ulmus.profile' 'themes/SUB_foundation_access/SUB_foundation_access.info' 'themes/SUB_foundation_access/css/SUB_styles.css' 'themes/SUB_foundation_access/template.php')
  for rename in "${renames[@]}"
    do
    sed -i '' "s/ulmus/$distro/g" $rename
    sed -i '' "s/SUB/$distro/g" $rename
    sed -i '' "s/Innovate/$distro/g" $rename
  done
  mv ulmus.info $distro.info
  mv ulmus.profile $distro.profile
  mv ulmus.install $distro.install
  mv drecipes/elmsln_ulmus.drecipe "drecipes/elmsln_${distro}.drecipe"
  mv themes/SUB_foundation_access/css/SUB_styles.css "themes/SUB_foundation_access/css/${distro}_styles.css"
  mv themes/SUB_foundation_access/SUB_foundation_access.info "themes/SUB_foundation_access/${distro}_foundation_access.info"
  mv themes/SUB_foundation_access "themes/${distro}"
  # add into the file the correct depdendencies for these
  if [ $tooltype == 'authority' ];
    then
    sed -i '' "s/\;dependencies\[\] = cis_course_authority/dependencies\[\] = cis_course_authority/g" ${distro}.info
    sed -i '' "s/elmslntype = \"service\"/elmslntype = \"authority\"/g" ${distro}.info
  fi
  # rewrite to disable this
  sed -i '' "s/dependencies\[\] = ${distro}_innovate/\;dependencies\[\] = ulmus_innovate/g" ${distro}.info
fi

# remove git in this new place and create a new repo w/ the correct name conventions
rm -rf .git
elmslnecho "issue this for d.o work:"
elmslnecho "git init"
elmslnecho "git remote add origin YOU@git.drupal.org:project/$distro.git"
elmslnecho "git checkout -b $version"
elmslnecho "git add -A"
elmslnecho "git commit -m 'initial commit of $distro'"
elmslnecho "git push origin $version"

# check that it doesn't already exist
if [ ! -d "$elmsln/domains/$domain" ]; then
  cd "$elmsln/domains"
  # authorities are just a symlink to the folder in question, much easier!
  if [ $tooltype == 'authority' ];
    then
    drush eas $domain "${distro}-${version}"
  fi
  # services have a bit more symlinks
  if [ $tooltype == 'service' ];
    then
    drush eas $domain "${distro}-${version}" --service-instance=TRUE
    cp "$elmsln/core/dslmcode/cores/drupal-7/entity-iframe-consumer.html" "$domain/entity-iframe-consumer.html"
    cp "$elmsln/core/dslmcode/cores/drupal-7/apple-touch-icon-precomposed.png" "$domain/apple-touch-icon-precomposed.png"
    cp "courses/.gitignore" "$domain/.gitignore"
    cp "courses/README.txt" "$domain/README.txt"
  fi
fi

# update the documentation file on apache config
echo "<VirtualHost *:80>" >>  "$elmsln/scripts/server/domains/${domain}.conf"
echo "    DocumentRoot /var/www/elmsln/domains/$domain" >> "$elmsln/scripts/server/domains/${domain}.conf"
echo "    ServerName $domain.${address}.edu" >> "$elmsln/scripts/server/domains/${domain}.conf"
echo "    ServerAlias ${serviceprefix}${domain}.${serviceaddress}.edu" >> "$elmsln/scripts/server/domains/${domain}.conf"
echo "</VirtualHost>" >> "$elmsln/scripts/server/domains/${domain}.conf"
echo "<Directory /var/www/elmsln/domains/$domain>" >> "$elmsln/scripts/server/domains/${domain}.conf"
echo "    AllowOverride All" >> "$elmsln/scripts/server/domains/${domain}.conf"
echo "    Order allow,deny" >> "$elmsln/scripts/server/domains/${domain}.conf"
echo "    allow from all" >> "$elmsln/scripts/server/domains/${domain}.conf"
echo "</Directory>" >> "$elmsln/scripts/server/domains/${domain}.conf"

elmslnecho "The tool named $domain has now been added to the ELMSLN structure."
