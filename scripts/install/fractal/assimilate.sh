#!/bin/bash
# a script to install take over a remote server and form a fractal network with this one

# provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
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

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../../config/scripts/drush-create-site/config.cfg

# TODO, allow for skipping this
elmslnwarn "We will now establish a connection from this server to the next, create an SSH key bind to it and then install assimilate this server into a fractal network that spans the servers."
prompt="What server do you want to connect to? "
read -rp "$prompt" address
prompt="What user name? "
read -rp "$prompt" name
prompt="What port (usually 22 / 2222 are common)? "
read -rp "$prompt" port
# copy id to the server
ssh-copy-id -i ~/.ssh/id_rsa.pub "-p $port $name@$address"

# ALL REMOTE STUFF
# dump to db export via remote execution
elmslnecho "installing elmsln on remote based on this deployment's settings; might take awhile"
# TODO, ask what handsfree to run
ssh -p $port $name@$address "yes | yum -y install wget git && git clone https://github.com/elmsln/elmsln.git /var/www/elmsln && bash /var/www/elmsln/scripts/install/handsfree/centos/centos-install.sh $university $host $address $protocol $admin $elmsln_stats_program"
# kill shared directory and then rsync the local one over
ssh -p $port $name@$address "rm -rf /var/www/elmsln/config/shared/"
dugecho 'rsyncing local to remote, will take a few minutes..'
# rsync the shared modules directory over to this box now that it's established
rsync -az -e "ssh -p $port" $name@$address:/var/www/elmsln/config/shared/ /var/www/elmsln/config/shared/

# need to select which tools to push to this box
# rsync full directory from that server for these tools
# leave local in-tact

# TODO, need to get cis correctly redirecting over to the other box
