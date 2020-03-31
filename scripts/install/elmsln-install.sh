#!/bin/bash
# This install script will build job files correctly that drush-create-site
# will pick up and build the initial sites for the system.
# Only user this to initially setup the system as it will add in jobs
# that would fail after the fact.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../config/scripts/drush-create-site/config.cfg
# load password config
source ../../config/scripts/drush-create-site/configpwd.cfg
  if [ $dbsupw == '' ];
    then
      dbpwstring=""
    else
      dbpwstring="--db-su-pw=$dbsupw"
  fi
# provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
installlog="${elmsln}/config/tmp/INSTALL-LOG.txt"
steplog="${elmsln}/config/tmp/STEP-LOG.txt"
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
  echo "$1" >> $installlog
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
  echo "$1" >> $installlog
}

#test for empty vars. if empty required var -- exit
if [ -z $fileloc ]; then
  elmslnwarn "please update your config.cfg file, file location variable missing"
  exit 1
fi
if [ -z $site_email ]; then
  elmslnwarn "please update your config.cfg file, site email variable missing"
  exit 1
fi
if [ -z $admin ]; then
  elmslnwarn "please update your config.cfg file, admin email variable missing"
  exit 1
fi
if [ -z $webdir ]; then
  elmslnwarn "please update your config.cfg file, webdir variable missing"
  exit 1
fi
echo '1' > $steplog
# FIGURE OUT WHATS GOING TO BE BUILT
# this is an ultra generic process of analyzing what the system says we can
# build and then actually doing it. When we wrap in the request form and
# automated PR process it will become apparent just how insane this is.

core='7.x'
distros=()
buildlist=()
authoritydistros=()
authoritylist=()
# all distributions / stacks we have
cd $elmsln/core/dslmcode/stacks
stacklist=( $(find . -maxdepth 1 -type d | sed 's/\///' | sed 's/\.//') )
# figure out the distros that go with each stack based on name
for stack in "${stacklist[@]}"
do
  cd $elmsln/core/dslmcode/stacks
  if [ -d "${stack}/profiles" ];
  then
    cd "${stack}/profiles"
    # pull the name of the profile in this stack by ignoring core ones
    profile=$(find . -maxdepth 1 -type l \( ! -iname "testing" ! -iname "minimal" ! -iname "README.txt" ! -iname "standard" \) | sed 's/\///' | sed 's/\.//')
    # add distros to our list
    distros+=($profile)
    cd $profile
    # dig into the file in question for the type values we need
    IFS=$'\n'
    for next in `cat ${profile}.info`
    do
      IFS=' = ' read -a tmp <<< "$next"
      # find the type
      if [[ ${tmp[0]} == 'elmslntype' ]]; then
        distrotype=${tmp[1]}
        if [[ $distrotype == '"authority"' ]]; then
          authoritydistros+=($profile)
          authoritylist+=($stack)
        else
          buildlist+=($stack)
        fi
      fi
    done
  fi
done

# support for hook architecture in bash call outs
hooksdir=$configsdir/scripts/hooks/elmsln-install

# used for random password generation
COUNTER=0
char=(0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V X W Y Z)
max=${#char[*]}

echo '2' > $steplog
# make sure drush is happy before we begin drush calls
drush cc drush
sudo chown -R $USER $HOME/.drush
# make sure the entire directory is writable by the current user
sudo chown -R $USER:$webgroup $elmsln

# random password for defaultdbo
dbpw=''
for j in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${dbpw}${char[$rand]}"
done

# build the default sites
for build in "${buildlist[@]}"
  do
  # install default site for associated stacks in the build list
  cd $stacks/$build
  elmslnecho "drush installing service placeholder: $build"
  drush site-install minimal --v --y --db-url=mysql://elmslndfltdbo:$dbpw@127.0.0.1/default_$build --db-su=$dbsu $dbpwstring --account-mail="$admin" --site-mail="$site_email"
done
echo '3' > $steplog
COUNTER=0
# install authority distributions like online, media, comply
for tool in "${authoritylist[@]}"
  do
  dist=${authoritydistros[$COUNTER]}
  # generate a random 30 digit password
  dbpw=''
  for k in `seq 1 30`
  do
    let "rand=$RANDOM % 62"
    dbpw="${dbpw}${char[$rand]}"
  done
  # move to the directory of this authority
  cd ${webdir}/${tool}
  sitedir=${webdir}/${tool}/sites
  elmslnecho "drush installing authority tool: $tool"
  drush site-install ${dist} --v --y --db-url=mysql://${tool}_${host}:$dbpw@127.0.0.1/${tool}_${host} --db-su=$dbsu $dbpwstring --account-mail="$admin" --site-mail="$site_email" --site-name="$tool"
  #move out of $tool site directory to host
  sudo mkdir -p $sitedir/$tool/$host
  sudo mkdir -p $sitedir/$tool/$host/files
  #modify ownership of these directories
  sudo chown -R $wwwuser:$webgroup $sitedir/$tool/$host/files
  sudo chmod -R 755 $sitedir/$tool/$host/files

  # setup private and tmp file directories
  sudo mkdir -p $drupal_priv/$tool
  sudo mkdir -p $drupal_priv/$tool/$tool
  sudo mkdir -p $drupal_tmp
  sudo chown -R $wwwuser:$webgroup $drupal_priv
  sudo chown -R $wwwuser:$webgroup $drupal_tmp
  sudo chmod -R 755 $drupal_priv
  sudo chmod -R 755 $drupal_tmp

  # copy the default settings file to this location
  # we leave the original for the time being because this is the first instace
  # of the system. most likely we'll always need a default to fall back on anyway
  sudo cp "$sitedir/default/settings.php" "$sitedir/$tool/$host/settings.php"
  sudo chown $USER:$webgroup $sitedir/default/settings.php
  sudo chown $USER:$webgroup $sitedir/$tool/$host/settings.php
  sudo chmod -R 755 $sitedir/$tool/$host/settings.php

  # establish these values real quick so its more readable below
  site_domain="$tool.${address}"
  # add site to the sites array
  echo "\$sites = array(" >> $sitedir/sites.php
  echo "  '${tool}.' . \$GLOBALS['elmslncfg']['address'] => '$tool/' . \$GLOBALS['elmslncfg']['host']," >> $sitedir/sites.php
  echo "  \$GLOBALS['elmslncfg']['serviceprefix'] . '${tool}.' . \$GLOBALS['elmslncfg']['serviceaddress'] => '$tool/services/' . \$GLOBALS['elmslncfg']['host']," >> $sitedir/sites.php
  echo ");" >> $sitedir/sites.php
  # set base_url
  echo "\$base_url = \$GLOBALS['elmslncfg']['protocol'] . '://${tool}.' . \$GLOBALS['elmslncfg']['address'];" >> $sitedir/$tool/$host/settings.php
  # enable the cis_settings registry, set private path, temporary path, then execute clean up routines
  drush -y --uri=$protocol://$site_domain vset file_private_path ${drupal_priv}/$tool/$tool
  drush -y --uri=$protocol://$site_domain vset file_temporary_path ${drupal_tmp}
  drush -y --uri=$protocol://$site_domain vset file_public_path sites/$tool/$host/files
  # distro specific additional install routine
  drush -y --uri=$protocol://$site_domain cook elmsln_$dist --quiet
  # clean up tasks per distro here
  if [ $dist == 'cis' ];
    then
    drush -y --uri=$protocol://$site_domain vset site_slogan 'Welcome to ELMSLN'
    drush -y --uri=$protocol://$site_domain vset cis_college_name $host
  fi

  # add in our cache bins now that we know it built successfully
  echo "" >> $sitedir/$tool/$host/settings.php
  echo "" >> $sitedir/$tool/$host/settings.php
  cachebin="${tool}_${host}"
  echo "\$conf['cache_prefix'] = '${cachebin}';" >> $sitedir/$tool/$host/settings.php
  echo "" >> $sitedir/$tool/$host/settings.php

  # adding servies conf file
  if [ ! -d $sitedir/$tool/services/$host ];
    then
      sudo mkdir -p $sitedir/$tool/services/$host
      sudo mkdir -p $sitedir/$tool/services/$host/files
      sudo chown -R $wwwuser:$webgroup $sitedir/$tool/services/$host/files
      sudo chmod -R 755 $sitedir/$tool/services/$host/files
      if [ -f $sitedir/$tool/$host/settings.php ]; then
        sudo cp $sitedir/$tool/$host/settings.php $sitedir/$tool/services/$host/settings.php
      fi
      if [ -f $sitedir/$tool/services/$host/settings.php ]; then
        sudo chown $USER:$webgroup $sitedir/$tool/services/$host/settings.php
        echo "" >> $sitedir/$tool/services/$host/settings.php
        echo "" >> $sitedir/$tool/services/$host/settings.php
        echo "\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $sitedir/$tool/services/$host/settings.php
        echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/$tool/services/$host/settings.php
      fi
  fi

  echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/$tool/$host/settings.php
  # make sure everything in that folder is as it should be ownerwise
  sudo chown -R $wwwuser:$webgroup $sitedir/$tool/$host/files
  # forcibly apply 1st ELMSLN global update since it isn't fixed tools
  # this makes it so that we don't REQUIRE multi-sites to run tools (stupid)
  # while still fixing the issue with httprl when used in multisites
  drush -y --uri=$protocol://$site_domain cook d7_elmsln_global_1413916953 --dr-locations=/var/www/elmsln/scripts/upgrade/drush_recipes/d7/global --quiet
  # ELMSLN clean up for authority distributions (single point)
  drush -y --uri=$protocol://$site_domain cook elmsln_authority_setup --quiet

  COUNTER=$COUNTER+1
done
echo '4' > $steplog
# perform some clean up tasks
# jobs file directory
sudo chown -R $wwwuser:$webgroup $elmsln/config/jobs
sudo chmod -R 755 $elmsln/config/jobs
# make sure webserver owns the files
sudo find $configsdir/stacks/ -type d -name files | sudo xargs chown -R $wwwuser:$webgroup

# clean up tmp directory .htaccess to make drupal happy
sudo rm /tmp/.htaccess
# last second security hardening as clean up to enforce defaults
sudo bash /var/www/elmsln/scripts/utilities/harden-security.sh
# hook post-install.sh
if [ -f  $hooksdir/post-install.sh ]; then
  # invoke this hook cause we found a file matching the name we need
  bash $hooksdir/post-install.sh
fi
echo '5' > $steplog
# set concurrency to help speed up install
concurrent=2
adminpw=''
for k in `seq 1 8`
do
  let "rand=$RANDOM % 62"
  adminpw="${adminpw}${char[$rand]}"
done
# make sure user password is admin as a fallback
elmslnecho "Set admin account everywhere"
drush @elmsln upwd admin --password=${adminpw} --concurrency=${concurrent} --strict=0 --y  --quiet
# enable bakery everywhere by default
elmslnecho "Enable bakery for unified logins"
drush @elmsln en elmsln_bakery --concurrency=${concurrent} --strict=0 --y  --quiet
# run all the existing crons so that they hit the CIS data and get sing100 for example
elmslnecho "Run Cron to do some clean up"
drush @elmsln cron --concurrency=${concurrent} --strict=0 --y  --quiet
# node access rebuild which will also clear caches
elmslnecho "Rebuild node access permissions"
drush @elmsln php-eval 'node_access_rebuild();' --concurrency=${concurrent} --strict=0 --y  --quiet
# revert everything as some last minute clean up
elmslnecho "Global feature revert as clean up"
drush @elmsln fr-all --concurrency=${concurrent} --strict=0 --y  --quiet
# APDQC cache bin to memory shift
drush @elmsln apdqc --concurrency=${concurrent} --strict=0 --y  --quiet
drush @elmsln apdqc --concurrency=${concurrent} --strict=0 --y  --quiet
# seed entity caches
elmslnecho "Seed some initial caches on all sites"
drush @elmsln ecl --concurrency=${concurrent} --strict=0 --y  --quiet
echo '6' > $steplog

# you get candy if you reference this
elmslnecho "╔✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻╗"
elmslnecho "║                               ✻                               ║"
elmslnecho "║                         ✻     ║     ✻                         ║"
elmslnecho "║                            ║  ║  ║                            ║"
elmslnecho "║                               ✻                               ║"
elmslnecho "║                            ║  ║  ║                            ║"
elmslnecho "║                         ✻     ║     ✻                         ║"
elmslnecho "║                               ✻                               ║"
elmslnecho "║                                                               ║"
elmslnecho "║                Welcome to                                     ║"
elmslnecho "║                                                               ║"
elmslnecho "║   EEEEEE   LL       MM    MM    SSSSS       LL      NN   NN   ║"
elmslnecho "║   EE       LL       MMM  MMM   SS       ✻   LL      NNN  NN   ║"
elmslnecho "║   EEEEE    LL       MM MM MM    SSSSS       LL      NN N NN   ║"
elmslnecho "║   EE       LL       MM    MM        SS  ✻   LL      NN  NNN   ║"
elmslnecho "║   EEEEEE   LLLLL    MM    MM    SSSSS       LLLLL   NN   NN   ║"
elmslnecho "║                                                               ║"
elmslnecho "╟───────────────────────────────────────────────────────────────╢"
elmslnecho "║ Brought to you by developer, faculty and staff from:          ║"
elmslnecho "║   Penn State College of Arts & Architecture                   ║"
elmslnecho "║   Penn State Eberly College of Science                        ║"
elmslnecho "║   Penn State Smeal College of Business                        ║"
elmslnecho "║   Buttercups Training                                         ║"
elmslnecho "║   You!                                                        ║"
elmslnecho "╟───────────────────────────────────────────────────────────────╢"
elmslnecho "║ Install issues logged to:                                     ║"
elmslnecho "║   /var/www/elmsln/config/tmp/INSTALL-LOG.txt                  ║"
elmslnecho "║ If you have issues, submit them to                            ║"
elmslnecho "║   http://github.com/elmsln/elmsln/issues                      ║"
elmslnecho "╟───────────────────────────────────────────────────────────────╢"
elmslnecho "║ ✻NOTES✻                                                       ║"
elmslnecho "║ There is a module that was authored during installation at    ║"
elmslnecho "║ config/shared/drupal-7.x/modules/_elmsln_scripted             ║"
elmslnecho "║ You may want to open this up and review it but it is your     ║"
elmslnecho "║ connection keychain for how all the webservices talk.         ║"
elmslnecho "║                                                               ║"
elmslnecho "╠───────────────────────────────────────────────────────────────╣"
elmslnecho "║ Use  the following to get started:                            ║"
elmslnecho "║  <a href='$protocol://online.${address}'>$protocol://online.${address}</a>"
elmslnecho "║  username: admin                                              ║"
elmslnecho "║  password: $adminpw                                           ║"
elmslnecho "║  (if in vagrant the password is admin)                        ║"
elmslnecho "║                                                               ║"
elmslnecho "║                        ✻ Ex  Uno Plures ✻                     ║"
elmslnecho "║                        ✻ From one, Many ✻                     ║"
elmslnecho "╚✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻✻╝"
