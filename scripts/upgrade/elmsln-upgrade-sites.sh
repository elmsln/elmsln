#!/bin/bash
#where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

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

# tee up the replay from value accounting for it not existing previously
# in this case we just set a really old date here
replay_file="${elmsln}/config/REPLAY.txt"
if [ ! -f ${replay_file} ];
  then
  touch $replay_file
  echo "1413916953" > $replay_file
fi
# find last stamp
replay1=$(<${elmsln}/config/REPLAY.txt)
# cue up 1 day so we dont get tripped by timezone
replay2=86400
# subtract 1 day
replay=$((${replay1} - ${replay2}))
# set the timestamp so that next time we use this as the weather mark
# this takes awhile to run so lets reduce risks even though the replay
# from value will still be the previous time this script ran
echo $(timestamp) > ${elmsln}/config/REPLAY.txt
# to decrease risk of a WSOD when there are significant shifts
# under the hood, we should run RRs prior to the rest of the routine
elmslnecho "Rebuilding registies and caches for all systems"
# set concurrency so these scripts can run in parallel execution
concurrent=2
drush @elmsln rr -concurrency=${concurrent} --strict=0 --v --y
# run the safe upgrade of projects by taking the site offline then back on
elmslnecho "Running update hooks"
# run database updates
drush @elmsln cook dr_run_updates --concurrency=${concurrent} --strict=0 --v --y
# make sure core is happy everywhere
drush @elmsln en elmsln_core --concurrency=${concurrent} --strict=0 --v --y
# run global upgrades from drup recipes
drush @elmsln drup d7_elmsln_global ${elmsln}/scripts/upgrade/drush_recipes/d7/global --replay-from=${replay} --concurrency=${concurrent} --strict=0 --v --y

# load the stacks in question
cd /var/www/elmsln/core/dslmcode/stacks
stacklist=( $(find . -maxdepth 1 -type d | sed 's/\///' | sed 's/\.//') )
for stack in "${stacklist[@]}"
do
  elmslnecho "Applying specific upgrades against $stack"
  # run stack specific upgrades if they exist
  drush @${stack}-all drup d7_elmsln_${stack} ${elmsln}/scripts/upgrade/drush_recipes/d7/${stack} --replay-from=${replay} --concurrency=${concurrent} --strict=0 --v --y
done

# trigger crons to run now that these sites are all back and happy
elmslnecho "Run crons as clean up"
drush @elmsln cron --concurrency=${concurrent} --strict=0 --v --y
# now loop through and prime the caches on everything
elmslnecho "Seeding caches of all entities"
drush @elmsln ecl --concurrency=${concurrent} --strict=0 --v --y
