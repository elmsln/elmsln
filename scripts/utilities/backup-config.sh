#!/bin/bash
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
# Define seconds timestamp
timestamp(){
  date +"%s"
}

#test for empty vars. if empty required var -- exit
if [ -z $elmsln ]; then
  elmslnwarn "please update your config.cfg file"
  exit 1
fi

# thx to bradallenfisher for this bit of funness
SITES_DIR=$configsdir
BACKUP_DIR="/var/backups/elmsln-config/"
d="$(timestamp)"
TAR_PATH="$(which tar)"
# END CONFIGURATION ============================================================

# Announce the backup time
elmslnecho "Backup Started: $(date)"

# Create the backup dirs if they don't exist
if [[ ! -d $BACKUP_DIR ]]
  then
  mkdir -p "$BACKUP_DIR"
fi
elmslnecho "------------------------------------"
cd $SITES_DIR
cd ..
$TAR_PATH --exclude="*/log" -C $SITES_DIR -czf $BACKUP_DIR$d.tgz $SITES_DIR

# Announce the completion time
elmslnecho "------------------------------------"
elmslnecho "Backup Completed: $(date)"
