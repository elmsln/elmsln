local ret_status="%(?:%{$fg_bold[green]%}➜ :%{$fg_bold[red]%}➜ )"
PROMPT='${ret_status} %{$fg[cyan]%}%c%{$reset_color%} $(git_prompt_info)$(elmsln_info): '

ZSH_THEME_GIT_PROMPT_PREFIX="%{$fg_bold[blue]%}git:(%{$fg[red]%}"
ZSH_THEME_GIT_PROMPT_SUFFIX="%{$reset_color%} "
ZSH_THEME_GIT_PROMPT_DIRTY="%{$fg[blue]%}) %{$fg[yellow]%}✗"
ZSH_THEME_GIT_PROMPT_CLEAN="%{$fg[blue]%})"
txtbld=$(tput bold)$(tput setab 4) # Bold blue bg
bldgrn=${txtbld}$(tput setaf 7) #  white
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}
# Get current context
elmsln_info() {
	if [[ $(pwd) == *"elmsln" ]]; then
	  elmslnecho "$(echo -e '\u273B') $(cat ~/elmsln/VERSION.txt)"
	fi
}
