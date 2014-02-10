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
# @todo Dann we need this to read from the hosts file somehow
# also, why is the hosts file separate from the rest of the configuration?
# seems like it could be consolidated
core='7.x'
distros=('cis' 'mooc' 'elmsmedia' 'remote_watchdog')
stacklist=('online' 'courses' 'media' 'studio')
# array of instance definitions for the distro type
instances=('FALSE' 'TRUE' 'TRUE' 'FALSE')
moduledir=$elmsln/config/shared/drupal-${core}/modules
cissettings=${university}_${host}_settings
# work on authoring the connector module automatically
# make an area specific to the university
mkdir ${moduledir}/${university}
mkdir ${moduledir}/${university}/${cissettings}
infofile=${moduledir}/${university}/${cissettings}/${cissettings}.info
modulefile=${moduledir}/${university}/${cissettings}/${cissettings}.module
# write the .info file
printf "name = ${university} ${host} Settings\ndescription = This contains registry information for all ${host} connection details\ncore = ${core}\npackage = ${university}" >> $infofile
# write the .module file
printf "<?php\n\n// service module that makes this implementation specific\n\n/**\n * Implements hook_cis_service_registry().\n */\nfunction ${university}_${host}_settings_cis_service_registry() {\n  \$items = array(\n" >> $modulefile
# write the array of connection values dynamically
COUNTER=0
char=(0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V X W Y Z)
max=${#char[*]}
for distro in "${distros[@]}"
do
  # array built up to password
  printf "    // ${distro} distro instance called ${stacklist[$COUNTER]}\n    '${distro}' => array(\n      'protocol' => '${protocol}',\n      'service_address' => 'data.${stacklist[$COUNTER]}.${serviceaddress}',\n      'address' => '${stacklist[$COUNTER]}.${host}.${address}',\n      'user' => 'SERVICE_${distro}_${host}',\n      'mail' => 'SERVICE_${distro}_${host}@${emailending}',\n      'pass' => '" >> $modulefile
  pass=''
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


# inital tests all passed, going to write all these into the jobs system

# cis jobs file
online=${fileloc}/online.online
touch $online
echo 'online' > $online
echo $host >> $online
echo "online.${$address}" >> $online
echo "data.online.${$serviceaddress}" >> $online
echo 'Online' >> $online
echo 'Welcome to ELMSLN' >> $online
echo $admin >> $online
echo 'cis' >> $online
echo "drush en ${cissettings}" >> $online
echo 'drush vset cron_safe_threshold 0' >> $online
echo 'drush vset user_register 1' >> $online
echo 'drush vset user_email_verification 0' >> $online
echo 'drush vset preprocess_css 1' >> $online
echo 'drush vset preprocess_js 1' >> $online
echo "drush vset file_private_path ${drupal_priv}/online/online" >> $online
echo 'drush vdel update_notify_emails' >> $online
echo 'drush cron' >> $online

# watchdog for the courses site
courseswd=${fileloc}/watchdog.courses
touch $courseswd
echo 'watchdog' > $courseswd
echo $host >> $courseswd
echo "courses.${$address}" >> $courseswd
echo "data.courses.${$serviceaddress}" >> $courseswd
echo 'Watchdog' >> $courseswd
echo 'Courses logging service' >> $courseswd
echo $admin >> $courseswd
echo 'remote_watchdog' >> $courseswd
echo "drush en ${cissettings}" >> $courseswd
echo 'drush vset cron_safe_threshold 0' >> $courseswd
echo 'drush vset user_register 1' >> $courseswd
echo 'drush vset user_email_verification 0' >> $courseswd
echo 'drush vset preprocess_css 1' >> $courseswd
echo 'drush vset preprocess_js 1' >> $courseswd
echo "drush vset file_private_path ${drupal_priv}/courses/watchdog" >> $courseswd
echo 'drush vdel update_notify_emails' >> $courseswd
echo 'drush cron' >> $courseswd
# watchdog for the media site
mediawd=${fileloc}/watchdog.media
touch $mediawd
echo 'watchdog' > $mediawd
echo $host >> $mediawd
echo "media.${$address}" >> $mediawd
echo "data.media.${$serviceaddress}" >> $mediawd
echo 'Watchdog' >> $mediawd
echo 'Media logging service' >> $mediawd
echo $admin >> $mediawd
echo 'remote_watchdog' >> $mediawd
echo "drush en ${cissettings}" >> $mediawd
echo 'drush vset cron_safe_threshold 0' >> $mediawd
echo 'drush vset user_register 1' >> $mediawd
echo 'drush vset user_email_verification 0' >> $mediawd
echo 'drush vset preprocess_css 1' >> $mediawd
echo 'drush vset preprocess_js 1' >> $mediawd
echo "drush vset file_private_path ${drupal_priv}/media/watchdog" >> $mediawd
echo 'drush vdel update_notify_emails' >> $mediawd
echo 'drush cron' >> $mediawd

# work on example course site
courses=${fileloc}/robots109.courses
touch $courses
echo 'robots109' > $courses
echo $host >> $courses
echo "courses.${$address}" >> $courses
echo "data.courses.${$serviceaddress}" >> $courses
echo 'Robots 109' >> $courses
echo 'An introduction to taking over the world' >> $courses
echo $admin >> $courses
echo 'mooc' >> $courses
echo "drush en cis_service_lti cis_remote_watchdog cis_service_restws ${cissettings}" >> $courses
echo 'drush vset cron_safe_threshold 0' >> $courses
echo 'drush vset user_register 1' >> $courses
echo 'drush vset user_email_verification 0' >> $courses
echo 'drush vset preprocess_css 1' >> $courses
echo 'drush vset preprocess_js 1' >> $courses
echo "drush vset file_private_path ${drupal_priv}/courses/robots109" >> $courses
echo 'drush vdel update_notify_emails' >> $courses
echo 'drush dis pathauto path' >> $courses
echo 'drush fr mooc_ux_defaults mooc_cis_ux cis_section cis_service_lti' >> $courses
echo 'drush pm-uninstall pathauto path' >> $courses
echo "drush feeds-import feeds_node_helper_book_import --file=${stacks}/online/profiles/cis/modules/custom/cis_helper/instructional_models/lesson-based.xml" >> $courses
echo 'drush cron' >> $courses
echo 'drush ecl' >> $courses
echo 'drush cron' >> $courses

# work on example media site
media=${fileloc}/robots109.media
touch $media
echo 'robots109' >> $media
echo $host >> $media
echo "media.${$address}" >> $media
echo "data.media.${$serviceaddress}" >> $media
echo 'Robots 109' >> $media
echo 'Robots 109 Asset management' >> $media
echo $admin >> $media
echo 'elmsmedia' >> $media
echo "drush en cis_remote_watchdog cis_service_restws ${cissettings}" >> $media
echo 'drush vset cron_safe_threshold 0' >> $media
echo 'drush vset user_register 1' >> $media
echo 'drush vset user_email_verification 0' >> $media
echo 'drush vset preprocess_js 1' >> $media
echo "drush vset file_private_path ${drupal_priv}/media/robots109" >> $media
echo 'drush vdel update_notify_emails' >> $media
echo 'drush cron' >> $media
echo 'drush ecl' >> $media
echo 'drush cron' >> $media
