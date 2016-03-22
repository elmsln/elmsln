#!/bin/bash
# this script assumes ELMSLN code base is on the server and that the server
# has the correct packages in place to start working. Now we need to run
# some things against mysql because root is completely wide open. Part
# of the handsfree mindset is that, effectively, no one knows root for
# mysql and instead, a high credential elmslndbo is created

# provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=${txtbld}$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
}

# detect OS version based on the ones we have support for
if [ -f /etc/debian_version ]; then
  elmslnecho "Detected Debian-based OS"
  os='ubuntu'
  apt-get update && apt-get -y install wget git
elif [ -f /etc/redhat-release ]; then
  elmslnecho "Detected RedHat-based OS"
  yes | yum -y install wget git
  if grep -r 'VERSION_ID="7"' /etc/os-release ; then
    os='centos7'
  else
    os='centos'
    wget http://rpms.famillecollet.com/enterprise/remi-release-6.rpm
    rpm -Uvh remi-release-6*.rpm
    wget http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
    rpm -Uvh epel-release-6*.rpm
  fi
elif grep -iq "Amazon Linux" /etc/issue ; then
  os='amazon'
  yes | yum -y install wget git
else
  elmslnwarn "Sorry, we don't know how to automatically install ELMSLN on your system."
  elmslnwarn ""
  elmslnwarn "See http://elmsln.readthedocs.org/en/latest/INSTALL/ for how to install."
  exit 1
fi
# run installer selected
git clone https://github.com/elmsln/elmsln.git /var/www/elmsln && bash /var/www/elmsln/scripts/install/handsfree/${os}/${os}-install.sh $1 $2 $3 $4 $5 $6