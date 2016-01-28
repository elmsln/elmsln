#!/usr/bin/env bash

# Assumes you have a symlink to the elmsln repo in your home directory on your local computer
local_root="$HOME/elmsln"
remote_root="ssh://default//var/www/elmsln"

# create ssh-config file
ssh_config="$local_root/.vagrant/ssh-config"
vagrant ssh-config > "$ssh_config"

# create unison profile
profile="
perms = 0
root = $local_root
root = $remote_root
path = core
path = docs
path = domains
path = scripts
path = config/shared
ignore = Name {.git,.vagrant,node_modules}

prefer = $local_root  
repeat = 2  
terse = true 
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
