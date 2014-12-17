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
# add as part of the webgroup to keep permissions happy
sudo usermod -G admin,$webgroup jenkins
# reset things to where they should be for apache for example
sudo bash "$elmsln/scripts/utilities/harden-security.sh" jenkins
# make jenkins able to utilize the same elmsln upgrade routines as a normal user
sudo -u jenkins bash "$elmsln/scripts/install/users/elmsln-admin-user.sh"
# make a local key and follow the prompts how the user desires
sudo -u jenkins ssh-keygen
sudo -u jenkins touch /home/jenkins/.ssh/authorized_keys
# that's it for automation, now to tell people to do stuff
echo "Now do the following (JENKINS = server hosting it; LOCAL = here, # is instructions, otherwise copy and paste) :"
echo "JENKINS: sudo -i -u jenkins"
echo "JENKINS: cat ~/.ssh/id_rsa.pub"
echo "JENKINS: #Copy output"
echo "LOCAL: sudo -i -u jenkins"
echo "LOCAL: vi ~/.ssh/authorized_keys"
echo "LOCAL: #press... i then paste then :wq"
echo "JENKINS: #try and ssh to the remote with ssh jenkins@{whatever}"
echo "JENKINS: #confirm that you want to accept this key, then if successful, type logout"
echo "JENKINS: sudo -i -u jenkins"
echo "JENKINS: vi ~/.elmsln/elmsln-hosts on your jenkins server"
echo "JENKINS: #create a line with the same ssh jenkins@{whatever} command that successfully connected"
echo "JENKINS: :wq"
echo "=============="
echo "You now should be able to execute commands against this host via Jenkins web interface"
echo "Ex Uno Plures"
echo "=============="
