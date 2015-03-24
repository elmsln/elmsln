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

mysql_install_db
# used for random password generation
COUNTER=0
char=(0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V X W Y Z)
max=${#char[*]}
# generate a random 30 digit password
pass=''
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  pass="${pass}${char[$rand]}"
done
# make mysql secure so no one knows the password except this script
cat <<EOF | mysql_secure_installation

Y
$pass
$pass
Y
Y
Y
Y
EOF
elmslnwarn "You'll never see this again so if you care.."
elmslnwarn "mysql root: $pass"
# generate a password for the elmslndbo account
dbopass=''
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbopass="${pass}${char[$rand]}"
done
# now make an elmslndbo
cat <<EOF | mysql -u root --password=$pass
CREATE USER 'elmslndbo'@'localhost' IDENTIFIED BY '$dbopass';
GRANT ALL PRIVILEGES ON *.* TO 'elmslndbo'@'localhost' WITH GRANT OPTION;
FLUSH PRIVILEGES;
exit
EOF
# now we can start into the actual ELMS stuff
cd $HOME
# @todo pipe in values
cat <<EOF | bash /var/www/elmsln/scripts/install/root/elmsln-preinstall.sh

$1
$2
$3
$4
$5
$6
$7
$8
$9
${10}
elmslndbo
$dbopass
${11}
${12}
EOF
# copy and paste this
cd $HOME
source .bashrc
# replace YOU with your username and root with whatever group you want
# to own the system. If not sure leave the second value as root though
# admin is common as well.
chown -R root:root /var/www/elmsln
# setup user as admin
bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh
# install system and off we go
bash /var/www/elmsln/scripts/install/elmsln-install.sh

# give them a roadmap for mapping to this until proving a real domain
stacklist=('online' 'courses' 'studio' 'interact' 'media' 'blog' 'comply' 'discuss')
domain=$4
ip=$(hostname -I)
elmslnecho "If you are developing with this and don't have a valid domain yet you can copy the following into your local machine's /etc/hosts file:"
elmslnecho "# ELMSLN cloud development"
# loop through and write each of these here
for stack in "${stacklist[@]}"
do
  elmslnecho "${ip}      ${stack}.${domain}"
done
