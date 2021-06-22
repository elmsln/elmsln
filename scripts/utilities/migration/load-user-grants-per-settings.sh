#!/usr/bin/sh
source /var/www/elmsln/config/scripts/drush-create-site/config.cfg
# load password config
source /var/www/elmsln/config/scripts/drush-create-site/configpwd.cfg
txtbld=$(tput bold)             # Bold
bldgrn=$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
}
# these live at 2 3 and 4 levels deep in folder nesting at times
dir="$configsdir"
domains="${webdir}/"
MYSQL=`which mysql`
localdbsu=$dbsu
localdbsupw=$dbsupw
for i in $(find ${dir}/stacks/*/sites/*/*/*/*/settings.php -type f); do
  tmpbase='define("DRUPAL_ROOT", "/var/www/elmsln/core/dslmcode/cores/drupal-7"); include_once DRUPAL_ROOT . "/../../elmsln_environment/elmsln_environment.php";require_once DRUPAL_ROOT . "/includes/bootstrap.inc";include_once "'$i'";'
  tmp=$tmpbase'echo $databases["default"]["default"]["database"];'
  tmpdb=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["username"];'
  tmpusr=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["password"];'
  tmppwd=$(php -r "$tmp")
  Q1="GRANT ALL ON ${tmpdb}.* TO '$tmpusr'@'localhost' IDENTIFIED BY '$tmppwd';"
  Q2="FLUSH PRIVILEGES;"
  SQL="${Q1}${Q2}"
  echo --user=$localdbsu --password=$localdbsupw -e "$SQL"
done
for i in $(find ${dir}/stacks/*/sites/*/*/*/settings.php -type f); do
  tmpbase='define("DRUPAL_ROOT", "/var/www/elmsln/core/dslmcode/cores/drupal-7"); include_once DRUPAL_ROOT . "/../../elmsln_environment/elmsln_environment.php";require_once DRUPAL_ROOT . "/includes/bootstrap.inc";include_once "'$i'";'
  tmp=$tmpbase'echo $databases["default"]["default"]["database"];'
  tmpdb=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["username"];'
  tmpusr=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["password"];'
  tmppwd=$(php -r "$tmp")
  Q1="GRANT ALL ON ${tmpdb}.* TO '$tmpusr'@'localhost' IDENTIFIED BY '$tmppwd';"
  Q2="FLUSH PRIVILEGES;"
  SQL="${Q1}${Q2}"
  echo --user=$localdbsu --password=$localdbsupw -e "$SQL"
done
for i in $(find ${dir}/stacks/*/sites/*/*/settings.php -type f); do
  tmpbase='define("DRUPAL_ROOT", "/var/www/elmsln/core/dslmcode/cores/drupal-7");include_once DRUPAL_ROOT . "/../../elmsln_environment/elmsln_environment.php";require_once DRUPAL_ROOT . "/includes/bootstrap.inc"; include_once "'$i'";'
  tmp=$tmpbase'echo $databases["default"]["default"]["database"];'
  tmpdb=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["username"];'
  tmpusr=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["password"];'
  tmppwd=$(php -r "$tmp")
  Q1="GRANT ALL ON ${tmpdb}.* TO '$tmpusr'@'localhost' IDENTIFIED BY '$tmppwd';"
  Q2="FLUSH PRIVILEGES;"
  SQL="${Q1}${Q2}"
  echo --user=$localdbsu --password=$localdbsupw -e "$SQL"
done
