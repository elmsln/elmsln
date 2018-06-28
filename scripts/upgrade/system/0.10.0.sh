#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# may not actually resolve it but worth attempting to auto set this for media domains
# now that we are going to serve all webcomponents from this domain for a massive performance bump
echo 'Header set Access-Control-Allow-Origin "*"' >> /var/www/elmsln/config/stacks/media/.htaccess
# restart apache to accept the CORS setting
/etc/init.d/httpd restart
service apache2 restart
service httpd restart
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

mkdir $configsdir/stacks/_toplevel
mkdir $configsdir/stacks/_toplevel/cache
mkdir $configsdir/stacks/_toplevel/backup
mkdir $configsdir/stacks/_toplevel/logs
mkdir $configsdir/stacks/_toplevel/tmp
mkdir $configsdir/stacks/_toplevel/user
# move to user dir so our symlink is correct
cd $configsdir/stacks/_toplevel/user
ln -s ../../../core/webcomponents webcomponents
# api setup
mkdir $configsdir/stacks/api
# try and install docker on Ubuntu / CentOS based targets
sudo apt-get -y install docker docker.io docker-compose
sudo yum -y install docker docker-io docker-compose
# move back to origin and invoke security repair
cd $DIR
bash ../../utilities/harden-security.sh