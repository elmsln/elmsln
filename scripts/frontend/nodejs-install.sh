#! /bin/bash

# cd into your home directory
cd ~/

# Install NVM with curl
curl https://raw.githubusercontent.com/creationix/nvm/v0.25.0/install.sh | bash

# Make the `nvm` command available to your session
source ~/.bashrc

# Install the latest stable release of node.js
nvm install stable

# Make installed version of node the default
nvm alias default node
