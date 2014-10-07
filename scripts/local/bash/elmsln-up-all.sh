#!/bin/bash

# Use this script to automatically loop through a command list of ssh
# servers you have authorized so that you can run the following example
# command against them. I use this every morning to keep all my galaxies
# in sync across environments.

#provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=${txtbld}$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  green
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
  return 1
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
  return 1
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
if [ -z $3 ]; then
  elmslnwarn "select branch you want config directory to update on (master)"
  exit 1
fi

start="$(timestamp)"
elmslnecho "$(date +%T) job started"
# read in file and execute commands against ssh'ed hosts
while read line
do
if [[ $line == *\#* ]]
then
  elmslnwarn "skipping this line as it is commented out: $line";
else
  elmslnecho "going to start working against $line"
  # setup line, not required but can help w/ upgrades that hang
  $line "cd ~/elmsln && git pull origin $2 && rm /tmp/elmsln-upgrade-lock" < /dev/null
  # reup the config directory
  $line "cd ~/elmsln/config && git pull origin $3" < /dev/null
  # things are in place, run the actual command
  $line "bash ~/elmsln/scripts/upgrade/elmsln-upgrade-sites.sh $2 yes && drush @online status;" < /dev/null
fi
done < "$1"

end="$(timestamp)"
elmslnecho "job took $(expr $end - $start) seconds to run"
