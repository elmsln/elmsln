ZSH ELMSLN theme
How to set this up if you have oh-mai-zsh installed. Create a symlink in home directory to where elmsln lives like:

ln -s ~/elmsln/scripts/local/zsh_custom ~/zsh_custom

Edit ~/.zshrc and add the following:

ZSH_THEME="elmsln"
ZSH_CUSTOM=~/zsh_custom

close the file and source the config file:
source ~/.zshrc
