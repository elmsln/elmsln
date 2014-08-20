#!/bin/bash

# Use this script to automatically loop through a command list of ssh
# servers you have authorized so that you can run the following example
# command against them. I use this every morning to keep all my galaxies
# in sync across environments.

# read in file and execute commands against ssh'ed hosts
while read line
do
    $line "bash ~/elmsln/scripts/upgrade/elmsln-upgrade-sites.sh master yes && drush @online status;" < /dev/null
done < "$1"
