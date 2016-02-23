#!/bin/bash
# This script will install behat for testing.

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
curl -sS https://getcomposer.org/installer | php
# 
# Install Composer with settings in composer.json file
#
php composer.phar install
#
# Initialize Behat
#
bin/behat --init
#
#TODO: Change Featureontext to use Mink
#
# where am i again? move to where I am. This ensures source is properly sourced
cd $DIR
# Change to the bootstrap dir to run the next command
cd features/bootstrap
# find and replace to use Mink context
sed -i '' 's#Behat\\Gherkin\\Node\\TableNode;#Behat\\Gherkin\\Node\\TableNode; use Behat\\MinkExtension\\Context\\MinkContext;#g' FeatureContext.php
sed -i "" "s|class FeatureContext extends BehatContext|class FeatureContext extends MinkContext|g" FeatureContext.php
