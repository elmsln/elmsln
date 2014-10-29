#!/bin/bash
# This will attempt to fix some known issues with piwik after installation
# and help streamline the installation of piwik as it powers the analytics
# domain.

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

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../config/scripts/drush-create-site/config.cfg

#test for empty vars. if empty required var -- exit
if [ -z $site_email ]; then
  elmslnwarn "please update your config.cfg file, site email variable missing"
  exit 1
fi
if [ -z $admin ]; then
  elmslnwarn "please update your config.cfg file, admin email variable missing"
  exit 1
fi
if [ -z $webdir ]; then
  elmslnwarn "please update your config.cfg file, webdir variable missing"
  exit 1
fi

# perform some clean up tasks
# check for tmp directory in config area
if [ ! -d $elmsln/config/_nondrupal/piwik/tmp ];
then
  sudo mkdir $elmsln/config/_nondrupal/piwik/tmp
  sudo chown -R $wwwuser:$webgroup $elmsln/config/_nondrupal/piwik/tmp
fi
sudo chown -R $wwwuser:$wwwuser $elmsln/config/_nondrupal/piwik
sudo chmod -R 0755 $elmsln/config/_nondrupal/piwik
# exotic install issue w/ file integrity check on piwik
if [ -f $elmsln/core/_nondrupal/piwik/plugins/DevicesDetection/images/brand/unknown.ico ]; then
  mv unknown.ico Unknown.ico
fi

