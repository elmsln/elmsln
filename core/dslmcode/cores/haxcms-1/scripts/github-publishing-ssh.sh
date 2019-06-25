#!/bin/bash
if [ -d "~/.config" ]; then
  chmod 755 ~/.config
fi
# set some defaults for publishing on the box
cat >> ~/.ssh/config <<EOL

host github.com
  HostName github.com
  IdentityFile /var/www/html/_config/.ssh/haxyourweb
  User git

EOL
