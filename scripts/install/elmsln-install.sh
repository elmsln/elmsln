#!/bin/bash
# This install script will build job files correctly that drush-create-site
# will pick up and build the initial sites for the system.
# Only user this to initially setup the system as it will add in jobs
# that would fail after the fact.

# provide messaging colors for output to console
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

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# include our config settings
source ../../config/scripts/drush-create-site/config.cfg

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

core='7.x'
distros=('cis' 'mooc' 'cle' 'icor' 'elmsmedia' 'meedjum_blog' 'remote_watchdog')
stacklist=('online' 'courses' 'studio' 'interact' 'media' 'blog' 'remote_watchdog')
buildlist=('courses' 'studio' 'interact' 'media' 'blog')
# array of instance definitions for the distro type
instances=('FALSE' 'TRUE' 'TRUE' 'TRUE' 'FALSE' 'TRUE' 'FALSE')
ignorelist=('TRUE' 'FALSE' 'FALSE' 'FALSE' 'TRUE' 'FALSE' 'TRUE')
defaulttitle=('Course information system' 'Course outline' 'Collaborative studio' 'Interactive object repository' 'Media asset management' 'Course Blog' 'Remote logging')
moduledir=$elmsln/config/shared/drupal-${core}/modules/_elmsln_scripted
cissettings=${university}_${host}_settings

# used for random password generation
COUNTER=0
char=(0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V X W Y Z)
max=${#char[*]}

# generate a scripted directory
if [ ! -d ${moduledir} ];
  then
  sudo mkdir -p ${moduledir}
  sudo mkdir -p ${moduledir}/${university}
fi
# work on authoring the connector module automatically
if [ ! -d ${moduledir}/${university}/${cissettings} ];
  then
  sudo mkdir -p ${moduledir}/${university}/${cissettings}
  sudo chown -R $USER:$USER ${moduledir}
  infofile=${moduledir}/${university}/${cissettings}/${cissettings}.info
  modulefile=${moduledir}/${university}/${cissettings}/${cissettings}.module
  touch $infofile
  chmod 744 $infofile
  touch $modulefile
  chmod 744 $modulefile
  # write the .info file
  echo -e "name = ${university} ${host} Settings\ndescription = This contains registry information for all ${host} connection details\ncore = ${core}\npackage = ${university}" >> $infofile
  # write the .module file
  echo -e "<?php\n\n// service module that makes this implementation specific\n\n/**\n * Implements hook_cis_service_registry().\n */\nfunction ${university}_${host}_settings_cis_service_registry() {\n  \$items = array(\n" >> $modulefile
  # write the array of connection values dynamically
  for distro in "${distros[@]}"
  do
    # array built up to `word
    echo -e "    // ${distro} distro instance called ${stacklist[$COUNTER]}\n    '${distro}' => array(\n      'protocol' => '${protocol}',\n      'service_address' => '${serviceprefix}${stacklist[$COUNTER]}.${serviceaddress}',\n      'address' => '${stacklist[$COUNTER]}.${address}',\n      'user' => 'SERVICE_${distro}_${host}',\n      'mail' => 'SERVICE_${distro}_${host}@${emailending}'," >> $modulefile
    # generate a random 30 digit password
    pass=''
    for i in `seq 1 30`
    do
      let "rand=$RANDOM % 62"
      pass="${pass}${char[$rand]}"
    done
    # write password to file
    echo -e "      'pass' => '$pass'," >> $modulefile
    # finish off array
    echo -e "      'instance' => ${instances[$COUNTER]}," >> $modulefile
    echo -e "      'default_title' => '${defaulttitle[$COUNTER]}'," >> $modulefile
    echo -e "      'ignore' => ${ignorelist[$COUNTER]},\n    ),\n" >> $modulefile
    COUNTER=$COUNTER+1
 done
  # close out function and file
  echo -e "  );\n\n  return \$items;\n}\n\n" >> $modulefile
  # add the function to include this in build outs automatically
  echo -e "/**\n * Implements hook_cis_service_instance_options_alter().\n */\nfunction ${university}_${host}_settings_cis_service_instance_options_alter(&\$options, \$course, \$service) {\n  // modules we require for all builds\n  \$options['en'][] = '$cissettings';\n}\n" >> $modulefile
fi

#test mysql login
#mysql -u$dbsu -p$dbsupw -e exit
#if [[ $? > 0 ]];then
  #echo "mysql connection failed"
  #exit 1
#fi

# make sure drush is happy before we begin drush calls
drush cc drush
sudo chown -R $USER:$USER $HOME/.drush
# make sure the entire directory is writable by the current user
sudo chown -R $USER:$USER $elmsln

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
  drush site-install -y --db-url=mysql://elmslndfltdbo:$dbpw@localhost/default_$build --db-su=$dbsu --db-su-pw=$dbsupw --account-mail="$admin" --site-mail="$site_email"
done

# install the CIS site
# generate a random 30 digit password
dbpw=''
for k in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${dbpw}${char[$rand]}"
done
cd $stacks/online
sitedir=$stacks/online/sites

drush site-install cis -y --db-url=mysql://online_$host:$dbpw@localhost/online_$host --db-su=$dbsu --db-su-pw=$dbsupw  --account-mail="$admin" --site-mail="$site_email" --site-name="Online"
#move out of online site directory to host
sudo mkdir -p $sitedir/online/$host
sudo mkdir -p $sitedir/online/$host/files
#modify ownership of these directories
sudo chown -R $wwwuser:$webgroup $sitedir/online/$host/files
sudo chmod -R 755 $sitedir/online/$host/files

# setup private file directory
sudo mkdir -p $drupal_priv/online
sudo mkdir -p $drupal_priv/online/online
sudo chown -R $wwwuser:$webgroup $drupal_priv
sudo chmod -R 755 $drupal_priv

# copy the default settings file to this location
# we leave the original for the time being because this is the first instace
# of the system. most likely we'll always need a default to fall back on anyway
sudo cp "$sitedir/default/settings.php" "$sitedir/online/$host/settings.php"
sudo chown $USER:$USER $sitedir/default/settings.php
sudo chown $USER:$USER $sitedir/online/$host/settings.php
sudo chmod -R 755 $sitedir/online/$host/settings.php

# establish these values real quick so its more readable below
online_domain="online.${address}"
online_service_domain="${serviceprefix}online.${serviceaddress}"
#add site to the sites array
echo "\$sites = array(" >> $sitedir/sites.php
echo "  '$online_domain' => 'online/$host'," >> $sitedir/sites.php
echo "  '$online_service_domain' => 'online/services/$host'," >> $sitedir/sites.php
echo ");" >> $sitedir/sites.php
# set base_url
echo "\$base_url= '$protocol://$online_domain';" >> $sitedir/online/$host/settings.php


# clean up tasks
drush -y --uri=$protocol://$online_domain vset site_slogan 'Welcome to ELMSLN'
drush -y --uri=$protocol://$online_domain en $cissettings
drush -y --uri=$protocol://$online_domain en cis_restws
drush -y --uri=$protocol://$online_domain vset cron_safe_threshold 0
drush -y --uri=$protocol://$online_domain vset user_register 1
drush -y --uri=$protocol://$online_domain vset user_email_verification 0
drush -y --uri=$protocol://$online_domain vset preprocess_css 1
drush -y --uri=$protocol://$online_domain vset preprocess_js 1
drush -y --uri=$protocol://$online_domain vset cis_college_name $host
drush -y --uri=$protocol://$online_domain vset file_private_path ${drupal_priv}/online/online
drush -y --uri=$protocol://$online_domain vset cis_build_lms cis_account_required,cis_lms_required
drush -y --uri=$protocol://$online_domain vset cis_build_code cis_account_required,cis_lms_required
drush -y --uri=$protocol://$online_domain vset cis_build_authenticated cis_account_required
drush -y --uri=$protocol://$online_domain vdel update_notify_emails

# specialized job to automatically produce service nodes to match registry we made
drush -y --uri=$protocol://$online_domain cis-sync-reg
# may seem odd but basically we want to import a default set of nodes then disable
# everything required to do this because it can throw a lot of errors but does work
drush -y --uri=$protocol://$online_domain en cis_sample_content

# uninstall all these now because they should be in correctly as sample nodes
drush -y --uri=$protocol://$online_domain dis cis_sample_content node_export node_export_features node_export_dependency
drush -y --uri=$protocol://$online_domain pm-uninstall cis_sample_content
drush -y --uri=$protocol://$online_domain pm-uninstall node_export_features node_export_dependency
drush -y --uri=$protocol://$online_domain pm-uninstall node_export

# run cron for the good of the order
drush -y --uri=$protocol://$online_domain cron

# print out a reset password link for the online site so you can gain access
drush -y --uri=$protocol://$online_domain upwd admin --password=admin

# add in our cache bins now that we know it built successfully
echo "" >> $sitedir/online/$host/settings.php
echo "" >> $sitedir/online/$host/settings.php
echo "\$conf['cache_prefix'] = 'online_$host';" >> $sitedir/online/$host/settings.php
echo "" >> $sitedir/online/$host/settings.php
echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/online/$host/settings.php

# adding servies conf file
if [ ! -d $sitedir/online/services/$host ];
  then
    sudo mkdir -p $sitedir/online/services/$host
    sudo mkdir -p $sitedir/online/services/$host/files
    sudo chown -R $wwwuser:$webgroup $sitedir/online/services/$host/files
    sudo chmod -R 755 $sitedir/online/services/$host/files
    if [ -f $sitedir/online/$host/settings.php ]; then
      sudo cp $sitedir/online/$host/settings.php $sitedir/online/services/$host/settings.php
    fi
    if [ -f $sitedir/online/services/$host/settings.php ]; then
      sudo chown $USER:$webgroup $sitedir/online/services/$host/settings.php
      echo "" >> $sitedir/online/services/$host/settings.php
      echo "" >> $sitedir/online/services/$host/settings.php
      echo "\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $sitedir/online/services/$host/settings.php
    fi
fi

# perform some clean up tasks
# piwik directories
sudo chown -R $wwwuser:$webgroup $elmsln/config/_nondrupal/piwik
sudo chmod -R 755 $elmsln/config/_nondrupal/piwik
sudo chown -R $wwwuser:$webgroup $elmsln/core/_nondrupal/piwik
# check for tmp directory in config area
if [ ! -d $elmsln/config/_nondrupal/piwik/tmp ];
then
  sudo mkdir $elmsln/config/_nondrupal/piwik/tmp
  sudo chown -R $wwwuser:$webgroup $elmsln/config/_nondrupal/piwik/tmp
fi
sudo chmod -R 0755 $elmsln/config/_nondrupal/piwik/tmp
# jobs file directory
sudo chown -R $wwwuser:$webgroup $elmsln/config/jobs
sudo chmod -R 755 $elmsln/config/jobs
# make sure everything in that folder is as it should be ownerwise
sudo chown -R $wwwuser:$webgroup $sitedir/online/$host/files
# make sure webserver owns the files
sudo find $configsdir/stacks/ -type d -name files | sudo xargs chown -R $wwwuser:$webgroup

# clean up tmp directory .htaccess to make drupal happy
sudo rm /tmp/.htaccess
# forcibly apply 1st ELMSLN global update since it isn't fixed in CIS
# this makes it so that we don't REQUIRE multi-sites to run CIS (stupid)
# while still fixing the issue with httprl when used in multisites
drush -y --uri=$protocol://$online_domain cook d7_elmsln_global_1413916953

# a message so you know where our head is at. you get candy if you reference this
elmslnecho "╔───────────────────────────────────────────────────────────────╗"
elmslnecho "║           ____  Welcome to      ____                          ║"
elmslnecho "║          |     |      /\  /\   /     |     |\   |             ║"
elmslnecho "║          |____ |     |  \/  |  \___  |     | \  |             ║"
elmslnecho "║          |     |     |      |      \ |     |  \ |             ║"
elmslnecho "║          |____ |____ |      |  ____/ |____ |   \|             ║"
elmslnecho "║                                                               ║"
elmslnecho "╟───────────────────────────────────────────────────────────────╢"
elmslnecho "║ If you are still having problems you may submit issues to     ║"
elmslnecho "║   http://github.com/btopro/elmsln/issues                      ║"
elmslnecho "╟───────────────────────────────────────────────────────────────╢"
elmslnecho "║ NOTES                                                         ║"
elmslnecho "║ There is a module that was authored during installation at    ║"
elmslnecho "║ config/shared/drupal-7.x/modules/_elmsln_scripted             ║"
elmslnecho "║ You may want to open this up and review it but it is your     ║"
elmslnecho "║ connection keychain for how all the webservices talk.         ║"
elmslnecho "║                                                               ║"
elmslnecho "╠───────────────────────────────────────────────────────────────╣"
elmslnecho "║ Use this link to access the Course Information System:        ║"
elmslnecho "║   $protocol://$online_domain                                   "
elmslnecho "║                                                               ║"
elmslnecho "║Welcome to the Singularity of edtech.. build the future..      ║"
elmslnecho "╚───────────────────────────────────────────────────────────────╝"
