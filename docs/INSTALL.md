#ELMSLN - Installation Guide

## Hands free install
There are some handsfree install routines (copy and paste) that you can try. This is the preferred method of installing ELMS Learning Network as it'll get you up and running with the least steps possible. You can watch @bradallenfisher [install via this method on ELMSLN](https://drupal.psu.edu/blog/post/elmsln-aws-ec2).

[This one-line builder](https://rawgit.com/elmsln/install-builder/master/install.html) can help you generate a one-line command to copy and paste.

### CentOS 6.x / RHEL 6.x
[Example Deployment](https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/centos/example-deploy)
### CentOS 7.x / RHEL 7.x
[Example Deployment](https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/centos7/example-deploy)
### AWS EC2 AMI
[Example Deployment](https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/amazon/example-deploy)
### Ubuntu 12.x / Debian 7.x
[Example Deployment](https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/ubuntu12/example-deploy)
### Ubuntu 14.x / Debian 8.x
[Example Deployment](https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/ubuntu14/example-deploy)

Hands free has some arguments passed into it to get going but these are for installation against a fresh copy of a server. If you install with the default options provided in those (with addresses of elmsln.dev) you'll want to make sure you modify your local `/etc/hosts` file to reflect these fake addresses.

See the [Vagrant installation documentation](https://elmsln.readthedocs.io/en/latest/development/Vagrant-Step-by-Step-setup/) on how to do this though in the installer you'll see a big ELMSLN ascii art message that should tell you what to place there based on your server.

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
https://piwik.org/download/
We love Piwik. It's a great open source user analytics tool that can help you track and aid students with technical support issues as well as gain insight into how they are accessing your content. ELMS:LN has native support via the piwik module included with Drupal. It is recommended to install on its own server.

## MCRYPT
You might need / want mcrypt if you are going to use file system encryption. All handsfree installers include this automatically.

Go here: https://mirrors.fedoraproject.org/publiclist/EPEL/6/x86_64/#US find a mirror that you want to use.

This example is 64 bit RHEL 6 building the rpm
```
wget http://ftp.linux.ncsu.edu/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
rpm -Uvh epel-release-6-8.noar- Installation: INSTALL.mdch.rpm
# install it
yum -y install php-mcrypt
```

## ChromeOS / ChromeBit / IoT
If you want to install ELMS:LN on a google Chromebit it is possible given it has 2 gigs of RAM (our minimum requirements). This is not supported but these are the steps to do it from testing:
- `http://www.howtogeek.com/162120/how-to-install-ubuntu-linux-on-your-chromebook-with-crouton/`
- at the end instead of launching X-windows run `sudo enter-chroot` which will boot into the device
- `sudo -i` to switch to root
- install as if this was Ubuntu 12, because it is. `https://github.com/elmsln/elmsln/blob/master/scripts/install/handsfree/ubuntu12/example-deploy`

Not working currently as it doesn't install mysql for some reason correctly



*Ex Uno Plures*
