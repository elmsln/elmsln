#!/bin/sh
# Get surge.sh setup
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# move back to install root
cd ../
# make node modules linked to the location of lrnwebcomponents
ln -s ~/company/factories/lrnwebcomponents/node_modules/ node_modules
cd _sites
# walk each directory and update it's demo automatically
for project in */ ; do
    cd ${project}
    ln -s ../../node_modules/ node_modules
    ln -s ../../dist/ dist
    cd ../
done
echo 'you are now hooked up as a developer of HAXCMS'
echo 'to do local development, cd into any sites/SITENAME directory and run yarn start to begin local development'
echo 'to do custom theme development, go into the custom folder and run yarn start as well'
echo 'these two commands work together to ensure that you can update the files of your custom theme appropriately'