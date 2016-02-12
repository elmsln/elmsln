#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

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

if [ -z $1 ]; then
  elmslnwarn "please select a branch you want to update"
  exit 1
fi

# move to elmsln home then issue git pull to kick it off
cd ../../config
git pull origin $1 || (elmslnwarn "git pull failed, you are out of sync with what we support. Exiting." && exit 1)

elmslnecho "ELMSLN deployment's config git repo updated!"
end="$(timestamp)"
elmslnecho "job took $(expr $end - $start) seconds to run"
