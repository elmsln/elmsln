#!/bin/sh
# elmsln.sh is intended to be an interactive prompt for administering elmsln
# this provides shortcuts for running commands you could have otherwise
# but like the developers of the project, are far too lazy to search for.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
drush @elmsln cron --y
drush @elmsln ecl --y
