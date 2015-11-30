#!/bin/bash
# create system level user accounts to improve security and segment elmsln
# on the box from other user accounts / groups

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

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
# Define seconds timestamp
timestamp(){
  date +"%s"
}
# generate a uuid
getuuid(){
  uuidgen -rt
}
# check that we are the root user
if [[ $EUID -ne 0 ]]; then
  elmslnwarn "Must run as root"
  exit 1
fi

# add a user group of elmsln
/usr/sbin/groupadd elmsln
# add the system user and put them in the above group
/usr/sbin/useradd -g elmsln ulmus -m -d /home/ulmus -s /bin/bash -c "ELMSLN task runner"

# create a new file inside sudoers.d
touch /etc/sudoers.d/ulmus

# this user can do anything basically since it has to create so much stuff
echo "ulmus ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/ulmus
# replicate the .composer directory for this user since composer doesn't like sudo -i
cp -R /root/.composer /home/ulmus/
chown -R ulmus:elmsln /home/ulmus/
# this user can just run drush commands and is used much more often
# now run this as the user we just made so it has the drush plugins
sudo -u ulmus bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh /home/ulmus

chown -R ulmus:elmsln /home/ulmus/
chmod -R 770 /home/ulmus
# add the system user and put them in the above group
/usr/sbin/useradd -g elmsln ulmusdrush -m -d /home/ulmusdrush -s /bin/bash -c "Drush task runner"
# create a new file inside sudoers.d so we can add some people here
touch /etc/sudoers.d/ulmusdrush
# commands this user can do
echo "ulmusdrush ALL=(ALL) NOPASSWD: /sbin/service mysqld status" >> /etc/sudoers.d/ulmusdrush
echo "ulmusdrush ALL=(ALL) NOPASSWD: /sbin/service httpd status" >> /etc/sudoers.d/ulmusdrush
echo "ulmusdrush ALL=(ALL) NOPASSWD: /sbin/service mysqld restart" >> /etc/sudoers.d/ulmusdrush
echo "ulmusdrush ALL=(ALL) NOPASSWD: /sbin/service httpd restart" >> /etc/sudoers.d/ulmusdrush
# replicate the .composer directory for this user since composer doesn't like sudo -i
cp -R /root/.composer /home/ulmusdrush/
chown -R ulmusdrush:elmsln /home/ulmusdrush/

# this user can just run drush commands and is used much more often
sudo -u ulmusdrush bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh /home/ulmusdrush

chown -R ulmusdrush:elmsln /home/ulmusdrush/
chmod -R 770 /home/ulmusdrush
elmslnecho "users created for ulmus and ulmusdrush to run backend commands"
