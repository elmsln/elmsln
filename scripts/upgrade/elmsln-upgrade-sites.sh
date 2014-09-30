#!/bin/bash
#where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

source ../../config/scripts/drush-create-site/config.cfg

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

#test for empty vars. if empty required var -- exit
if [ -z $elmsln ]; then
  elmslnwarn "please update your config.cfg file"
  exit 1
fi
if [ -z $host ]; then
  elmslnwarn "please update your config.cfg file"
  exit 1
fi
if [ -z $1 ]; then
  elmslnwarn "please select a branch you want to update too (like master)"
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
  elmslnwarn 'elmsln-upgrade-lock is in place, this command must have failed previously or is currently already running.'
  elmslnwarn "in order to override this manually you'll have to run rm /tmp/elmsln-upgrade-lock"
  exit 1
fi
start="$(timestamp)"
echo "$(date +%T) job started"
# issue the git pull to version selected at commandline
cd ../..
git pull origin $1 || (elmslnwarn "git pull failed, make sure you sync correctly" && exit 1)

touch /tmp/elmsln-upgrade-lock
# stacks we currently are supporting for these type of upgrades
standalone=('online' 'media' 'courses' 'studio' 'interact' 'blog')
for stack in "${standalone[@]}"
do
  elmslnecho "working against $stack"
  drush @${stack}-all cook dr_safe_upgrade --y
done
# this only makes sense for online
elmslnecho "online: seed entity / front facing caches"
drush @online-all hss --y

elmslnecho "ELMSLN full network upgrade complete!"
end="$(timestamp)"
elmslnecho "job took $(expr $end - $start) seconds to run"
rm /tmp/elmsln-upgrade-lock
