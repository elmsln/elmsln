#!/bin/bash

# generate a uuid
getuuid(){
  uuidgen -rt
}
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../../config/scripts/drush-create-site/config.cfg
# make tmp directory as this is made now at run time based on latest repo check out but not previously existing ones
mkdir -p ${elmsln}/config/tmp
# make permissions match for this directory
bash ../../utilities/harden-security.sh
# create a salt file that we can use later on to hash values against
# echo a uuid to a salt file we can use later on
echo "$(getuuid)" >> /var/www/elmsln/config/SALT.txt
