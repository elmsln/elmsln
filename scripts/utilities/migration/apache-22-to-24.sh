#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# load config
source ../../../config/scripts/drush-create-site/config.cfg

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
if [ -z $1 ]; then
    owner='root'
  else
    owner=$1
fi

# fix user from RHEL to Ubuntu
sed -i 's/apache/www-data/g' $configsdir/scripts/drush-create-site/config.cfg

# remove this line from htaccess files bc of Apache 2.2 vs 2.4 syntax
for i in $(find $configsdir/stacks/*/.htaccess -type f); do
  sed -i 's/ExpiresActive/#ExpiresActive/g' $i
done

# fix perms
bash ../harden-security.sh
