#!/usr/bin/env bash

# create ssh-config file
ssh_config="/Users/scienceonlineed/Documents/websites/elmsln/.vagrant/ssh-config"
vagrant ssh-config > "$ssh_config"

local_root="/Users/scienceonlineed/Documents/websites/elmsln"
remote_root="ssh://default//var/www/elmsln"

# create unison profile
profile="  
root = $local_root
root = $remote_root
ignore = Name {.git,.vagrant,node_modules}

prefer = $local_root  
repeat = 2  
terse = true 
perms = -1  
sshargs = -F $ssh_config  
"

# write profile

if [ -z ${USERPROFILE+x} ]; then  
  UNISONDIR=$HOME
else  
  UNISONDIR=$USERPROFILE
fi

cd $UNISONDIR  
[ -d .unison ] || mkdir .unison
echo "$profile" > .unison/elmsln.prf