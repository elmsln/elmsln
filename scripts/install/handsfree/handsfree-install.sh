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
mysql -e "UPDATE mysql.user SET Password = PASSWORD('$pass') WHERE User = 'root'"
# Kill the anonymous users
mysql -e "DROP USER ''@'localhost'"
# Because our hostname varies we'll use some Bash magic here.
mysql -e "DROP USER ''@'$(hostname)'"
# Kill off the demo database
mysql -e "DROP DATABASE test"
# Make our changes take effect
mysql -e "FLUSH PRIVILEGES"
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
cd /var/www/elmsln/core/dslmcode/stacks
stacklist=( $(find . -maxdepth 1 -type d | sed 's/\///' | sed 's/\.//') )
domain=$5
datadomain=$6
prefix=$7
ip=$(hostname -I)
elmslnecho "If you are developing with this and don't have a valid domain yet you can copy the following into your local machine's /etc/hosts file:"
elmslnecho "# ELMSLN development"
# loop through and write each of these here
for stack in "${stacklist[@]}"
do
  elmslnecho "${ip}      ${stack}.${domain}"
done
elmslnecho ""
# loop again on webservices domains
for stack in "${stacklist[@]}"
do
  elmslnecho "${ip}      ${prefix}${stack}.${datadomain}"
done
