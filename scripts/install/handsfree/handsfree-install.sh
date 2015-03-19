#!/bin/bash
# hands free driving is the safest kind of driving
# when this is all said and done, no one knows the root mysql password
# no one knows the elmslndbo password except elmsln
# and the entire box is built to exactly what it needs to be from the
# ground up

# this script assumes ELMSLN code base is on the server and that the server
# has the correct packages in place to start working. Now we need to run
# some things against mysql because root is completely wide open. Part
# of the handsfree mindset is that, effectively, no one knows root for
# mysql and instead, a high credential elmslndbo is created
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
exit;
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
$10
elmslndbo
$dbopass
$11
$12
EOF
# copy and paste this
cd $HOME
rm -rf $HOME/.drush
# replace YOU with your username and root with whatever group you want
# to own the system. If not sure leave the second value as root though
# admin is common as well.
chown -R root:root /var/www/elmsln
# setup user as admin
bash /var/www/elmsln/scripts/install/users/elmsln-admin-user.sh
# install system and off we go
bash /var/www/elmsln/scripts/install/elmsln-install.sh
