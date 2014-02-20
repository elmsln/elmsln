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

core='7.x'
distros=('cis' 'mooc' 'elmsmedia' 'remote_watchdog')
stacklist=('online' 'courses' 'media' 'remote_watchdog')
# array of instance definitions for the distro type
instances=('FALSE' 'TRUE' 'TRUE' 'FALSE')
moduledir=$elmsln/config/shared/drupal-${core}/modules
cissettings=${university}_${host}_settings

# used for random password generation
COUNTER=0
char=(0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V X W Y Z)
max=${#char[*]}
pass=''
# work on authoring the connector module automatically if needed
mkdir ${moduledir}/${university}
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
    printf "    // ${distro} distro instance called ${stacklist[$COUNTER]}\n    '${distro}' => array(\n      'protocol' => '${protocol}',\n      'service_address' => 'data.${stacklist[$COUNTER]}.${serviceaddress}',\n      'address' => '${stacklist[$COUNTER]}.${host}.${address}',\n      'user' => 'SERVICE_${distro}_${host}',\n      'mail' => 'SERVICE_${distro}_${host}@${emailending}',\n      'pass' => '" >> $modulefile
    # generate a random 30 digit password
    for i in `seq 1 30`
    do
      let "rand=$RANDOM % 62"
      pass="${pass}${char[$rand]}"
    done
    # write password to file
    printf $pass >> $modulefile
    # finish off array
    printf "',\n      'instance' => ${instances[$COUNTER]},\n    ),\n" >> $modulefile
    COUNTER=$[COUNTER + 1]
  done
  # close out function and file
  printf "  );\n\n  return \$items;\n}" >> $modulefile
  # add the function to include this in build outs automatically
  printf "\n/**\n * Implements hook_cis_service_instance_options_alter().\n */\nfunction ${university}_${host}_cis_service_instance_options_alter(&/$options, /$course, /$service) {\n  // modules we require for all builds\n  /$options['en'][] = '$modulefile';\n}\n" >> $modulefile
fi
# make sure drush is happy post addition of drush files
/usr/bin/drush cc drush
# install default site for courses stack
# generate a random 30 digit password
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${pass}${char[$rand]}"
done
cd $stacks/courses
/usr/bin/drush site-install -y --db-url=mysql://default_courses:$dbpw@localhost/default_courses --db-su=$dbsu --db-su-pw=$dbsupw

# install default site for media stack
# generate a random 30 digit password
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${pass}${char[$rand]}"
done
cd $stacks/media
/usr/bin/drush site-install -y --db-url=mysql://default_media:$dbpw@localhost/default_media --db-su=$dbsu --db-su-pw=$dbsupw

# install default site for studio stack
# generate a random 30 digit password
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${pass}${char[$rand]}"
done
cd $stacks/studio
/usr/bin/drush site-install -y --db-url=mysql://default_media:$dbpw@localhost/default_media --db-su=$dbsu --db-su-pw=$dbsupw

# install default site for online stack
# generate a random 30 digit password
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${pass}${char[$rand]}"
done
cd $stacks/online
/usr/bin/drush site-install -y --db-url=mysql://default_online:$dbpw@localhost/default_online --db-su=$dbsu --db-su-pw=$dbsupw

# install the CIS site
# generate a random 30 digit password
for i in `seq 1 30`
do
  let "rand=$RANDOM % 62"
  dbpw="${pass}${char[$rand]}"
done
cd $stacks/online
/usr/bin/drush site-install cis -y --db-url=mysql://online_$host:$dbpw@localhost/online_$host --db-su=$dbsu --db-su-pw=$dbsupw --sites-subdir=onlinetmp --site-mail=$site_email --site-name=Online

sitedir=$stacks/online/sites
#create file directory
mkdir -p $sitedir/online
mv  $sitedir/onlinetmp $sitedir/online/$host
mkdir $sitedir/online/$host/files
chown $wwwuser:$webgroup $sitedir/online/$host/files
chmod 755 $sitedir/online/$host/files

#add site to the sites array

if [ -f $stacks/online/sites/sites.php ]; then
  arraytest=`/bin/grep -e "^\\$sites" $sitedir/sites.php`
  if [[ -z $arraytest ]]; then
    echo "\$sites = array(" >> $sitedir/sites.php
    echo "" >> $sitedir/sites.php
    echo ");" >> $sitedir/sites.php
  fi
  /bin/sed -i "/^\$sites = array/a \ \t \'$online_domain\' =\> \'online\/$host\'\," $sitedir/sites.php
  /bin/sed -i "/^\$sites = array/a \ \t \'$online_service_domain\' =\> \'online\/services\/$host\/\'\," $sitedir/sites.php
fi

# add in our cache bins - todo move to configsdir?
  echo "\$conf['cache_prefix'] = 'online_$host';" >> $sitedir/online/$host/settings.php
  echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/online/$host/settings.php

#adding servies conf file
if [ ! -d $sitedir/online/services/$host ];
  then mkdir -p $sitedir/online/services/$host
    mkdir $sitedir/online/services/$host/files
    chown $wwwuser:$webgroup $sitedir/online/services/$host/files
    chmod 755 $sitedir/online/services/$host/files
    if [ -f $sitedir/online/$host/settings.php ]; then
      /bin/cp $sitedir/online/$host/settings.php $sitedir/online/services/$host/settings.php
    fi
    if [ -f $sitedir/online/services/$host/settings.php ]; then
    echo "\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $sitedir/online/services/$host/settings.php
    fi
fi

#set base_url
/bin/sed -i "/\# \$base_url/a \ \t \$base_url= '$protocol://$online_domain';" $sitedir/online/$host/settings.php

# clean up tasks
/usr/bin/drush -y --uri=$protocol://$online_domain vset site_slogan 'Welcome to ELMSLN'
/usr/bin/drush -y --uri=$protocol://$online_domain en $cissettings
/usr/bin/drush -y --uri=$protocol://$online_domain vset cron_safe_threshold 0
/usr/bin/drush -y --uri=$protocol://$online_domain vset user_register 1
/usr/bin/drush -y --uri=$protocol://$online_domain vset user_email_verification 0
/usr/bin/drush -y --uri=$protocol://$online_domain vset preprocess_css 1
/usr/bin/drush -y --uri=$protocol://$online_domain vset preprocess_js 1
/usr/bin/drush -y --uri=$protocol://$online_domain vset file_private_path ${drupal_priv}/online/online
/usr/bin/drush -y --uri=$protocol://$online_domain vdel update_notify_emails
/usr/bin/drush -y --uri=$protocol://$online_domain cron

echo 'Lets see if it worked out..'
