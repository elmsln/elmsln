#!/bin/bash
# Get surge.sh setup
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# project name
projectname=$1
# move into project to operate on it
cd "../_sites/${projectname}"
# move things around so that its the default from unpkg
mv index.html index2.html
mv unpkg.html index.html
# publish it
surge .
# set this back since its just for publishing
mv index.html unpkg.html
mv index2.html index.html