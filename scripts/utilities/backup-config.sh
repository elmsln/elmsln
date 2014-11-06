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
BACKUP_DIR="/var/www/elmsln-config-backups/$(timestamp)/"

TAR_PATH="$(which tar)"

# END CONFIGURATION ============================================================

# Announce the backup time
elmslnecho "Backup Started: $(timestamp)"

# Create the backup dirs if they don't exist
if [[ ! -d $BACKUP_DIR ]]
then
mkdir -p "$BACKUP_DIR"
fi

# Get a list of files in the sites directory and tar them one by one
elmslnecho "------------------------------------"

cd $configsdir
for d in *
do
elmslnecho "Archiving $d..."
if [[ ! -d $BACKUP_DIR$d ]]
then
mkdir -p "$BACKUP_DIR$d/"
fi

$TAR_PATH --exclude="*/log" -C $configsdir -czf $BACKUP_DIR$d/$d.tgz $d
done

# Announce the completion time
elmslnecho "------------------------------------"
elmslnecho "Backup Completed: $(timestamp)"
