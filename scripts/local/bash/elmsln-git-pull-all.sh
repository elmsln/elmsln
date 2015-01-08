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
  elmslnwarn "please select a branch you want to update on (master)"
  exit 1
fi

start="$(timestamp)"
msg="Grove online, initializing ELMSLN global git pull at $(date +%T)"
elmslnecho "${msg}"
# optional property for channel reporting script
if [ $4 ]; then
  attachments=",\"attachments\": [{\"fallback\": \"Grove git pull status\",\"pretext\": \"Grove git pull status: start\",\"color\": \"warning\",\"fields\": [{\"title\": \"start\",\"value\": \"$start\",\"short\": false}]}]"
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
    attachments=",\"attachments\": [{\"fallback\": \"ELMSLN instance found, beginning git pull\",\"pretext\": \"ELMSLN instance found, beginning git pull\",\"color\": \"warning\",\"fields\": [{\"title\": \"start\",\"value\": \"$tmpstart\",\"short\": false}]}]"
    bash $4 "${msg}" "${attachments}"
  fi
  elmslnecho "${msg}"
  # reup normal location
  $line "cd ~/elmsln && git pull origin $2" < /dev/null
  # print an sa to ensure health
  $line "drush sa" < /dev/null
  tmpend="$(timestamp)"
  msg="Finished working on '${prevline}' in $(expr $tmpend - $tmpstart) seconds"
  elmslnecho "${msg}"
  if [ $4 ]; then
    attachments=",\"attachments\": [{\"fallback\": \"Grove: ELMSLN node git status: complete\",\"pretext\": \"Grove: ELMSLN node git pull status: complete for ${prevline}\",\"color\": \"good\",\"fields\": [{\"title\": \"end\",\"value\": \"$tmpend\",\"short\": false},{\"title\": \"duration\",\"value\": \"$(expr $tmpend - $tmpstart) seconds\",\"short\": false}]}]"
    bash $4 "${msg}" "${attachments}"
  fi
fi
done < "$1"

end="$(timestamp)"
msg="Grove powering down, ELMSLN global git pull complete. git pull took $(expr $end - $start) seconds to complete. Welcome to the future."
elmslnecho "${msg}"
if [ $4 ]; then
  attachments=",\"attachments\": [{\"fallback\": \"Grove git status: complete\",\"pretext\": \"Grove git status: complete\",\"color\": \"good\",\"fields\": [{\"title\": \"start\",\"value\": \"$start\",\"short\": false},{\"title\": \"end\",\"value\": \"$end\",\"short\": false},{\"title\": \"duration\",\"value\": \"$(expr $end - $start) seconds\",\"short\": false}]}]"
  bash $4 "${msg}" "${attachments}"
fi
