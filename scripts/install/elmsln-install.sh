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

core='7.x'
distros=('cis' 'mooc' 'studio' 'icor' 'elmsmedia' 'remote_watchdog')
stacklist=('online' 'courses' 'studio' 'interact' 'media' 'remote_watchdog')
buildlist=('courses' 'studio' 'interact' 'media')
# array of instance definitions for the distro type
instances=('FALSE' 'TRUE' 'TRUE' 'TRUE' 'TRUE' 'FALSE')
moduledir=$elmsln/config/shared/drupal-${core}/modules/_elmsln_scripted
cissettings=${university}_${host}_settings

# used for random password generation
COUNTER=0
char=(0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V X W Y Z)
max=${#char[*]}
# generate a scripted directory
if [ ! -d ${moduledir} ];
  then
  mkdir ${moduledir}
  mkdir ${moduledir}/${university}
fi
# work on authoring the connector module automatically
if [ ! -d ${moduledir}/${university}/${cissettings} ];
  then
  mkdir ${moduledir}/${university}/${cissettings}
  infofile=${moduledir}/${university}/${cissettings}/${cissettings}.info
  modulefile=${moduledir}/${university}/${cissettings}/${cissettings}.module
  # write the .info file
  printf "name = ${university} ${host} Settings\ndescription = This contains registry information for all ${host} connection details\ncore = ${core}\npackage = ${university}" >> $infofile
  # write the .module file
  printf "<?php\n\n// service module that makes this implementation specific\n\n/**\n * Implements hook_cis_service_registry().\n */\nfunction ${university}_${host}_settings_cis_service_registry() {\n  \$items = array(\n" >> $modulefile
  # write the array of connection values dynamically
  for distro in "${distros[@]}"
  do
    # array built up to password
    printf "    // ${distro} distro instance called ${stacklist[$COUNTER]}\n    '${distro}' => array(\n      'protocol' => '${protocol}',\n      'service_address' => 'data.${stacklist[$COUNTER]}.${serviceaddress}',\n      'address' => '${stacklist[$COUNTER]}.${address}',\n      'user' => 'SERVICE_${distro}_${host}',\n      'mail' => 'SERVICE_${distro}_${host}@${emailending}',\n      'pass' => '" >> $modulefile
    # generate a random 30 digit password
    pass=''
    for i in `seq 1 30`
    do
      let "rand=$RANDOM % 62"
      pass="${pass}${char[$rand]}"
    done
    # write password to file
    printf $pass >> $modulefile
    # finish off array
    printf "',\n      'instance' => ${instances[$COUNTER]},\n    ),\n" >> $modulefile
    COUNTER=$COUNTER+1
 done
  # close out function and file
  printf "  );\n\n  return \$items;\n}\n\n" >> $modulefile
  # add the function to include this in build outs automatically
  printf "/**\n * Implements hook_cis_service_instance_options_alter().\n */\nfunction ${university}_${host}_settings_cis_service_instance_options_alter(&\$options, \$course, \$service) {\n  // modules we require for all builds\n  \$options['en'][] = '$cissettings';\n}\n" >> $modulefile
fi

# generate a random 30 digit password
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${pass}${char[$rand]}"
done
# build the default sites
for build in "${buildlist[@]}"
  do
  # install default site for associated stacks in the build list
  cd $stacks/$build
  drush site-install -y --db-url=mysql://elmslndfltdbo:$dbpw@localhost/default_$build --db-su=$dbsu --db-su-pw=$dbsupw
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

drush site-install cis -y --db-url=mysql://online_$host:$dbpw@localhost/online_$host --db-su=$dbsu --db-su-pw=$dbsupw --site-mail="$site_email" --site-name="Online"
#move out of online site directory to host
mkdir -p $sitedir/online/$host
mkdir -p $sitedir/online/$host/files
#modify ownership of these directories
chown -R $wwwuser:$webgroup $sitedir/online/$host/files
chmod -R 755 $sitedir/online/$host/files

# copy the default settings file to this location, remove original
mv $sitedir/default/settings.php $sitedir/online/$host/settings.php

#add site to the sites array
printf "\$sites = array(\n  '$online_domain' => 'online/$host',\n" >> $sitedir/sites.php
printf "  '$online_service_domain' => 'online/services/$host',\n);\n" >> $sitedir/sites.php
# set base_url
printf "\n\$base_url= '$protocol://$online_domain';" >> $sitedir/online/$host/settings.php

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
drush -y --uri=$protocol://$online_domain vdel update_notify_emails
drush -y --uri=$protocol://$online_domain cron

# print out a reset password link for the online site so you can gain access
drush -y --uri=$protocol://$online_domain upwd admin --password=admin

# add in our cache bins
printf "\n\n\$conf['cache_prefix'] = 'online_$host';" >> $sitedir/online/$host/settings.php
printf "\n\nrequire_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/online/$host/settings.php

#adding servies conf file
if [ ! -d $sitedir/online/services/$host ];
  then
    mkdir -p $sitedir/online/services/$host
    mkdir -p $sitedir/online/services/$host/files
    chown -R $wwwuser:$webgroup $sitedir/online/services/$host/files
    chmod -R 755 $sitedir/online/services/$host/files
    if [ -f $sitedir/online/$host/settings.php ]; then
      cp $sitedir/online/$host/settings.php $sitedir/online/services/$host/settings.php
    fi
    if [ -f $sitedir/online/services/$host/settings.php ]; then
      printf "\n\n\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $sitedir/online/services/$host/settings.php
    fi
fi

# perform some clean up tasks
# piwik directories
chown -R $wwwuser:$webgroup $elmsln/config/_nondrupal/piwik
chmod -R 755 $elmsln/config/_nondrupal/piwik
# jobs file directory
chown -R $wwwuser:$webgroup $elmsln/config/jobs
chmod -R 755 $elmsln/config/jobs

# a message so you know where my head is at. you get candy if you reference this
echo 'Welcome to the Singularity of edtech.. Go forth, build the future.'
