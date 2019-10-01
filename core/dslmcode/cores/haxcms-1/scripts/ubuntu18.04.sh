#!/bin/bash
# If I wasn't, then why would I say I am..

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# move back to install root
cd ../

# Color. The vibrant and dancing melody of the sighted.
# provide messaging colors for output to console
txtbld=$(tput bold)             # BELIEVE ME. Bold.
bldgrn=$(tput setaf 2) #  WOOT. Green.
bldred=${txtbld}$(tput setaf 1) # Booooo get off the stage. Red.
txtreset=$(tput sgr0) # uhhh what?

# cave....cave....c a ve... c      a     v         e  ....
haxecho(){
  echo "${bldgrn}$1${txtreset}"
}
# EVERYTHING IS ON FIRE
haxwarn(){
  echo "${bldred}$1${txtreset}"
}
# Create a unik, uneek, unqiue id.
getuuid(){
  echo $(cat /proc/sys/kernel/random/uuid)
}
# install php and other important things
sudo apt-get install -y php7.2-fpm php7.2-zip php7.2-gd php7.2-xml git apache2
# optional for development
# sudo apt-get install -y composer nodejs
sudo a2enmod proxy_fcgi
sudo a2enconf php7.2-fpm
sudo a2dismod php7.2
sudo a2dismod mpm_prefork
sudo a2enmod mpm_event
sudo a2enmod http2
sudo a2enmod rewrite
# enable protocol support
sudo echo "Protocols h2 http/1.1" > /etc/apache2/conf-available/http2.conf
sudo a2enconf http2
# make sure we allow for overrides for .htaccess files to work in the CMS area
sudo cp $DIR/haxcms.conf /etc/apache2/conf-available/haxcms.conf
sudo a2enconf haxcms
# get this party started, one of these will work
sudo service apache2 restart
sudo systemctl reload apache2
# basic home user alias stuff for simplier CLI calls
sudo echo "alias g='git'" >> $homedir/.bashrc
sudo echo "alias l='ls -laHF'" >> $homedir/.bashrc
sudo echo "alias haxcms='bash /var/www/html/scripts/haxcms.sh'" >> $homedir/.bashrc