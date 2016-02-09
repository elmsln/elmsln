#!/bin/bash

# Use this script to automatically loop through a command list of ssh
# servers you have authorized so that you can run the following example
# command against them. I use this every morning to keep all my galaxies
# in sync across environments.

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

if [ -z $1 ]; then
  elmslnwarn "define the location of your elmsln-hosts file"
  exit 1
fi
if [ -z $2 ]; then
  elmslnwarn "please select a branch you want to update on"
  exit 1
fi
if [ -z $3 ]; then
  elmslnwarn "select branch you want config directory to update"
  exit 1
fi

start="$(timestamp)"
msg="Grove online, initializing ELMSLN global upgrade at $(date +%T)"
elmslnecho "${msg}"
# optional property for channel reporting script
if [ $4 ]; then
  attachments=",\"attachments\": [{\"fallback\": \"Grove upgrade status\",\"pretext\": \"Grove upgrade status: start\",\"color\": \"warning\",\"fields\": [{\"title\": \"start\",\"value\": \"$start\",\"short\": false}]}]"
  bash $4 "${msg}" "${attachments}"
fi
# read in file and execute commands against ssh'ed hosts
while read line
do
if [[ $line == *\#* ]]
then
  #elmslnwarn "skipping this line as it is commented out: $line";
  prevline=$line
else
  tmpstart="$(timestamp)"
  msg="${tmpstart} going to start working against '${prevline}'"
  if [ $4 ]; then
    attachments=",\"attachments\": [{\"fallback\": \"ELMSLN instance found, beginning upgrade\",\"pretext\": \"ELMSLN instance found, beginning upgrade\",\"color\": \"warning\",\"fields\": [{\"title\": \"start\",\"value\": \"$tmpstart\",\"short\": false}]}]"
    bash $4 "${msg}" "${attachments}"
  fi
  elmslnecho "${msg}"
  # setup line, not required but can help w/ upgrades that hang
  $line "cd ~/elmsln && git pull origin $2 && rm /tmp/elmsln-upgrade-lock" < /dev/null
  # reup the config directory
  $line "cd ~/elmsln/config && git pull origin $3" < /dev/null
  # things are in place, run the actual command
  $line "bash ~/elmsln/scripts/upgrade/elmsln-upgrade-system.sh $2 yes && drush @online status;" < /dev/null
  tmpend="$(timestamp)"
  msg="Finished working on '${prevline}' in $(expr $tmpend - $tmpstart) seconds"
  elmslnecho "${msg}"
  if [ $4 ]; then
    attachments=",\"attachments\": [{\"fallback\": \"Grove: ELMSLN node upgrade status: complete\",\"pretext\": \"Grove: ELMSLN node upgrade status: complete for ${prevline}\",\"color\": \"good\",\"fields\": [{\"title\": \"end\",\"value\": \"$tmpend\",\"short\": false},{\"title\": \"duration\",\"value\": \"$(expr $tmpend - $tmpstart) seconds\",\"short\": false}]}]"
    bash $4 "${msg}" "${attachments}"
  fi
fi
done < "$1"

end="$(timestamp)"
msg="Grove powering down, ELMSLN global upgrade complete. Upgrade took $(expr $end - $start) seconds to complete. Welcome to the future."
elmslnecho "${msg}"
if [ $4 ]; then
  attachments=",\"attachments\": [{\"fallback\": \"Grove upgrade status: complete\",\"pretext\": \"Grove upgrade status: complete\",\"color\": \"good\",\"fields\": [{\"title\": \"start\",\"value\": \"$start\",\"short\": false},{\"title\": \"end\",\"value\": \"$end\",\"short\": false},{\"title\": \"duration\",\"value\": \"$(expr $end - $start) seconds\",\"short\": false}]}]"
  bash $4 "${msg}" "${attachments}"
fi
