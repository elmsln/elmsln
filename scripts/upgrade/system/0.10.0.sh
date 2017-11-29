#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../../config/scripts/drush-create-site/config.cfg
# generate gravCMS place holders in the config directory for
mkdir $configsdir/stacks/_installer
mkdir $configsdir/stacks/_installer/cache
mkdir $configsdir/stacks/_installer/backup
mkdir $configsdir/stacks/_installer/logs
mkdir $configsdir/stacks/_installer/tmp
mkdir $configsdir/stacks/_installer/user
# move to user dir so our symlink is correct
cd $configsdir/stacks/_installer/user
ln -s ../../../core/webcomponents webcomponents
# move back to origin and invoke security repair
cd $DIR
bash ../../utilities/harden-security.sh