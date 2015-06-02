#ELMSLN - Installation Guide

# Automated installation -- run the following for all prerequisits
sudo -i
# copy and paste this
cd ~
mkdir -p /var/www/elmsln
cd /var/www
git clone https://github.com/elmsln/elmsln.git
cd ~
bash /var/www/elmsln/scripts/install/root/elmsln-preinstall.sh
# answer the questions in the pre-installation routine
# even though it asks you your OS you might want to select other
# just to see the steps its going to go through

# log out as root so you can finish install as you
logout

# copy and paste this
cd ~
# replace YOU with your username and root with whatever group you want
# to own the system. If not sure leave the second value as root though
# admin is common as well.
sudo chown -R YOU:root /var/www/elmsln
# copy and paste these lines to setup your user and install the system
bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh
bash /var/www/elmsln/scripts/install/elmsln-install.sh

# to verify that it worked you should be able to do the following
drush sa
drush @online status

# to set up ease of use and standard development for other users that need to administer the system run the following as them
bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh


#=== EXTRA INSTALL INFORMATION BEYOND THE BASE ===

#=== PIWIK (optional) ===
#Install the analytics package by pointing a domain to the
#elmsln/domains/analytics.  This is running piwik and has config and tmp files
#modified to point to the symlink directories in the config directory.

#Create a database named analytics_{host} to match the rest of your systems.
#You'll need to create a user / password and then  run through the installation
#at analytics.{domain}. There are examples in the cis_example modules included
#with this package as to how that might look.

#elmsln-config-vagrant also includes a working analytics example to see how
#a feature might be created to help make hooking in new systems easier.

#=== Single Sign On ===
#There are examples included with elmsln-config-vagrant to provide SSO via
#the drupal bakery module. This relationship is similar to PIWIK in that you
#you install the master module on the source and the service module to talk
#to it on each instance. This is being worked on as an optional install
#routine since the entire system depends on it.

#Regardless of that being finished, it is still recommended that you use
#LDAP, Shibboleth, Cosign, or some other single sign on system as drupal's
#bakery is rather limitted and ELMSLN really shines when integrated with
#the rest of your organizations systems anyway!

#Bakery can conflict with (a lot of stuff) as one reason to potentially not use it. To correctly use it (til we formally support it on install) you'll need to add the following to your /service/ based domains so that webservices work (cause it will intercept them unfortunately).
$conf['bakery_is_master'] = TRUE;

# === MCRYPT (optional) ===
# Go here: https://mirrors.fedoraproject.org/publiclist/EPEL/6/x86_64/#US
# find a mirror that you want to use

# this example is 64 bit  RHEL 6 building the rpm
wget http://ftp.linux.ncsu.edu/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
rpm -Uvh epel-release-6-8.noarch.rpm
# install it
yum -y install php-mcrypt

#Welcome to the Singularity of Edtech.
