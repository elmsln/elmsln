#!/bin/sh -xe
# this utility can help establish a jenkins user for a box and then
# rewrites the permissions on the $elmsln directory to match
# what jenkins needs in order to help out remotely

# where are we
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include vars from configuration
source ../../config/scripts/drush-create-site/config.cfg

# test for empty vars. if empty required var -- exit
if [ -z $elmsln ]; then
  echo "please update your config.cfg file"
  exit 1
fi
# check that we are the root user
if [[ $EUID -ne 0 ]]; then
  elmslnwarn "Please run as root"
  exit 1
fi
# make the jenkins user
sudo useradd -gadmin jenkins
# chown so jenkins owns it all
sudo chown -R jenkins:$webgroup $elmsln
# reset things to where they should be for apache for example
sudo bash "$elmsln/scripts/utilities/harden-security.sh"
# make jenkins able to utilize the same elmsln upgrade routines as a normal user
sudo -u jenkins bash "$elmsln/scripts/install/user/elmsln-admin-user.sh"
# make a local key and follow the prompts
sudo -u jenkins ssh-keygen
sudo -u jenkins touch ~/.ssh/authorized_keys

echo "Now go to your jenkins server and copy the public key into ~/.ssh/authorized_keys"
echo "Then goto your jernkins server and try to ssh to this one via commandline"
echo "If this works, then add the line used to connect to ~/.elmsln/elmsln-hosts on your jenkins server"
