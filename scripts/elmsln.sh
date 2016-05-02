#!/bin/sh
# elmsln.sh is intended to be an interactive prompt for administering elmsln
# this provides shortcuts for running commands you could have otherwise
# but like the developers of the project, are far too lazy to search for.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
source ../config/scripts/drush-create-site/config.cfg

#provide messaging colors for output to console
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

# prompt the user
prompt="Leafy: Type the number for what you'd like to do today: "
items=("oops, didn't want to be here" 'show me the sites drush knows about' 'upgrade the ELMSLN code base and system' 'upgrade just the drupal sites' 'backup the drupal databases.' 'backup the configuration directory.' 'clean up directory and file permissions issues.' 'refresh the drush plugins my user has' 'setup (or refresh) the recommended elmsln configuration for my user account' 'apply server level upgrades (can not be undone)' 'add domain support (can not be undone)' 'remove a drupal site from ELMSLN (can not be undone)' 'restart apache, mysql and php (can not be undone)')
locations=('' '' 'upgrade/elmsln-upgrade-system.sh' 'upgrade/elmsln-upgrade-sites.sh' '' 'utilities/backup-config.sh' 'utilities/harden-security.sh' 'utilities/refresh-drush-config.sh' 'install/users/elmsln-admin-user.sh' 'upgrade/elmsln-bash-upgrades.sh' 'utilities/add-domain-support.sh' 'drush-create-site/rm-site.sh' 'utilities/restart-elmsln.sh')
commands=('' 'drush sa' 'bash' 'bash' 'drush @elmsln sql-dump --result-file --y' 'sudo bash' 'sudo bash' 'bash' 'bash' 'sudo bash' 'sudo bash' 'sudo bash' 'sudo bash')

# allow for dropping into developer mode if a flag isset
if [[ ! -z $1 && $1 == 'dev' ]]; then
  elmslnecho 'DEVELOPER MODE'
  items+=('Create new tool')
  locations+=('developer/create-new-tool.sh')
  commands+=('bash')
fi

# render the menu options
menuitems() {
  elmslnecho "Hi I'm Leafy, what would you like me to do for you: "
  for i in ${!items[@]}; do
    echo $((i))") ${items[i]}"
  done
  [[ "$msg" ]] && echo "" && echo "$msg"; :
}
version=$(cat "$elmsln/VERSION.txt")
config_version=$(cat "$elmsln/config/SYSTEM_VERSION.txt")
courses=$(drush @online efq node course --count)
seviceinstance=$(drush @online efq node service_instance --count)
sections=$(drush @online efq field_collection_item field_sections --count)
if [[ $config_version != $version ]]; then
  elmslnwarn "Config version different from code version! It is recommended that you select apply server level upgrades from the below list."
fi
elmslnecho "ELMSLN VERSION: $version"
elmslnecho "Courses in CIS: $courses"
elmslnecho "Service instances in CIS: $seviceinstance"
elmslnecho "Sections in CIS: $sections"

# make sure we get a valid response before doing anything
while menuitems && read -rp "$prompt" num && [[ "$num" ]]; do
  (( num > 0 && num <= ${#items[@]} )) || {
    if [ $num == 0 ]; then
      elmslnwarn 'Leafy: See ya later!'
      exit
    fi
    msg="Leafy: $num is not a valid option, try again."; continue
  }
  # if we got here it means we have valid input
  choice="${items[num]}"
  if [ "${locations[num]}" == '' ]; then
    location=''
  else
    location="/var/www/elmsln/scripts/${locations[num]}"
  fi
  cmd="${commands[num]}"
  elmslnecho "Leafy: $choice ($cmd $location)"
  $cmd $location
done