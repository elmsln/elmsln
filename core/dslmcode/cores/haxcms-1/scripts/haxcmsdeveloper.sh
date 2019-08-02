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
echo 'to do local development, cd into any _sites/whatever directory and run polymer serve --open'
echo 'then add dev.html to the path to start local development'