#!/bin/bash

# a script to install server dependencies

# provide messaging colors for output to console

txtbld=$(tput bold)  # Bold
bldgrn=$(tput setaf 2) #  green
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
start="$(timestamp)"

# kick off hands free deployment
cd $HOME
bash /var/www/elmsln/scripts/install/handsfree/handsfree-install.sh 2 $1 $2 $3 $3 $3 data- $4 $5 $5 elmsln $6


cd $HOME
source .bashrc
end="$(timestamp)"
elmslnecho "This took $(expr $end - $start) seconds to complete the whole thing!"
