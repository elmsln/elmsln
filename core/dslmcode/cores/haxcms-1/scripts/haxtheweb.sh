#!/bin/bash
# Welcome to HAXCMS. Decentralize already.

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

# Time to get down to brass tacks
sudo chmod 777 _sites
sudo chmod 775 _config
sudo chmod 777 _config/sites.json
# whew that was hard work. the end.

# jk
# echo a uuid to a salt file we can use later on
touch _config/SALT.txt
echo "$(getuuid)" > _config/SALT.txt
# write private key
pk="$(getuuid)"
sed -i "s/HAXTHEWEBPRIVATEKEY/${pk}/g" _config/config.php
user=$1
pass=$2
email=$3
surgepassword=$4
# enter a super user name, dun dun dun dunnnnnnn!
if [ -z $user ]; then
  read -rp "Super user name:" user
fi
sed -i "s/jeff/${user}/g" _config/config.php
# a super, scary password prompt approaches. You roll a 31 and deal a critical security hit
if [ -z $pass ]; then
  read -rp "Super user password:" pass
fi
sed -i "s/jimmerson/${pass}/g" _config/config.php
# da email, da email, what what, da email. Dear Strong Bad.
if [ -z $email ]; then
  read -rp "Surge email address:" email
fi
# SERGE IS BACK
if [ -z $surgepassword ]; then
  read -rp "Surge password:" surgepassword
fi
# seed login info so we have an account primed

cat <<EOF | surge login

$email
$surgepassword
EOF

# only if you use apache
if [ -z $1 ]; then
  haxecho "www-data or apache is common, hit enter to ignore"
  read -rp "Web server user:" wwwuser
fi
# only if you use apache
if [ -z $1 ]; then
  read -rp "Web server group:" wwwgrp
fi
# account for www user messaging, which is not required
if [ -z ${wwwuser} ]; then
  # I've got a bad feeling about this
  haxwarn "did nothing, make sure your web server user can write to _sites"
else
  sudo chown ${wwwuser}:${wwwgrp} _sites
fi

# you get candy if you reference this
haxecho ""
haxecho "╔✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻╗"
haxecho "║                Welcome to the decentralization.               ║"
haxecho "║                                                               ║"
haxwarn "║                   H  H      AAA     X   X                     ║"
haxwarn "║                   H  H     A   A     X X                      ║"
haxwarn "║                   HHHH     AAAAA      X                       ║"
haxwarn "║                   H  H     A   A     X X                      ║"
haxwarn "║                   H  H     A   A    X   X                     ║"
haxecho "║                                                               ║"
haxecho "╟───────────────────────────────────────────────────────────────╢"
haxecho "║ If you have issues, submit them to                            ║"
haxwarn "║   http://github.com/elmsln/haxcms/issues                      ║"
haxecho "╟───────────────────────────────────────────────────────────────╢"
haxecho "║ ✻NOTES✻                                                       ║"
haxecho "║ All changes should be made in the _config/config.php file     ║"
haxecho "║ which has been setup during this install routine              ║"
haxecho "║                                                               ║"
haxecho "╠───────────────────────────────────────────────────────────────╣"
haxecho "║ Use  the following to get started:                            ║"
haxecho "║                                                               ║"
haxwarn "║    user name:    $user"
haxwarn "║    password:     $pass"
haxecho "║                                                               ║"
haxecho "║                        ✻ Ex  Uno Plures ✻                     ║"
haxecho "║                        ✻ From one, Many ✻                     ║"
haxecho "╚✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻╝"