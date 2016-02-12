#ELMSLN - Installation Guide

## Hands free install
There are some handsfree install routines (copy and paste) that you can try. This is the preferred method of installing ELMS Learning Network as it'll get you up and running with the least steps possible.

### CentOS 6.x / RHEL 6.x
https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/centos/example-deploy
### AWS managed image
https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/amazon/example-deploy
### CentOS 7.x
https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/centos7/example-deploy
### Ubuntu 14.x / Debian 8.x
https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/ubuntu/example-deploy

Hands free has some arguments passed into it to get going but these are for installation against a fresh copy of a server. If you install with the default options provided in those (with addresses of elmsln.dev) you'll want to make sure you modify your local `/etc/hosts` file to reflect these fake addresses.

See the Vagrant installation documentation on how to do this - http://docs.elmsln.org/en/latest/development/Vagrant-Step-by-Step-setup/ though in the installer you'll see a big ELMSLN ascii art message that should tell you what to place there based on your server.

## Manual but mostly automated installation
copy and paste the following offset command prompt items
```
sudo -i
cd ~
mkdir -p /var/www/elmsln
cd /var/www
git clone https://github.com/elmsln/elmsln.git
cd ~

bash /var/www/elmsln/scripts/install/root/elmsln-preinstall.sh
```
answer the questions in the pre-installation routine.
Even though it asks you your OS you might want to select other just to see the steps its going to go through and in case you do anything different.
With the "Other" OS selection it should be possible to install ELMSLN on *nix*flavors other then CentOS / Ubuntu but those have greater support.

log out as root so you can finish install as you
`logout`

copy and paste this while replacing *YOU* with your username and *root* with whatever group you want to own the system. If not sure leave the second value as root but admin is common as well.
```
cd ~
sudo chown -R YOU:root /var/www/elmsln
# copy and paste these lines to setup your user and install the system
bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh
bash /var/www/elmsln/scripts/install/elmsln-install.sh
```
to verify that it worked you should be able to do the following
`drush sa`
`drush @online status`

to set up ease of use and standard development for other users that need to administer the system run the following as them
`bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh`

## Single Sign On
There are examples included with elmsln-config-vagrant to provide SSO via
the drupal bakery module. Bakery is included and supported in elmsln core but isn't the most robust of options. ELMSLN's technique and architecture is really only useful when run within an environment that supports single sign on so fallback on bakery if you have to.

For most production use cases it is recommended that you use LDAP, Shibboleth, Cosign, or some other single sign on system as drupal's bakery is limitted in what it provides. ELMSLN really shines when integrated with the rest of your organization anyway!

# EXTRAS (optional)

## PIWIK
Install the analytics package by pointing a domain to the
elmsln/domains/analytics.  This is running piwik and has config and tmp files
modified to point to the symlink directories in the config directory.

Create a database named analytics_{host} to match the rest of your systems.
You'll need to create a user / password and then  run through the installation
at analytics.{domain}. There are examples in the cis_example modules included
with this package as to how that might look.

elmsln-config-vagrant also includes a working analytics example to see how
a feature might be created to help make hooking in new systems easier.

## MCRYPT
You might need / want mcrypt if you are going to use file system encryption. All handsfree installers include this automatically.

Go here: https://mirrors.fedoraproject.org/publiclist/EPEL/6/x86_64/#US find a mirror that you want to use.

This example is 64 bit RHEL 6 building the rpm
```
wget http://ftp.linux.ncsu.edu/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
rpm -Uvh epel-release-6-8.noarch.rpm
# install it
yum -y install php-mcrypt
```

*Ex Uno Plures*
