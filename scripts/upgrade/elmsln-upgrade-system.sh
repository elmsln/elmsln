#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# load config
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

if [ -z $1 ]; then
  elmslnwarn "please select a branch you want to update (like master)"
  exit 1
fi

# allow for lazy, dangerous people like btopro who enter yes via commandline
if [ -z $2 ]; then
  elmslnecho "Are you sure you want to upgrade the entire network? (Type yes)"
  read yesprompt
else
  yesprompt=$2
fi
# ensure they type yes, this is a big deal command
if [ "$yesprompt" != "yes" ]; then
  elmslnwarn "please type yes to execute the script, exited early"
  exit 1
fi

#prevent the script from being run more than once
if [ -f /tmp/elmsln-upgrade-lock ]; then
  elmslnwarn 'elmsln-upgrade-lock is in place, this command must have failed previously or is currently running.'
  elmslnwarn "in order to override this manually you'll have to run rm /tmp/elmsln-upgrade-lock"
  exit 1
fi
# touch the lock to start off the job
touch /tmp/elmsln-upgrade-lock
# record when we start
start="$(timestamp)"
echo "$(date +%T) job started"
# move to elmsln home then issue git pull to kick it off
cd ../..
git pull origin $1 || (elmslnwarn "git pull failed, you are out of sync with what we support. Exiting." && exit 1)

# make sure we are running off of the correct drush plugins and what not
# since they could change or be upgraded
rm -rf ~/.drush
mkdir ~/.drush
cp -R ${elmsln}/scripts/drush/server/* ~/.drush/
drush cc drush

# check for log file in existance so we can track what happened after the fact
if [ -f ${configsdir}/logs/elmsln-upgrade.log ]; then
  else
    mkdir -p ${configsdir}/logs
    touch ${configsdir}/logs/elmsln-upgrade.log
fi
# execute the upgrade to all sites
bash ${elmsln}/scripts/upgrade/elmsln-upgrade-sites.sh | tee ${configsdir}/logs/elmsln-upgrade.log

# @todo ping home if a key is stored and we are sending analytics
#drush elmsln-call-home

elmslnecho "ELMSLN full network upgrade complete!"
end="$(timestamp)"
elmslnecho "job took $(expr $end - $start) seconds to run"
rm /tmp/elmsln-upgrade-lock
