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

core='7.x'
distros=('cis' 'mooc' 'cle' 'icor' 'elmsmedia' 'meedjum_blog' 'remote_watchdog')
stacklist=('online' 'courses' 'studio' 'interact' 'media' 'blog' 'remote_watchdog')
buildlist=('courses' 'studio' 'interact' 'media' 'blog')
# array of instance definitions for the distro type
instances=('FALSE' 'TRUE' 'TRUE' 'TRUE' 'TRUE' 'TRUE' 'FALSE')
ignorelist=('TRUE' 'FALSE' 'FALSE' 'FALSE' 'FALSE' 'FALSE' 'TRUE')
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
  sudo mkdir ${moduledir}
  sudo mkdir ${moduledir}/${university}
fi
# work on authoring the connector module automatically
if [ ! -d ${moduledir}/${university}/${cissettings} ];
  then
  sudo mkdir ${moduledir}/${university}/${cissettings}
  infofile=${moduledir}/${university}/${cissettings}/${cissettings}.info
  modulefile=${moduledir}/${university}/${cissettings}/${cissettings}.module
  sudo touch $infofile
  sudo chmod 744 $infofile
  sudo touch $modulefile
  sudo chmod 744 $modulefile
  # write the .info file
  sudo echo -e "name = ${university} ${host} Settings\ndescription = This contains registry information for all ${host} connection details\ncore = ${core}\npackage = ${university}" >> $infofile
  # write the .module file
  sudo echo -e "<?php\n\n// service module that makes this implementation specific\n\n/**\n * Implements hook_cis_service_registry().\n */\nfunction ${university}_${host}_settings_cis_service_registry() {\n  \$items = array(\n" >> $modulefile
  # write the array of connection values dynamically
  for distro in "${distros[@]}"
  do
    # array built up to `word
    sudo echo -e "    // ${distro} distro instance called ${stacklist[$COUNTER]}\n    '${distro}' => array(\n      'protocol' => '${protocol}',\n      'service_address' => '${serviceprefix}${stacklist[$COUNTER]}.${serviceaddress}',\n      'address' => '${stacklist[$COUNTER]}.${address}',\n      'user' => 'SERVICE_${distro}_${host}',\n      'mail' => 'SERVICE_${distro}_${host}@${emailending}',\n" >> $modulefile
    # generate a random 30 digit password
    pass=''
    for i in `seq 1 30`
    do
      let "rand=$RANDOM % 62"
      pass="${pass}${char[$rand]}"
    done
    # write password to file
    sudo echo -e "      'pass' ='$pass',\n" >> $modulefile
    # finish off array
    sudo echo -e "      'instance' => ${instances[$COUNTER]}," >> $modulefile
    sudo echo -e "      'default_title' => '${defaulttitle[$COUNTER]}'," >> $modulefile
    sudo echo -e "      'ignore' => ${ignorelist[$COUNTER]},\n    ),\n" >> $modulefile
    COUNTER=$COUNTER+1
 done
  # close out function and file
  sudo echo -e "  );\n\n  return \$items;\n}\n\n" >> $modulefile
  # add the function to include this in build outs automatically
  sudo echo -e "/**\n * Implements hook_cis_service_instance_options_alter().\n */\nfunction ${university}_${host}_settings_cis_service_instance_options_alter(&\$options, \$course, \$service) {\n  // modules we require for all builds\n  \$options['en'][] = '$cissettings';\n}\n" >> $modulefile
fi

#test for empty vars. if empty required var -- exit
if [ -z $fileloc ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $site_email ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $admin ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $webdir ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $hostfile ]; then
  echo "please update your config.cfg file"
  exit 1
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

# build the default sites
for build in "${buildlist[@]}"
  do
  # install default site for associated stacks in the build list
  cd $stacks/$build
  drush site-install -y --db-url=mysql://elmslndfltdbo:$dbpw@localhost/default_$build --db-su=$dbsu --db-su-pw=$dbsupw --account-mail="$admin" --site-mail="$site_email"
done

# install the CIS site
# generate a random 30 digit password
pass=''
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${pass}${char[$rand]}"
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

#add site to the sites array
sudo echo "\$sites = array(" >> $sitedir/sites.php
sudo echo "  '$online_domain' => 'online/$host'," >> $sitedir/sites.php
sudo echo "  '$online_service_domain' => 'online/services/$host'," >> $sitedir/sites.php
sudo echo ");" >> $sitedir/sites.php
# set base_url
sudo echo "\$base_url= '$protocol://$online_domain';" >> $sitedir/online/$host/settings.php


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
sudo echo "" >> $sitedir/online/$host/settings.php
sudo echo "" >> $sitedir/online/$host/settings.php
sudo echo "\$conf['cache_prefix'] = 'online_$host';" >> $sitedir/online/$host/settings.php
sudo echo "" >> $sitedir/online/$host/settings.php
sudo echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/online/$host/settings.php

# adding servies conf file
if [ ! -d $sitedir/online/services/$host ];
  then
    sudo mkdir -p $sitedir/online/services/$host
    sudo mkdir -p $sitedir/online/services/$host/files
    sudo chown -R $wwwuser:$webgroup $sitedir/online/services/$host/files
    sudo chmod -R 755 $sitedir/online/services/$host/files
    if [ -f $sitedir/online/$host/settings.php ]; then
      sudo cp "$sitedir/online/$host/settings.php" "$sitedir/online/services/$host/settings.php"
    fi
    if [ -f $sitedir/online/services/$host/settings.php ]; then
      sudo echo "" >> $sitedir/online/services/$host/settings.php
      sudo echo "" >> $sitedir/online/services/$host/settings.php
      sudo echo "\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $sitedir/online/services/$host/settings.php
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
sudo find $configsdir/stacks/ -type d -name files | xargs chown -R $wwwuser:$webgroup

# a message so you know where my head is at. you get candy if you reference this
  echo "╔═══════════════════════════════════════════════════════════════╗"
  echo "║           ____  Welcome to      ____                          ║"
  echo "║          |     |      /\  /\   /     |     |\   |             ║"
  echo "║          |____ |     |  \/  |  \___  |     | \  |             ║"
  echo "║          |     |     |      |      \ |     |  \ |             ║"
  echo "║          |____ |____ |      |  ____/ |____ |   \|             ║"
  echo "║                                                               ║"
  echo "╟───────────────────────────────────────────────────────────────╢"
  echo "║ If you are still having problems you may submit an issue at   ║"
  echo "║   http://github.com/btopro/elmsln/issues                      ║"
  echo "╟───────────────────────────────────────────────────────────────╢"
  echo "║ NOTES                                                         ║"
  echo "║ There is a module that was authored during installation at    ║"
  echo "║ config/shared/drupal-7.x/modules/_elmsln_scripted             ║"
  echo "║ You may want to open this up and review it but it is your     ║"
  echo "║ connection keychain for how all the webservices talk.         ║"
  echo "║                                                               ║"
  echo "╠═══════════════════════════════════════════════════════════════╣"
  echo "║ Use this link to access the Course Information System:        ║"
  echo "║ $protocol://$online_domain                                    ║"
  echo "║                                                               ║"
  echo "║Welcome to the Singularity of edtech.. build the future..      ║"
  echo "╚═══════════════════════════════════════════════════════════════╝"
