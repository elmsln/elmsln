#!/bin/bash

# Use this script to execute something remotely, useful for making calls to
# jenkins free of connection details cause it loops through the host registry

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
  elmslnwarn "please include a human readable name for what the current task is"
  exit 1
fi
if [ -z $3 ]; then
  elmslnwarn "please include a command to run"
  exit 1
fi

start="$(timestamp)"
msg="ELMSLN Grove online, initializing $2 at $(date +%T)"
elmslnecho "${msg}"
# optional property for channel reporting script
if [ $4 ]; then
  attachments=",\"attachments\": [{\"fallback\": \"Grove $2\",\"pretext\": \"Grove $2: start\",\"color\": \"warning\",\"fields\": [{\"title\": \"start\",\"value\": \"$start\",\"short\": false}]}]"
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
    attachments=",\"attachments\": [{\"fallback\": \"ELMSLN instance found, beginning $2\",\"pretext\": \"ELMSLN instance found, beginning $2\",\"color\": \"warning\",\"fields\": [{\"title\": \"start\",\"value\": \"$tmpstart\",\"short\": false}]}]"
    bash $4 "${msg}" "${attachments}"
  fi
  elmslnecho "${msg}"
  # setup line, almost everything will move to this location
  $line "cd ~/elmsln" < /dev/null
  # run whatever the command is for remote host execution
  $line "$3" < /dev/null
  tmpend="$(timestamp)"
  msg="Finished working on '${prevline}' in $(expr $tmpend - $tmpstart) seconds"
  elmslnecho "${msg}"
  if [ $4 ]; then
    attachments=",\"attachments\": [{\"fallback\": \"Grove: ELMSLN instance status: complete\",\"pretext\": \"Grove: ELMSLN instance status: complete for ${prevline}\",\"color\": \"good\",\"fields\": [{\"title\": \"end\",\"value\": \"$tmpend\",\"short\": false},{\"title\": \"duration\",\"value\": \"$(expr $tmpend - $tmpstart) seconds\",\"short\": false}]}]"
    bash $4 "${msg}" "${attachments}"
  fi
fi
done < "$1"

end="$(timestamp)"
msg="ELMSLN Grove powering down, $2 complete. This took $(expr $end - $start) seconds to complete. Welcome to the future."
elmslnecho "${msg}"
if [ $4 ]; then
  attachments=",\"attachments\": [{\"fallback\": \"Grove instance status: complete\",\"pretext\": \"Grove instance status: complete\",\"color\": \"good\",\"fields\": [{\"title\": \"start\",\"value\": \"$start\",\"short\": false},{\"title\": \"end\",\"value\": \"$end\",\"short\": false},{\"title\": \"duration\",\"value\": \"$(expr $end - $start) seconds\",\"short\": false}]}]"
  bash $4 "${msg}" "${attachments}"
fi
