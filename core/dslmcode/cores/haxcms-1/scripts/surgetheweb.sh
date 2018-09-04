#!/bin/sh
# Get surge.sh setup
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# move back to install root
cd ../
# run install to ensure we have it
npm install --global surge
# project name
projectname=$1
# seed login info which will force a prompting
surge login
# move into project to operate on it
cd "_sites/${projectname}"
mv index.html index2.html
mv rawgit.html index.html
# publish it
surge .
# set this back since its just for publishing
mv index.html rawgit.html
mv index2.html index.html