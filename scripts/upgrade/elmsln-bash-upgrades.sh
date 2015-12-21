#!/bin/bash
# Loop through process update files based on what updates are missing
# this allows our upgrade routine to be deployed in a lazy loaded fashipn
# instead of requiring people to upgrade to each version 1 at a time.
# This also allows the upgrades to perfrom whatever they want, which is
# scary for sure but requires this only be run via bash.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

source ../../config/scripts/drush-create-site/config.cfg

# provide messaging colors for output to console
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
# generate a uuid
getuuid(){
  uuidgen -rt
}
# check that we are the root user
if [[ $EUID -ne 0 ]]; then
  elmslnwarn "Please run as root"
  exit 1
fi

vercomp () {
  if [[ $1 == $2 ]]
  then
      return 0
  fi
  local IFS=.
  local i ver1=($1) ver2=($2)
  # fill empty fields in ver1 with zeros
  for ((i=${#ver1[@]}; i<${#ver2[@]}; i++))
  do
      ver1[i]=0
  done
  for ((i=0; i<${#ver1[@]}; i++))
  do
      if [[ -z ${ver2[i]} ]]
      then
          # fill empty fields in ver2 with zeros
          ver2[i]=0
      fi
      if ((10#${ver1[i]} > 10#${ver2[i]}))
      then
          return 1
      fi
      if ((10#${ver1[i]} < 10#${ver2[i]}))
      then
          return 2
      fi
  done
  return 0
}

# variables for finding versions and doing comparisons
source_dir="${elmsln}/scripts/upgrade/system"
cd $elmsln
code_version=$(<VERSION.txt)
system_version_file="${elmsln}/config/SYSTEM_VERSION.txt"
upgrade_history="${elmsln}/config/logs/upgrade_history.txt"
# make sure config file for version exists
# if it doesn't this implies a much older deployment getting
# onto versions now
if [ ! -f ${system_version_file} ];
  then
  touch $system_version_file
  echo "0.0.0" > $system_version_file
fi
system_version=$(<${system_version_file})
if [ ! -f ${upgrade_history} ];
  then
  touch $upgrade_history
  echo "PRODUCED VIA UPGRADE SCRIPT ITSELF; this suggests a pre-version deployment just as an FYI" >> $upgrade_history
  echo "Initially installed as: ${code_version}" >> $upgrade_history
fi

# todo, need to account for config directories that are further ahead then the code base
#if [[ "$code_version" < "$system_version" ]]; then
#  elmslnwarn "Your codebase is furter behind then the reported version of this config directory! Can't apply updates as this may have been migrated from a newer deployment into an older one. Make sure you update the elmsln code base via leafy in order to correct this issue!"
#  exit 1
#fi
elmslnwarn "Current version of codebase: $code_version"
elmslnwarn "Current version of your system: $system_version"

# move into the upgrade directory
cd $source_dir
# find the potential bash scripts to run, then only apply the ones that have the right name
systemupgrades=( $(find . -maxdepth 1 -type f | sed 's/\///' | sed 's/\.//' | sed 's/.sh//' | sort --version-sort) )
# figure out the distros that go with each stack based on name
for upgrade in "${systemupgrades[@]}"
do
  # check if this upgrade name is greater then the current one
  # but less then the code version; this is more so a sanity check
  # where as the greater then system version implies that the system was
  # installed at SYSTEM_VERSION, but now the code says it is actually on
  # a higher version. This comparison reflects that you could be running
  # multiple semantically versioned upgrades in the interum. As a result
  # you SHOULD be able to go from a 0.0.1 to a 1.2.1 successfully just
  # by running all upgrades in the correct sort order for all things
  # greater then 0.0.1 with the sanity check ensuring a 1.2.2 would not
  # be possible to run
  mincomp=$(vercomp $upgrade $system_version)
  min=$?
  maxcomp=$(vercomp $code_version $upgrade)
  max=$?
  if [[ $min == 1 ]] && [[ $max == 1 ]]; then
    elmslnecho "$(timestamp): We need to run upgrade: $upgrade"
    bash "${upgrade}.sh"
    echo "Applied upgrade $upgrade on $(timestamp)" >> $upgrade_history
  else
    # fallback case to see if they are the same so we know to apply
    # this last upgrade script
    if [[ "$upgrade" = "$code_version" ]]; then
      if [[ "$upgrade" != "$system_version" ]]; then
        elmslnecho "$(timestamp): We need to run upgrade: $upgrade"
        bash "${upgrade}.sh"
        echo "Applied upgrade $upgrade on $(timestamp)" >> $upgrade_history
        # this is a sanity check to ensure we don't run scripts that shouldn't exist
      fi
      break
    fi
  fi
done
# set to code version in case that version release doesn't have a bash script for it
echo $code_version > $system_version_file
elmslnecho "Bash based upgade complete!"
